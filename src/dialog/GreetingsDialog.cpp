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
#include <qlayout.h>
#include <qlabel.h>
#include <QTextEdit>
#include <qpushbutton.h>
#include <qtimer.h>
//Added by qt3to4:
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCloseEvent>

#include "GreetingsDialog.h"
#include "UmlDesktop.h"

GreetingsDialog::GreetingsDialog() : QDialog(0/*, "", TRUE*/)
{
    setWindowTitle("Greetings");

    QVBoxLayout * vbox = new QVBoxLayout(this);
    QHBoxLayout * hbox;

    vbox->setMargin(5);

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);

    const char * msg = "\
<br>\n\
Hello!<br>\n\
<br>\n\
Thank you for using <i>DoUML!</i><br>\n\
<br>\n\
<br>DoUML is a fork of the original BoUML project,\n\
<br>with the focus of porting the UI to Qt4 and to\n\
<br>continue development of the best UML 2.x tool!\n\
<br>\n\
<br>Please be aware that this is a testing version\n\
<br>and should <i>not</i> be considered ready for production\n\
<br>projects! We encourage you to use it and report bugs\n\
<br>to us so that we may reach a stable version soon!\n\
<br>\n\
<br>Thank you!\n\
<br>\n\
Visit us at <i>http://bouml-ng.sourceforge.net</i>\n\
<br>\n<br>\n<br>\n";

    QTextEdit * tx =
        new QTextEdit(msg, this);
    QFont fnt = tx->font();

    fnt.setItalic(TRUE);

    QFontMetrics fm(fnt);

    tx->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tx->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tx->setMinimumSize(fm.size(0, msg));
    hbox->addWidget(tx);

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);

    ok = new QPushButton("&OK", this);
    ok->setDefault(TRUE);
    ok->setEnabled(FALSE);

    hbox->addWidget(new QLabel(this));
    hbox->addWidget(ok);
    hbox->addWidget(new QLabel(this));

    if (UmlDesktop::fixed())
        UmlDesktop::tocenter(this);

    connect(ok, SIGNAL(clicked()), this, SLOT(reject()));

    QTimer::singleShot(5000, this, SLOT(valid_ok()));
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
}

void GreetingsDialog::valid_ok()
{
    ok->setEnabled(TRUE);
    QApplication::restoreOverrideCursor();
}

void GreetingsDialog::closeEvent(QCloseEvent * e)
{
    if (ok->isEnabled())
        QDialog::closeEvent(e);
}
