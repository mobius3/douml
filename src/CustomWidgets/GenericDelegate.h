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

#ifndef GENERICDELEGATE_H
#define GENERICDELEGATE_H

#include <QStyledItemDelegate>
#include <functional>

class GenericDelegate : public QStyledItemDelegate
{
public:
    GenericDelegate(QObject *parent = 0, bool _hideText = false);

    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const override;

    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model,
                              const QModelIndex &index) const override;
    virtual QString displayText(const QVariant &value, const QLocale &locale) const override;

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual bool editorEvent(QEvent *event,
                             QAbstractItemModel *model,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) override;

    std::function<void(QWidget *, const QModelIndex &) > dataAccessor;
    std::function<void(QWidget *,QAbstractItemModel*,  const QModelIndex &)> dataSetter;
    std::function<QWidget *(QWidget *)> widgetCreator;
    std::function<void (const QStyledItemDelegate* , QPainter *,const QStyleOptionViewItem&,const QModelIndex &)> paintProcessor;
    std::function<bool(QEvent *event,QAbstractItemModel *model,const QStyleOptionViewItem &option,const QModelIndex &index)> editorEventProcessor;
    bool hideText = false;

private:
    //std::function<void(QWidget *,  const QStyleOptionViewItem &, const QModelIndex &)const> geometryUpdater;
};

#endif // GENERICDELEGATE_H
