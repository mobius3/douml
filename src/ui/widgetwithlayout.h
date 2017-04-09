#ifndef WIDGETWITHLAYOUT_H
#define WIDGETWITHLAYOUT_H
#include <QWidget>
class WidgetWithLayout
{
public:
    static QWidget *gridBox(int nCols, QWidget *parent);
    static QWidget *vBox(QWidget *parent);
    static QWidget *hBox(QWidget *parent);
private:
    WidgetWithLayout();
};

#endif // WIDGETWITHLAYOUT_H
