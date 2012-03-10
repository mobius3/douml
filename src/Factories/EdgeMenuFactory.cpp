// *************************************************************************
//
// Copyright 2012-2012 Nikolai Marchenko.
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
#include "EdgeMenuFactory.h"
#include "dialog/EdgeMenuDialog.h"
#include "dialog/ClassDialog.h" //< todo Temporary
#include "Factories/DialogConnections.h"
#include "Factories/EdgeToolBarCreation.h"
#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCursor>
#include <QPushButton>

void EdgeMenuFactory::OnEdgeMenuRequested(uint classID)
{
    EdgeMenuDialog* senderWidget = qobject_cast<EdgeMenuDialog*>(sender());
    SpawnEdgeMenu(classID,senderWidget);
}

void EdgeMenuFactory::SpawnEdgeMenu(uint classID, EdgeMenuDialog* senderWidget)
{
    QToolBar* toolbar;
    if(!createdToolbars.contains(classID))
    {
        toolbar = (factories[classID])();
        createdToolbars.insert(classID,toolbar);
    }
    toolbar = createdToolbars[classID];


    int trueOrientation = ClosestEdge(senderWidget, QCursor::pos());
    int orientation;

    // position 0 and 1 signify horizontal orientation
    //          2 and 3 signify  vertical orientation
    if(trueOrientation < 2)
        orientation = 1;
    else
        orientation = 2;

    toolbar->setOrientation(static_cast<Qt::Orientation>(orientation));
    QPoint point = QCursor::pos();
    //now we need to position toolbar correctly

    int toolBarIconHeight = 30;
    int toolBarIconWidth = 30;

    // if we are near the top
    if(trueOrientation == 0)
    {
        point.setY(point.y() - toolBarIconHeight);
        point.setX(point.x() - toolBarIconWidth/2);
    }
    // if we are near the top
    if(trueOrientation == 1)
    {
        point.setY(point.y());
        point.setX(point.x() - toolBarIconWidth/2);
    }
    // if we are near the left edge
    if(trueOrientation == 2)
    {
        point.setX(point.x() - toolBarIconWidth);
        point.setY(point.y() - toolBarIconHeight/2);
    }
    // if we are near the right edge
    if(trueOrientation == 3)
    {
        point.setX(point.x());
        point.setY(point.y() - toolBarIconHeight/2);
    }
    toolbar->move(point);

    if(!senderWidget->IsConnectedToToolBar())
        signalFunctors[classID](senderWidget, toolbar);

    toolbar->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
    toolbar->resize(toolbar->sizeHint());
    toolbar->show();
}

void EdgeMenuFactory::AddFactory(uint id, ToolbarFactory factory)
{
    if(!factories.contains(id))
    {
        factories.insert(id,factory);
    }
}

void EdgeMenuFactory::AddConnectionFunctor(uint classID, ConnectionFunctor functor)
{
    if(!signalFunctors.contains(classID))
    {
        signalFunctors.insert(classID,functor);
    }
}

void EdgeMenuFactory::SpawnEdgeMenu(uint classID, EdgeMenuDialog* parent,  QPoint origin)
{
    SpawnEdgeMenu(classID, parent);
}

EdgeMenuFactory::~EdgeMenuFactory()
{
}

EdgeMenuFactory::EdgeMenuFactory()
{
}
