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
#include <Q3ValueList>
#include <Q3PopupMenu>
#include <QLabel>
#include <QKeyEvent>
#include <QMainWindow>
#include <QSharedPointer>
#include <QModelIndex>
#include <functional>
//#include "Libs/L_UniversalModels/include/ItemController.h"

class Q3CanvasView;
class QWorkspace;
class QToolBar;
class Q3PopupMenu;
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
class Q3ListViewItem;
class CatalogWidget;
class QShortcut;
class UmlWindow : public QMainWindow
{
    Q_OBJECT

protected:
    static UmlWindow * the;

    QWorkspace * ws = nullptr;
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
    Q3PopupMenu * projectMenu;
    Q3PopupMenu * windowsMenu;
    Q3PopupMenu * toolMenu;
    Q3PopupMenu * langMenu;
    Q3PopupMenu * miscMenu;
    Q3PopupMenu * fontSizeMenu;
    Q3PopupMenu * formatMenu;
    Q3PopupMenu * formatLandscapeMenu;
    QAction* cppAction = nullptr;
    QAction* javaAction = nullptr;
    QAction* phpAction = nullptr;
    QAction* pythonAction = nullptr;
    QAction* idlAction = nullptr;
    QAction* generateLabelAction = nullptr;
    QLabel* generateLabel = nullptr;
    int use_cpp_id;
    int use_java_id;
    int use_php_id;
    int use_python_id;
    int use_idl_id;
    int verbose_gen_id;
    int preserve_bodies_id;
    int add_operation_profile_id;
    int shortcut_id;
    int img_root_dir_id;
    int show_browser_stereotypes_id;
    int completion_id;
    QStringList historic;
    CanvasFormat format;
    QString img_root_dir;
    QSplitter * spl1;
    QSplitter * spl2;
    char style;	// '?' unknown, 'm' = motif, '+' = motif+, 'w' = windows
    QToolButton * prev;
    QToolButton * next;
    QToolButton * tbClipboard = nullptr;
    QToolButton * tbQuickEdit = nullptr;
    Q3ValueList<BrowserNode *> select_historic;
    bool quitConfirmed = false;

public:
    UmlWindow(bool batch);
    virtual ~UmlWindow();

    void load(QString fn, bool forcesaveas = FALSE);
    bool can_close();
    static void set_marked_generation();
    static void set_selected_generation();

    static void set_commented(BrowserNode * bn);
    static void update_comment_if_needed(BrowserNode * bn);
    static void set_message(const QString &);
    static QWorkspace * get_workspace();
    static void clear();
    static void historic_add(QString fn);
    static void historic_forget(BrowserNode *);
    static void save_it();
    static bool saveas_it();
    static void close_it();
    static void do_close();
    static void do_quit();
    static void load_it();
    static void load_it(QString fn);
    static void reload_it();
    static CanvasFormat default_format();
    static void set_default_format(CanvasFormat);
    static QString images_root_dir();
    static void set_images_root_dir(QString);
    static void abort_line_construction();
    static void clear_select_historic();
    static void browser_search_it();
    static void print_it();

protected:
    void init_format_menu(Q3PopupMenu * m, Q3PopupMenu * lm);
    void is_selected(BrowserNode *);
    virtual void closeEvent(QCloseEvent *);
    void save_session();
    void read_session();
    void setup_generator_action_visibility();

private slots:
    void newProject();
    void newFromTemplate();
    void load();
    void save();
    void saveAs();
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
    bool using_cpp();
    bool using_java();
    bool using_php();
    bool using_python();
    bool using_idl();
    void verbose();
    void preserve();
    void addoperationprofile();
    void edit_shortcuts();
    void edit_env();
    void edit_image_root_dir();

    void motif_style();
    void motifplus_style();
    //void sgi_style();
    //void cde_style();
    void windows_style();

    void show_stereotypes();

    void do_completion();

    void about();
    void aboutQt();
    void help();

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
    void run_tool(int param);
    void tool_settings();
    void import_tool_settings();
    void plug_out_upgrade();

    void comment_changed();
    void preferred_geometry();
    void close_all_windows();

    void toolMenuAboutToShow();
    void projectMenuAboutToShow();
    void historicActivated(int id);

    void langMenuAboutToShow();

    void miscMenuAboutToShow();

    void fontSizeMenuAboutToShow();
    void setFontSize(int);

    void formatMenuAboutToShow();
    void setFormat(int);

    void windowsMenuAboutToShow();
    void windowsMenuActivated(int id);
    void dialogsMenuActivated(int id);

    virtual void keyPressEvent(QKeyEvent * e);


public slots:
    void whats_this() const;
    void OnPickSelectionFromItem(const QModelIndex&,const QModelIndex& );
    void OnChooseQuickEditMode(Q3ListViewItem *item);
    void OnShowQuickEdit();
    void OnCallClipboardMenu();
    //void OnCallQuickEdit();

};

extern QString template_project();
extern void set_template_project(QString s);

#endif
