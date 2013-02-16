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
#include "browser/BrowserPackage.h"
#include "ProfiledStereotypes.h"
#include "ClassData.h"
#include <functional>
#include <QTreeView>

CatalogWidget::CatalogWidget( QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatalogWidget)
{
    ui->setupUi(this);
}

CatalogWidget::~CatalogWidget()
{
    delete ui;
}

bool ProcessDragDrop(QObject* /*obj*/, QEvent *event, QTreeView* view)
{
    if(event->type() == QEvent::DragMove)
    {
        QModelIndex index =view->selectionModel()->currentIndex();
        if(!index.isValid())
            return true;
        return true;
    }
    return false;
}

void CatalogWidget::Init(BrowserView* view)
{
    originalView = view;

    connect(view, SIGNAL(selectionChanged(Q3ListViewItem *)),
            this, SLOT(OnUpdateVisitedView(Q3ListViewItem *)));
    connect(ui->leVisitedSearch, SIGNAL(returnPressed()), this, SLOT(OnPerformVisitedFiltering()));

    qRegisterMetaType<QList<BrowserNode*>>("QList<BrowserNode*>");
    connect(view, SIGNAL(marked_list(QList<BrowserNode*>)), this, SLOT(OnUpdateMarkedView(QList<BrowserNode*>)));

    SetupTreeModel(tmodVisited, ui->tvVisitedNodes,rootVisitedInterface,controllerVisited,rootVisited,
                   originalView, SLOT(OnPickSelectionFromVisited( QModelIndex, QModelIndex )));
    SetupTreeModel(tmodMarked, ui->tvMarkedNodes,rootMarkedInterface,controllerMarked,rootMarked,
                   originalView, SLOT(OnPickSelectionFromVisited(QModelIndex,QModelIndex )));
    SetupTreeModel(tmodFavourites, ui->tvFavourites,rootFavouritesInterface,controllerFavourites,rootFavourites,
                   originalView, SLOT(OnPickSelectionFromVisited( QModelIndex, QModelIndex )));


    dragDropFilter = new GenericEventFilter(this);
    dragDropFilter->SetEventProcessor(std::bind(ProcessDragDrop,std::placeholders::_1, std::placeholders::_2, ui->tvFavourites));
    ui->tvFavourites->installEventFilter(dragDropFilter);
}


void CatalogWidget::SetupTreeModel(TreeModel* model , QTreeView* view,
                               QSharedPointer<TreeItemInterface> &interface,
                               QSharedPointer<ItemController<BrowserNode> > &controller,
                               QSharedPointer<BrowserNode> &data, BrowserView* originalView ,const char* slotName)
{
    model = new TreeModel();
    SetupTreeController(controller);

    TreeItem<BrowserNode>* pointer = new TreeItem<BrowserNode>(0);
    interface = QSharedPointer<TreeItemInterface >(pointer);
    QList<QSharedPointer<TreeItemInterface > >  items;
    pointer->SetController(controller);
    pointer->addChildren(items);
    //result = new BrowserClass(s, parent, new ClassData, id);
    data = QSharedPointer<BrowserNode>(new BrowserPackage(QString("hmm"), dummyView));

    pointer->SetInternalData(data.data());
    controller->SetColumns(QStringList() << "class");
    model->InsertRootItem(interface);
    //templateRootItem->AddChildren();

    view->setModel(model);
    view->setContextMenuPolicy(Qt::CustomContextMenu);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setColumnWidth(0, 230);
    view->setExpandsOnDoubleClick(false);
    view->setRootIsDecorated(true);
    connect(view, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(OnTreeRequestsContextMenu(QPoint)));
    connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(OnTreeItemDoubleClicked(QModelIndex)));
    connect(model, SIGNAL(dataEditFinished(QModelIndex)), this, SLOT(OnDataEditFinished(QModelIndex)));

    connect(view->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            originalView, slotName);
}


void CatalogWidget::SetupTreeController(QSharedPointer<ItemController<BrowserNode> >& treeController)
{
    treeController = QSharedPointer<ItemController<BrowserNode> >( new ItemController<BrowserNode>());
    treeController->AddGetter(QPair<int,int>(0,0),

                              [] (const BrowserNode* data)
    {
        if(data)
            return QVariant(data->get_name());
        else
            return QVariant();
    }
    );

    treeController->AddGetter(QPair<int,int>(0,1),

                              [] (const BrowserNode* data)
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


void CatalogWidget::OnUpdateFavoutitesView()
{
}

void CatalogWidget::OnPerformVisitedFiltering()
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
    BrowserNode* itemAsNode = static_cast<BrowserNode*>(item);
    itemAsNode = itemAsNode->get_first_generatable_node();

    QList<std::function<bool (TreeItemInterface *)> > checkList;
    QString value = itemAsNode->get_name();
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

    TreeFunctions::RecursiveModify(rootVisitedInterface.data(), checkList << nameFilterFunc, modifyList << modifyFunc, true, false);


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

void CatalogWidget::OnUpdateMarkedView(QList<BrowserNode *>)
{

}
