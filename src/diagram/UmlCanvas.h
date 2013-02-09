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

#ifndef UMLCANVAS
#define UMLCANVAS





#include <q3canvas.h>
#include <qfont.h>
#include <q3intdict.h>

#include "UmlEnum.h"
#include "Labeled.h"

class Q3CanvasLine;
class QPainter;
class BrowserNode;
class BrowserDiagram;
class DiagramView;
class DiagramItem;

class UmlCanvas : public Q3Canvas
{
    Q_OBJECT

protected:
    Q3CanvasItemList selected;
    BrowserDiagram * br_diagram;
    DiagramView * view;
    bool do_scale;
    bool do_paste;
    bool show_shadow;
    bool draw_all_relations;
    bool saved_draw_all_relations;
    double zoom_value;
    int width100percent;
    int height100percent;
    QFont the_fonts[UmlFontNumber];
    IdDict<DiagramItem> all_items;	// to re-use the same id for the DiagramItems
    Q3CanvasLine * hlimit;
    Q3CanvasLine * vlimit;

    void update_limits();

public:
    UmlCanvas(CanvasFormat f, BrowserDiagram * br_diag);
    virtual ~UmlCanvas();

    Q3CanvasItem * collision(const QPoint &) const;
    Q3CanvasItem * collision(const QPoint &, int except) const;
    const Q3CanvasItemList & selection() const {
        return selected;
    };
    void select(Q3CanvasItem * i);
    void unselect(Q3CanvasItem * i);
    void unselect_all();

    void del(Q3CanvasItem * i);

    void set_zoom(double zm);
    void zoom_end() {
        do_scale = FALSE;
    };
    bool do_zoom() const {
        return do_scale;
    };
    double zoom() const {
        return zoom_value;
    };

    void resize(CanvasFormat);

    int shadow() const;
    bool must_draw_all_relations() const {
        return draw_all_relations;
    }
    void dont_draw_all_relations();
    void freeze_draw_all_relations() {
        saved_draw_all_relations = draw_all_relations;
        draw_all_relations = FALSE;
    }
    void unfreeze_draw_all_relations() {
        draw_all_relations = saved_draw_all_relations;
    }
    static void update_global_settings();

    QFont get_font(UmlFont f) const {
        return the_fonts[f];
    };

    BrowserDiagram * browser_diagram() const {
        return br_diagram;
    };
    void set_view(DiagramView * v);
    DiagramView * get_view() const {
        return view;
    };

    IdDict<DiagramItem> & get_all_items() {
        return all_items;
    }
    void read_old_diagram(bool y) {
        all_items.read_old_diagram(y);
    }
    void set_paste(bool y) {
        do_paste = y;
        all_items.read_old_diagram(y);
    }
    bool paste() {
        return do_paste;
    }
    void clear_old_ids() {
        all_items.clear(TRUE);
    }

    void show_limits(bool y);

    bool already_drawn(BrowserNode * bn);

public slots:
    virtual void update();
};

#endif
