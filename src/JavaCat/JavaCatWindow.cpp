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
#include <q3popupmenu.h>
#include <qmenubar.h>
#include <q3toolbar.h>
#include <qtoolbutton.h>
#include <qsplitter.h>
#include <qwindowsstyle.h>
#include <qmotifstyle.h>
//#include <qmotifplusstyle.h>
#include <q3whatsthis.h>
#include <q3filedialog.h>
#include <qfile.h>
#include <qdir.h>
#include <qdatastream.h>
#include <QTextStream>
//Added by qt3to4:
#include "misc/mystr.h"
#include <Q3ValueList>
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

JavaCatWindow * JavaCatWindow::the;

const char * OpenText = "";
const char * SaveText = "";
const char * ScanText =
    "To add the <i>java classes</i> defined under the choosen directory.";
const char * SearchText = "To search an item in the <i>browser</i>.";
const char * UpText = "To select the <i>browser</i> current item's parent.";
const char * LeftText = "Go to previous selected <i>class</i>";
const char * RightText = "Go to next selected <i>class</i>";

JavaCatWindow::JavaCatWindow() : Q3MainWindow(0, "Java Catalog", Qt::WDestructiveClose)
{
    the = this;
    setCaption("Java Catalog");
    commented = 0;

    Q3PopupMenu * menu;
    QPixmap pixmap;

    Q3ToolBar * tools = new Q3ToolBar(this, "operations");

    addToolBar(tools, "Operations", Qt::DockTop, TRUE);

    menu = new Q3PopupMenu(this);
    menuBar()->insertItem("&File", menu);

    pixmap = QPixmap(fileopen);
    Q3WhatsThis::add(new QToolButton(pixmap, "Open", QString(),
                                     this, SLOT(load()), tools, "open"),
                     OpenText);
    menu->setWhatsThis(menu->insertItem(pixmap, "&Open", this,
                                        SLOT(load()), Qt::CTRL + Qt::Key_O),
                       OpenText);

    pixmap = QPixmap(filesave);
    Q3WhatsThis::add(new QToolButton(pixmap, "Save", QString(),
                                     this, SLOT(save()), tools, "save"),
                     SaveText);
    menu->setWhatsThis(menu->insertItem(pixmap, "&Save", this,
                                        SLOT(save()), Qt::CTRL + Qt::Key_S),
                       SaveText);

    menu->insertSeparator();
    pixmap = QPixmap(::scan);
    Q3WhatsThis::add(new QToolButton(pixmap, "Scan", QString(),
                                     this, SLOT(scan()), tools, "scan"),
                     ScanText);
    menu->setWhatsThis(menu->insertItem(pixmap, "S&can", this,
                                        SLOT(scan()), Qt::CTRL + Qt::Key_C),
                       ScanText);

    menu->insertSeparator();
    menu->insertItem("&Quit", this, SLOT(quit()), Qt::CTRL + Qt::Key_Q);

    menu = new Q3PopupMenu(this);
    menuBar()->insertItem("&Browse", menu);

    pixmap = QPixmap(browsersearch);
    Q3WhatsThis::add(new QToolButton(pixmap, "Search", QString(),
                                     this, SLOT(browser_search()), tools, "search"),
                     SearchText);
    menu->setWhatsThis(menu->insertItem(pixmap, "&Search", this,
                                        SLOT(browser_search()), Qt::CTRL + Qt::Key_S),
                       SearchText);

    pixmap = QPixmap(left_xpm);
    Q3WhatsThis::add(new QToolButton(pixmap, "Back", QString(),
                                     this, SLOT(historic_back()),
                                     tools, "back"),
                     LeftText);

    pixmap = QPixmap(right_xpm);
    Q3WhatsThis::add(new QToolButton(pixmap, "Forward", QString(),
                                     this, SLOT(historic_forward()),
                                     tools, "forward"),
                     RightText);

    (void)Q3WhatsThis::whatsThisButton(tools);

    //

    menu = new Q3PopupMenu(this);
    menuBar()->insertItem("&Style", menu);

#if !defined(QT_NO_STYLE_MOTIF)
    menu->insertItem("Motif", this, SLOT(motif_style()));
#endif
#if !defined(QT_NO_STYLE_MOTIFPLUS)
    menu->insertItem("MotifPlus", this, SLOT(motifplus_style()));
#endif
    menu->insertItem("Windows", this, SLOT(windows_style()));

    //

    menuBar()->insertSeparator();
    menu = new Q3PopupMenu(this);
    menuBar()->insertItem("&Help", menu);

    menu->insertItem("&About", this, SLOT(about()), Qt::Key_F1);
    menu->insertItem("About&Qt", this, SLOT(aboutQt()));
    menu->insertSeparator();
    menu->insertItem("What's This", this, SLOT(whatsThis()), Qt::SHIFT + Qt::Key_F1);

    //

    spl = new QSplitter(Qt::Vertical, this, "spl");

    browser = new BrowserView(spl);
    comment = new CommentView(spl);

    connect(comment, SIGNAL(refer(const QString &)),
            browser, SLOT(refer(const QString &)));

    spl->moveToFirst(browser);

    Q3ValueList<int> lsz = spl->sizes();
    int h = lsz.first() + lsz.last();

    lsz.first() = (h * 3) / 4;
    lsz.last() = h - lsz.first();

    spl->setSizes(lsz);

    spl->setResizeMode(comment, QSplitter::KeepSize);
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
    QString here = QDir::currentDirPath();
    QString start;

    // note : QFile fp(QDir::home().absFilePath(".doumlcat")) doesn't work
    // if the path contains non latin1 characters, for instance cyrillic !
    QString s = QDir::home().absFilePath(".doumlcat");
    FILE * fp = fopen((const char *) s, "r");
















    if (fp != 0) {
        char line[512];

        if (fgets(line, sizeof(line) - 1, fp) != 0) {
            remove_crlf(line);
            start = line;
        }

        fclose(fp);
    }

    QString path =
        Q3FileDialog::getOpenFileName(start, "*.cat", this);

    if (! path.isEmpty()) {
        QApplication::setOverrideCursor(Qt::waitCursor);

        QFile f(path);

        if (f.open(QIODevice::ReadOnly)) {
            if ((fp = fopen((const char *) s, "w")) != 0) {
                fwrite((const char *) path, 1, path.length(), fp);
                fputc('\n', fp);
                fclose(fp);
            }

            QDataStream dt(&f);

            Package::get_root()->restore_children(dt);
            Package::get_root()->setOpen(TRUE);
        }

        QApplication::restoreOverrideCursor();
    }

    QDir::setCurrent(here);
}

void JavaCatWindow::save()
{
    QString path =
        Q3FileDialog::getSaveFileName(QString(), "*.cat", this);

    if (! path.isEmpty()) {
        QApplication::setOverrideCursor(Qt::waitCursor);

        if (path.right(4).upper() != ".CAT")
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
    QApplication::setStyle(new QMotifStyle);
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
    QApplication::setStyle(new QWindowsStyle);
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

    Q3ValueList<int> sz = the->spl->sizes();

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
