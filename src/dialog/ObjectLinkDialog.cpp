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
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "ObjectLinkDialog.h"
#include "MyTable.h"
#include "BrowserClass.h"
#include "BrowserClassInstance.h"
#include "ClassInstanceData.h"
#include "BrowserRelation.h"
#include "RelationData.h"
#include "UmlDesktop.h"
#include "translate.h"

QSize ObjectLinkDialog::previous_size;

ObjectLinkDialog::ObjectLinkDialog(BrowserClassInstance * a, BrowserClassInstance * b,
                                   QList<RelationData *> & l, RelationData * current,
                                   int nfirstdir)
    : QDialog(0/*, "object link dialog", TRUE*/),
      rels(l), nforward(nfirstdir), clia(a), clib(b), choozen(0), reverse(FALSE)
{
    setWindowTitle(TR("Object link dialog"));

    QVBoxLayout * vbox = new QVBoxLayout(this);
    QHBoxLayout * hbox;

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);

    hbox->addWidget(new QLabel(TR("\n"
                                  "To set the association, select a cell or the first column with a single click, then press 'OK'\n"
                                  "To unset the association press 'Unset' then press 'OK'\n"),
                               this));

    init(current);	// update table

    vbox->addWidget(table);

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);
    QPushButton * newrel =
        (((ClassInstanceData *) clia->get_data())->get_class()->is_writable() ||
         ((ClassInstanceData *) clib->get_data())->get_class()->is_writable())
        ? new QPushButton(TR("&New"), this) : 0;
    QPushButton * unset = new QPushButton(TR("&Unset"), this);
    QPushButton * accept = new QPushButton(TR("&OK"), this);
    QPushButton * cancel = new QPushButton(TR("&Cancel"), this);
    QSize bs(cancel->sizeHint());

    if (newrel != 0) {
        newrel->setFixedSize(bs);
        hbox->addWidget(newrel);
        connect(newrel, SIGNAL(clicked()), this, SLOT(create()));
    }

    unset->setFixedSize(bs);
    accept->setFixedSize(bs);
    cancel->setFixedSize(bs);

    hbox->addWidget(unset);
    hbox->addWidget(accept);
    hbox->addWidget(cancel);

    connect(unset, SIGNAL(clicked()), this, SLOT(unselect()));
    connect(accept, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

ObjectLinkDialog::~ObjectLinkDialog()
{
    previous_size = size();
}

void ObjectLinkDialog::polish()
{
    QDialog::ensurePolished();
    UmlDesktop::limitsize_center(this, previous_size, 0.8, 0.8);
}

static void add_rel(MyTable * table, RelationData * d, int row,
                    QString a, QString b)
{
    table->setItem(row, 0, new TableItem(table, TableItem::Never, a, TableItem::TableItemType));

    const char * s;

    s = d->get_role_b();
    table->setItem(row, 1, new TableItem(table, TableItem::Never, (s == 0) ? "" : s, TableItem::TableItemType));

    table->setItem(row, 2, new TableItem(table, TableItem::Never, stringify(d->get_type()), TableItem::TableItemType));

    s = d->get_role_a();
    table->setItem(row, 3, new TableItem(table, TableItem::Never, (s == 0) ? "" : s, TableItem::TableItemType));

    table->setItem(row, 4, new TableItem(table, TableItem::Never, b, TableItem::TableItemType));
}

void ObjectLinkDialog::init(RelationData * current)
{
    table = new MyTable(this);
    table->setSelectionMode(QAbstractItemView::MultiSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    table->setRowCount(rels.count());
    table->setColumnCount(5);
    table->setSelectionMode(QTableWidget::SingleSelection);
    //table->setSortingEnabled(true);

    table->setHorizontalHeaderLabel(0, TR("Class Inst."));
    table->setHorizontalHeaderLabel(1, TR("Role"));
    table->setHorizontalHeaderLabel(2, TR("kind"));
    table->setHorizontalHeaderLabel(3, TR("Role"));
    table->setHorizontalHeaderLabel(4, TR("Class Inst."));

    ra = clia->get_name() + QString(":") +
         ((ClassInstanceData *) clia->get_data())->get_class()->get_name();
    rb = clib->get_name() + QString(":") +
         ((ClassInstanceData *) clib->get_data())->get_class()->get_name();
    QListIterator<RelationData *> iter(rels);
    int row = 0;

    for (; (row != nforward) && iter.hasNext(); ++row)
        add_rel(table, iter.next(), row, ra, rb);

    for (; iter.hasNext(); ++row)
        add_rel(table, iter.next(), row, rb, ra);

    ninputrels = row;

    table->setColumnStretchable(1, TRUE);
    table->setColumnStretchable(3, TRUE);
    table->adjustColumn(0);
    table->adjustColumn(2);
    table->adjustColumn(4);

    if (current != 0) {
        int row = rels.indexOf(current);
        table->selectRow(row);
    }
}

void ObjectLinkDialog::unselect()
{
    // multi selection possible even table->setSelectionMode(QTable::Single)
    QList<QTableWidgetSelectionRange> selectedRanges= table->selectedRanges();
    foreach (QTableWidgetSelectionRange range, selectedRanges) {
        table->setRangeSelected(range, false);
    }
}

void ObjectLinkDialog::create()
{
    BrowserClass * cla = ((ClassInstanceData *) clia->get_data())->get_class();
    BrowserClass * clb = ((ClassInstanceData *) clib->get_data())->get_class();
    RelationData * d = (cla->is_writable())
                       ? (RelationData *) cla->add_relation((clb->is_writable()) ? UmlAssociation
                               : UmlDirectionalAssociation,
                               clb)
                           : (RelationData *) clb->add_relation(UmlDirectionalAssociation, cla);

    d->get_start()->select_in_browser();
    d->edit();

    int n = table->rowCount();

    table->setRowCount(n + 1);
    add_rel(table, d, n, ra, rb);
    rels.append(d);

    // multi selection possible even table->setSelectionMode(QTable::Single)
    QList<QTableWidgetSelectionRange> selectedRanges= table->selectedRanges();
    foreach (QTableWidgetSelectionRange range, selectedRanges) {
        table->setRangeSelected(range, false);
    }
    table->selectRow(n);
}

void ObjectLinkDialog::accept()
{
    QList<QTableWidgetSelectionRange> selectedRanges= table->selectedRanges();
    if(selectedRanges.count())
    {
        choozen = rels.at(selectedRanges.at(0).topRow());
        reverse = (selectedRanges.at(0).topRow() >= nforward) && (selectedRanges.at(0).topRow() < ninputrels);
    }
    QDialog::accept();
}
