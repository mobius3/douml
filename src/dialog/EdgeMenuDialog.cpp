// *************************************************************************
//
// Copyright 2012-2012 Nikolai Marchenko  .
//
// This file is part of the BreezeUML Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// e-mail : enmarantispam@gmail.com
//
// *************************************************************************
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
    currentNode = 0;
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
    QPoint cursorPosition = mapFromGlobal(QCursor::pos());
    bool isWithinX = cursorPosition.x() > 0 && cursorPosition.x() < size().width();
    bool isWithinY = cursorPosition.y() > 0 && cursorPosition.y() < size().height();
    bool isOutside = !isWithinX || !isWithinY;
    if(isOutside)
        emit edgeMenuRequested(this->TypeID());
}

void EdgeMenuDialog::enterEvent(QEvent *event)
{
    QPoint cursorPosition = mapFromGlobal(QCursor::pos());
    bool isWithinX = cursorPosition.x() > 0 && cursorPosition.x() < size().width();
    bool isWithinY = cursorPosition.y() > 0 && cursorPosition.y() < size().height();
    bool isOutside = !isWithinX || !isWithinY;
    if(isOutside)
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

void EdgeMenuDialog::OnInitiateMove(QPoint origin)
{
    IntitiateMove(origin);
}

void EdgeMenuDialog::OnInitiateResize(QPoint origin)
{
    InitiateResize(origin);
}

void EdgeMenuDialog::OnNewCoordinatesReceived(QPoint newPoint)
{
    if(modificationMode == wmm_drag)
        MoveThis(modificationOrigin, newPoint);
    if(modificationMode == wmm_resize)
        ResizeThis(modificationOrigin, newPoint);
}

void EdgeMenuDialog::OnChangeTab(int delta)
{
    ChangeTab(delta);
}

void EdgeMenuDialog::InitGui()
{
    //this is just a stub for dialogs that still do not have this function themselves
}

void EdgeMenuDialog::FillGuiElements(BrowserNode *)
{
    //this is just a stub for dialogs that still do not have this function themselves
}

bool EdgeMenuDialog::ContainsUnsavedChanges()
{
    false;
}

void EdgeMenuDialog::SaveData()
{
    //todo implement
}

void EdgeMenuDialog::RejectData()
{
    //todo implement
}

void EdgeMenuDialog::SetCurrentNode(BrowserNode * node)
{
    currentNode = node;
}

BrowserNode * EdgeMenuDialog::GetCurrentNode()
{
    return currentNode;
}

void EdgeMenuDialog::IntitiateMove(QPoint origin)
{
    modificationOrigin = origin;
    dialogOrigin = mapToGlobal(QPoint());
    modificationMode = wmm_drag;
}

void EdgeMenuDialog::InitiateResize(QPoint origin)
{
    modificationOrigin = origin;
    //dialogOrigin = mapToGlobal(QPoint());
    originalSize = size();
    modificationMode = wmm_resize;
}

void EdgeMenuDialog::ResizeThis(QPoint origin, QPoint newPoint)
{
    int newWidth = originalSize.width() + (newPoint.x() - origin.x());
    int newHeight = originalSize.height() + (newPoint.y() - origin.y());
    this->resize(newWidth, newHeight);
}

void EdgeMenuDialog::MoveThis(QPoint origin, QPoint newPoint)
{
    this->move(newPoint - origin + dialogOrigin);
}

void EdgeMenuDialog::ChangeTab(int delta)
{
    currentTab += delta;
    if(currentTab > tabBar()->count())
        currentTab = 0;
    if(currentTab < 0)
        currentTab = tabBar()->count() - 1;
    tabBar()->setCurrentIndex(currentTab);
}
