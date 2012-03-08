
#include "EdgeMenuFactory.h"
#include "dialog/EdgeMenuDialog.h"
#include "dialog/ClassDialog.h" //< todo Temporary
#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCursor>
#include <QPushButton>


//std::map<uint,boost::function<QWidget*(EdgeMenuFactory*, uint)> > factories;

void ConnectToClassDialog(ClassDialog* dialog, QToolBar* toolbar)
{



}

QToolBar* CreateClassDialogMenu()
{
    QToolBar* toolbar = new QToolBar();
    QPushButton* nextElement = new QPushButton(toolbar);
    QPushButton* previousElement = new QPushButton(toolbar);
    return toolbar;
}

void EdgeMenuFactory::OnEdgeMenuRequested(uint classID, uint orientation)
{
    CreateEdgeMenu(classID, orientation);
}

void EdgeMenuFactory::CreateEdgeMenu(uint classID, uint _orientation)
{
    if(!createdToolbars.contains(classID))
    {
        QToolBar* newToolbar = (factories[classID])(classID);
        //new
    }

    QWidget* senderWidget = qobject_cast<QWidget*>(sender());
    int orientation = ClosestEdge(senderWidget, QCursor::pos()) ? Qt::Horizontal : Qt::Vertical;
}

EdgeMenuFactory::~EdgeMenuFactory()
{
}
