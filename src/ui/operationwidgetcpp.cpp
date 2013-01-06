#include "operationwidgetcpp.h"
#include "ui_operationwidgetcpp.h"

OperationWidgetCpp::OperationWidgetCpp(QWidget * parent) :
    QWidget(parent),
    ui(new Ui::OperationWidgetCpp)
{
    ui->setupUi(this);
}

OperationWidgetCpp::~OperationWidgetCpp()
{
    delete ui;
}
