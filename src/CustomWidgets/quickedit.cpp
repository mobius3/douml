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
#include "browser/BrowserRelation.h"
#include "browser/BrowserExtraMember.h"
#include "AttributeData.h"
#include "BrowserView.h"
#include "AType.h"
#include "UmlEnum.h"
#include "data/ClassData.h"
#include "data/OperationData.h"
#include "data/RelationData.h"
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
    itemCreators.insert(UmlAggregation, std::bind(&QuickEdit::AssignItemsForRelation, this, std::placeholders::_1, std::placeholders::_2));
    itemCreators.insert(UmlAggregationByValue, std::bind(&QuickEdit::AssignItemsForRelation, this, std::placeholders::_1, std::placeholders::_2));
    itemCreators.insert(UmlDirectionalAggregation, std::bind(&QuickEdit::AssignItemsForRelation, this, std::placeholders::_1, std::placeholders::_2));
    itemCreators.insert(UmlDirectionalAggregationByValue, std::bind(&QuickEdit::AssignItemsForRelation, this, std::placeholders::_1, std::placeholders::_2));
    itemCreators.insert(UmlExtraMember, std::bind(&QuickEdit::AssignItemsForExtraNode, this, std::placeholders::_1, std::placeholders::_2));
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

void QuickEdit::Init(UmlWindow* window, BrowserView* view)
{
    originalView = view;
    mainWindow = window;
    nullController = QSharedPointer<ItemController<BrowserNode> > (new ItemController<BrowserNode>());
    //validTypes = {UmlAggregation,UmlAggregationByValue,UmlDirectionalAggregation, UmlClass,
    //                                        UmlDirectionalAggregationByValue, UmlAttribute, UmlOperation, UmlExtraMember};
    validTypes = {UmlAggregation,UmlAggregationByValue,UmlDirectionalAggregation, UmlClass,
                  UmlDirectionalAggregationByValue, UmlAttribute, UmlOperation, UmlExtraMember};
    //validTypes = {UmlClass, UmlOperation, UmlAttribute};

    SetupItemCreationFuncs();
    qRegisterMetaType<QList<BrowserNode*>>("QList<BrowserNode*>");
    SetupControllers();
    SetupTreeModel(treeModel,ui->tvEditor,rootInterface,classController,modelRoot);
    ui->tvEditor->setContextMenuPolicy(Qt::CustomContextMenu);
    CheckBoxDelegateSetup();
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
    std::reverse(children.begin(), children.end());
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

void QuickEdit::AssignItemsForAttribute(QSharedPointer<TreeItemInterface> root,  BrowserNode * classNode)
{
    QSharedPointer<TreeItemInterface > interfaceItem = CreateInterfaceNode(root, attributeController, classNode);
    root->AddChildren(QList<QSharedPointer<TreeItemInterface> >() << interfaceItem);
}

void QuickEdit::AssignItemsForRelation(QSharedPointer<TreeItemInterface> root,  BrowserNode * classNode)
{
    QSharedPointer<TreeItemInterface > interfaceItem = CreateInterfaceNode(root, relationController, classNode);
    root->AddChildren(QList<QSharedPointer<TreeItemInterface> >() << interfaceItem);
}

void QuickEdit::AssignItemsForExtraNode(QSharedPointer<TreeItemInterface> root, BrowserNode * extraNode)
{
    QSharedPointer<TreeItemInterface > interfaceItem = CreateInterfaceNode(root, extraNodeController, extraNode);
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


static void paintCheckbox(const QStyledItemDelegate* delegate, QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    QVariant value = index.model()->data(index, Qt::DisplayRole);
    delegate->QStyledItemDelegate::paint(painter, option, index);
    if(!value.isValid())
        return;

    bool checked = index.model()->data(index, Qt::DisplayRole).toBool();

    QStyleOptionButton check_box_style_option;
    check_box_style_option.state |= QStyle::State_Enabled;
    if (checked) {
        check_box_style_option.state |= QStyle::State_On;
    } else {
        check_box_style_option.state |= QStyle::State_Off;
    }
    check_box_style_option.rect = CheckBoxRect(option);

    QApplication::style()->drawControl(QStyle::CE_CheckBox,
                                       &check_box_style_option,
                                       painter);
}
void QuickEdit::CheckBoxDelegateSetup()
{
    GenericDelegate* checkboxDelegate = new GenericDelegate(ui->tvEditor, true);
    checkboxDelegate->widgetCreator = [](QWidget * parent) {return static_cast<QWidget*>(0);};
    checkboxDelegate->paintProcessor = paintCheckbox;
//    checkboxDelegate->dataAccessor = [](QWidget * editor, const QModelIndex & index)
//    {
//        bool value = index.model()->data(index, Qt::EditRole).toBool();
//        QCheckBox *checkboxEdit = static_cast<QCheckBox*>(editor);
//        checkboxEdit->setChecked(value);
//    };
//    checkboxDelegate->dataSetter = [](QWidget * editor,QAbstractItemModel* model, const QModelIndex &index)
//    {
//        QCheckBox * checkboxEdit = static_cast<QCheckBox*>(editor);
//        bool value = checkboxEdit->isChecked();
//        model->setData(index, value, Qt::EditRole);
//    };
    checkboxDelegate->editorEventProcessor = editorEvent;

    ui->tvEditor->setItemDelegateForColumn(staticIndex, checkboxDelegate);
    ui->tvEditor->setItemDelegateForColumn(abstractIndex, checkboxDelegate);
}

void QuickEdit::ComboBoxDelegateSetup()
{

}
