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





#include <qsplitter.h>
#include <gridbox.h>
#include <vvbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <QList>
#include "ParameterSetDialog.h"
#include "UmlDesktop.h"
#include "BrowserParameterSet.h"
#include "BrowserActivityAction.h"
#include "ParameterSetData.h"
#include "BrowserPin.h"
#include "UmlWindow.h"
#include "DialogUtil.h"
#include "KeyValueTable.h"
#include "ListBoxBrowserNode.h"
#include "strutil.h"
#include "UmlPixmap.h"
#include "BodyDialog.h"
#include "ProfiledStereotypes.h"
#include "translate.h"
#include "hhbox.h"

QSize ParameterSetDialog::previous_size;

ParameterSetDialog::ParameterSetDialog(ParameterSetData * nd)
    : TabDialog(0, 0, FALSE, Qt::WA_DeleteOnClose), data(nd)
{
    nd->browser_node->edit_start();

    if (nd->browser_node->is_writable()) {
        setOkButton(TR("OK"));
        setCancelButton(TR("Cancel"));
    }
    else {
        setOkButton(QString());
        setCancelButton(TR("Close"));
    }

    setWindowTitle(TR("ParameterSet dialog"));

    init_uml_tab();
    init_pins_tab();

    // USER : list key - value

    GridBox * grid = new GridBox(2, this);

    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(kvtable = new KeyValuesTable((BrowserParameterSet *) data->get_browser_node(),
                                 grid, !hasOkButton()));
    addTab(grid, TR("Properties"));

    //

    connect(this, SIGNAL(currentChanged(QWidget *)),
            this, SLOT(change_tabs(QWidget *)));

    open_dialog(this);
}

ParameterSetDialog::~ParameterSetDialog()
{
    data->browser_node->edit_end();
    previous_size = size();

    foreach (BodyDialog *dialog, edits)
        dialog->close();
    edits.clear();

    close_dialog(this);
}

void ParameterSetDialog::change_tabs(QWidget * w)
{
    if (hasOkButton() && (w == umltab))
        edname->setFocus();
}

void ParameterSetDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::limitsize_center(this, previous_size, 0.8, 0.8);
}

void ParameterSetDialog::init_uml_tab()
{
    bool visit = !hasOkButton();

    BrowserParameterSet * bn =
        (BrowserParameterSet *) data->get_browser_node();
    VVBox * vbox;
    GridBox * grid = new GridBox(2, this);

    umltab = grid;
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(TR("name : "), grid));
    grid->addWidget(edname = new LineEdit(bn->get_name(), grid));
    edname->setReadOnly(visit);

    grid->addWidget(new QLabel(TR("stereotype : "), grid));
    grid->addWidget(edstereotype = new QComboBox(grid));
    edstereotype->setEditable(true);
    edstereotype->addItem(toUnicode(data->get_stereotype()));

    if (! visit) {
        edstereotype->addItems(BrowserParameterSet::default_stereotypes());
        edstereotype->addItems(ProfiledStereotypes::defaults(UmlParameterSet));
        edstereotype->setAutoCompletion(completion());
    }

    edstereotype->setCurrentIndex(0);
    QSizePolicy sp = edstereotype->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    edstereotype->setSizePolicy(sp);

    grid->addWidget(vbox = new VVBox(grid));
    vbox->addWidget(new QLabel(TR("description :"), vbox));
    SmallPushButton* b;
    if (! visit) {
        connect( b = new SmallPushButton(TR("Editor"), vbox), SIGNAL(clicked()),
                this, SLOT(edit_description()));
        vbox->addWidget(b);
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
}

void ParameterSetDialog::init_pins_tab()
{
    bool visit = !hasOkButton();
    HHBox * hbox;
    QPushButton * button;
    VVBox * vbox = new VVBox(this);
    VVBox * page = vbox;
    const QList<BrowserPin *> & inpins = data->pins;
    QList<BrowserPin *>::ConstIterator it;
    QLabel* l;
    if (!visit) {
        vbox->addWidget(hbox = new HHBox(vbox));
        hbox->addWidget(vbox = new VVBox(hbox));
        vbox->setMargin(5);
        (l = new QLabel(TR("Parameters out of Parameter Set"), vbox))->setAlignment(Qt::AlignCenter);
        vbox->addWidget(l);
        vbox->addWidget(lb_available = new QListWidget(vbox));
        lb_available->setSelectionMode(QListWidget::MultiSelection);

        BrowserParameterSet * bn =
            (BrowserParameterSet *) data->get_browser_node();
        QList<BrowserPin *> allpins =
            ((BrowserActivityAction *) bn->parent())->get_pins();

        for (it = allpins.begin(); it != allpins.end(); it++)
            if (!inpins.contains(*it))
                lb_available->addItem(new ListBoxBrowserNode(*it, (*it)->full_name(TRUE)));

        lb_available->sortItems();

        hbox->addWidget(vbox = new VVBox(hbox));
        vbox->setMargin(5);
        (l = new QLabel("", vbox))->setScaledContents(TRUE);
        vbox->addWidget(l);
        vbox->addWidget(button = new QPushButton(vbox));
        button->setIcon(*rightPixmap);
        connect(button, SIGNAL(clicked()), this, SLOT(associate_cls()));
        (l =new QLabel("", vbox))->setScaledContents(TRUE);
        vbox->addWidget(l);
        vbox->addWidget(button = new QPushButton(vbox));
        button->setIcon(*leftPixmap);
        connect(button, SIGNAL(clicked()), this, SLOT(unassociate_cls()));
        (l = new QLabel("", vbox))->setScaledContents(TRUE);
        vbox->addWidget(l);
        hbox->addWidget(vbox = new VVBox(hbox));
    }

    vbox->setMargin(5);
    (l = new QLabel(TR("Parameters in Parameter Set"), vbox))->setAlignment(Qt::AlignCenter);
    vbox->addWidget(l);
    vbox->addWidget(lb_member = new QListWidget(vbox));
    lb_member->setSelectionMode((visit) ? QListWidget::NoSelection
                                : QListWidget::MultiSelection);

    for (it = inpins.begin(); it != inpins.end(); ++it)
        lb_member->addItem(new ListBoxBrowserNode(*it, (*it)->full_name(TRUE)));

    addTab(page, TR("Parameters"));
}

void ParameterSetDialog::edit_description()
{
    edit(comment->text(), edname->text().trimmed() + "_description",
         data, TxtEdit, this, (post_edit) post_edit_description, edits);
}

void ParameterSetDialog::post_edit_description(ParameterSetDialog * d, QString s)
{
    d->comment->setText(s);
}

void ParameterSetDialog::associate_cls()
{
    unsigned int i = 0;

    while (i < lb_available->count()) {
        QListWidgetItem * item = lb_available->item(i);

        if (item->isSelected()) {
            lb_available->takeItem(lb_available->row(item));
            lb_member->addItem(item);
        }
        else
            i += 1;
    }

    lb_member->sortItems();
}

void ParameterSetDialog::unassociate_cls()
{
    unsigned int i = 0;

    while (i < lb_member->count()) {
        QListWidgetItem * item = lb_member->item(i);

        if (item->isSelected()) {
            lb_member->takeItem(lb_member->row(item));
            lb_available->addItem(item);
        }
        else
            i += 1;
    }

    lb_available->sortItems();
}

void ParameterSetDialog::accept()
{
    if (!check_edits(edits) || !kvtable->check_unique())
        return;

    QString s = edname->text().trimmed();
    BrowserParameterSet * bn =
        (BrowserParameterSet *) data->get_browser_node();

    if ((s != bn->get_name()) &&
        ((BrowserNode *) bn->parent())->wrong_child_name(s, bn->get_type(),
                bn->allow_spaces(),
                bn->allow_empty()))
        msg_critical(TR("Error"), edname->text() + TR("\n\nillegal name or already used"));
    else {
        bn->set_name(s);
        bn->set_comment(comment->text());
        UmlWindow::update_comment_if_needed(bn);

        QString stereotype =
            fromUnicode(edstereotype->currentText().trimmed());
        bool newst = data->set_stereotype(stereotype);
        QList<BrowserPin *> l;
        unsigned n = lb_member->count();

        for (unsigned i = 0; i != n; i += 1)
            l.append((BrowserPin *)
                     (((ListBoxBrowserNode *) lb_member->item(i))
                      ->browser_node));

        data->set_pins(l);

        kvtable->updateNodeFromThis(bn);

        ProfiledStereotypes::modified(bn, newst);

        bn->modified();
        bn->package_modified();
        data->modified();

        TabDialog::accept();
    }
}
