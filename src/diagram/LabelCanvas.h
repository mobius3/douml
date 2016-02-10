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

#ifndef LABELCANVAS_H
#define LABELCANVAS_H

#include <qfont.h>

#include "QGraphicsScene"
//Added by qt3to4:
#include <QTextStream>

#include "DiagramItem.h"
#include "UmlCanvas.h"

#define LABEL_Z 3000
#define OLD_LABEL_Z 1e100

#define isa_label(x) ((x)->type() == RTTI_LABEL)

class LabelCanvas : public QGraphicsSimpleTextItem, public DiagramItem
{
public:
    static const char * Triangle;
    static const char * Zigzag;

protected:
    bool multi_lines_centered;
    int center_x_scale100;
    int center_y_scale100;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
public:
    LabelCanvas(const QString & n, UmlCanvas * canvas, int x, int y,
                bool bold = FALSE, bool italic = FALSE,
                bool underlined = FALSE, bool mlcentered = TRUE);
    virtual ~LabelCanvas();

    virtual void delete_it() override;

    const QString get_name() const {
        return text();
    };
    virtual QRect rect() const override;
    virtual QRect sceneRect() const override;

    int width() const {
        return boundingRect().width();
    };
    int height() const {
        return boundingRect().height();
    };
    void set_name(const QString &);

    void set_strikeout(bool yes);
    void set_underlined(bool yes);

    void move_outside(QRect r, double angle);

    virtual void draw(QPainter & p);

    virtual UmlCode typeUmlCode() const override;
    virtual int rtti() const;
    virtual void moveBy(double dx, double dy) override;
    virtual QPoint center() const override;
    void recenter();
    void set_center100();
    using QGraphicsSimpleTextItem::contains;
    virtual bool contains(int, int) const override;
    virtual void change_scale() override;
    virtual void open() override;
    void menu(const QPoint &) override;
    virtual QString may_start(UmlCode &) const override;
    virtual QString may_connect(UmlCode & l, const DiagramItem * dest) const override;
    virtual void connexion(UmlCode, DiagramItem *, const QPoint &, const QPoint &) override;
    virtual double get_z() const override;
    virtual void set_z(double z) override;	// only called by upper() & lower()
    virtual UmlCanvas * the_canvas() const override;
    virtual bool isSelected() const override;
    virtual void save(QTextStream  & st, bool ref, QString & warning) const override;
    static LabelCanvas * read(char *& st, UmlCanvas * canvas, char *);
    virtual void history_save(QBuffer &) const override;
    virtual void history_load(QBuffer &) override;
    virtual void history_hide() override;

    virtual void check_stereotypeproperties() override;

    virtual int type() const override;
};

#endif
