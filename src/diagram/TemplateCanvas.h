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

#ifndef TEMPLATECANVAS_H
#define TEMPLATECANVAS_H

#include "DiagramCanvas.h"
#include <QTextStream> //[lgfreitas] needed by QTextStream

class CdClassCanvas;

#define TEMPLATE_CANVAS_MIN_SIZE 1

class TemplateCanvas : public DiagramCanvas
{
protected:
    DiagramCanvas * cl;
    QString text;

public:
    TemplateCanvas(DiagramCanvas * c);
    virtual ~TemplateCanvas();

    virtual void draw(QPainter & p);

    virtual UmlCode type() const;
    virtual void open();
    virtual void menu(const QPoint &);
    virtual QString may_start(UmlCode &) const;
    virtual QString may_connect(UmlCode & l, const DiagramItem * dest) const;
    virtual void moveBy(double dx, double dy);
    virtual void change_scale();
    virtual void upper();
    virtual void lower();
    virtual void z_up();
    virtual void z_down();
    virtual bool primaryItem() const;
    virtual void set_z(double z);	// only called by upper() & lower()
    virtual void save(QTextStream &, bool ref, QString & warning) const;

    void update();
};

#endif
