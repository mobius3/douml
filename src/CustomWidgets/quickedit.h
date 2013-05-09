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
class Q3ListViewItem;
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
    void closeEvent(QCloseEvent *) override;

private:
    Ui::QuickEdit *ui = nullptr;
    BrowserView* dummyView = nullptr;
    BrowserView* originalView = nullptr;
    UmlWindow* mainWindow = nullptr;
    QScopedPointer<QMenu> contextMenu;
    QMenu* collapseExpandMenu = nullptr;
    QList<UmlCode> validTypes;
    QList<QSharedPointer<BrowserNode> > localNodeHolder;
    QHash<UmlCode, std::function<void(QSharedPointer<TreeItemInterface>, BrowserNode*) > > itemCreators;

    TreeModel* treeModel = nullptr;
    bool isFiltered = false;
    QStringList expandedNodes;
    QSharedPointer<TreeItemInterface> rootInterface;
    QSharedPointer<BrowserNode> modelRoot;

    QSharedPointer<ItemController<BrowserNode> > nullController;
    QSharedPointer<ItemController<BrowserNode> > classController;
    QSharedPointer<ItemController<BrowserNode> > operationController;
    QSharedPointer<ItemController<BrowserNode> > attributeController;
    QSharedPointer<ItemController<BrowserNode> > operationReturnTypeController;
    QSharedPointer<ItemController<BrowserNode> > operationAttributeController;
    QSharedPointer<ItemController<BrowserNode> > relationController;
    QSharedPointer<ItemController<BrowserNode> > extraNodeController;
    QSharedPointer<ItemController<BrowserNode> > classviewController;
    QSharedPointer<ItemController<BrowserNode> > packageController;

    QSharedPointer<TreeItemInterface > classInterface;
    QSharedPointer<TreeItemInterface > operationInterface;
    QSharedPointer<TreeItemInterface > attributeInterface;
    QSharedPointer<TreeItemInterface > operationReturnTypeInterface;
    QSharedPointer<TreeItemInterface> operationAttributeInterface;
    QSharedPointer<TreeItemInterface > relationInterface;
    QSharedPointer<TreeItemInterface > extraNodeInterface;
    QSharedPointer<TreeItemInterface> classviewInterface;
    QSharedPointer<TreeItemInterface > packageInterface;


    QAction* actBefore = nullptr;
    QAction* actAfter = nullptr;
    QAction* actCollapseExpandSelf = nullptr;
    QAction* actCollapseExpandParent = nullptr;


    QStringList columns;
    //QModelIndex current;
    BrowserNode* currentNode = nullptr;

    void SetupTreeModel(TreeModel*& , QTreeView*,
                        QSharedPointer<TreeItemInterface>&,
                        QSharedPointer<ItemController<BrowserNode> >&,
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
    QList<std::function<bool (TreeItemInterface *)> > CreateCheckList();
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


    QSharedPointer<TreeItemInterface > CreateInterfaceNode(QSharedPointer<TreeItemInterface> root, QSharedPointer<ItemController<BrowserNode> > controller, BrowserNode *node);
    void AssignItemsForOperation(QSharedPointer<TreeItemInterface> root,BrowserNode*);
    void AssignItemsForClass(QSharedPointer<TreeItemInterface> root,BrowserNode*);
    void AssignItemsForAttribute(QSharedPointer<TreeItemInterface> root,BrowserNode*);
    void AssignItemsForRelation(QSharedPointer<TreeItemInterface> root,  BrowserNode *);
    void AssignItemsForExtraNode(QSharedPointer<TreeItemInterface> root,BrowserNode*);
    void AssignItemsForClassView(QSharedPointer<TreeItemInterface> root,BrowserNode*);
    void AssignItemsForPackage(QSharedPointer<TreeItemInterface> root,BrowserNode*);

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
