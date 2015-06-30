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





#include <qmenu.h>
#include <qcursor.h>

#include "StringTable.h"
#include "translate.h"
#include "ui/menufactory.h"
#include <QHeaderView>

StringTable::StringTable(int rowCount, int columnCount, QWidget * parent, bool visit)
    : MyTable(rowCount, columnCount, parent)
{

    //setSortingEnabled(-1);
    setSelectionMode(NoSelection);	// single does not work
    verticalHeader()->setSectionsMovable(true);

    copy = new QString[columnCount];

    if (! visit) {
        connect(this, SIGNAL(pressed(QModelIndex)),
                this, SLOT(button_pressed(QModelIndex)));
        connect(this, SIGNAL(cellChanged(int,int)),
                this, SLOT(value_changed(int, int)));
    }
}

StringTable::~StringTable()
{
    delete [] copy;
}

void StringTable::activateNextCell()
{
    int row = currentRow();
    int col = currentColumn();

    if (col == (columnCount() - 2)) {
        // goto next line
        if (++row == rowCount()) {
            // adds a new line
            setRowCount(row + 1);
            init_row(row);
            setText(row, columnCount() - 1, QString());
        }
        setCurrentCell(row, 0);
    }
    else
        setCurrentCell(row, col + 1);
}

void StringTable::value_changed(int row, int col)
{
    if ((row == (rowCount() - 1)) && (col != 0) && !text(row, col).isEmpty())
        insert_row_after(row);
}

void StringTable::button_pressed(const QModelIndex &modelindex)
{
    int col = modelindex.column();
    int index = modelindex.row();
    if (col == columnCount() - 1) {
        QString s;
        QMenu m;

        s.sprintf("%d", index + 1);
        MenuFactory::addItem(m,TR("row %1").arg(s).toLatin1().constData(), -1);
        m.addSeparator();
        MenuFactory::addItem(m,TR("Insert row before").toLatin1().constData(), 0);
        MenuFactory::addItem(m,TR("Insert row after").toLatin1().constData(), 1);
        m.addSeparator();
        MenuFactory::addItem(m,TR("Delete row").toLatin1().constData(), 2);
        m.addSeparator();
        MenuFactory::addItem(m,TR("Copy row").toLatin1().constData(), 3);
        MenuFactory::addItem(m,TR("Cut row").toLatin1().constData(), 4);
        MenuFactory::addItem(m,TR("Paste row").toLatin1().constData(), 5);
        m.addSeparator();

        QMenu mv;
        int rank;

        for (rank = 0; rank != rowCount(); rank += 1)
            if (rank != index)
                MenuFactory::addItem(mv, QString::number(rank + 1).toLatin1().constData(), 10 + rank);

        mv.setTitle(TR("Move row"));
        //MenuFactory::addItem(m,TR("Move row"), &mv);
        m.addMenu(&mv);

        QAction * action = m.exec(QCursor::pos());
        if(action)
        {
            rank = action->data().toInt();
            switch (rank) {
            case 0:
                insert_row_before(index);
                break;

            case 1:
                insert_row_after(index);
                break;

            case 2:
                delete_row(index);
                break;

            case 3:
                copy_row(index);
                break;

            case 4:
                cut_row(index);
                break;

            case 5:
                paste_row(index);
                break;

            default:
                if (rank >= 10)
                    move_row(index, rank - 10);

                break;
            }
        }
    }
}

void StringTable::insert_row_before(int row)
{
    /*int n = rowCount();
    int index;

    setRowCount(n + 1);

    for (index = n; index != row; index -= 1) {
        int col;

        for (col = 0; col <= columnCount() - 1; col += 1)
        {
            QTableWidgetItem * it;
            it = item(index, col);
            if(it)
            {
                it->setText( itemAt(index - 1, col)->text());
            }
        }
    }*/
    blockSignals(true);
    DISABLESORTINGMYTABLE;
    insertRow(row);
    init_row(row);
    setText(row, columnCount() - 1, QString());
    ENABLESORTINGMYTABLE;
    blockSignals(false);
}

void StringTable::insert_row_after(int row)
{
    /*int n = rowCount();
    int index;

    setRowCount(n + 1);

    for (index = n; index > row + 1; index -= 1) {
        int col;

        for (col = 0; col <= columnCount() - 1; col += 1)
            itemAt(index, col)->setText(itemAt(index - 1, col)->text());
    }
    */
    blockSignals(true);
    DISABLESORTINGMYTABLE;
    insertRow(row+1);
    init_row(row + 1);
    setText(row + 1, columnCount() - 1, QString());
    ENABLESORTINGMYTABLE;
    blockSignals(false);
}

void StringTable::delete_row(int row)
{
    int n = rowCount();
    int index;

    removeCellWidget(row, 1);

    if (n == 1) {
        // the alone line : empty it
        init_row(0);
        setText(0, columnCount() - 1, QString());
    }
    else {
        for (index = row; index != n - 1; index += 1) {
            int col;

            for (col = 0; col <= columnCount() - 1; col += 1)
                item(index, col)->setText( text(index + 1, col));
        }

        setRowCount(n - 1);
    }
}

void StringTable::copy_row(int row)
{
    int col;

    for (col = 0; col <= columnCount() - 1; col += 1)
        copy[col] = text(row, col);
}

void StringTable::cut_row(int row)
{
    copy_row(row);
    delete_row(row);
}

void StringTable::paste_row(int row)
{
    int col;

    for (col = 0; col <= columnCount() - 1; col += 1)
        setText(row, col, copy[col]);

    if (row == (rowCount() - 1))
        insert_row_after(row);
}

void StringTable::move_row(int from, int to)
{
    QString * save = new QString[columnCount()];
    int col;

    for (col = 0; col <= columnCount() - 1; col += 1)
        save[col] = copy[col];

    cut_row(from);

    if (to > from)
        insert_row_after(to - 1);
    else
        insert_row_before(to);

    paste_row(to);

    for (col = 0; col <= columnCount() - 1; col += 1)
        copy[col] = save[col];

    delete [] save;
}
