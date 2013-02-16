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
#ifndef _TREEITEMINTERFACE_H
#define _TREEITEMINTERFACE_H


#include <QList>
#include <QSharedPointer>
#include <QVariant>
#include <QStringList>
#include <QModelIndex>

#include "l_tree_controller_global.h"

#include <QWeakPointer>
#include <QList>
#include <functional>



class L_TREE_CONTROLLER_EXPORT TreeItemInterface  
{
  public:
    explicit TreeItemInterface();

    virtual ~TreeItemInterface();

    virtual QList<QSharedPointer<TreeItemInterface> > GetChildren() = 0;

    virtual int childCount() const = 0;

    virtual int columnCount() const = 0;

    virtual QVariant data(int column, int role) = 0;

    virtual bool isCheckable() const = 0;

    virtual void setCheckState(Qt::CheckState state) = 0;

    virtual Qt::CheckState checkState() = 0;

    virtual bool setData(int column, const QVariant & value, int role) = 0;

    virtual bool removeChildren(int position, int count) = 0;

    virtual bool insertChildren(int position, int count) = 0;

    virtual QStringList GetColumns() = 0;

    virtual void* InternalPointer() = 0;

    virtual TreeItemInterface* child(int row) = 0;

    virtual TreeItemInterface* parent() = 0;

    virtual int row() = 0;

    virtual void SetParent(QSharedPointer<TreeItemInterface > _parent) = 0;

    virtual Qt::ItemFlags flags(const QModelIndex & index) const = 0;

    virtual void AddChildren(QList<QSharedPointer<TreeItemInterface> > children, int insertAfter = 0) = 0;

    virtual int IndexOf(TreeItemInterface * item) = 0;

    virtual int GetIndexOfChild(TreeItemInterface * child) = 0;

};

#endif
