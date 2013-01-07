#ifndef OPERATIONWIDGETCPP_H
#define OPERATIONWIDGETCPP_H

#include <QWidget>

namespace Ui
{
class OperationWidgetCpp;
}

class OperationWidgetCpp : public QWidget
{
    Q_OBJECT

public:
    explicit OperationWidgetCpp(QWidget * parent = 0);
    ~OperationWidgetCpp();
    Ui::OperationWidgetCpp * ui;
private:

};

#endif // OPERATIONWIDGETCPP_H
