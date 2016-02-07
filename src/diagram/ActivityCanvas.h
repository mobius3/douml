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

#ifndef ACTIVITYCANVAS_H
#define ACTIVITYCANVAS_H





#include <qobject.h>
#include <QList>
#include <QTextStream>
#include "ActivityContainerCanvas.h"
#include "Settings.h"

#define ACTIVITY_CANVAS_MIN_SIZE 40

class ParameterCanvas;
class InfoCanvas;

class ActivityCanvas : public QObject, public ActivityContainerCanvas
{
    Q_OBJECT

protected:
    ActivityDrawingSettings settings;
    UmlColor itscolor;
    UmlColor used_color;
    bool show_info_note;
    int min_width;
    int min_height;
    QString pre;
    QString post;
    QPoint singleexec_offset;
    QPoint readonly_offset;
    QPoint pre_offset;
    QPoint post_offset;
    int post_width;
    QList<ParameterCanvas *> params;
    InfoCanvas * constraint;

protected:
    ActivityCanvas(UmlCanvas * canvas, int id);

    void check_params();
    void check_constraint();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
public:
    ActivityCanvas(BrowserNode * bn, UmlCanvas * canvas, int x, int y);
    virtual ~ActivityCanvas();

    QList<ParameterCanvas *> get_params() {
        return params;
    }
    void force_sub_inside(bool rz);

    virtual void delete_it() override;

    void compute_size();
    void deleted(ParameterCanvas *);

    virtual void draw(QPainter & p);
    virtual void change_scale();

    virtual UmlCode typeUmlCode() const;
    virtual void delete_available(BooL & in_model, BooL & out_model) const;
    virtual bool alignable() const;
    virtual bool copyable() const;
    virtual void remove(bool from_model);
    virtual void open();
    virtual void menu(const QPoint &);
    virtual QString may_start(UmlCode &) const;
    virtual QString may_connect(UmlCode & l, const DiagramItem * dest) const;
    virtual void connexion(UmlCode, DiagramItem *, const QPoint &, const QPoint &);
    virtual void set_z(double z);
    virtual aCorner on_resize_point(const QPoint & p);
    virtual void resize(aCorner c, int dx, int dy, QPoint &);
    virtual void resize(const QSize & sz, bool w, bool h);
    virtual bool move_with_its_package() const;
    virtual void moveBy(double dx, double dy);

    virtual bool has_drawing_settings() const;
    virtual void edit_drawing_settings(QList<DiagramItem *> &);
    virtual void clone_drawing_settings(const DiagramItem *src);

    virtual void apply_shortcut(QString s);
    void edit_drawing_settings();
    virtual bool get_show_stereotype_properties() const override;

    virtual void save(QTextStream  & st, bool ref, QString & warning) const override;
    static ActivityCanvas * read(char *& , UmlCanvas *, char *);

    virtual void history_save(QBuffer &) const override;
    virtual void history_load(QBuffer &) override;
    virtual void history_hide() override;

private slots:
    void modified();	// canvas must be updated
    void deleted();
};

#endif
