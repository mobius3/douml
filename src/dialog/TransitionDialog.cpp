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
#include "TransitionDialog.h"
#include "TransitionData.h"
#include "BrowserTransition.h"
#include "KeyValueTable.h"
#include "UmlWindow.h"
#include "DialogUtil.h"
#include "strutil.h"
#include "UmlDesktop.h"
#include "BodyDialog.h"
#include "GenerationSettings.h"
#include "ProfiledStereotypes.h"
#include "translate.h"

QSize TransitionDialog::previous_size;

TransitionDialog::TransitionDialog(TransitionData * r)
    : TabDialog(0, 0, true, Qt::WA_DeleteOnClose), rel(r)
{
    r->browser_node->edit_start();

    if (r->browser_node->is_writable()) {
        setOkButton(tr("OK"));
        setCancelButton(tr("Cancel"));
    }
    else {
        setOkButton(QString());
        setCancelButton(tr("Close"));
    }

    setWindowTitle(tr("Transition dialog"));
    visit = !hasOkButton();

    BrowserNode * bn = rel->browser_node;
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
    grid->addWidget(edstereotype = new QComboBox(grid));
    edstereotype->setEditable(!visit);
    edstereotype->addItem(toUnicode(rel->get_stereotype()));

    if (!visit) {
        //edstereotype->addItems(rel->get_start()->default_stereotypes(type));
        edstereotype->setAutoCompletion(completion());
        edstereotype->addItems(ProfiledStereotypes::defaults(UmlTransition));
    }

    edstereotype->setCurrentIndex(0);
    QSizePolicy sp = edstereotype->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    edstereotype->setSizePolicy(sp);

    if (r->get_start_node() != r->get_end_node())
        internal_cb = 0;
    else {
        grid->addWidget(new QLabel(grid));
        grid->addWidget(internal_cb = new QCheckBox(tr("internal"), grid));
        internal_cb->setChecked(r->internal());
    }

    VVBox * vtab;
    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(tr("description :"), vtab));

    if (! visit)
    {
        SmallPushButton* sButton;
        connect(sButton = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_description()));
        vtab->addWidget(sButton);
    }

    grid->addWidget(comment = new MultiLineEdit(grid));
    comment->setReadOnly(visit);
    comment->setText(bn->get_comment());
    //comment->setFont(font);

    addTab(grid, "Uml");

    // UML / OCL
    init_tab(ocltab, uml, rel->uml, "Ocl", SLOT(edit_uml_trigger()),
             SLOT(edit_uml_guard()), SLOT(edit_uml_expr()), TRUE);

    // CPP
    init_tab(cppTab, cpp, rel->cpp, "C++", SLOT(edit_cpp_trigger()),
             SLOT(edit_cpp_guard()), SLOT(edit_cpp_expr()),
             GenerationSettings::cpp_get_default_defs());

    // Java
    init_tab(javatab, java, rel->java, "Java", SLOT(edit_java_trigger()),
             SLOT(edit_java_guard()), SLOT(edit_java_expr()),
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

TransitionDialog::~TransitionDialog()
{
    rel->browser_node->edit_end();
    previous_size = size();

    foreach (BodyDialog *dialog, edits)
        dialog->close();
    edits.clear();

    close_dialog(this);
}

void TransitionDialog::change_tabs(QWidget * w)
{
    if (!visit) {
        if (w == umltab)
            edname->setFocus();
        else if (w == ocltab)
            uml.edtrigger->setFocus();
        else if (w == cppTab)
            cpp.edtrigger->setFocus();
        else if (w == javatab)
            java.edtrigger->setFocus();
    }
}

void TransitionDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::limitsize_center(this, previous_size, 0.8, 0.8);
}

void TransitionDialog::init_tab(QWidget *& tab, TransDialog & d, TransDef & td,
                                const char * lbl, const char * sl_trigger,
                                const char * sl_guard, const char * sl_expr,
                                bool enabled)
{
    GridBox * grid = new GridBox(2, this);
    VVBox * vtab;
    SmallPushButton* sButton;
    tab = grid;
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(tr("trigger : "), vtab));

    if (! visit)
    {
        connect(sButton = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, sl_trigger);
        vtab->addWidget(sButton);
    }

    grid->addWidget(d.edtrigger = new MultiLineEdit(grid));

    QFont font = d.edtrigger->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);
    d.edtrigger->setFont(font);
    d.edtrigger->setText(td.trigger);

    if (visit)
        d.edtrigger->setReadOnly(TRUE);

    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(tr("guard\nconstraint : "), vtab));

    if (! visit)
    {
        connect(sButton = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, sl_guard);
        vtab->addWidget(sButton);
    }

    grid->addWidget(d.edguard = new MultiLineEdit(grid));
    d.edguard->setFont(font);
    d.edguard->setText(td.guard);

    if (visit)
        d.edguard->setReadOnly(TRUE);

    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(tr("activity\nexpression : "), vtab));

    if (! visit)
    {
        connect(sButton = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, sl_expr);
        vtab->addWidget(sButton);
    }

    grid->addWidget(d.edexpr = new MultiLineEdit(grid));
    d.edexpr->setFont(font);
    d.edexpr->setText(td.expr);

    if (visit)
        d.edexpr->setReadOnly(TRUE);

    addTab(grid, lbl);

    if (! enabled)
        removePage(grid);
}

void TransitionDialog::edit_description()
{
    edit(comment->text(), "transition_description", rel, TxtEdit,
         this, (post_edit) post_edit_description, edits);
}

void TransitionDialog::post_edit_description(TransitionDialog * d, QString s)
{
    d->comment->setText(s);
}

#define DEF_EDIT(attr, lang, Lang) \
void TransitionDialog::edit_##lang##_##attr() {	\
  edit(lang.ed##attr->text(), "transition_"#lang"_"#attr, rel, Lang,  \
       this, (post_edit) post_edit_##lang##_##attr, edits);	\
} \
  \
void TransitionDialog::post_edit_##lang##_##attr(TransitionDialog * d, QString s) \
{ \
  d->lang.ed##attr->setText(s); \
}

DEF_EDIT(trigger, uml, TxtEdit)
DEF_EDIT(trigger, cpp, CppEdit)
DEF_EDIT(trigger, java, JavaEdit)

DEF_EDIT(guard, uml, TxtEdit)
DEF_EDIT(guard, cpp, CppEdit)
DEF_EDIT(guard, java, JavaEdit)

DEF_EDIT(expr, uml, TxtEdit)
DEF_EDIT(expr, cpp, CppEdit)
DEF_EDIT(expr, java, JavaEdit)

void TransitionDialog::accept()
{
    if (!check_edits(edits) || !kvtable->check_unique())
        return;

    BrowserNode * bn = rel->browser_node;
    QString s;

    s = edname->text().trimmed();

    if (s.isEmpty())
        s = "<transition>";

    if ((s != bn->get_name()) &&
        ((BrowserNode *) bn->parent())->wrong_child_name(s, UmlTransition,
                bn->allow_spaces(),
                bn->allow_empty()))
        msg_critical(tr("Error"), s + tr("\n\nillegal name or already used"));
    else {
        bn->set_name(s);

        bool newst = rel->set_stereotype(fromUnicode(edstereotype->currentText().trimmed()));

        if (internal_cb != 0)
            rel->set_internal(internal_cb->isChecked());

        uml.accept(rel->uml);
        cpp.accept(rel->cpp);
        java.accept(rel->java);

        bn->set_comment(comment->text());
        UmlWindow::update_comment_if_needed(bn);

        kvtable->updateNodeFromThis(bn);

        ProfiledStereotypes::modified(bn, newst);

        bn->modified();
        bn->package_modified();
        rel->modified();

        TabDialog::accept();
    }
}

void TransDialog::accept(TransDef & td)
{
    td.trigger = edtrigger->text();
    td.guard = edguard->text();
    td.expr = edexpr->text();
}
