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
#ifndef TREEVIEWTEMPLATEFUNCTIONS_H
#define TREEVIEWTEMPLATEFUNCTIONS_H
#include <QAbstractItemView>
#include <QTreeView>
#include "include/TreeModel.h"
#include "include/TreeItemInterface.h"
#include "include/treeviewfunctions.h"
#include "include/treeitemfunctions.h"
#include "include/l_tree_controller_global.h"
//class QAbstractItemView;
namespace TreeFunctions
{

/* Создаёт структуру интерфейса дерева из предварительно созданного объекта данных
 * @parentItem объект к которому следует прицепить данный интерфейс как потомка
 * @data готовая к обработке структура с данными
 * @controller указатель на структуру доступа к данным из модели
 **/
template<typename DataType, typename InterfaceType, template <typename> class ItemType, template <typename> class ControllerType>
QSharedPointer<InterfaceType>  CreateInterfaceFromData(QSharedPointer<InterfaceType> parentItem, DataType& data,
                                                       QSharedPointer<ControllerType<DataType> > controller)
{
    ItemType<DataType>* pointer = new ItemType<DataType>();
    QSharedPointer<InterfaceType > newItem(pointer);
    pointer->SetInternalData(data);
    pointer->SetController(controller);
    pointer->SetParent(parentItem);

    data.SetInterfacePointer(newItem.data());
    return newItem;
}
/* Возвращет из отображения указатель на текущий интерфейс
 * @view указатель на отображение из которого извлекается интерфейс
 **/
template<typename InterfaceType>
InterfaceType* GetCurrentInterface(QAbstractItemView* view)
{
    auto currentIndex = view->selectionModel()->currentIndex();
    if(!currentIndex.isValid())
        return nullptr;
    auto pointer = static_cast<InterfaceType*>(currentIndex.internalPointer());
    return pointer;
}
/* Возвращет из отображения указатель на текущие данные
 * @view указатель на отображение из которого извлекаются данные
 **/
template<template<typename> class TreeItemType, typename DataType, typename InterfaceType>
DataType* GetCurrentDataPointer(QAbstractItemView* view)
{
    TreeItemType<DataType> *pointer = dynamic_cast<TreeItemType<DataType>* >(GetCurrentInterface<InterfaceType>(view));
    DataType* data = static_cast<DataType*>(pointer->InternalPointer());
    return data;
}



/* Возвращает родителя для создаваемого потомка на основании режима вставки
 * @insertionMode Информация о том как именно вставляется потомок. Нодой или папкой
 * @current указатель на интерфейс являющийся текущим в модели
 * @root указатель на корневую ноду (для сличения с корнем дерева)
 **/
template<template<typename> class TreeItemType, typename DataType, typename InterfaceType>
QSharedPointer<InterfaceType> GetParent(ENodeInsertionMode insertionMode, InterfaceType* current, QSharedPointer<InterfaceType> root)
{
    InterfaceType* parent = current->parent();
    bool parentIsRoot = parent == root.data();
    QSharedPointer<InterfaceType> sharedOfParent;
    if(insertionMode == ENodeInsertionMode::sibling)
    {
        if(parentIsRoot)
            sharedOfParent = root;
        else
        {
            TreeItemType<DataType>* parentOfParent = dynamic_cast<TreeItemType<DataType>*>(parent->parent());
            sharedOfParent = parent->parent()->GetChildren().at(parentOfParent->IndexOf(parent));
        }
    }
    else
    {
        sharedOfParent = parent->GetChildren().at(parent->IndexOf(current));
    }
    return sharedOfParent;

}

/* Возвращает индекс строки для создания нового потомка в модели
 * @view указатель на отображение из которого извлекаются данные
 * @insertionMode Информация о том как именно вставляется потомок. Нодой или папкой
 * @addBelow указывает вставить потомка перед текущим индексом или после него
 **/
static inline int GetChildInsertionIndex(QAbstractItemView* view, ENodeInsertionMode insertionMode, bool addBelow)
{
    if(insertionMode == ENodeInsertionMode::child)
        return view->model()->rowCount()-1;
    int indexOfCurrentNode = view->selectionModel()->currentIndex().row();
    int indexToInsert;
    if(addBelow)
    {
        if(indexOfCurrentNode + 1 < view->model()->rowCount())
            indexToInsert = indexOfCurrentNode + 1;
        else
            indexToInsert = indexOfCurrentNode;

    }
    else
        indexToInsert = indexOfCurrentNode;
    return indexToInsert;
}

/* Создаёт потомка или сиблинга для текущей ноды в дереве (берется из view)
 * @dataGenerator генератор для создания данных для помещения в интерфейс
 * @view указатель на отображение
 * @root указатель на корневую ноду (для сличения с корнем дерева)
 * @insertionMode Информация о том как именно вставляется потомок. Нодой или папкой
 * @addBelow указывает вставить потомка перед текущим индексом или после него
 **/
template<template<typename> class TreeItemType, typename DataType, typename InterfaceType>
TreeItemType<DataType>* AddItem(std::function<DataType(DataType*)> dataGenerator, QAbstractItemView* view,
                                QSharedPointer<InterfaceType> root, ENodeInsertionMode insertionMode, bool addBelow = true)
{
    QSharedPointer<InterfaceType> parent = GetParent<TreeItemType, DataType, InterfaceType>
            (insertionMode, GetCurrentInterface<InterfaceType>(view), root);

    bool parentIsRoot = parent.data() == root.data();

    TreeItemType<DataType>* parentItem = dynamic_cast<TreeItemType<DataType>*>(parent.data());
    DataType* parentData = static_cast<DataType*>(parentItem->InternalPointer());


    DataType data = dataGenerator(parentIsRoot ? nullptr : parentData);


    TreeItemType<DataType>* newTemplateItem = new TreeItemType<DataType>();
    QSharedPointer<InterfaceType > newItem(newTemplateItem);
    newTemplateItem->SetInternalData(data);
    newTemplateItem->SetController(dynamic_cast<TreeItemType<DataType>*>(parent.data())->GetController());
    newTemplateItem->SetParent(parent);

    data.SetInterfacePointer(newItem.data());

    int indexToInsert = GetChildInsertionIndex(view, insertionMode, addBelow);
    parent->AddChildren(QList<QSharedPointer<InterfaceType> >() << newItem, indexToInsert);
    TreeModel* model = dynamic_cast<TreeModel*>(view->model());
    model->InsertRootItem(root);
    return dynamic_cast<TreeItemType<DataType>*>(newItem.data());
}


/* Производит фильтрацию в дереве и устанавливает результат в качестве корневой ноды
 * @dataGenerator генератор для создания данных для помещения в интерфейс
 * @treeView указатель на дерево-отображение
 * @rootItem указатель на корневую ноду (для сличения с корнем дерева)
 * @createCheckListFunc фуннкция создающая необходимые для фильтрации проверки
 * @expandedNodes ссылка на хранилице открытых нод дерева
 * @isFilteredTree ссылка на хранилище состояние фильтрованности дерева
 **/

template<typename InterfaceType, template <typename> class ItemType, typename DataType>
bool PerformFiltering(TreeModel* treeModel,
                      QSharedPointer<InterfaceType > rootItem,
                      std::function<QList<std::function<bool (InterfaceType *)> > ()> createCheckListFunc,bool forceRoot = false,  bool forceChildren = true)
{
    QSharedPointer<InterfaceType > item;
    QList<std::function<bool (InterfaceType *)> > checkList = createCheckListFunc();
    if(checkList.isEmpty())
        item = rootItem;
    else
        item = TreeFunctions::FilterSubset<InterfaceType,ItemType,DataType>(rootItem, checkList, forceRoot, forceChildren);
    treeModel->InsertRootItem(item);
    if(item == rootItem)
        return false;
    return true;
}

template<typename InterfaceType, template <typename> class ItemType, typename DataType>
static inline QString GetPathFromIndex(std::function<QVariant(DataType*)> dataAccessor, const QModelIndex& startIndex)
{
    auto pointer = static_cast<InterfaceType*>(startIndex.internalPointer());
    ItemType<DataType> *dataPointer = nullptr;
    QString path;
    if(pointer)
    {
        dataPointer = dynamic_cast<ItemType<DataType>* >(pointer);
        DataType* data = static_cast<DataType*>(dataPointer->InternalPointer());
        QString newPath = dataAccessor(data).toString() + QObject::tr(",");
        path+=newPath;
    }
    else
    {
        path+=QObject::tr("-11111,");
    }
    return path;
}

template<typename InterfaceType, template <typename> class ItemType, typename DataType>
static inline QString GetFullPathFromIndex(std::function<QVariant(DataType*)> dataAccessor, QModelIndex startIndex)
{
    QString result;
    if(!startIndex.isValid())
        return QString();
    if(startIndex.parent().isValid())
        result.append(GetFullPathFromIndex<InterfaceType,ItemType,DataType>(dataAccessor, startIndex.parent()));
    return result + GetPathFromIndex<InterfaceType,ItemType,DataType>(dataAccessor, startIndex);
}


/* Рекурсивно восстанавливает состояние нод дерева
 * @nodes список открытых нод. Заполняется как послеовательная строка строка-колонка...
 * @view отображение в котором требуется восстановить состояние
 * @model указатель на модель
 * @startIndex индекс для детей которого восстанавливается состояние
 * @path текущий путь вверх по дереву
 **/
//template<template<typename> class TreeItemType, typename DataType, typename InterfaceType>
//DataType* GetCurrentDataPointer(QAbstractItemView* view)

template<typename InterfaceType, template <typename> class ItemType, typename DataType>
void ApplyNodePathExpandState(std::function<QVariant(DataType*)> dataAccessor,
                              QStringList & nodes,
                              QTreeView * view,
                              QAbstractItemModel * model,
                              const QModelIndex startIndex,
                              QString path = QString())
{
    path+=GetPathFromIndex<InterfaceType,ItemType,DataType>(dataAccessor, startIndex);
    for(int i(0); i < model->rowCount(startIndex); ++i)
    {
        QModelIndex child = model->index(i, 0, startIndex);
        QString nextPath = path + GetPathFromIndex<InterfaceType,ItemType,DataType>(dataAccessor,child);
        if(!nodes.contains(nextPath))
            continue;
        ApplyNodePathExpandState<InterfaceType,ItemType, DataType>
                (dataAccessor, nodes, view, model, child, path);
    }
    if(nodes.contains(path))
        view->setExpanded( startIndex.sibling(startIndex.row(), 0), true );
}
/* Рекурсивно сохраняет состояние нод дерева
 * @nodes список открытых нод. Заполняется как последовательная строка строка-колонка...
 * @view отображение в котором требуется сохранить состояние
 * @model указатель на модель
 * @startIndex индекс для детей которого сохраняется состояние
 * @path текущий путь вверх по дереву
 **/
template<typename InterfaceType, template <typename> class ItemType, typename DataType>
void StoreNodePathExpandState(std::function<QVariant(DataType*)> dataAccessor,
                              QStringList & nodes,
                              QTreeView * view,
                              QAbstractItemModel * model,
                              const QModelIndex startIndex,
                              QString path = QString())
{
    // Bouml preserved body begin 002020AA
    path+=GetPathFromIndex<InterfaceType,ItemType,DataType>(dataAccessor, startIndex);
    for(int i(0); i < model->rowCount(startIndex); ++i)
    {
        QModelIndex child = model->index(i, 0, startIndex);
        if(!child.isValid())
            continue;
        if(!view->isExpanded(child))
        {
            QString nextPath = path + GetPathFromIndex<InterfaceType,ItemType,DataType>(dataAccessor,child);
            nodes.removeAll(nextPath);
            continue;
        }
        StoreNodePathExpandState<InterfaceType,ItemType, DataType>
                (dataAccessor,nodes, view, model, model->index(i, 0, startIndex), path);
    }

    if(view->isExpanded(startIndex))
    {
        if(!nodes.contains(path))
            nodes << path;
    }
    // Bouml preserved body end 002020AA
}


template<typename InterfaceType>
bool ExpandAllSatisfying(std::function<bool(InterfaceType*)> check,
                              QTreeView * view,
                              QAbstractItemModel * model,
                              const QModelIndex startIndex)
{
    bool returnResult = false;
    for(int i(0); i < model->rowCount(startIndex); ++i)
    {
        QModelIndex child = model->index(i, 0, startIndex);
        if(ExpandAllSatisfying<InterfaceType>
                (check, view, model, child))
        {
            view->setExpanded( startIndex.sibling(startIndex.row(), 0), true );
            returnResult = true;
        }
    }
    if(returnResult || check(static_cast<InterfaceType*>(startIndex.internalPointer())))
        returnResult = true;
    return returnResult;
}


static int MaxOpenLevel(QTreeView * view, QAbstractItemModel * model,const QModelIndex startIndex, int level = -1, bool isFirst = true)
{
    static int result = 0;
    level++;
    if(isFirst)
    {
        result = 0;
        isFirst = false;
    }
    if(view->isExpanded(startIndex.sibling(startIndex.row(), 0)) && (result <= level))
        result = level;

    for(int i(0); i < model->rowCount(startIndex); ++i)
    {
        QModelIndex child = model->index(i, 0, startIndex);
        MaxOpenLevel(view, model, child, level, isFirst);

    }
    level--;
    return result;
}

static void ExpandUpToLevel(QTreeView * view,QAbstractItemModel * model, const QModelIndex startIndex,int maxLevel, int level = -1)
{
    int currentLevel = level+1;
    for(int i(0); i < model->rowCount(startIndex); ++i)
    {
        bool expand = currentLevel <= maxLevel;
//        qDebug() << "Level: " << currentLevel;
//        qDebug() << "Maxlevel: " << maxLevel;
//        qDebug() << "Expand? " << expand;
        QModelIndex child = model->index(i, 0, startIndex);
        view->setExpanded( startIndex.sibling(startIndex.row(), 0), expand);
        ExpandUpToLevel(view, model, child,maxLevel, currentLevel);
    }
}


template<typename InterfaceType, template <typename> class ItemType, typename DataType>
void FilterTreeAndRestoreNodes(std::function<QVariant(DataType*)> dataAccessor,
                               std::function<QList<std::function<bool (InterfaceType *)> > ()> createCheckListFunc,
                               QStringList & nodes,
                               QTreeView * view,
                               TreeModel * model,
                               QSharedPointer<InterfaceType > startIndex, bool forceRoot = false,  bool forceChildren = true)
{
    TreeFunctions::StoreNodePathExpandState<InterfaceType,ItemType,DataType>(dataAccessor, nodes, view, model, QModelIndex());
    PerformFiltering<InterfaceType,ItemType,DataType>(model,startIndex,createCheckListFunc, forceRoot, forceChildren);
    TreeFunctions::ApplyNodePathExpandState<InterfaceType,ItemType,DataType>(dataAccessor, nodes, view, model, QModelIndex());
}
}
#endif // TREEVIEWTEMPLATEFUNCTIONS_H
