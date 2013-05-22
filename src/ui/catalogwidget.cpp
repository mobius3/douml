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
#include "catalogwidget.h"
#include "ui_catalogwidget.h"

// some very perverted stuff
#include "Libs/L_UniversalModels/include/TreeModel.h"
#include "Libs/L_UniversalModels/include/TreeItemInterface.h"
#include "Libs/L_UniversalModels/include/treeviewfunctions.h"
#include "Libs/L_UniversalModels/include/treeviewtemplatefunctions.h"
#include "Libs/L_UniversalModels/include/TreeItem.h"
#include "Libs/L_UniversalModels/include/genericeventfilter.h"
#include "diagram/BrowserView.h"
//#include "browser/BrowserClassView.h"
#include "browser/BrowserNodeDummy.h"
#include "diagram/UmlWindow.h"
#include "misc/UmlDrag.h"
#include "ClassData.h"
#include <functional>
#include <QTreeView>
#include <QMouseEvent>
#include <QDragMoveEvent>

CatalogWidget::CatalogWidget( QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatalogWidget)
{
    ui->setupUi(this);
    if(!dummyView)
        dummyView = new BrowserView();
}

CatalogWidget::~CatalogWidget()
{
    delete dummyView;
    delete ui;
}

bool ProcessDragDrop(QObject* /*obj*/, QEvent *event, std::function<void(BrowserNode*)> favsFunc)
{
    if(event->type() == QEvent::DragEnter)
    {
        QList<UmlCode> codes;
        codes << UmlClass << UmlAttribute << UmlOperation << UmlDeploymentNode;
        BrowserNode * node = UmlDrag::get_node();
        UmlCode code = node->get_type();
        if(codes.contains(code))
            return true;
        return false;
    }
    else if(event->type() == QEvent::Drop)
    {
        QList<UmlCode> codes;
        codes << UmlClass << UmlAttribute << UmlOperation << UmlDeploymentNode;
        BrowserNode * node = UmlDrag::get_node();
        UmlCode code = node->get_type();
        if(!codes.contains(code))
            return false;

        favsFunc(UmlDrag::get_node());
        return true;
    }
    return false;
}

void CatalogWidget::Init(UmlWindow* window, BrowserView* view)
{
    originalView = view;
    mainWindow = window;

    connect(view, SIGNAL(selectionChanged(Q3ListViewItem *)),
            this, SLOT(OnUpdateVisitedView(Q3ListViewItem *)));
    connect(ui->leVisitedSearch, SIGNAL(textChanged(QString)), this, SLOT(OnPerformVisitedFiltering(QString)));

    qRegisterMetaType<QList<BrowserNode*>>("QList<BrowserNode*>");
    connect(view, SIGNAL(marked_list(QList<BrowserNode*>)), this, SLOT(OnUpdateMarkedView(QList<BrowserNode*>)));

    SetupTreeModel(tmodVisited, ui->tvVisitedNodes,rootVisitedInterface,controllerVisited,rootVisited,
                   this, SLOT(OnSelectedInVisited(const QModelIndex &, const QModelIndex &)));
    SetupTreeModel(tmodMarked, ui->tvMarkedNodes,rootMarkedInterface,controllerMarked,rootMarked,
                   mainWindow, SLOT(OnPickSelectionFromItem(QModelIndex,QModelIndex )));
    SetupTreeModel(tmodFavourites, ui->tvFavourites,rootFavouritesInterface,controllerFavourites,rootFavourites,
                   mainWindow, SLOT(OnPickSelectionFromItem( QModelIndex, QModelIndex )));


    //dragDropFilter = new GenericEventFilter(this);
    //std::function<void(BrowserNode*)>favsFunc = std::bind(&CatalogWidget::AddToFavourites, this, std::placeholders::_1);
    //dragDropFilter->SetEventProcessor(std::bind(ProcessDragDrop,std::placeholders::_1, std::placeholders::_2, favsFunc));
    //ui->tvFavourites->installEventFilter(dragDropFilter);
    ui->tvFavourites->setAcceptDrops(true);
    ui->tvFavourites->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tvMarkedNodes->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tvFavourites, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(OnFavouritesContextMenu(QPoint)));
    connect(ui->tvMarkedNodes, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(OnMarkedContextMenu(QPoint)));
}

void CatalogWidget::CleanupBeforeNewProject()
{
    rootVisitedInterface->removeChildren(0,rootVisitedInterface->childCount());
    tmodVisited->InsertRootItem(rootVisitedInterface);
    if(rootMarkedInterface)
    {
        rootMarkedInterface->removeChildren(0,rootMarkedInterface->childCount());
        tmodMarked->InsertRootItem(rootMarkedInterface);
    }
    if(rootFavouritesInterface)
    {
        rootFavouritesInterface->removeChildren(0,rootFavouritesInterface->childCount());
        tmodFavourites->InsertRootItem(rootFavouritesInterface);
    }
}

void CatalogWidget::StageSkipVisited()
{
    skipVisited = true;
}

bool CatalogWidget::UseSkipVisited()
{
    if(skipVisited)
    {
        skipVisited = false;
        return true;
    }
    return false;
}


void CatalogWidget::SetupTreeModel(TreeModel*& model , QTreeView* view,
                               QSharedPointer<TreeItemInterface> &interface,
                               QSharedPointer<ItemController<BrowserNode> > &controller,
                               QSharedPointer<BrowserNode> &data, QWidget* originalView ,const char* slotName)
{
    model = new TreeModel();
    SetupTreeController(controller);

    TreeItem<BrowserNode>* pointer = new TreeItem<BrowserNode>(0);
    interface = QSharedPointer<TreeItemInterface >(pointer);
    QList<QSharedPointer<TreeItemInterface > >  items;
    pointer->SetController(controller);
    pointer->addChildren(items);

    data = QSharedPointer<BrowserNode>(new BrowserNodeDummy(dummyView));

    pointer->SetInternalData(data.data());
    controller->SetColumns(QStringList() << "class");
    model->InsertRootItem(interface);

    view->setModel(model);
    view->setContextMenuPolicy(Qt::CustomContextMenu);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setColumnWidth(0, 230);
    view->setExpandsOnDoubleClick(false);
    view->setRootIsDecorated(true);
    if(originalView)
        connect(view->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            originalView, slotName);
}


void CatalogWidget::SetupTreeController(QSharedPointer<ItemController<BrowserNode> >& treeController)
{
    treeController = QSharedPointer<ItemController<BrowserNode> >( new ItemController<BrowserNode>());
    treeController->AddGetter(QPair<int,int>(0,0),

                              [] (const BrowserNode* data, QModelIndex )
    {
        if(data)
            return QVariant(data->get_name());
        else
            return QVariant();
    }
    );

    treeController->AddGetter(QPair<int,int>(0,1),

                              [] (const BrowserNode* data, QModelIndex )
    {
        const QPixmap * pm = data->pixmap(true);
        if(!pm)
            return QIcon();
        return QIcon(*pm);
    }
    );

    treeController->AddFlagsFunctor(
                [](const QModelIndex& )
    {
        Qt::ItemFlags result;
        result |= Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        return result;
    }
    );
}


QList<std::function<bool (TreeItemInterface *)> > CatalogWidget::CreateCheckList()
{
    QList<std::function<bool (TreeItemInterface *)> > result;
    if(!ui->leVisitedSearch->text().trimmed().isEmpty())
    {
        QString value = ui->leVisitedSearch->text();
        std::function<bool(TreeItemInterface*)> addressFilterFunc =  [value](TreeItemInterface* iface)
        {
            BrowserNode* data = static_cast<BrowserNode*>(iface->InternalPointer());
            bool match = data->get_name().contains(value, Qt::CaseInsensitive);
            return match;
        };
        result.append(addressFilterFunc);
    }
    return result;
}

bool CatalogWidget::RemoveExisting(BrowserNode * node, QSharedPointer<TreeItemInterface> rootInterface)
{
    QList<std::function<bool (TreeItemInterface *)> > checkList;
    QString value = node->get_name();
    std::function<bool(TreeItemInterface*)> nameFilterFunc =  [value](TreeItemInterface* iface)
    {
        BrowserNode* data = static_cast<BrowserNode*>(iface->InternalPointer());
        bool match = data->get_name() == value;
        return match;
    };


    QList<std::function<void (TreeItemInterface *)> > modifyList;
    TreeFunctions::ModifierFunction<TreeItemInterface> modifyFunc = [] (TreeItemInterface* interface)
    {
        TreeItemInterface* parent = interface->parent();
        if(parent)
            parent->removeChildren(parent->GetIndexOfChild(interface),1);
    };

    return TreeFunctions::RecursiveModify(rootInterface.data(), checkList << nameFilterFunc, modifyList << modifyFunc, true, false);
}

bool CatalogWidget::AddToFavourites(BrowserNode * node)
{
    QList<std::function<bool (TreeItemInterface *)> > checkList;
    QString value = node->get_name();
    UmlCode code = node->get_type();
    std::function<bool(TreeItemInterface*)> nameFilterFunc =  [value](TreeItemInterface* iface)
    {
        BrowserNode* data = static_cast<BrowserNode*>(iface->InternalPointer());
        bool match = data->get_name() == value;
        return match;
    };
    std::function<bool(TreeItemInterface*)> typeFilterFunc =  [code](TreeItemInterface* iface)
    {
        BrowserNode* data = static_cast<BrowserNode*>(iface->InternalPointer());
        bool match = data->get_type() == code;
        return match;
    };
    bool result = TreeFunctions::RecursiveSearch<TreeItemInterface>(rootFavouritesInterface.data(), checkList << nameFilterFunc << typeFilterFunc);
    if(result)
        return true;

    TreeItem<BrowserNode>* pointer = new TreeItem<BrowserNode>(0);
    QSharedPointer<TreeItemInterface > interfaceItem(pointer);

    pointer->SetController(controllerFavourites);

    pointer->SetInternalData(node);
    pointer->SetParent(rootFavouritesInterface);
    QList<QSharedPointer<TreeItemInterface > >  items;
    items << interfaceItem;
    rootFavouritesInterface->AddChildren(items);
    tmodFavourites->InsertRootItem(rootFavouritesInterface);
    return true;
}

void CatalogWidget::CreateFavouritesMenu()
{
    if(favouritesMenu.isNull())
    {
        favouritesMenu.reset(new QMenu());
        favouritesMenu->addAction(tr("Remove from favourites"), this, SLOT(OnRemoveCurrentItemFromFavourites()));
    }
}

void CatalogWidget::CreateMarkedMenu()
{
    if(markedMenu.isNull())
    {
        markedMenu.reset(new QMenu());
        markedMenu->addAction(tr("Unmark"), this, SLOT(OnRemoveCurrentItemFromMarked()));
        markedMenu->addAction(tr("Unmark all"), this, SLOT(OnRemoveAllItemsFromMarked()));
    }
}

void CatalogWidget::PullNodeUpwardsInVisited(BrowserNode * itemAsNode)
{
    RemoveExisting(itemAsNode, rootVisitedInterface);

    TreeItem<BrowserNode>* pointer = new TreeItem<BrowserNode>(0);
    QSharedPointer<TreeItemInterface > interfaceItem(pointer);

    pointer->SetController(controllerVisited);

    pointer->SetInternalData(itemAsNode);
    pointer->SetParent(rootVisitedInterface);
    QList<QSharedPointer<TreeItemInterface > >  items;
    items << interfaceItem;
    rootVisitedInterface->AddChildren(items);
    tmodVisited->InsertRootItem(rootVisitedInterface);
}


void CatalogWidget::OnUpdateFavoutitesView()
{
}

void CatalogWidget::OnSelectedInVisited(const QModelIndex& current, const QModelIndex&)
{
    StageSkipVisited();
    TreeItemInterface *itemAsInterface = static_cast<TreeItemInterface*>(current.internalPointer());
    BrowserNode* itemAsNode = static_cast<BrowserNode*>(itemAsInterface->InternalPointer());
    itemAsNode->select_in_browser();
}

void CatalogWidget::OnRemoveCurrentItemFromFavourites()
{
    QModelIndex current = ui->tvFavourites->currentIndex();
    rootFavouritesInterface->removeChildren(current.row(),1);
    tmodFavourites->InsertRootItem(rootFavouritesInterface);
}

void CatalogWidget::OnRemoveCurrentItemFromMarked()
{
    QModelIndex current = ui->tvMarkedNodes->currentIndex();
    TreeItemInterface *itemAsInterface = static_cast<TreeItemInterface*>(current.internalPointer());
    BrowserNode* itemAsNode = static_cast<BrowserNode*>(itemAsInterface->InternalPointer());
    if(itemAsNode)
    {
        emit markedRemove(itemAsNode->get_name(), itemAsNode->get_type());
    }
}

void CatalogWidget::OnRemoveAllItemsFromMarked()
{
    emit allMarkedRemove();
}

void CatalogWidget::OnFavouritesContextMenu(QPoint point)
{
    CreateFavouritesMenu();
    favouritesMenu->popup(ui->tvFavourites->mapToGlobal(point));
}
void CatalogWidget::OnMarkedContextMenu(QPoint point)
{
    CreateMarkedMenu();
    markedMenu->popup(ui->tvMarkedNodes->mapToGlobal(point));
}

void CatalogWidget::OnPerformVisitedFiltering(QString)
{
    PerformFiltering(expandedNodesVisited, ui->tvVisitedNodes, tmodVisited, rootVisitedInterface);
}

void CatalogWidget::OnPerformMarkedFiltering()
{
    PerformFiltering(expandedNodesMarked, ui->tvMarkedNodes, tmodMarked, rootMarkedInterface);
}

void CatalogWidget::OnPerformFavouritesFiltering()
{
    PerformFiltering(expandedNodesFavourites, ui->tvFavourites, tmodFavourites, rootFavouritesInterface);
}


void CatalogWidget::PerformFiltering(QStringList expandedNodes, QTreeView* view, TreeModel* model, QSharedPointer<TreeItemInterface > interface)
{
    std::function<QVariant(BrowserNode*)> dataAccessFunc =
            [](BrowserNode* data){return QVariant(data->get_name());};

    std::function<QList<std::function<bool (TreeItemInterface *)> > ()> checksFunc =
            std::bind(&CatalogWidget::CreateCheckList, this);

    TreeFunctions::FilterTreeAndRestoreNodes<TreeItemInterface, TreeItem, BrowserNode>
            (dataAccessFunc, checksFunc,
                     expandedNodes, view, model, interface);
}



void CatalogWidget::OnUpdateVisitedView(Q3ListViewItem * item)
{
    if(UseSkipVisited())
        return;
    //this->ui->tabWidget->setCurrentWidget(this->ui->tabVisited);
    BrowserNode* itemAsNode = static_cast<BrowserNode*>(item);
    itemAsNode = itemAsNode->get_first_generatable_node();

    PullNodeUpwardsInVisited(itemAsNode);
}

void CatalogWidget::OnUpdateMarkedView(QList<BrowserNode *> markedItems)
{
    this->ui->tabWidget->setCurrentWidget(this->ui->tabMarked);
    if(rootMarkedInterface.isNull())
        return;
    StageSkipVisited();
    QList<QSharedPointer<TreeItemInterface > >  items;
    rootMarkedInterface->removeChildren(0, rootMarkedInterface->childCount());
    for(BrowserNode * marked : markedItems)
    {
        TreeItem<BrowserNode>* pointer = new TreeItem<BrowserNode>(0);
        QSharedPointer<TreeItemInterface > interfaceItem(pointer);

        pointer->SetController(controllerMarked);

        pointer->SetInternalData(marked);
        pointer->SetParent(rootMarkedInterface);

        items << interfaceItem;
    }
    rootMarkedInterface->AddChildren(items);
    tmodMarked->InsertRootItem(rootMarkedInterface);
}
