
// *************************************************************************
//
// Copyright 2012-2013 Nikolai Marchenko.
//
// This file is part of the Douml Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License Version 3.0 as published by
// the Free Software Foundation and appearing in the file LICENSE.GPL included in the
//  packaging of this file.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License Version 3.0 for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// e-mail : doumleditor@gmail.com
//
// *************************************************************************
#include "edgemenudialogqt4.h"
#include "browser/BrowserNode.h"
#include "Logging/QsLog.h"
#include "Factories/EdgeMenuFactory.h"
#include "QApplication"
#include "QDesktopWidget"


EdgeMenuDialogQt4::EdgeMenuDialogQt4(QWidget * parent, Qt::WindowFlags f): QDialog(parent, f)
{
    currentTab = 0;
    currentNode = 0;
    isConnectedToToolBar = false;
    An<EdgeMenuFactory> factory;
    QObject::connect(this, SIGNAL(edgeMenuRequested(uint)), factory.getData(), SLOT(OnEdgeMenuRequested(uint)));
}

EdgeMenuDialogQt4::~EdgeMenuDialogQt4()
{}

bool EdgeMenuDialogQt4::IsConnectedToToolBar()
{
    return isConnectedToToolBar;
}

void EdgeMenuDialogQt4::ConnectionToToolBarEstablished()
{
    isConnectedToToolBar = true;
}

void EdgeMenuDialogQt4::BreakConnectionToToolBar()
{
    isConnectedToToolBar = false;
}

void EdgeMenuDialogQt4::leaveEvent(QEvent * )
{
    QPoint cursorPosition = mapFromGlobal(QCursor::pos());
    bool isWithinX = cursorPosition.x() > 0 && cursorPosition.x() < size().width();
    bool isWithinY = cursorPosition.y() > 0 && cursorPosition.y() < size().height();
    bool isOutside = !isWithinX || !isWithinY;

    if (isOutside)
        emit edgeMenuRequested(this->TypeID());
}

void EdgeMenuDialogQt4::enterEvent(QEvent * )
{
    QPoint cursorPosition = mapFromGlobal(QCursor::pos());
    bool isWithinX = cursorPosition.x() > 0 && cursorPosition.x() < size().width();
    bool isWithinY = cursorPosition.y() > 0 && cursorPosition.y() < size().height();
    bool isOutside = !isWithinX || !isWithinY;

    if (isOutside)
        emit edgeMenuRequested(this->TypeID());
}

void EdgeMenuDialogQt4::closeEvent(QCloseEvent *)
{
    emit hideEdgeMenu();
}

void EdgeMenuDialogQt4::hideEvent(QHideEvent *)
{
    emit hideEdgeMenu();
}

void EdgeMenuDialogQt4::moveEvent(QMoveEvent * event)
{
    emit repositionMenu(event->pos() - event->oldPos());
}

void EdgeMenuDialogQt4::focusOutEvent(QFocusEvent *)
{
    emit lostFocus();
}

void EdgeMenuDialogQt4::showEvent(QShowEvent * )
{
    An<EdgeMenuFactory> factory;
    int yPos = QCursor::pos().y();
    if((QApplication::desktop()->height() - QCursor::pos().y()) < this->height())
        yPos=(QApplication::desktop()->height() - this->height() - 120);
    this->move(QCursor::pos().x() + 15, yPos);
    //factory->SpawnEdgeMenu(this->TypeID(), this, QCursor::pos());
    factory->SpawnEdgeMenu(this->TypeID(), dynamic_cast<EdgeMenuDialogBase*>(this));
    this->setFocus();
}


void EdgeMenuDialogQt4::OnPickNextSibling()
{
    bool continueSearch = true;
    BrowserNode * nextNode = 0;
    BrowserNode * originalNode = GetCurrentNode();
    BrowserNode * currentNode = originalNode;

    while (continueSearch)
    {
        nextNode = dynamic_cast<BrowserNode *>(currentNode->itemAbove());
        QLOG_INFO() << "CurrentNode is: "<< currentNode->get_name();

        QLOG_INFO() << "NEXT: " << nextNode->get_name() << " " << nextNode->depth();
        if (!nextNode)
            break;

        QLOG_INFO() << "NextNode is: "<< nextNode->get_name();
        bool sameLevel = originalNode->depth() == nextNode->depth();

        bool sameType = originalNode->get_stype() == nextNode->get_stype();

        QLOG_INFO() << originalNode->get_stype();
        QLOG_INFO() << nextNode->get_stype();
        //        QLOG_INFO() << "NEXT: " << "Origin level : " << originalNode->depth();
        //        QLOG_INFO() << "NEXT: " << "Current level : " << nextNode->depth();
        if (sameLevel && sameType)
            continueSearch = false;

        currentNode = nextNode;
    }

    if (nextNode == 0)
        return;

    SaveData();
    FillGuiElements(nextNode);
}

void EdgeMenuDialogQt4::OnPickPreviousSibling()
{
    bool continueSearch = true;
    BrowserNode * previousNode = 0;
    BrowserNode * originalNode = GetCurrentNode();
    int originalDepth = originalNode->depth();
    BrowserNode * currentNode = originalNode;

    while (continueSearch)
    {
        QLOG_INFO() << "CurrentNode is: " << currentNode->get_name();
        previousNode = dynamic_cast<BrowserNode *>(currentNode->itemBelow());

        QLOG_INFO() << "Nodename is: " << previousNode->get_name() << " " << previousNode->depth();
        if (!previousNode)
            break;

        QLOG_INFO() << "Previous Node is: "<< previousNode->get_name();
        int previousDepth = previousNode->depth();
        bool sameType = originalNode->get_stype() == previousNode->get_stype();
        QLOG_INFO() << "PREVIOUS: " << "Origin level : " << originalDepth;
        QLOG_INFO() << "PREVIOUS: " << "Current level : " << previousDepth;
        bool sameLevel = originalDepth == previousDepth;

        if (sameLevel && sameType)
            continueSearch = false;

        currentNode = previousNode;
    }

    if (previousNode == 0)
        return;

    SaveData();
    FillGuiElements(previousNode);
}

void EdgeMenuDialogQt4::OnInitiateMove(QPoint origin)
{
    IntitiateMove(origin);
}

void EdgeMenuDialogQt4::OnInitiateResize(QPoint origin)
{
    InitiateResize(origin);
}

void EdgeMenuDialogQt4::OnNewCoordinatesReceived(QPoint newPoint)
{
    if (modificationMode == wmm_drag)
        MoveThis(modificationOrigin, newPoint);

    if (modificationMode == wmm_resize)
        ResizeThis(modificationOrigin, newPoint);
}


void EdgeMenuDialogQt4::InitGui()
{
    //this is just a stub for dialogs that still do not have this function themselves
}

void EdgeMenuDialogQt4::FillGuiElements(BrowserNode *)
{
    //this is just a stub for dialogs that still do not have this function themselves
}

bool EdgeMenuDialogQt4::ContainsUnsavedChanges()
{
    return false;
}

bool EdgeMenuDialogQt4::SaveData()
{
    // this is reimplemented to do actual work in subclasses
    // but since not all subclasses reimplement this as of now
    // I can't make this pure virtual
    // Therefore, I provide default implementation that does nothing instead
    return true;
}

void EdgeMenuDialogQt4::RejectData()
{
}

void EdgeMenuDialogQt4::SetCurrentNode(BrowserNode * node)
{
    currentNode = node;
}

BrowserNode * EdgeMenuDialogQt4::GetCurrentNode()
{
    return currentNode;
}

void EdgeMenuDialogQt4::IntitiateMove(QPoint origin)
{
    modificationOrigin = origin;
    dialogOrigin = mapToGlobal(QPoint(
                                   (frameGeometry().width() - width()) / 2,
                                   -1 * (frameGeometry().height() - height())
                                   ));
    modificationMode = wmm_drag;
}

void EdgeMenuDialogQt4::InitiateResize(QPoint origin)
{
    modificationOrigin = origin;
    //dialogOrigin = mapToGlobal(QPoint());
    originalSize = size();
    modificationMode = wmm_resize;
}

void EdgeMenuDialogQt4::ResizeThis(QPoint origin, QPoint newPoint)
{
    int newWidth;

    if (origin.x() > newPoint.x())
    {
        newWidth = originalSize.width() + (origin.x() - newPoint.x());
        this->move(origin.x() - 1 * (origin.x() - newPoint.x()), origin.y());
    }
    else
        newWidth = originalSize.width() + (newPoint.x() - origin.x());

    int newHeight = originalSize.height() + (newPoint.y() - origin.y());
    this->resize(newWidth, newHeight);
}

void EdgeMenuDialogQt4::MoveThis(QPoint origin, QPoint newPoint)
{
    QPoint difference;
    this->move(newPoint - origin + dialogOrigin);

}


