// *************************************************************************
//
// Copyright 2012-2013 Nikolai Marchenko.
//
// This file is part of the Douml Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License Version 3.0 as published by
// the Free Software Foundation and appearing in the file LICENSE.GPL included in the
//  packaging of this file.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License Version 3.0 for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// e-mail : doumleditor@gmail.com
//
// *************************************************************************
#include "CustomWidgets/EdgeMenuToolBar.h"
#include "dialog/EdgeMenuDialog.h"
#include "misc/ClipboardManager.h"
#include <QAction>

EdgeMenuToolBar::EdgeMenuToolBar(QWidget * _parent) : QToolBar(_parent)
{
    clipboardMenu = new QMenu(this);
    lastClipboardItemShown = 0;
    clipboardListSize = 10;
    connect(&decayTimer, SIGNAL(timeout()), this, SLOT(hide()));
    An<ClipboardManager> clipboard;
    connect(this, SIGNAL(putIntoClipboard(QString)), clipboard.getData(), SLOT(OnPutItemIntoClipboard(QString)));
}


EdgeMenuToolBar::~EdgeMenuToolBar()
{
}

void EdgeMenuToolBar::SetRelativeOrientation(int value)
{
    relativeOrientation = value;
}

void EdgeMenuToolBar::SetDialog(EdgeMenuDialog * dialog)
{
    linkedDialog = dialog;
}

void EdgeMenuToolBar::leaveEvent(QEvent * )
{
    decayTimer.start(15000);
}

void EdgeMenuToolBar::enterEvent(QEvent * )
{
    decayTimer.stop();
}

void EdgeMenuToolBar::focusOutEvent(QFocusEvent *)
{
    if (!linkedDialog->hasFocus())
        hide();
}

void EdgeMenuToolBar::IntitiateMove(QPoint origin)
{
    decayTimer.stop();
    modificationMode = wmm_drag;
    modificationOrigin = origin;
    toolbarOrigin = mapToGlobal(QPoint());
}

void EdgeMenuToolBar::IntitiateResize(QPoint)
{
    decayTimer.stop();
    modificationMode = wmm_resize;
}

void EdgeMenuToolBar::MoveThis(QPoint origin, QPoint newPoint)
{
    this->move(newPoint - origin + toolbarOrigin);
}

void EdgeMenuToolBar::FillClipboardMenu(int base)
{
    clipboardMenu->clear();
    An<ClipboardManager> clipboard;
    QStringList strings = clipboard->GetStrings();

    if (base != 0) {
        QAction * lessClipboard = new QAction("Less Clipboard", clipboardMenu);
        connect(lessClipboard, SIGNAL(triggered()), this, SLOT(OnLessClipboardRequested()));
        clipboardMenu->addAction(lessClipboard);
    }

    int maxItems = strings.size() > 10 ? 10 : strings.size();
    int i = base;

    for (; i < maxItems; ++i) {
        QString text = strings.at(strings.size() - 1 - i);
        clipboard->blockSignals(true);
        QString itemText;

        if (text.length() < 15)
            itemText = text;
        else {
            text.left(15);
            itemText = text  + "...";
        }

        QAction * action = new QAction(itemText, clipboardMenu);
        action->setData(text);
        connect(action, SIGNAL(triggered()), this, SLOT(OnPutIntoClipboardRequested()));
        clipboard->blockSignals(false);
        clipboardMenu->addAction(action);

    }

    lastClipboardItemShown += i;

    if (lastClipboardItemShown < strings.size()) {
        QAction * moreClipboard = new QAction("More Clipboard", clipboardMenu);
        connect(moreClipboard, SIGNAL(triggered()), this, SLOT(OnMoreClipboardRequested()));
        clipboardMenu->addAction(moreClipboard);
    }

}

void EdgeMenuToolBar::OnInitiateMove(QPoint origin)
{
    IntitiateMove(origin);
}

void EdgeMenuToolBar::OnInitiateResize(QPoint origin)
{
    IntitiateResize(origin);
}

void EdgeMenuToolBar::OnNewCoordinatesReceived(QPoint newPoint)
{
    if (modificationMode == wmm_drag)
        MoveThis(modificationOrigin, newPoint);
}

void EdgeMenuToolBar::OnEndResize()
{
    this->hide();
}

void EdgeMenuToolBar::OnEndMove()
{
    this->show();
    //todo to implement
}

void EdgeMenuToolBar::OnClipboardRequested()
{
    FillClipboardMenu(0);
    clipboardMenu->exec(this->mapToGlobal(QPoint(0, 0)));
}

void EdgeMenuToolBar::OnMoreClipboardRequested()
{
    FillClipboardMenu(lastClipboardItemShown);
}

void EdgeMenuToolBar::OnLessClipboardRequested()
{
    FillClipboardMenu(lastClipboardItemShown - clipboardListSize);
}

void EdgeMenuToolBar::OnPutIntoClipboardRequested()
{
    QAction * senderAction = qobject_cast<QAction *>(sender());
    emit putIntoClipboard(senderAction->data().toString());
}

void EdgeMenuToolBar::OnDialogLostFocus()
{
    if (!this->underMouse())
        hide();
}

void EdgeMenuToolBar::OnMenuRepositionRequested(const QPoint & diff)
{
    this->move(this->pos() + diff);
}

void EdgeMenuToolBar::OnMenuHideRequested()
{
    hide();
}
