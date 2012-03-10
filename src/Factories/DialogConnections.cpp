#include "Factories/DialogConnections.h"
#include "dialog/EdgeMenuDialog.h"
#include "QPushButton"

void ConnectToClassDialog(EdgeMenuDialog* dialog, QToolBar* toolbar)
{
    QPushButton* pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("NextElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), dialog, SLOT(OnPickNextSibling()));

    pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("PreviousElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), dialog, SLOT(OnPickPreviousSibling()));

    ConnectToLimitedtDialog(dialog, toolbar);

    dialog->ConnectionToToolBarEstablished();
}


void ConnectToLimitedtDialog(EdgeMenuDialog* dialog, QToolBar* toolbar)
{
    QPushButton* pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("OkayElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), dialog, SLOT(accept()));
    pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("CancelElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), dialog, SLOT(reject()));

    pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("OkayElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), toolbar, SLOT(close()));
    pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("CancelElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), toolbar, SLOT(close()));
    dialog->ConnectionToToolBarEstablished();

}
