#include "GenericDelegate.h"
#include <QApplication>
#include <QVariant>
static QRect CheckBoxRect(const QStyleOptionViewItem &view_item_style_options) {
  QStyleOptionButton check_box_style_option;
  QRect check_box_rect = QApplication::style()->subElementRect(
      QStyle::SE_CheckBoxIndicator,
      &check_box_style_option);
  QPoint check_box_point(view_item_style_options.rect.x() +
                         view_item_style_options.rect.width() / 2 -
                         check_box_rect.width() / 2,
                         view_item_style_options.rect.y() +
                         view_item_style_options.rect.height() / 2 -
                         check_box_rect.height() / 2);
  return QRect(check_box_point, check_box_rect.size());
}

GenericDelegate::GenericDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}
QWidget * GenericDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    //return widgetCreator(parent);
    return static_cast<QWidget*>(0);
}

void GenericDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    //dataAccessor(editor, index);
}
void GenericDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    //dataSetter(editor, model, index);
}

QString GenericDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    return QString();
}


void GenericDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!index.isValid())
            return;

    QVariant value = index.model()->data(index, Qt::DisplayRole);
    QStyledItemDelegate::paint(painter, option, index);
    if(!value.isValid())
    {
        return;
    }

    bool checked = index.model()->data(index, Qt::DisplayRole).toBool();

    QStyleOptionButton check_box_style_option;
    check_box_style_option.state |= QStyle::State_Enabled;
    if (checked) {
        check_box_style_option.state |= QStyle::State_On;
    } else {
        check_box_style_option.state |= QStyle::State_Off;
    }
    check_box_style_option.rect = CheckBoxRect(option);

    QApplication::style()->drawControl(QStyle::CE_CheckBox,
                                       &check_box_style_option,
                                       painter);
    //QStyledItemDelegate::paint(painter, option, index);
}

bool GenericDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(editorEventProcessor)
        return editorEventProcessor(event, model, option, index);
    else
        return QStyledItemDelegate::editorEvent(event, model, option, index);
}
