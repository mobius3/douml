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

#ifndef CODLINKCANVAS_H
#define CODLINKCANVAS_H

#include "ArrowCanvas.h"
//Added by qt3to4:
#include <QTextStream>

class BrowserClass;
class CdClassCanvas;
class CodDirsCanvas;
class LabelCanvas;
class CodObjCanvas;
class ColMsg;

class CodLinkCanvas : public ArrowCanvas
{
protected:
    CodDirsCanvas * dirs;

public:
    CodLinkCanvas(UmlCanvas * canvas, DiagramItem * b, DiagramItem * e,
                  int id, float d_start, float d_end);
    virtual ~CodLinkCanvas();

    virtual void delete_it();

    virtual void setVisible(bool yes);
    virtual void moveBy(double dx, double dy);

    virtual void update_pos();
    virtual ArrowPointCanvas * brk(const QPoint &);
    virtual ArrowCanvas * join(ArrowCanvas * other, ArrowPointCanvas * ap);

    virtual void open();
    virtual void menu(const QPoint &);

    void get_start_end(CodObjCanvas *& from, CodObjCanvas *& to);
    CodDirsCanvas * find_dirs() const;
    void set_dirs(CodDirsCanvas * d) {
        dirs = d;
    };

    virtual void history_save(QBuffer &) const;
    virtual void history_load(QBuffer &);

    virtual void save(QTextStream & st, bool ref, QString & warning) const;
    static CodLinkCanvas * read(char *& st, UmlCanvas * canvas, char *& k);
};

#endif
