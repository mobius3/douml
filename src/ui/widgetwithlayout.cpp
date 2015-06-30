#include "widgetwithlayout.h"
#include <QGridLayout>
#include <QVBoxLayout>
QWidget *WidgetWithLayout::gridBox(int nCols, QWidget *parent)
{
    QGridLayout *layout = new QGridLayout(parent);
    QWidget *widget = new QWidget(parent);
    widget->setLayout(layout);
    return widget;
}

QWidget *WidgetWithLayout::vBox(QWidget *parent)
{
    QVBoxLayout *layout = new QVBoxLayout(parent);
    QWidget *widget = new QWidget(parent);
    widget->setLayout(layout);
    return widget;
}

QWidget *WidgetWithLayout::hBox(QWidget *parent)
{
    QHBoxLayout *layout = new QHBoxLayout(parent);
    QWidget *widget = new QWidget(parent);
    widget->setLayout(layout);
    return widget;
}

WidgetWithLayout::WidgetWithLayout()
{
}
