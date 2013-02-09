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

#ifndef VISIBILITYGROUP_H
#define VISIBILITYGROUP_H

#include <qstring.h>

#include "UmlEnum.h"

class QRadioButton;
class Q3ButtonGroup;

class VisibilityGroup
{
protected:
    Q3ButtonGroup * bgroup;
    QRadioButton * public_rb;
    QRadioButton * protected_rb;
    QRadioButton * private_rb;
    QRadioButton * package_rb;

    QString default_pfix;
    QRadioButton * default_visibility_rb;

public:
    VisibilityGroup() {
        bgroup = 0;
    }

    Q3ButtonGroup * init(QWidget * parent,
                         UmlVisibility v,
                         bool pack_allowed = 0,
                         const char * title = 0, const char * default_prefix = 0);
    void update_default(const VisibilityGroup & default_grp);
    void connect(const char *, QWidget *, const char *);
    void follow(const VisibilityGroup & other);
    UmlVisibility value();

    QString state();
};

#endif
