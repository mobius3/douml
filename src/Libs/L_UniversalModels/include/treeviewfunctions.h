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
#ifndef TREEFUNCTIONS_H
#define TREEFUNCTIONS_H
#include <QList>
#include <QModelIndex>
#include <QAbstractItemView>
#include "l_tree_controller_global.h"


class QTreeView;
namespace TreeFunctions
{
enum class ENodeInsertionMode
{
    sibling,
    child
};


/*
 * Информация о том как именно вставляется потомок. Нодой или папкой
 **/


/* Рекурсивно восстанавливает состояние нод дерева
 * @nodes список открытых нод. Заполняется как послеовательная строка строка-колонка...
 * @view отображение в котором требуется восстановить состояние
 * @model указатель на модель
 * @startIndex индекс для детей которого восстанавливается состояние
 * @path текущий путь вверх по дереву
 **/
L_TREE_CONTROLLER_EXPORT void ApplyNodePathExpandState(QStringList & nodes, QTreeView * view, QAbstractItemModel * model, const QModelIndex startIndex, QString path = QString());
/* Рекурсивно сохраняет состояние нод дерева
 * @nodes список открытых нод. Заполняется как последовательная строка строка-колонка...
 * @view отображение в котором требуется сохранить состояние
 * @model указатель на модель
 * @startIndex индекс для детей которого сохраняется состояние
 * @path текущий путь вверх по дереву
 **/
L_TREE_CONTROLLER_EXPORT void StoreNodePathExpandState(QStringList & nodes, QTreeView * view, QAbstractItemModel * model, const QModelIndex startIndex, QString path = QString());
}
#endif // TREEFUNCTIONS_H
