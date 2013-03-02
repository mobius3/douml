#ifndef QUICKEDIT_H
#define QUICKEDIT_H

#include <QWidget>
#include <QSharedPointer>
#include <QMenu>
#include <functional>
#include "Libs/L_UniversalModels/include/ItemController.h"

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
    
private:
    Ui::QuickEdit *ui = nullptr;
    BrowserView* dummyView = nullptr;
    BrowserView* originalView = nullptr;
    UmlWindow* mainWindow = nullptr;
    QScopedPointer<QMenu> contextMenu;

    // visited treeview
    TreeModel* tmodVisited = nullptr;
    bool isFilteredVisited = false;
    QStringList expandedNodesVisited;
    QSharedPointer<TreeItemInterface> rootVisitedInterface;
    QSharedPointer<ItemController<BrowserNode> > controllerVisited;
    QSharedPointer<BrowserNode> rootVisited;


    void SetupTreeModel(TreeModel*& , QTreeView*,
                        QSharedPointer<TreeItemInterface>&,
                        QSharedPointer<ItemController<BrowserNode> >&,
                        QSharedPointer<BrowserNode>&, QWidget *window, const char *);
    void SetupTreeController(QSharedPointer<ItemController<BrowserNode> >&);
    void PerformFiltering(QStringList, QTreeView*, TreeModel*, QSharedPointer<TreeItemInterface>);
    QList<std::function<bool (TreeItemInterface *)> > CreateCheckList();
    void CreateMenu();

    public slots:
    void OnContextMenu(QPoint);

};

#endif // QUICKEDIT_H
