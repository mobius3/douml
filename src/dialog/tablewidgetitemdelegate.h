#ifndef TABLEWIDGETITEMDELEGATE_H
#define TABLEWIDGETITEMDELEGATE_H
#include <QStyledItemDelegate>
#include <QTableWidget>
class TableWidgetItemDelegate : public QStyledItemDelegate
{
public:
    TableWidgetItemDelegate(QTableWidget *parent = 0, bool edit = true);

     virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;

     virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
     virtual void setModelData(QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index) const;
     void setTypes(QStringList &value);

     bool getEditable() const;
     void setEditable(bool value);

private:
     mutable QStringList m_types;
     mutable bool isEditable;
     QTableWidget *m_tableWidget;
};

#endif // TABLEWIDGETITEMDELEGATE_H
