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
#include <bbuttongroup.h>
#include <qcheckbox.h>
#include <qradiobutton.h>
#include <qpushbutton.h>
#include "ExtraMemberDialog.h"
#include "ExtraMemberData.h"
#include "BrowserExtraMember.h"
#include "KeyValueTable.h"
#include "UmlWindow.h"
#include "DialogUtil.h"
#include "UmlDesktop.h"
#include "BodyDialog.h"
#include "GenerationSettings.h"
#include "strutil.h"
#include "ProfiledStereotypes.h"
#include "translate.h"

QSize ExtraMemberDialog::previous_size;

ExtraMemberDialog::ExtraMemberDialog(ExtraMemberData * ex)
    : TabDialog(0, 0, FALSE, Qt::WA_DeleteOnClose), emd(ex)
{
    ex->browser_node->edit_start();

    if (ex->browser_node->is_writable()) {
        setOkButton(tr("OK"));
        setCancelButton(tr("Cancel"));
    }
    else {
        setOkButton(QString());
        setCancelButton(tr("Close"));
    }

    bool visit = !hasOkButton();

    setWindowTitle(tr("Extra Class Member dialog"));

    GridBox * grid;

    // general tab

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(tr("name :"), grid));
    grid->addWidget(edname = new LineEdit(ex->name(), grid));
    edname->setReadOnly(visit);

    QFont font = edname->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);

    grid->addWidget(new QLabel(tr("stereotype :"), grid));
    grid->addWidget(edstereotype = new QComboBox(grid));
    edstereotype->setEditable(!visit);
    edstereotype->addItem(toUnicode(ex->get_stereotype()));
    edstereotype->setCurrentIndex(0);

    if (! visit) {
        edstereotype->addItems(ProfiledStereotypes::defaults(UmlExtraMember));
        edstereotype->setAutoCompletion(completion());
    }

    QSizePolicy sp = edstereotype->sizePolicy();

    edstereotype->setSizePolicy(sp);

    VVBox * vtab;
    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(tr("description :"), vtab));

    SmallPushButton *b;
    if (! visit)
    {
        connect(b = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_description()));
        vtab->addWidget(b);
    }

    grid->addWidget(comment = new MultiLineEdit(grid));
    comment->setReadOnly(visit);
    comment->setText(ex->get_browser_node()->get_comment());
    comment->setFont(font);

    addTab(grid, "Uml");

    // C++

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(grid));
    BButtonGroup * gp;
    grid->addWidget(gp =
        new BButtonGroup(1, Qt::Horizontal, QString(), grid));
    gp->addWidget(inline_cb = new QCheckBox("inline", gp));
    inline_cb->setDisabled(visit);

    if (ex->cpp_inline)
        inline_cb->setChecked(TRUE);

    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(tr("C++ \ndeclaration :"), vtab));

    if (! visit)
    {
        connect(b = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_cpp_decl()));
        vtab->addWidget(b);
    }

    grid->addWidget(edcpp_decl = new MultiLineEdit(grid));
    edcpp_decl->setReadOnly(visit);
    edcpp_decl->setText(ex->cpp_decl);
    edcpp_decl->setFont(font);

    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(tr("C++ \ndefinition :"), vtab));

    if (! visit)
    {
        connect(b= new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_cpp_def()));
        vtab->addWidget(b);
    }

    grid->addWidget(edcpp_def = new MultiLineEdit(grid));
    edcpp_def->setReadOnly(visit);
    edcpp_def->setText(ex->cpp_def);
    edcpp_def->setFont(font);

    addTab(grid, "C++");

    if (!GenerationSettings::cpp_get_default_defs())
        removePage(grid);

    // Java

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel("Java :", vtab));
    if (! visit)
    {
        connect(b = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_java_decl()));
        vtab->addWidget(b);
    }

    grid->addWidget(edjava_decl = new MultiLineEdit(grid));
    edjava_decl->setReadOnly(visit);
    edjava_decl->setText(ex->java_decl);
    edjava_decl->setFont(font);

    addTab(grid, "Java");

    if (!GenerationSettings::java_get_default_defs())
        removePage(grid);

    // Php

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel("Php :", vtab));

    if (! visit)
    {
        connect(b = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_php_decl()));
        vtab->addWidget(b);
    }

    grid->addWidget(edphp_decl = new MultiLineEdit(grid));
    edphp_decl->setReadOnly(visit);
    edphp_decl->setText(ex->php_decl);
    edphp_decl->setFont(font);

    addTab(grid, "Php");

    if (!GenerationSettings::php_get_default_defs())
        removePage(grid);

    // Python

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel("Python :", vtab));

    if (! visit)
    {
        connect(b = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_python_decl()));
        vtab->addWidget(b);
    }

    grid->addWidget(edpython_decl = new MultiLineEdit(grid));
    edpython_decl->setReadOnly(visit);
    edpython_decl->setText(ex->python_decl);
    edpython_decl->setFont(font);

    addTab(grid, "Python");

    if (!GenerationSettings::python_get_default_defs())
        removePage(grid);

    // IDL

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel("Idl :", vtab));

    if (! visit)
    {
        connect(b = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_idl_decl()));
        vtab->addWidget(b);
    }

    grid->addWidget(edidl_decl = new MultiLineEdit(grid));
    edidl_decl->setReadOnly(visit);
    edidl_decl->setText(ex->idl_decl);
    edidl_decl->setFont(font);

    addTab(grid, "Idl");

    if (!GenerationSettings::idl_get_default_defs())
        removePage(grid);

    // USER : list key - value

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(kvtable = new KeyValuesTable(ex->get_browser_node(), grid, visit));
    addTab(grid, tr("Properties"));

    open_dialog(this);
}

void ExtraMemberDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::limitsize_move(this, previous_size, 0.8, 0.8);
}

ExtraMemberDialog::~ExtraMemberDialog()
{
    emd->browser_node->edit_end();
    previous_size = size();

    foreach (BodyDialog *dialog, edits)
        dialog->close();
    edits.clear();

    close_dialog(this);
}

void ExtraMemberDialog::accept()
{
    if (!check_edits(edits) || !kvtable->check_unique())
        return;

    BrowserNode * bn = emd->browser_node;
    QString s;

    s = edname->text().trimmed();
    bn->set_name(s);

    bool newst = emd->set_stereotype(fromUnicode(edstereotype->currentText().trimmed()));

    emd->cpp_decl = edcpp_decl->text();
    emd->cpp_def = edcpp_def->text();
    emd->cpp_inline = inline_cb->isChecked();
    emd->java_decl = edjava_decl->text();
    emd->php_decl = edphp_decl->text();
    emd->python_decl = edpython_decl->text();
    emd->idl_decl = edidl_decl->text();

    bn->set_comment(comment->text());
    UmlWindow::update_comment_if_needed(bn);

    kvtable->updateNodeFromThis(bn);

    ProfiledStereotypes::modified(bn, newst);

    bn->modified();
    bn->package_modified();
    emd->modified();

    TabDialog::accept();
}

void ExtraMemberDialog::edit_description()
{
    edit(comment->text(), edname->text().trimmed() + "_description",
         emd, TxtEdit, this, (post_edit) post_edit_description, edits);
}

void ExtraMemberDialog::post_edit_description(ExtraMemberDialog * d, QString s)
{
    d->comment->setText(s);
}

void ExtraMemberDialog::edit_cpp_decl()
{
    edit(edcpp_decl->text(), edname->text().trimmed() + "_class_extra_member_decl",
         emd, CppEdit, this, (post_edit) post_edit_cpp_decl, edits);
}

void ExtraMemberDialog::post_edit_cpp_decl(ExtraMemberDialog * d, QString s)
{
    d->edcpp_decl->setText(s);
}

void ExtraMemberDialog::edit_cpp_def()
{
    edit(edcpp_def->text(), edname->text().trimmed() + "_class_extra_member_def",
         emd, CppEdit, this, (post_edit) post_edit_cpp_def, edits);
}

void ExtraMemberDialog::post_edit_cpp_def(ExtraMemberDialog * d, QString s)
{
    d->edcpp_def->setText(s);
}

void ExtraMemberDialog::edit_java_decl()
{
    edit(edjava_decl->text(), edname->text().trimmed() + "_class_extra_member",
         emd, JavaEdit, this, (post_edit) post_edit_java_decl, edits);
}

void ExtraMemberDialog::post_edit_java_decl(ExtraMemberDialog * d, QString s)
{
    d->edjava_decl->setText(s);
}

void ExtraMemberDialog::edit_php_decl()
{
    edit(edphp_decl->text(), edname->text().trimmed() + "_class_extra_member",
         emd, PhpEdit, this, (post_edit) post_edit_php_decl, edits);
}

void ExtraMemberDialog::post_edit_php_decl(ExtraMemberDialog * d, QString s)
{
    d->edphp_decl->setText(s);
}

void ExtraMemberDialog::edit_python_decl()
{
    edit(edpython_decl->text(), edname->text().trimmed() + "_class_extra_member",
         emd, PythonEdit, this, (post_edit) post_edit_python_decl, edits);
}

void ExtraMemberDialog::post_edit_python_decl(ExtraMemberDialog * d, QString s)
{
    d->edpython_decl->setText(s);
}

void ExtraMemberDialog::edit_idl_decl()
{
    edit(edidl_decl->text(), edname->text().trimmed() + "_class_extra_member",
         emd, TxtEdit, this, (post_edit) post_edit_idl_decl, edits);
}

void ExtraMemberDialog::post_edit_idl_decl(ExtraMemberDialog * d, QString s)
{
    d->edidl_decl->setText(s);
}

