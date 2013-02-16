#ifndef CATALOGWIDGET_H
#define CATALOGWIDGET_H

#include <QWidget>
#include <QSharedPointer>
#include <functional>
#include "Libs/L_UniversalModels/include/ItemController.h"

namespace Ui {
class CatalogWidget;
}
class BrowserView;
class TreeModel;
class QMenu;
class BrowserNode;
class TreeItemInterface;
class QTreeView;
class Q3ListViewItem;
class GenericEventFilter;
class CatalogWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit CatalogWidget(QWidget *parent = 0);
    ~CatalogWidget();

    // visited treeview
    TreeModel* tmodVisited = nullptr;
    bool isFilteredVisited = false;
    QStringList expandedNodesVisited;
    QSharedPointer<TreeItemInterface> rootVisitedInterface;
    QSharedPointer<ItemController<BrowserNode> > controllerVisited;
    QSharedPointer<BrowserNode> rootVisited;

    // marked treeview
    TreeModel* tmodMarked = nullptr;
    bool isFilteredMarked = false;
    QStringList expandedNodesMarked;
    QSharedPointer<TreeItemInterface> rootMarkedInterface;
    QSharedPointer<ItemController<BrowserNode> > controllerMarked;
    QSharedPointer<BrowserNode> rootMarked;

    // favourites treeview
    TreeModel* tmodFavourites = nullptr;
    bool isFilteredFavourites = false;
    QStringList expandedNodesFavourites;
    QSharedPointer<TreeItemInterface> rootFavouritesInterface;
    QSharedPointer<ItemController<BrowserNode> > controllerFavourites;
    QSharedPointer<BrowserNode> rootFavourites;

    void Init(BrowserView*);

    GenericEventFilter* dragDropFilter;


    
private:
    Ui::CatalogWidget *ui = nullptr;
    BrowserView* dummyView = nullptr;
    BrowserView* originalView = nullptr;


    void SetupTreeModel(TreeModel* ,QTreeView*,
                        QSharedPointer<TreeItemInterface>&,
                        QSharedPointer<ItemController<BrowserNode> >&,
                        QSharedPointer<BrowserNode>&, BrowserView*, const char *);
    void SetupTreeController(QSharedPointer<ItemController<BrowserNode> >&);
    void PerformFiltering(QStringList, QTreeView*, TreeModel*, QSharedPointer<TreeItemInterface>);
    QList<std::function<bool (TreeItemInterface *)> > CreateCheckList();

public slots:
    void OnPerformVisitedFiltering();
    void OnPerformMarkedFiltering();
    void OnPerformFavouritesFiltering();
    void OnUpdateVisitedView(Q3ListViewItem * item);
    void OnUpdateMarkedView(QList<BrowserNode*>);
    void OnUpdateFavoutitesView();

};

#endif // CATALOGWIDGET_H
