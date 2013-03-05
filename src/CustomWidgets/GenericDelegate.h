#ifndef GENERICDELEGATE_H
#define GENERICDELEGATE_H
#include <QStyledItemDelegate>
#include <functional>
class GenericDelegate : public QStyledItemDelegate
{
public:
    GenericDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;
    QString displayText(const QVariant &value, const QLocale &locale) const;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event,
                                       QAbstractItemModel *model,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index) override;

    std::function<void(QWidget *, const QModelIndex &) > dataAccessor;
    std::function<void(QWidget *,QAbstractItemModel*,  const QModelIndex &)> dataSetter;
    std::function<QWidget *(QWidget *)> widgetCreator;
    std::function<bool(QEvent *event,QAbstractItemModel *model,const QStyleOptionViewItem &option,const QModelIndex &index)> editorEventProcessor;

private:

    //std::function<void(QWidget *,  const QStyleOptionViewItem &, const QModelIndex &)const> geometryUpdater;
};


#endif // GENERICDELEGATE_H
