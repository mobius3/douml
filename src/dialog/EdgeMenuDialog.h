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

#ifndef EDGEMENUDIALOG_H
#define EDGEMENUDIALOG_H
#include <Q3TabDialog>
#include <QWidget>
#include <QMouseEvent>
#include <QList>
#include <QHash>
#include <QMap>
#include "CustomWidgets/MultiPurposeDragArea.h"

unsigned int ClosestEdge(QWidget*, QPoint);
class BrowserNode;

//! class contains some methods that make it possible to change
//! the behaviour of Bruno's dialogs as non-intrusively as possible
class EdgeMenuDialog : public Q3TabDialog
{
Q_OBJECT
public:
    EdgeMenuDialog(QWidget * parent = 0, const char * name = 0, bool modal = false, Qt::WindowFlags f = 0);
    virtual ~EdgeMenuDialog();


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
    virtual void leaveEvent ( QEvent * event );

    //! called when user enters the window
    virtual void enterEvent ( QEvent * event );

    void moveEvent(QMoveEvent *);

    virtual void focusOutEvent(QFocusEvent *) override;

    //! called on window show()
    void showEvent ( QShowEvent * event );
    //! called when user srolls with mouse wheel
    void wheelEvent ( QWheelEvent * event );

    //! registers tab for later use
    //! registered tab can be safely removed from tab dialog and then restored
    virtual void RegisterTab(QString, QWidget*);
    //! hides the tabs
    virtual void HideTab(QString);
    //! shows the tab
    virtual void ShowTab(QString);

    //! sets the node that dialog is in
    //! dialogs that are not writable have slightly different element structure
    virtual void SetDialogMode(bool _isWritable);

    //! if data contains unsaved changes this shoould pop up to warn the user
    void ShowSaveDataWarning();

    void IntitiateMove(QPoint);
    void InitiateResize(QPoint);
    void ResizeThis(QPoint,QPoint);
    void MoveThis(QPoint,QPoint);
    void ChangeTab(int);


    //! return unique TypeId associated with each classs
    //! crc on PRETTY_FUNCTION is basically used to create one
    virtual uint TypeID() = 0;
    //! Returns the current node associated with this dialog
    virtual BrowserNode * GetCurrentNode();
    //! Assigns a browser node(listview node effectively) to this dialog
    void SetCurrentNode(BrowserNode* );

    // these functions should be pure virtual in the end
    //! Initializes GUI elements
    virtual void InitGui();
    //! fills GUI elements with values from a new BrowserNode
    virtual void FillGuiElements(BrowserNode *);
    //! Tells if there have been any changes in the data associated with the dialog
    bool ContainsUnsavedChanges();
    //! Called on accept() and saves GUI elements
    virtual void SaveData();
    //! Called on reject() and discards gui data
    virtual void RejectData();



    bool isWritable;
    bool isConnectedToToolBar;

    int currentTab;

    QMap<QString, QWidget*> tabs;
    BrowserNode * currentNode;
    EWidgetModificationMode modificationMode;
    QPoint modificationOrigin;
    QPoint dialogOrigin;
    QSize originalSize;



signals:
    void edgeMenuRequested(uint);
    void lostFocus();
    void hideEdgeMenu();
    void repositionMenu(const QPoint&);

public slots:
    virtual void OnPickNextSibling();
    virtual void OnPickPreviousSibling();
    virtual void OnInitiateMove(QPoint);
    virtual void OnInitiateResize(QPoint);
    virtual void OnNewCoordinatesReceived(QPoint);
    virtual void OnChangeTab(int);
};

#endif // EDGEMENUDIALOG_H
