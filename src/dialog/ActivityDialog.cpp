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
#include <qcheckbox.h>
#include <bbuttongroup.h>
#include <qcursor.h>
#include "ActivityDialog.h"
#include "ActivityData.h"
#include "BrowserActivity.h"
#include "BrowserOperation.h"
#include "BrowserView.h"
#include "KeyValueTable.h"
#include "UmlWindow.h"
#include "DialogUtil.h"
#include "strutil.h"
#include "UmlDesktop.h"
#include "BodyDialog.h"
#include "GenerationSettings.h"
#include "ProfiledStereotypes.h"
#include "translate.h"
#include "menufactory.h"

QSize ActivityDialog::previous_size;

ActivityDialog::ActivityDialog(ActivityData * d)
    : TabDialog(0, 0, FALSE, Qt::WA_DeleteOnClose), activity(d)
{
    d->browser_node->edit_start();

    if (d->browser_node->is_writable()) {
        setOkButton(tr("OK"));
        setCancelButton(tr("Cancel"));
    }
    else {
        setOkButton(QString());
        setCancelButton(tr("Close"));
    }

    setWindowTitle(tr("Activity dialog"));
    visit = !hasOkButton();

    BrowserNode * bn = activity->browser_node;
    GridBox * grid;

    //
    // general tab
    //

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(tr("name : "), grid));
    grid->addWidget(edname = new LineEdit(bn->get_name(), grid));
    edname->setReadOnly(visit);

    grid->addWidget(new QLabel(tr("stereotype : "), grid));
    grid->addWidget(edstereotype = new QComboBox(grid));
    edstereotype->setEditable(!visit);
    edstereotype->addItem(toUnicode(activity->get_stereotype()));

    if (!visit) {
        edstereotype->addItems(BrowserActivity::default_stereotypes());
        edstereotype->addItems(ProfiledStereotypes::defaults(UmlActivity));
        edstereotype->setAutoCompletion(completion());
    }

    edstereotype->setCurrentIndex(0);
    QSizePolicy sp = edstereotype->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    edstereotype->setSizePolicy(sp);

    SmallPushButton* sButton;
    connect(sButton = new SmallPushButton(tr("specification :"), grid), SIGNAL(clicked()),
            this, SLOT(menu_specification()));
    grid->addWidget(sButton);
    grid->addWidget(edspecification = new QComboBox(grid));
    edspecification->setSizePolicy(sp);

    if (visit) {
        if (activity->get_specification() == 0)
            edspecification->addItem("");
        else
            edspecification->addItem(activity->get_specification()->full_name(TRUE));
    }
    else {
        edspecification->addItem("");
        edspecification->setAutoCompletion(completion());
        BrowserOperation::instances(opers);
        opers.full_names(list);
        edspecification->addItems(list);
        edspecification->setCurrentIndex((activity->get_specification() == 0)
                                         ? 0
                                         : opers.indexOf(activity->get_specification()) + 1);
    }

    grid->addWidget(new QLabel(grid));
    BButtonGroup * bg;
    grid->addWidget(bg =
            new BButtonGroup(3, Qt::Horizontal, QString(), grid));

    bg->addWidget(readonly_cb = new QCheckBox(tr("read only"), bg));

    if (activity->read_only)
        readonly_cb->setChecked(TRUE);

    readonly_cb->setDisabled(visit);

    bg->addWidget(singlexec_cb = new QCheckBox(tr("single execution"), bg));

    if (activity->single_execution)
        singlexec_cb->setChecked(TRUE);

    singlexec_cb->setDisabled(visit);

    bg->addWidget(active_cb = new QCheckBox(tr("active"), bg));

    if (activity->is_active)
        active_cb->setChecked(TRUE);

    active_cb->setDisabled(visit);

    VVBox * vtab;
    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(tr("description :"), vtab));

    if (! visit)
    {
        connect(sButton = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_description()));
    vtab->addWidget(sButton);
    }

    grid->addWidget(comment = new MultiLineEdit(grid));
    comment->setReadOnly(visit);
    comment->setText(bn->get_comment());
    //comment->setFont(font);

    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(tr("constraint :"), vtab));

    if (! visit) {
        connect(sButton = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_constraint()));
        vtab->addWidget(sButton);
    }


    grid->addWidget(constraint = new MultiLineEdit(grid));
    constraint->setReadOnly(visit);
    constraint->setText(activity->constraint);
    //constraint->setFont(font);

    addTab(grid, "Uml");

    // UML / OCL
    init_tab(uml, activity->uml_condition, "Ocl", TRUE);

    // CPP
    init_tab(cpp, activity->cpp_condition, "C++",
             GenerationSettings::cpp_get_default_defs());

    // Java
    init_tab(java, activity->java_condition, "Java",
             GenerationSettings::java_get_default_defs());

    // USER : list key - value

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(kvtable = new KeyValuesTable(bn, grid, visit));
    addTab(grid, tr("Properties"));

    //

    connect(this, SIGNAL(currentChanged(QWidget *)),
            this, SLOT(change_tabs(QWidget *)));

    open_dialog(this);
}

void ActivityDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::limitsize_center(this, previous_size, 0.8, 0.8);
}

void ActivityDialog::menu_specification()
{
    QMenu m(0);

    MenuFactory::addItem(m, tr("Choose"), -1);
    m.addSeparator();

    int index = list.indexOf(edspecification->currentText().trimmed());

    if (index != -1)
        MenuFactory::addItem(m, tr("Select in browser"), 0);

    BrowserNode * bn = 0;

    if (! visit) {
        bn = BrowserView::selected_item();

        if ((bn != 0) && (bn->get_type() == UmlOperation) && !bn->deletedp())
            MenuFactory::addItem(m, tr("Choose operation selected in browser"), 1);
        else
            bn = 0;
    }

    if ((index != -1) || (bn != 0)) {
        QAction *retActon = m.exec(QCursor::pos());
        if(retActon)
        {
            switch (retActon->data().toInt()) {
            case 0:
                opers.at(index)->select_in_browser();
                break;

            case 1: {
                QString s = bn->full_name(TRUE);

                if ((index = list.indexOf(s)) == -1) {
                    // new operation, may be created through an other dialog
                    index = 0;
                    QStringList::Iterator iter = list.begin();
                    QStringList::Iterator iter_end = list.end();

                    while ((iter != iter_end) && (*iter < s)) {
                        ++iter;
                        index += 1;
                    }

                    opers.insert((unsigned) index, bn);
                    list.insert(iter, s);
                    edspecification->addItem(s, index + 1);
                }
            }


                edspecification->setCurrentIndex(index + 1);
                break;

            default:
                break;
            }
        }
    }
}

ActivityDialog::~ActivityDialog()
{
    activity->browser_node->edit_end();
    previous_size = size();

    foreach (BodyDialog *dialog, edits)
        dialog->close();
    edits.clear();

    close_dialog(this);
}

void ActivityDialog::change_tabs(QWidget *)
{
    if (!visit)
        edname->setFocus();
}

void ActivityDialog::init_tab(CondDialog & d, InfoData & cd,
                              const char * lbl, bool enabled)
{
    GridBox * grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(tr("Pre\ncondition : "), grid));
    grid->addWidget(d.edpre = new MultiLineEdit(grid));
    d.edpre->setText(cd.first);

    if (visit)
        d.edpre->setReadOnly(TRUE);

    grid->addWidget(new QLabel(tr("Post\ncondition : "), grid));
    grid->addWidget(d.edpost = new MultiLineEdit(grid));
    d.edpost->setText(cd.second);

    if (visit)
        d.edpost->setReadOnly(TRUE);

    addTab(grid, lbl);

    if (! enabled)
        removePage(grid);
}

void ActivityDialog::edit_description()
{
    edit(comment->text(), "activity_description", activity, TxtEdit,
         this, (post_edit) post_edit_description, edits);
}

void ActivityDialog::post_edit_description(ActivityDialog * d, QString s)
{
    d->comment->setText(s);
}

void ActivityDialog::edit_constraint()
{
    edit(constraint->text(), edname->text().trimmed() + "_constraint",
         activity, TxtEdit, this, (post_edit) post_edit_constraint, edits);
}

void ActivityDialog::post_edit_constraint(ActivityDialog * d, QString s)
{
    d->constraint->setText(s);
}

void ActivityDialog::accept()
{
    if (!check_edits(edits) || !kvtable->check_unique())
        return;

    BrowserNode * bn = activity->browser_node;
    QString s;

    s = edname->text().trimmed();

    if ((s != bn->get_name()) &&
            ((BrowserNode *) bn->parent())->wrong_child_name(s, UmlActivity,
                                                             bn->allow_spaces(),
                                                             bn->allow_empty()))
        msg_critical(tr("Error"), s + tr("\n\nillegal name or already used"));
    else {
        bn->set_name(s);

        bool newst = activity->set_stereotype(fromUnicode(edstereotype->currentText().trimmed()));
        int index = list.indexOf(edspecification->currentText().trimmed());

        activity->set_specification((index != -1)
                                    ? (BrowserOperation *) opers.at(index)
                                    : 0);

        activity->read_only = readonly_cb->isChecked();
        activity->single_execution = singlexec_cb->isChecked();
        activity->is_active = active_cb->isChecked();

        uml.accept(activity->uml_condition);
        cpp.accept(activity->cpp_condition);
        java.accept(activity->java_condition);

        bn->set_comment(comment->text());
        UmlWindow::update_comment_if_needed(bn);

        activity->constraint = constraint->trimmedText();

        kvtable->updateNodeFromThis(bn);

        ProfiledStereotypes::modified(bn, newst);

        bn->modified();
        bn->package_modified();
        activity->modified();

        TabDialog::accept();
    }
}

void CondDialog::accept(InfoData & cond)
{
    cond.first = edpre->text().trimmed();
    cond.second = edpost->text().trimmed();
}
