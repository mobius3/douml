// *************************************************************************
//
// 
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

#ifndef _TREEITEM_H
#define _TREEITEM_H

#include <QList>
#include <QSharedPointer>
#include "TreeItemInterface.h"
#include <QVariant>
#include <QModelIndex>
#include "ItemController.h"
#include <QStringList>

#include "l_tree_controller_global.h"

#include <QAbstractItemView>

template<class T>
class TreeItem : public TreeItemInterface  
{
typedef TreeItem<T> value_type;
public:
    TreeItem(T * data = nullptr);
    explicit TreeItem();

    virtual QList<QSharedPointer<TreeItemInterface> > GetChildren() override;

    void ResetState();

    virtual ~TreeItem();

    virtual int columnCount() const override;
    virtual int childCount() const override;
    virtual QVariant data(const QModelIndex & index, int role) override;
    virtual bool isCheckable() const override;
    virtual void setCheckState(Qt::CheckState state) override;
    virtual Qt::CheckState checkState() override;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role) override;
    virtual bool removeChildren(int position, int count) override;
    virtual bool insertChildren(int position, int count) override;

    virtual QList<QSharedPointer<TreeItemInterface > >& children();
    virtual const QList<QSharedPointer<TreeItemInterface > >& children() const;
    void addChildren(QList<QSharedPointer<TreeItemInterface> > _children);
    inline QSharedPointer<ItemController<T> > GetController() const;

    void SetController(QSharedPointer<ItemController<T> > value);
    virtual QStringList GetColumns() override;
    virtual int IndexOf(TreeItemInterface * item) override;
    void SetInternalData(T * _data);
    virtual void* InternalPointer() override;
    virtual void* InternalPointer() const override;
    virtual TreeItemInterface* child(int row) override;
    virtual TreeItemInterface* parent() override;
    virtual int row() override;
    virtual void SetParent(QSharedPointer<TreeItemInterface > _parent) override;
    virtual int GetIndexOfChild(TreeItemInterface * child) override;
    virtual Qt::ItemFlags flags(const QModelIndex & index) const override;
    virtual void AddChildren(QList<QSharedPointer<TreeItemInterface> > children, int insertAfter = 0) override;
    virtual QSharedPointer<TreeItemInterface> GetParent() override;

private:
    T* m_data = nullptr;

protected:
     QList<QSharedPointer<TreeItemInterface > > m_children;
     QWeakPointer<TreeItemInterface > m_parent;

private:
    bool m_isCheckable;
    Qt::CheckState m_checkState;
    QSharedPointer<ItemController<T> > controller;
};

template<class T>
TreeItem<T>::TreeItem(T * data) : TreeItemInterface()
{
    // Bouml preserved body begin 0020A62A
    ResetState();
    m_data = data;
    // Bouml preserved body end 0020A62A
}

template<class T>
TreeItem<T>::TreeItem() : TreeItemInterface()
{
    // Bouml preserved body begin 0020A72A
    ResetState();
    // Bouml preserved body end 0020A72A
}

template<class T>
QList<QSharedPointer<TreeItemInterface> > TreeItem<T>::GetChildren() 
{
    // Bouml preserved body begin 002202AA
    return m_children;
    // Bouml preserved body end 002202AA
}

template<class T>
void TreeItem<T>::ResetState() 
{
    // Bouml preserved body begin 0021CE2A
    m_checkState = Qt::Unchecked;
    //m_data = T();
    m_children.clear();
    m_parent.clear();
    m_isCheckable = false;
    controller = QSharedPointer<ItemController<T> >();
    // Bouml preserved body end 0021CE2A
}

template<class T>
TreeItem<T>::~TreeItem() 
{
    // Bouml preserved body begin 0020A6AA
    // Bouml preserved body end 0020A6AA
}

template<class T>
int TreeItem<T>::columnCount() const 
{
    // Bouml preserved body begin 0020402A
    return controller->GetColumns().size();
    // Bouml preserved body end 0020402A
}

template<class T>
int TreeItem<T>::childCount() const 
{
    // Bouml preserved body begin 002040AA
    return m_children.size();
    // Bouml preserved body end 002040AA
}

template<class T>
QVariant TreeItem<T>::data(const QModelIndex & index, int role) 
{
    // Bouml preserved body begin 00203FAA
    return controller->GetValue(m_data, index, role);
    // Bouml preserved body end 00203FAA
}

template<class T>
bool TreeItem<T>::isCheckable() const 
{
    // Bouml preserved body begin 00203F2A
    return m_isCheckable;
    // Bouml preserved body end 00203F2A
}

template<class T>
void TreeItem<T>::setCheckState(Qt::CheckState state) 
{
    // Bouml preserved body begin 00203EAA
    m_checkState = state;
    // Bouml preserved body end 00203EAA
}

template<class T>
Qt::CheckState TreeItem<T>::checkState() 
{
    // Bouml preserved body begin 00203E2A
    return m_checkState;
    // Bouml preserved body end 00203E2A
}

template<class T>
bool TreeItem<T>::setData(const QModelIndex & index, const QVariant & value, int role) 
{
    // Bouml preserved body begin 00203D2A
    controller->SetValue(m_data, index,value, role);
    return true;
    // Bouml preserved body end 00203D2A
}

template<class T>
bool TreeItem<T>::removeChildren(int position, int count) 
{
    // Bouml preserved body begin 00203CAA
    if (position < 0 || position > m_children.size())
        return false;
    //qDebug() << Q_FUNC_INFO;
    auto leftBound = m_children.begin()+position;
    auto rightBound = leftBound + (count);
    m_children.erase(leftBound,rightBound);
    return true;
    // Bouml preserved body end 00203CAA
}

template<class T>
bool TreeItem<T>::insertChildren(int position, int count) 
{
    // Bouml preserved body begin 00203C2A
    if (position < 0 || position > m_children.size())
        return false;

    for (int row = 0; row < count; ++row)
    {
        QSharedPointer<TreeItemInterface> item (new TreeItem<T>(0));
        item->SetParent(this->parent()->GetChildren()[this->parent()->GetIndexOfChild(this)]);
        m_children.insert(position, item);
    }

    return true;
    // Bouml preserved body end 00203C2A
}

template<class T>
QList<QSharedPointer<TreeItemInterface > >& TreeItem<T>::children() 
{
    // Bouml preserved body begin 0020432A
    return m_children;
    // Bouml preserved body end 0020432A
}

template<class T>
const QList<QSharedPointer<TreeItemInterface > >& TreeItem<T>::children() const 
{
    // Bouml preserved body begin 002042AA
    return m_children;
    // Bouml preserved body end 002042AA
}

template<class T>
void TreeItem<T>::addChildren(QList<QSharedPointer<TreeItemInterface> > _children) 
{
    // Bouml preserved body begin 0020422A
    m_children.append(_children);
    // Bouml preserved body end 0020422A
}

template<class T>
inline QSharedPointer<ItemController<T> > TreeItem<T>::GetController() const 
{
    return controller;
}

template<class T>
void TreeItem<T>::SetController(QSharedPointer<ItemController<T> > value) 
{
    controller = value;
}

template<class T>
QStringList TreeItem<T>::GetColumns() 
{
    // Bouml preserved body begin 00206CAA
    return controller->GetColumns();
    // Bouml preserved body end 00206CAA
}

template<class T>
int TreeItem<T>::IndexOf(TreeItemInterface * item) 
{
    // Bouml preserved body begin 00206D2A
    return GetIndexOfChild(item);
    // Bouml preserved body end 00206D2A
}

template<class T>
void TreeItem<T>::SetInternalData(T * _data) 
{
    // Bouml preserved body begin 0020A7AA
    m_data = _data;
    // Bouml preserved body end 0020A7AA
}

template<class T>
void* TreeItem<T>::InternalPointer() 
{
    // Bouml preserved body begin 002086AA
    return m_data;
    // Bouml preserved body end 002086AA
}

template<class T>
void* TreeItem<T>::InternalPointer() const 
{
    // Bouml preserved body begin 00235B2A
     return m_data;
    // Bouml preserved body end 00235B2A
}

template<class T>
TreeItemInterface* TreeItem<T>::child(int row) 
{
    // Bouml preserved body begin 0020CD2A
    TreeItemInterface* returnChildren = nullptr;
    if (m_children.size() > row)
        returnChildren = m_children[row].data();
    return returnChildren;
    // Bouml preserved body end 0020CD2A
}

template<class T>
TreeItemInterface* TreeItem<T>::parent() 
{
    // Bouml preserved body begin 0020CDAA
    return m_parent.toStrongRef().data();
    // Bouml preserved body end 0020CDAA
}

template<class T>
int TreeItem<T>::row() 
{
    // Bouml preserved body begin 0020CEAA
    if (!m_parent.isNull())
        return dynamic_cast<TreeItem<T>*>(m_parent.toStrongRef().data())->IndexOf(this);
    return 0;
    // Bouml preserved body end 0020CEAA
}

template<class T>
void TreeItem<T>::SetParent(QSharedPointer<TreeItemInterface > _parent) 
{
    // Bouml preserved body begin 0020CFAA
    m_parent = _parent;
    // Bouml preserved body end 0020CFAA
}

template<class T>
int TreeItem<T>::GetIndexOfChild(TreeItemInterface * child) 
{
    // Bouml preserved body begin 0020D02A
    for (int i = 0; i < m_children.size(); ++i)
    {
        if (m_children.at(i).data() == child)
            return i;
    }
    return -1;
    // Bouml preserved body end 0020D02A
}

template<class T>
Qt::ItemFlags TreeItem<T>::flags(const QModelIndex & index) const 
{
    // Bouml preserved body begin 0021B2AA
    if (index.isValid())
        return controller->flags(index);
    return Qt::ItemFlags();
    // Bouml preserved body end 0021B2AA
}

template<class T>
void TreeItem<T>::AddChildren(QList<QSharedPointer<TreeItemInterface> > children, int insertAfter) 
{
    // Bouml preserved body begin 002201AA
    //m_children.insert(m_children.begin() + insertAfter, children);
    //m_children.reserve(m_children.size() + children.size());
    int i = 0;
    for (const auto& child : children)
    {
        m_children.insert(m_children.begin() + insertAfter + i, child);
        i++;
    }
    // Bouml preserved body end 002201AA
}

template<class T>
QSharedPointer<TreeItemInterface> TreeItem<T>::GetParent() 
{
    // Bouml preserved body begin 002341AA
    return m_parent.toStrongRef();
    // Bouml preserved body end 002341AA
}

#endif
