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
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "BrowserSearchDialog.h"
#include "BrowserView.h"
#include <QComboBox>
#include <QGroupBox>

QString BrowserSearchDialog::saved_ed;
bool BrowserSearchDialog::saved_case_sensitive;

BrowserSearchDialog::BrowserSearchDialog(const QPoint & p)
    : QDialog(0)
{
    setWindowTitle("Browser search");
    setModal(true);
    move(p);
    QVBoxLayout * vbox = new QVBoxLayout(this);

    vbox->setMargin(5);

    QGridLayout * gl = new QGridLayout(this);//(4, 2, 5/*space*/);
    vbox->addLayout(gl);

    ed = new QLineEdit(this);
    ed->setText(saved_ed);
    gl->addWidget(new QLabel("Containing", this), 1, 0, Qt::AlignLeft);
    gl->addWidget(ed, 1, 1);

    QGroupBox * gb = new QGroupBox(this);//(2, Qt::Horizontal, this);

    gb->setLayout(new QVBoxLayout);
    case_sensitive = new QCheckBox("case sensitive", gb);
    gb->layout()->addWidget(case_sensitive);
    case_sensitive->setChecked(saved_case_sensitive);

    gl->addWidget(gb, 2, 1);

    gl->addWidget(new QLabel("Result", this), 3, 0, Qt::AlignLeft);
    results = new QComboBox(this);
    results->setEditable(false);
    gl->addWidget(results, 3, 1);

    QHBoxLayout * hbox = new QHBoxLayout();
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
    saved_ed = ed->text();
    saved_case_sensitive = case_sensitive->isChecked();
}
bool compareItems( BrowserNode * s1 , BrowserNode * s2 )
{
    //return s1. < s2.getRollNo();
    //return ((BrowserNode *) s1)->text(TREE_COL).compare(((BrowserNode *) s2)->text(TREE_COL));
    return BrowserNodeList::compareItems(s1,s2);
}
void BrowserSearchDialog::search()
{
    nodes.clear();
    results->clear();

    nodes.search(BrowserView::get_project(), ed->text(),
                 case_sensitive->isChecked());
    //nodes.sort();
    //qSort(nodes.begin(), nodes.end(), compareItems);
    std::sort(nodes.begin(), nodes.end(), compareItems);

    BrowserNode * bn;

    int i = 0;
    for (i = 0; i < nodes.count(); i++) {
        bn = nodes.at(i);
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

