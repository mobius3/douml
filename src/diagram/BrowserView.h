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

#ifndef BROWSERVIEW_H
#define BROWSERVIEW_H

//#include <q3listview.h>
#include <qdir.h>
//Added by qt3to4:
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QTreeView>
#include <QTreeWidgetItem>
class QDragEnterEvent;
class QDragMoveEvent;
class QDragLeaveEvent;
class QDropEvent;
class QKeyEvent;

class BrowserNode;
class BrowserPackage;


// in fact it is a singleton => static members (except slots !)
/* [lgfreitas] This class provides the tree view in the left side */
class BrowserView : public QTreeWidget
{
    Q_OBJECT

private:
    static BrowserView * the;
    static BrowserPackage * project;
    static QDir dir;
    static BrowserPackage * imported_project;
    static QDir import_dir;

    QPoint presspos;
    bool mousePressed;

public:
    BrowserView(QWidget * parent = 0);
    virtual ~BrowserView();

    virtual void clear();

    void set_project(const QDir & d);
    bool save_as(const QDir & new_dir);

    static BrowserPackage * get_project() {
        return project;
    }
    static QDir get_dir() {
        return dir;
    }
    static void set_imported_project(const QDir &, BrowserPackage *);
    static BrowserPackage * get_imported_project() {
        return imported_project;
    }
    static QDir get_import_dir() {
        return import_dir;
    }
    static void select(QTreeWidgetItem *);
    static void deselect(QTreeWidgetItem *);
    static BrowserNode * selected_item();
    static void force_visible(QTreeWidgetItem *);
    static void remove_temporary_files();
    void send_marked(QList<BrowserNode*>);



protected:
    virtual void keyPressEvent(QKeyEvent * e) override;

protected slots:
    void onItemSelected();
    void selected(BrowserNode *b);
    void rightPressed(const QPoint &point);
    void rightPressed(BrowserNode* node);
    void doubleClick(QTreeWidgetItem *, int);

    void menu();

    virtual void dragMoveEvent(QDragMoveEvent * e) override;
    virtual void dropEvent(QDropEvent * e) override;
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dragLeaveEvent(QDragLeaveEvent *event) override;
    virtual void startDrag(Qt::DropActions supportedActions) override;




    virtual void mouseMoveEvent(QMouseEvent * e) override;
    virtual void mousePressEvent(QMouseEvent * e) override;
    virtual void mouseReleaseEvent(QMouseEvent * e) override;

public slots:
    void OnGenerateCpp();
    void OnGenerateJava();
    void OnGeneratePhp();
    void OnGeneratePython();
    void OnGenerateIdl();
    void OnUnmarkItem(QString name, int type);
    void OnUnmarkAll();
signals:
    void marked_list(QList<BrowserNode*>);
};

#endif
