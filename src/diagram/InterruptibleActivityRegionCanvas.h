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

#ifndef INTERRUPTIBLEACTIVITYREGIONCANVAS_H
#define INTERRUPTIBLEACTIVITYREGIONCANVAS_H





#include <qobject.h>
#include <QList>
#include <QTextStream>
#include "ActivityContainerCanvas.h"

#define INTERRUPTIBLE_ACTIVITY_REGION_CANVAS_MIN_SIZE 40

class InterruptibleActivityRegionCanvas : public QObject, public ActivityContainerCanvas
{
    Q_OBJECT

protected:
    UmlColor itscolor;
    UmlColor used_color;

protected:
    InterruptibleActivityRegionCanvas(UmlCanvas * canvas, int id);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
public:
    InterruptibleActivityRegionCanvas(BrowserNode * bn, UmlCanvas * canvas, int x, int y);
    virtual ~InterruptibleActivityRegionCanvas();

    void force_sub_inside(bool rz);

    virtual void delete_it() override;

    virtual void update() override;

    virtual void draw(QPainter & p);

    virtual UmlCode typeUmlCode() const override;
    virtual void delete_available(BooL & in_model, BooL & out_model) const override;
    virtual bool alignable() const override;
    virtual bool copyable() const override;
    virtual void remove(bool from_model) override;
    virtual void open() override;
    virtual void menu(const QPoint &) override;
    virtual QString may_start(UmlCode &) const override;
    virtual QString may_connect(UmlCode & l, const DiagramItem * dest) const override;
    virtual void connexion(UmlCode, DiagramItem *, const QPoint &, const QPoint &) override;
    virtual aCorner on_resize_point(const QPoint & p) override;
    virtual void resize(aCorner c, int dx, int dy, QPoint &) override;
    virtual void resize(const QSize & sz, bool w, bool h) override;
    virtual bool move_with_its_package() const override;

    virtual bool has_drawing_settings() const override;
    virtual void edit_drawing_settings(QList<DiagramItem *> &) override;
    virtual void clone_drawing_settings(const DiagramItem *src) override;
    void edit_drawing_settings();

    virtual void apply_shortcut(QString s);

    virtual void save(QTextStream  & st, bool ref, QString & warning) const override;
    static InterruptibleActivityRegionCanvas * read(char *& , UmlCanvas *, char *);

    virtual void history_save(QBuffer &) const override;
    virtual void history_load(QBuffer &) override;
    virtual void history_hide() override;

private slots:
    void modified();	// canvas must be updated
    void deleted();
};

#endif
