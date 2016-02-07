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

#ifndef COMPONENTCANVAS_H
#define COMPONENTCANVAS_H





#include <qobject.h>
//Added by qt3to4:
#include <QTextStream>

#include "DiagramCanvas.h"
#include "MultipleDependency.h"
#include "Settings.h"

#define COMPONENT_CANVAS_MIN_SIZE 40

class ComponentCanvas : public QObject, public DiagramCanvas,
    public MultipleDependency<BasicData>
{
    Q_OBJECT

protected:
    ComponentDrawingSettings settings;
    UmlColor itscolor;
    UmlColor used_color;
    bool as_icon;
    bool req_prov;
    bool rea;
    int min_width;
    int min_height;

protected:
    ComponentCanvas(UmlCanvas * canvas, int id);
    bool valid(ArrowCanvas * a) const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
public:
    ComponentCanvas(BrowserNode * bn, UmlCanvas * canvas, int x, int y);
    virtual ~ComponentCanvas();

    virtual void delete_it() override;

    void compute_size();

    virtual void draw(QPainter & p);
    virtual void change_scale() override;

    virtual UmlCode typeUmlCode() const override;
    virtual void delete_available(BooL & in_model, BooL & out_model) const override;
    virtual bool alignable() const override;
    virtual bool copyable() const override;
    virtual void remove(bool from_model) override;
    virtual void open() override;
    virtual void menu(const QPoint &) override;
    virtual QString may_start(UmlCode &) const override;
    virtual bool may_connect(UmlCode l) const override;
    virtual QString may_connect(UmlCode & l, const DiagramItem * dest) const override;
    virtual bool connexion(UmlCode action, const QPoint &, const QPoint &) override;
    virtual void connexion(UmlCode, DiagramItem *, const QPoint &, const QPoint &) override;
    virtual void check_line(ArrowCanvas * l) override;
    virtual aCorner on_resize_point(const QPoint & p) override;
    virtual void resize(aCorner c, int dx, int dy, QPoint &) override;
    virtual void resize(const QSize & sz, bool w, bool h) override;
    virtual void prepare_for_move(bool on_resize) override;
    virtual bool move_with_its_package() const override;

    virtual void save(QTextStream  & st, bool ref, QString & warning) const override;
    static ComponentCanvas * read(char *& , UmlCanvas *, char *);
    virtual void post_loaded() override;

    virtual void history_save(QBuffer &) const override;
    virtual void history_load(QBuffer &) override;
    virtual void history_hide() override;

    virtual bool has_drawing_settings() const override;
    virtual void edit_drawing_settings(QList<DiagramItem *> &) override;
    virtual void clone_drawing_settings(const DiagramItem *src) override;
    void edit_drawing_settings();
    virtual bool get_show_stereotype_properties() const override;

    virtual void apply_shortcut(const QString & s) override;

private slots:
    void modified();	// canvas must be updated
    void deleted();	// the class is deleted
};

#endif
