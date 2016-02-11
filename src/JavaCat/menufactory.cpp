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
#include <QObject>

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
    QMenu & menu,
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
    QMenu   &   menu,
    const char * const name,
    const int         id,
    const char * const whatsThis)
{
    QAction *action = menu.addAction(QObject::tr(name));
    if(whatsThis)
        action->setWhatsThis(QObject::tr(whatsThis));
    action->setData(id);
}
void MenuFactory::addItem(
    QMenu   &   menu,
    QString const name,
    const int         id,
    QString const whatsThis)
{
    QAction *action = menu.addAction(name);
    if(!whatsThis.isEmpty())
        action->setWhatsThis((whatsThis));
    action->setData(id);
}
QMenu & MenuFactory::menu()
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
    Q_UNUSED(name);
    
    //m_menu.insertItem(name, subMenu);
    m_menu.addMenu(subMenu);
}


void MenuFactory::insertSeparator()
{
    m_menu.addSeparator();
}

QAction *MenuFactory::findAction(const QMenu &menu, int id)
{
    foreach (QAction* action, menu.actions()) {
        if(action->data().toInt() == id)return action;
    }
    return NULL;
}

void MenuFactory::insertItem(QMenu &parentMenu, QString name, QMenu *menu, QString what)
{
    menu->setTitle(name);
    parentMenu.addMenu(menu);
    if(!what.isEmpty())
        menu->setWhatsThis(what);
}
