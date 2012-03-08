
#include "EdgeMenuFactory.h"
#include "dialog/EdgeMenuDialog.h"
#include "dialog/ClassDialog.h" //< todo Temporary
#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCursor>


//std::map<uint,boost::function<QWidget*(EdgeMenuFactory*, uint)> > factories;

void ConnectToClassDialog(ClassDialog* dialog, QToolBar* toolbar)
{



}

QToolBar* CreateClassDialogMenu()
{
    QToolBar* toobar = new QToolBar(menu);
    QPushButton nextElement = new QPushButton(toobar);
    QPushButton previousElement = new QPushButton(toobar);
    return toolbar;
}

void EdgeMenuFactory::OnEdgeMenuRequested(uint classID, uint orientation)
{
    CreateEdgeMenu(classID, orientation);
}

EdgeMenuFactory::CreateEdgeMenu(uint classID, uint orientation)
{
    if(!createdToolbars.contains(classID))
    {
        QToolBar* newToolbar = factories[classID]();
        new
    }

    QWidget* senderWidget == qobject_cast<QWidget*>(sender());
    int orientation = ClosestEdge(senderWidget, QCursor::pos()) ? Qt::Horizontal : Qt::Vertical;
}
