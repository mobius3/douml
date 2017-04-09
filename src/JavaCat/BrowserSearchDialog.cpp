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
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qgroupbox.h>
//Added by qt3to4:
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "BrowserSearchDialog.h"
#include "BrowserView.h"
#include "Package.h"
#include "Class.h"
#include "aRelationKind.h"
#include "aDirection.h"
#include "aVisibility.h"
#include "anItemKind.h"

int BrowserSearchDialog::saved_kind;
QString BrowserSearchDialog::saved_ed;
bool BrowserSearchDialog::saved_case_sensitive;

static const struct {
    const char * lbl;
    int k;
} Kinds[] = {
    { "in class description", -1 },
    { "a class ", aClass },
    { "a package", aPackage }
};

BrowserSearchDialog::BrowserSearchDialog(const QPoint & p)
    : QDialog(0 )
{
    setModal(true);
    setWindowTitle("Browser search");
    move(p);

    QVBoxLayout * vbox = new QVBoxLayout(this);

    vbox->setMargin(5);
    QGridLayout * gl = new QGridLayout(this/*4, 2, 5space*/);
    vbox->addLayout(gl);

    gl->addWidget(new QLabel("Kind", this), 0, 0, Qt::AlignLeft);
    kind = new QComboBox(this);

    for (int index = 0; index != sizeof(Kinds) / sizeof(*Kinds); index += 1)
        kind->addItem(Kinds[index].lbl);

    kind->setCurrentIndex(saved_kind);
    gl->addWidget(kind, 0, 1);

    ed = new QLineEdit(this);
    ed->setText(saved_ed);
    gl->addWidget(new QLabel("Containing", this), 1, 0, Qt::AlignLeft);
    gl->addWidget(ed, 1, 1);

    QGridLayout *gbLayout =new QGridLayout(this);
    QGroupBox * gb = new QGroupBox(/*2, Qt::Horizontal,*/ this);
    gb->setLayout(gbLayout);

    case_sensitive = new QCheckBox("case sensitive", gb);
    gbLayout->addWidget(case_sensitive);
    case_sensitive->setChecked(saved_case_sensitive);

    gl->addWidget(gb, 2, 1);

    gl->addWidget(new QLabel("Result", this), 3, 0, Qt::AlignLeft);
    results = new QComboBox(this);
    gl->addWidget(results, 3, 1);

    QHBoxLayout * hbox = new QHBoxLayout(this);
    vbox->addLayout(hbox);
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

    saved_kind = kind->currentIndex();
    saved_ed = ed->text();
    saved_case_sensitive = case_sensitive->isChecked();
}

void BrowserSearchDialog::search()
{
    nodes.clear();
    results->clear();

    nodes.search(Package::get_root(), Kinds[kind->currentIndex()].k,
                 ed->text(), (Qt::CaseSensitivity)case_sensitive->isChecked());
    nodes.sort();

    foreach (BrowserNode *bn, nodes) {
        QString up = ((BrowserNode *) bn->parent())->get_path();

        results->addItem((up.isEmpty())
                            ? QString(bn->text(0))
                            : bn->text(0) + QString("   [") + up + "]");
    }
}

void BrowserSearchDialog::select()
{
    if (results->count() != 0)
        BrowserView::select(nodes.at(results->currentIndex()));
}

