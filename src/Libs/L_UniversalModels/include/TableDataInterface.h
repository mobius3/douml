// *************************************************************************
//
// Copyright 2012-2013 Nikolai Marchenko.
//
// This file is part of the Douml Uml Toolkit.
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
//
// *************************************************************************
#ifndef _TABLEDATAINTERFACE_H
#define _TABLEDATAINTERFACE_H


#include <QObject>
#include <QVariant>
#include <QStringList>
#include <QModelIndex>

#include "l_tree_controller_global.h"



class L_TREE_CONTROLLER_EXPORT TableDataInterface  : public QObject
{

Q_OBJECT

  public:
    TableDataInterface(QObject * parent = 0);

    virtual ~TableDataInterface();

    virtual QVariant GetValue(int row, int column, int role) const = 0;

    virtual void SetValue(int row, int column, int role, const QVariant & value) = 0;

    virtual QStringList GetColumns() = 0;

    virtual int rowCount() const = 0;

    virtual int columnCount() const = 0;

    virtual int PreviousRowCount() = 0;

    virtual void* InternalPointer() const = 0;

    virtual void* InternalPointer(int row) const = 0;

    virtual bool Equal(int row, void* data) = 0;

    virtual void SetSortFunction(std::function<bool(void*, void*)> func) = 0;

    virtual void sort() = 0;

    virtual Qt::ItemFlags flags(const QModelIndex & index) const = 0;

    virtual void RemoveRow(int index) = 0;


signals:
    void reloadData();

};
#endif
