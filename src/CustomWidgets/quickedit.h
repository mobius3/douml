#ifndef QUICKEDIT_H
#define QUICKEDIT_H

#include <QWidget>
#include <QSharedPointer>
#include <QModelIndex>
#include <QMenu>
#include <QStyledItemDelegate>
#include <functional>
#include "Libs/L_UniversalModels/include/ItemController.h"
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

class QuickEdit : public QWidget
{
    Q_OBJECT
    
public:
    explicit QuickEdit(QWidget *parent = 0);
    ~QuickEdit();
    void Init(UmlWindow* window, BrowserView* view);
    void Show(BrowserNode*);
    
private:
    Ui::QuickEdit *ui = nullptr;
    BrowserView* dummyView = nullptr;
    BrowserView* originalView = nullptr;
    UmlWindow* mainWindow = nullptr;
    QScopedPointer<QMenu> contextMenu;
    QList<UmlCode> validTypes;
    QList<QSharedPointer<BrowserNode> > localNodeHolder;
    QHash<UmlCode, std::function<void(QSharedPointer<TreeItemInterface>, BrowserNode*) > > itemCreators;

    // visited treeview
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

    QSharedPointer<TreeItemInterface > classInterface;
    QSharedPointer<TreeItemInterface > operationInterface;
    QSharedPointer<TreeItemInterface > attributeInterface;
    QSharedPointer<TreeItemInterface > operationReturnTypeInterface;
    QSharedPointer<TreeItemInterface> operationAttributeInterface;
    QSharedPointer<TreeItemInterface > relationInterface;
    QSharedPointer<TreeItemInterface > extraNodeInterface;

    std::function<Qt::ItemFlags(const QModelIndex&)> classFlagFunctor;
    std::function<Qt::ItemFlags(const QModelIndex&)> operationFlagFunctor;
    std::function<Qt::ItemFlags(const QModelIndex&)> attributeFlagFunctor;
    std::function<Qt::ItemFlags(const QModelIndex&)> operationReturnTypeFlagFunctor;
    std::function<Qt::ItemFlags(const QModelIndex&)> operationAttributeFlagFunctor;
    std::function<Qt::ItemFlags(const QModelIndex&)> extraNodeFlagFunctor;


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
    void VisibilityDelegateSetup();
    void TypeDelegateSetup();
    void DirectionDelegateSetup();
    void CheckBoxDelegateSetup();
    void SetupItemCreationFuncs();

    QSharedPointer<TreeItemInterface > CreateInterfaceNode(QSharedPointer<TreeItemInterface> root, QSharedPointer<ItemController<BrowserNode> > controller, BrowserNode *node);
    void AssignItemsForOperation(QSharedPointer<TreeItemInterface> root,BrowserNode*);
    void AssignItemsForClass(QSharedPointer<TreeItemInterface> root,BrowserNode*);
    void AssignItemsForAttribute(QSharedPointer<TreeItemInterface> root,BrowserNode*);
    void AssignItemsForRelation(QSharedPointer<TreeItemInterface> root,  BrowserNode * classNode);
    void AssignItemsForExtraNode(QSharedPointer<TreeItemInterface> root,BrowserNode*);
//    void AssignItemsForAggregation(QSharedPointer<TreeItemInterface> root,BrowserNode*);

    public slots:
    void OnContextMenu(QPoint);
    void OnShow();
    //void OnPerformFiltering(QString);

};

#endif // QUICKEDIT_H
