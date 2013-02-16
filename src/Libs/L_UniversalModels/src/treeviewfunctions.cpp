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
#include "include/treeviewfunctions.h"
#include <QTreeView>
#include <functional>
namespace TreeFunctions
{
void ApplyNodePathExpandState(QStringList & nodes,
                      QTreeView * view,
                      QAbstractItemModel * model,
                      const QModelIndex startIndex,
                      QString path)
{
    // Bouml preserved body begin 00201FAA
    path+=QString::number(startIndex.row()) + QString::number(startIndex.column());
    for(int i(0); i < model->rowCount(startIndex); ++i)
    {
        QModelIndex nextIndex = model->index(i, 0, startIndex);
        QString nextPath = path + QString::number(nextIndex.row()) + QString::number(nextIndex.column());
        if(!nodes.contains(nextPath))
            continue;
        ApplyNodePathExpandState(nodes, view, model, nextIndex, path);
    }
    if(nodes.contains(path))
        view->setExpanded( startIndex.sibling(startIndex.row(), 0), true );
    // Bouml preserved body end 00201FAA
}

void StoreNodePathExpandState(QStringList & nodes,
                      QTreeView * view,
                      QAbstractItemModel * model,
                      const QModelIndex startIndex,
                      QString path)
{
    // Bouml preserved body begin 002020AA
    path+=QString::number(startIndex.row()) + QString::number(startIndex.column());
    for(int i(0); i < model->rowCount(startIndex); ++i)
    {
        if(!view->isExpanded(model->index(i, 0, startIndex)))
            continue;
        StoreNodePathExpandState(nodes, view, model, model->index(i, 0, startIndex), path);
    }

    if(view->isExpanded(startIndex))
        nodes << path;
    // Bouml preserved body end 002020AA
}


}
