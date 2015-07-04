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

#include <stdlib.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <QToolBar>
#include <qtoolbutton.h>
#include <qsplitter.h>
//#include <qwindowsstyle.h>
//#include <qmotifstyle.h>
//#include <qmotifplusstyle.h>
#include <qwhatsthis.h>
#include <qfiledialog.h>
#include <qfile.h>
#include <qdir.h>
#include <qdatastream.h>
#include <QTextStream>
//Added by qt3to4:
#include "misc/mystr.h"
#include <QList>
#include <QPixmap>

#include "JavaCatWindow.h"
#include "BrowserView.h"
#include "Package.h"
#include "BrowserSearchDialog.h"
#include "CommentView.h"
#include "UmlCom.h"
#include "Class.h"

#include "filesave.xpm"
#include "fileopen.xpm"
#include "browsersearch.xpm"
#include "scan.xpm"
#include "left_xpm.xpm"
#include "right_xpm.xpm"
#include "menufactory.h"

JavaCatWindow * JavaCatWindow::the;

const char * OpenText = "";
const char * SaveText = "";
const char * ScanText =
    "To add the <i>java classes</i> defined under the choosen directory.";
const char * SearchText = "To search an item in the <i>browser</i>.";
const char * UpText = "To select the <i>browser</i> current item's parent.";
const char * LeftText = "Go to previous selected <i>class</i>";
const char * RightText = "Go to next selected <i>class</i>";

JavaCatWindow::JavaCatWindow() : QMainWindow(0)
{
    setAttribute(Qt::WA_DeleteOnClose);
    the = this;
    setWindowTitle("Java Catalog");
    commented = 0;

    QMenu * menu;
    QPixmap pixmap;
    QAction *action;

    QToolBar * tools = new QToolBar("operations", this);

    addToolBar(Qt::TopToolBarArea, tools);

    //menu = new QMenu(this);
    menu = menuBar()->addMenu("&File");

    pixmap = QPixmap(fileopen);
    action = tools->addAction(pixmap,"Open", this, SLOT(load()));
    action->setWhatsThis(OpenText);
    action->setToolTip("open");


    action = menu->addAction(pixmap,"&Open", this, SLOT(load()));
    action->setWhatsThis(OpenText);
    action->setToolTip("open");
    action->setShortcut(Qt::CTRL + Qt::Key_O);

    pixmap = QPixmap(filesave);
    action = tools->addAction(pixmap,"Save", this, SLOT(save()));
    action->setWhatsThis(SaveText);
    action->setToolTip("save");


    action = menu->addAction(pixmap,"&Save", this, SLOT(save()));
    action->setWhatsThis(SaveText);
    action->setToolTip("save");
    action->setShortcut(Qt::CTRL + Qt::Key_S);


    menu->addSeparator();

    pixmap = QPixmap(::scan);
    action = tools->addAction(pixmap,"Scan", this, SLOT(save()));
    action->setWhatsThis(ScanText);
    action->setToolTip("scan");

    action = menu->addAction(pixmap,"S&can", this, SLOT(save()));
    action->setWhatsThis(ScanText);
    action->setToolTip("scan");
    action->setShortcut(Qt::CTRL + Qt::Key_C);



    menu->addSeparator();


    action = menu->addAction("&Quit", this, SLOT(quit()), Qt::CTRL + Qt::Key_Q);

    //menu = new QMenu(this);
    menu = menuBar()->addMenu("&Browse");

    pixmap = QPixmap(browsersearch);
    action = tools->addAction(pixmap,"Search", this, SLOT(browser_search()));
    action->setWhatsThis(SearchText);
    action->setToolTip("Search");

    action = menu->addAction(pixmap,"&Search", this, SLOT(browser_search()));
    action->setWhatsThis(SearchText);
    action->setToolTip("Search");
    action->setShortcut(Qt::CTRL + Qt::Key_S);


    pixmap = QPixmap(left_xpm);
    action = tools->addAction(pixmap,"Back", this, SLOT(historic_back()));
    action->setWhatsThis(LeftText);
    action->setToolTip("back");

    pixmap = QPixmap(right_xpm);
    action = tools->addAction(pixmap,"Forward", this, SLOT(historic_forward()));
    action->setWhatsThis(RightText);
    action->setToolTip("forward");

    action = tools->addAction(QApplication::style()->standardIcon(QStyle::SP_TitleBarContextHelpButton).pixmap(200,2000), "Whats's this?",
                               this, SLOT(whats_this()));



    //(void)QWhatsThis::whatsThisButton(tools);

    //

    //menu = new QMenu(this);
    menu = menuBar()->addMenu("&Style");

#if !defined(QT_NO_STYLE_MOTIF)
    menu->addAction("Motif", this, SLOT(motif_style()));
#endif
#if !defined(QT_NO_STYLE_MOTIFPLUS)
    menu->addAction("MotifPlus", this, SLOT(motifplus_style()));
#endif
    menu->addAction("Windows", this, SLOT(windows_style()));

    //

    menuBar()->addSeparator();
    //menu = new QMenu(this);
    menu = menuBar()->addMenu("&Help");

    menu->addAction("&About", this, SLOT(about()), Qt::Key_F1);
    menu->addAction("About&Qt", this, SLOT(aboutQt()));
    menu->addSeparator();
    menu->addAction("What's This", this, SLOT(whatsThis()), Qt::SHIFT + Qt::Key_F1);

    //

    spl = new QSplitter(Qt::Vertical, this/*, "spl"*/);

    browser = new BrowserView(spl);
    comment = new CommentView(spl);

    connect(comment, SIGNAL(refer(const QString &)),
            browser, SLOT(refer(const QString &)));

    spl->addWidget(browser);

    QList<int> lsz = spl->sizes();
    int h = lsz.first() + lsz.last();

    lsz.first() = (h * 3) / 4;
    lsz.last() = h - lsz.first();

    spl->setSizes(lsz);

    //spl->setResizeMode(comment, QSplitter::KeepSize);
    setCentralWidget(spl);
}

void remove_crlf(char * s)
{
    int len = strlen(s);

    if (len != 0) {
        if (s[len - 1] == '\n')
            s[--len] = 0;

        if ((len != 0) && (s[len - 1] == '\r'))
            s[len - 1] = 0;
    }
}

void JavaCatWindow::load()
{
    QString here = QDir::currentPath();
    QString start;

    // note : QFile fp(QDir::home().absFilePath(".doumlcat")) doesn't work
    // if the path contains non latin1 characters, for instance cyrillic !
    QString s = QDir::home().absoluteFilePath(".doumlcat");
    FILE * fp = fopen((const char *) s.toLatin1().constData(), "r");
















    if (fp != 0) {
        char line[512];

        if (fgets(line, sizeof(line) - 1, fp) != 0) {
            remove_crlf(line);
            start = line;
        }

        fclose(fp);
    }

    QString path =
        QFileDialog::getOpenFileName(this, "", start, "*.cat");

    if (! path.isEmpty()) {
        QApplication::setOverrideCursor(Qt::WaitCursor);

        QFile f(path);

        if (f.open(QIODevice::ReadOnly)) {
            if ((fp = fopen((const char *) s.toLatin1().constData(), "w")) != 0) {
                fwrite((const char *) path.toLatin1().constData(), 1, path.length(), fp);
                fputc('\n', fp);
                fclose(fp);
            }

            QDataStream dt(&f);

            Package::get_root()->restore_children(dt);
            Package::get_root()->setExpanded(TRUE);
        }

        QApplication::restoreOverrideCursor();
    }

    QDir::setCurrent(here);
}

void JavaCatWindow::save()
{
    QString path =
        QFileDialog::getSaveFileName(this, QString(), QString(), "*.cat");

    if (! path.isEmpty()) {
        QApplication::setOverrideCursor(Qt::WaitCursor);

        if (path.right(4).toUpper() != ".CAT")
            path += ".cat";

        QFile f(path);

        if (f.open(QIODevice::WriteOnly)) {
            QDataStream dt(&f);

            Package::get_root()->backup_children(dt);
        }

        QApplication::restoreOverrideCursor();
    }
}

void JavaCatWindow::scan()
{
    int n;

    Package::scan_dir(n);
    UmlCom::message("");
}

void JavaCatWindow::browser_search()
{
    BrowserSearchDialog dialog(QCursor::pos());

    dialog.exec();
}

void JavaCatWindow::historic_back()
{
    Class::historic_back();
}

void JavaCatWindow::historic_forward()
{
    Class::historic_forward();
}

void JavaCatWindow::quit()
{
    QApplication::exit(0);
}

void JavaCatWindow::motif_style()
{
#if !defined(QT_NO_STYLE_MOTIF)
    QApplication::setStyle("motif");
#endif
}

void JavaCatWindow::motifplus_style()
{
//#if !defined(QT_NO_STYLE_MOTIFPLUS)
#if 0
    QApplication::setStyle(new QMotifPlusStyle);
#endif
}

void JavaCatWindow::windows_style()
{
#ifndef QT_NO_STYLE_WINDOWS
    QApplication::setStyle("windows");
#endif
}

void JavaCatWindow::about()
{
    QMessageBox::about(this, "Java Catalog", "<p>release <b>2.14.1</b></p>");
}

void JavaCatWindow::aboutQt()
{
    QMessageBox::aboutQt(this, "Java Catalog");
}

void JavaCatWindow::trace(QString s)
{
    the->comment->append(s);
    the->comment->update();

    // sometimes the contains/scrollbar does not show all
    // change the split position to force correct updating

    QList<int> sz = the->spl->sizes();

    if (sz[1] & 1) {
        sz[0] += 1;
        sz[1] -= 1;
    }
    else {
        sz[0] -= 1;
        sz[1] += 1;
    }

    the->spl->setSizes(sz);
}

void JavaCatWindow::trace(WrapperStr s)
{
    trace(s);
}

void JavaCatWindow::clear_trace()
{
    the->comment->setText(QString());
}
void JavaCatWindow::whats_this() const
{
    QWhatsThis::enterWhatsThisMode();
}
