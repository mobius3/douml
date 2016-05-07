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





#include <stdio.h>
#include <gridbox.h>
#include <vvbox.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qfiledialog.h>

#include "PackageDialog.h"
#include "PackageData.h"
#include "GenerationSettings.h"
#include "BrowserPackage.h"
#include "KeyValueTable.h"
#include "UmlWindow.h"
#include "DialogUtil.h"
#include "BrowserView.h"
#include "UmlDesktop.h"
#include "BodyDialog.h"
#include "strutil.h"
#include "ProfiledStereotypes.h"
#include "translate.h"
#include "hhbox.h"
static QString Relative;
static QString Absolute;

QSize PackageDialog::previous_size;

PackageDialog::PackageDialog(PackageData * da)
    : TabDialog(0, 0, FALSE, Qt::WA_DeleteOnClose), pa(da)
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    Relative = QObject::tr("Set it relative");
    Absolute = QObject::tr("Set it absolute");

    da->browser_node->edit_start();

    bool visit = !da->browser_node->is_writable();

    if (!visit) {
        setOkButton(tr("OK"));
        setCancelButton(tr("Cancel"));
    }
    else {
        setOkButton(QString());
        setCancelButton(tr("Close"));
    }

    setWindowTitle(tr("Package dialog"));
    GridBox * grid;
    VVBox * vtab;
    HHBox * htab;
    QPushButton * button;

    // general tab

    grid = new GridBox(2, this);
    umltab = grid;
    grid->setSpacing(5);
    grid->setMargin(5);

    grid->addWidget(new QLabel(tr("name : "), grid));
    grid->addWidget(edname = new LineEdit(pa->name(), grid));
    edname->setReadOnly(!da->browser_node->is_writable() ||
                        (da->browser_node == BrowserView::get_project()));

    grid->addWidget(new QLabel(tr("stereotype : "), grid));
    grid->addWidget(edstereotype = new QComboBox(grid));
    edstereotype->setEditable(!visit);
    edstereotype->addItem(toUnicode(pa->stereotype));

    if (! visit) {
        edstereotype->addItems(BrowserPackage::default_stereotypes());
        edstereotype->addItems(ProfiledStereotypes::defaults(UmlPackage));
        edstereotype->setAutoCompletion(completion());
        connect(edstereotype, SIGNAL(activated(const QString &)),
                this, SLOT(edStereotypeActivated(const QString &)));
    }

    edstereotype->setCurrentIndex(0);
    QSizePolicy sp = edstereotype->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    edstereotype->setSizePolicy(sp);

    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(tr("description :"), vtab));

    SmallPushButton *sButton;
    if (! visit)
    {
        connect(sButton = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_description()));
        vtab->addWidget(sButton);
    }
    grid->addWidget(comment = new MultiLineEdit(grid));
    comment->setReadOnly(visit);
    comment->setText(da->browser_node->get_comment());
    QFont font = comment->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);
    comment->setFont(font);

    addTab(grid, "Uml");

    // C++

    vtab = new VVBox(this);
    cppTab = vtab;
    vtab->setMargin(1);

    vtab->addWidget( htab = new HHBox(vtab));
    htab->setMargin(1);
    htab->addWidget(new QLabel(tr("The generation directories may be relative in case the root directory\n\
is specified (through the project menu entry 'edit generation settings')\n\n"), htab));

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(1);
    QLabel * lbl1;
    htab->addWidget(lbl1 = new QLabel(tr("headers directory : "), htab));
    htab->addWidget(edcpphdir = new LineEdit(pa->cpp_h_dir, htab));

    if (visit)
        edcpphdir->setReadOnly(TRUE);
    else {
        vtab->addWidget(htab = new HHBox(vtab));
        htab->addWidget(new QLabel("", htab));
        htab->addWidget(button = new QPushButton(tr("Browse"), htab));
        connect(button, SIGNAL(clicked()), this, SLOT(cpph_browse()));
        htab->addWidget(new QLabel("", htab));
        htab->addWidget(cpphbutton = new QPushButton((pa->cpp_h_dir.isEmpty() ||
                                      QDir::isRelativePath(pa->cpp_h_dir))
                                     ? Absolute : Relative, htab));

        if (GenerationSettings::get_cpp_root_dir().isEmpty())
            cpphbutton->setEnabled(FALSE);

        connect(cpphbutton, SIGNAL(clicked()), this, SLOT(cpph_relative()));
        htab->addWidget(new QLabel("", htab));
    }

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(1);
    new QLabel("", htab);

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(1);
    QLabel * lbl2;
    htab->addWidget(lbl2 = new QLabel(tr("sources directory : "), htab));
    htab->addWidget(edcppsrcdir = new LineEdit(pa->cpp_src_dir, htab));

    if (visit)
        edcppsrcdir->setReadOnly(TRUE);
    else {
        vtab->addWidget(htab = new HHBox(vtab));
        htab->addWidget(new QLabel("", htab));
        htab->addWidget(button = new QPushButton(tr("Browse"), htab));
        connect(button, SIGNAL(clicked()), this, SLOT(cppsrc_browse()));
        htab->addWidget(new QLabel("", htab));
        htab->addWidget(cppsrcbutton =
            new QPushButton((pa->cpp_src_dir.isEmpty() ||
                             QDir::isRelativePath(pa->cpp_src_dir))
                            ? Absolute : Relative, htab));

        if (GenerationSettings::get_cpp_root_dir().isEmpty())
            cppsrcbutton->setEnabled(FALSE);

        connect(cppsrcbutton, SIGNAL(clicked()), this, SLOT(cppsrc_relative()));
        htab->addWidget(new QLabel("", htab));
    }

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(1);
    htab->addWidget(new QLabel("", htab));

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(5);
    QLabel * lbl3;
    htab->addWidget(lbl3 = new QLabel("namespace : ", htab));
    htab->addWidget(edcppnamespace = new LineEdit(pa->cpp_namespace, htab));
    edcppnamespace->setReadOnly(visit);

    same_width(lbl1, lbl2, lbl3);

    vtab->setStretchFactor(new HHBox(vtab), 1000);

    addTab(vtab, "C++");

    if (!GenerationSettings::cpp_get_default_defs())
        removePage(vtab);

    // Java

    vtab = new VVBox(this);
    javatab = vtab;
    vtab->setMargin(1);

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(1);
    htab->addWidget(new QLabel(tr("The generation directory may be relative in case the root directory\n\
is specified (through the project menu entry 'edit generation settings')\n\n"), htab));

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(1);
    htab->addWidget(lbl1 = new QLabel(tr("directory : "), htab));
    htab->addWidget(edjavadir = new LineEdit(pa->java_dir, htab));

    if (visit)
        edjavadir->setReadOnly(TRUE);
    else {
        vtab->addWidget(htab = new HHBox(vtab));
        htab->addWidget(new QLabel("", htab));
        htab->addWidget(button = new QPushButton(tr("Browse"), htab));
        connect(button, SIGNAL(clicked()), this, SLOT(java_browse()));
        htab->addWidget(new QLabel("", htab));
        htab->addWidget(javabutton = new QPushButton((pa->java_dir.isEmpty() ||
                                      QDir::isRelativePath(pa->java_dir))
                                     ? Absolute : Relative, htab));

        if (GenerationSettings::get_java_root_dir().isEmpty())
            javabutton->setEnabled(FALSE);

        connect(javabutton, SIGNAL(clicked()), this, SLOT(java_relative()));
        htab->addWidget(new QLabel("", htab));
    }

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(1);
    htab->addWidget(new QLabel("", htab));

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(5);
    htab->addWidget(lbl2 = new QLabel("package : ", htab));
    htab->addWidget(edjavapackage = new LineEdit(pa->java_package, htab));
    edjavapackage->setReadOnly(visit);

    same_width(lbl1, lbl2);

    vtab->setStretchFactor(new HHBox(vtab), 1000);

    addTab(vtab, "Java");

    if (!GenerationSettings::java_get_default_defs())
        removePage(vtab);

    // Php

    vtab = new VVBox(this);
    phptab = vtab;
    vtab->setMargin(5);

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(5);
    htab->addWidget(new QLabel(tr("The generation directory may be relative in case the root directory\n\
is specified (through the project menu entry 'edit generation settings')\n\n"), htab));

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(5);
    htab->addWidget(lbl1 = new QLabel(tr("directory : "), htab));
    htab->addWidget(edphpdir = new LineEdit(pa->php_dir, htab));

    if (visit)
        edphpdir->setReadOnly(TRUE);
    else {
        vtab->addWidget(htab = new HHBox(vtab));
        htab->addWidget(new QLabel("", htab));
        htab->addWidget(button = new QPushButton(tr("Browse"), htab));
        connect(button, SIGNAL(clicked()), this, SLOT(php_browse()));
        htab->addWidget(new QLabel("", htab));
        htab->addWidget(phpbutton = new QPushButton((pa->php_dir.isEmpty() ||
                                     QDir::isRelativePath(pa->php_dir))
                                    ? Absolute : Relative, htab));

        if (GenerationSettings::get_php_root_dir().isEmpty())
            phpbutton->setEnabled(FALSE);

        connect(phpbutton, SIGNAL(clicked()), this, SLOT(php_relative()));
        htab->addWidget(new QLabel("", htab));
    }

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(5);
    htab->addWidget(new QLabel("", htab));

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(5);
    htab->addWidget(lbl2 = new QLabel("namespace : ", htab));
    htab->addWidget(edphpnamespace = new LineEdit(pa->php_namespace, htab));
    edphpnamespace->setReadOnly(visit);

    same_width(lbl1, lbl2);

    vtab->setStretchFactor(new HHBox(vtab), 1000);

    addTab(vtab, "Php");

    if (!GenerationSettings::php_get_default_defs())
        removePage(vtab);

    // Python

    vtab = new VVBox(this);
    pythontab = vtab;
    vtab->setMargin(5);

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(5);
    htab->addWidget(new QLabel(tr("The generation directory may be relative in case the root directory\n\
is specified (through the project menu entry 'edit generation settings')\n\n"), htab));

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(5);
    htab->addWidget(lbl1 = new QLabel(tr("directory : "), htab));
    htab->addWidget(edpythondir = new LineEdit(pa->python_dir, htab));

    if (visit)
        edpythondir->setReadOnly(TRUE);
    else {
        vtab->addWidget(htab = new HHBox(vtab));
        htab->addWidget(new QLabel("", htab));
        htab->addWidget(button = new QPushButton(tr("Browse"), htab));
        connect(button, SIGNAL(clicked()), this, SLOT(python_browse()));
       htab->addWidget( new QLabel("", htab));
        htab->addWidget(pythonbutton = new QPushButton((pa->python_dir.isEmpty() ||
                                        QDir::isRelativePath(pa->python_dir))
                                       ? Absolute : Relative, htab));

        if (GenerationSettings::get_python_root_dir().isEmpty())
            pythonbutton->setEnabled(FALSE);

        connect(pythonbutton, SIGNAL(clicked()), this, SLOT(python_relative()));
        htab->addWidget(new QLabel("", htab));
    }

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(5);
    htab->addWidget(new QLabel("", htab));

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(5);
    htab->addWidget(lbl2 = new QLabel("package : ", htab));
    htab->addWidget(edpythonpackage = new LineEdit(pa->python_package, htab));
    edpythonpackage->setReadOnly(visit);

    same_width(lbl1, lbl2);

    vtab->setStretchFactor(new HHBox(vtab), 1000);

    addTab(vtab, "Python");

    if (!GenerationSettings::python_get_default_defs())
        removePage(vtab);

    // IDL

    vtab = new VVBox(this);
    idltab = vtab;
    vtab->setMargin(5);

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(5);
    htab->addWidget(new QLabel(tr("The generation directory may be relative in case the root directory\n\
is specified (through the project menu entry 'edit generation settings')\n\n"), htab));

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(5);
    htab->addWidget(lbl1 = new QLabel(tr("directory : "), htab));
    htab->addWidget(edidldir = new LineEdit(pa->idl_dir, htab));

    if (visit)
        edidldir->setReadOnly(TRUE);
    else {
        vtab->addWidget(htab = new HHBox(vtab));
        htab->addWidget(new QLabel("", htab));
        htab->addWidget(button = new QPushButton(tr("Browse"), htab));
        connect(button, SIGNAL(clicked()), this, SLOT(idl_browse()));
        htab->addWidget(new QLabel("", htab));
        htab->addWidget(idlbutton = new QPushButton((pa->idl_dir.isEmpty() ||
                                     QDir::isRelativePath(pa->idl_dir))
                                    ? Absolute : Relative, htab));

        if (GenerationSettings::get_idl_root_dir().isEmpty())
            idlbutton->setEnabled(FALSE);

        connect(idlbutton, SIGNAL(clicked()), this, SLOT(idl_relative()));
        htab->addWidget(new QLabel("", htab));
    }

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(5);
    htab->addWidget(new QLabel("", htab));

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(5);
    htab->addWidget(lbl2 = new QLabel("module : ", htab));
    htab->addWidget(edidlmodule = new LineEdit(pa->idl_module, htab));
    edidlmodule->setReadOnly(visit);

    same_width(lbl1, lbl2);

    vtab->setStretchFactor(new HHBox(vtab), 1000);

    addTab(vtab, "IDL");

    if (!GenerationSettings::idl_get_default_defs())
        removePage(vtab);

    // Profile

    vtab = new VVBox(this);
    profiletab = vtab;
    vtab->setMargin(5);

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(5);
    htab->addWidget(new QLabel("", htab));

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(5);
    htab->addWidget(lbl1 = new QLabel(tr("meta model : \nreference"), htab));
    htab->addWidget(edmetamodelReference =
        new LineEdit(pa->browser_node->get_value("metamodelReference"), htab));
    edmetamodelReference->setReadOnly(visit);

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(5);
    htab->addWidget(new QLabel("", htab));

    vtab->addWidget(htab = new HHBox(vtab));
    htab->setMargin(5);
    htab->addWidget(lbl2 = new QLabel(tr("meta class : \nreference"), htab));
    htab->addWidget(edmetaclassreference =
        new LineEdit(pa->browser_node->get_value("metaclassreference"), htab));
    edidlmodule->setReadOnly(visit);

    same_width(lbl1, lbl2);

    vtab->setStretchFactor(new HHBox(vtab), 1000);

    addTab(vtab, QObject::tr("Profile"));

    // USER : list key - value

    vtab = new VVBox(this);
    vtab->addWidget(kvtable = new KeyValuesTable(da->browser_node, vtab, visit));

    kvtable->remove("metamodelReference");
    kvtable->remove("metaclassreference");
    addTab(vtab, QObject::tr("Properties"));

    //

    edStereotypeActivated(edstereotype->currentText());
    connect(this->m_tabWidget, SIGNAL(currentChanged(int)),
            this, SLOT(change_tabs(int)));

    open_dialog(this);
}

void PackageDialog::polish()
{
    QDialog::ensurePolished();
    UmlDesktop::limitsize_move(this, previous_size, 0.8, 0.8);
}

PackageDialog::~PackageDialog()
{
    pa->browser_node->edit_end();
    previous_size = size();
    foreach (BodyDialog *dialog, edits)
        dialog->close();
    edits.clear();

    close_dialog(this);
}

void PackageDialog::edStereotypeActivated(const QString & s)
{
    bool np = (s.trimmed() != "profile");
    if (GenerationSettings::cpp_get_default_defs())
        setTabEnabled(cppTab, np);

    if (GenerationSettings::java_get_default_defs())
        setTabEnabled(javatab, np);

    if (GenerationSettings::idl_get_default_defs())
        setTabEnabled(idltab, np);

    if (GenerationSettings::php_get_default_defs())
        setTabEnabled(phptab, np);

    if (GenerationSettings::python_get_default_defs())
        setTabEnabled(pythontab, np);

    setTabEnabled(profiletab, !np);
    if (!np &&
        edmetamodelReference->text().simplified().isEmpty() &&
        edmetaclassreference->text().simplified().isEmpty())
        edmetamodelReference->setText("http://schema.omg.org/spec/UML/2.1/uml.xml");
}

void PackageDialog::change_tabs(int index)
{
    QWidget * w = m_tabWidget->widget(index);
    if (hasOkButton()) {
        if (w == umltab)
            edname->setFocus();
        else if (w == cppTab)
            edcpphdir->setFocus();
        else if (w == javatab)
            edjavadir->setFocus();
        else if (w == phptab)
            edphpdir->setFocus();
        else if (w == pythontab)
            edpythondir->setFocus();
        else if (w == idltab)
            edidldir->setFocus();
    }
}

void PackageDialog::edit_description()
{
    edit(comment->text(), edname->text().trimmed() + "_description",
         pa, TxtEdit, this, (post_edit) post_edit_description, edits);

}

void PackageDialog::post_edit_description(PackageDialog * d, QString s)
{
    d->comment->setText(s);
}

void PackageDialog::accept()
{
    if (!check_edits(edits) || !kvtable->check_unique())
        return;

    BrowserPackage * bn = (BrowserPackage *) pa->browser_node;
    QString oldname = pa->name();
    bool was_pr = !strcmp(pa->get_stereotype(), "profile");
    QString st = fromUnicode(edstereotype->currentText().trimmed());
    QString s;

    s = edname->text().trimmed();

    if (s != oldname) {
        if (((BrowserNode *) bn->parent())->wrong_child_name(s, UmlPackage,
                bn->allow_spaces(),
                bn->allow_empty())) {
            msg_critical(tr("Error"), s + QObject::tr("\n\nillegal name or already used"));
            return;
        }

        if ((st == "profile") && !ProfiledStereotypes::canAddPackage(bn, s)) {
            msg_critical(tr("Error"), QObject::tr("conflict on stereotypes"));
            return;
        }

        bn->set_name(s);
    }
    else if ((st == "profile") &&
             !was_pr &&
             !ProfiledStereotypes::canAddPackage(bn, s)) {
        msg_critical(tr("Error"), QObject::tr("conflict on stereotypes"));
        return;
    }

    bool newst = pa->set_stereotype(st);

    pa->cpp_h_dir = edcpphdir->text().simplified();
    pa->cpp_src_dir = edcppsrcdir->text().simplified();
    pa->cpp_namespace = edcppnamespace->text().simplified();
    pa->java_dir = edjavadir->text().simplified();
    pa->java_package = edjavapackage->text().simplified();
    pa->php_dir = edphpdir->text().simplified();
    pa->php_namespace = edphpnamespace->text().simplified();
    pa->python_dir = edpythondir->text().simplified();
    pa->python_package = edpythonpackage->text().simplified();
    pa->idl_dir = edidldir->text().simplified();
    pa->idl_module = edidlmodule->text().simplified();

    bn->set_comment(comment->text());
    UmlWindow::update_comment_if_needed(bn);

    kvtable->updateNodeFromThis(bn);

    if (st == "profile") {
        unsigned n = bn->get_n_keys();

        bn->set_n_keys(n + 2);
        bn->set_key(n, "metamodelReference");
        bn->set_value(n, fromUnicode(edmetamodelReference->text().simplified()));
        bn->set_key(n + 1, "metaclassreference");
        bn->set_value(n + 1, fromUnicode(edmetaclassreference->text().simplified()));

        if (was_pr && (oldname != bn->get_name()))
            ProfiledStereotypes::renamed(bn, oldname);
    }
    else if (was_pr) {
        bool propag = (msg_warning(tr("Question"),
                                   QObject::tr("Propagate the removal of the profile ?"),
                                   1, 2)
                       == 1);

        ProfiledStereotypes::deleted(bn, propag);
    }

    ProfiledStereotypes::modified(bn, newst);

    bn->package_modified();
    pa->modified();
    QDialog::accept();
}

void PackageDialog::browse(LineEdit * ed, QPushButton * button,
                           QString caption, QString root)
{
    QString s = ed->text();
    bool rel = FALSE;

    if (s.isNull())
        s = root;
    else if (!root.isEmpty() && QDir::isRelativePath(s)) {
        rel = TRUE;
        s = root + s;
    }

    const QString ns = QFileDialog::getExistingDirectory(this, caption, s);


    if (! ns.isNull()) {
        int len = root.length();

        if (rel &&
            (ns.indexOf(root) == 0) &&
            (ns.length() >= len))
            ed->setText(ns.mid(len));
        else {
            ed->setText(ns);
            button->setText(Relative);
        }
    }
}

void PackageDialog::cpph_browse()
{
    browse(edcpphdir, cpphbutton, QObject::tr("C++ header directory"),
           GenerationSettings::get_cpp_root_dir());
}

void PackageDialog::cppsrc_browse()
{
    browse(edcppsrcdir, cppsrcbutton, QObject::tr("C++ source directory"),
           GenerationSettings::get_cpp_root_dir());
}

void PackageDialog::java_browse()
{
    browse(edjavadir, javabutton, QObject::tr("Java directory"),
           GenerationSettings::get_java_root_dir());
}

void PackageDialog::php_browse()
{
    browse(edphpdir, phpbutton, QObject::tr("Php directory"),
           GenerationSettings::get_php_root_dir());
}

void PackageDialog::python_browse()
{
    browse(edpythondir, pythonbutton, QObject::tr("Python directory"),
           GenerationSettings::get_python_root_dir());
}

void PackageDialog::idl_browse()
{
    browse(edidldir, idlbutton, QObject::tr("Idl directory"),
           GenerationSettings::get_idl_root_dir());
}

void PackageDialog::relative(LineEdit * ed, QPushButton * button,
                             QString root)
{
    const QString s = QDir::toNativeSeparators(ed->text());

    if (QDir::isRelativePath(root))
        root = BrowserView::get_dir().filePath(root);

    if (button->text() == Relative) {
        int len = root.length();

        if (
            (s.indexOf(root) == 0) &&
            (s.length() >= len)) {
            ed->setText(s.mid(len));
            button->setText(Absolute);
        }
    }
    else {
        ed->setText(root + s);
        button->setText(Relative);
    }
}

void PackageDialog::cpph_relative()
{
    relative(edcpphdir, cpphbutton, GenerationSettings::get_cpp_root_dir());
}

void PackageDialog::cppsrc_relative()
{
    relative(edcppsrcdir, cppsrcbutton, GenerationSettings::get_cpp_root_dir());
}

void PackageDialog::java_relative()
{
    relative(edjavadir, javabutton, GenerationSettings::get_java_root_dir());
}

void PackageDialog::php_relative()
{
    relative(edphpdir, phpbutton, GenerationSettings::get_php_root_dir());
}

void PackageDialog::python_relative()
{
    relative(edpythondir, pythonbutton, GenerationSettings::get_python_root_dir());
}

void PackageDialog::idl_relative()
{
    relative(edidldir, idlbutton, GenerationSettings::get_idl_root_dir());
}
