
#include "EdgeMenuFactory.h"
#include "dialog/EdgeMenuDialog.h"
#include "dialog/ClassDialog.h" //< todo Temporary
#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCursor>
#include <QPushButton>


void ConnectToClassDialog(EdgeMenuDialog* dialog, QToolBar* toolbar)
{
    QPushButton* pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("NextElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), dialog, SLOT(OnPickNextSibling()));

    pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("PreviousElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), dialog, SLOT(OnPickPreviousSibling()));

    pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("OkayElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), dialog, SLOT(accept()));
    pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("CancelElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), dialog, SLOT(reject()));

    pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("OkayElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), toolbar, SLOT(close()));
    pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("CancelElement"));
    QObject::connect(pageButton, SIGNAL(clicked()), toolbar, SLOT(close()));

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

void EdgeMenuFactory::OnEdgeMenuRequested(uint classID)
{
    EdgeMenuDialog* senderWidget = qobject_cast<EdgeMenuDialog*>(sender());
    SpawnEdgeMenu(classID,senderWidget);
}

void EdgeMenuFactory::SpawnEdgeMenu(uint classID, EdgeMenuDialog* senderWidget)
{
    QToolBar* toolbar;
    if(!createdToolbars.contains(classID))
    {
        toolbar = (factories[classID])();
        createdToolbars.insert(classID,toolbar);
    }
    toolbar = createdToolbars[classID];


    int trueOrientation = ClosestEdge(senderWidget, QCursor::pos());
    int orientation;

    // position 0 and 1 signify horizontal orientation
    //          2 and 3 signify  vertical orientation
    if(trueOrientation < 2)
        orientation = 1;
    else
        orientation = 2;

    toolbar->setOrientation(static_cast<Qt::Orientation>(orientation));
    QPoint point = QCursor::pos();
    //now we need to position toolbar correctly

    int toolBarIconHeight = 30;
    int toolBarIconWidth = 30;

    // if we are near the top
    if(trueOrientation == 0)
    {
        point.setY(point.y() - toolBarIconHeight);
        point.setX(point.x() - toolBarIconWidth/2);
    }
    // if we are near the top
    if(trueOrientation == 1)
    {
        point.setY(point.y());
        point.setX(point.x() - toolBarIconWidth/2);
    }
    // if we are near the left edge
    if(trueOrientation == 2)
    {
        point.setX(point.x() - toolBarIconWidth);
        point.setY(point.y() - toolBarIconHeight/2);
    }
    // if we are near the right edge
    if(trueOrientation == 3)
    {
        point.setX(point.x());
        point.setY(point.y() - toolBarIconHeight/2);
    }
    toolbar->move(point);

    ConnectToClassDialog(senderWidget, toolbar);
    toolbar->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
    toolbar->resize(toolbar->sizeHint());
    toolbar->show();
}

void EdgeMenuFactory::AddFactory(uint id, ToolbarFactory factory)
{
    if(!factories.contains(id))
    {
        factories.insert(id,factory);
    }
}

void EdgeMenuFactory::SpawnEdgeMenu(uint classID, EdgeMenuDialog* parent,  QPoint origin)
{
    SpawnEdgeMenu(classID, parent);
}

EdgeMenuFactory::~EdgeMenuFactory()
{
}

EdgeMenuFactory::EdgeMenuFactory()
{
}
