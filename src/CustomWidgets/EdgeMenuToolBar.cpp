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
#include "CustomWidgets/EdgeMenuToolBar.h"

EdgeMenuToolBar::EdgeMenuToolBar(QWidget * _parent) : QToolBar(_parent)
{
    connect(&decayTimer, SIGNAL(timeout()), this, SLOT(hide()));
}

EdgeMenuToolBar::~EdgeMenuToolBar()
{
}

void EdgeMenuToolBar::leaveEvent(QEvent *event)
{

    decayTimer.start(500);
}

void EdgeMenuToolBar::enterEvent(QEvent *event)
{
    decayTimer.stop();
}

void EdgeMenuToolBar::mouseMoveEvent(QMouseEvent *event)
{
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
    if(modificationMode == wmm_drag)
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
