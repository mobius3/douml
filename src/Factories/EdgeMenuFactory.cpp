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
#include "EdgeMenuFactory.h"
#include "dialog/EdgeMenuDialog.h"
#include "dialog/edgemenudialogqt4.h"
#include "Factories/DialogConnections.h"
#include "Factories/EdgeToolBarCreation.h"
#include "CustomWidgets/EdgeMenuToolBar.h"
#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCursor>
#include <QPushButton>

void EdgeMenuFactory::OnEdgeMenuRequested(uint classID)
{
    SpawnEdgeMenu(classID, dynamic_cast<EdgeMenuDialogBase*>(sender()));
}

void EdgeMenuFactory::SpawnEdgeMenu(uint classID, EdgeMenuDialogBase * sender)
{
    EdgeMenuToolBar * toolbar;

    if (!createdToolbars.contains(classID)) {
        toolbar = (factories[classID])();
        createdToolbars.insert(classID, toolbar);
    }

    toolbar = createdToolbars[classID];
    toolbar->setAttribute(Qt::WA_ShowWithoutActivating);

    QDialog* senderDialog = dynamic_cast<QDialog *>(sender);
    toolbar->setParent(senderDialog);


    int trueOrientation = ClosestEdge(senderDialog, QCursor::pos());
    int orientation;

    // position 0 and 1 signify horizontal orientation
    //          2 and 3 signify  vertical orientation
    if (trueOrientation < 2)
        orientation = 1;
    else
        orientation = 2;

    if (!sender->IsConnectedToToolBar())
    {
        EdgeMenuDialog * senderWidget = dynamic_cast<EdgeMenuDialog *>(sender);
        EdgeMenuDialogQt4 * senderWidgetqt4 = dynamic_cast<EdgeMenuDialogQt4 *>(sender);
        if(senderWidget)
            signalFunctors[classID](senderWidget, toolbar);
        else
            signalFunctorsQt4[classID](senderWidgetqt4, toolbar);
    }

    toolbar->setOrientation(static_cast<Qt::Orientation>(orientation));
    QPoint point = QCursor::pos();
    //now we need to position toolbar correctly

    int toolBarIconHeight = 30;
    int toolBarIconWidth = 30;

    // if we are near the top
    if (trueOrientation == 0)
    {
        int yFixup = senderDialog->frameGeometry().height() - senderDialog->height();
        QPoint yEventClamp = senderDialog->mapToGlobal(QPoint(0,0));
        point.setY(yEventClamp.y() - toolBarIconHeight - yFixup);
        point.setX(point.x() - toolBarIconWidth / 2);
    }

    // if we are near the top
    if (trueOrientation == 1)
    {
        QPoint yEventClamp = senderDialog->mapToGlobal(QPoint(0,senderDialog->height()));
        point.setY(yEventClamp.y());
        point.setX(point.x() - toolBarIconWidth / 2);
    }

    // if we are near the left edge
    if (trueOrientation == 2)
    {
        point.setX(point.x() - toolBarIconWidth);
        point.setY(point.y() - toolBarIconHeight / 2);
    }

    // if we are near the right edge
    if (trueOrientation == 3)
    {
        point.setX(point.x());
        point.setY(point.y() - toolBarIconHeight / 2);
    }

    toolbar->move(point);
    toolbar->resize(toolbar->sizeHint());

    if (!toolbar->isVisible()) {
        toolbar->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
        toolbar->setAttribute(Qt::WA_ShowWithoutActivating);
        toolbar->show();
    }
}

void EdgeMenuFactory::AddFactory(uint id, ToolbarFactory factory)
{
    if (!factories.contains(id)) {
        factories.insert(id, factory);
    }
}

void EdgeMenuFactory::AddConnectionFunctor(uint classID, ConnectionFunctor functor)
{
    if (!signalFunctors.contains(classID)) {
        signalFunctors.insert(classID, functor);
    }
}

void EdgeMenuFactory::AddConnectionFunctorQt4(uint classID, ConnectionFunctorQt4 functor)
{
    if (!signalFunctorsQt4.contains(classID)) {
        signalFunctorsQt4.insert(classID, functor);
    }
}

EdgeMenuFactory::~EdgeMenuFactory()
{
}

EdgeMenuFactory::EdgeMenuFactory()
{
}
