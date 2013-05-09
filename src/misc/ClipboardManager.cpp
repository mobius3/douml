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
#include "misc/ClipboardManager.h"
#include <QClipboard>
#include <QApplication>
#include <QMimeSource>
#include <QMimeData>


ClipboardManager::ClipboardManager(QObject * _parent): QObject(_parent)
{}

QStringList ClipboardManager::GetStrings()
{
    return strings;
}

QMenu* ClipboardManager::GetMenuInstance(int base, QMenu* existingMenu)
{
    if(!existingMenu)
    {
        if(!clipboardMenu)
            clipboardMenu = new QMenu();
        existingMenu = clipboardMenu;
    }
    FillClipboardMenu(existingMenu, base);
    return existingMenu;
}
ClipboardManager::~ClipboardManager()
{}

void ClipboardManager::OnClipboardUpdate()
{
    QClipboard * clipboard = QApplication::clipboard();
    const QMimeData * data = clipboard->mimeData();

    if (data->hasText())
        strings += data->text();
}

void ClipboardManager::OnPutItemIntoClipboard(QString text)
{
    QClipboard * clipboard = QApplication::clipboard();
    clipboard->setText(text);
}

void ClipboardManager::OnPutItemIntoClipboardRequested()
{
    QAction * senderAction = qobject_cast<QAction *>(sender());
    OnPutItemIntoClipboard(senderAction->data().toString());
}

void ClipboardManager::OnClipboardRequested()
{

}

void ClipboardManager::OnMoreClipboardRequested()
{
    FillClipboardMenu(clipboardMenu, lastClipboardItemShown);
}

void ClipboardManager::OnLessClipboardRequested()
{
    FillClipboardMenu(clipboardMenu, lastClipboardItemShown - clipboardListSize);
}

void ClipboardManager::FillClipboardMenu(QMenu * clipboardMenu, int base)
{
    clipboardMenu->clear();
    if (base != 0)
    {
        QAction * lessClipboard = new QAction("Less Clipboard", clipboardMenu);
        connect(lessClipboard, SIGNAL(triggered()), this, SLOT(OnLessClipboardRequested()));
        clipboardMenu->addAction(lessClipboard);
    }

    int maxItems = strings.size() > 10 ? 10 : strings.size();
    int i = base;

    for (; i < maxItems; ++i) {
        QString text = strings.at(strings.size() - 1 - i);
        this->blockSignals(true);
        QString itemText;

        if (text.length() < 15)
            itemText = text;
        else {
            text.left(15);
            itemText = text  + "...";
        }

        QAction * action = new QAction(itemText, clipboardMenu);
        action->setData(text);
        connect(action, SIGNAL(triggered()), this, SLOT(OnPutItemIntoClipboardRequested()));
        this->blockSignals(false);
        clipboardMenu->addAction(action);

    }

    lastClipboardItemShown += i;

    if (lastClipboardItemShown < strings.size()) {
        QAction * moreClipboard = new QAction("More Clipboard", clipboardMenu);
        connect(moreClipboard, SIGNAL(triggered()), this, SLOT(OnMoreClipboardRequested()));
        clipboardMenu->addAction(moreClipboard);
    }
}

