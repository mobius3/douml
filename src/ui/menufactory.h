// *************************************************************************
//
// Copyright 2012 Daniel Hellsson
//
// This file is part of the DoUML Uml Toolkit.
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
// e-mail : douml@hellsson.com
// home   : http://github.com/leonardo2d/douml/
//
// *************************************************************************

#ifndef MENUFACTORY_H
#define MENUFACTORY_H

#include <QMenu>
#include <QMenuItem>
#include <Q3PopupMenu>
#include "mystr.h"

class MenuFactory
{
private:
    Q3PopupMenu m_menu;

public:
    typedef struct _Item {
        const char * const name;
        const int id;
        const char * const whatsThis;
    } Item;

    MenuFactory(
        const WrapperStr & menuName);
    virtual ~MenuFactory();

    static void createTitle(
        QMenu     &     menu,
        const QString & title);

    static void addItems(
        Q3PopupMenu & menu,
        const Item    items[],
        const int     nofItems);

    static void addItem(
        Q3PopupMenu   &   menu,
        const char * const name,
        const int         id,
        const char * const whatsThis = NULL);

    virtual void createTitle(
        const QString title);

    virtual void addItems(
        const Item    items[],
        const int     nofItems);

    virtual void addItem(
        const char * const name,
        const int         id,
        const char * const whatsThis = NULL);

    virtual void addItem(
        const char * const name,
        QMenu * const      subMenu);

    virtual Q3PopupMenu & menu();

    virtual void insertSeparator();

};

#endif // MENUFACTORY_H
