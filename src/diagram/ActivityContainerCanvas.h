// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
// Copyright 2012-2013 Nikolai Marchenko.
// Copyright 2012-2013 Leonardo Guilherme.
//
// This file is part of the DOUML Uml Toolkit.
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
// home   : http://sourceforge.net/projects/douml
//
// *************************************************************************

#ifndef ACTIVITYCONTAINERCANVAS_H
#define ACTIVITYCONTAINERCANVAS_H





#include "DiagramCanvas.h"

class ActivityContainerCanvas : public DiagramCanvas
{
protected:
    ActivityContainerCanvas(UmlCanvas * canvas, int id)
        : DiagramCanvas(canvas, id) {
    }

public:
    ActivityContainerCanvas(BrowserNode * bn, UmlCanvas * canvas,
                            int x, int y, int w, int h, int id)
        : DiagramCanvas(bn, canvas, x, y, w, h, id) {
    }

    void force_inside(DiagramItem * di, QGraphicsItem * ci, BooL & need_sub_upper);
    void force_sub_inside(QList<QGraphicsItem*> & all, BooL & need_sub_upper);
    void resize_to_contain(QList<QGraphicsItem*> & all, BooL & need_sub_upper);
    void force_sub_upper(QList<QGraphicsItem*> & all);
    virtual void prepare_for_move(bool on_resize);
    static bool force_inside(DiagramCanvas * elt, bool part);
};

#endif
