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
#include <q3combobox.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <q3groupbox.h>
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>

#include "BrowserSearchDialog.h"
#include "BrowserView.h"

QString BrowserSearchDialog::saved_ed;
bool BrowserSearchDialog::saved_case_sensitive;

BrowserSearchDialog::BrowserSearchDialog(const QPoint & p)
    : QDialog(0, "Browser search", TRUE)
{
    setCaption("Browser search");
    move(p);

    Q3VBoxLayout * vbox = new Q3VBoxLayout(this);

    vbox->setMargin(5);

    Q3GridLayout * gl = new Q3GridLayout(vbox, 4, 2, 5/*space*/);

    ed = new QLineEdit(this);
    ed->setText(saved_ed);
    gl->addWidget(new QLabel("Containing", this), 1, 0, Qt::AlignLeft);
    gl->addWidget(ed, 1, 1);

    Q3GroupBox * gb = new Q3GroupBox(2, Qt::Horizontal, this);

    case_sensitive = new QCheckBox("case sensitive", gb);
    case_sensitive->setChecked(saved_case_sensitive);

    gl->addWidget(gb, 2, 1);

    gl->addWidget(new QLabel("Result", this), 3, 0, Qt::AlignLeft);
    results = new Q3ComboBox(FALSE, this);
    gl->addWidget(results, 3, 1);

    Q3HBoxLayout * hbox = new Q3HBoxLayout(vbox);
    hbox->setMargin(5);
    QPushButton * search_b = new QPushButton("Search", this);
    QPushButton * select_b = new QPushButton("Select", this);
    QPushButton * close_b = new QPushButton("Close", this);

    search_b->setDefault(TRUE);

    hbox->addWidget(search_b);
    hbox->addWidget(select_b);
    hbox->addWidget(close_b);

    connect(search_b, SIGNAL(clicked()), this, SLOT(search()));
    connect(select_b, SIGNAL(clicked()), this, SLOT(select()));
    connect(close_b, SIGNAL(clicked()), this, SLOT(reject()));

    setMaximumHeight(sizeHint().height());
}

BrowserSearchDialog::~BrowserSearchDialog()
{
    saved_ed = ed->text();
    saved_case_sensitive = case_sensitive->isChecked();
}

void BrowserSearchDialog::search()
{
    nodes.clear();
    results->clear();

    nodes.search(BrowserView::get_project(), ed->text(),
                 case_sensitive->isChecked());
    nodes.sort();

    BrowserNode * bn;

    for (bn = nodes.first(); bn != 0; bn = nodes.next()) {
        QString up = ((BrowserNode *) bn->parent())->get_path();

        results->insertItem((up.isEmpty())
                            ? QString(bn->text(0))
                            : bn->text(0) + QString("   [") + up + "]");
    }
}

void BrowserSearchDialog::select()
{
    if (results->count() != 0)
        BrowserView::select(nodes.at(results->currentItem()));
}

