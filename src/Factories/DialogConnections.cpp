// *************************************************************************
//
// Copyright 2012-2012 Nikolai Marchenko  .
//
// This file is part of the BreezeUML Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// e-mail : enmarantispam@gmail.com
//
// *************************************************************************
#include "Factories/DialogConnections.h"
#include "CustomWidgets/MultiPurposeDragArea.h"
#include "CustomWidgets/EdgeMenuToolBar.h"
#include "dialog/EdgeMenuDialog.h"
#include "QPushButton"

void ConnectToClassDialog(EdgeMenuDialog* dialog, EdgeMenuToolBar* toolbar)
{

    MultiPurposeDragArea* dragArea = qobject_cast<MultiPurposeDragArea*>(toolbar->findChild<MultiPurposeDragArea*>("DragArea"));
    QObject::connect(dragArea, SIGNAL(changeTab(int)), dialog, SLOT(OnChangeTab(int)));
    QObject::connect(dragArea, SIGNAL(initiateMove(QPoint)), dialog, SLOT(OnInitiateMove(QPoint)));
    QObject::connect(dragArea, SIGNAL(initiateResize(QPoint)), dialog, SLOT(OnInitiateResize(QPoint)));
    QObject::connect(dragArea, SIGNAL(newCoordinates(QPoint)), dialog, SLOT(OnNewCoordinatesReceived(QPoint)));

    QObject::connect(dragArea, SIGNAL(initiateMove(QPoint)), toolbar, SLOT(OnInitiateMove(QPoint)));
    QObject::connect(dragArea, SIGNAL(initiateResize(QPoint)), toolbar, SLOT(OnInitiateResize(QPoint)));
    QObject::connect(dragArea, SIGNAL(newCoordinates(QPoint)), toolbar, SLOT(OnNewCoordinatesReceived(QPoint)));
    QObject::connect(dragArea, SIGNAL(endResize()), toolbar, SLOT(OnEndResize()));
    QObject::connect(dragArea, SIGNAL(endMove()), toolbar, SLOT(OnEndMove()));


    QPushButton* pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("NextElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), dialog, SLOT(OnPickNextSibling()));

    pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("PreviousElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), dialog, SLOT(OnPickPreviousSibling()));

    ConnectToLimitedtDialog(dialog, toolbar);

    dialog->ConnectionToToolBarEstablished();
}


void ConnectToLimitedtDialog(EdgeMenuDialog* dialog, EdgeMenuToolBar* toolbar)
{
    QPushButton* pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("OkayElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), dialog, SLOT(accept()));
    pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("CancelElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), dialog, SLOT(reject()));

    pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("OkayElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), toolbar, SLOT(close()));
    pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("CancelElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), toolbar, SLOT(close()));
    dialog->ConnectionToToolBarEstablished();

    QAction* clipAction = qobject_cast<QAction*>(toolbar->findChild<QAction*>("Clipboard"));
    QObject::connect(clipAction, SIGNAL(triggered()), toolbar, SLOT(OnClipboardRequested()));

}
