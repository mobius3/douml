// *************************************************************************
//
//
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

#ifndef QUICKEDIT_H
#define QUICKEDIT_H

#include <QWidget>
#include <QHash>
#include <functional>
#include "UmlEnum.h"

namespace Ui {
class QuickEdit;
}
class BrowserView;
class TreeModel;
class BrowserNode;
class TreeItemInterface;
class QTreeView;
class QListWidgetItem;
class GenericEventFilter;
class UmlWindow;
class QMenu;
class QModelIndex;
template <typename T>
class ItemController;

template <typename T>
class QSharedPointer;
template <typename T, typename K>
class QHash;


class QuickEdit : public QWidget
{
    Q_OBJECT
    
public:
    explicit QuickEdit(QWidget *parent = 0);
    ~QuickEdit();
    void Init(UmlWindow* window, BrowserView* view);
    void Show(BrowserNode*);
    bool ValidType(BrowserNode*);
protected:
    virtual void closeEvent(QCloseEvent *) override;

private:
    Ui::QuickEdit *ui = nullptr;
    BrowserView* dummyView = nullptr;
    BrowserView* originalView = nullptr;
    UmlWindow* mainWindow = nullptr;
    QScopedPointer<QMenu> contextMenu;
    QMenu* collapseExpandMenu = nullptr;
    QList<UmlCode> validTypes;

    QList<QSharedPointer<BrowserNode> > localNodeHolder;
    QHash<UmlCode, std::function<void(QSharedPointer<TreeItemInterface>, BrowserNode*)>> itemCreators;
    TreeModel* treeModel = nullptr;
    bool isFiltered = false;
    QStringList expandedNodes;
    QSharedPointer<TreeItemInterface> rootInterface;
    QSharedPointer<BrowserNode> modelRoot;

    QSharedPointer<ItemController<BrowserNode>> nullController;
    QSharedPointer<ItemController<BrowserNode>> classController;
    QSharedPointer<ItemController<BrowserNode>> operationController;
    QSharedPointer<ItemController<BrowserNode>> attributeController;
    QSharedPointer<ItemController<BrowserNode>> operationAttributeController;
    QSharedPointer<ItemController<BrowserNode>> relationController;
    QSharedPointer<ItemController<BrowserNode>> extraNodeController;

    QAction* actBefore = nullptr;
    QAction* actAfter = nullptr;
    QAction* actCollapseExpandSelf = nullptr;
    QAction* actCollapseExpandParent = nullptr;


    QStringList columns;
    //QModelIndex current;
    BrowserNode* currentNode = nullptr;

    void SetupTreeModel(TreeModel*&,
                        QTreeView*,
                        QSharedPointer<TreeItemInterface>&,
                        QSharedPointer<ItemController<BrowserNode>>&,
                        QSharedPointer<BrowserNode>&);

    void SetupClassController();
    void SetupOperationController();
    void SetupAttributeController();
    void SetupOperationAttributeController();
    void SetupRelationController();
    void SetupExtraNodeController();
    void SetupControllers();
    void SetupDelegates();
    void PerformFiltering(QStringList, QTreeView*, TreeModel*, QSharedPointer<TreeItemInterface>);
    QList<std::function<bool(TreeItemInterface*)>> CreateCheckList();
    void CreateMenu();
    void SetupMenu(TreeItemInterface *);
    void VisibilityDelegateSetup();
    void TypeDelegateSetup();
    void DirectionDelegateSetup();
    void CheckBoxDelegateSetup();
    void PrefixDelegateSetup();
    void PostfixDelegateSetup();
    void SetupItemCreationFuncs();
    void CheckColumnVisibility();

    void AddParameter();
    void AddOperation();
    void AddAttribute();

    void RefreshTable();
    void CollapseExpand(const QModelIndex& index );


    BrowserNode* GetCurrentNode();
    QSharedPointer<TreeItemInterface> GetSharedOfOperation(const QModelIndex& );

    QSharedPointer<TreeItemInterface> CreateInterfaceNode(QSharedPointer<TreeItemInterface> root,
                                                          QSharedPointer<ItemController<BrowserNode>> controller,
                                                          BrowserNode* node);

    void AssignItemsForOperation(QSharedPointer<TreeItemInterface> root, BrowserNode*);
    void AssignItemsForClass(QSharedPointer<TreeItemInterface> root, BrowserNode*);
    void AssignItemsForAttribute(QSharedPointer<TreeItemInterface> root, BrowserNode*);
    void AssignItemsForRelation(QSharedPointer<TreeItemInterface> root, BrowserNode *);
    void AssignItemsForExtraNode(QSharedPointer<TreeItemInterface> root, BrowserNode*);
    void AssignItemsForClassView(QSharedPointer<TreeItemInterface> root, BrowserNode*);
    void AssignItemsForPackage(QSharedPointer<TreeItemInterface> root, BrowserNode*);

    void MoveMarked(bool);

public slots:
    void OnContextMenu(QPoint);
    void OnShow();
    void OnAddParameter();
    void OnAddOperation();
    void OnAddAttribute();
    void OnPerformFiltering(QString);
    void OnDecreaseOpenLevels();
    void OnIncreaseOpenLevels();
    void OnChangeColumnVisibility();
    void OnMoveMarkedAfter();
    void OnMoveMarkedBefore();
    void OnRefreshTable();
    void OnCollapseExpandSelf();
    void OnCollapseExpandParent();
};

#endif // QUICKEDIT_H
