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

#include "quickedit.h"
#include "ui_quickedit.h"

#include "Libs/L_UniversalModels/include/TreeModel.h"
#include "Libs/L_UniversalModels/include/TreeItemInterface.h"
#include "Libs/L_UniversalModels/include/treeviewfunctions.h"
#include "Libs/L_UniversalModels/include/treeviewtemplatefunctions.h"
#include "Libs/L_UniversalModels/include/TreeItem.h"
#include "Libs/L_UniversalModels/include/genericeventfilter.h"
#include "Libs/L_UniversalModels/include/ItemController.h"

#include "browser/BrowserClass.h"
#include "browser/BrowserOperationAttribute.h"
#include "browser/BrowserNodeDummy.h"
#include "browser/BrowserAttribute.h"
#include "browser/BrowserRelation.h"
#include "browser/BrowserOperationAttribute.h"
#include "browserfunctions/operationfuncs.h"
#include "browser/BrowserExtraMember.h"
#include "tool/snippets.h"
#include "GenerationSettings.h"
#include "AttributeData.h"
#include "BrowserView.h"
#include "AType.h"
#include "UmlEnum.h"
#include "data/ClassData.h"

#include "data/OperationData.h"
#include "data/RelationData.h"
#include "GenericDelegate.h"
#include <QStyledItemDelegate>

#include <QCompleter>
#include <QStringListModel>
#include <QSettings>
#include <QHeaderView>
#include <algorithm>
#include <iostream>
#include <array>
#include <functional>
#include <QMenu>
#include <QMouseEvent>
#include <QTextCodec>

namespace TreeFunctions {


}

using namespace TreeFunctions;

static QRect CheckBoxRect(const QStyleOptionViewItem &view_item_style_options)
{
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
                        const QModelIndex &index)
{
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
#ifdef __sil__
    this->setToolTip("QuickEdit");
#endif
    this->setWindowTitle(QObject::tr("Quick Edit"));
    if(!dummyView)
        dummyView = new BrowserView();
}

QuickEdit::~QuickEdit()
{
    delete ui;
}

void QuickEdit::PerformFiltering(QStringList expandedNodes, QTreeView* view, TreeModel* model, QSharedPointer<TreeItemInterface> interface)
{
    FilterTreeAndRestoreNodes<TreeItemInterface, TreeItem, BrowserNode>(
        [](BrowserNode* data) { return QVariant(data->get_name()); },
        bind(&QuickEdit::CreateCheckList, this),
        expandedNodes,
        view,
        model,
        interface,
        false,
        true);
}

void QuickEdit::OnContextMenu(QPoint point)
{
    QModelIndex current = ui->tvEditor->selectionModel()->currentIndex();
    if (!current.isValid())
        return;

    current = current.sibling(current.row(), 0);
    TreeItemInterface* itemAsInterface = static_cast<TreeItemInterface*>(current.internalPointer());
    BrowserNode* currentNode = static_cast<BrowserNode*>(itemAsInterface->InternalPointer());
    if (!itemAsInterface)
        return;

    CreateMenu();
    SetupMenu(itemAsInterface);
    if (currentNode->TypeID() != TypeIdentifier<BrowserOperationAttribute>::id())
    {
        contextMenu->removeAction(actBefore);
        contextMenu->removeAction(actAfter);
    }

    contextMenu->popup(ui->tvEditor->mapToGlobal(point));
}

void QuickEdit::OnShow()
{
    currentNode = static_cast<BrowserNode*>(originalView->currentItem());
    if (!currentNode)
        return;
    Show(currentNode);
}

void QuickEdit::OnAddParameter()
{
    AddParameter();
}

void QuickEdit::OnAddOperation()
{
    AddOperation();
}

void QuickEdit::OnAddAttribute()
{
    AddAttribute();
}

void QuickEdit::OnPerformFiltering(QString)
{
    PerformFiltering(expandedNodes, ui->tvEditor, treeModel, rootInterface);

    // expand all items
    ExpandAllSatisfying<TreeItemInterface>([](TreeItemInterface*) { return true; },
                                           ui->tvEditor,
                                           treeModel,
                                           QModelIndex());
}

void QuickEdit::OnDecreaseOpenLevels()
{
    int level = MaxOpenLevel(ui->tvEditor, treeModel, QModelIndex());
    level--;
    ExpandUpToLevel(ui->tvEditor, treeModel, QModelIndex(), level);
}

void QuickEdit::OnIncreaseOpenLevels()
{
    int level = MaxOpenLevel(ui->tvEditor, treeModel, QModelIndex());
    level++;
    ExpandUpToLevel(ui->tvEditor, treeModel, QModelIndex(), level);
}

void QuickEdit::OnChangeColumnVisibility()
{
    CheckColumnVisibility();
}

void QuickEdit::OnMoveMarkedAfter()
{
    MoveMarked(false);
}

void QuickEdit::OnMoveMarkedBefore()
{
    MoveMarked(true);
}

void QuickEdit::OnRefreshTable()
{
    RefreshTable();
}

void QuickEdit::OnCollapseExpandSelf()
{
    QModelIndex index = ui->tvEditor->currentIndex();
    if (index.isValid())
        CollapseExpand(index.sibling(index.row(), 0));
}

void QuickEdit::OnCollapseExpandParent()
{
    QModelIndex index = ui->tvEditor->currentIndex();
    index = index.parent();
    if (index.isValid())
        CollapseExpand(index.sibling(index.row(), 0));
}

void QuickEdit::CreateMenu()
{
    if (!contextMenu.isNull())
        return;

    contextMenu.reset(new QMenu());
    collapseExpandMenu = new QMenu();
    collapseExpandMenu->setTitle(tr("Collapse/Expand"));
    actCollapseExpandSelf = new QAction(tr("Self"), this);
    actCollapseExpandParent = new QAction(tr("Parent"), this);
    contextMenu->addSeparator();
    actBefore = new QAction(tr("Move marked before"), this);
    actAfter = new QAction(tr("Move marked after"), this);

    connect(actBefore, SIGNAL(triggered()), this, SLOT(OnMoveMarkedBefore()));
    connect(actAfter, SIGNAL(triggered()), this, SLOT(OnMoveMarkedAfter()));
    connect(actCollapseExpandSelf, SIGNAL(triggered()), this, SLOT(OnCollapseExpandSelf()));
    connect(actCollapseExpandParent, SIGNAL(triggered()), this, SLOT(OnCollapseExpandParent()));
}

void QuickEdit::SetupMenu(TreeItemInterface * interface)
{
    contextMenu->clear();
    collapseExpandMenu->addAction(actCollapseExpandSelf);
    collapseExpandMenu->addAction(actCollapseExpandParent);
    contextMenu->addMenu(collapseExpandMenu);
    contextMenu->addSeparator();
    contextMenu->addAction(actBefore);
    contextMenu->addAction(actAfter);

    if (BrowserNode::marked_nodes().count() == 0)
    {
        actBefore->setEnabled(false);
        actAfter->setEnabled(false);
    }
    else
    {
        actBefore->setEnabled(true);
        actAfter->setEnabled(true);
    }

    actCollapseExpandSelf->setEnabled(interface->childCount() != 0);
}

void QuickEdit::SetupItemCreationFuncs()
{
    itemCreators.insert(UmlClass,                         std::bind(&QuickEdit::AssignItemsForClass, this, std::placeholders::_1, std::placeholders::_2));
    itemCreators.insert(UmlAttribute,                     std::bind(&QuickEdit::AssignItemsForAttribute, this, std::placeholders::_1, std::placeholders::_2));
    itemCreators.insert(UmlOperation,                     std::bind(&QuickEdit::AssignItemsForOperation, this, std::placeholders::_1, std::placeholders::_2));
    itemCreators.insert(UmlAggregation,                   std::bind(&QuickEdit::AssignItemsForRelation, this, std::placeholders::_1, std::placeholders::_2));
    itemCreators.insert(UmlAggregationByValue,            std::bind(&QuickEdit::AssignItemsForRelation, this, std::placeholders::_1, std::placeholders::_2));
    itemCreators.insert(UmlDirectionalAggregation,        std::bind(&QuickEdit::AssignItemsForRelation, this, std::placeholders::_1, std::placeholders::_2));
    itemCreators.insert(UmlDirectionalAggregationByValue, std::bind(&QuickEdit::AssignItemsForRelation, this, std::placeholders::_1, std::placeholders::_2));
    itemCreators.insert(UmlExtraMember,                   std::bind(&QuickEdit::AssignItemsForExtraNode, this, std::placeholders::_1, std::placeholders::_2));
    itemCreators.insert(UmlClassView,                     std::bind(&QuickEdit::AssignItemsForClassView, this, std::placeholders::_1, std::placeholders::_2));
    itemCreators.insert(UmlPackage,                       std::bind(&QuickEdit::AssignItemsForPackage, this, std::placeholders::_1, std::placeholders::_2));
}

void QuickEdit::CheckColumnVisibility()
{
    const bool hide = !(ui->chkCpp->isChecked());

    ui->tvEditor->header()->setSectionHidden(columns.indexOf("pass"), hide);
    ui->tvEditor->header()->setSectionHidden(columns.indexOf("const"), hide);
    ui->tvEditor->header()->setSectionHidden(columns.indexOf("volatile"), hide);
    ui->tvEditor->header()->setSectionHidden(columns.indexOf("friend"), hide);
    ui->tvEditor->header()->setSectionHidden(columns.indexOf("virtual"), hide);
    ui->tvEditor->header()->setSectionHidden(columns.indexOf("inline"), hide);
    ui->tvEditor->header()->setSectionHidden(columns.indexOf("defaulted"), hide);
    ui->tvEditor->header()->setSectionHidden(columns.indexOf("delete"), hide);
    ui->tvEditor->header()->setSectionHidden(columns.indexOf("override"), hide);
    ui->tvEditor->header()->setSectionHidden(columns.indexOf("final"), hide);
    ui->tvEditor->header()->setSectionHidden(columns.indexOf("default_value"), hide);
    ui->tvEditor->header()->setSectionHidden(columns.indexOf("prefix"), hide);
    ui->tvEditor->header()->setSectionHidden(columns.indexOf("postfix"), hide);
}

void QuickEdit::AddParameter()
{
    QModelIndex current = ui->tvEditor->selectionModel()->currentIndex();
    if (!current.isValid())
        return;

    current = current.sibling(current.row(), 0);
    TreeItemInterface* itemAsInterface = static_cast<TreeItemInterface*>(current.internalPointer());
    BrowserNode* currentNode = static_cast<BrowserNode*>(itemAsInterface->InternalPointer());

    BrowserOperation* operationNode;

    if (currentNode->TypeID() == TypeIdentifier<BrowserOperation>::id())
    {
        operationNode = static_cast<BrowserOperation*>(currentNode);
    }
    else if (currentNode->TypeID() == TypeIdentifier<BrowserOperationAttribute>::id())
    {
        operationNode = static_cast<BrowserOperationAttribute*>(currentNode)->get_operation();
        itemAsInterface = itemAsInterface->parent();
        current = current.parent();
    }
    else
        return;

    OperationData* currentData = static_cast<OperationData*>(operationNode->get_data());
    int originalParamCount = currentData->nparams;
    currentData->set_n_params(originalParamCount + 1);
    QModelIndex parentIndex = current.parent();

    parentIndex = parentIndex.sibling(parentIndex.row(), 0);
    TreeItemInterface* parent = static_cast<TreeItemInterface*>(parentIndex.internalPointer());
    if (!parent)
        parent = treeModel->RootItem();
    int insertIndex = parent->GetIndexOfChild(itemAsInterface);
    auto sharedOfOperation = parent->GetChildren()[insertIndex];

    int newItemPosition = currentData->nparams;
    if (!treeModel->insertRows(sharedOfOperation->childCount(), 1, current))
        return;

    QSharedPointer<BrowserNode> param(new BrowserOperationAttribute(dummyView,
                                                                    static_cast<BrowserOperation*>(operationNode),
                                                                    currentData->params.last()));
    localNodeHolder.push_back(param);
    if (!current.isValid())
        return;
    QModelIndex newItem = treeModel->index(sharedOfOperation->childCount() - 1, 0, current);
    TreeItemInterface *newItemInterface = static_cast<TreeItemInterface*>(newItem.internalPointer());
    TreeItem<BrowserNode>* newItemAsNode = static_cast<TreeItem<BrowserNode>*>(newItemInterface);
    newItemAsNode->SetController(operationAttributeController);
    newItemAsNode->SetParent(sharedOfOperation);
    newItemAsNode->SetInternalData(param.data());
    operationNode->modified();
    OperationFuncs::recompute_param(operationNode, newItemPosition - 1, true);
}

void QuickEdit::AddOperation()
{
    QModelIndex current = ui->tvEditor->selectionModel()->currentIndex();
    if (!current.isValid())
        return;

    current = current.sibling(current.row(), 0);
    TreeItemInterface *itemAsInterface = static_cast<TreeItemInterface*>(current.internalPointer());
    BrowserNode* currentNode = static_cast<BrowserNode*>(itemAsInterface->InternalPointer());

    BrowserClass* classNode;

    int newItemPosition = 0;
    if (currentNode->TypeID() == TypeIdentifier<BrowserClass>::id())
    {
        classNode = static_cast<BrowserClass*>(currentNode);
        newItemPosition = itemAsInterface->childCount();
    }
    else if (currentNode->TypeID() == TypeIdentifier<BrowserOperation>::id() && current.parent().isValid())
    {
        itemAsInterface = static_cast<TreeItemInterface*>(current.parent().internalPointer());
        classNode = static_cast<BrowserClass*>(itemAsInterface->InternalPointer());
        newItemPosition = current.row()+1;
        current = current.parent();
    }
    else
        return;

    if (!classNode)
        return;
    BrowserOperation* newOperation = static_cast<BrowserOperation*>(classNode->addOperation());
    //classNode->move(newOperation, currentNode);
    classNode->select_in_browser();
    QModelIndex parentIndex;
    TreeItemInterface* parent;
    if (treeModel->parent(current).isValid())
    {
        parentIndex = treeModel->parent(current);
        parentIndex = parentIndex.sibling(parentIndex.row(), 0);
        parent = static_cast<TreeItemInterface*>(parentIndex.internalPointer());
    }
    else
        parent = treeModel->RootItem();
    int insertIndex = parent->GetIndexOfChild(itemAsInterface);
    auto sharedOfOperation = parent->GetChildren()[insertIndex];

    if (!treeModel->insertRows(newItemPosition - 1, 1, current))
        return;

    if (!current.isValid())
        return;

    QModelIndex newItem = treeModel->index(newItemPosition - 1, 0, current);
    TreeItemInterface *newItemInterface = static_cast<TreeItemInterface*>(newItem.internalPointer());
    TreeItem<BrowserNode>* newItemAsNode = static_cast<TreeItem<BrowserNode>*>(newItemInterface);
    newItemAsNode->SetController(operationController);
    newItemAsNode->SetParent(sharedOfOperation);
    newItemAsNode->SetInternalData(newOperation);
}

void QuickEdit::AddAttribute()
{
    QModelIndex current = ui->tvEditor->selectionModel()->currentIndex();
    if (!current.isValid())
        return;

    current = current.sibling(current.row(), 0);
    TreeItemInterface *itemAsInterface = static_cast<TreeItemInterface*>(current.internalPointer());
    BrowserNode* currentNode = static_cast<BrowserNode*>(itemAsInterface->InternalPointer());

    BrowserClass* classNode;

    int newItemPosition = 0;
    if (currentNode->TypeID() == TypeIdentifier<BrowserClass>::id())
    {
        classNode = static_cast<BrowserClass*>(currentNode);
        if (!classNode)
            return;
        newItemPosition = itemAsInterface->childCount();
    }
    else if((currentNode->TypeID() * in(TypeIdentifier<BrowserOperation>::id(),
                                       TypeIdentifier<BrowserAttribute>::id())) &&
            current.parent().isValid())
    {
        itemAsInterface = static_cast<TreeItemInterface*>(current.parent().internalPointer());
        classNode = static_cast<BrowserClass*>(itemAsInterface->InternalPointer());
        newItemPosition = current.row() + 1;
        current = current.parent();
    }
    else
        return;

    //classNode->addOperation()
    BrowserAttribute* newAttribute;
    if (QString(classNode->get_stereotype()) == "enum")
        newAttribute = static_cast<BrowserAttribute*>(classNode->addEnumItem());
    else
        newAttribute = static_cast<BrowserAttribute*>(classNode->addAttribute());
    //classNode->move(newAttribute, currentNode);
    classNode->select_in_browser();
    QModelIndex parentIndex;
    TreeItemInterface* parent;
    if (treeModel->parent(current).isValid())
    {
        parentIndex = treeModel->parent(current);
        parentIndex = parentIndex.sibling(parentIndex.row(), 0);
        parent = static_cast<TreeItemInterface*>(parentIndex.internalPointer());
    }
    else
        parent = treeModel->RootItem();

    int insertIndex = parent->GetIndexOfChild(itemAsInterface);

    QSharedPointer<TreeItemInterface> sharedOfNode = parent->GetChildren()[insertIndex];

    if (!treeModel->insertRows(newItemPosition, 1, current))
        return;

    if (!current.isValid())
        return;

    QModelIndex newItem = treeModel->index(newItemPosition,0,current);
    TreeItemInterface *newItemInterface = static_cast<TreeItemInterface*>(newItem.internalPointer());
    TreeItem<BrowserNode>* newItemAsNode = static_cast<TreeItem<BrowserNode>*>(newItemInterface);
    newItemAsNode->SetController(attributeController);
    newItemAsNode->SetParent(sharedOfNode);
    newItemAsNode->SetInternalData(newAttribute);
}

void QuickEdit::RefreshTable()
{
    if (currentNode)
        Show(currentNode);
}

void QuickEdit::CollapseExpand(const QModelIndex &index)
{
    ui->tvEditor->setExpanded(index, !ui->tvEditor->isExpanded(index));
}

BrowserNode *QuickEdit::GetCurrentNode()
{
    QModelIndex current = ui->tvEditor->currentIndex();
    TreeItemInterface* itemAsInterface = static_cast<TreeItemInterface*>(current.internalPointer());
    BrowserNode* itemAsNode = static_cast<BrowserNode*>(itemAsInterface->InternalPointer());
    return itemAsNode;
}

QSharedPointer<TreeItemInterface> QuickEdit::GetSharedOfOperation(const QModelIndex & index)
{
    QModelIndex parentIndex = index.parent();
    parentIndex = parentIndex.sibling(parentIndex.row(), 0);
    TreeItemInterface* parent = static_cast<TreeItemInterface*>(parentIndex.internalPointer());
    if (!parent)
        parent = treeModel->RootItem();
    TreeItemInterface* itemAsInterface = static_cast<TreeItemInterface*>(index.internalPointer());
    int operationIndex = parent->GetIndexOfChild(itemAsInterface);
    return parent->GetChildren()[operationIndex];
}

QList<std::function<bool (TreeItemInterface *)> > QuickEdit::CreateCheckList()
{
    QList<std::function<bool(TreeItemInterface*)>> result;
    if (!ui->leSearch->text().trimmed().isEmpty())
    {
        QString value = ui->leSearch->text();
        auto addressFilterFunc = [value](TreeItemInterface* iface)
            {
                BrowserNode* data = static_cast<BrowserNode*>(iface->InternalPointer());
                QString name = data->get_name();
                bool match = data->get_name().contains(value, Qt::CaseInsensitive);
                return match;
            };

        result.append(addressFilterFunc);
    }
    return result;
}

void QuickEdit::SetupTreeModel(TreeModel*& model,
                               QTreeView* view,
                               QSharedPointer<TreeItemInterface>& interface,
                               QSharedPointer<ItemController<BrowserNode>>& controller,
                               QSharedPointer<BrowserNode>& data)
{
    model = new TreeModel();

    TreeItem<BrowserNode>* pointer = new TreeItem<BrowserNode>(0);
    data = QSharedPointer<BrowserNode>(new BrowserNodeDummy(dummyView));
    pointer->SetController(controller);
    pointer->SetInternalData(data.data());
    //controller->SetColumns(QStringList() << "class");
    interface = QSharedPointer<TreeItemInterface>(pointer);

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

    // setup null controller
    nullController = QSharedPointer<ItemController<BrowserNode>>(new ItemController<BrowserNode>());

    validTypes << UmlAggregation << UmlAggregationByValue << UmlDirectionalAggregation << UmlClass
               << UmlDirectionalAggregationByValue << UmlAttribute << UmlOperation << UmlExtraMember << UmlClassView << UmlPackage;

    columns << "name" << "mark" << "deleted" << "prefix" << "type" << "postfix" << "default_value" << "stereotype"
            << "visibility" << "direction" << "static" << "abstract" << "multiplicity"
            << "const" << "volatile" << "friend" << "virtual" << "inline"
            << "defaulted" << "delete" << "override" << "final" << "noexcept";

    SetupItemCreationFuncs();
    qRegisterMetaType<QList<BrowserNode*>>("QList<BrowserNode*>");
    SetupControllers();
    SetupDelegates();
    SetupTreeModel(treeModel, ui->tvEditor, rootInterface, classController, modelRoot);
    ui->tvEditor->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->tvEditor->setAlternatingRowColors(true);
    connect(ui->tvEditor, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(OnContextMenu(QPoint)));
    connect(ui->leSearch, SIGNAL(textChanged(QString)), this, SLOT(OnPerformFiltering(QString)));
    connect(ui->pbUpOneLevel, SIGNAL(clicked()), this, SLOT(OnDecreaseOpenLevels()));
    connect(ui->pbDownOneLevel, SIGNAL(clicked()), this, SLOT(OnIncreaseOpenLevels()));
    connect(ui->pbAddParameter, SIGNAL(clicked()), this, SLOT(OnAddParameter()));
    connect(ui->pbAddOperation, SIGNAL(clicked()), this, SLOT(OnAddOperation()));
    connect(ui->pbAddAttribute, SIGNAL(clicked()), this, SLOT(OnAddAttribute()));
    connect(ui->pbRefreshView, SIGNAL(clicked()), this, SLOT(OnRefreshTable()));
    connect(ui->chkCpp, SIGNAL(clicked()), this, SLOT(OnChangeColumnVisibility()));
//    connect(ui->tvEditor->header(), SIGNAL(sectionResized(int,int,int)),
//            this, SLOT(OnNewSectionSizes(int,int,int)));

}

void QuickEdit::Show(BrowserNode * node)
{
    //first, we need to determine the type of currently selected item
    // if we cannot open window for such node type - do nothing
    rootInterface->removeChildren(0, rootInterface->childCount());
    localNodeHolder.clear();
    if (!node)
        return;
    UmlCode nodeType = node->get_type();
    if(!validTypes.contains(nodeType))
        return;
    //next we need to recursively create items for node
    if (!itemCreators.contains(nodeType))
        return;
    itemCreators[nodeType](rootInterface, node);
    // we then assign items and all is ok
    treeModel->InsertRootItem(rootInterface);

    // expand all items
    ExpandAllSatisfying<TreeItemInterface>([](TreeItemInterface*) { return true; },
                                           ui->tvEditor,
                                           treeModel,
                                           QModelIndex());

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "DoUML", "settings");
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    QByteArray arr = settings.value("headers/quickedit", QByteArray()).toByteArray();
    if (!arr.isNull())
        ui->tvEditor->header()->restoreState(arr);

    ui->chkCpp->setChecked(settings.value("quickedit_checkboxes/cpp",true).toBool());
    ui->chkJava->setChecked(settings.value("quickedit_checkboxes/java", true).toBool());
    ui->chkPhp->setChecked(settings.value("quickedit_checkboxes/php",true).toBool());
    ui->chkPython->setChecked(settings.value("quickedit_checkboxes/python", true).toBool());
    ui->chkIdl->setChecked(settings.value("quickedit_checkboxes/idl", true).toBool());
    QSize size = settings.value("window/size", QSize()).toSize();

    CheckColumnVisibility();
    if (!size.isValid())
        this->showMaximized();
    else
    {
        this->resize(size);
        this->show();
    }

}
bool QuickEdit::ValidType(BrowserNode * node)
{
    if (!node)
        return false;
    UmlCode nodeType = node->get_type();
    if (!validTypes.contains(nodeType))
        return false;
    return true;
}


void QuickEdit::closeEvent(QCloseEvent *)
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "DoUML", "settings");
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    if (ui->tvEditor->header()->count() > 0)
    {
        settings.setValue("headers/quickedit", ui->tvEditor->header()->saveState());
        settings.sync();
    }
    settings.setValue("quickedit_checkboxes/cpp", ui->chkCpp->isChecked());
    settings.setValue("quickedit_checkboxes/java", ui->chkJava->isChecked());
    settings.setValue("quickedit_checkboxes/php",ui->chkPhp->isChecked());
    settings.setValue("quickedit_checkboxes/python", ui->chkPython->isChecked());
    settings.setValue("quickedit_checkboxes/idl", ui->chkIdl->isChecked());
    if (!this->isMaximized())
        settings.setValue("window/size", this->size());
    else
        settings.setValue("window/size",QSize());
    ui->leSearch->setText("");
}

QSharedPointer<TreeItemInterface> QuickEdit::CreateInterfaceNode(QSharedPointer<TreeItemInterface> root,
                                                                 QSharedPointer<ItemController<BrowserNode>> controller,
                                                                 BrowserNode* node)
{
    TreeItem<BrowserNode>* pointer = new TreeItem<BrowserNode>(0);
    QSharedPointer<TreeItemInterface> interfaceItem(pointer);
    pointer->SetController(controller);
    pointer->SetInternalData(node);
    pointer->SetParent(root);
    return interfaceItem;
}


void QuickEdit::AssignItemsForClass(QSharedPointer<TreeItemInterface> root, BrowserNode* classNode)
{
    auto interfaceItem = CreateInterfaceNode(root, classController, classNode);
    auto children = classNode->children(validTypes);
    std::reverse(children.begin(), children.end());
    for (const auto& child : children)
    {
        if (!child)
            continue;
        UmlCode nodeType = child->get_type();
        itemCreators[nodeType](interfaceItem, child);
    }
    root->AddChildren(QList<QSharedPointer<TreeItemInterface>>() << interfaceItem);
}

void QuickEdit::AssignItemsForAttribute(QSharedPointer<TreeItemInterface> root, BrowserNode* classNode)
{
    auto interfaceItem = CreateInterfaceNode(root, attributeController, classNode);
    root->AddChildren(QList<QSharedPointer<TreeItemInterface>>() << interfaceItem);
}

void QuickEdit::AssignItemsForRelation(QSharedPointer<TreeItemInterface> root, BrowserNode* classNode)
{
    auto interfaceItem = CreateInterfaceNode(root, relationController, classNode);
    root->AddChildren(QList<QSharedPointer<TreeItemInterface>>() << interfaceItem);
}

void QuickEdit::AssignItemsForExtraNode(QSharedPointer<TreeItemInterface> root, BrowserNode* extraNode)
{
    auto interfaceItem = CreateInterfaceNode(root, extraNodeController, extraNode);
    root->AddChildren(QList<QSharedPointer<TreeItemInterface>>() << interfaceItem);
}

void QuickEdit::AssignItemsForClassView(QSharedPointer<TreeItemInterface> root, BrowserNode* classViewNode)
{
    auto interfaceItem = CreateInterfaceNode(root, classController, classViewNode);
    auto children = classViewNode->children(validTypes);
    std::reverse(children.begin(), children.end());
    for (const auto& child : children)
    {
        if (!child)
            continue;
        UmlCode nodeType = child->get_type();
        itemCreators[nodeType](root, child);
    }
}

void QuickEdit::AssignItemsForPackage(QSharedPointer<TreeItemInterface> root, BrowserNode* packageNode)
{
    auto interfaceItem = CreateInterfaceNode(root, classController, packageNode);
    auto children = packageNode->children(validTypes);
    std::reverse(children.begin(), children.end());
    for (const auto& child : children)
    {
        if (!child)
            continue;
        UmlCode nodeType = child->get_type();
        itemCreators[nodeType](root, child);
    }
}

void QuickEdit::MoveMarked(bool before)
{
    QModelIndex current = ui->tvEditor->currentIndex();

    if (!current.isValid())
        return;

    TreeItemInterface* itemAsInterface = static_cast<TreeItemInterface*>(current.internalPointer());
    BrowserNode* currentNode = static_cast<BrowserNode*>(itemAsInterface->InternalPointer());

    //next we reorganize nodes in parent
    TreeItemInterface* parentInterface = itemAsInterface->parent();
    auto children = parentInterface->GetChildren();
    QList<QSharedPointer<TreeItemInterface>> markedChildren;
    // we store all marked nodes
    QList<BrowserNode*> parentList;
    for (const auto& child : children)
    {
        BrowserNode* childNode = static_cast<BrowserNode*>(child->InternalPointer());
        if(!parentList.contains(static_cast<BrowserNode*>(childNode->parent())))
            parentList.append(static_cast<BrowserNode*>(childNode->parent()));
        if(childNode->markedp())
            markedChildren.append(child);
    }

    if (parentList.size() > 1)
        return;

    // remove all marked from children
    for (const auto& child : markedChildren)
    {
        children.removeOne(child);
    }
    //get the new position of origin node
    int newPositionOfCurrent = -1;
    for (const auto& child : children)
    {
        newPositionOfCurrent++;
        BrowserNode* childNode = static_cast<BrowserNode*>(child->InternalPointer());
        if(childNode == currentNode)
        {
            if(!before)
                newPositionOfCurrent++;
            break;
        }
    }
    //insert the nodes back
    std::reverse(markedChildren.begin(), markedChildren.end());
    for (const auto& child : markedChildren)
    {
        children.insert(newPositionOfCurrent, child);
    }

    auto sharedOfOperation = GetSharedOfOperation(current.parent());
    TreeItem<BrowserNode>* operationItemAsNode = static_cast<TreeItem<BrowserNode>*>(sharedOfOperation.data());
    // reorganize params vector

    BrowserOperation* operationNode = static_cast<BrowserOperation*>(operationItemAsNode->InternalPointer());
    OperationData* operationData = static_cast<OperationData*>(operationNode->get_data());
    operationData->params.clear();
    for (const auto& child : children)
    {
        BrowserOperationAttribute* attributeNode = static_cast<BrowserOperationAttribute*>(child->InternalPointer());
        operationData->params.append(attributeNode->get_param());
    }

    // install children back
    QModelIndex parentIndex = current.parent();
    treeModel->removeRows(0, children.count(), parentIndex);
    treeModel->insertRows(0, children.count(), parentIndex);
    int pos = -1;
    for (const auto& child : children)
    {
        pos++;
        QModelIndex newItem = treeModel->index(pos, 0, parentIndex);
        if (!newItem.isValid())
            continue;
        TreeItemInterface *newItemInterface = static_cast<TreeItemInterface*>(newItem.internalPointer());
        TreeItem<BrowserNode>* newItemAsNode = static_cast<TreeItem<BrowserNode>*>(newItemInterface);
        newItemAsNode->SetController(operationAttributeController);
        newItemAsNode->SetParent(sharedOfOperation);
        newItemAsNode->SetInternalData(static_cast<BrowserNode*>(child->InternalPointer()));
    }
    pos = -1;
    for (const auto& child : children)
    {
        pos++;
        QModelIndex newItem = treeModel->index(pos, 0, parentIndex);
        if (!newItem.isValid())
            continue;
        BrowserNode* node = static_cast<BrowserNode*>(child->InternalPointer());
        node->set_marked(false);
    }

    QModelIndex newItem = treeModel->index(pos, 0, parentIndex);
    if (newItem.isValid())
        pos++;
    operationNode->modified();
}

void QuickEdit::AssignItemsForOperation(QSharedPointer<TreeItemInterface> root, BrowserNode* node)
{
    QList<QSharedPointer<TreeItemInterface>> items;

    auto interfaceItem = CreateInterfaceNode(root, operationController, node);
    BrowserOperation* operationNode = static_cast<BrowserOperation*>(node);
    // first we make a dummy node for return type
    QSharedPointer<BrowserNode> returnType(new BrowserOperationReturnType(dummyView, operationNode));
    QList<QSharedPointer<BrowserNode>> operationNodes;
    operationNodes << returnType;
    // next we make dummy nodes for all attributes
    int paramCount = ((OperationData*)operationNode->get_data())->nparams;

    for (int i = 0; i < paramCount; ++i)
    {
        QSharedPointer<BrowserNode> param(new BrowserOperationAttribute(dummyView,
                                                                        operationNode,
                                                                        ((OperationData*)operationNode->get_data())->params[i]));
        operationNodes << param;
        items << CreateInterfaceNode(interfaceItem, operationAttributeController, param.data());
    }
    interfaceItem->AddChildren(items);
    root->AddChildren(QList<QSharedPointer<TreeItemInterface>>() << interfaceItem);
    localNodeHolder.append(operationNodes);
}

static void paintCheckbox(const QStyledItemDelegate* delegate,
                          QPainter* painter,
                          const QStyleOptionViewItem& option,
                          const QModelIndex& index)
{
    QVariant value = index.model()->data(index, Qt::DisplayRole);
    delegate->QStyledItemDelegate::paint(painter, option, index);
    if (!value.isValid())
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
    checkboxDelegate->widgetCreator = [](QWidget*) { return static_cast<QWidget*>(0); };
    checkboxDelegate->paintProcessor = paintCheckbox;
    checkboxDelegate->editorEventProcessor = editorEvent;

    ui->tvEditor->setItemDelegateForColumn(columns.indexOf("static"), checkboxDelegate);
    ui->tvEditor->setItemDelegateForColumn(columns.indexOf("abstract"), checkboxDelegate);
    ui->tvEditor->setItemDelegateForColumn(columns.indexOf("const"), checkboxDelegate);
    ui->tvEditor->setItemDelegateForColumn(columns.indexOf("volatile"), checkboxDelegate);
    ui->tvEditor->setItemDelegateForColumn(columns.indexOf("friend"), checkboxDelegate);
    ui->tvEditor->setItemDelegateForColumn(columns.indexOf("virtual"), checkboxDelegate);
    ui->tvEditor->setItemDelegateForColumn(columns.indexOf("inline"), checkboxDelegate);
    ui->tvEditor->setItemDelegateForColumn(columns.indexOf("defaulted"), checkboxDelegate);
    ui->tvEditor->setItemDelegateForColumn(columns.indexOf("delete"), checkboxDelegate);
    ui->tvEditor->setItemDelegateForColumn(columns.indexOf("override"), checkboxDelegate);
    ui->tvEditor->setItemDelegateForColumn(columns.indexOf("final"), checkboxDelegate);
    ui->tvEditor->setItemDelegateForColumn(columns.indexOf("deleted"), checkboxDelegate);
    ui->tvEditor->setItemDelegateForColumn(columns.indexOf("mark"), checkboxDelegate);
}

void QuickEdit::VisibilityDelegateSetup()
{
    GenericDelegate* visibilityDelegate = new GenericDelegate(ui->tvEditor, false);

    visibilityDelegate->widgetCreator = [](QWidget* parent)
    {
        QStringList visibilities;
        visibilities << "public" << "protected" << "private" << "package" << "default";
        QComboBox* box = new QComboBox(parent);
        QStringListModel* model = new QStringListModel;
        model->setStringList(visibilities);
        box->setModel(model);
        box->setEditable(false);
        return box;
    };

    visibilityDelegate->dataAccessor = [](QWidget* editor, const QModelIndex& index)
    {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        QComboBox* box = static_cast<QComboBox*>(editor);
        box->setCurrentText(value);
    };

    visibilityDelegate->dataSetter = [](QWidget* editor, QAbstractItemModel* model, const QModelIndex& index)
    {
        QComboBox* box = static_cast<QComboBox*>(editor);
        QString value = box->currentText();
        model->setData(index, value, Qt::EditRole);
    };
    
    ui->tvEditor->setItemDelegateForColumn(columns.indexOf("visibility"), visibilityDelegate);
}

void QuickEdit::TypeDelegateSetup()
{
    GenericDelegate* delegate = new GenericDelegate(ui->tvEditor, false);

    delegate->widgetCreator = [](QWidget* parent)
    {
        BrowserNodeList result;
        QStringList classes;
        BrowserClass::instances(result);
        result.full_names(classes);

        QStringList basics = GenerationSettings::basic_types();
        classes+=basics;
        QCompleter* completer = new QCompleter(classes, parent);
        completer->setCaseSensitivity(Qt::CaseSensitive);

        QComboBox* box = new QComboBox(parent);
        QStringListModel* model = new QStringListModel;
        model->setStringList(classes);
        box->setModel(model);
        box->setEditable(true);
        box->setCompleter(completer);
        return box;
    };

    delegate->dataAccessor = [](QWidget* editor, const QModelIndex& index)
    {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        QComboBox* box = static_cast<QComboBox*>(editor);
        box->setCurrentText(value);
    };

    delegate->dataSetter = [](QWidget* editor, QAbstractItemModel* model, const QModelIndex& index)
    {
        QComboBox* box = static_cast<QComboBox*>(editor);
        QString value = box->currentText();
        model->setData(index, value, Qt::EditRole);
    };

    ui->tvEditor->setItemDelegateForColumn(columns.indexOf("type"), delegate);
}

void QuickEdit::PrefixDelegateSetup()
{
    GenericDelegate* delegate = new GenericDelegate(ui->tvEditor, false);

    delegate->widgetCreator = [](QWidget* parent)
    {
        QStringList list;
        list << " " << "const " << "volatile ";
        QCompleter* completer = new QCompleter(list, parent);
        completer->setCaseSensitivity(Qt::CaseSensitive);

        QComboBox* box = new QComboBox(parent);
        QStringListModel* model = new QStringListModel;
        model->setStringList(list);
        box->setModel(model);
        box->setEditable(true);
        box->setCompleter(completer);
        return box;
    };

    delegate->dataAccessor = [](QWidget* editor, const QModelIndex& index)
    {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        QComboBox* box = static_cast<QComboBox*>(editor);
        box->setCurrentText(value);
    };
    
    delegate->dataSetter = [](QWidget* editor, QAbstractItemModel* model, const QModelIndex& index)
    {
        QComboBox* box = static_cast<QComboBox*>(editor);
        QString value = box->currentText();
        model->setData(index, value, Qt::EditRole);
    };

    ui->tvEditor->setItemDelegateForColumn(columns.indexOf("prefix"), delegate);
}

void QuickEdit::PostfixDelegateSetup()
{
    GenericDelegate* delegate = new GenericDelegate(ui->tvEditor, false);

    delegate->widgetCreator = [](QWidget* parent)
    {
        QStringList list;
        list << " " << "*" << "&";
        QCompleter* completer = new QCompleter(list, parent);
        completer->setCaseSensitivity(Qt::CaseSensitive);

        QComboBox* box = new QComboBox(parent);
        QStringListModel* model = new QStringListModel;
        model->setStringList(list);
        box->setModel(model);
        box->setEditable(true);
        box->setCompleter(completer);
        return box;
    };

    delegate->dataAccessor = [](QWidget* editor, const QModelIndex& index)
    {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        QComboBox* box = static_cast<QComboBox*>(editor);
        box->setCurrentText(value);
    };

    delegate->dataSetter = [](QWidget * editor,QAbstractItemModel* model, const QModelIndex& index)
    {
        QComboBox* box = static_cast<QComboBox*>(editor);
        QString value = box->currentText();
        model->setData(index, value, Qt::EditRole);
    };

    ui->tvEditor->setItemDelegateForColumn(columns.indexOf("postfix"), delegate);
}

void QuickEdit::DirectionDelegateSetup()
{
    GenericDelegate* delegate = new GenericDelegate(ui->tvEditor, false);

    delegate->widgetCreator = [](QWidget* parent)
    {
        QStringList visibilities;
        visibilities << "inout" << "in" << "out";
        QComboBox* box = new QComboBox(parent);
        QStringListModel* model = new QStringListModel;
        model->setStringList(visibilities);
        box->setModel(model);
        box->setEditable(false);
        return box;
    };
    
    delegate->dataAccessor = [](QWidget* editor, const QModelIndex& index)
    {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        QComboBox* box = static_cast<QComboBox*>(editor);
        box->setCurrentText(value);
    };

    delegate->dataSetter = [](QWidget* editor, QAbstractItemModel* model, const QModelIndex& index)
    {
        QComboBox* box = static_cast<QComboBox*>(editor);
        QString value = box->currentText();
        model->setData(index, value, Qt::EditRole);
    };

    ui->tvEditor->setItemDelegateForColumn(columns.indexOf("direction"), delegate);
}
