
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
    QPushButton* pageButton = qobject_cast<QPushButton*>(toolbar->findChild<QPushButton*>("NextPage"));
    QObject::connect(pageButton, SIGNAL(pressed()), dialog, SLOT(OnPickNextSibling()));

}

QToolBar* CreateClassDialogMenu()
{
    QToolBar* toolbar = new QToolBar();
    QPushButton* nextElement = new QPushButton(toolbar);
    nextElement->setName("NextPage");
    toolbar->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    toolbar->setMinimumHeight(30);
    toolbar->setMinimumWidth(30);
    toolbar->resize(toolbar->sizeHint());
    toolbar->setWindowFlags(Qt::FramelessWindowHint);
    //QPushButton* previousElement = new QPushButton(toolbar);
    return toolbar;
}

void EdgeMenuFactory::OnEdgeMenuRequested(uint classID)
{
    SpawnEdgeMenu(classID);
}

void EdgeMenuFactory::SpawnEdgeMenu(uint classID)
{
    QToolBar* toolbar;
    if(!createdToolbars.contains(classID))
    {
        toolbar = (factories[classID])();
        createdToolbars.insert(classID,toolbar);
    }
    toolbar = createdToolbars[classID];

    EdgeMenuDialog* senderWidget = qobject_cast<EdgeMenuDialog*>(sender());
    //int orientation = ClosestEdge(senderWidget, QCursor::pos()) ? Qt::Horizontal : Qt::Vertical;
    ConnectToClassDialog(senderWidget, toolbar);
    QPoint point = QCursor::pos();
    point.setX(point.x() - 30);
    toolbar->move(point);
    toolbar->show();
}

void EdgeMenuFactory::AddFactory(uint id, ToolbarFactory factory)
{
    if(!factories.contains(id))
    {
        factories.insert(id,factory);
    }
}

EdgeMenuFactory::~EdgeMenuFactory()
{
}

EdgeMenuFactory::EdgeMenuFactory()
{
}
