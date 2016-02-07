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

#ifndef DIAGRAMVIEW_H
#define DIAGRAMVIEW_H
#include <QList>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTextStream>
//Added by qt3to4:

#include <QWheelEvent>
#include <QList>
#include <QMouseEvent>
////#include <QMenu>
#include <QKeyEvent>

#include "UmlEnum.h"
#include "UmlCanvas.h"

#ifndef QT_NO_PRINTER
class QPrinter;
#endif
class QKeyEvent;
class QMenu;
class QBuffer;

class DiagramItem;
class DiagramWindow;

#define EDIT_DRAWING_SETTING_CMD 0
#define RELOAD_CMD 6

class DiagramView : public QGraphicsView
{
    Q_OBJECT

protected:
    int id;
    int pressedButton;
    QPoint mousePressPos;	// mouse position when it is pressed or moved
    QGraphicsRectItem * selectArea;
    DiagramItem * start;	// last added line part start
    QGraphicsLineItem * line;
    DiagramItem * arrowBeginning;// broken line start
    QList<QGraphicsItem*> temp;
    QSize preferred_size;
    double preferred_zoom;
    bool draw_line;
    aCorner do_resize;
    bool history_protected;
    bool history_frozen;
    bool first_move;
    bool on_arrow_decenter;
    BooL decenter_start;
    BooL decenter_horiz;
    QList<QPoint> previousResizeCorrection;
    QList<QByteArray> history;
    int history_index;




    static WrapperStr clipboard;
    static UmlCode copied_from;

public:
    DiagramView(QWidget * parent, UmlCanvas * canvas, int i);

    void select_all();
    void unselect_all() {
        the_canvas()->unselect_all();
    };
    const QList<QGraphicsItem*> & selection() {
        return the_canvas()->selection();
    };
    void select(QGraphicsItem * i) {
        the_canvas()->select(i);
    };
    void unselect(QGraphicsItem * i) {
        the_canvas()->unselect(i);
    };
    void abort_line_construction();
    void relation_to_simplerelation(UmlCode k);
    void set_zoom(double);
    void fit_scale();
    void preferred_size_zoom();
    bool has_preferred_size_zoom() {
        return preferred_zoom != 0;
    }
    void multiple_selection_menu(bool in_model, bool out_model, bool alignable,
                                 int n_resize, QList<DiagramItem *> & l_drawing_settings);
    bool is_present(BrowserNode * bn);
    virtual void add_related_elements(DiagramItem *, QString what,
                                      bool inh, bool assoc);

    virtual UmlCanvas * the_canvas() const;
    QGraphicsScene *canvas() const;

    virtual void menu(const QPoint &) = 0;

    void read();
    void paste();
    virtual void read(char *, char * k) = 0;
    virtual void save(QTextStream & st, QString & warning, bool copy) const = 0;
    void load(const char *);

    void protect_history(bool y) {
        history_protected = y;
    }
    void freeze_history(bool y) {
        history_frozen = y;
    }
    void history_save(bool on_undo = FALSE);
    void history_load();
    void update_history();
    void undo();
    void redo();
    bool available_undo();
    bool available_redo();

    void save_session(QTextStream & st);
    void read_session(char *& st);

    static void init();

#ifndef QT_NO_PRINTER
    void print(QPrinter & p, int div);
#endif

    void copy_in_clipboard(bool optimal, bool temporary);
    bool save_pict(const char * f, bool optimal, bool temporary);
    bool save_in(const char * f, bool optimal, bool temporary);
    bool svg_save_in(const char * f, bool optimal, bool temporary);

    void renumber(int ident);

    void do_optimal_window_size();

private:
    DiagramWindow * window() const {
        return (DiagramWindow *) parent();
    };

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void wheelEvent(QWheelEvent *);
    void moveSelected(int dx, int dy, bool first);
    void resizeSelected(int dx, int dy);
    void add_point(QMouseEvent * e);
    bool multiple_selection_for_menu(BooL & in_model, BooL & out_model,
                                     BooL & alignable, int & n_resize,
                                     QList<DiagramItem *> & l_drawing_settings,
                                     const QList<QGraphicsItem*> & selected);

    void set_format(int);
    void init_format_menu(QMenu &, QMenu &, int) const;
    int default_menu(QMenu & m, int f);
    void needed_width_height(int & maxx, int & maxy, int & minx, int & miny) const;

    void save_picture(bool optimal, bool svg);

    void alignLeft();
    void alignRight();
    void alignTop();
    void alignBottom();
    void alignCenter();
    void alignHorizontaly();
    void alignVerticaly();
    void same_size(bool w, bool h);

    void delete_them(bool in_model);

protected slots:
    virtual void keyPressEvent(QKeyEvent * e);
private slots:
    virtual void keyReleaseEvent(QKeyEvent *);
    void optimal_window_size();
    void restore_window_size();

    void update() {
        canvas()->update();
    };
};

#endif
