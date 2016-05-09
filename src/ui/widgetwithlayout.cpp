#include "widgetwithlayout.h"
#include <QGridLayout>
#include <QVBoxLayout>

QWidget *WidgetWithLayout::gridBox(int nCols, QWidget *parent)
{
    Q_UNUSED(nCols);
    
    QGridLayout *layout = new QGridLayout();
    QWidget *widget = new QWidget(parent);
    widget->setLayout(layout);
    return widget;
}

QWidget *WidgetWithLayout::vBox(QWidget *parent)
{
    QVBoxLayout *layout = new QVBoxLayout();
    QWidget *widget = new QWidget(parent);
    widget->setLayout(layout);
    return widget;
}

QWidget *WidgetWithLayout::hBox(QWidget *parent)
{
    QHBoxLayout *layout = new QHBoxLayout();
    QWidget *widget = new QWidget(parent);
    widget->setLayout(layout);
    return widget;
}

WidgetWithLayout::WidgetWithLayout()
{
}
