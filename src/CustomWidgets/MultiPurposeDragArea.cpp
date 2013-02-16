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
#include "CustomWidgets/MultiPurposeDragArea.h"
#include <QMouseEvent>

MultiPurposeDragArea::MultiPurposeDragArea(QWidget * _parent): QWidget(_parent)
{}

MultiPurposeDragArea::~MultiPurposeDragArea()
{
}

void MultiPurposeDragArea::wheelEvent(QWheelEvent * event)
{
    int sign = event->delta() > 0 ? 1 : -1;
    emit changeTab(sign);
}

void MultiPurposeDragArea::mouseMoveEvent(QMouseEvent * event)
{
    if (modificationMode == wmm_none)
        return;

    emit newCoordinates(mapToGlobal(event->pos()));
}

void MultiPurposeDragArea::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton) {
        grabMouse();

        if (event->button() == Qt::LeftButton) {
            modificationMode = wmm_drag;
            emit initiateMove(mapToGlobal(event->pos()));
        }

        if (event->button() == Qt::RightButton) {
            modificationMode = wmm_resize;
            emit initiateResize(mapToGlobal(event->pos()));
        }
    }
}

void MultiPurposeDragArea::mouseReleaseEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton) {
        if (modificationMode == wmm_resize)
            emit endResize();

        if (modificationMode == wmm_drag)
            emit endMove();

        modificationMode = wmm_none;
        releaseMouse();
    }
}
