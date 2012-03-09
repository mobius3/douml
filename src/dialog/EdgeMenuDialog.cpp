#include <QTabBar>
#include "EdgeMenuDialog.h"
#include "browser/BrowserNode.h"
#include "Logging/QsLog.h"
#include "Factories/EdgeMenuFactory.h"

unsigned int ClosestEdge(QWidget* widget, QPoint position)
{
    QPoint widgetGlobalOrigin = widget->mapToGlobal(QPoint());
    QSize widgetSize = widget->size();
    QPoint widgetGlobalFarEnd = widgetGlobalOrigin;
    widgetGlobalFarEnd.setX(widgetGlobalFarEnd.x() + widgetSize.width());
    widgetGlobalFarEnd.setY(widgetGlobalFarEnd.y() + widgetSize.height());

    QVector<int> distances;
    distances << qAbs(position.y() -  widgetGlobalOrigin.y());
    distances << qAbs(position.y() -  widgetGlobalFarEnd.y());
    distances << qAbs(position.x() -  widgetGlobalOrigin.x());
    distances << qAbs(position.x() -  widgetGlobalFarEnd.x());


    // origial minDistance should be sufficient
    // so that it cannot be less than what can actually happen
    int minDistance = 200000;
    minDistance = qMin(distances[0],distances[1]);
    minDistance = qMin(minDistance,distances[2]);
    minDistance = qMin(minDistance,distances[3]);

    auto it = qFind(distances.begin(),distances.end(), minDistance);

    return it - distances.begin();
}

EdgeMenuDialog::EdgeMenuDialog(QWidget * parent, const char * name, bool modal , Qt::WindowFlags f): Q3TabDialog(parent, name, modal, f)
{
    currentTab = 0;
    isConnectedToToolBar = false;
    An<EdgeMenuFactory> factory;
    QObject::connect(this, SIGNAL(edgeMenuRequested(uint)),factory.getData(), SLOT(OnEdgeMenuRequested(uint)));
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

EdgeMenuDialog::~EdgeMenuDialog()
{}

bool EdgeMenuDialog::IsConnectedToToolBar()
{
    return isConnectedToToolBar;
}

void EdgeMenuDialog::ConnectionToToolBarEstablished()
{
    isConnectedToToolBar = true;
}

void EdgeMenuDialog::BreakConnectionToToolBar()
{
    isConnectedToToolBar = false;
}

void EdgeMenuDialog::leaveEvent(QEvent *event)
{
    emit edgeMenuRequested(this->TypeID());
}

void EdgeMenuDialog::showEvent(QShowEvent *event)
{
    An<EdgeMenuFactory> factory;
    this->move(QCursor::pos().x() + 15, QCursor::pos().y());
    factory->SpawnEdgeMenu(this->TypeID(), this, QCursor::pos());
    this->setFocus();
}

void EdgeMenuDialog::wheelEvent(QWheelEvent *event)
{
    currentTab += event->delta()/event->delta();
    if(currentTab > tabBar()->count())
        currentTab = 0;
    if(currentTab < 0)
        currentTab = tabBar()->count() - 1;
    tabBar()->setCurrentIndex(currentTab);
    //tabBar()->
}

void EdgeMenuDialog::RegisterTab(QString name, QWidget * widget)
{
    if(!tabs.contains(name))
        tabs.insert(name,widget);
}

void EdgeMenuDialog::HideTab(QString name)
{
    removePage(tabs[name]);
}

void EdgeMenuDialog::ShowTab(QString name)
{
    addTab(tabs[name],name);
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

void EdgeMenuDialog::OnPickNextSibling()
{
    bool continueSearch = true;
    BrowserNode* nextNode = 0;
    BrowserNode* originalNode = GetCurrentNode();
    BrowserNode* currentNode = originalNode;

    while(continueSearch)
    {
        nextNode = dynamic_cast<BrowserNode*>(currentNode->itemAbove());
        //QLOG_INFO() << "NEXT: " << nextNode->get_name() << " " << nextNode->depth();
        if(!nextNode)
        {
            continueSearch = false;
        }
        bool sameLevel = originalNode->depth() == nextNode->depth();
//        QLOG_INFO() << "NEXT: " << "Origin level : " << originalNode->depth();
//        QLOG_INFO() << "NEXT: " << "Current level : " << nextNode->depth();
        if(sameLevel)
            continueSearch = false;
        currentNode = nextNode;
    }
    if(nextNode == 0)
        return;
    SaveData();
    FillGuiElements(nextNode);
}

void EdgeMenuDialog::OnPickPreviousSibling()
{
    bool continueSearch = true;
    BrowserNode* previousNode = 0;
    BrowserNode* originalNode = GetCurrentNode();
    int originalDepth = originalNode->depth();
    BrowserNode* currentNode = originalNode;
    while(continueSearch)
    {
        previousNode = dynamic_cast<BrowserNode*>(currentNode->itemBelow());
        //QLOG_INFO() << "Nodename is: " << previousNode->get_name() << " " << previousNode->depth();
        if(!previousNode)
        {
            continueSearch = false;
        }
        int previousDepth = previousNode->depth();
        //QLOG_INFO() << "PREVIOUS: " << "Origin level : " << originalDepth;
        //QLOG_INFO() << "PREVIOUS: " << "Current level : " << previousDepth;
        bool sameLevel = originalDepth == previousDepth;

        if(sameLevel)
            continueSearch = false;
        currentNode = previousNode;
    }
    if(previousNode == 0)
        return;
    SaveData();
    FillGuiElements(previousNode);
}
