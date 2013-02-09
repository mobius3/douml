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
    Q3TableItem * itm = item(row, col);

    if (itm != 0) {
        itm->setText(text);
        updateCell(row, col);
    }
    else
        setItem(row, col, new TableItem(this, Q3TableItem::OnTyping, text));
}

// force end of edition

void MyTable::forceUpdateCells()
{
    for (int row = 0; row != numRows(); row += 1) {
        for (int col = 0; col != numCols(); col += 1) {
            QWidget * w = cellWidget(row, col);

            if (w != 0) {
                QString s = item(row, col)->text();

                item(row, col)->setContentFromEditor(w);

                if (item(row, col)->text() != s)
                    emit valueChanged(row, col);

                // warning : may have other edited cells
            }
        }
    }
}
