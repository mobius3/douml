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
#include <qmessagebox.h>
#include <QMenu>
#include <qmenubar.h>
#include <QFileDialog>
#include <qfile.h>
#include <qdir.h>
#include <QTextStream>
#include <QPixmap>
#include "SynchroWindow.h"
#include "BrowserView.h"
#include "BrowserNode.h"
#include "SynchroDialog.h"
#include "myio.h"

SynchroWindow * SynchroWindow::the;

SynchroWindow::SynchroWindow() : QMainWindow(0)
{
    setAttribute(Qt::WA_DeleteOnClose);
    the = this;
    setWindowTitle("Project synchro");

    QMenu * menu;
    QPixmap pixmap;

    //menu = new QMenu(this);
    menu = menuBar()->addMenu("&Project");

    // open

#include "fileopen.xpm"
    pixmap = QPixmap(fileopen);
    menu->addAction(pixmap, "&Open", this,
                     SLOT(load()), Qt::CTRL + Qt::Key_O);

    // quit

    menu->addAction("&Quit", this, SLOT(quit()), Qt::CTRL + Qt::Key_Q);

    // synchronize

    menu->addSeparator();
    menu->addAction("&Synchonize", this, SLOT(synchronize()), Qt::CTRL + Qt::Key_S);

    // style

    //menu = new Q3PopupMenu(this);
    menu = menuBar()->addMenu("&Style");

#if !defined(QT_NO_STYLE_MOTIF)
    menu->addAction("Motif", this, SLOT(motif_style()));
#endif
#if !defined(QT_NO_STYLE_MOTIFPLUS)
    menu->addAction("MotifPlus", this, SLOT(motifplus_style()));
#endif
    menu->addAction("Windows", this, SLOT(windows_style()));

    // help & about

    menuBar()->addSeparator();
    //menu = new Q3PopupMenu(this);
    menu = menuBar()->addMenu("&Help");

    menu->addAction("&About", this, SLOT(about()), Qt::Key_F1);
    menu->addAction("About&Qt", this, SLOT(aboutQt()));

    //
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    hbox = new QHBoxLayout(central);
    //setCentralWidget(hbox);
}

SynchroWindow::~SynchroWindow()
{
    foreach (BrowserView * browser, browsers) {
        browser->close();
    }

}

QString my_baseName(QFileInfo & fi)
{
    QString fn = fi.fileName();
    int index = fn.lastIndexOf('.');

    return (index == -1)
           ? fn
           : fn.left(index);
}

void SynchroWindow::load(QString path)
{
    QFileInfo fi(path);

    if (!fi.exists()) {
        QMessageBox::critical(0, "Synchro project",
                              path + " doesn't exist");
        return;
    }

    QDir dir(fi.path());
    BrowserView * browser;

    path = dir.canonicalPath();
    foreach (BrowserView * browser, browsers) {

        if (browser->get_dir().canonicalPath() == path) {
            QMessageBox::critical(0, "Project synchro",
                                  "Project instance already read");
            return;
        }
    }

    if (has_backup_files(dir))
        QMessageBox::critical(0, "Synchro project", path + " contains .bak files");
    else if (! dir.mkdir("all.lock"))
        QMessageBox::critical(0, "Synchro project",
                              (dir.exists("all.lock"))
                              ? "\
The project is already locked by 'Project control' or 'Project syncho'\n\
(the directory '" + path + "/all.lock' exists)"
                              : "Can't create directory '" + path + "/all.lock'");
    else {
        const QFileInfoList l = dir.entryInfoList(QStringList()<<"*.lock");

        if (!l.isEmpty()) {
            //Q3PtrListIterator<QFileInfo> it(*l);
            //QFileInfo * pfi;
            QString ids;
            /*
            while ((pfi = it.current()) != 0) {
                if (pfi->isDir() && (my_baseName(*pfi) != "all"))
                    ids += " " + my_baseName(*pfi);

                ++it;
            }*/
            foreach (QFileInfo fi, l) {
                if (fi.isDir() && (my_baseName(fi) != "all"))
                    ids += " " + my_baseName(fi);
            }

            if (! ids.isEmpty()) {
                QMessageBox::critical(0, "Synchro project",
                                      "The project " + path + " is edited by the users having these IDs :" + ids);
                dir.rmdir("all.lock");
                return;
            }
        }

        QVBoxLayout * vbox = new QVBoxLayout();
        hbox->addLayout(vbox);
        BrowserView * browser = new BrowserView(this);
        vbox->addWidget(browser);

        QApplication::setOverrideCursor(Qt::WaitCursor);
        browser->set_project(dir);

        bool r = browser->get_project()->load(dir);

        QApplication::restoreOverrideCursor();

        if (! r) {
            browser->close();
            delete vbox;
            // note : all.lock will be deleted by BrowserView
        }
        else {
            if (browsers.isEmpty())
                project_name = fi.fileName();

#if 0
            vbox->show();
#endif
            browsers.append(browser);
        }
    }
}

void SynchroWindow::load()
{   
    QString path = QFileDialog::getOpenFileName(this, QString(), (project_name.isEmpty())
                                                ? "*.prj"
                                                : project_name);


    if (! path.isEmpty()) {
        load(path);

        if (browsers.count() > 1)
            BrowserView::update(browsers);
    }
}

// prog removed from argc & argv
void SynchroWindow::load(int argc, char ** argv)
{
    // check it is the same project
    QString name;
    int index;

    for (index = 0; index < argc; index += 1) {
        QFileInfo fi(argv[index]);

        if (!fi.exists()) {
            QMessageBox::critical(0, "Project synchro",
                                  argv[index] + QString(" doesn't exist"));
            return;
        }

        if (!fi.fileName().endsWith(".prj")) {
            QMessageBox::critical(0, "Project synchro",
                                  argv[index] + QString(" is not a project"));
            return;
        }

        if (name.isEmpty())
            name = my_baseName(fi);
        else if (my_baseName(fi) != name) {
            QMessageBox::critical(0, "Project synchro", "not the same project");
            return;
        }
    }

    // all is ok, load them
    for (index = 0; index < argc; index += 1)
        load(argv[index]);

    if (browsers.count() > 1)
        BrowserView::update(browsers);
}

void SynchroWindow::quit()
{

    foreach (BrowserView * browser, browsers) {
        browser->close();
    }

    QApplication::exit(0);
}

void SynchroWindow::abort()
{
    the->quit();
}

void SynchroWindow::synchronize()
{
    if (browsers.count() > 1) {
        SynchroDialog d(browsers);

        if (d.exec() == QDialog::Accepted) {
            QMessageBox::information(0, "Project synchro", "synchronization done");
            quit();
        }
    }
}

void SynchroWindow::motif_style()
{
#if !defined(QT_NO_STYLE_MOTIF)
    QApplication::setStyle("motif");
#endif
}

void SynchroWindow::motifplus_style()
{
#if !defined(QT_NO_STYLE_MOTIFPLUS)
    QApplication::setStyle("motifPlus");
#endif
}

void SynchroWindow::windows_style()
{
#ifndef QT_NO_STYLE_WINDOWS
    QApplication::setStyle("windows");
#endif
}

void SynchroWindow::about()
{
    QMessageBox::about(this, "Project synchro", "<p>Version <b>1.2.4</b></p>");
}

void SynchroWindow::aboutQt()
{
    QMessageBox::aboutQt(this, "Project synchro");
}
