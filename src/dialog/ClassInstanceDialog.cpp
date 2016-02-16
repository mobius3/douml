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





#include <gridbox.h>
#include <vvbox.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qcursor.h>
#include <QList>
#include "ClassInstanceDialog.h"
#include "BrowserClassInstance.h"
#include "ClassInstanceData.h"
#include "RelationData.h"
#include "BrowserClass.h"
#include "BrowserAttribute.h"
#include "BrowserView.h"
#include "DialogUtil.h"
#include "BodyDialog.h"
#include "UmlWindow.h"
#include "UmlDesktop.h"
#include "KeyValueTable.h"
#include "strutil.h"
#include "ProfiledStereotypes.h"
#include "translate.h"
#include "menufactory.h"
#include <QHeaderView>
RelTable::RelTable(QWidget * parent, ClassInstanceData * inst, bool visit)
    : MyTable(parent)
{
    const QList<SlotRel> & rels = inst->get_relations();

    setRowCount(rels.count());
    setColumnCount((visit) ? 5 : 6);
    setSelectionMode(QTableWidget::SingleSelection);
    //setSortingEnabled(true);

    setHorizontalHeaderLabel(0, tr("Class Inst."));
    setHorizontalHeaderLabel(1, tr("Role"));
    setHorizontalHeaderLabel(2, tr("kind"));
    setHorizontalHeaderLabel(3, tr("Role"));
    setHorizontalHeaderLabel(4, tr("Class Inst."));
    setHorizontalHeaderLabel(5, tr("Delete"));

    QString role = inst->get_browser_node()->get_name() + QString(":") +
            inst->get_class()->get_name();
    int row = 0;
    QList<SlotRel>::ConstIterator it;

    for (it = rels.begin(); it != rels.end(); ++it)
        init_row(*it, row++, role, visit);

    setColumnStretchable(1, TRUE);
    setColumnStretchable(3, TRUE);
    adjustColumn(0);
    adjustColumn(2);
    adjustColumn(4);

    if (! visit)
        adjustColumn(5);

    connect(this, SIGNAL(pressed(QModelIndex)),
            this, SLOT(button_pressed(QModelIndex)));
}

void RelTable::init_row(const SlotRel & sr, int row, QString a, bool visit)
{
    QString b = sr.value->get_name() + QString(":") +
            ((ClassInstanceData *) sr.value->get_data())->get_class()->get_name();

    setItem(row, 0, new TableItem(TableItem::Never,
                                  (sr.is_a) ? a : b, TableItem::TableItemType));

    RelationData * d = sr.rel;
    const char * s;

    s = d->get_role_b();
    setItem(row, 1, new TableItem(TableItem::Never, (s == 0) ? "" : s, TableItem::TableItemType));

    setItem(row, 2, new TableItem(TableItem::Never, stringify(d->get_type()), TableItem::TableItemType));

    s = d->get_role_a();
    setItem(row, 3, new TableItem(TableItem::Never, (s == 0) ? "" : s, TableItem::TableItemType));

    setItem(row, 4, new TableItem(TableItem::Never,
                                  (sr.is_a) ? b : a, TableItem::TableItemType));

    if (! visit)
        setText(row, 5, "");
}

void RelTable::button_pressed(const QModelIndex &index)
{
    if (index.column() == 5)
        setText(index.row(), index.column(), text(index.row(), index.column()).isEmpty() ? tr("   Yes") : QString());
}

//

QSize ClassInstanceDialog::previous_size;

ClassInstanceDialog::ClassInstanceDialog(ClassInstanceData * i)
    : TabDialog(0, "class instance dialog", FALSE, Qt::WA_DeleteOnClose),
      inst(i), atbl(0), rtbl(0)
{
    setWindowTitle(tr("Class instance dialog"));

    BrowserNode * bn = inst->get_browser_node();

    bn->edit_start();

    if (bn->is_writable()) {
        setOkButton(tr("OK"));
        setCancelButton(tr("Cancel"));
    }
    else {
        setOkButton(QString());
        setCancelButton(tr("Close"));
    }

    visit = !hasOkButton();

    GridBox * grid;

    // general tab

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(tr("name : "), grid));
    grid->addWidget(edname = new LineEdit(bn->get_name(), grid));

    if (visit)
        edname->setReadOnly(TRUE);

    grid->addWidget(new QLabel(tr("stereotype :"), grid));
    grid->addWidget(edstereotype = new QComboBox( grid));
    edstereotype->setEditable(!visit);
    edstereotype->addItem(toUnicode(bn->get_stereotype()));

    if (! visit) {
        edstereotype->addItems(ProfiledStereotypes::defaults(UmlClassInstance));
        edstereotype->setAutoCompletion(completion());
    }

    SmallPushButton  * b;
    grid->addWidget(b = new SmallPushButton(tr("class :"), grid));

    connect(b, SIGNAL(clicked()), this, SLOT(menu_class()));

    grid->addWidget(edtype = new QComboBox(grid));

    if (visit) {
        edtype->addItem(inst->get_class()->full_name());
        nodes.append(inst->get_class());
    }
    else {
        BrowserClass::instances(nodes);
        nodes.full_names(list);
        edtype->addItems(list);
        edtype->setCurrentIndex(nodes.indexOf(inst->get_class()));
        connect(edtype, SIGNAL(activated(int)), this, SLOT(type_changed(int)));
    }

    if (visit)
        cl_container = 0;
    else {
        cl_container = (BrowserNode *) bn->parent();

        if ((cl_container != 0) && !cl_container->is_writable())
            cl_container = 0;
    }

    VVBox * vtab;
    grid->addWidget(vtab = new VVBox(grid));

    vtab->addWidget(new QLabel(tr("description :"), vtab));

    if (! visit) {
        connect(b =new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_description()));
        vtab->addWidget(b);
    }

    grid->addWidget(comment = new MultiLineEdit(grid));
    comment->setReadOnly(visit);
    comment->setText(bn->get_comment());

    QFont font = comment->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);

    comment->setFont(font);

    addTab(grid, "Uml");

    // attributes tab

    atbl = new MyTable(this);
    atbl->setColumnCount(3);
    //atbl->setSortingEnabled(true);
    atbl->setSelectionMode(QTableWidget::NoSelection);	// single does not work
    atbl->verticalHeader()->setSectionsMovable(true);
    atbl->verticalHeader()->setSectionsMovable(true);
    atbl->setHorizontalHeaderLabel(0, tr(" Attribute "));
    atbl->setHorizontalHeaderLabel(1, tr(" Class "));
    atbl->setHorizontalHeaderLabel(2, tr(" Value "));

    addTab(atbl, tr("Attributes"));

    // relation tab

    if (! inst->relations.isEmpty()) {
        rtbl = new RelTable(this, inst, visit);
        addTab(rtbl, tr("Relations"));
    }

    // USER : list key - value

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(kvtable = new KeyValuesTable(bn, grid, visit));
    addTab(grid, tr("Properties"));

    type_changed(edtype->currentIndex());

    connect(m_tabWidget, SIGNAL(currentChanged(int)),
            this, SLOT(update_all_tabs(int)));

    open_dialog(this);
}

void ClassInstanceDialog::polish()
{
    QDialog::ensurePolished();
    UmlDesktop::limitsize_move(this, previous_size, 0.8, 0.8);
}

ClassInstanceDialog::~ClassInstanceDialog()
{
    inst->browser_node->edit_end();
    previous_size = size();

    foreach (BodyDialog *dialog, edits)
        dialog->close();
    edits.clear();

    close_dialog(this);
}

void ClassInstanceDialog::update_all_tabs(int index)
{
    QWidget * w = m_tabWidget->widget(index);
    if (w == atbl) {
        if (! visit)
            edname->setFocus();
    }
}

void ClassInstanceDialog::edit_description()
{
    edit(comment->text(), edname->text().trimmed() + "_description",
         inst, TxtEdit, this, (post_edit) post_edit_description, edits);
}

void ClassInstanceDialog::post_edit_description(ClassInstanceDialog * d, QString s)
{
    d->comment->setText(s);
}

void ClassInstanceDialog::menu_class()
{
    QMenu m(0);

    MenuFactory::addItem(m, tr("Choose"), -1);
    m.addSeparator();

    int index = list.indexOf(edtype->currentText().trimmed());

    if (index != -1)
        MenuFactory::addItem(m, tr("Select in browser"), 0);

    BrowserNode * bn = 0;

    if (! visit) {
        bn = BrowserView::selected_item();

        if ((bn != 0) && (bn->get_type() == UmlClass) && !bn->deletedp())
            MenuFactory::addItem(m, tr("Choose class selected in browser"), 1);
        else
            bn = 0;

        if (cl_container != 0)
            MenuFactory::addItem(m, tr("Create class and choose it"), 2);
    }

    if ((index != -1) || (bn != 0) || (cl_container != 0)) {
        QAction* retAction = m.exec(QCursor::pos());
        if(retAction)
        {
            switch (retAction->data().toInt()) {
            case 0:
                nodes.at(index)->select_in_browser();
                break;

            case 2:
                bn = BrowserClass::add_class(FALSE, cl_container);

                if (bn == 0)
                    return;

                bn->select_in_browser();

                // no break
            case 1: {
                if ((index = nodes.indexOf(bn)) == -1) {
                    // new class, may be created through an other dialog
                    QStringList::Iterator iter = list.begin();
                    QStringList::Iterator iter_end = list.end();
                    QString s = bn->full_name(TRUE);

                    index = 0;

                    while ((iter != iter_end) && (*iter < s)) {
                        ++iter;
                        index += 1;
                    }

                    nodes.insert((unsigned) index, bn);
                    list.insert(iter, s);
                    edtype->insertItem(index,s);
                }
            }

                edtype->setCurrentIndex(index);
                type_changed(index);
                break;

            default:
                break;
            }
        }
    }
}

void ClassInstanceDialog::type_changed(int i)
{
    // made attribute list
    BrowserClass * cl = (BrowserClass *) nodes.at(i);

    cl->get_attrs(attributes);
    attributes.sort();

    // fill table
    atbl->setRowCount(0);
    atbl->setRowCount(attributes.count());

    QList<SlotAttr> attrs = inst->attributes;

    int index = 0;
    foreach (BrowserNode * at, attributes) {
        atbl->setItem(index, 0, new TableItem(TableItem::Never, at->get_name(), TableItem::TableItemType));
        atbl->setItem(index, 1, new TableItem(TableItem::Never, ((BrowserNode *) at->parent())->get_name(), TableItem::TableItemType));

        QList<SlotAttr>::Iterator it_attr;

        for (it_attr = attrs.begin(); it_attr != attrs.end(); ++it_attr) {
            if ((*it_attr).att == at) {
                atbl->setText(index, 2, (*it_attr).value);
                break;
            }
        }

        if (it_attr == attrs.end())
            atbl->setText(index, 2, QString());
        ++index;
    }

    atbl->setColumnStretchable(2, TRUE);
    atbl->adjustColumn(0);
    atbl->adjustColumn(1);

    if (rtbl)
        rtbl->setEnabled(cl == inst->cl);
}

void ClassInstanceDialog::accept()
{
    if (!kvtable->check_unique())
        return;

    atbl->forceUpdateCells();

    BrowserClassInstance * bn = (BrowserClassInstance *) inst->get_browser_node();

    bn->set_name(edname->text().trimmed());

    bool newst = bn->get_data()->set_stereotype(fromUnicode(edstereotype->currentText().trimmed()));
    BrowserClass * new_cl = (BrowserClass *) nodes.at(edtype->currentIndex());

    if (new_cl != inst->cl)
        inst->set_class(new_cl);
    else if (rtbl) {
        QList<SlotRel> rels = inst->get_relations(); // copy !
        QList<SlotRel>::Iterator it;
        int row = 0;
        QString yes = tr("Yes");

        for (row = 0, it = rels.begin(); it != rels.end(); ++it, row += 1) {
            if (rtbl->text(row, 5).trimmed() == yes) {
                SlotRel & sr = *it;

                inst->replace(sr.value, sr.rel, 0, sr.is_a, FALSE);
            }
        }
    }

    bn->set_comment(comment->text());
    UmlWindow::update_comment_if_needed(bn);

    inst->attributes.clear();

    int n = atbl->rowCount();
    int index;

    for (index = 0; index != n; index += 1) {
        QString s = atbl->text(index, 2).trimmed();

        if (! s.isEmpty())
            inst->attributes.append(SlotAttr((BrowserAttribute *) attributes.at(index),
                                             s));
    }

    kvtable->updateNodeFromThis(bn);

    ProfiledStereotypes::modified(bn, newst);

    bn->modified();
    bn->package_modified();
    inst->modified();

    QDialog::accept();
}
