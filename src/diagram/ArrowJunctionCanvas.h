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

#ifndef ARROWJUNCTIONCANVAS_H
#define ARROWJUNCTIONCANVAS_H

#include "DiagramCanvas.h"
//Added by qt3to4:
#include <QTextStream>

#define ARROW_JUNCTION_SIZE 19
#define PROVIDED_RADIUS 5.5

class ArrowJunctionCanvas : public QObject, public DiagramCanvas
{
    Q_OBJECT

protected:
    BrowserClass * interface;
public:
    ArrowJunctionCanvas(UmlCanvas * canvas, int x, int y,
                        BrowserClass * i, int id = -1);
    virtual ~ArrowJunctionCanvas();

    virtual void delete_it();
    virtual void unconnect();

    virtual void draw(QPainter & p);

    virtual UmlCode type() const;
    virtual void change_scale();
    virtual void open();
    virtual void menu(const QPoint &);
    virtual QString may_start(UmlCode &) const;
    virtual QString may_connect(UmlCode & l, const DiagramItem * dest) const;
    //virtual void connexion(UmlCode, DiagramItem *, const QPoint &, const QPoint &);
    //virtual void delete_available(BooL & in_model, BooL & out_model) const;
    virtual bool alignable() const;
    virtual void remove_line(ArrowCanvas * l, bool onbrkjoin);
    BrowserClass * get_interface() const {
        return interface;
    }
    virtual void history_load(QBuffer &);
    virtual void history_hide();

    virtual void save(QTextStream & st, bool ref, QString & warning) const;
    static ArrowJunctionCanvas * read(char *& st, UmlCanvas * canvas, char * k);

private slots:
    void modified();	// canvas must be updated
    void deleted();	// interface deleted
};

#endif
