#include "quickedit.h"
#include "ui_quickedit.h"

#include "Libs/L_UniversalModels/include/TreeModel.h"
#include "Libs/L_UniversalModels/include/TreeItemInterface.h"
#include "Libs/L_UniversalModels/include/treeviewfunctions.h"
#include "Libs/L_UniversalModels/include/treeviewtemplatefunctions.h"
#include "Libs/L_UniversalModels/include/TreeItem.h"
#include "Libs/L_UniversalModels/include/genericeventfilter.h"
#include "browser/BrowserClass.h"
#include "browser/BrowserOperationAttribute.h"
#include "browser/BrowserNodeDummy.h"
#include "BrowserView.h"
#include "UmlEnum.h"
#include "data/ClassData.h"
#include "data/OperationData.h"


#include <algorithm>
#include <iostream>
#include <array>
#include <functional>



QuickEdit::QuickEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuickEdit)
{
    ui->setupUi(this);
}

QuickEdit::~QuickEdit()
{
    delete ui;
}


void QuickEdit::PerformFiltering(QStringList expandedNodes, QTreeView* view, TreeModel* model, QSharedPointer<TreeItemInterface > interface)
{
    std::function<QVariant(BrowserNode*)> dataAccessFunc =
            [](BrowserNode* data){return QVariant(data->get_name());};

    std::function<QList<std::function<bool (TreeItemInterface *)> > ()> checksFunc =
            std::bind(&QuickEdit::CreateCheckList, this);

    TreeFunctions::FilterTreeAndRestoreNodes<TreeItemInterface, TreeItem, BrowserNode>
            (dataAccessFunc, checksFunc,
                     expandedNodes, view, model, interface);
}

void QuickEdit::OnContextMenu(QPoint point)
{
    CreateMenu();
    contextMenu->popup(ui->tvEditor->mapToGlobal(point));
}


void QuickEdit::CreateMenu()
{
    if(contextMenu.isNull())
    {
        contextMenu.reset(new QMenu());
        contextMenu->addAction(tr("Remove from favourites"), this, SLOT(OnRemoveCurrentItemFromFavourites()));
    }
}

void QuickEdit::SetupItemCreationFuncs()
{
//    itemCreators.insert(UmlAggregation, std::bind(CreateItemsForAggregation, this, std::placeholders::_1, std::placeholders::_2));
//    itemCreators.insert(UmlAggregationByValue, std::bind(CreateItemsForAggregation, this, std::placeholders::_1, std::placeholders::_2));/*composition?*/
//    itemCreators.insert(UmlDirectionalAggregation, std::bind(CreateItemsForAggregation, this, std::placeholders::_1, std::placeholders::_2));
//    itemCreators.insert(UmlDirectionalAggregationByValue, std::bind(CreateItemsForAggregation, this, std::placeholders::_1, std::placeholders::_2));
    //void QuickEdit::AssignItemsForClass(QSharedPointer<TreeItemInterface> root,  BrowserNode * classNode)

    //std::function<>
    itemCreators.insert(UmlClass, std::bind(&QuickEdit::AssignItemsForClass, this, std::placeholders::_1, std::placeholders::_2));
    //itemCreators.insert(UmlAttribute, std::bind(CreateItemsForAttribute, this, std::placeholders::_1, std::placeholders::_2));
    itemCreators.insert(UmlOperation, std::bind(&QuickEdit::AssignItemsForOperation, this, std::placeholders::_1, std::placeholders::_2));
    //itemCreators.insert(UmlExtraMember, std::bind(CreateItemsForExternal, this, std::placeholders::_1, std::placeholders::_2));
}

QList<std::function<bool (TreeItemInterface *)> > QuickEdit::CreateCheckList()
{
//    QList<std::function<bool (TreeItemInterface *)> > result;
//    if(!ui->leVisitedSearch->text().trimmed().isEmpty())
//    {
//        QString value = ui->leVisitedSearch->text();
//        std::function<bool(TreeItemInterface*)> addressFilterFunc =  [value](TreeItemInterface* iface)
//        {
//            BrowserNode* data = static_cast<BrowserNode*>(iface->InternalPointer());
//            bool match = data->get_name().contains(value, Qt::CaseInsensitive);
//            return match;
//        };
//        result.append(addressFilterFunc);
//    }
//    return result;
}

void QuickEdit::SetupTreeModel(TreeModel*& model , QTreeView* view,
                               QSharedPointer<TreeItemInterface> &interface,
                               QSharedPointer<ItemController<BrowserNode> > &controller,
                               QSharedPointer<BrowserNode> &data)
{
    model = new TreeModel();
    SetupClassController(controller);

    TreeItem<BrowserNode>* pointer = new TreeItem<BrowserNode>(0);
    data = QSharedPointer<BrowserNode>(new BrowserNodeDummy(dummyView));
    pointer->SetController(controller);
    pointer->SetInternalData(data.data());
    controller->SetColumns(QStringList() << "class");
    interface = QSharedPointer<TreeItemInterface >(pointer);
    model->InsertRootItem(interface);

    view->setModel(model);
    view->setContextMenuPolicy(Qt::CustomContextMenu);
    view->setEditTriggers(QAbstractItemView::AllEditTriggers);
    view->setColumnWidth(0, 230);
    view->setExpandsOnDoubleClick(false);
    view->setRootIsDecorated(true);
}

#define ADD_GETSET(TYPE,HOLDER,ROW,ROLE,CONVERTER,ACCESSOR,SETTER)  \
HOLDER->AddGetter(QPair<int,int>(ROW,ROLE), \
[] (const BrowserNode* data) \
{ \
    if(!data)\
        return QVariant(); \
    const TYPE* pointer = static_cast<const TYPE*>(data);\
    if(pointer) \
        return QVariant(pointer->ACCESSOR()); \
    else \
        return QVariant(); \
} \
); \
HOLDER->AddSetter(QPair<int,int>(ROW,ROLE), \
[] (BrowserNode* data, QVariant value) \
{ \
    if(!data)\
        return false; \
    TYPE* pointer = static_cast<TYPE*>(data);\
    if(pointer) \
        pointer->SETTER(value.CONVERTER()); \
    pointer->modified();\
    return true;\
} \
);


// some really insane code from stackoverflow that allows to shorten lengthy ifs
template <typename T0, typename T1, std::size_t N>
bool operator *(const T0& lhs, const std::array<T1, N>& rhs) {
  return std::find(begin(rhs), end(rhs), lhs) != end(rhs);
}

template<class T0, class...T> std::array<T0, 1+sizeof...(T)> in(T0 arg0, T...args) {
  return {{arg0, args...}};
}

void QuickEdit::SetupClassController(QSharedPointer<ItemController<BrowserNode> > &)
{
    ADD_GETSET(BrowserClass, classController, 1, 0, toString, get_name, set_name);
    ADD_GETSET(BrowserClass, classController, 1, 2, toString, get_name, set_name);

    ADD_GETSET(BrowserClass, classController, 4, 0, toString, get_stereotype, def->set_stereotype);
    ADD_GETSET(BrowserClass, classController, 4, 2, toString, get_stereotype, def->set_stereotype);

    ADD_GETSET(BrowserClass, classController, 5, 0, toInt, def->get_uml_visibility, def->set_uml_visibility);
    ADD_GETSET(BrowserClass, classController, 5, 2, toInt, def->get_uml_visibility, def->set_uml_visibility);

    ADD_GETSET(BrowserClass, classController, 6, 0, toBool, def->get_is_abstract, def->set_is_abstract);
    ADD_GETSET(BrowserClass, classController, 6, 2, toBool, def->get_is_abstract, def->set_is_abstract);


    classController->AddFlagsFunctor
            (
                [](const QModelIndex& index)
    {
        Qt::ItemFlags result;
        if(!(index.column() *in(1,4,5,6)))
            return result;

        TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
        if(!iface)
            return result;
        BrowserNode* pointer = static_cast<BrowserNode*>(iface->InternalPointer());
        if(!pointer)
            return result;
        if(pointer->is_writable())
            result |= Qt::ItemIsEditable;
        result |=  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        return result;
    }
    );

}

void QuickEdit::SetupOperationController(QSharedPointer<ItemController<BrowserNode> > &)
{
}

void QuickEdit::SetupAttributeController(QSharedPointer<ItemController<BrowserNode> > &)
{
}

void QuickEdit::SetupOperationAttributeController(QSharedPointer<ItemController<BrowserNode> > &)
{
}

void QuickEdit::SetupOperationReturnTypeController(QSharedPointer<ItemController<BrowserNode> > &)
{
}

void QuickEdit::Init(UmlWindow* window, BrowserView* view)
{
    originalView = view;
    mainWindow = window;
    validTypes = {UmlAggregation,UmlAggregationByValue,UmlDirectionalAggregation, UmlClass,
                                        UmlDirectionalAggregationByValue, UmlAttribute, UmlOperation, UmlExtraMember};
    SetupItemCreationFuncs();
    qRegisterMetaType<QList<BrowserNode*>>("QList<BrowserNode*>");
    SetupTreeModel(treeModel,ui->tvEditor,rootInterface,classController,modelRoot);
    ui->tvEditor->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tvEditor, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(OnContextMenu(QPoint)));
    connect(ui->leSearch, SIGNAL(textChanged(QString)), this, SLOT(OnPerformFiltering(QString)));
}

void QuickEdit::Show(BrowserNode * node)
{
    //first, we need to determine the type of currently selected item
    // if we cannot open window for such node type - do nothing
    if(!node)
        return;
    UmlCode nodeType = node->get_type();
    if(!validTypes.contains(nodeType))
        return;
    //next we need to recursively create items for node
    if(!itemCreators.contains(nodeType))
        return;
    QList<TreeItemInterface> items;
    itemCreators[nodeType](rootInterface, node);
    // we then assign items and all is ok
    //rootInterface->AddChildren(items);
    treeModel->InsertRootItem(rootInterface);

}

QSharedPointer<TreeItemInterface> QuickEdit::CreateInterfaceNode(QSharedPointer<TreeItemInterface> root,
                                                               QSharedPointer<ItemController<BrowserNode> > controller, BrowserNode * node )
{
    TreeItem<BrowserNode>* pointer = new TreeItem<BrowserNode>(0);
    QSharedPointer<TreeItemInterface > interfaceItem(pointer);
    pointer->SetController(controller);
    pointer->SetInternalData(node);
    pointer->SetParent(root);
    return interfaceItem;
}


void QuickEdit::AssignItemsForClass(QSharedPointer<TreeItemInterface> root,  BrowserNode * classNode)
{

    QSharedPointer<TreeItemInterface > interfaceItem = CreateInterfaceNode(root, classController, classNode);

    QList<BrowserNode*> children = classNode->children(validTypes);
    QList<TreeItemInterface> items;
    for(BrowserNode* child : children)
    {
        if(!child)
            continue;
        UmlCode nodeType = child->get_type();
        itemCreators[nodeType](interfaceItem, child);
    }
    root->AddChildren(QList<QSharedPointer<TreeItemInterface> >() << interfaceItem);
}

void QuickEdit::AssignItemsForOperation(QSharedPointer<TreeItemInterface> root, BrowserNode * node)
{
    QList<QSharedPointer<TreeItemInterface>> items;

    QSharedPointer<TreeItemInterface > interfaceItem = CreateInterfaceNode(root, operationController, node);
    BrowserOperation* operationNode = static_cast<BrowserOperation*>(node);
    // first we make a dummy node for return type
    QSharedPointer<BrowserNode> returnType(new BrowserOperationReturnType(dummyView, operationNode));
    QList<QSharedPointer<BrowserNode> > operationNodes;
    operationNodes << returnType;
    // next we make dummy nodes for all attributes
    int paramCount = ((OperationData*)operationNode->get_data())->nparams;
    items << CreateInterfaceNode(root, operationReturnTypeController, returnType.data());

    for(int i(0); i< paramCount; ++i)
    {
        ParamData* data = &((OperationData*)operationNode->get_data())->params[i];
        QSharedPointer<BrowserNode> param(new BrowserOperationAttribute(dummyView,operationNode,data));
        operationNodes << param;
        items << CreateInterfaceNode(root, operationAttributeController, param.data());
    }
    interfaceItem->AddChildren(items);
    root->AddChildren(QList<QSharedPointer<TreeItemInterface> >() << interfaceItem);
}
