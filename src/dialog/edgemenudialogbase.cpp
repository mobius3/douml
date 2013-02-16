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
#include "edgemenudialogbase.h"
#include "browser/BrowserNode.h"
#include "Logging/QsLog.h"
#include "Factories/EdgeMenuFactory.h"
#include "CustomWidgets/EdgeMenuToolBar.h"
#include "QApplication"
#include "QDesktopWidget"

bool EdgeMenuDialogBase::IsConnectedToToolBar()
{
    return isConnectedToToolBar;
}

void EdgeMenuDialogBase::ConnectionToToolBarEstablished()
{
    isConnectedToToolBar = true;
}

void EdgeMenuDialogBase::BreakConnectionToToolBar()
{
    isConnectedToToolBar = false;
}

void EdgeMenuDialogBase::PickNextSibling()
{
    bool continueSearch = true;
    BrowserNode * nextNode = 0;
    BrowserNode * originalNode = GetCurrentNode();
    BrowserNode * currentNode = originalNode;

    while (continueSearch)
    {
        nextNode = dynamic_cast<BrowserNode *>(currentNode->itemAbove());
        QLOG_INFO() << "CurrentNode is: "<< currentNode->get_name();
        if (!nextNode)
            break;

        QLOG_INFO() << "NEXT: " << nextNode->get_name() << " " << nextNode->depth();


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

void EdgeMenuDialogBase::PickPreviousSibling()
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

void EdgeMenuDialogBase::SetToolBar(EdgeMenuToolBar * newToolbar)
{
    toolbar = newToolbar;
}

void EdgeMenuDialogBase::InitGui()
{
    //this is just a stub for dialogs that still do not have this function themselves
}

void EdgeMenuDialogBase::FillGuiElements(BrowserNode *)
{
    //this is just a stub for dialogs that still do not have this function themselves
}

bool EdgeMenuDialogBase::ContainsUnsavedChanges()
{
    return false;
}

bool EdgeMenuDialogBase::SaveData()
{
    // this is reimplemented to do actual work in subclasses
    // but since not all subclasses reimplement this as of now
    // I can't make this pure virtual
    // Therefore, I provide default implementation that does nothing instead
    return true;
}

void EdgeMenuDialogBase::RejectData()
{
}

void EdgeMenuDialogBase::SetCurrentNode(BrowserNode * node)
{
    currentNode = node;
}

BrowserNode * EdgeMenuDialogBase::GetCurrentNode()
{
    return currentNode;
}




