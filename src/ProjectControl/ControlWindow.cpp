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
#include <QToolBar>
#include <qtoolbutton.h>
#include <qstatusbar.h>
#include <qfile.h>
#include <qdir.h>
#include <QTextStream>
#include <QPixmap>

#include "ControlWindow.h"
#include "BrowserView.h"
#include "BrowserSearchDialog.h"
#include "UserDialog.h"
#include "myio.h"

#include "fileopen.xpm"
#include "browsersearch.xpm"
#include "actor.xpm"
#include <QFileDialog>
#include <QWhatsThis>
#include <QSettings>
#include <QTextCodec>
ControlWindow * ControlWindow::the;

const char * OpenText = "To load a project";
const char * SearchText = "To search a <i>package</i> in the <i>browser</i>.";
const char * ChangeUserText = "To be an other user.";
QToolButton *
CreateToolButton(
        QPixmap icon,
        QWidget * receiver,
        const char * boundslot,
        QToolBar * parent,
        QString shown,
        QString whatsThis)
{
    QToolButton * newButton = new QToolButton();
    QObject::connect(newButton, SIGNAL(clicked()), receiver, boundslot);
    newButton->setIcon(icon);
    newButton->setText(shown);
    newButton->setToolTip(shown);
    newButton->setMinimumSize(30, 30);
    newButton->setWhatsThis(whatsThis);
    parent->addWidget(newButton);
    return newButton;
}

ControlWindow::ControlWindow(QDir & homeDir) : QMainWindow(0)
{
    setAttribute(Qt::WA_DeleteOnClose);
    the = this;
    setWindowTitle("Project control");

    QMenu * menu;
    QPixmap pixmap;
    QAction *action;

    QToolBar * tools = new QToolBar("operations", this);

    addToolBar(Qt::TopToolBarArea, tools);

    menu = new QMenu(this);
    menu->setTitle("P&roject");
    menuBar()->addMenu(menu);

    // open

    pixmap = QPixmap(fileopen);
    QToolButton *button = CreateToolButton(pixmap,this, SLOT(load()), tools, "Open", OpenText);
    //Q3WhatsThis::add(new QToolButton(pixmap, "Open", QString(),
    //                               this, SLOT(load()), tools, "open"),
    //             OpenText);

    action = menu->addAction(pixmap, "&Open", this,
                             SLOT(load()), Qt::CTRL + Qt::Key_O);
    action->setWhatsThis(OpenText);
    //    menu->setWhatsThis(menu->insertItem(pixmap, "&Open", this,
    //                                        SLOT(load()), Qt::CTRL + Qt::Key_O),
    //                       OpenText);


    // change user
    pixmap = QPixmap(actor);


    button = CreateToolButton(pixmap,this, SLOT(change_user()), tools, "Who", ChangeUserText);

    //    Q3WhatsThis::add(new QToolButton(pixmap, "Who", QString(),
    //                                     this, SLOT(change_user()), tools, "Change user"),
    //                     ChangeUserText);
    action  = menu->addAction(pixmap, "Change &user", this,
                              SLOT(change_user()), Qt::CTRL + Qt::Key_C);
    action->setWhatsThis(ChangeUserText);

    // search

    pixmap = QPixmap(browsersearch);
    button = CreateToolButton(pixmap,this, SLOT(browser_search()), tools, "Search", SearchText);
    //    Q3WhatsThis::add(new QToolButton(pixmap, "Search", QString(),
    //                                     this, SLOT(browser_search()), tools, "search"),
    //                     SearchText);
    action = menu->addAction(pixmap, "&Search", this,
                             SLOT(browser_search()), Qt::CTRL + Qt::Key_S);
    action->setWhatsThis(SearchText);

    // quit & what

    action = menu->addAction("&Quit", this, SLOT(quit()), Qt::CTRL + Qt::Key_Q);
    QAction *whatsThisAction = QWhatsThis::createAction();
    tools->addAction(whatsThisAction);
    //(void)Q3WhatsThis::whatsThisButton(tools);

    // historic

    // note : QFile fp(QDir::home().absFilePath(".douml")) doesn't work
    // if the path contains non latin1 characters, for instance cyrillic !
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "DoUML", "settings");
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    settings.beginGroup("Recent_Files");
    for(int i = 1; i <= 10; ++i)
    {
        const QString line = settings.value(tr("File%1").arg(i)).toString();
        if(!line.isEmpty())
        {
            historic.append(line);
        }
        else
        {
            break;
        }
    }
    menu->addSeparator();
    QString whats = QString("to open this project.<br><br>The historic is saved in <i>")
            + homeDir.absoluteFilePath(".douml") + "</i>";

    for (int i = 0; i < int(historic.count()); i += 1) {
        action = menu->addAction(historic.at(i),
                                 this, SLOT(historicActivated()));
        action->setData(i);
        action->setWhatsThis(whats);
        //menu->setItemParameter(id, i);
        //menu->setWhatsThis(id, whats);
    }

    // style


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
    menu = menuBar()->addMenu("&Help");

    menu->addAction("&About", this, SLOT(about()), Qt::Key_F1);
    menu->addAction("About&Qt", this, SLOT(aboutQt()));
    menu->addSeparator();
    //menu->addAction("What's This", whatsThisAction, SIGNAL(triggered(bool)), Qt::SHIFT + Qt::Key_F1);
    menu->addAction(whatsThisAction);
    //

    browser = new BrowserView(this);
    setCentralWidget(browser);

    //

    show_identity();
}

ControlWindow::~ControlWindow()
{
    browser->close();
}

void ControlWindow::historicActivated()
{
    QAction* s = static_cast<QAction* >(sender());
    if(s)
    {
        load(s->text());
    }
}

void ControlWindow::show_identity()
{
    statusBar()->showMessage("User is " + user_name(user_id()) +
                             " [id " + QString::number(user_id()) + "]");
}

void ControlWindow::change_user()
{
    UserDialog d(QCursor::pos());

    if (d.exec() == QDialog::Accepted) {
        set_user_id(d.id(), d.name());
        show_identity();
        browser->hide();
        browser->show();
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

void ControlWindow::load(QString path)
{
    browser->close();

    QFileInfo fi(path);

    if (!fi.exists())
        return;

    QDir dir(fi.path());

    if (! dir.mkdir("all.lock"))
        QMessageBox::critical(0, "Control project",
                              (dir.exists("all.lock"))
                              ? "\
                                The project is already locked by 'Project control' or 'Project syncho'\n\
                                (the directory 'all.lock' exists)"
                              : "Can't create directory 'all.lock'");
    else {
        const QFileInfoList l = dir.entryInfoList(QStringList()<<"*.lock");

        if (!l.isEmpty())  {
            //QFileInfoList::iterator it= l.begin();
            //Q3PtrListIterator<QFileInfo> it(*l);
            //QFileInfo * fi;
            QString ids;

            /*while ((fi = it.current()) != 0) {
                if (fi->isDir() && (my_baseName(*fi) != "all"))
                    ids += " " + my_baseName(*fi);

                ++it;
            }*/
            foreach (QFileInfo fi, l) {
                if (fi.isDir() && (my_baseName(fi) != "all"))
                    ids += " " + my_baseName(fi);
            }

            if (! ids.isEmpty()) {
                QMessageBox::critical(0, "Control project",
                                      "The project is edited by the users having these IDs :" + ids);
                dir.rmdir("all.lock");
                return;
            }
        }

        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        browser->set_project(dir);
        browser->get_project()->setExpanded(TRUE);

        bool r = browser->get_project()->load(dir);
        browser->resizeColumnToContents(0);
        browser->resizeColumnToContents(1);
        browser->resizeColumnToContents(2);
        browser->resizeColumnToContents(3);
        browser->resizeColumnToContents(4);

        QApplication::restoreOverrideCursor();

        if (! r)
            browser->close();

        // note : all.lock will be deleted by BrowserView
    }
}

void ControlWindow::load()
{
    QString path = QFileDialog::getOpenFileName(this, QString(), "*.prj");

    if (! path.isEmpty())
        load(path);
}

void ControlWindow::quit()
{
    browser->close();
    QApplication::exit(0);
}

void ControlWindow::browser_search()
{
    BrowserSearchDialog dialog(QCursor::pos());

    dialog.exec();
}

void ControlWindow::motif_style()
{
#if !defined(QT_NO_STYLE_MOTIF)
    QApplication::setStyle("motif");
#endif
}

void ControlWindow::motifplus_style()
{
#if !defined(QT_NO_STYLE_MOTIFPLUS)
    QApplication::setStyle("motifPlus");
#endif
}

void ControlWindow::windows_style()
{
#ifndef QT_NO_STYLE_WINDOWS
    QApplication::setStyle("windows");
#endif
}

void ControlWindow::about()
{
    QMessageBox::about(this, "Project control", "<p>Version <b>1.2.5</b></p>");
}

void ControlWindow::aboutQt()
{
    QMessageBox::aboutQt(this, "Project control");
}
