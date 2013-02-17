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

#ifndef UMLDRAG_H
#define UMLGRAG_H

#include <q3dragobject.h>
#include <qstring.h>
//Added by qt3to4:
#include <QDragMoveEvent>
#include <QDropEvent>

#include "UmlEnum.h"
#include "browser/BrowserNode.h"

//class BrowserNode;

class UmlDrag : public Q3StoredDrag
{
private:
    static QString postfix;
    static bool ro;

public:
    static const QString Key;
    static BrowserNode* node;

    UmlDrag(BrowserNode * bn, QWidget * parent = 0, const char * name = 0);
    virtual ~UmlDrag() {};

    static bool canDecode(QDragMoveEvent * e, UmlCode type,
                          bool withpostfix = FALSE,
                          bool evenro = FALSE);
    static bool canDecode(QDragMoveEvent * e, const QString & type);
    static BrowserNode * decode(QDropEvent * e, UmlCode type, bool withpostfix = FALSE);
    static BrowserNode * decode(QDropEvent * e, const QString & type);
    static BrowserNode* get_node();
};

#endif
