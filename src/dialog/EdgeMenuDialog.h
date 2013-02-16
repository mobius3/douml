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

#ifndef EDGEMENUDIALOG_H
#define EDGEMENUDIALOG_H
#include <Q3TabDialog>
#include <QWidget>
#include <QMouseEvent>
#include <QList>
#include <QHash>
#include <QMap>
#include "CustomWidgets/MultiPurposeDragArea.h"
#include "edgemenudialogbase.h"

unsigned int ClosestEdge(QWidget *, QPoint);
class BrowserNode;

//! class contains some methods that make it possible to change
//! the behaviour of Bruno's dialogs as non-intrusively as possible
class EdgeMenuDialog : public Q3TabDialog, public EdgeMenuDialogBase
{
    Q_OBJECT
public:
    EdgeMenuDialog(QWidget * parent = 0, const char * name = 0, bool modal = false, Qt::WindowFlags f = 0);
    virtual ~EdgeMenuDialog();

protected:

    //! called when user leaves the window
    void leaveEvent(QEvent * event);

    //! called when user enters the window
    void enterEvent(QEvent * event) override;

    void closeEvent(QCloseEvent *) override;

    void hideEvent(QHideEvent *) override;

    void moveEvent(QMoveEvent *) override;

    void focusOutEvent(QFocusEvent *) override;

    //! called on window show()
    void showEvent(QShowEvent * event);
    //! called when user srolls with mouse wheel


    //! registers tab for later use
    //! registered tab can be safely removed from tab dialog and then restored
    virtual void RegisterTab(QString, QWidget *);
    //! hides the tabs
    virtual void HideTab(QString);
    //! shows the tab
    virtual void ShowTab(QString);

    //! sets the node that dialog is in
    //! dialogs that are not writable have slightly different element structure
    virtual void SetDialogMode(bool _isWritable);


    void MoveThis(QPoint, QPoint);
    void ChangeTab(int);

    virtual void IntitiateMove(QPoint);
    virtual void InitiateResize(QPoint);
    virtual void ResizeThis(QPoint, QPoint);

    bool isWritable;


    int currentTab;

    QMap<QString, QWidget *> tabs;

signals:
    void edgeMenuRequested(uint);
    void lostFocus();
    void hideEdgeMenu();
    void repositionMenu(const QPoint &);


public slots:
    virtual void OnPickNextSibling();
    virtual void OnPickPreviousSibling();
    virtual void OnInitiateMove(QPoint);
    virtual void OnInitiateResize(QPoint);
    virtual void OnNewCoordinatesReceived(QPoint);
    virtual void OnChangeTab(int);
};


#endif // EDGEMENUDIALOG_H
