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
#ifndef EDGEMENUDIALOGBASE_H
#define EDGEMENUDIALOGBASE_H
#include "CustomWidgets/MultiPurposeDragArea.h"
class BrowserNode;
class EdgeMenuToolBar;
class EdgeMenuDialogBase
{
public:
    //! return unique TypeId associated with each classs
    //! crc on PRETTY_FUNCTION is basically used to create one
    virtual uint TypeID() = 0;

    //! Returns if this dialog already has signal connections to some toolbar
    //! if this function is not used the double(triple...) connections are created
    //! and next/previous slots start beng called multiple times per click
    bool IsConnectedToToolBar();
    //! notifies dialog that connection has been established
    void ConnectionToToolBarEstablished();
    //! notifies dialog that connection has been broken
    void BreakConnectionToToolBar();

    //! if data contains unsaved changes this shoould pop up to warn the user
    void ShowSaveDataWarning();

    virtual void IntitiateMove(QPoint) = 0;
    virtual void InitiateResize(QPoint) = 0;
    virtual void ResizeThis(QPoint, QPoint) = 0;


    //! Returns the current node associated with this dialog
    virtual BrowserNode * GetCurrentNode();
    //! Assigns a browser node(listview node effectively) to this dialog
    void SetCurrentNode(BrowserNode *);

    // these functions should be pure virtual in the end
    //! Initializes GUI elements
    virtual void InitGui();
    //! fills GUI elements with values from a new BrowserNode
    virtual void FillGuiElements(BrowserNode *);
    //! Tells if there have been any changes in the data associated with the dialog
    bool ContainsUnsavedChanges();
    //! Called on accept() and saves GUI elements
    virtual bool SaveData();
    //! Called on reject() and discards gui data
    virtual void RejectData();
    void PickNextSibling();
    void PickPreviousSibling();
    void SetToolBar(EdgeMenuToolBar*);

    bool isConnectedToToolBar;
    EdgeMenuToolBar* toolbar = 0;
    BrowserNode * currentNode;
    EWidgetModificationMode modificationMode;
    QPoint modificationOrigin;
    QPoint dialogOrigin;
    QSize originalSize;


};
#endif // EDGEMENUDIALOGBASE_H
