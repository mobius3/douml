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

#ifndef TREEFILTER_TREEMODEL_H
#define TREEFILTER_TREEMODEL_H

#include <QObject>
#include <QVariant>
#include <QModelIndex>
#include <QString>
#include <QDebug>
#include "include/TreeItemInterface.h"
#include "l_tree_controller_global.h"

class QTreeView;

class L_TREE_CONTROLLER_EXPORT TreeModel  : public QAbstractItemModel
{
  Q_OBJECT
  public:
    TreeModel(QObject * parent = 0);

    virtual ~TreeModel();

    virtual QVariant data(const QModelIndex & index, int role) const override;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) override;
    virtual Qt::ItemFlags flags(const QModelIndex & index) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex & index) const override;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex & parent = QModelIndex()) const override;

    TreeItemInterface * RootItem();
    void UpdateData(QModelIndex);
    void InsertRootItem(QSharedPointer<TreeItemInterface>);
    TreeItemInterface * getItem(const QModelIndex & index) const;

    virtual bool insertRows(int position, int rows, const QModelIndex & parent) override;
    virtual bool removeRows(int position, int rows, const QModelIndex & parent) override;

    void reset();

    QSharedPointer<TreeItemInterface> rootItem;

signals:
    void dataEditFinished(const QModelIndex &);
};


#endif
