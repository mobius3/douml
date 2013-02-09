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
#include <QTabBar>
#include "EdgeMenuDialog.h"
#include "browser/BrowserNode.h"
#include "Logging/QsLog.h"
#include "Factories/EdgeMenuFactory.h"
#include "QApplication"
#include "QDesktopWidget"
unsigned int ClosestEdge(QWidget * widget, QPoint position)
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
    minDistance = qMin(distances[0], distances[1]);
    minDistance = qMin(minDistance, distances[2]);
    minDistance = qMin(minDistance, distances[3]);

    auto it = qFind(distances.begin(), distances.end(), minDistance);

    return it - distances.begin();
}

EdgeMenuDialog::EdgeMenuDialog(QWidget * parent, const char * name, bool modal , Qt::WindowFlags f): Q3TabDialog(parent, name, modal, f)
{
    currentTab = 0;
    currentNode = 0;
    isConnectedToToolBar = false;
    An<EdgeMenuFactory> factory;
    QObject::connect(this, SIGNAL(edgeMenuRequested(uint)), factory.getData(), SLOT(OnEdgeMenuRequested(uint)));
}

EdgeMenuDialog::~EdgeMenuDialog()
{}


void EdgeMenuDialog::leaveEvent(QEvent * )
{
    QPoint cursorPosition = mapFromGlobal(QCursor::pos());
    bool isWithinX = cursorPosition.x() > 0 && cursorPosition.x() < size().width();
    bool isWithinY = cursorPosition.y() > 0 && cursorPosition.y() < size().height();
    bool isOutside = !isWithinX || !isWithinY;

    if (isOutside)
        emit edgeMenuRequested(this->TypeID());
}

void EdgeMenuDialog::enterEvent(QEvent * )
{
    QPoint cursorPosition = mapFromGlobal(QCursor::pos());
    bool isWithinX = cursorPosition.x() > 0 && cursorPosition.x() < size().width();
    bool isWithinY = cursorPosition.y() > 0 && cursorPosition.y() < size().height();
    bool isOutside = !isWithinX || !isWithinY;

    if (isOutside)
        emit edgeMenuRequested(this->TypeID());
}

void EdgeMenuDialog::closeEvent(QCloseEvent *)
{
    emit hideEdgeMenu();
}

void EdgeMenuDialog::hideEvent(QHideEvent *)
{
    emit hideEdgeMenu();
}

void EdgeMenuDialog::moveEvent(QMoveEvent * event)
{
    emit repositionMenu(event->pos() - event->oldPos());
}

void EdgeMenuDialog::focusOutEvent(QFocusEvent *)
{
    emit lostFocus();
}

void EdgeMenuDialog::showEvent(QShowEvent * )
{
    An<EdgeMenuFactory> factory;
    int yPos = QCursor::pos().y();
    if((QApplication::desktop()->height() - QCursor::pos().y()) < this->height())
        yPos=(QApplication::desktop()->height() - this->height() - 120);
    this->move(QCursor::pos().x() + 15, yPos);
    factory->SpawnEdgeMenu(this->TypeID(), dynamic_cast<EdgeMenuDialogBase*>(this));
    this->setFocus();
}

void EdgeMenuDialog::RegisterTab(QString name, QWidget * widget)
{
    if (!tabs.contains(name))
        tabs.insert(name, widget);
}

void EdgeMenuDialog::HideTab(QString name)
{
    removePage(tabs[name]);
}

void EdgeMenuDialog::ShowTab(QString name)
{
    addTab(tabs[name], name);
}

void EdgeMenuDialog::SetDialogMode(bool _isWritable)
{
    isWritable = _isWritable;
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

void EdgeMenuDialog::OnChangeTab(int delta)
{
    ChangeTab(delta);
}


void EdgeMenuDialog::ChangeTab(int delta)
{
    currentTab += delta;

    if (currentTab > tabBar()->count())
        currentTab = 0;

    if (currentTab < 0)
        currentTab = tabBar()->count() - 1;

    tabBar()->setCurrentIndex(currentTab);
}

void EdgeMenuDialog::OnPickNextSibling()
{
    PickNextSibling();
}
void EdgeMenuDialog::OnPickPreviousSibling()
{
    PickPreviousSibling();
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
    if (modificationMode == wmm_drag)
        MoveThis(modificationOrigin, newPoint);

    if (modificationMode == wmm_resize)
        ResizeThis(modificationOrigin, newPoint);
}
void EdgeMenuDialog::IntitiateMove(QPoint origin)
{
    modificationOrigin = origin;
    dialogOrigin = mapToGlobal(QPoint(
                                   (frameGeometry().width() - width()) / 2,
                                   -1 * (frameGeometry().height() - height())
                                   ));
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

void EdgeMenuDialog::MoveThis(QPoint origin, QPoint newPoint)
{
    QPoint difference;
    this->move(newPoint - origin + dialogOrigin);

}
