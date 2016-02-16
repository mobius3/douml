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

#ifndef ARROWPOINTCANVAS_H
#define ARROWPOINTCANVAS_H

#include "DiagramCanvas.h"
//Added by qt3to4:
#include <QTextStream>

#define ARROW_POINT_SIZE 5

class ArrowPointCanvas : public DiagramCanvas
{
public:
    ArrowPointCanvas(UmlCanvas * canvas, int x, int y);
    virtual ~ArrowPointCanvas();

    virtual void delete_it() override;

    ArrowCanvas * get_other(const ArrowCanvas *) const;

    virtual void draw(QPainter & p);

    virtual UmlCode typeUmlCode() const override;
    virtual void change_scale() override;
    virtual void open() override;
    virtual void menu(const QPoint &) override;
    virtual QString may_start(UmlCode &) const override;
    virtual QString may_connect(UmlCode & l, const DiagramItem * dest) const override;
    virtual void connexion(UmlCode, DiagramItem *, const QPoint &, const QPoint &) override;
    virtual void delete_available(BooL & in_model, BooL & out_model) const override;
    virtual bool alignable() const override;
    virtual void prepare_for_move(bool on_resize) override;
    virtual void save(QTextStream & st, bool ref, QString & warning) const override;
    static ArrowPointCanvas * read(char *& st, UmlCanvas * canvas, char * k);
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif
