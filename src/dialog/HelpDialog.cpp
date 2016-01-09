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
#include <errno.h>


#include <qmessagebox.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qdir.h>

#include "HelpDialog.h"
#include "UmlDesktop.h"
#include "DialogUtil.h"
#include "translate.h"
#include <QTextBrowser>
#include <QDesktopServices>
static QString NavigatorPath;
static QString ManualDir;
static QSize Sz;
static QString DocDir;

QString manual_dir()
{
    return ManualDir;
}

void set_manual_dir(QString p)
{
    ManualDir = p;
}

QString navigator_path()
{
    return NavigatorPath;
}

void set_navigator_path(QString p)
{
    NavigatorPath = p;
}

//

HelpDialog * HelpDialog::the;

HelpDialog::HelpDialog()
    : QDialog(0, Qt::Dialog)
{
    setWindowTitle(TR("BOUML Help"));

    QVBoxLayout * vbox = new QVBoxLayout(this);
    QHBoxLayout * hbox;

    vbox->setMargin(5);

    br = new QTextBrowser(this);
    vbox->addWidget(br);

    //vbox->addWidget(new QLabel(this));

    if (!DocDir.isEmpty()) {
        QDir d(DocDir);

        hbox = new QHBoxLayout();
        vbox->addLayout(hbox);
        hbox->addWidget(new QLabel(this));
        hbox->addWidget(new QLabel(TR("To set the navigator by setting the environment through the menu"
                                      " Miscellaneous allows to see all the documentation in better conditions")
                                   , this));
        hbox->addWidget(new QLabel(this));
    }
    else
        vbox->addWidget(new QLabel(this));

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);

    QPushButton * ok = new QPushButton(TR("Close"), this);

    hbox->addWidget(new QLabel(this));
    hbox->addWidget(ok);
    hbox->addWidget(new QLabel(this));

    QSize sz;
    UmlDesktop::setsize_center(this, Sz, 0.7, 0.7);
    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    open_dialog(this);
}

HelpDialog::~HelpDialog()
{
    the = 0;
    close_dialog(this);
}

void HelpDialog::show(QString topic)
{
    unsigned index;




    QString topicUnchanged = topic;
    QString dirs[3];

    dirs[1] = "/usr/share/doc/packages/bouml";
    dirs[2] = "/usr/share/doc/bouml";


    dirs[0] = ManualDir;
    DocDir = "";
    for (index = (ManualDir.isEmpty()) ? 1 : 0;
         index != sizeof(dirs) / sizeof(*dirs);
         index += 1) {
        QDir dir(dirs[index]);

        if (dir.exists(topic + ".html")) {
            DocDir = dir.absolutePath();



            if (!NavigatorPath.isEmpty()) {

                if (dir.exists("index_" + topic + ".html"))
                    topic = dir.absoluteFilePath("index_" + topic + ".html");
                else
                    topic = dir.absoluteFilePath(topic + ".html");

                int index = 0;

                QString navPath = QDir::toNativeSeparators(NavigatorPath);
                navPath.prepend("\"");
                navPath.append("\"");
                QString s = navPath +" " + QString(QUrl::fromLocalFile(topic).toEncoded()) +"&";


                errno = 0;
                (void) system(s.toLatin1().constData());

                if (errno != 0)
                    QMessageBox::critical(0, "Douml",
                                          QObject::tr("HelpDialog : error while executing '%1'\n"
                                                      "perhaps you must specify its absolute path"
                                                      "or set the environment variable PATH ?").arg(NavigatorPath));

                return;
            }
            else
            {

                if (dir.exists("index_" + topic + ".html"))
                    topic = dir.absoluteFilePath("index_" + topic + ".html");
                else
                    topic = dir.absoluteFilePath(topic + ".html");
                if(QDesktopServices::openUrl(QUrl::fromLocalFile(topic)))
                    return;
            }

            break;
        }
    }

    if (the == 0)
        the = new HelpDialog();

    if (!DocDir.isEmpty()) {
        the->br->setSearchPaths(QStringList()<<DocDir);
        topicUnchanged = topicUnchanged + ".html";
        the->br->setSource(topicUnchanged);
    }
    else {
        bool old = FALSE;

        for (index = 0; index != sizeof(dirs) / sizeof(*dirs); index += 1) {
            QDir dir(dirs[index]);

            if (dir.exists("bouml.html") && dir.exists("browseritems.html")) {
                old = true;
                break;
            }
        }

        the->br->setText(QString((old) ? QObject::tr("The documentation is too old.<br><br>")
                                       : QObject::tr("The documentation isn't installed.<br><br>")) +
                         QObject::tr("The \".tar.gz\" or \".7z\" archives are available here:"
                                     "<ul><li>http://bouml.sourceforge.net/documentation.html</li>"
                                     "<li>http://sourceforge.net/projects/douml/documentation.html</li></ul>"
                                     "<br>Extract an archive and set the environment through the Miscellaneous"
                                     "menu to indicate where the directory \"doc\" is then close this dialog and redo"));
        the->setMinimumSize(QSize(600, 300));
    }

    the->QDialog::show();
    the->raise();
}
