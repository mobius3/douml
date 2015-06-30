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
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <QList>
#include "ComponentDialog.h"
#include "BrowserComponent.h"
#include "SimpleData.h"
#include "BrowserClass.h"
#include "UmlWindow.h"
#include "UmlDesktop.h"
#include "DialogUtil.h"
#include "KeyValueTable.h"
#include "ListBoxBrowserNode.h"
#include "strutil.h"
#include "UmlPixmap.h"
#include "BodyDialog.h"
#include "ProfiledStereotypes.h"
#include "translate.h"
#include "hhbox.h"
QSize ComponentDialog::previous_size;

ComponentDialog::ComponentDialog(SimpleData * nd)
    : TabDialog(0, 0, FALSE, Qt::WA_DeleteOnClose), data(nd)
{
    nd->get_browser_node()->edit_start();

    if (nd->get_browser_node()->is_writable()) {
        setOkButton(TR("OK"));
        setCancelButton(TR("Cancel"));
    }
    else {
        setOkButton(QString());
        setCancelButton(TR("Close"));
    }

    setWindowTitle(TR("component dialog"));

    BrowserComponent * bn = (BrowserComponent *) nd->get_browser_node();

    init_uml_tab();
    rqs = bn->get_required_classes();
    init_l_tab(rq_page, rq_stereotypefilter, &ComponentDialog::rq_stereotypeFilterActivated,
               SLOT(rq_stereotypeFilterActivated(const QString &)),
               SLOT(require_cls()), SLOT(unrequire_cls()),
               lb_rq_available, lb_rq, rqs, tr("Required classes"));
    prs = bn->get_provided_classes();
    init_l_tab(pr_page, pr_stereotypefilter, &ComponentDialog::pr_stereotypeFilterActivated,
               SLOT(pr_stereotypeFilterActivated(const QString &)),
               SLOT(provide_cls()), SLOT(unprovide_cls()),
               lb_pr_available, lb_pr, prs, TR("Provided classes"));
    rzs = bn->get_realizing_classes();
    init_l_tab(rz_page, rz_stereotypefilter, &ComponentDialog::rz_stereotypeFilterActivated,
               SLOT(rz_stereotypeFilterActivated(const QString &)),
               SLOT(realize_cls()), SLOT(unrealize_cls()),
               lb_rz_available, lb_rz, rzs, TR("Realizing classes"));

    // USER : list key - value

    GridBox * grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(kvtable = new KeyValuesTable((BrowserComponent *) data->get_browser_node(),
                                 grid, !hasOkButton()));
    addTab(grid, TR("Properties"));

    //

    connect(this, SIGNAL(currentChanged(QWidget *)),
            this, SLOT(change_tabs(QWidget *)));

    open_dialog(this);
}

void ComponentDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::setsize_center(this, previous_size, 0.8, 0.8);
}

ComponentDialog::~ComponentDialog()
{
    data->get_browser_node()->edit_end();
    previous_size = size();

    foreach (BodyDialog *dialog, edits)
        dialog->close();
    edits.clear();

    close_dialog(this);
}

void ComponentDialog::change_tabs(QWidget * w)
{
    if (hasOkButton() && (w == umltab))
        edname->setFocus();
}

void ComponentDialog::init_uml_tab()
{
    bool visit = !hasOkButton();

    BrowserComponent * bn = (BrowserComponent *) data->get_browser_node();
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
        edstereotype->addItems(BrowserComponent::default_stereotypes());
        edstereotype->addItems(ProfiledStereotypes::defaults(UmlComponent));
        edstereotype->setAutoCompletion(completion());
    }

    edstereotype->setCurrentIndex(0);
    QSizePolicy sp = edstereotype->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    edstereotype->setSizePolicy(sp);

    grid->addWidget(vbox = new VVBox(grid));
    vbox->addWidget(new QLabel(TR("description :"), vbox));

    if (! visit)
    {
        SmallPushButton* sButton;
        connect(sButton = new SmallPushButton(TR("Editor"), vbox), SIGNAL(clicked()),
                this, SLOT(edit_description()));
        vbox->addWidget(sButton);
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

void ComponentDialog::init_l_tab(VVBox *& page, QComboBox *& stereotypefilter,
                                 void (ComponentDialog::* filteractivated)(const QString & st),
                                 const char * slt,
                                 const char * add_slt, const char * remove_slt,
                                 QListWidget *& lb_available, QListWidget *& lb,
                                 const QList<BrowserClass *> & cls,
                                 QString lbl)
{
    bool visit = !hasOkButton();
    HHBox * hbox;
    VVBox * vbox;
    QPushButton * button;
        QLabel* label;
    page = new VVBox(this);

    if (!visit) {
        page->addWidget(hbox = new HHBox(page));
        hbox->setMargin(5);
        hbox->addWidget(new QLabel(TR("Stereotype filtering  "), hbox));
        hbox->addWidget(stereotypefilter = new QComboBox(hbox));
        stereotypefilter->setEditable(true);
        stereotypefilter->setAutoCompletion(completion());
        stereotypefilter->addItem("");
        stereotypefilter->addItems(BrowserClass::default_stereotypes());
        stereotypefilter->addItems(ProfiledStereotypes::defaults(UmlComponent));
        stereotypefilter->setCurrentIndex(0);
        QSizePolicy sp = stereotypefilter->sizePolicy();
        sp.setHorizontalPolicy(QSizePolicy::Expanding);
        stereotypefilter->setSizePolicy(sp);
        connect(stereotypefilter, SIGNAL(activated(const QString &)),
                this, slt);

        page->addWidget(hbox = new HHBox(page));
        hbox->addWidget(vbox = new VVBox(hbox));
        vbox->setMargin(5);
        (label = new QLabel(TR("Available classes"), vbox))->setAlignment(Qt::AlignCenter);
        vbox->addWidget(label);
        vbox->addWidget(lb_available = new QListWidget(vbox));
        lb_available->setSelectionMode(QListWidget::MultiSelection);

        hbox->addWidget(vbox = new VVBox(hbox));
        vbox->setMargin(5);
        (label = new QLabel("", vbox))->setScaledContents(TRUE);
        vbox->addWidget(label);
        vbox->addWidget(button = new QPushButton(vbox));
        button->setIcon(*rightPixmap);
        connect(button, SIGNAL(clicked()), this, add_slt);
        (label = new QLabel("", vbox))->setScaledContents(TRUE);
        vbox->addWidget(label);
        vbox->addWidget(button = new QPushButton(vbox));
        button->setIcon(*leftPixmap);
        connect(button, SIGNAL(clicked()), this, remove_slt);
        (label = new QLabel("", vbox))->setScaledContents(TRUE);
        vbox->addWidget(label);
        hbox->addWidget(vbox = new VVBox(hbox));
    }
    else
        vbox = page;

    vbox->setMargin(5);
    ( label = new QLabel(lbl, vbox))->setAlignment(Qt::AlignCenter);
    vbox->addWidget(label);
    vbox->addWidget(lb = new QListWidget(vbox));
    lb->setSelectionMode((visit) ? QListWidget::NoSelection
                         : QListWidget::MultiSelection);

    QList<BrowserClass *>::ConstIterator it;

    for (it = cls.begin(); it != cls.end(); ++it)
        if (!(*it)->deletedp())
            lb->addItem(new ListBoxBrowserNode(*it, (*it)->full_name(TRUE)));

    lb->sortItems();

    if (! visit)
        (this->*filteractivated)(QString());

    addTab(page, lbl);
}

void ComponentDialog::rq_stereotypeFilterActivated(const QString & st)
{
    lb_rq_available->clear();

    BrowserNodeList classes;

    BrowserClass::instances(classes, st.toLatin1().constData(), TRUE);

    foreach (BrowserNode *cl, classes)
        if (rqs.indexOf((BrowserClass *) cl) == -1)
            lb_rq_available->addItem(new ListBoxBrowserNode(cl, cl->full_name(TRUE)));

    lb_rq_available->sortItems();
}

void ComponentDialog::pr_stereotypeFilterActivated(const QString & st)
{
    lb_pr_available->clear();

    BrowserNodeList classes;

    BrowserClass::instances(classes, st.toLatin1().constData(), TRUE);

    foreach (BrowserNode *cl, classes)
        if (prs.indexOf((BrowserClass *) cl) == -1)
            lb_pr_available->addItem(new ListBoxBrowserNode(cl, cl->full_name(TRUE)));

    lb_pr_available->sortItems();
}

void ComponentDialog::rz_stereotypeFilterActivated(const QString & st)
{
    lb_rz_available->clear();

    BrowserNodeList classes;

    BrowserClass::instances(classes, st.toLatin1().constData(), TRUE);

    foreach (BrowserNode *cl, classes)
        if (rzs.indexOf((BrowserClass *) cl) == -1)
            lb_rz_available->addItem(new ListBoxBrowserNode(cl, cl->full_name(TRUE)));

    lb_rz_available->sortItems();
}

void ComponentDialog::require_cls()
{
    unsigned int i = 0;

    while (i != lb_rq_available->count()) {
        QListWidgetItem * item = lb_rq_available->item(i);

        if (item->isSelected()) {
            rqs.append((BrowserClass *)((ListBoxBrowserNode *) item)->browser_node);
            lb_rq_available->takeItem(lb_rq_available->row(item));
            lb_rq->addItem(item);
        }
        else
            i += 1;
    }

    lb_rq->sortItems();
}

void ComponentDialog::unrequire_cls()
{
    unsigned int i = 0;

    while (i != lb_rq->count()) {
        QListWidgetItem * item = lb_rq->item(i);

        if (item->isSelected()) {
            BrowserNode * c = ((ListBoxBrowserNode *) item)->browser_node;
            QString s = item->text();

            delete item;
            rqs.removeOne((BrowserClass *) c);

            if (rq_stereotypefilter->currentText().isEmpty() ||
                (c->get_stereotype() == rq_stereotypefilter->currentText()))
                lb_rq_available->addItem(new ListBoxBrowserNode(c, s));
        }
        else
            i += 1;
    }

    lb_rq_available->sortItems();
}

void ComponentDialog::provide_cls()
{
    unsigned int i = 0;

    while (i != lb_pr_available->count()) {
        QListWidgetItem * item = lb_pr_available->item(i);

        if (item->isSelected()) {
            prs.append((BrowserClass *)((ListBoxBrowserNode *) item)->browser_node);
            lb_pr_available->takeItem(lb_pr_available->row(item));
            lb_pr->addItem(item);
        }
        else
            i += 1;
    }

    lb_pr->sortItems();
}

void ComponentDialog::unprovide_cls()
{
    unsigned int i = 0;

    while (i != lb_pr->count()) {
        QListWidgetItem * item = lb_pr->item(i);

        if (item->isSelected()) {
            BrowserNode * c = ((ListBoxBrowserNode *) item)->browser_node;
            QString s = item->text();

            delete item;
            prs.removeOne((BrowserClass *) c);

            if (pr_stereotypefilter->currentText().isEmpty() ||
                (c->get_stereotype() == pr_stereotypefilter->currentText()))
                lb_pr_available->addItem(new ListBoxBrowserNode(c, s));
        }
        else
            i += 1;
    }

    lb_pr_available->sortItems();
}

void ComponentDialog::realize_cls()
{
    unsigned int i = 0;

    while (i != lb_rz_available->count()) {
        QListWidgetItem * item = lb_rz_available->item(i);

        if (item->isSelected()) {
            rzs.append((BrowserClass *)((ListBoxBrowserNode *) item)->browser_node);
            lb_rz_available->takeItem(lb_rz_available->row(item));
            lb_rz->addItem(item);
        }
        else
            i += 1;
    }

    lb_rz->sortItems();
}

void ComponentDialog::unrealize_cls()
{
    unsigned int i = 0;

    while (i != lb_rz->count()) {
        QListWidgetItem * item = lb_rz->item(i);

        if (item->isSelected()) {
            BrowserNode * c = ((ListBoxBrowserNode *) item)->browser_node;
            QString s = item->text();

            delete item;
            rzs.removeOne((BrowserClass *) c);

            if (rz_stereotypefilter->currentText().isEmpty() ||
                (c->get_stereotype() == rz_stereotypefilter->currentText()))
                lb_rz_available->addItem(new ListBoxBrowserNode(c, s));
        }
        else
            i += 1;
    }

    lb_rz_available->sortItems();
}

void ComponentDialog::edit_description()
{
    edit(comment->text(), edname->text().trimmed() + "_description",
         data, TxtEdit, this, (post_edit) post_edit_description, edits);
}

void ComponentDialog::post_edit_description(ComponentDialog * d, QString s)
{
    d->comment->setText(s);
}

void ComponentDialog::accept()
{
    if (!check_edits(edits) || !kvtable->check_unique())
        return;

    QString s = edname->text().trimmed();
    BrowserComponent * bn = (BrowserComponent *) data->get_browser_node();

    if ((s != bn->get_name()) &&
        ((BrowserNode *) bn->parent())->wrong_child_name(s, bn->get_type(),
                bn->allow_spaces(),
                bn->allow_empty()))
        msg_critical(TR("Error"), edname->text() + TR("\n\nillegal name or already used"));
    else {
        bn->set_name(s);
        bn->set_comment(comment->text());
        UmlWindow::update_comment_if_needed(bn);

        bool newst = data->set_stereotype(fromUnicode(edstereotype->currentText().trimmed()));
        QList<BrowserClass *> rq;
        QList<BrowserClass *> rz;
        QList<BrowserClass *> pr;

        unsigned int i;
        unsigned int n;

        for (i = 0, n = lb_rq->count(); i != n; i += 1)
            rq.append((BrowserClass *)((ListBoxBrowserNode *) lb_rq->item(i))->browser_node);

        for (i = 0, n = lb_pr->count(); i != n; i += 1)
            pr.append((BrowserClass *)((ListBoxBrowserNode *) lb_pr->item(i))->browser_node);

        for (i = 0, n = lb_rz->count(); i != n; i += 1)
            rz.append((BrowserClass *)((ListBoxBrowserNode *) lb_rz->item(i))->browser_node);

        bn->set_associated_classes(rz, pr, rq);

        kvtable->updateNodeFromThis(bn);

        ProfiledStereotypes::modified(bn, newst);

        bn->modified();
        bn->package_modified();
        data->modified();

        TabDialog::accept();
    }
}
