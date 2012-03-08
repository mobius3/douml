#include "EdgeMenuDialog.h"

unsigned int ClosestEdge(QWidget*, QPoint)
{
    return 0;
}

EdgeMenuDialog::EdgeMenuDialog(QWidget * parent, const char * name, bool modal , Qt::WindowFlags f): Q3TabDialog(parent, name, modal, f)
{
}

EdgeMenuDialog::~EdgeMenuDialog()
{}

void EdgeMenuDialog::leaveEvent(QEvent *event)
{
    emit edgeMenuRequested(this->TypeID());
}

void EdgeMenuDialog::SetDialogMode(bool _isWritable)
{

    if (isWritable)
    {
        setOkButton(QObject::tr("OK"));
        setCancelButton(QObject::tr("Cancel"));
    }
    else
    {
        setOkButton(QString());
        setCancelButton(QObject::tr("Close"));
    }

}

