// *************************************************************************
//
// Copyright 2012-2013 Nikolai Marchenko  .
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

#ifndef EDGEMENUDIALOGQT4_H
#define EDGEMENUDIALOGQT4_H

#include <QWidget>
#include <QMouseEvent>
#include <QList>
#include <QHash>
#include <QMap>
#include <QDialog>
#include "CustomWidgets/MultiPurposeDragArea.h"
#include "CustomWidgets/EdgeMenuToolBar.h"
#include "edgemenudialogbase.h"

unsigned int ClosestEdge(QWidget *, QPoint);

class BrowserNode;

class EdgeMenuDialogQt4 : public QDialog, public EdgeMenuDialogBase
{
    Q_OBJECT
public:
    EdgeMenuDialogQt4(QWidget * parent = 0, Qt::WindowFlags f = 0);
    virtual ~EdgeMenuDialogQt4();


    //! Returns if this dialog already has signal connections to some toolbar
    //! if this function is not used the double(triple...) connections are created
    //! and next/previous slots start beng called multiple times per click
    bool IsConnectedToToolBar();
    //! notifies dialog that connection has been established
    void ConnectionToToolBarEstablished();
    //! notifies dialog that connection has been broken
    void BreakConnectionToToolBar();

protected:

    //! called when user leaves the window
    virtual void leaveEvent(QEvent * event) override;

    //! called when user enters the window
    virtual void enterEvent(QEvent * event) override;

    virtual void closeEvent(QCloseEvent *) override;

    virtual void hideEvent(QHideEvent *) override;

    virtual void moveEvent(QMoveEvent *) override;

    virtual void focusOutEvent(QFocusEvent *) override;

    //! called on window show()
    virtual void showEvent(QShowEvent * event) override;
    //! called when user srolls with mouse wheel


    //! if data contains unsaved changes this shoould pop up to warn the user
    void ShowSaveDataWarning();

    virtual void IntitiateMove(QPoint) override;
    virtual void InitiateResize(QPoint) override;
    virtual void ResizeThis(QPoint, QPoint) override;
    void MoveThis(QPoint, QPoint);

    //! Returns the current node associated with this dialog
    virtual BrowserNode * GetCurrentNode() override;
    //! Assigns a browser node(listview node effectively) to this dialog
    void SetCurrentNode(BrowserNode *);

    // these functions should be pure virtual in the end
    //! Initializes GUI elements
    virtual void InitGui() override;
    //! fills GUI elements with values from a new BrowserNode
    virtual void FillGuiElements(BrowserNode *) override;
    //! Tells if there have been any changes in the data associated with the dialog
    bool ContainsUnsavedChanges();
    //! Called on accept() and saves GUI elements
    virtual bool SaveData() override;
    //! Called on reject() and discards gui data
    virtual void RejectData() override;



    bool isConnectedToToolBar;

    int currentTab;

    QMap<QString, QWidget *> tabs;
    BrowserNode * currentNode;
    EWidgetModificationMode modificationMode;
    QPoint modificationOrigin;
    QPoint dialogOrigin;
    QSize originalSize;



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
};


#endif // EDGEMENUDIALOGQT4_H
