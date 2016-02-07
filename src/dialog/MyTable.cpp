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





#include "MyTable.h"
#include "strutil.h"
#include <QHeaderView>
// TableItem is defined to redefine alignment() because the default
// definition calls QString::to[U]Long which does not properly
// manage the empty but not null QString (ie QString(""))

int TableItem::alignment() const
{
    return Qt::AlignLeft | Qt::AlignVCenter;
}

// to use TableItem rather than QTableItem

void MyTable::setText(int row, int col, const QString & text)
{
    QTableWidgetItem * itm = item(row, col);

    if (itm != 0) {
        itm->setText(text);
        //update(this->model()->index(row,col));
    }
    else
    {
        setItem(row, col, new TableItem(this, TableItem::OnTyping, text, TableItem::TableItemType));
    }
}

QString MyTable::text(int row, int colum) const
{
    if(item(row, colum))
        return item(row, colum)->text();
    else
        return QString();
}

// force end of edition

void MyTable::forceUpdateCells()
{
}

void MyTable::setVerticalHeaderLabel(int section, const QIcon &icon, const QString &s)
{
    QTableWidgetItem *item = verticalHeaderItem(section);
    if(item)
    {
        item->setIcon(icon);
    }
    else
    {
        item = new QTableWidgetItem(icon,s,0);
        setVerticalHeaderItem(section, item);
    }
}

void MyTable::setHorizontalHeaderLabel(int section, const QIcon &icon, const QString &s)
{
    QTableWidgetItem *item = horizontalHeaderItem(section);
    if(item)
    {
        item->setIcon(icon);
    }
    else
    {
        item = new QTableWidgetItem(icon,s,0);
        setHorizontalHeaderItem(section, item);
    }
}
void MyTable::setVerticalHeaderLabel(int section, const QString &s)
{
    QTableWidgetItem *item = verticalHeaderItem(section);
    if(item)
    {
        item->setText(s);
    }
    else
    {
        item = new QTableWidgetItem(s,0);
        setVerticalHeaderItem(section, item);
    }
}

void MyTable::setHorizontalHeaderLabel(int section,  const QString &s)
{
    QTableWidgetItem *item = horizontalHeaderItem(section);
    if(item)
    {
        item->setText(s);
    }
    else
    {
        item = new QTableWidgetItem(s,0);
        setHorizontalHeaderItem(section, item);
    }
}

void MyTable::setColumnStretchable(int column, bool state)
{
    if(state)
        horizontalHeader()->setSectionResizeMode(column, QHeaderView::Stretch);
    else
        horizontalHeader()->setSectionResizeMode(column, QHeaderView::Interactive);
}

void MyTable::setRowStretchable(int column, bool state)
{
    if(state)
        verticalHeader()->setSectionResizeMode(column, QHeaderView::Stretch);
    else
        verticalHeader()->setSectionResizeMode(column, QHeaderView::Fixed);
}

void MyTable::adjustColumn(int col)
{
    Q_UNUSED(col);
    
    horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
}
