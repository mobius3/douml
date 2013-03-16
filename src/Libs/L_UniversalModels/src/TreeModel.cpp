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
#include <QSize>
#include <QColor>
#include "include/TreeModel.h"
//#include "include/Logging/LoggerTracer.h"
#include "include/ItemController.h"
#include "include/TreeItemInterface.h"

TreeModel::TreeModel(QObject * parent)
    : QAbstractItemModel(parent)

{
    // Bouml preserved body begin 0014C62A
    // Bouml preserved body end 0014C62A
}

TreeModel::~TreeModel()
{
    // Bouml preserved body begin 0014C6AA
    // Bouml preserved body end 0014C6AA
}

QVariant TreeModel::data(const QModelIndex & index, int role) const
{
    // Bouml preserved body begin 0014C72A

    if (!index.isValid())
        return QVariant();

    TreeItemInterface *item = static_cast<TreeItemInterface*>(index.internalPointer());


    if ( role == Qt::CheckStateRole && index.column() == 0 && (flags(index) & Qt::ItemIsUserCheckable))
        return static_cast< int >( item->checkState() ? Qt::Checked : Qt::Unchecked );

    if(role == Qt::DisplayRole || role == Qt::EditRole ||  role == Qt::DecorationRole)
        return item->data(index,role);

//    if(role == Qt::DecorationRole )
//        return item->data(index.column(),role);

    if(role == Qt::SizeHintRole)
        return QSize(100, 20);
    return QVariant();
    // Bouml preserved body end 0014C72A
}

bool TreeModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    // Bouml preserved body begin 0014C7AA
    if (role != Qt::EditRole && role!=Qt::CheckStateRole)
        return false;


    if(role==Qt::CheckStateRole)
    {
        TreeItemInterface *item = static_cast<TreeItemInterface*>(index.internalPointer());
        item->setCheckState(static_cast<Qt::CheckState>(value.toInt()));
        emit dataChanged(index,index);
        return true;
    }

    if(role==Qt::EditRole)
    {
        TreeItemInterface* item = dynamic_cast<TreeItemInterface*>(getItem(index));
        bool result = item->setData(index, value, role);

        if (result)
        {
            emit dataChanged(index, index);
            emit dataEditFinished(index);
        }
    }
    return false;
    // Bouml preserved body end 0014C7AA
}

Qt::ItemFlags TreeModel::flags(const QModelIndex & index) const
{
    // Bouml preserved body begin 0014C82A

    if (!index.isValid())
        return 0;

    //Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
    Qt::ItemFlags flags = iface->flags(index);

//    if ( index.column() == 0 )
//        flags |= Qt::ItemIsUserCheckable;

    return flags;
    // Bouml preserved body end 0014C82A
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // Bouml preserved body begin 0014C8AA
    if(rootItem == 0 )
        return QVariant();
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->GetColumns().at(section);
    return QVariant();
    // Bouml preserved body end 0014C8AA
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex & parent) const
{
    // Bouml preserved body begin 0014C92A

    //TRACE_FUNCTION;
    if(rootItem.isNull())
        return QModelIndex();
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItemInterface *parentItem;

    if (!parent.isValid())
        parentItem = rootItem.data();
    else
        parentItem = static_cast<TreeItemInterface*>(parent.internalPointer());

    TreeItemInterface *childItem = static_cast<TreeItemInterface*>(parentItem->child(row));
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
    // Bouml preserved body end 0014C92A
}

QModelIndex TreeModel::parent(const QModelIndex & index) const
{
    // Bouml preserved body begin 0014C9AA

    //TRACE_FUNCTION;
    if (!index.isValid())
        return QModelIndex();

    TreeItemInterface *childItem = static_cast<TreeItemInterface*>(index.internalPointer());
    TreeItemInterface *parentItem = dynamic_cast<TreeItemInterface*>(childItem->parent());

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
    // Bouml preserved body end 0014C9AA
}

int TreeModel::rowCount(const QModelIndex & parent) const
{
    // Bouml preserved body begin 0014CA2A
    //TRACE_FUNCTION;
    if(rootItem.isNull())
        return 0;
    TreeItemInterface *parentItem;
    //    if (parent.column() > 0)
    //        return 0;

    if (!parent.isValid())
        parentItem = rootItem.data();
    else
        parentItem = static_cast<TreeItemInterface*>(parent.internalPointer());

    return parentItem->childCount();
    // Bouml preserved body end 0014CA2A
}

int TreeModel::columnCount(const QModelIndex & parent) const
{
    // Bouml preserved body begin 0014CAAA
    //TRACE_FUNCTION;
    if(rootItem.isNull())
        return 0;
    if (parent.isValid())
        return static_cast<TreeItemInterface*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
    // Bouml preserved body end 0014CAAA
}

TreeItemInterface * TreeModel::RootItem()
{
    // Bouml preserved body begin 0014CB2A
    //TRACE_FUNCTION;
    return rootItem.data();
    // Bouml preserved body end 0014CB2A
}

void TreeModel::UpdateData(QModelIndex index)
{
    TreeItemInterface* item = static_cast<TreeItemInterface*>(index.internalPointer());
    QModelIndex lastChild = index.child(item->childCount()-1, item->columnCount()-1);
    emit dataChanged(index.sibling(index.row(),0),
                     lastChild);
}

void TreeModel::InsertRootItem(QSharedPointer<TreeItemInterface> item)
{
    reset();
    if(!rootItem.isNull() && rootItem->childCount() != 0)
    {
        int prevRows = rootItem->childCount();
        int prevColumns = rootItem->columnCount();
        beginRemoveRows(QModelIndex(), 0, prevRows-1);
        endRemoveRows();
        emit dataChanged(index(0,0), index(prevRows-1, prevColumns));
    }

    if(!item.isNull() && item->childCount() != 0)
    {
        beginInsertRows(QModelIndex(), 0, item->childCount()-1);
        endInsertRows();
        emit dataChanged(index(0,0), index(item->childCount()-1, item->columnCount()));
    }
    rootItem = item;
}


TreeItemInterface * TreeModel::getItem(const QModelIndex & index) const
{
    // Bouml preserved body begin 0014CC2A
    //TRACE_FUNCTION;
    if (index.isValid()) {
        TreeItemInterface *item = static_cast<TreeItemInterface*>(index.internalPointer());
        if (item) return item;
    }
    return rootItem.data();
    // Bouml preserved body end 0014CC2A
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex & parent)
{
    // Bouml preserved body begin 0014CCAA
    //TRACE_FUNCTION;
    TreeItemInterface *parentItem = getItem(parent);
    bool success = true;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows);
    endInsertRows();

    emit dataChanged(this->index(position, 0, parent), this->index(position + rows - 1, columnCount(), parent));
    return success;
    // Bouml preserved body end 0014CCAA
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex & parent)
{
    // Bouml preserved body begin 0014CD2A
    //TRACE_FUNCTION;
    TreeItemInterface *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();
    //emit dataChanged(this->index(position, 0, parent), this->index(position + rows - 1, columnCount(), parent));

    return success;
    // Bouml preserved body end 0014CD2A
}

void TreeModel::reset()
{
    QAbstractItemModel::reset();
}


