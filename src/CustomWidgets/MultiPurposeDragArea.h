// *************************************************************************
//
// Copyright 2012-2013 Nikolai Marchenko  .
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
#ifndef MULTIPURPOSEDRAGAREA_H
#define MULTIPURPOSEDRAGAREA_H

#include <QWidget>

enum EWidgetModificationMode {
    wmm_none = 0,
    wmm_drag = 1,
    wmm_resize = 2
};

class MultiPurposeDragArea : public QWidget
{
    Q_OBJECT
public:
    MultiPurposeDragArea(QWidget * _parent = 0);
    ~MultiPurposeDragArea();
protected:
    //! called when user srolls with mouse wheel
    void wheelEvent(QWheelEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event) ;
    EWidgetModificationMode modificationMode;

signals:
    void initiateMove(QPoint);
    void initiateResize(QPoint);
    void endResize();
    void endMove();
    void newCoordinates(QPoint);
    void changeTab(int);
};


#endif // MULTIPURPOSEDRAGAREA_H
