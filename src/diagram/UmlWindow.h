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

#ifndef UMLWINDOW_H
#define UMLWINDOW_H

///#include <q3mainwindow.h>
#include <qstringlist.h>
//Added by qt3to4:
#include <QCloseEvent>
//#include <QList>
////#include <QMenu>
#include <QLabel>
#include <QKeyEvent>
#include <QMainWindow>
#include <QSharedPointer>
#include <QModelIndex>
#include <functional>
#include <QMdiArea>
//#include "Libs/L_UniversalModels/include/ItemController.h"

class QGraphicsView;
class QWorkspace;
class QToolBar;
class QSplitter;
class QToolButton;

class BrowserView;
class BrowserNode;
class MultiLineEdit;
class QuickEdit;

#include "UmlEnum.h"

// singleton

/* This class seems to be responsible for the main Project, with Open,
 * Save, Close, etc... It is the main window */
class QTreeView;
class QTabWidget;
class TreeItemInterface;
class TreeModel;
class QLineEdit;
class QTreeWidgetItem;
class CatalogWidget;
class QShortcut;
class UmlWindow : public QMainWindow
{
    Q_OBJECT

protected:
    static UmlWindow * the;

    QMdiArea  * ws = nullptr;

    BrowserView * browser = nullptr;
    BrowserView * dummyBrowser = nullptr;
    // perverted stuff
    QSplitter* splTreeTab = nullptr;
    CatalogWidget* wdgCatalog = nullptr;
    void SetupTreeModel();
    void SetupTreeController();
    void PerformFiltering();
    QList<std::function<bool (TreeItemInterface *)> > CreateCheckList();

    QuickEdit* quickEdit = nullptr;
    QShortcut* sh1;
    // end of perverted stuff
    MultiLineEdit * comment;
    BrowserNode * commented;	// the commented object
    QToolBar * projectTools;
    QMenu * projectMenu;
    QMenu * windowsMenu;
    QMenu * toolMenu;
	bool isToolMenuLoaded;
    QMenu * langMenu;
    QMenu * miscMenu;
    QMenu * fontSizeMenu;
    QMenu * formatMenu;
    QMenu * formatLandscapeMenu;
    QAction* cppAction = nullptr;
    QAction* javaAction = nullptr;
    QAction* phpAction = nullptr;
    QAction* pythonAction = nullptr;
    QAction* idlAction = nullptr;
    QAction* generateLabelAction = nullptr;
    QLabel* generateLabel = nullptr;
    QAction* use_cpp_id;
    QAction* use_java_id;
    QAction* use_php_id;
    QAction* use_python_id;
    QAction* use_idl_id;
    QAction*  verbose_gen_id;
    QAction*  preserve_bodies_id;
    QAction*  add_operation_profile_id;
    QAction*  shortcut_id;
    QAction*  img_root_dir_id;
    QAction*  show_browser_stereotypes_id;
    QAction*  completion_id;
    QStringList historic;

    CanvasFormat format;
    QString img_root_dir;
    QSplitter * spl1;
    QSplitter * spl2;
    QString style;
    QToolButton * prev;
    QToolButton * next;
    QToolButton * tbClipboard = nullptr;
    QToolButton * tbQuickEdit = nullptr;
    QList<BrowserNode *> select_historic;
    bool quitConfirmed = false;
public:
    UmlWindow(bool batch);
    virtual ~UmlWindow();


    bool can_close();
    static void set_marked_generation();
    static void set_selected_generation();

    static void set_commented(BrowserNode * bn);
    static void update_comment_if_needed(BrowserNode * bn);
    static void set_message(const QString &);
    static void clear();
    static void historic_forget(BrowserNode *);
    static void save_it();
    static bool saveas_it();
    static void do_close();
    static void do_quit();
    static void historic_add(QString fn);
    static void close_it();
    void load(QString fn, bool forcesaveas = FALSE);
    static QMdiArea * get_workspace();
    static void load_it();
    static void load_it(QString fn);
    static void reload_it();
    static void abort_line_construction();
    static void set_default_format(CanvasFormat);
    static CanvasFormat default_format();
    static QString images_root_dir();
    static void set_images_root_dir(QString);
    static void clear_select_historic();

    static void browser_search_it();
    static void print_it();
protected:
    void init_format_menu(QMenu * m, QMenu * lm);

    void is_selected(BrowserNode *);
    virtual void closeEvent(QCloseEvent *) override;
    void save_session();

    void setup_generator_action_visibility();
    void read_session();
private slots:
    void saveAs();
    void save();
    void newProject();
    void newFromTemplate();
    void load();


    void print();
    void close();
    void quit();
    void browser_search();
    void next_select();
    void prev_select();

    void edit_gen_settings();
    void edit_stereotypes();
    void edit_class_settings();
    void edit_drawing_settings();

    void use_cpp();
    void use_java();
    void use_php();
    void use_python();
    void use_idl();

    void verbose();
    void preserve();
    void addoperationprofile();
    void edit_shortcuts();
    bool using_cpp();
    bool using_java();
    bool using_php();
    bool using_python();
    bool using_idl();
    void edit_env();
    void setApplicationStyleSlot();
    void show_stereotypes();
    void about();
    void aboutQt();
    void help();

     void edit_image_root_dir();
    void do_completion();



    void show_trace();
    void cpp_generate();
    void java_generate();
    void php_generate();
    void python_generate();
    void idl_generate();
    void java_catalog();
    //void doc_generate();
    void cpp_reverse();
    void cpp_roundtrip();
    void java_reverse();
    void java_roundtrip();
    void php_reverse();
    void python_reverse();
    void cpp_roundtripbody();
    void java_roundtripbody();
    void php_roundtripbody();
    void python_roundtripbody();
    void plug_out_upgrade();

    void run_tool();
    void tool_settings();
    void import_tool_settings();


    void preferred_geometry();
    void close_all_windows();

    void comment_changed();
    void historicActivated();
    void projectMenuAboutToShow();
    void toolMenuAboutToShow();

    void langMenuAboutToShow();

    void miscMenuAboutToShow();

    void fontSizeMenuAboutToShow();
    void setFontSize();

    void formatMenuAboutToShow();
    void setFormat();
    void windowsMenuAboutToShow();
    void windowsMenuActivated();
    void dialogsMenuActivated();
    virtual void keyPressEvent(QKeyEvent * e) override;
public slots:
    void whats_this() const;
    void OnPickSelectionFromItem(const QModelIndex&,const QModelIndex& );
    void OnChooseQuickEditMode(QTreeWidgetItem *item, QTreeWidgetItem *old);
    void OnShowQuickEdit();
    void OnCallClipboardMenu();
private:
    void setApplicationStyle(QString s);
    //void OnCallQuickEdit();

};

extern QString template_project();
extern void set_template_project(QString s);

#endif
