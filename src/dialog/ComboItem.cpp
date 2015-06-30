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





#include <qcombobox.h>

#include "ComboItem.h"
#include "DialogUtil.h"


bool ComboItem::getEditable() const
{
    return editable;
}

void ComboItem::setEditable(bool value)
{
    editable = value;
}

QStringList ComboItem::getTypes()
{
    return types;
}

ComboItem::ComboItem(QTableWidget * ta, const QString & s,
                     const QStringList & list, bool edit)
    : TableItem(ta, TableItem::WhenCurrent, s, TableItem::ComboType), editable(edit), cb(0), types(list)
{
    //cb->setEditable(false);
}


