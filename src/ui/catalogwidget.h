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
#ifndef CATALOGWIDGET_H
#define CATALOGWIDGET_H

#include <QWidget>
#include <QSharedPointer>
#include <QMenu>
#include <functional>
#include "Libs/L_UniversalModels/include/ItemController.h"

namespace Ui {
class CatalogWidget;
}
class BrowserView;
class TreeModel;

class BrowserNode;
class TreeItemInterface;
class QTreeView;
class Q3ListViewItem;
class GenericEventFilter;
class UmlWindow;
class CatalogWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit CatalogWidget(QWidget *parent = 0);
    ~CatalogWidget();

    void Init(UmlWindow*,BrowserView*);
    void CleanupBeforeNewProject();
    void StageSkipVisited();
    bool UseSkipVisited();
    
private:
    Ui::CatalogWidget *ui = nullptr;
    BrowserView* dummyView = nullptr;
    BrowserView* originalView = nullptr;
    UmlWindow* mainWindow = nullptr;
    QScopedPointer<QMenu> favouritesMenu;
    QScopedPointer<QMenu> markedMenu;
    bool skipVisited = false;

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
    //QList<QSharedPointer<BrowserNode> >favouritesList;
    QSharedPointer<BrowserNode> rootFavourites;

    GenericEventFilter* dragDropFilter;


    void SetupTreeModel(TreeModel*& , QTreeView*,
                        QSharedPointer<TreeItemInterface>&,
                        QSharedPointer<ItemController<BrowserNode> >&,
                        QSharedPointer<BrowserNode>&, QWidget *window, const char *);
    void SetupTreeController(QSharedPointer<ItemController<BrowserNode> >&);
    void PerformFiltering(QStringList, QTreeView*, TreeModel*, QSharedPointer<TreeItemInterface>);
    QList<std::function<bool (TreeItemInterface *)> > CreateCheckList();
    bool RemoveExisting(BrowserNode *,QSharedPointer<TreeItemInterface> );
    bool AddToFavourites(BrowserNode*);
    void CreateFavouritesMenu();
    void CreateMarkedMenu();
    void PullNodeUpwardsInVisited(BrowserNode*);

public slots:
    //void OnPerformVisitedFiltering();
    void OnPerformVisitedFiltering(QString);
    void OnPerformMarkedFiltering();
    void OnPerformFavouritesFiltering();
    void OnUpdateVisitedView(Q3ListViewItem * item);
    void OnUpdateMarkedView(QList<BrowserNode*>);
    void OnUpdateFavoutitesView();
    void OnSelectedInVisited(const QModelIndex &, const QModelIndex &);
    void OnRemoveCurrentItemFromFavourites();
    void OnRemoveCurrentItemFromMarked();
    void OnRemoveAllItemsFromMarked();
    void OnFavouritesContextMenu(QPoint);
    void OnMarkedContextMenu(QPoint point);
signals:
    void markedRemove(QString, int);
    void allMarkedRemove();

};

#endif // CATALOGWIDGET_H
