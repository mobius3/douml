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
#include "browser/BrowserAttribute.h"
#include "AttributeData.h"
#include "BrowserView.h"
#include "AType.h"
#include "UmlEnum.h"
#include "data/ClassData.h"
#include "data/OperationData.h"
#include "GenericDelegate.h"


#include <algorithm>
#include <iostream>
#include <array>
#include <functional>

static const int nameIndex = 0;
static const int typeIndex = 1;
static const int defaultIndex = 2;
static const int stereotypeIndex = 3;
static const int visibilityIndex = 4;
static const int staticIndex = 5;
static const int abstractIndex = 6;
static const int multiplicityIndex = 7;
static const int directionIndex = 8;


static QRect CheckBoxRect(const QStyleOptionViewItem &view_item_style_options) {
  QStyleOptionButton check_box_style_option;
  QRect check_box_rect = QApplication::style()->subElementRect(
      QStyle::SE_CheckBoxIndicator,
      &check_box_style_option);
  QPoint check_box_point(view_item_style_options.rect.x() +
                         view_item_style_options.rect.width() / 2 -
                         check_box_rect.width() / 2,
                         view_item_style_options.rect.y() +
                         view_item_style_options.rect.height() / 2 -
                         check_box_rect.height() / 2);
  return QRect(check_box_point, check_box_rect.size());
}


static bool editorEvent(QEvent *event,
                                   QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index) {
  if ((event->type() == QEvent::MouseButtonRelease) ||
      (event->type() == QEvent::MouseButtonDblClick)) {
    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
    if (mouse_event->button() != Qt::LeftButton ||
        !CheckBoxRect(option).contains(mouse_event->pos())) {
      return false;
    }
    if (event->type() == QEvent::MouseButtonDblClick) {
      return true;
    }
  } else if (event->type() == QEvent::KeyPress) {
    if (static_cast<QKeyEvent*>(event)->key() != Qt::Key_Space &&
        static_cast<QKeyEvent*>(event)->key() != Qt::Key_Select) {
      return false;
    }
  } else {
    return false;
  }

  bool checked = index.model()->data(index, Qt::DisplayRole).toBool();
  model->setData(index, !checked, Qt::DisplayRole);
  return model->setData(index, !checked, Qt::EditRole);
}

QuickEdit::QuickEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuickEdit)
{
    ui->setupUi(this);
    if(!dummyView)
        dummyView = new BrowserView();
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

void QuickEdit::OnShow()
{
    BrowserNode* current = static_cast<BrowserNode*>(originalView->currentItem());
    if(!current)
        return;
    Show(current);
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
    itemCreators.insert(UmlAttribute, std::bind(&QuickEdit::AssignItemsForAttribute, this, std::placeholders::_1, std::placeholders::_2));
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


    TreeItem<BrowserNode>* pointer = new TreeItem<BrowserNode>(0);
    data = QSharedPointer<BrowserNode>(new BrowserNodeDummy(dummyView));
    pointer->SetController(controller);
    pointer->SetInternalData(data.data());
    //controller->SetColumns(QStringList() << "class");
    interface = QSharedPointer<TreeItemInterface >(pointer);
    model->InsertRootItem(interface);

    view->setModel(model);
    view->setContextMenuPolicy(Qt::CustomContextMenu);
    view->setEditTriggers(QAbstractItemView::DoubleClicked);
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


#define ADD_GETSET_DATA(TYPE,DATA_TYPE, HOLDER,ROW,ROLE,CONVERTER,ACCESSOR,SETTER)  \
HOLDER->AddGetter(QPair<int,int>(ROW,ROLE), \
[] (const BrowserNode* data) \
{ \
    if(!data)\
        return QVariant(); \
    const TYPE* pointer = static_cast<const TYPE*>(data);\
    if(pointer) \
        return QVariant(((DATA_TYPE*)pointer->get_data())->ACCESSOR()); \
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
        ((DATA_TYPE*)pointer->get_data())->SETTER(value.CONVERTER()); \
    pointer->modified();\
    return true;\
} \
);

void QuickEdit::SetupClassController(QSharedPointer<ItemController<BrowserNode> > &)
{
    classController = QSharedPointer<ItemController<BrowserNode> >( new ItemController<BrowserNode>());
    classController->SetColumns(QStringList() << "name" <<   "type" <<  "default_value" <<  "stereotype"
                                << "visibility" << "static" <<  "abstract" <<  "multiplicity" <<  "direction"
                                );
    ADD_GETSET(BrowserClass, classController, nameIndex, 0, toString, get_name, set_name);
    ADD_GETSET(BrowserClass, classController, nameIndex, 2, toString, get_name, set_name);

    ADD_GETSET(BrowserClass, classController, stereotypeIndex, 0, toString, get_stereotype, def->set_stereotype);
    ADD_GETSET(BrowserClass, classController, stereotypeIndex, 2, toString, get_stereotype, def->set_stereotype);

    ADD_GETSET(BrowserClass, classController, visibilityIndex, 0, toInt, def->get_uml_visibility, def->set_uml_visibility);
    ADD_GETSET(BrowserClass, classController, visibilityIndex, 2, toInt, def->get_uml_visibility, def->set_uml_visibility);

    ADD_GETSET(BrowserClass, classController, abstractIndex, 0, toBool, def->get_is_abstract, def->set_is_abstract);
    ADD_GETSET(BrowserClass, classController, abstractIndex, 2, toBool, def->get_is_abstract, def->set_is_abstract);


    classController->AddFlagsFunctor
            (
                [](const QModelIndex& index)
    {
        Qt::ItemFlags result;
        result |= Qt::ItemIsSelectable;
        if(!(index.column() *in(nameIndex,stereotypeIndex,visibilityIndex,abstractIndex)))
            return result;

        TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
        if(!iface)
            return result;
        BrowserNode* pointer = static_cast<BrowserNode*>(iface->InternalPointer());
        if(!pointer)
            return result;
        if(pointer->is_writable())
            result |= Qt::ItemIsEditable;
        result |=  Qt::ItemIsEnabled;
        return result;
    }
    );

}

void QuickEdit::SetupOperationController(QSharedPointer<ItemController<BrowserNode> > &)
{
    operationController = QSharedPointer<ItemController<BrowserNode> >( new ItemController<BrowserNode>());
    operationController->SetColumns(QStringList() << "name" <<  "type" <<  "default_value" <<  "stereotype"
                                << "visibility" << "static" <<  "abstract" <<  "multiplicity" <<  "direction"
                                );
    ADD_GETSET(BrowserOperation, operationController, nameIndex, 0, toString, get_name, set_name);
    ADD_GETSET(BrowserOperation, operationController, nameIndex, 2, toString, get_name, set_name);

    ADD_GETSET(BrowserOperationReturnType, operationController, typeIndex, 0, toString,
               get_param_type().get_type, set_param_type);
    ADD_GETSET(BrowserOperationReturnType, operationController, typeIndex, 2, toString,
               get_param_type().get_type, set_param_type);

    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, visibilityIndex, 0, toInt,
               get_cpp_visibility, set_cpp_visibility);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, visibilityIndex, 2, toInt,
               get_cpp_visibility, set_cpp_visibility);

    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, staticIndex, 0, toBool,
                    get_isa_class_operation, set_isa_class_operation);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, staticIndex, 2, toBool,
                    get_isa_class_operation, set_isa_class_operation);

    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, abstractIndex, 0, toBool,
                    get_is_abstract, set_is_abstract);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, abstractIndex, 2, toBool,
                    get_is_abstract, set_is_abstract);


    operationController->AddFlagsFunctor
            (
                [](const QModelIndex& index)
    {
        Qt::ItemFlags result;
        result |= Qt::ItemIsSelectable;
        if(!(index.column() *in(nameIndex,typeIndex,staticIndex,visibilityIndex,abstractIndex)))
            return result;

        TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
        if(!iface)
            return result;
        BrowserNode* pointer = static_cast<BrowserNode*>(iface->InternalPointer());
        if(!pointer)
            return result;
        if(pointer->is_writable())
            result |= Qt::ItemIsEditable;
        result |=  Qt::ItemIsEnabled;
        return result;
    }
    );
}

void QuickEdit::SetupAttributeController(QSharedPointer<ItemController<BrowserNode> > &)
{
    attributeController = QSharedPointer<ItemController<BrowserNode> >( new ItemController<BrowserNode>());
    attributeController->SetColumns(QStringList() << "name" <<  "type" <<  "default_value" <<  "stereotype"
                                << "visibility" << "static" <<  "abstract" <<  "multiplicity" <<  "direction"
                                );
    ADD_GETSET(BrowserAttribute, attributeController, nameIndex, 0, toString, get_name, set_name);
    ADD_GETSET(BrowserAttribute, attributeController, nameIndex, 2, toString, get_name, set_name);

    ADD_GETSET_DATA(BrowserAttribute, AttributeData, attributeController, typeIndex, 0, toString,
                    get_type().get_type, set_type);
    ADD_GETSET_DATA(BrowserAttribute, AttributeData, attributeController, typeIndex, 2, toString,
                    get_type().get_type, set_type);

    ADD_GETSET_DATA(BrowserAttribute, AttributeData, attributeController, defaultIndex, 0, toString,
                    get_init_value, set_init_value);
    ADD_GETSET_DATA(BrowserAttribute, AttributeData, attributeController, defaultIndex, 2, toString,
                    get_init_value, set_init_value);

    ADD_GETSET(BrowserAttribute, attributeController, stereotypeIndex, 0, toString,
               get_stereotype, def->set_stereotype);
    ADD_GETSET(BrowserAttribute, attributeController, stereotypeIndex, 2, toString,
               get_stereotype, def->set_stereotype);

    ADD_GETSET(BrowserAttribute, attributeController, visibilityIndex, 0, toInt, def->get_uml_visibility, def->set_visibility);
    ADD_GETSET(BrowserAttribute, attributeController, visibilityIndex, 2, toInt, def->get_uml_visibility, def->set_visibility);

    ADD_GETSET_DATA(BrowserAttribute, AttributeData, attributeController, staticIndex, 0, toBool,
                    get_isa_class_attribute, set_isa_class_attribute);
    ADD_GETSET_DATA(BrowserAttribute, AttributeData, attributeController, staticIndex, 2, toBool,
                    get_isa_class_attribute, set_isa_class_attribute);


    attributeController->AddFlagsFunctor
            (
                [](const QModelIndex& index)
    {
        Qt::ItemFlags result;
        result |= Qt::ItemIsSelectable;
        if(!(index.column() *in(nameIndex,typeIndex,defaultIndex,stereotypeIndex, visibilityIndex, staticIndex)))
            return result;

        TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
        if(!iface)
            return result;
        BrowserNode* pointer = static_cast<BrowserNode*>(iface->InternalPointer());
        if(!pointer)
            return result;
        if(pointer->is_writable())
            result |= Qt::ItemIsEditable;
        result |=  Qt::ItemIsEnabled ;
        return result;
    }
    );
}

void QuickEdit::SetupOperationAttributeController(QSharedPointer<ItemController<BrowserNode> > &)
{
    operationAttributeController = QSharedPointer<ItemController<BrowserNode> >( new ItemController<BrowserNode>());
    operationAttributeController->SetColumns(QStringList() << "name" <<  "type" <<  "default_value" <<  "stereotype"
                                << "visibility" << "static" <<  "abstract" <<  "multiplicity" <<  "direction"
                                );
    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, nameIndex, 0, toString, get_name, set_name);
    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, nameIndex, 2, toString, get_name, set_name);

    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, typeIndex, 0, toString,
               get_param_type().get_type, set_param_type);
    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, typeIndex, 2, toString,
               get_param_type().get_type, set_param_type);

    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, defaultIndex, 0, toString,
               get_default_value, set_default_value);
    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, defaultIndex, 2, toString,
               get_default_value, set_default_value);

    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, directionIndex, 0, toString,
               get_direction, set_direction);
    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, directionIndex, 2, toString,
               get_direction, set_direction);



    operationAttributeController->AddFlagsFunctor
            (
                [](const QModelIndex& index)
    {
        Qt::ItemFlags result;
        result |= Qt::ItemIsSelectable;
        if(!(index.column() *in(nameIndex,typeIndex,defaultIndex,visibilityIndex)))
            return result;

        TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
        if(!iface)
            return result;
        BrowserNode* pointer = static_cast<BrowserNode*>(iface->InternalPointer());
        if(!pointer)
            return result;
        if(pointer->is_writable())
            result |= Qt::ItemIsEditable;
        result |=  Qt::ItemIsEnabled ;
        return result;
    }
    );
}
void QuickEdit::Init(UmlWindow* window, BrowserView* view)
{
    originalView = view;
    mainWindow = window;
    nullController = QSharedPointer<ItemController<BrowserNode> > (new ItemController<BrowserNode>());
    //validTypes = {UmlAggregation,UmlAggregationByValue,UmlDirectionalAggregation, UmlClass,
//                                        UmlDirectionalAggregationByValue, UmlAttribute, UmlOperation, UmlExtraMember};
    validTypes = {UmlClass, UmlOperation, UmlAttribute};

    SetupItemCreationFuncs();
    qRegisterMetaType<QList<BrowserNode*>>("QList<BrowserNode*>");
    SetupClassController(classController);
    SetupOperationController(operationController);
    SetupAttributeController(attributeController);
    SetupOperationAttributeController(operationAttributeController);
    SetupTreeModel(treeModel,ui->tvEditor,rootInterface,classController,modelRoot);
    ui->tvEditor->setContextMenuPolicy(Qt::CustomContextMenu);

    GenericDelegate* checkboxDelegate = new GenericDelegate(ui->tvEditor);
    checkboxDelegate->widgetCreator = [](QWidget * parent) {return new QCheckBox(parent);};
    checkboxDelegate->dataAccessor = [](QWidget * editor, const QModelIndex & index)
    {
        bool value = index.model()->data(index, Qt::EditRole).toBool();
        QCheckBox *checkboxEdit = static_cast<QCheckBox*>(editor);
        checkboxEdit->setChecked(value);
    };
    checkboxDelegate->dataSetter = [](QWidget * editor,QAbstractItemModel* model, const QModelIndex &index)
    {
        QCheckBox * checkboxEdit = static_cast<QCheckBox*>(editor);
        bool value = checkboxEdit->isChecked();
        model->setData(index, value, Qt::EditRole);
    };
    checkboxDelegate->editorEventProcessor = editorEvent;

    ui->tvEditor->setItemDelegateForColumn(6, checkboxDelegate);
    ui->tvEditor->setItemDelegateForColumn(5, checkboxDelegate);
    //ui->tvEditor->setStyleSheet("QTreeView::item { border-right: 1px solid black }");
    ui->tvEditor->setAlternatingRowColors(true);
    //connect(ui->tvEditor, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(OnContextMenu(QPoint)));
    connect(ui->leSearch, SIGNAL(textChanged(QString)), this, SLOT(OnPerformFiltering(QString)));
}

void QuickEdit::Show(BrowserNode * node)
{
    //first, we need to determine the type of currently selected item
    // if we cannot open window for such node type - do nothing
    rootInterface->removeChildren(0, rootInterface->childCount());
    localNodeHolder.clear();
    if(!node)
        return;
    UmlCode nodeType = node->get_type();
    if(!validTypes.contains(nodeType))
        return;
    //next we need to recursively create items for node
    if(!itemCreators.contains(nodeType))
        return;
    itemCreators[nodeType](rootInterface, node);
    // we then assign items and all is ok
    //rootInterface->AddChildren(items);
    treeModel->InsertRootItem(rootInterface);
    ui->tvEditor->resizeColumnToContents(0);
    ui->tvEditor->resizeColumnToContents(1);
    ui->tvEditor->resizeColumnToContents(2);
    this->show();

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
    //interfaceItem->AddChildren(items);
    root->AddChildren(QList<QSharedPointer<TreeItemInterface> >() << interfaceItem);
}

void QuickEdit::AssignItemsForAttribute(QSharedPointer<TreeItemInterface> root,  BrowserNode * classNode)
{
    QSharedPointer<TreeItemInterface > interfaceItem = CreateInterfaceNode(root, attributeController, classNode);
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
    //items << CreateInterfaceNode(interfaceItem, nullController, returnType.data());

    for(int i(0); i< paramCount; ++i)
    {
        ParamData* data = &((OperationData*)operationNode->get_data())->params[i];
        QSharedPointer<BrowserNode> param(new BrowserOperationAttribute(dummyView,operationNode,data));
        operationNodes << param;
        items << CreateInterfaceNode(interfaceItem, operationAttributeController, param.data());
    }
    interfaceItem->AddChildren(items);
    root->AddChildren(QList<QSharedPointer<TreeItemInterface> >() << interfaceItem);
    localNodeHolder.append(operationNodes);
}
