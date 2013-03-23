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





#include <qlayout.h>
#include <qlabel.h>
#include <q3textview.h>
#include <qpushbutton.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <QPixmap>
#include <Q3HBoxLayout>

#include "About.h"
#include "bp_xpm.xpm"
#include "UmlDesktop.h"
#include "translate.h"

AboutDialog::AboutDialog() : QDialog(0, "About DoUML", TRUE)
{
    setCaption(TR("About DoUML"));
    //move(p);

    Q3VBoxLayout * vbox = new Q3VBoxLayout(this);
    Q3HBoxLayout * hbox;

    vbox->setMargin(5);

    hbox = new Q3HBoxLayout(vbox);
    hbox->setMargin(5);

    QPixmap bp((const char **) bp_xpm);
    // QLabel * lbp = new QLabel(this);

    // lbp->setPixmap(bp);
    //  hbox->addWidget(lbp);
    hbox->addWidget(new QLabel("  ", this));
    // Replacing about to bouml-ng
    const char htmltext[] = "<p>DoUML</p>\n"
                            "<p>This project is a fork of\n"
                            "Bruno Pages's work, BoUML:\n"
                            "<i>http://sourceforge.net/projects/bouml/</i></p>\n"
                            "<p>DoUML focus is to port BoUML to Qt4\n"
                            "and to maintain it as a community</p>\n"
                            "<p>Join us at:<br>\n"
                            "https://github.com/DoUML/douml<br>\n"
                            "#bdouml@irc.freenode.net</p>\n\n\n";

    Q3TextView * tx =
        new Q3TextView(htmltext, QString(), this);
    QFont fnt = tx->font();

    fnt.setItalic(TRUE);

    QFontMetrics fm(fnt);

    tx->setVScrollBarMode(Q3ScrollView::AlwaysOff);
    tx->setHScrollBarMode(Q3ScrollView::AlwaysOff);
    tx->setMinimumSize(fm.size(0, htmltext));
    hbox->addWidget(tx);

    hbox = new Q3HBoxLayout(vbox);
    hbox->setMargin(5);
    QPushButton * ok = new QPushButton(TR("&OK"), this);

    ok->setDefault(TRUE);

    hbox->addWidget(new QLabel(this));
    hbox->addWidget(ok);
    hbox->addWidget(new QLabel(this));

    if (UmlDesktop::fixed())
        UmlDesktop::tocenter(this);

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
}

