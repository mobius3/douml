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

#include "menufactory.h"
#include <translate.h>

void MenuFactory::createTitle(
    QMenu & menu,
    const QString & title)
{
    QAction * pItem = menu.addAction(title);
    QFont font = menu.font();
    font.setBold(true);
    pItem->setFont(font);
    pItem->setEnabled(false);
}

void MenuFactory::addItems(
    Q3PopupMenu & menu,
    const Item items[],
    const int nofItems)
{
    for (int i = 0; i < nofItems; i++) {
        addItem(
            menu,
            items[i].name,
            items[i].id,
            items[i].whatsThis);
    }
}

void MenuFactory::addItem(
    Q3PopupMenu   &   menu,
    const char * const name,
    const int         id,
    const char * const whatsThis)
{
    const int itemId = menu.insertItem(
                           TR(name),
                           id);

    if (NULL != whatsThis) {
        menu.setWhatsThis(itemId, TR(whatsThis));
    }
}

MenuFactory::MenuFactory(
    const WrapperStr & menuName)
    : m_menu(0, menuName)
{

}

MenuFactory::~MenuFactory()
{

}

Q3PopupMenu & MenuFactory::menu()
{
    return m_menu;
}

void MenuFactory::createTitle(
    const QString title)
{
    createTitle(m_menu, title);
}

void MenuFactory::addItems(
    const Item    items[],
    const int     nofItems)
{
    addItems(m_menu, items, nofItems);
}

void MenuFactory::addItem(
    const char * const name,
    const int         id,
    const char * const whatsThis)
{
    addItem(m_menu, name, id, whatsThis);
}

void MenuFactory::addItem(
    const char * const name,
    QMenu * const      subMenu)
{
    m_menu.insertItem(name, subMenu);
}


void MenuFactory::insertSeparator()
{
    m_menu.insertSeparator();
}
