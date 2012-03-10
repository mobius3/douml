#include "Factories/EdgeToolBarCreation.h"
#include <QPushButton>
#include <QIcon>

QToolBar* CreateLimitedDialogMenu()
{
    QToolBar* toolbar = new QToolBar();

    QPushButton* okayElement = new QPushButton();
    okayElement->setIcon(QIcon(":\\root\\icons\\accept.png"));
    okayElement->setName("OkayElement");
    okayElement->setBaseSize(30,30);

    QPushButton* cancelElement = new QPushButton();
    cancelElement->setIcon(QIcon(":\\root\\icons\\reject.png"));
    cancelElement->setName("CancelElement");
    cancelElement->setBaseSize(30,30);

    toolbar->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    toolbar->setMinimumHeight(30);
    toolbar->setMinimumWidth(30);
    toolbar->resize(toolbar->sizeHint());
    toolbar->setWindowFlags(Qt::FramelessWindowHint);

    toolbar->addWidget(cancelElement);
    toolbar->addWidget(okayElement);
    return toolbar;
}

QToolBar* CreateClassDialogMenu()
{
    QToolBar* toolbar = new QToolBar();


    QPushButton* okayElement = new QPushButton();
    okayElement->setIcon(QIcon(":\\root\\icons\\accept.png"));
    okayElement->setName("OkayElement");
    okayElement->setBaseSize(30,30);

    QPushButton* nextElement = new QPushButton();
    nextElement->setIcon(QIcon(":\\root\\icons\\up.png"));
    nextElement->setName("NextElement");
    nextElement->setBaseSize(30,30);

    QPushButton* previousElement = new QPushButton();
    previousElement->setIcon(QIcon(":\\root\\icons\\down.png"));
    previousElement->setName("PreviousElement");
    previousElement->setBaseSize(30,30);

    QPushButton* cancelElement = new QPushButton();
    cancelElement->setIcon(QIcon(":\\root\\icons\\reject.png"));
    cancelElement->setName("CancelElement");
    cancelElement->setBaseSize(30,30);

    toolbar->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    toolbar->setMinimumHeight(30);
    toolbar->setMinimumWidth(30);
    toolbar->resize(toolbar->sizeHint());
    toolbar->setWindowFlags(Qt::FramelessWindowHint);

    toolbar->addWidget(cancelElement);
    toolbar->addWidget(nextElement);
    toolbar->addWidget(previousElement);
    toolbar->addWidget(okayElement);
    return toolbar;
}

