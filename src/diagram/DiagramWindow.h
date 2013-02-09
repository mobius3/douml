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

#ifndef DIAGRAMWINDOW_H
#define DIAGRAMWINDOW_H

#include <q3canvas.h>
#include <q3mainwindow.h>
#include <QTextStream>

#include "UmlEnum.h"

class QPrinter;
class QToolButton;
class QSpinBox;
class QComboBox;
class Q3ToolBar;

class BrowserDiagram;
class UmlCanvas;
class DiagramView;

#define SCALE_MIN 30
#define SCALE_MAX 200

/* This represents a window that is a diagram, have a canvas and a toolbox */
class DiagramWindow : public Q3MainWindow
{
    Q_OBJECT

protected:
    bool no_save;
    UmlCanvas * canvas;
    /* This links us to the diagram in the browser */
    BrowserDiagram * browser_node = nullptr;
    UmlCode current_button;

    QToolButton * select;
    QSpinBox * sb_zoom;
    QToolButton * optwinsize;
    QComboBox * viewmode;
    QToolButton * edit;






public:
    DiagramWindow(BrowserDiagram * br, const QString & s);
    virtual ~DiagramWindow();

    virtual DiagramView * get_view() const = 0;

    void raise();

    virtual void hit_button(UmlCode, QToolButton *) = 0;
    void selectOn();
    UmlCode & buttonOn() {
        return current_button;
    };

    void add_edit_button(Q3ToolBar *);
    void add_scale_cmd(Q3ToolBar *);
    void change_zoom(int);

    BrowserDiagram * browser_diagram() const {
        return browser_node;
    };

    void set_browser_diagram(BrowserDiagram* value)
    {
        browser_node = value;
    }
    void package_modified() const;
    bool frozen() const;

    void save(const char * ext, QString & warning, BooL & is_new) const;
    void duplicate(int dest_id, const char * ext) const;
    QString copy_selected() const;

    void dont_save() {
        no_save = TRUE;
    };

    void save_session(QTextStream & st);
    void read_session(char *& st);

public slots:
    void new_scale(int);
    void fit_scale();
    void optimal_window_size();
    void session_window_size();
    virtual void call_menu();

protected slots:
    void hit_select();
};

#endif
