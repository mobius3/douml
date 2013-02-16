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
#ifndef DIALOGCONNECTIONS_H
#define DIALOGCONNECTIONS_H

#include <QToolBar>
class EdgeMenuDialog;
class EdgeMenuToolBar;
#include "Factories/DialogConnections.h"
#include "CustomWidgets/MultiPurposeDragArea.h"
#include "CustomWidgets/EdgeMenuToolBar.h"
#include "dialog/EdgeMenuDialog.h"
#include "QPushButton"
template<typename DialogType>
void ConnectToLimitedDialog(DialogType * dialog, EdgeMenuToolBar * toolbar)
{
    QPushButton * pageButton = qobject_cast<QPushButton *>(toolbar->findChild<QPushButton *>("OkayElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), dialog, SLOT(accept()));
    pageButton = qobject_cast<QPushButton *>(toolbar->findChild<QPushButton *>("CancelElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), dialog, SLOT(reject()));

    pageButton = qobject_cast<QPushButton *>(toolbar->findChild<QPushButton *>("OkayElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), toolbar, SLOT(close()));
    pageButton = qobject_cast<QPushButton *>(toolbar->findChild<QPushButton *>("CancelElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), toolbar, SLOT(close()));

    MultiPurposeDragArea * dragArea = qobject_cast<MultiPurposeDragArea *>(toolbar->findChild<MultiPurposeDragArea *>("DragArea"));
    QObject::connect(dragArea, SIGNAL(initiateMove(QPoint)), dialog, SLOT(OnInitiateMove(QPoint)));
    QObject::connect(dragArea, SIGNAL(initiateResize(QPoint)), dialog, SLOT(OnInitiateResize(QPoint)));
    QObject::connect(dragArea, SIGNAL(newCoordinates(QPoint)), dialog, SLOT(OnNewCoordinatesReceived(QPoint)));

    QObject::connect(dragArea, SIGNAL(initiateMove(QPoint)), toolbar, SLOT(OnInitiateMove(QPoint)));
    QObject::connect(dragArea, SIGNAL(initiateResize(QPoint)), toolbar, SLOT(OnInitiateResize(QPoint)));
    QObject::connect(dragArea, SIGNAL(newCoordinates(QPoint)), toolbar, SLOT(OnNewCoordinatesReceived(QPoint)));

    QObject::connect(dragArea, SIGNAL(endResize()), toolbar, SLOT(OnEndResize()));
    QObject::connect(dragArea, SIGNAL(endMove()), toolbar, SLOT(OnEndMove()));
    QObject::connect(dialog, SIGNAL(lostFocus()), toolbar, SLOT(OnDialogLostFocus()));
    QObject::connect(dialog, SIGNAL(hideEdgeMenu()), toolbar, SLOT(OnMenuHideRequested()));
    QObject::connect(dialog, SIGNAL(repositionMenu(QPoint)), toolbar, SLOT(OnMenuRepositionRequested(QPoint)));

    QAction * clipAction = qobject_cast<QAction *>(toolbar->findChild<QAction *>("Clipboard"));
    QObject::connect(clipAction, SIGNAL(triggered()), toolbar, SLOT(OnClipboardRequested()));
    dialog->ConnectionToToolBarEstablished();
    dialog->SetToolBar(toolbar);
    //toolbar->setParent(dialog);
}
template<typename DialogType>
void ConnectToClassDialog(DialogType * dialog, EdgeMenuToolBar * toolbar)
{
    MultiPurposeDragArea * dragArea = qobject_cast<MultiPurposeDragArea *>(toolbar->findChild<MultiPurposeDragArea *>("DragArea"));
    QObject::connect(dragArea, SIGNAL(changeTab(int)), dialog, SLOT(OnChangeTab(int)));

    QPushButton * pageButton = qobject_cast<QPushButton *>(toolbar->findChild<QPushButton *>("NextElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), dialog, SLOT(OnPickNextSibling()));

    pageButton = qobject_cast<QPushButton *>(toolbar->findChild<QPushButton *>("PreviousElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), dialog, SLOT(OnPickPreviousSibling()));

    ConnectToLimitedDialog<DialogType>(dialog, toolbar);
}




#endif // DIALOGCONNECTIONS_H
