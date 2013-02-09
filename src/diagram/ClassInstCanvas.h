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

#ifndef CLASSINSTCANVAS_H
#define CLASSINSTCANVAS_H

#define CLASSINST_CANVAS_MIN_SIZE 50

#include <qstring.h>
#include <qrect.h>
//Added by qt3to4:
#include <QTextStream>

#include "UmlEnum.h"
#include "Instance.h"

class QPainter;
class QTextStream;

class BrowserClass;
class UmlCanvas;

class ClassInstCanvas : public Instance
{
    friend class ClassInstDialog;

protected:
    UmlColor itscolor;
    UmlColor used_color;
    Uml3States write_horizontally;
    bool horiz;
    Uml3States show_stereotype_properties;
    bool show_properties;
    ShowContextMode show_context_mode;
    ShowContextMode used_show_context_mode;

public:
    ClassInstCanvas();
    virtual ~ClassInstCanvas();

    QString full_name() const;

    virtual BrowserNode * new_type();
    virtual bool new_type_available();
    virtual BrowserNode * container(UmlCode) const = 0;
    void compute_size(int & w, int & h, UmlCanvas *);
    void draw(QPainter & p, UmlCanvas * canvas, QRect r);

    void save(QTextStream & st) const;
    void read(char *& st, char *& k);
};

#endif
