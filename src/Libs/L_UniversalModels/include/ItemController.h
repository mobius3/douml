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
#ifndef _ITEMCONTROLLER_H
#define _ITEMCONTROLLER_H


#include <QStringList>
#include <QVariant>
#include <QModelIndex>
#include <QVector>
#include <QHash>

#include "l_tree_controller_global.h"

#include <functional>

template<class T>
class ItemController  
{
  public:
    inline QStringList GetColumns() const;

    void SetColumns(QStringList value);

    QVariant GetValue(const T * item, const QModelIndex & index, int role);

    bool SetValue(T * item, const QModelIndex & index, const QVariant & value, int role);

    void AddGetter(const QPair<int,int> & index, std::function<QVariant(const T*, QModelIndex)> function);

    void AddGetter(int row, const QVector<int> & roles, std::function<QVariant(const T*, QModelIndex)> function);

    void AddSetter(const QPair<int,int> & index, std::function<bool(T*, QVariant, QModelIndex)> function);

    void AddSetter(int row, const QVector<int> & roles, std::function<bool(T*, QVariant, QModelIndex)> function);

    void AddPostProcessor(int column, int role, std::function<void(T*, const QModelIndex&)> & _postProcessor);

    void AddPostProcessors(int column, const QVector<int> & roles, std::function<void(T*,const QModelIndex&)> & _postProcessor);

    Qt::ItemFlags flags(const QModelIndex & index) const;

    inline QVector<std::function<Qt::ItemFlags(const QModelIndex&)> > GetFlagsFunctors();

    void SetFlagsFunctors(QVector<std::function<Qt::ItemFlags(const QModelIndex&)> > value);

    void AddFlagsFunctor(std::function<Qt::ItemFlags(const QModelIndex&)> functor);

    void SetDefaultTreeFunctor();


  private:
     QStringList columns;
     QHash<QPair<int, int>, std::function<QVariant(const T*, QModelIndex)> > getters;
     QHash<QPair<int,int>, std::function<bool(T*, QVariant, QModelIndex)> > setters;
     QVector<std::function<Qt::ItemFlags(const QModelIndex&)> > flagsFunctors;
     QHash<QPair<int, int> , std::function<void(T*, const QModelIndex&)> > postProcessors;
};
template<class T>
inline QStringList ItemController<T>::GetColumns() const 
{
    return columns;
}

template<class T>
void ItemController<T>::SetColumns(QStringList value) 
{
    columns = value;
}

template<class T>
QVariant ItemController<T>::GetValue(const T * item, const QModelIndex & index, int role) 
{
    // Bouml preserved body begin 00203B2A
    //return QVariant();
    if(!getters.contains(QPair<int,int>(index.column(), role)))
        return QVariant();
    QVariant ret = getters[QPair<int,int>(index.column(), role)](item, index);
    return ret;
    // Bouml preserved body end 00203B2A
}

template<class T>
bool ItemController<T>::SetValue(T * item, const QModelIndex & index, const QVariant & value, int role) 
{
    // Bouml preserved body begin 00203BAA
    if(!setters.contains(QPair<int,int>(index.column(), role)))
        return false;
    bool result = setters[QPair<int,int>(index.column(), role)](item, value, index);
    if(postProcessors.contains(QPair<int,int>(index.column(), role)) && postProcessors[QPair<int,int>(index.column(), role)] != 0)
        postProcessors[QPair<int,int>(index.column(), role)](item, index);
    return result;
    // Bouml preserved body end 00203BAA
}

template<class T>
void ItemController<T>::AddGetter(const QPair<int,int> & index, std::function<QVariant(const T*, QModelIndex)> function) 
{
    // Bouml preserved body begin 002117AA
    getters.insert(index, function);
    // Bouml preserved body end 002117AA
}

template<class T>
void ItemController<T>::AddGetter(int row, const QVector<int> & roles, std::function<QVariant(const T*, QModelIndex)> function) 
{
    // Bouml preserved body begin 00230DAA
    for(int role : roles)
    {
        AddGetter(QPair<int,int>(row, role), function);
    }
    // Bouml preserved body end 00230DAA
}

template<class T>
void ItemController<T>::AddSetter(const QPair<int,int> & index, std::function<bool(T*, QVariant, QModelIndex)> function) 
{
    // Bouml preserved body begin 0021182A
    setters.insert(index, function);
    // Bouml preserved body end 0021182A
}

template<class T>
void ItemController<T>::AddSetter(int row, const QVector<int> & roles, std::function<bool(T*, QVariant, QModelIndex)> function) 
{
    // Bouml preserved body begin 00230D2A
    for(int role : roles)
    {
        AddSetter(QPair<int,int>(row, role), function);
    }
    // Bouml preserved body end 00230D2A
}

template<class T>
void ItemController<T>::AddPostProcessor(int column, int role, std::function<void(T*, const QModelIndex&)> & _postProcessor) 
{
    // Bouml preserved body begin 002327AA
    postProcessors.insert(QPair<int,int>(column,role), _postProcessor);
    // Bouml preserved body end 002327AA
}

template<class T>
void ItemController<T>::AddPostProcessors(int column, const QVector<int> & roles, std::function<void(T*,const QModelIndex&)> & _postProcessor) 
{
    // Bouml preserved body begin 0023272A
    for(int role : roles)
    {
        AddPostProcessor(column, role, _postProcessor);
    }
    // Bouml preserved body end 0023272A
}

template<class T>
Qt::ItemFlags ItemController<T>::flags(const QModelIndex & index) const 
{
    // Bouml preserved body begin 0021AFAA
    Qt::ItemFlags result;
    for(auto func: flagsFunctors)
    {
        result |= func(index);
    }
    return result;
    // Bouml preserved body end 0021AFAA
}

template<class T>
inline QVector<std::function<Qt::ItemFlags(const QModelIndex&)> > ItemController<T>::GetFlagsFunctors() 
{
    return flagsFunctors;
}

template<class T>
void ItemController<T>::SetFlagsFunctors(QVector<std::function<Qt::ItemFlags(const QModelIndex&)> > value) 
{
    flagsFunctors = value;
}

template<class T>
void ItemController<T>::AddFlagsFunctor(std::function<Qt::ItemFlags(const QModelIndex&)> functor) 
{
    // Bouml preserved body begin 0021B22A
    flagsFunctors.append(functor);
    // Bouml preserved body end 0021B22A
}

template<class T>
void ItemController<T>::SetDefaultTreeFunctor() 
{
    // Bouml preserved body begin 0021B1AA
    AddFlagsFunctor([](const QModelIndex& index)
    {
        Qt::ItemFlags flags;
        if ( index.column() == 0 )
            flags |= Qt::ItemIsUserCheckable;
        return flags;
    }
    );
    // Bouml preserved body end 0021B1AA
}

#endif
