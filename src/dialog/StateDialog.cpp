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
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <bbuttongroup.h>
#include <qcursor.h>
#include "StateDialog.h"
#include "StateData.h"
#include "BrowserState.h"
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
QSize StateDialog::previous_size;

StateDialog::StateDialog(StateData * d)
    : TabDialog(0, 0, true, Qt::WA_DeleteOnClose), state(d)
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

    setWindowTitle(tr("State dialog"));
    visit = !hasOkButton();

    BrowserNode * bn = state->browser_node;
    GridBox * grid;

    //
    // general tab
    //

    grid = new GridBox(2, this);
    umltab = grid;
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(tr("name : "), grid));
    grid->addWidget(edname = new LineEdit(bn->get_name(), grid));
    edname->setReadOnly(visit);

    grid->addWidget(new QLabel(tr("stereotype : "), grid));
    grid->addWidget(edstereotype = new QComboBox( grid));
    edstereotype->setEditable(!visit);
    edstereotype->addItem(toUnicode(state->get_stereotype()));

    if (!visit) {
        edstereotype->addItems(BrowserState::default_stereotypes());
        edstereotype->addItems(ProfiledStereotypes::defaults(UmlState));
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
        if (state->get_specification() == 0)
            edspecification->addItem("");
        else
            edspecification->addItem(state->get_specification()->full_name(TRUE));
    }
    else {
        edspecification->addItem("");
        edspecification->setAutoCompletion(completion());
        BrowserOperation::instances(opers);
        opers.full_names(speclist);
        edspecification->addItems(speclist);
        edspecification->setCurrentIndex((state->get_specification() == 0)
                                         ? 0
                                         : opers.indexOf(state->get_specification()) + 1);
    }

    switch (((BrowserNode *) bn->parent())->get_type()) {
    case UmlState:
    case UmlRegion:
        if ((state->get_reference() != 0) || (bn->firstChild() == 0)) {
            connect(sButton = new SmallPushButton(tr("reference :"), grid), SIGNAL(clicked()),
                    this, SLOT(menu_reference()));
            grid->addWidget(sButton);
            grid->addWidget(edreference = new QComboBox(grid));
            edreference->setSizePolicy(sp);

            if (visit) {
                if (state->get_reference() == 0)
                    edreference->addItem("");
                else
                    edreference->addItem(state->get_reference()->full_name(TRUE));
            }
            else {
                edreference->addItem("");
                edreference->setAutoCompletion(completion());

                if (((BrowserState *) bn)->can_reference()) {
                    BrowserState::instances(states, TRUE);

                    QMutableListIterator<BrowserNode *> it(states);

                    while (it.hasNext()) {
                        BrowserState *state = (BrowserState *)it.next();
                        if (!((BrowserState *) bn)->can_reference(state) ||
                                state->is_ref()) {
                            it.remove();
                        }
                    }
                }
                else
                    states.append(state->get_reference());

                states.full_names(reflist);
                edreference->addItems(reflist);
                edreference->setCurrentIndex((state->get_reference() == 0)
                                             ? 0
                                             : states.indexOf(state->get_reference()) + 1);

                connect(edreference, SIGNAL(activated(int)), this, SLOT(ed_ref_activated(int)));
            }

            break;
        }

        // no break
    default:
        edreference = 0;
    }

    grid->addWidget(new QLabel(grid));
    BButtonGroup * bg;

    grid->addWidget(bg = new BButtonGroup(1, Qt::Horizontal, QString(), grid));

    bg->addWidget( active_cb = new QCheckBox(tr("active"), bg));

    if (state->is_active)
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

    addTab(grid, "Uml");

    // UML / OCL
    init_tab(ocltab, uml, state->uml, "Ocl", SLOT(edit_uml_entry()),
             SLOT(edit_uml_exit()), SLOT(edit_uml_activity()), TRUE);

    // CPP
    init_tab(cppTab, cpp, state->cpp, "C++", SLOT(edit_cpp_entry()),
             SLOT(edit_cpp_exit()), SLOT(edit_cpp_activity()),
             GenerationSettings::cpp_get_default_defs());

    // Java
    init_tab(javatab, java, state->java, "Java", SLOT(edit_java_entry()),
             SLOT(edit_java_exit()), SLOT(edit_java_activity()),
             GenerationSettings::java_get_default_defs());

    // USER : list key - value

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(kvtable = new KeyValuesTable(bn, grid, visit));
    addTab(grid, tr("Properties"));

    //

    if (edreference != 0)
        ed_ref_activated(edreference->currentIndex());

    connect(this, SIGNAL(currentChanged(QWidget *)),
            this, SLOT(change_tabs(QWidget *)));

    open_dialog(this);
}

StateDialog::~StateDialog()
{
    state->browser_node->edit_end();
    previous_size = size();

    foreach (BodyDialog *dialog, edits)
        dialog->close();
    edits.clear();

    close_dialog(this);
}

void StateDialog::change_tabs(QWidget * w)
{
    if (!visit) {
        if (w == umltab)
            edname->setFocus();
        else if (w == ocltab)
            uml.edentry->setFocus();
        else if (w == cppTab)
            cpp.edentry->setFocus();
        else if (w == javatab)
            java.edentry->setFocus();
    }
}

void StateDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::limitsize_center(this, previous_size, 0.8, 0.8);
}

void StateDialog::ed_ref_activated(int r)
{
    bool enabled = edreference->itemText(r).isEmpty();

    edspecification->setEnabled(enabled);
    active_cb->setEnabled(enabled);

    if (ocltab != 0)
        ocltab->setEnabled(enabled);

    if (cppTab != 0)
        cppTab->setEnabled(enabled);

    if (javatab != 0)
        javatab->setEnabled(enabled);
}

void StateDialog::menu_specification()
{
    QMenu m(0);

    MenuFactory::addItem(m, tr("Choose"), -1);
    m.addSeparator();

    int index = speclist.indexOf(edspecification->currentText());

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

                if ((index = speclist.indexOf(s)) == -1) {
                    // new operation, may be created through an other dialog
                    index = 0;
                    QStringList::Iterator iter = speclist.begin();
                    QStringList::Iterator iter_end = speclist.end();

                    while ((iter != iter_end) && (*iter < s)) {
                        ++iter;
                        index += 1;
                    }

                    opers.insert((unsigned) index, bn);
                    speclist.insert(iter, s);
                    edspecification->insertItem(index + 1, s);
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

void StateDialog::menu_reference()
{
    QMenu m(0);

    MenuFactory::addItem(m, tr("Choose"), -1);
    m.addSeparator();

    int index = reflist.indexOf(edreference->currentText());

    if (index != -1)
        MenuFactory::addItem(m, tr("Select in browser"), 0);

    BrowserNode * bn = 0;

    if (! visit) {
        bn = BrowserView::selected_item();

        if ((bn != 0) &&
                (bn->get_type() == UmlState) &&
                !bn->deletedp() &&
                ((BrowserState *)state->browser_node)->can_reference((BrowserState *) bn))
            MenuFactory::addItem(m, tr("Choose state selected in browser"), 1);
        else
            bn = 0;
    }

    if ((index != -1) || (bn != 0)) {
        QAction *retActon = m.exec(QCursor::pos());
        if(retActon)
        {
            switch (retActon->data().toInt()) {
            case 0:
                states.at(index)->select_in_browser();
                break;

            case 1: {
                QString s = bn->full_name(TRUE);

                if ((index = reflist.indexOf(s)) == -1) {
                    // new state, may be created through an other dialog
                    index = 0;
                    QStringList::Iterator iter = reflist.begin();
                    QStringList::Iterator iter_end = reflist.end();

                    while ((iter != iter_end) && (*iter < s)) {
                        ++iter;
                        index += 1;
                    }

                    states.insert((unsigned) index, bn);
                    reflist.insert(iter, s);
                    edreference->insertItem(index + 1, s);
                }
            }

                edreference->setCurrentIndex(index + 1);
                break;

            default:
                break;
            }
        }
    }
}

void StateDialog::init_tab(QWidget *& tab, StDialog & d, StateBehavior & st,
                           const char * lbl, const char * sl_enbeh,
                           const char * sl_exbeh, const char * sl_beh,
                           bool enabled)
{
    GridBox * grid = new GridBox(2, this);
    VVBox * vtab;

    tab = grid;
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(tr("Entry\nbehavior : "), vtab));

    SmallPushButton* sButton;
    if (! visit)
    {
        connect(sButton = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()), this, sl_enbeh);
        vtab->addWidget(sButton);
    }
    grid->addWidget(d.edentry = new MultiLineEdit(grid));

    QFont font = d.edentry->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);
    d.edentry->setFont(font);
    d.edentry->setText(st.on_entry);

    if (visit)
        d.edentry->setReadOnly(TRUE);

    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(tr("Exit\nbehavior : "), vtab));

    if (! visit)
    {
        connect(sButton = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()), this, sl_exbeh);
        vtab->addWidget(sButton);
    }
    grid->addWidget(d.edexit = new MultiLineEdit(grid));
    d.edexit->setFont(font);
    d.edexit->setText(st.on_exit);

    if (visit)
        d.edexit->setReadOnly(TRUE);

    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(tr("Do\nbehavior : "), vtab));

    if (! visit)
    {
        connect(sButton = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()), this, sl_beh);
        vtab->addWidget(sButton);
    }
    grid->addWidget(d.edactivity = new MultiLineEdit(grid));
    d.edactivity->setFont(font);
    d.edactivity->setText(st.do_activity);

    if (visit)
        d.edactivity->setReadOnly(TRUE);

    addTab(grid, lbl);

    if (! enabled) {
        removePage(grid);
        tab = 0;
    }
}

void StateDialog::edit_description()
{
    edit(comment->text(), "state_description", state, TxtEdit,
         this, (post_edit) post_edit_description, edits);
}

void StateDialog::post_edit_description(StateDialog * d, QString s)
{
    d->comment->setText(s);
}

#define DEF_EDIT(attr, lang, Lang) \
    void StateDialog::edit_##lang##_##attr() {	\
    edit(lang.ed##attr->text(), "state_"#lang"_"#attr, state, Lang,  \
    this, (post_edit) post_edit_##lang##_##attr, edits);	\
    } \
    \
    void StateDialog::post_edit_##lang##_##attr(StateDialog * d, QString s) \
{ \
    d->lang.ed##attr->setText(s); \
    }

DEF_EDIT(entry, uml, TxtEdit)
DEF_EDIT(entry, cpp, CppEdit)
DEF_EDIT(entry, java, JavaEdit)

DEF_EDIT(exit, uml, TxtEdit)
DEF_EDIT(exit, cpp, CppEdit)
DEF_EDIT(exit, java, JavaEdit)

DEF_EDIT(activity, uml, TxtEdit)
DEF_EDIT(activity, cpp, CppEdit)
DEF_EDIT(activity, java, JavaEdit)

void StateDialog::accept()
{
    if (!check_edits(edits) || !kvtable->check_unique())
        return;

    BrowserNode * bn = state->browser_node;
    QString s;

    s = edname->text().trimmed();

    if ((s != bn->get_name()) &&
            ((BrowserNode *) bn->parent())->wrong_child_name(s, UmlState,
                                                             bn->allow_spaces(),
                                                             bn->allow_empty()))
        msg_critical(tr("Error"), s + tr("\n\nillegal name or already used"));
    else {
        bn->set_name(s);

        bool newst = state->set_stereotype(fromUnicode(edstereotype->currentText().trimmed()));
        int index;

        index = speclist.indexOf(edspecification->currentText());
        state->set_specification((index != -1)
                                 ? (BrowserOperation *) opers.at(index)
                                 : 0);

        if (edreference != 0) {
            index = reflist.indexOf(edreference->currentText());
            state->set_reference((index != -1)
                                 ? (BrowserState *) states.at(index)
                                 : 0);
        }

        state->is_active = active_cb->isChecked();

        uml.accept(state->uml);
        cpp.accept(state->cpp);
        java.accept(state->java);

        bn->set_comment(comment->text());
        UmlWindow::update_comment_if_needed(bn);

        kvtable->updateNodeFromThis(bn);

        ProfiledStereotypes::modified(bn, newst);

        bn->modified();
        bn->package_modified();
        state->modified();

        TabDialog::accept();
    }
}

void StDialog::accept(StateBehavior & st)
{
    st.on_entry = edentry->text();
    st.on_exit = edexit->text();
    st.do_activity = edactivity->text();
}
