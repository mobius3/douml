// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
// Copyright 2012-2013 Nikolai Marchenko.
// Copyright 2012-2013 Leonardo Guilherme.
//
// This file is part of the DOUML Uml Toolkit.
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
// home   : http://sourceforge.net/projects/douml
//
// *************************************************************************





#include <qapplication.h>
//#include <q3popupmenu.h>
//#include <q3dragobject.h>
//#include <q3header.h>
#include <qcursor.h>
//Added by qt3to4:
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include "BrowserView.h"
#include "UmlWindow.h"
#include "BrowserPackage.h"
#include "BrowserSearchDialog.h"
#include "UmlDrag.h"
#include "Shortcut.h"
#include "myio.h"
#include "mu.h"
#include "translate.h"
#include "ToolCom.h"
#include "Tool.h"
#include <QHeaderView>
#include <QDrag>
#include <QKeyEvent>
BrowserPackage * BrowserView::project;
BrowserPackage * BrowserView::imported_project;
QDir BrowserView::dir;
QDir BrowserView::import_dir;
BrowserView * BrowserView::the;

BrowserView::BrowserView(QWidget * parent) : QTreeWidget(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    the = this;
    BrowserNode::setup_generatable_types();
    project = 0;			// no project yet
    mousePressed = FALSE;
    setSortingEnabled(false);		// manual sorting
    setSelectionMode(QAbstractItemView::SingleSelection);

    //addColumn(TR("browser          "));
    setColumnCount(1);
    headerItem()->setText(0, QObject::tr("browser          "));

    //setSelectionMode(Extended);	// multi selection
    headerItem()->setFlags(headerItem()->flags()|Qt::ItemIsSelectable| Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    setAcceptDrops(TRUE);
    viewport()->setAcceptDrops(TRUE);
    this->header()->setSectionsClickable(true);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(rightPressed(const QPoint&)));

    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            this, SLOT(doubleClick(QTreeWidgetItem*, int )));
    connect(this->header(), SIGNAL(sectionClicked(int)), this, SLOT(menu()));
    connect(this, SIGNAL(itemSelectionChanged()),
            this, SLOT(onItemSelected()));
    setDragDropMode(DragDrop);
}

void BrowserView::remove_temporary_files()
{
    if (project) {
        QStringList filter;
        //filter.sprintf("*_%d.*", user_id());
        filter.append(QString("*_%1.*").arg(user_id()));

        const QFileInfoList l = dir.entryInfoList(filter);
        if (!l.empty()) {
            QListIterator<QFileInfo> it(l);
            QFileInfo fi;

            while (it.hasNext()) {
                fi = it.next();
                if (!fi.fileName().endsWith( "prj", Qt::CaseInsensitive))
                    QFile::remove(fi.absoluteFilePath());
            }

        }
    }
}

void BrowserView::send_marked(QList<BrowserNode *> list)
{
    emit marked_list(list);
}

BrowserView::~BrowserView()
{
    remove_temporary_files();
    set_user_id(-1);
}

void BrowserView::clear()
{
    remove_temporary_files();
    set_user_id(-1);
    QTreeWidget::clear();
    project = 0;
}

void BrowserView::set_project(const QDir & di)
{
    dir = di;
    project = new BrowserPackage(dir.dirName(), (BrowserView *) 0, PROJECT_ID);
    the->addTopLevelItem(project);
    setRootIsDecorated(FALSE);
}

void BrowserView::set_imported_project(const QDir & di,
                                       BrowserPackage * p)
{
    import_dir = di;
    imported_project = p;
}

bool BrowserView::save_as(const QDir & new_dir)
{
    // copy USER temporary files
    QStringList filter;
    filter.append(QString("*_%1.?").arg(user_id()));

    QFileInfoList l = dir.entryInfoList(filter); //[lgfreitas] Since Mr. Pagès uses l again, removing const from l

    if (!l.empty()) {
        QListIterator<QFileInfo> it(l);
        QFileInfo fi;

        while (it.hasNext()) {
            fi = it.next();

            if (!copy_file(&fi, new_dir)) //[lgfreitas] entryInfoList does not return a pointer anymore, but copy_file expects it
                return FALSE;
        }
    }

    // copy non package non temporary files
    filter.clear();
    filter<<"*.??*";
    l = dir.entryInfoList(filter);

    if (!l.empty()) {
        QListIterator<QFileInfo> it(l);
        QFileInfo fi;

        while (it.hasNext()) {
            fi = it.next();

            if ((!fi.fileName().endsWith( "prj", Qt::CaseInsensitive)) &&
                    (!fi.fileName().endsWith("lock",Qt::CaseInsensitive)) &&
                    !copy_file(&fi, new_dir))
                return FALSE;
        }
    }

    // delete old temporary files and rename the project
    remove_temporary_files();
    set_user_id(-1);
    get_project()->set_name(new_dir.dirName());
    dir = new_dir;

    // create new lock
    user_id();

    return TRUE;
}

void BrowserView::select(QTreeWidgetItem * i)
{
    //the->ensureVisible(i);
    the->scrollToItem(i);
    the->setCurrentItem(i/*, TRUE*/);
}

void BrowserView::deselect(QTreeWidgetItem * i)
{
    the->setCurrentItem(i/*, false*/);
}

void BrowserView::force_visible(QTreeWidgetItem * i)
{
    the->scrollToItem(i);
}

BrowserNode * BrowserView::selected_item()
{
    return (BrowserNode *) the->currentItem();
}
void BrowserView::rightPressed(const QPoint &point)
{
    QTreeWidgetItem *item = this->itemAt(point);
    if (item &&
            ((!((BrowserNode *) item)->deletedp()) ||
             (!((BrowserNode *) item->parent())->deletedp())) &&
            !BrowserNode::popupMenuActive()) {	// Qt bug
        BrowserNode::setPopupMenuActive(TRUE);
        ((BrowserNode *) item)->menu();
        BrowserNode::setPopupMenuActive(FALSE);
    }
}
void BrowserView::rightPressed(BrowserNode* node)
{
    BrowserNode *item = node;
    if (item &&
            ((!((BrowserNode *) item)->deletedp()) ||
             (!((BrowserNode *) item->parent())->deletedp())) &&
            !BrowserNode::popupMenuActive()) {	// Qt bug
        BrowserNode::setPopupMenuActive(TRUE);
        ((BrowserNode *) item)->menu();
        BrowserNode::setPopupMenuActive(FALSE);
    }
}

void BrowserView::doubleClick(QTreeWidgetItem * item, int)
{
    UmlWindow::abort_line_construction();

    if (item && !((BrowserNode *) item)->deletedp())
        ((BrowserNode *) item)->open(FALSE);
}

void BrowserView::dragMoveEvent(QDragMoveEvent * e)
{
    if (!BrowserNode::edition_active()) {
        BrowserNode * item = (BrowserNode *)itemAt(e->pos());
        if (item && !((BrowserNode *) item)->deletedp())
            ((BrowserNode *) item)->DragMoveEvent(e);
    }
}

void BrowserView::dropEvent(QDropEvent * e)
{
    if (!BrowserNode::edition_active()) {
        BrowserNode * item = (BrowserNode *)itemAt(e->pos());

        if (item && !((BrowserNode *) item)->deletedp())
            ((BrowserNode *) item)->DropEvent(e);
    }
    //QTreeWidget::dropEvent(e);
}

void BrowserView::dragEnterEvent(QDragEnterEvent *event)
{
    event->setDropAction(Qt::MoveAction);
    event->accept();
    //QTreeWidget::dragEnterEvent(event);
}

void BrowserView::dragLeaveEvent(QDragLeaveEvent *event)
{
    QTreeWidget::dragLeaveEvent(event);
}

void BrowserView::startDrag(Qt::DropActions supportedActions)
{
    /*BrowserNode * item = (BrowserNode *)itemAt(e->pos());

    if (item) {
        UmlDrag * di = new UmlDrag((BrowserNode *) item, this);
        QDrag *drag = new QDrag(this);
        drag->setMimeData(di);
        drag->setPixmap(*(item->pixmap(0)), QPoint(8, 8));
        //drag->dragMove();
        if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
        {

        }
    }*/
    //QTreeWidget::startDrag(supportedActions);
}

void BrowserView::mousePressEvent(QMouseEvent * e)
{
    UmlWindow::abort_line_construction();

    //QPoint p(contentsToViewport(e->pos()));
    QModelIndex indexOfItem = indexAt(e->pos());
    int row = indexOfItem.row();
    int column = indexOfItem.column();
    BrowserNode * i = (BrowserNode *)itemAt(e->pos());

    if (i != 0) {
        // to force update of comment else nothing done
        // when the click is made on the already selected item
        // (but the comment is one of an other element selected
        // in a diagram)
        selected(i);

        if (e->button() == ::Qt::LeftButton) {
            if (!((BrowserNode *) i)->deletedp() && (i != project))
            {
                if (e->modifiers() & ::Qt::ControlModifier)
                {
                    ((BrowserNode *) i)->toggle_mark();
                }
                else if (i->parent()/* ||
                                                           p.x() < header()->cellPos(header()->mapToActual(0))*/) {
                    // if the user clicked into the root decoration of the item, don't try to start a drag!
                    presspos = e->pos();
                    mousePressed = TRUE;
                }
            }
        }
    }
    QTreeView::mousePressEvent(e);
}

void BrowserView::mouseMoveEvent(QMouseEvent * e)
{
    if (mousePressed &&
            ((presspos - e->pos()).manhattanLength() > QApplication::startDragDistance())) {
        mousePressed = FALSE;
        BrowserNode * item = (BrowserNode *)itemAt(e->pos());

        if (item) {
            UmlDrag * di = new UmlDrag((BrowserNode *) item, this);
            QDrag *drag = new QDrag(this);
            drag->setMimeData(di);
            drag->setHotSpot( QPoint(8, 8));
            drag->setPixmap(*(item->pixmap(0)));//, QPoint(8, 8));
            //di->dragMove();
            drag->exec(Qt::CopyAction | Qt::MoveAction);
        }

    }
    //QTreeView::mouseMoveEvent(e);
}

void BrowserView::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = FALSE;
}

void BrowserView::OnGenerateCpp()
{
    QList<BrowserNode*> toGenerate = static_cast<BrowserNode*>(this->currentItem())->get_generation_list();
    for(BrowserNode* node: toGenerate)
    {
        if(!node)
            continue;

        bool preserve = preserve_bodies();


        ToolCom::run((verbose_generation())
                     ? ((preserve) ? "cpp_generator -v -p" : "cpp_generator -v")
                     : ((preserve) ? "cpp_generator -p" : "cpp_generator"),
                     node);
    }
}

void BrowserView::OnGenerateJava()
{
    QList<BrowserNode*> toGenerate = static_cast<BrowserNode*>(this->currentItem())->get_generation_list();
    for(BrowserNode* node: toGenerate)
    {
        if(!node)
            continue;

        bool preserve = preserve_bodies();



        ToolCom::run((verbose_generation())
                     ? ((preserve) ? "java_generator -v -p" : "java_generator -v")
                     : ((preserve) ? "java_generator -p" : "java_generator"),
                     node);
    }
}

void BrowserView::OnGeneratePhp()
{
    QList<BrowserNode*> toGenerate = static_cast<BrowserNode*>(this->currentItem())->get_generation_list();
    for(BrowserNode* node: toGenerate)
    {
        if(!node)
            continue;

        bool preserve = preserve_bodies();


        ToolCom::run((verbose_generation())
                     ? ((preserve) ? "php_generator -v -p" : "php_generator -v")
                     : ((preserve) ? "php_generator -p" : "php_generator"),
                     node);
    }
}

void BrowserView::OnGeneratePython()
{
    QList<BrowserNode*> toGenerate = static_cast<BrowserNode*>(this->currentItem())->get_generation_list();
    for(BrowserNode* node: toGenerate)
    {
        if(!node)
            continue;

        bool preserve = preserve_bodies();

        ToolCom::run((verbose_generation())
                     ? ((preserve) ? "python_generator -v -p" : "python_generator -v")
                     : ((preserve) ? "python_generator -p" : "python_generator"),
                     node);
    }
}

void BrowserView::OnGenerateIdl()
{
    QList<BrowserNode*> toGenerate = static_cast<BrowserNode*>(this->currentItem())->get_generation_list();
    for(BrowserNode* node: toGenerate)
    {
        if(!node)
            continue;

        ToolCom::run((verbose_generation()) ? "idl_generator -v" : "idl_generator", node);
    }
}

void BrowserView::OnUnmarkItem(QString name, int type)
{
    foreach (BrowserNode *node, BrowserNode::marked_list)
        if(node->get_name() == name && node->get_type() == type)
            node->toggle_mark();
}

void BrowserView::OnUnmarkAll()
{
    BrowserNode::unmark_all();
}

void BrowserView::keyPressEvent(QKeyEvent * e)
{
    UmlWindow::abort_line_construction();
    QString s = Shortcut::shortcut(e->key(), e->modifiers());

    if (!s.isEmpty()) {
        e->accept();

        if (s == "Save")
            UmlWindow::save_it();
        else if (s == "Save as")
            UmlWindow::saveas_it();
        else if (s == "Close")
            UmlWindow::do_close();
        else if (s == "Quit")
            UmlWindow::do_quit();
        else if (s == "Browser search")
            UmlWindow::browser_search_it();
        else if (s == "Open project")
            UmlWindow::load_it();
        else {
            BrowserNode * bn = (BrowserNode *) currentItem();

            if (bn != 0) {
                if (s == "Menu")
                    rightPressed(bn);
                else if (s == "Delete") {
                    QApplication::setOverrideCursor(::Qt::WaitCursor);
                    bn->apply_shortcut("Delete");
                    QApplication::restoreOverrideCursor();
                }
                else if(s == "Expand All")
                {
                    bn->expandAll();
                }
                else if(s == "Collapse All")
                {
                    bn->collapseAll();
                }
                else if ((s != "Move left") && (s != "Move right") &&
                         (s != "Move up") && (s != "Move down"))
                    bn->apply_shortcut(s);
                else
                    QTreeWidget::keyPressEvent(e);
            }
        }
    }
    else {
        // no shortcut
        QTreeWidget::keyPressEvent(e);
    }
}

void BrowserView::menu()
{

    if (project != 0) {
        if (BrowserSearchDialog::get() == 0)
            (new BrowserSearchDialog())->show();
        else
        {
            BrowserSearchDialog::get()->show();
            BrowserSearchDialog::get()->raise();
        }
    }
}

void BrowserView::onItemSelected()
{
    if(selectedItems().count())
    {
        QTreeWidgetItem * b = selectedItems().at(0);
        UmlWindow::set_commented((BrowserNode *) b);
    }
}

void BrowserView::selected(BrowserNode * b)
{
    UmlWindow::set_commented((BrowserNode *) b);
}
