#include "tablewidgetitemdelegate.h"
#include <QComboBox>
#include "ComboItem.h"
#include "MLinesItem.h"
TableWidgetItemDelegate::TableWidgetItemDelegate(QTableWidget *parent, bool edit)
    : QStyledItemDelegate(parent), isEditable(edit)
{
    m_tableWidget = parent;
}

QWidget *TableWidgetItemDelegate::createEditor(QWidget *parent,
                                               const QStyleOptionViewItem & option ,
                                               const QModelIndex & index ) const
{
    if(m_tableWidget->item(index.row(), index.column())) //no item is set in read only mode
    {
        if(m_tableWidget->item(index.row(), index.column())->type() == TableItem::ComboType)
        {
            QComboBox *editor = new QComboBox(parent);
            return editor;
        }
        else if(m_tableWidget->item(index.row(), index.column())->type() == TableItem::MLinesType)
        {
            QTextEdit *editor = new QTextEdit(parent);
            return editor;
        }
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void TableWidgetItemDelegate::setEditorData(QWidget *editor,
                                            const QModelIndex &index) const
{
    if(m_tableWidget->item(index.row(), index.column())) //no item is set in read only mode
    {
        if(m_tableWidget->item(index.row(), index.column())->type() == TableItem::ComboType)
        {
            if(m_tableWidget->item(index.row(), index.column()))
            {
                ComboItem *it = static_cast<ComboItem *> (m_tableWidget->item(index.row(), index.column()));
                m_types = it->getTypes();
                isEditable = it->getEditable();
            }
            QComboBox *cb = static_cast<QComboBox*>(editor);
            cb->clear();
            cb->setEditable(isEditable);
            if(index.model()->data(index, Qt::DisplayRole).isValid())
                cb->addItem(index.model()->data(index, Qt::DisplayRole).toString());
            cb->addItems(m_types);
            cb->setAutoCompletion(completion());
            int cbIndex = m_types.indexOf(index.model()->data(index, Qt::DisplayRole).toString());
            if (cbIndex != -1)
                cb->setCurrentIndex(cbIndex + 1);
            return;
        }
        else if(m_tableWidget->item(index.row(), index.column())->type() == TableItem::MLinesType)
        {
            QTextEdit *te = static_cast<QTextEdit*>(editor);
            te->clear();
            te->setReadOnly(false);
            te->setText(index.model()->data(index, Qt::DisplayRole).toString());
            return;
        }
    }
    QStyledItemDelegate::setEditorData(editor, index);
}

void TableWidgetItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                           const QModelIndex &index) const
{
    if(m_tableWidget->item(index.row(), index.column())) //no item is set in read only mode
    {
        if(m_tableWidget->item(index.row(), index.column())->type() == TableItem::ComboType)
        {
            QComboBox *cb = static_cast<QComboBox*>(editor);
            model->setData(index, cb->currentText(), Qt::EditRole);
            return;
        }
        else if(m_tableWidget->item(index.row(), index.column())->type() == TableItem::MLinesType)
        {
            QTextEdit *te = static_cast<QTextEdit*>(editor);
            model->setData(index, te->toPlainText(), Qt::EditRole);
            return;
        }
    }
    QStyledItemDelegate::setModelData(editor, model, index);

}


void TableWidgetItemDelegate::setTypes(QStringList &value)
{
    m_types = value;
}
bool TableWidgetItemDelegate::getEditable() const
{
    return isEditable;
}

void TableWidgetItemDelegate::setEditable(bool value)
{
    isEditable = value;
}

