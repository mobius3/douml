#include "EdgeMenuDialog.h"

unsigned int ClosestEdge(QWidget*, QCursor)
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
    isWritable = _isWritable;
    if (isWritable)
    {
        setOkButton(TR("OK"));
        setCancelButton(TR("Cancel"));
    }
    else
    {
        setOkButton(QString());
        setCancelButton(TR("Close"));
    }

}

