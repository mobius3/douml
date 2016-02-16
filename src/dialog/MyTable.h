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

#ifndef TABLEITEM_H
#define TABLEITEM_H

#include "DialogUtil.h"
#include <QTableWidget>
//Added by qt3to4:
#include <QPixmap>
#include "tablewidgetitemdelegate.h"

class TableItem : public QTableWidgetItem
{
public:
    enum {
        TableItemType = UserType,
        ComboType,
        MLinesType,
        MsgTableItemType
    };
    enum EditType {
        Always,
        WhenCurrent,
        OnTyping,
        Never
    };

    TableItem(EditType et, const QString & text, int type)
        : QTableWidgetItem(text, type)
    {
        switch(et)
        {
        case Always:
            setFlags(flags()| Qt::ItemIsEditable);
            break;
        case WhenCurrent:
            setFlags(flags()| Qt::ItemIsEditable);
            break;
        case OnTyping:
            setFlags(flags()| Qt::ItemIsEditable);
            break;
        case Never:
            setFlags(flags()& ~Qt::ItemIsEditable);
            break;
        }
    }

    TableItem(EditType et, const QString & text, const QPixmap & p, int type)
        : QTableWidgetItem(QIcon(p), text, type)
    {
        switch(et)
        {
        case Always:
            setFlags(flags()| Qt::ItemIsEditable);
            break;
        case WhenCurrent:
            setFlags(flags()| Qt::ItemIsEditable);
            break;
        case OnTyping:
            setFlags(flags()| Qt::ItemIsEditable);
            break;
        case Never:
            setFlags(flags()& ~Qt::ItemIsEditable);
            break;
        }
    }

    virtual int alignment() const;

};

#define DISABLESORTINGMYTABLE bool sortingEnabled = false;\
if(isSortingEnabled())\
{\
    sortingEnabled =true;\
    setSortingEnabled(false);\
}

#define ENABLESORTINGMYTABLE if(sortingEnabled)\
{\
    setSortingEnabled(true);\
}

class MyTable : public QTableWidget
{
    Q_OBJECT

public:
    MyTable(QWidget * parent = 0)
        : QTableWidget(parent)
    {
    }
    MyTable(int numRows, int numCols, QWidget * parent = 0)
        : QTableWidget(numRows, numCols, parent)
    {
    }

    ~MyTable()
    {
    }

    virtual void setText(int row, int col, const QString & text);
    QString text(int row, int colum) const;

    void forceUpdateCells();

    void setVerticalHeaderLabel(int section, const QIcon & icon, const QString & s);
    void setHorizontalHeaderLabel(int section, const QIcon & icon, const QString & s);
    void setVerticalHeaderLabel(int section,  const QString & s);
    void setHorizontalHeaderLabel(int section,  const QString & s);
    void setColumnStretchable(int column, bool state);
    void setRowStretchable(int column, bool state);
    void adjustColumn(int col);
};

#endif
