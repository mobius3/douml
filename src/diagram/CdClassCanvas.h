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

#ifndef CDCLASSCANVAS_H
#define CDCLASSCANVAS_H





#include <qobject.h>
//Added by qt3to4:
#include <QTextStream>
#include <QList>

#include "DiagramCanvas.h"
#include "MultipleDependency.h"
#include "Settings.h"

class TemplateCanvas;
class RelationData;
class ConstraintCanvas;

class CdClassCanvas : public QObject, public DiagramCanvas,
    public MultipleDependency<BasicData>
{
    Q_OBJECT

protected:
    TemplateCanvas * templ;
    ClassDiagramSettings settings;
    ClassDiagramSettings used_settings;
    UmlColor itscolor;
    UmlColor used_color;
    ClassDrawingMode used_view_mode;
    bool indicate_visible_attr : 2;
    bool indicate_visible_oper : 2;
    bool manual_size : 2;
    int width_min;
    int height_min;
    QString full_name;
    QList<BrowserNode *> hidden_visible_attributes;
    QList<BrowserNode *> hidden_visible_operations;
    ConstraintCanvas * constraint;

protected:
    CdClassCanvas(UmlCanvas * canvas, int id);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
public:
    CdClassCanvas(BrowserNode * bn, UmlCanvas * canvas, int x, int y);
    virtual ~CdClassCanvas();

    virtual void delete_it() override;

    void check_size();
    virtual bool has_relation(BasicData *) const override;
    bool has_inner(DiagramItem * end) const;
    void draw_all_relations(CdClassCanvas * end = 0);
    void draw_all_class_assoc();
    void check_constraint();
    void check_inner();
    const ClassDiagramSettings & get_settings() const {
        return settings;
    }

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
    virtual QString may_connect(UmlCode & l, const DiagramItem * dest) const override;
    virtual void post_connexion(UmlCode, DiagramItem *) override;
    virtual void connexion(UmlCode, DiagramItem *, const QPoint &, const QPoint &) override;
    virtual aCorner on_resize_point(const QPoint & p) override;
    virtual void resize(aCorner c, int dx, int dy, QPoint &) override;
    virtual void resize(const QSize & sz, bool w, bool h) override;
    virtual bool move_with_its_package() const override;
    virtual void moveBy(double dx, double dy) override;
    virtual void set_z(double z) override;	// only called by upper() & lower()
    virtual void history_save(QBuffer &) const override;
    virtual void history_load(QBuffer &) override;
    virtual void history_hide() override;

    virtual bool has_drawing_settings() const override;
    virtual void edit_drawing_settings(QList<DiagramItem *> &) override;
    virtual void clone_drawing_settings(const DiagramItem *src) override;
    void edit_drawing_settings();
    virtual bool get_show_stereotype_properties() const override;

    virtual void apply_shortcut(QString s);

    virtual void save(QTextStream  & st, bool ref, QString & warning) const override;
    static CdClassCanvas * read(char *& , UmlCanvas *, char *);
    virtual void post_loaded() override;

private slots:
    void modified();	// canvas must be updated
    void deleted();	// the class is deleted
};

#endif
