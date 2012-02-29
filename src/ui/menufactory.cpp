// *************************************************************************
//
// Copyright 2012 Daniel Hellsson
//
// This file is part of the DoUML Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
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
    QMenu& menu,
    const QString& title )
{
    QAction* pItem = menu.addAction( title );
    QFont font = menu.font();
    font.setBold( true );
    pItem->setFont( font );
    pItem->setEnabled( false );
}

void MenuFactory::addItems(
    Q3PopupMenu& menu,
    const Item items[],
    const int nofItems )
{
    for ( int i = 0; i < nofItems; i++ )
    {
      const int itemId = menu.insertItem(
            TR(items[i].name),
            items[i].id );
      menu.setWhatsThis( itemId, TR(items[i].whatsThis ) );
    }
}
