#include "quickedit.h"
#include "ui_quickedit.h"

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
            std::bind(&CatalogWidget::CreateCheckList, this);

    TreeFunctions::FilterTreeAndRestoreNodes<TreeItemInterface, TreeItem, BrowserNode>
            (dataAccessFunc, checksFunc,
                     expandedNodes, view, model, interface);
}

void QuickEdit::OnContextMenu(QPoint point)
{
    CreateFavouritesMenu();
    CreateMenu->popup(ui->tvEditor->mapToGlobal(point));
}


void QuickEdit::CreateMenu()
{
    if(favouritesMenu.isNull())
    {
        favouritesMenu.reset(new QMenu());
        favouritesMenu->addAction(tr("Remove from favourites"), this, SLOT(OnRemoveCurrentItemFromFavourites()));
    }
}

QList<std::function<bool (TreeItemInterface *)> > QuickEdit::CreateCheckList()
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

#define ADD_STRING_GETSET(HOLDER,ROW,ROLE,PARAM)  \
HOLDER->AddGetter(QPair<int,int>(ROW,ROLE), \
[] (const Builtin* data) \
{ \
    if(data) \
        return QVariant(data->PARAM); \
    else \
        return QVariant(); \
} \
); \
HOLDER->AddSetter(QPair<int,int>(ROW,ROLE), \
[] (Builtin* data, QVariant value) \
{ \
    if(data) \
        data->PARAM = value.toString(); \
} \
);


void QuickEdit::SetupTreeController(QSharedPointer<ItemController<BrowserNode> >& treeController)
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

void QuickEdit::SetupTreeModel(TreeModel*& model , QTreeView* view,
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

void QuickEdit::Init(UmlWindow* window, BrowserView* view)
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


    dragDropFilter = new GenericEventFilter(this);
    std::function<void(BrowserNode*)>favsFunc = std::bind(&CatalogWidget::AddToFavourites, this, std::placeholders::_1);
    dragDropFilter->SetEventProcessor(std::bind(ProcessDragDrop,std::placeholders::_1, std::placeholders::_2, favsFunc));
    ui->tvFavourites->installEventFilter(dragDropFilter);
    ui->tvFavourites->setAcceptDrops(true);
    ui->tvFavourites->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tvMarkedNodes->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tvFavourites, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(OnFavouritesContextMenu(QPoint)));
    connect(ui->tvMarkedNodes, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(OnMarkedContextMenu(QPoint)));
}

void QuickEdit::OnContextMenu(QPoint)
{


}
