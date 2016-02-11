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

#ifndef OBJECTLINKCANVAS_H
#define OBJECTLINKCANVAS_H

#include "ArrowCanvas.h"
//Added by qt3to4:
#include <QTextStream>

class BrowserClass;
class RelationData;
class DiagramItem;
struct SlotRel;

class ObjectLinkCanvas : public ArrowCanvas
{
    Q_OBJECT

protected:
    RelationData * data;
    LabelCanvas * role_a;
    LabelCanvas * role_b;

public:
    ObjectLinkCanvas(UmlCanvas * canvas, DiagramItem * b, DiagramItem * e,
                     UmlCode t, int id, float d_start, float d_end,
                     RelationData * d = 0);
    virtual ~ObjectLinkCanvas();

    virtual void delete_it() override;
    virtual void unconnect() override;

    virtual void history_save(QBuffer & b) const override;
    virtual void history_load(QBuffer &) override;
    virtual void history_hide() override;

    virtual void setVisible(bool yes) override;
    virtual void moveBy(double dx, double dy) override;
    virtual void set_z(double z) override;
    virtual void select_associated() override;

    virtual void update_pos() override;
    virtual ArrowPointCanvas * brk(const QPoint &) override;
    virtual ArrowCanvas * join(ArrowCanvas * other, ArrowPointCanvas * ap) override;

    virtual void save(QTextStream & st, bool ref, QString & warning) const override;
    static ObjectLinkCanvas * read(char *& st, UmlCanvas * canvas, char *);

    virtual void delete_available(BooL & in_model, BooL & out_model) const override;
    virtual void remove(bool from_model) override;
    virtual void open() override;
    virtual void menu(const QPoint &) override;

    void label_default_position() const;
    void role_a_default_position() const;
    void role_b_default_position() const;

    bool reflexive() const;
    void check();

    bool is(const SlotRel &, bool isa) const;
    RelationData * get_rel() const {
        return data;
    }

    virtual bool represents(BrowserNode *) override;

protected:
    void internal_set_relation(RelationData * d);
    void set_relation(RelationData * d);
    using DiagramItem::update;
    void update(bool updatepos);

private slots:
    void modified();	// canvas must be updated
    void deleted();	// the relation is deleted
};

#endif
