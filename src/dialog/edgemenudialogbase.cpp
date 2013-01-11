#include "edgemenudialogbase.h"
#include "browser/BrowserNode.h"
#include "Logging/QsLog.h"
#include "Factories/EdgeMenuFactory.h"
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

void EdgeMenuDialogBase::SaveData()
{
    // this is reimplemented to do actual work in subclasses
    // but since not all subclasses reimplement this as of now
    // I can't make this pure virtual
    // Therefore, I provide default implementation that does nothing instead
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




