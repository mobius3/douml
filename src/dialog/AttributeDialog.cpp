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






#include <qlabel.h>
#include <qcombobox.h>
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qradiobutton.h>
#include <qpushbutton.h>
//#include <q3popupmenu.h>
#include <qcursor.h>
//Added by qt3to4:


#include "AttributeDialog.h"
#include "AttributeData.h"
#include "ClassData.h"
#include "BrowserView.h"
#include "BrowserClass.h"
#include "BrowserAttribute.h"
#include "BrowserOperation.h"
#include "KeyValueTable.h"
#include "UmlWindow.h"
#include "UmlDesktop.h"
#include "DialogUtil.h"
#include "GenerationSettings.h"
#include "strutil.h"
#include "BodyDialog.h"
#include "AnnotationDialog.h"
#include "ProfiledStereotypes.h"
#include "translate.h"
#include "gridbox.h"
#include "hhbox.h"
#include "bbuttongroup.h"
#include "vvbox.h"
#include "menufactory.h"
QSize AttributeDialog::previous_size;

AttributeDialog::AttributeDialog(AttributeData * a, bool new_st_attr)
    : TabDialog(0, 0, true, Qt::WA_DeleteOnClose),
      new_in_st(new_st_attr), att(a)
{
    a->browser_node->edit_start();

    if (a->browser_node->is_writable()) {
        setOkButton(tr("OK"));
        setCancelButton(tr("Cancel"));
    }
    else {
        setOkButton(QString());
        setCancelButton(tr("Close"));
    }

    visit = !hasOkButton();
    ClassData * cld = (ClassData *)
                      ((BrowserNode *) a->browser_node->parent())->get_data();
    QString stereotype = cld->get_stereotype();
    QString lang_st;

    in_enum = (stereotype == "enum");

    lang_st = GenerationSettings::cpp_class_stereotype(stereotype);
    cpp_in_enum = in_enum || (lang_st == "enum");
    cpp_ignored = !cpp_in_enum && ((lang_st == "typedef") || (lang_st == "ignored"));

    lang_st = GenerationSettings::java_class_stereotype(stereotype);
    java_in_enum = in_enum || (lang_st == "enum");
    java_in_enum_pattern = !java_in_enum && (lang_st == "enum_pattern");
    java_ignored = (lang_st == "ignored");

    lang_st = GenerationSettings::php_class_stereotype(stereotype);
    php_in_enum = in_enum || (lang_st == "enum");
    php_ignored = !php_in_enum && (lang_st == "ignored");

    lang_st = GenerationSettings::python_class_stereotype(stereotype);
    python_in_enum = in_enum || (lang_st == "enum");
    python_ignored = !python_in_enum && (lang_st == "ignored");

    lang_st = GenerationSettings::idl_class_stereotype(stereotype);
    idl_in_enum = in_enum || (lang_st == "enum");
    idl_in_typedef = !idl_in_enum && (lang_st == "typedef");
    idl_in_struct = !idl_in_enum && ((lang_st == "struct") || (lang_st == "exception"));
    idl_in_union = !idl_in_enum && (lang_st == "union");

    setCaption((in_enum || java_in_enum_pattern) ? tr("Enum item dialog") : tr("Attribute dialog"));

    GridBox * grid;
    HHBox * htab;
    QString s;
    SmallPushButton* pButton;
    // general tab

    grid = new GridBox(2, this);
    umltab = grid;
    grid->setMargin(2);
    grid->setSpacing(2);

    grid->addWidget(new QLabel(tr("class : "), grid));
    grid->addWidget(new QLabel(((BrowserNode *) a->get_browser_node()->parent())->full_name(TRUE),
               grid));

    grid->addWidget(new QLabel(tr("name :"), grid));
    edname = new LineEdit(a->name(), grid);
    grid->addWidget(edname);
    edname->setReadOnly(visit);

    QFont font = edname->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);

    if (!java_in_enum_pattern) {
        grid->addWidget(new QLabel(tr("stereotype :"), grid));
        htab = new HHBox(grid);
        grid->addWidget(htab);
        edstereotype = new QComboBox(htab);
        htab->addWidget(edstereotype);
        edstereotype->setEditable(!visit);
        edstereotype->addItem(toUnicode(a->get_stereotype()));

        if (!visit) {
//
           QStringList list1 =  BrowserAttribute::default_stereotypes();
           QStringList list2 =  ProfiledStereotypes::defaults(UmlAttribute);
            edstereotype->addItems(BrowserAttribute::default_stereotypes());
            edstereotype->addItems(ProfiledStereotypes::defaults(UmlAttribute));

            if (java_in_enum) {
                int n = edstereotype->count();

                for (attribute_st_rank = 0; attribute_st_rank != n; attribute_st_rank += 1)
                    if (edstereotype->itemText(attribute_st_rank) == "attribute")
                        break;

                if (attribute_st_rank == n) {
                    edstereotype->addItem("attribute");
                    n += 1;
                }

                for (empty_st_rank = 0; empty_st_rank != n; empty_st_rank += 1)
                    if (edstereotype->itemText(empty_st_rank).isEmpty())
                        break;

                if (empty_st_rank == n)
                    edstereotype->addItem("");
            }

            edstereotype->setAutoCompletion(completion());
        }
        edstereotype->setCurrentIndex(0);

        QSizePolicy sp = edstereotype->sizePolicy();

        sp.setHorizontalPolicy(QSizePolicy::Expanding);
        edstereotype->setSizePolicy(sp);

        htab->addWidget(new QLabel(tr("    multiplicity :  "), htab));
        multiplicity = new QComboBox( htab);
        htab->addWidget(multiplicity);
        multiplicity->setEditable(!visit);
        multiplicity->setSizePolicy(sp);
        previous_multiplicity = a->get_multiplicity();
        multiplicity->addItem(previous_multiplicity);

        if (!visit) {
            multiplicity->addItem("1");
            multiplicity->addItem("0..1");
            multiplicity->addItem("*");
            multiplicity->addItem("1..*");
        }
        connect(pButton = new SmallPushButton(tr("type :"), grid), SIGNAL(clicked()),
                this, SLOT(menu_type()));
        grid->addWidget(pButton);
        edtype = new QComboBox( grid);
        grid->addWidget(edtype);
        edtype->setEditable(!visit);
        edtype->addItem(a->get_type().get_full_type());
        BrowserClass::instances(nodes);
        nodes.full_names(list);

        if (!visit) {
            QStringList l = GenerationSettings::basic_types();

            cld->addFormals(l);
            edtype->addItems(l);
            offset = edtype->count();
            edtype->addItems(list);
            edtype->setAutoCompletion(completion());
            view = a->browser_node->container(UmlClass);
        }

        edtype->setCurrentIndex(0);
        edtype->setSizePolicy(sp);

        grid->addWidget(new QLabel(tr("initial value :"), grid));
    }
    else {
        multiplicity = 0;
        grid->addWidget(new QLabel(tr("value :"), grid));
    }
    htab = new HHBox(grid);
    grid->addWidget(htab);
    edinit = new LineEdit(a->get_init_value_qstring(), htab);
    htab->addWidget(edinit);

    if (visit)
        edinit->setReadOnly(TRUE);
    else
        connect( pButton = new SmallPushButton(tr("Editor"), htab), SIGNAL(clicked()),
                this, SLOT(edit_init()));
    htab->addWidget(pButton);
    BButtonGroup * bg;

    if (!java_in_enum_pattern) {
        grid->addWidget(new QLabel(grid));

        htab = new HHBox(grid);
        grid->addWidget(htab);
        bg = uml_visibility.init(htab, a->get_uml_visibility(), TRUE);
        htab->addWidget(bg);
        if (visit)
            bg->setEnabled(FALSE);

        bg = new BButtonGroup(7, Qt::Horizontal, QString(), htab);
        htab->addWidget(bg);
        bg->setExclusive(FALSE);
        classattribute_cb = new QCheckBox("static", bg);
        bg->addWidget(classattribute_cb);

        if (a->get_isa_class_attribute())
            classattribute_cb->setChecked(TRUE);

        classattribute_cb->setDisabled(visit);

        volatile_cb = new QCheckBox("volatile", bg);
        bg->addWidget(volatile_cb);

        if (a->isa_volatile_attribute)
            volatile_cb->setChecked(TRUE);

        volatile_cb->setDisabled(visit);

        constattribute_cb = new QCheckBox(tr("read-only"), bg);
        bg->addWidget(constattribute_cb);

        if (a->get_isa_const_attribute())
            constattribute_cb->setChecked(TRUE);

        constattribute_cb->setDisabled(visit);

        derived_cb = new QCheckBox(tr("derived"), bg);
        bg->addWidget(derived_cb);
        if (a->get_is_derived())
            derived_cb->setChecked(TRUE);

        derived_cb->setDisabled(visit);
        connect(derived_cb, SIGNAL(toggled(bool)), SLOT(derived_changed(bool)));
        derivedunion_cb = new QCheckBox("union", bg);
        bg->addWidget(derivedunion_cb);
        if (a->get_is_derivedunion())
            derivedunion_cb->setChecked(TRUE);

        derivedunion_cb->setDisabled(visit || !derived_cb->isChecked());

        ordered_cb = new QCheckBox(tr("ordered"), bg);
        bg->addWidget(ordered_cb);
        if (a->get_is_ordered())
            ordered_cb->setChecked(TRUE);

        ordered_cb->setDisabled(visit);

        unique_cb = new QCheckBox("unique", bg);
        bg->addWidget(unique_cb);
        if (a->get_is_unique())
            unique_cb->setChecked(TRUE);

        unique_cb->setDisabled(visit);
    }

    VVBox * vtab = new VVBox(grid);
    grid->addWidget(vtab);

    new QLabel(tr("description :"), vtab);

    if (! visit) {
        connect(pButton = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_description()));
        vtab->addWidget(pButton);
        connect(pButton = new SmallPushButton(tr("Default"), vtab), SIGNAL(clicked()),
                this, SLOT(default_description()));
        vtab->addWidget(pButton);
    }

    comment = new MultiLineEdit(grid);
    grid->addWidget(comment);
    comment->setReadOnly(visit);
    QString temp =  a->browser_node->get_comment();
    comment->setText(temp);
    comment->setFont(font);

    vtab = new VVBox(grid);
    grid->addWidget(vtab);
    vtab->addWidget(new QLabel(tr("constraint :"), vtab));

    if (! visit) {
        connect(pButton = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_constraint()));
        vtab->addWidget(pButton);
    }

    constraint = new MultiLineEdit(grid);
    grid->addWidget(constraint);
    constraint->setReadOnly(visit);
    constraint->setText(a->constraint);
    constraint->setFont(font);
    addTab(grid, "Uml");

    // C++

    if (! cpp_ignored) {
        grid = new GridBox(2, this);
        cppTab = grid;
        grid->setMargin(0);
        grid->setSpacing(0);

        if (!cpp_in_enum) {
            grid->addWidget(new QLabel(tr("Visibility :"), grid));
            htab = new HHBox(grid);
            grid->addWidget(htab);
            BButtonGroup * bg =
                cpp_visibility.init((QWidget *)htab, a->get_cpp_visibility(), FALSE, NULL, tr("follow uml"));

            htab->addWidget(bg);
            if (visit)
                bg->setEnabled(FALSE);

            htab->addWidget(new QLabel(" ", htab));

            htab->addWidget(mutable_cb = new QCheckBox("mutable", htab));

            if (a->cpp_mutable)
                mutable_cb->setChecked(TRUE);

            if (visit)
                mutable_cb->setDisabled(TRUE);
            else
                connect(mutable_cb, SIGNAL(toggled(bool)), this, SLOT(cpp_update()));
        }

        grid->addWidget(new QLabel(tr("Declaration :"), grid));
        edcppdecl = new MultiLineEdit(grid);
        grid->addWidget(edcppdecl);
        edcppdecl->setText(a->get_cppdecl());
        edcppdecl->setFont(font);

        if (visit)
            edcppdecl->setReadOnly(TRUE);
        else
            connect(edcppdecl, SIGNAL(textChanged()), this, SLOT(cpp_update()));

        grid->addWidget(new QLabel(tr("Result after\nsubstitution :"), grid));
        showcppdecl = new MultiLineEdit(grid);
        grid->addWidget(showcppdecl);
        showcppdecl->setReadOnly(TRUE);
        showcppdecl->setFont(font);

        if (! visit) {
            grid->addWidget(new QLabel(grid));
            htab = new HHBox(grid);
            grid->addWidget(htab);
            QPushButton *button;
            connect(button = new QPushButton(tr("Default declaration"), htab), SIGNAL(clicked()),
                    this, SLOT(cpp_default()));
            htab->addWidget(button);
            connect(button = new QPushButton(tr("Not generated in C++"), htab), SIGNAL(clicked()),
                    this, SLOT(cpp_unmapped()));
            htab->addWidget(button);
        }

        addTab(grid, "C++");

        if (!GenerationSettings::cpp_get_default_defs())
            removePage(grid);
    }
    else
        cppTab = 0;

    // Java

    if (! java_ignored) {
        grid = new GridBox(2, this);
        javatab = grid;
        grid->setMargin(0);
        grid->setSpacing(0);

        if (!java_in_enum && !java_in_enum_pattern) {
            grid->addWidget(new QLabel("", grid));
            transient_cb = new QCheckBox("transient", grid);
            grid->addWidget(transient_cb);
            if (a->java_transient)
                transient_cb->setChecked(TRUE);

            if (visit)
                transient_cb->setDisabled(TRUE);
            else
                connect(transient_cb, SIGNAL(toggled(bool)), this, SLOT(java_update()));
        }

        grid->addWidget(new QLabel(tr("Declaration :"), grid));
        edjavadecl = new MultiLineEdit(grid);
        grid->addWidget(edjavadecl);
        edjavadecl->setText(a->get_javadecl());
        edjavadecl->setFont(font);

        if (visit)
            edjavadecl->setReadOnly(TRUE);
        else
            connect(edjavadecl, SIGNAL(textChanged()), this, SLOT(java_update()));

        grid->addWidget(new QLabel(tr("Result after\nsubstitution :"), grid));
        showjavadecl = new MultiLineEdit(grid);
        grid->addWidget(showjavadecl);
        showjavadecl->setReadOnly(TRUE);
        showjavadecl->setFont(font);

        grid->addWidget(new QLabel(grid));
        htab = new HHBox(grid);
        grid->addWidget(htab);
        if (! visit) {
            QPushButton *button;

            if (java_in_enum) {
                connect(button = new QPushButton(tr("Default item declaration"), htab), SIGNAL(clicked()),
                        this, SLOT(java_default_item()));
                htab->addWidget(button);
                connect(button = new QPushButton(tr("Default attribute declaration"), htab), SIGNAL(clicked()),
                        this, SLOT(java_default()));
                htab->addWidget(button);
            }
            else
            {
                connect(button = new QPushButton(tr("Default declaration"), htab), SIGNAL(clicked()),
                        this, SLOT(java_default()));
                htab->addWidget(button);
            }

            connect(button = new QPushButton(tr("Not generated in Java"), htab), SIGNAL(clicked()),
                    this, SLOT(java_unmapped()));
            htab->addWidget(button);

        }

        javaannotation = (const char *) a->java_annotation;
        htab->addWidget(editjavaannotation =
            new QPushButton((visit) ? tr("Show annotation") : tr("Edit annotation"),
                            htab));
        connect(editjavaannotation, SIGNAL(clicked()),
                this, SLOT(java_edit_annotation()));

        addTab(grid, "Java");

        if (!GenerationSettings::java_get_default_defs())
            removePage(grid);
    }
    else
        javatab = 0;

    // Php

    if (! php_ignored) {
        python_self =
            BrowserOperation::python_init_self((BrowserNode *) a->browser_node->parent())
            + ".";

        grid = new GridBox(2, this);
        phptab = grid;
        grid->setMargin(0);
        grid->setSpacing(0);

        grid->addWidget(new QLabel(tr("Declaration :"), grid));
        edphpdecl = new MultiLineEdit(grid);
        grid->addWidget(edphpdecl);
        edphpdecl->setText(a->get_phpdecl());
        edphpdecl->setFont(font);

        if (visit)
            edphpdecl->setReadOnly(TRUE);
        else
            connect(edphpdecl, SIGNAL(textChanged()), this, SLOT(php_update()));

        grid->addWidget(new QLabel(tr("Result after\nsubstitution :"), grid));
        showphpdecl = new MultiLineEdit(grid);
        grid->addWidget(showphpdecl);
        showphpdecl->setReadOnly(TRUE);
        showphpdecl->setFont(font);

        grid->addWidget(new QLabel(grid));
        htab = new HHBox(grid);
        grid->addWidget(htab);
        if (! visit) {
            QPushButton *button;
            connect(button = new QPushButton(tr("Default declaration"), htab), SIGNAL(clicked()),
                    this, SLOT(php_default()));
            htab->addWidget(button);
            connect(button = new QPushButton(tr("Not generated in Php"), htab), SIGNAL(clicked()),
                    this, SLOT(php_unmapped()));
            htab->addWidget(button);
        }

        addTab(grid, "Php");

        if (!GenerationSettings::php_get_default_defs())
            removePage(grid);
    }
    else
        phptab = 0;

    // Python

    if (! python_ignored) {
        grid = new GridBox(2, this);
        pythontab = grid;
        grid->setMargin(0);
        grid->setSpacing(0);

        grid->addWidget(new QLabel(tr("Declaration :"), grid));
        edpythondecl = new MultiLineEdit(grid);
        grid->addWidget(edpythondecl);
        edpythondecl->setText(a->get_pythondecl());
        edpythondecl->setFont(font);

        if (visit)
            edpythondecl->setReadOnly(TRUE);
        else
            connect(edpythondecl, SIGNAL(textChanged()), this, SLOT(python_update()));

        grid->addWidget(new QLabel(tr("Result after\nsubstitution :"), grid));
        showpythondecl = new MultiLineEdit(grid);
        grid->addWidget(showpythondecl);
        showpythondecl->setReadOnly(TRUE);
        showpythondecl->setFont(font);

        grid->addWidget(new QLabel(grid));
        htab = new HHBox(grid);
        grid->addWidget(htab);
        if (! visit) {
            QPushButton* button;
            connect(button = new QPushButton(tr("Default declaration"), htab), SIGNAL(clicked()),
                    this, SLOT(python_default()));
            htab->addWidget(button);
            connect(button =  new QPushButton(tr("Not generated in Python"), htab), SIGNAL(clicked()),
                    this, SLOT(python_unmapped()));
            htab->addWidget(button);
        }

        addTab(grid, "Python");

        if (!GenerationSettings::python_get_default_defs())
            removePage(grid);
    }
    else
        pythontab = 0;

    // IDL

    if (! idl_in_typedef) {
        grid = new GridBox(2, this);
        idltab = grid;
        grid->setMargin(0);
        grid->setSpacing(0);

        if (idl_in_union) {
            grid->addWidget(new QLabel("Case :", grid));
            edcase = new QComboBox( grid);
            grid->addWidget(edcase);
            edcase->setEditable(TRUE);
            edcase->addItem(a->get_idlcase());

            if (! visit) {
                AType switch_type = cld->get_switch_type();

                if (switch_type.type != 0) {
                    switch_type.type->children(enums, UmlAttribute);
                    enums.names(enum_names);
                    edcase->addItems(enum_names);
                    edcase->setAutoCompletion(completion());
                }
            }

            edcase->setCurrentIndex(0);

            QSizePolicy sp = edcase->sizePolicy();

            sp.setHorizontalPolicy(QSizePolicy::Expanding);
            edcase->setSizePolicy(sp);

            if (! visit)
                connect(edcase, SIGNAL(activated(int)), this, SLOT(idl_update()));
        }

        grid->addWidget(new QLabel(tr("Declaration :"), grid));
        edidldecl = new MultiLineEdit(grid);
        grid->addWidget(edidldecl);
        edidldecl->setText(a->get_idldecl());
        edidldecl->setFont(font);

        if (visit)
            edidldecl->setReadOnly(TRUE);
        else
            connect(edidldecl, SIGNAL(textChanged()), this, SLOT(idl_update()));

        grid->addWidget(new QLabel(tr("Result after\nsubstitution :"), grid));
        showidldecl = new MultiLineEdit(grid);
        grid->addWidget(showidldecl);
        showidldecl->setReadOnly(TRUE);
        showidldecl->setFont(font);

        if (! visit) {
            grid->addWidget(new QLabel(grid));
            htab = new HHBox(grid);
            grid->addWidget(htab);
            QPushButton *button;
            connect(button = new QPushButton((idl_in_enum) ? tr("Default declaration")
                                    : tr("Default attribute declaration"),
                                    htab),
                    SIGNAL(clicked()), this, SLOT(idl_default()));
            htab->addWidget(button);

            if (!idl_in_enum && !idl_in_union) {
                if (!idl_in_struct)
                {
                    connect(button = new QPushButton(tr("Default state declaration"), htab), SIGNAL(clicked()),
                            this, SLOT(idl_default_state()));
                    htab->addWidget(button);
                }

                connect(button = new QPushButton(tr("Default constant declaration"), htab), SIGNAL(clicked()),
                        this, SLOT(idl_default_constant()));
                htab->addWidget(button);
            }

            connect(button = new QPushButton(tr("Not generated in Idl"), htab), SIGNAL(clicked()),
                    this, SLOT(idl_unmapped()));
            htab->addWidget(button);
        }

        addTab(grid, "Idl");

        if (!GenerationSettings::idl_get_default_defs())
            removePage(grid);
    }
    else
        idltab = 0;

    // USER : list key - value

    grid = new GridBox(2, this);
    grid->setMargin(0);
    grid->setSpacing(0);

    kvtable = new KeyValuesTable(a->browser_node, grid, visit);
    grid->addWidget(kvtable);
    addTab(grid, tr("Properties"));

    //

    connect(m_tabWidget, SIGNAL(currentChanged(int)),
            this, SLOT(update_all_tabs(int)));

    open_dialog(this);
}

AttributeDialog::~AttributeDialog()
{
    att->browser_node->edit_end();
    previous_size = size();

    foreach (BodyDialog *dialog, edits)
        dialog->close();
    edits.clear();

    if (new_in_st)
        // new_in_st cleared by accept
        ProfiledStereotypes::added((BrowserAttribute *) att->browser_node);

    close_dialog(this);
}

void AttributeDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::limitsize_center(this, previous_size, 0.8, 0.8);
}

void AttributeDialog::default_defs_if_needed()
{
    QString m = multiplicity->currentText().trimmed();

    if (m != previous_multiplicity) {
        default_cpp_if_needed(previous_multiplicity, m);
        default_java_if_needed(previous_multiplicity, m);
        default_idl_if_needed(previous_multiplicity, m);
        default_php_if_needed(previous_multiplicity, m);
        default_python_if_needed(previous_multiplicity, m);

        previous_multiplicity = m;
    }
}

void AttributeDialog::menu_type()
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

        MenuFactory::addItem(m, tr("Create class and choose it"), 2);
    }

    if (!visit || (index != -1) || (bn != 0)) {
        QAction *retActon = m.exec(QCursor::pos());
        if(retActon)
        switch (retActon->data().toInt()) {
        case 0:
            nodes.at(index)->select_in_browser();
            break;

        case 2:
            bn = BrowserClass::add_class(FALSE, view);

            if (bn == 0)
                return;

            bn->select_in_browser();

            // no break
        case 1: {
            QString s = bn->full_name(TRUE);

            if ((index = list.indexOf(s)) == -1) {
                // new class, may be created through an other dialog
                index = 0;
                QStringList::Iterator iter = list.begin();
                QStringList::Iterator iter_end = list.end();

                while ((iter != iter_end) && (*iter < s)) {
                    ++iter;
                    index += 1;
                }

                nodes.insert((unsigned) index, bn);
                list.insert(iter, s);
                edtype->insertItem(index + offset, s);
            }
        }

        edtype->setCurrentIndex(index + offset);
        break;

        default:
            break;
        }
    }
}

void AttributeDialog::derived_changed(bool on)
{
    derivedunion_cb->setEnabled(on);
}

void AttributeDialog::accept()
{
    if (
            !check_edits(edits) ||
            !kvtable->check_unique())
        return;

    BrowserNode * bn = att->browser_node;
    QString oldname = att->name();
    QString s;

    s = edname->text().trimmed();

    if ((s != oldname) &&
        ((BrowserNode *) bn->parent())->wrong_child_name(s, UmlAttribute,
                bn->allow_spaces(),
                bn->allow_empty()))
        msg_critical(tr("Error"), s + tr("\n\nillegal name or already used"));
    else {
        default_defs_if_needed();

        bn->set_name(s);

        bool newst = FALSE;

        if (!java_in_enum_pattern) {
            AType t;

            s = edtype->currentText().trimmed();

            if (!s.isEmpty()) {
                int index = list.indexOf(s);

                if (index >= 0)
                    t.type = (BrowserClass *) nodes.at(index);
                else
                    t.explicit_type = s;
            }

            att->set_type(t);
            att->uml_visibility = uml_visibility.value();
            att->isa_class_attribute = classattribute_cb->isChecked();
            att->isa_volatile_attribute = volatile_cb->isChecked();
            att->isa_const_attribute = constattribute_cb->isChecked();
            att->is_derived = derived_cb->isChecked();
            att->is_derivedunion = derivedunion_cb->isChecked();
            att->is_ordered = ordered_cb->isChecked();
            att->is_unique = unique_cb->isChecked();

            att->multiplicity = multiplicity->currentText().trimmed();

            WrapperStr tempStereo = fromUnicode(edstereotype->currentText().trimmed());
            newst = att->set_stereotype(/*tempStereo.operator const char *()*/edstereotype->currentText().trimmed().toLatin1().constData());
        }

        att->init_value = edinit->text();

        if (cpp_ignored)
            att->cpp_decl = QString();
        else {
            att->cpp_decl = edcppdecl->text();
            if (!cpp_in_enum)
                att->cpp_visibility = cpp_visibility.value();
        }

        att->cpp_mutable = (cpp_in_enum || cpp_ignored)
                           ? FALSE
                           : mutable_cb->isChecked();

        att->java_transient = (java_in_enum || java_ignored || java_in_enum_pattern)
                              ? FALSE
                              : transient_cb->isChecked();
        att->java_decl = (java_ignored) ? QString() : edjavadecl->text();
        att->java_annotation = javaannotation;

        att->php_decl = (php_ignored) ? QString() : edphpdecl->text();

        att->python_decl = (python_ignored) ? QString() : edpythondecl->text();

        att->idl_decl = (idl_in_typedef) ? QString() : edidldecl->text();

        if (idl_in_union) {
            int index;
            s = edcase->currentText().trimmed();

            if (!s.isEmpty() && ((index = enum_names.indexOf(s)) != -1))
                att->set_idlcase((BrowserAttribute *) enums.at(index), "");
            else
                att->set_idlcase(0, s.toLatin1().constData());
        }

        bn->set_comment(comment->text());
        UmlWindow::update_comment_if_needed(bn);

        att->constraint = constraint->trimmedText();

        kvtable->updateNodeFromThis(bn);

        ProfiledStereotypes::modified(bn, newst);

        if (new_in_st) {
            ProfiledStereotypes::added((BrowserAttribute *) bn);
            new_in_st = FALSE;
        }
        else if (!strcmp(((BrowserNode *) bn->parent())->get_data()->get_stereotype(), "stereotype"))
            ProfiledStereotypes::changed((BrowserAttribute *) bn, oldname);

        bn->modified();
        bn->package_modified();
        att->modified();

        QDialog::accept();
    }
}

void AttributeDialog::update_all_tabs(int index)
{
    QWidget * w = m_tabWidget->widget(index);
    if (!visit)
        default_defs_if_needed();

    edname->setText(edname->text().trimmed());

    if (w == umltab) {
        if (!visit)
            edname->setFocus();
    }
    else if (w == cppTab) {
        cpp_update();

        if (!visit)
            edcppdecl->setFocus();
    }
    else if (w == javatab) {
        java_update();

        if (!visit)
            edjavadecl->setFocus();
    }
    else if (w == phptab) {
        php_update();

        if (!visit)
            edphpdecl->setFocus();
    }
    else if (w == pythontab) {
        python_update();

        if (!visit)
            edpythondecl->setFocus();
    }
    else if (w == idltab) {
        idl_update();

        if (!visit)
            edidldecl->setFocus();
    }
}

void AttributeDialog::default_description()
{
    comment->setText(GenerationSettings::default_attribute_description());
}

void AttributeDialog::edit_description()
{
    edit(comment->text(), edname->text().trimmed() + "_description",
         att, TxtEdit, this, (post_edit) post_edit_description, edits);
}

void AttributeDialog::post_edit_description(AttributeDialog * d, QString s)
{
    d->comment->setText(s);
}

void AttributeDialog::edit_constraint()
{
    edit(constraint->text(), edname->text().trimmed() + "_constraint",
         att, TxtEdit, this, (post_edit) post_edit_constraint, edits);
}

void AttributeDialog::post_edit_constraint(AttributeDialog * d, QString s)
{
    d->constraint->setText(s);
}

void AttributeDialog::edit_init()
{
    edit(edinit->text(), edname->text().trimmed() + "_initialization",
         att, TxtEdit, this, (post_edit) post_edit_init, edits);
}

void AttributeDialog::post_edit_init(AttributeDialog * d, QString s)
{
    d->edinit->setText(s);
}

void AttributeDialog::cpp_default()
{
    edcppdecl->setText((cpp_in_enum)
                       ? GenerationSettings::cpp_default_enum_item_decl()
                       : GenerationSettings::cpp_default_attr_decl(multiplicity->currentText().trimmed()));
    cpp_update();
}

void AttributeDialog::default_cpp_if_needed(QString prev_mult, QString new_mult)
{
    if (!cpp_in_enum && !edcppdecl->text().isEmpty()) {
        QString n = GenerationSettings::cpp_default_attr_decl(new_mult);

        if (n != GenerationSettings::cpp_default_attr_decl(prev_mult))
            edcppdecl->setText(n);
    }
}

void AttributeDialog::cpp_unmapped()
{
    edcppdecl->setText(QString());
    showcppdecl->setText(QString());
}

void AttributeDialog::cpp_update()
{
    if (!cpp_in_enum)
        cpp_visibility.update_default(uml_visibility);

    // do NOT write
    //	const char * p = edcppdecl->text();
    // because the QString is immediatly destroyed !
    QString def = edcppdecl->text();
    QByteArray defArray = def.toLatin1();
    const char * p = defArray.constData();
    const char * pp = 0;
    QString indent = "";
    QString s;

    while ((*p == ' ') || (*p == '\t'))
        indent += *p++;

    if (*p != '#')
        s = indent;

    for (;;) {
        if (*p == 0) {
            if (pp == 0)
                break;

            // comment management done
            p = pp;
            pp = 0;

            if (*p == 0)
                break;

            if (*p != '#')
                s += indent;
        }

        if (!strncmp(p, "${comment}", 10))
            manage_comment(comment->text(), p, pp,
                           GenerationSettings::cpp_javadoc_style());
        else if (!strncmp(p, "${description}", 14))
            manage_description(comment->text(), p, pp);
        else if (!strncmp(p, "${name}", 7)) {
            p += 7;
            s += edname->text();
        }
        else if ((cpp_in_enum && !strncmp(p, "${value}", 8)) ||
                 !strncmp(p, "${h_value}", 10)) {
            QString i = edinit->text().trimmed();

            if (!i.isEmpty() && (cpp_in_enum || classattribute_cb->isChecked())) {
                if (need_equal(p, i, TRUE))
                    s += " = ";

                s += edinit->text();
            }

            p += (p[2] == 'h') ? 10 : 8;
        }
        else if (!strncmp(p, "${value}", 8)) {
            QString i = edinit->text().trimmed();

            if (!i.isEmpty()) {
                if (need_equal(p, i, TRUE))
                    s += " = ";

                s += edinit->text();
                p += (p[2] == 'h') ? 10 : 8;
            }
            else
                p += 8;
        }
        //p += 8;
        else if (*p == '\n') {
            s += *p++;

            if (*p && (*p != '#'))
                s += indent;
        }
        else if (cpp_in_enum)
            s += *p++;
        else if (!strncmp(p, "${static}", 9)) {
            p += 9;

            if (classattribute_cb->isChecked())
                s += "static ";
        }
        else if (!strncmp(p, "${const}", 8)) {
            p += 8;

            if (constattribute_cb->isChecked())
                s += "const ";
        }
        else if (!strncmp(p, "${mutable}", 10)) {
            p += 10;

            if (mutable_cb->isChecked())
                s += "mutable ";
        }
        else if (!strncmp(p, "${volatile}", 11)) {
            p += 11;

            if (volatile_cb->isChecked())
                s += "volatile ";
        }
        else if (!strncmp(p, "${type}", 7)) {
            p += 7;
            s += get_cpp_name(the_type(edtype->currentText().trimmed(),
                                       list, nodes));
        }
        else if (!strncmp(p, "${multiplicity}", 15)) {
            p += 15;

            QString m = multiplicity->currentText().trimmed();

            s += (m.startsWith('[')) ? m : QString("[") + m + "]";
        }
        else if (!strncmp(p, "${stereotype}", 13)) {
            p += 13;
            s += GenerationSettings::cpp_relationattribute_stereotype(fromUnicode(edstereotype->currentText().trimmed()));
        }
        else if (*p == '@')
            manage_alias(att->browser_node, p, s, kvtable);
        else
            s += *p++;
    }

    showcppdecl->setText(s);
}

QString AttributeDialog::cpp_decl(const BrowserAttribute * at, bool init,
                                  ShowContextMode mode)
{
    QString s;
    AttributeData * d = (AttributeData *) at->get_data();
    WrapperStr decl = d->cpp_decl;
    remove_comments(decl);
    remove_preprocessor(decl);

    const char * p = decl;

    while ((*p == ' ') || (*p == '\t'))
        p += 1;

    while (*p) {
        if (!strncmp(p, "${comment}", 10))
            p += 10;
        else if (!strncmp(p, "${description}", 14))
            p += 14;
        else if (!strncmp(p, "${name}", 7)) {
            p += 7;
            s += at->get_name();
        }
        else if (!strncmp(p, "${value}", 8) || !strncmp(p, "${h_value}", 10)) {
            if (init) {
                const char * v = d->get_init_value().toLatin1().constData();

                if (*v) {
                    if (need_equal(p, v, TRUE))
                        s += " = ";

                    s += v;
                }
            }

            break;
        }
        else if (!strncmp(p, "${static}", 9))
            p += 9;
        else if (!strncmp(p, "${const}", 8))
            p += 8;
        else if (!strncmp(p, "${mutable}", 10))
            p += 10;
        else if (!strncmp(p, "${volatile}", 11))
            p += 11;
        else if (!strncmp(p, "${type}", 7)) {
            p += 7;
            s += get_cpp_name(d->type, mode);
        }
        else if (!strncmp(p, "${multiplicity}", 15)) {
            p += 15;

            QString m = d->get_multiplicity();

            if (!m.isEmpty())
                s += (m.startsWith('[')) ? m : QString("[") + m + "]";
        }
        else if (!strncmp(p, "${stereotype}", 13)) {
            p += 13;
            s += GenerationSettings::cpp_relationattribute_stereotype(d->stereotype);
        }
        else if (*p == '\n') {
            s += " ";

            do
                p += 1;

            while ((*p == ' ') || (*p == '\t'));
        }
        else if (*p == ';')
            break;
        else if (*p == '@')
            manage_alias(at, p, s, static_cast<KeyValuesTable*>(0));
        else
            s += *p++;
    }
    return s;
}

void AttributeDialog::java_default_item()
{
    edjavadecl->setText(GenerationSettings::java_default_enum_item_decl());

    if (edstereotype->currentText().trimmed() == "attribute")
        edstereotype->setCurrentIndex(empty_st_rank);

    java_update();
}

void AttributeDialog::java_default()
{
    if (java_in_enum_pattern)
        edjavadecl->setText(GenerationSettings::java_default_enum_pattern_item_decl());
    else {
        if (java_in_enum)
            edstereotype->setCurrentIndex(attribute_st_rank);

        edjavadecl->setText(GenerationSettings::java_default_attr_decl(multiplicity->currentText().trimmed()));
    }

    java_update();
}

void AttributeDialog::default_java_if_needed(QString prev_mult, QString new_mult)
{
    if (!java_in_enum_pattern && !edjavadecl->text().isEmpty()) {
        QString n = GenerationSettings::java_default_attr_decl(new_mult);

        if (n != GenerationSettings::java_default_attr_decl(prev_mult))
            edjavadecl->setText(n);
    }
}

void AttributeDialog::java_unmapped()
{
    edjavadecl->setText(QString());
    showjavadecl->setText(QString());
}

void AttributeDialog::java_update()
{
    // do NOT write
    //	const char * p = edjavadecl->text();
    // because the QString is immediatly destroyed !
    QString def = edjavadecl->text();
    QByteArray defArray = def.toLatin1();
    const char * p = defArray.constData();
    const char * pp = 0;
    QString indent = "";
    QString s;
    while ((*p == ' ') || (*p == '\t'))
        indent += *p++;

    s = indent;

    for (;;) {
        if (*p == 0) {
            if (pp == 0)
                break;

            // comment management done
            p = pp;
            pp = 0;

            if (*p == 0)
                break;

            s += indent;
        }

        if (!strncmp(p, "${comment}", 10))
            manage_comment(comment->text(), p, pp,
                           GenerationSettings::java_javadoc_style());
        else if (!strncmp(p, "${description}", 14))
            manage_description(comment->text(), p, pp);
        else if (!strncmp(p, "${name}", 7)) {
            p += 7;
            s += edname->text();
        }
        else if (!strncmp(p, "${value}", 8)) {
            QString i = edinit->text().trimmed();

            if (!i.isEmpty()) {
                if (java_in_enum &&
                    (edstereotype->currentText().trimmed() != "attribute"))
                    s += '(' + edinit->text() + ')';
                else {
                    if (need_equal(p, i, FALSE))
                        s += " = ";

                    s += edinit->text();
                }
            }
            else if (java_in_enum_pattern)
                s += (need_equal(p, "", FALSE)) ? " = ..." : "...";

            p += 8;
        }
        else if (*p == '\n') {
            s += *p++;

            if (*p)
                s += indent;
        }
        else if (!strncmp(p, "${@}", 4)) {
            p += 4;

            if (pp != 0)
                s += "${@}";
            else if (!javaannotation.isEmpty()) {
                pp = p;
                p = javaannotation.toLatin1().constData();
            }
        }
        else if (*p == '@')
            manage_alias(att->browser_node, p, s, kvtable);
        else if (java_in_enum_pattern) {
            if (!strncmp(p, "${class}", 8)) {
                p += 8;
                s += ((BrowserNode *) att->browser_node->parent())->get_name();
            }
            else
                s += *p++;
        }
        else if (!strncmp(p, "${visibility}", 13)) {
            p += 13;

            if (uml_visibility.value() != UmlPackageVisibility)
                s += uml_visibility.state() + " ";
        }
        else if (!strncmp(p, "${static}", 9)) {
            p += 9;

            if (classattribute_cb->isChecked())
                s += "static ";
        }
        else if (!strncmp(p, "${transient}", 12)) {
            p += 12;

            if (!java_in_enum && !java_in_enum_pattern && !java_ignored && transient_cb->isChecked())
                s += "transient ";
        }
        else if (!strncmp(p, "${volatile}", 11)) {
            p += 11;

            if (volatile_cb->isChecked())
                s += "volatile ";
        }
        else if (!strncmp(p, "${final}", 8)) {
            p += 8;

            if (constattribute_cb->isChecked())
                s += "final ";
        }
        else if (!strncmp(p, "${type}", 7)) {
            p += 7;
            s += get_java_name(the_type(edtype->currentText().trimmed(),
                                        list, nodes));
        }
        else if (!strncmp(p, "${multiplicity}", 15)) {
            p += 15;
            s += java_multiplicity(multiplicity->currentText().trimmed());
        }
        else if (!strncmp(p, "${stereotype}", 13)) {
            p += 13;
            s += GenerationSettings::java_relationattribute_stereotype(fromUnicode(edstereotype->currentText().trimmed()));
        }
        else
            s += *p++;
    }

    editjavaannotation->setEnabled(def.indexOf("${@}") != -1);
    showjavadecl->setText(s);
}

QString AttributeDialog::java_decl(const BrowserAttribute * at, bool init,
                                   ShowContextMode mode)
{
    QString s;
    AttributeData * d = (AttributeData *) at->get_data();
    WrapperStr decl = d->java_decl;
    remove_comments(decl);

    const char * p = decl;

    while ((*p == ' ') || (*p == '\t'))
        p += 1;

    while (*p) {
        if (!strncmp(p, "${comment}", 10))
            p += 10;
        else if (!strncmp(p, "${description}", 14))
            p += 14;
        else if (!strncmp(p, "${name}", 7)) {
            p += 7;
            s += at->get_name();
        }
        else if (!strncmp(p, "${value}", 8)) {
            if (init) {
                const char * v = d->get_init_value().toLatin1().constData();

                if (*v) {
                    if (need_equal(p, v, FALSE))
                        s += " = ";

                    s += v;
                }
            }

            break;
        }
        else if (!strncmp(p, "${class}", 8)) {
            p += 8;
            s += ((BrowserNode *) at->parent())->get_name();
        }
        else if (!strncmp(p, "${visibility}", 13))
            p += 13;
        else if (!strncmp(p, "${static}", 9))
            p += 9;
        else if (!strncmp(p, "${transient}", 12))
            p += 12;
        else if (!strncmp(p, "${volatile}", 11))
            p += 11;
        else if (!strncmp(p, "${final}", 8))
            p += 8;
        else if (!strncmp(p, "${type}", 7)) {
            p += 7;
            s += get_java_name(d->type, mode);
        }
        else if (!strncmp(p, "${multiplicity}", 15)) {
            p += 15;

            QString m = d->get_multiplicity();

            if (!m.startsWith('['))
                s += "[]";
            else {
                for (int index = 0; index != m.length(); index += 1) {
                    switch (m.at(index).toLatin1()) {
                    case '[':
                        s += '[';
                        break;

                    case ']':
                        s += ']';

                    default:
                        break;
                    }
                }
            }
        }
        else if (!strncmp(p, "${stereotype}", 13)) {
            p += 13;
            s += GenerationSettings::java_relationattribute_stereotype(d->get_multiplicity());
        }
        else if (!strncmp(p, "${@}", 4))
            p += 4;
        else if (*p == '\n') {
            s += " ";

            do
                p += 1;

            while ((*p == ' ') || (*p == '\t'));
        }
        else if (*p == ';')
            break;
        else if (*p == '@')
            manage_alias(at, p, s, static_cast<KeyValuesTable*>(0));
        else
            s += *p++;
    }
    return s;
}

void AttributeDialog::java_edit_annotation()
{
    AnnotationDialog dialog(this, javaannotation, !hasOkButton());

    if (dialog.exec() == QDialog::Accepted)
        java_update();
}

void AttributeDialog::php_default()
{
    if (php_in_enum)
        edphpdecl->setText(GenerationSettings::php_default_enum_item_decl());
    else
        edphpdecl->setText(GenerationSettings::php_default_attr_decl());

    php_update();
}

void AttributeDialog::default_php_if_needed(QString, QString)
{
    // do nothing : no link with multiplicity
}

void AttributeDialog::php_unmapped()
{
    edphpdecl->setText(QString());
    showphpdecl->setText(QString());
}

void AttributeDialog::php_update()
{
    // do NOT write
    //	const char * p = edphpdecl->text();
    // because the QString is immediatly destroyed !
    QString def = edphpdecl->text();
    QByteArray defArray = def.toLatin1();
    const char * p = defArray.constData();
    const char * pp = 0;
    QString indent = "";
    QString s;
    while ((*p == ' ') || (*p == '\t'))
        indent += *p++;

    s = indent;

    for (;;) {
        if (*p == 0) {
            if (pp == 0)
                break;

            // comment management done
            p = pp;
            pp = 0;

            if (*p == 0)
                break;

            s += indent;
        }

        if (!strncmp(p, "${comment}", 10))
            manage_comment(comment->text(), p, pp,
                           GenerationSettings::php_javadoc_style());
        else if (!strncmp(p, "${description}", 14))
            manage_description(comment->text(), p, pp);
        else if (!strncmp(p, "${name}", 7)) {
            p += 7;

            if (!php_in_enum && !constattribute_cb->isChecked())
                s += "$";

            s += edname->text();
        }
        else if (!strncmp(p, "${value}", 8)) {
            QString i = edinit->text().trimmed();

            if (!i.isEmpty()) {
                if (need_equal(p, i, FALSE))
                    s += " = ";

                s += edinit->text();
            }
            else if (php_in_enum)
                s += (need_equal(p, "", FALSE)) ? " = ..." : "...";

            p += 8;
        }
        else if (!strncmp(p, "${const}", 8)) {
            p += 8;

            if (constattribute_cb->isChecked())
                s += "const ";
        }
        else if (!strncmp(p, "${var}", 6)) {
            p += 6;

            if (!php_in_enum &&
                !constattribute_cb->isChecked() &&
                !classattribute_cb->isChecked() &&
                (uml_visibility.value() == UmlPackageVisibility))
                s += "var ";
        }
        else if (*p == '\n') {
            s += *p++;

            if (*p)
                s += indent;
        }
        else if (*p == '@')
            manage_alias(att->browser_node, p, s, kvtable);
        else if (!strncmp(p, "${visibility}", 13)) {
            p += 13;

            if (uml_visibility.value() != UmlPackageVisibility)
                s += uml_visibility.state() + " ";
        }
        else if (!strncmp(p, "${static}", 9)) {
            p += 9;

            if (classattribute_cb->isChecked())
                s += "static ";
        }
        else if (!strncmp(p, "${type}", 7)) {
            // for comment
            p += 7;
            s += get_php_name(the_type(edtype->currentText().trimmed(),
                                       list, nodes));
        }
        else
            s += *p++;
    }
    showphpdecl->setText(s);
}

QString AttributeDialog::php_decl(const BrowserAttribute * at, bool init,
                                  ShowContextMode mode)
{
    QString s;
    AttributeData * d = (AttributeData *) at->get_data();
    WrapperStr decl = d->php_decl;
    remove_comments(decl);

    const char * p = decl;

    while ((*p == ' ') || (*p == '\t'))
        p += 1;

    while (*p) {
        if (!strncmp(p, "${comment}", 10))
            p += 10;
        else if (!strncmp(p, "${description}", 14))
            p += 14;
        else if (!strncmp(p, "${name}", 7)) {
            p += 7;

            ClassData * cld = (ClassData *)
                              ((BrowserNode *) at->parent())->get_data();
            QString stereotype = cld->get_stereotype();
            bool in_enum = (stereotype == "enum");
            QString lang_st = GenerationSettings::php_class_stereotype(stereotype);

            in_enum |= (lang_st == "enum");

            if (!in_enum &&
                !((AttributeData *) at->get_data())->get_isa_const_attribute())
                s += "$";

            s += at->get_name();
        }
        else if (!strncmp(p, "${value}", 8)) {
            if (init) {
                const char * v = d->get_init_value().toLatin1().constData();

                if (*v) {
                    if (need_equal(p, v, FALSE))
                        s += " = ";

                    s += v;
                }
            }

            break;
        }
        else if (!strncmp(p, "${const}", 8))
            p += 8;
        else if (!strncmp(p, "${visibility}", 13))
            p += 13;
        else if (!strncmp(p, "${static}", 9))
            p += 9;
        else if (!strncmp(p, "${var}", 6))
            p += 6;
        else if (*p == '\n') {
            s += " ";

            do
                p += 1;

            while ((*p == ' ') || (*p == '\t'));
        }
        else if (*p == ';')
            break;
        else if (*p == '@')
            manage_alias(at, p, s, static_cast<KeyValuesTable*>(0));
        else if (!strncmp(p, "${type}", 7)) {
            // for comment
            p += 7;
            s += get_php_name(d->type, mode);
        }
        else
            s += *p++;
    }
    return s;
}

void AttributeDialog::python_default()
{
    if (python_in_enum)
        edpythondecl->setText(GenerationSettings::python_default_enum_item_decl());
    else if (!java_in_enum_pattern)
        edpythondecl->setText(GenerationSettings::python_default_attr_decl(""));
    else
        edpythondecl->setText(GenerationSettings::python_default_attr_decl(multiplicity->currentText().trimmed()));

    python_update();
}

void AttributeDialog::default_python_if_needed(QString prev_mult, QString new_mult)
{
    if (!python_in_enum && !java_in_enum_pattern && !edpythondecl->text().isEmpty()) {
        QString n = GenerationSettings::python_default_attr_decl(new_mult);

        if (n != GenerationSettings::python_default_attr_decl(prev_mult))
            edpythondecl->setText(n);
    }
}

void AttributeDialog::python_unmapped()
{
    edpythondecl->setText(QString());
    showpythondecl->setText(QString());
}

void AttributeDialog::python_update()
{
    // do NOT write
    //	const char * p = edpythondecl->text();
    // because the QString is immediatly destroyed !
    QString def = edpythondecl->text();
    QByteArray defArray = def.toLatin1();
    const char * p = defArray.constData();
    const char * pp = 0;
    QString s;
    for (;;) {
        if (*p == 0) {
            if (pp == 0)
                break;

            // comment management done
            p = pp;
            pp = 0;

            if (*p == 0)
                break;
        }

        if (!strncmp(p, "${comment}", 10))
            manage_python_comment(comment->text(), p, pp);
        else if (!strncmp(p, "${description}", 14))
            manage_python_description(comment->text(), p, pp);
        else if (!strncmp(p, "${name}", 7)) {
            p += 7;
            s += edname->text();
        }
        else if (!strncmp(p, "${value}", 8)) {
            QString i = edinit->text().trimmed();

            if (!i.isEmpty()) {
                if (need_equal(p, i, FALSE))
                    s += " = ";

                s += edinit->text();
            }
            else if (python_in_enum)
                s += (need_equal(p, "", FALSE)) ? " = ..." : "...";
            else if (need_equal(p, "None", FALSE))
                s += " = None";
            else
                s += "None";

            p += 8;
        }
        else if (!strncmp(p, "${self}", 7)) {
            p += 7;

            if (java_in_enum_pattern || !classattribute_cb->isChecked())
                s += python_self;
        }
        else if (!strncmp(p, "${stereotype}", 13)) {
            p += 13;

            if (! java_in_enum_pattern)
                s += GenerationSettings::python_relationattribute_stereotype(fromUnicode(edstereotype->currentText().trimmed()));
        }
        else if (!strncmp(p, "${type}", 7)) {
            p += 7;
            s += get_python_name(the_type(edtype->currentText().trimmed(),
                                          list, nodes));
        }
        else if (*p == '@')
            manage_alias(att->browser_node, p, s, kvtable);
        else
            s += *p++;
    }
    showpythondecl->setText(s);
}

// produced out of __init__
QString AttributeDialog::python_decl(const BrowserAttribute * at,
                                     bool init, ShowContextMode)
{
    QString s;
    AttributeData * d = (AttributeData *) at->get_data();
    WrapperStr decl = d->python_decl;

    remove_comments(decl);

    const char * p = decl;
    while (*p) {
        if (!strncmp(p, "${comment}", 10)) {
            p += 10;
        }
        else if (!strncmp(p, "${description}", 14)) {
            p += 14;
        }
        else if (!strncmp(p, "${name}", 7)) {
            p += 7;
            s += at->get_name();
        }
        else if (!strncmp(p, "${value}", 8)) {
            if (init) {
                const char * v = d->get_init_value().toLatin1().constData();

                if (*v) {
                    if (need_equal(p, v, FALSE))
                        s += " = ";

                    s += v;
                }
            }

            break;
        }
        else if (!strncmp(p, "${self}", 7)) {
            p += 7;
        }
        else if (!strncmp(p, "${stereotype}", 13)) {
            p += 13;
        }
        else if (!strncmp(p, "${type}", 7)) {
            p += 7;
        }
        else if (*p == '=') {
            if (!init)
                break;
            else
                s += *p++;
        }
        else if (*p == '\n') {
            s += " ";

            do
                p += 1;

            while ((*p == ' ') || (*p == '\t'));
        }
        else if (*p == '@')
            manage_alias(at, p, s, static_cast<KeyValuesTable*>(0));
        else
            s += *p++;
    }
    return s;
}

void AttributeDialog::idl_default()
{
    if (idl_in_enum)
        edidldecl->setText(GenerationSettings::idl_default_enum_item_decl());
    else if (idl_in_union)
        edidldecl->setText(GenerationSettings::idl_default_union_item_decl(multiplicity->currentText().trimmed()));
    else
        edidldecl->setText((constattribute_cb->isChecked() &&
                            !edinit->text().trimmed().isEmpty())
                           ? GenerationSettings::idl_default_const_decl(multiplicity->currentText().trimmed())
                           : GenerationSettings::idl_default_attr_decl(multiplicity->currentText().trimmed()));

    idl_update();
}

void AttributeDialog::default_idl_if_needed(QString prev_mult, QString new_mult)
{
    if (!idl_in_enum && !idl_in_union && !edidldecl->text().isEmpty()) {
        QString p;
        QString n;

        if (constattribute_cb->isChecked() && !edinit->text().trimmed().isEmpty()) {
            p = GenerationSettings::idl_default_const_decl(prev_mult);
            n = GenerationSettings::idl_default_const_decl(new_mult);
        }
        else {
            p = GenerationSettings::idl_default_attr_decl(prev_mult);
            n = GenerationSettings::idl_default_attr_decl(new_mult);
        }

        if (n != p)
            edidldecl->setText(n);
    }
}

void AttributeDialog::idl_default_state()
{
    edidldecl->setText(GenerationSettings::idl_default_valuetype_attr_decl(multiplicity->currentText().trimmed()));
    idl_update();
}

void AttributeDialog::idl_default_constant()
{
    edidldecl->setText(GenerationSettings::idl_default_const_decl(multiplicity->currentText().trimmed()));
    idl_update();
}

void AttributeDialog::idl_unmapped()
{
    edidldecl->setText(QString());
    showidldecl->setText(QString());
}

void AttributeDialog::idl_update()
{
    // do NOT write
    //	const char * p = edidldecl->text();
    // because the QString is immediatly destroyed !
    QString def = edidldecl->text();
    QByteArray defArray = def.toLatin1();
    const char * p = defArray.constData();
    const char * pp = 0;
    QString indent = "";
    QString s;
    while ((*p == ' ') || (*p == '\t'))
        indent += *p++;

    if (*p != '#')
        s = indent;

    for (;;) {
        if (*p == 0) {
            if (pp == 0)
                break;

            // comment management done
            p = pp;
            pp = 0;

            if (*p == 0)
                break;

            s += indent;
        }

        if (!strncmp(p, "${comment}", 10))
            manage_comment(comment->text(), p, pp, FALSE);
        else if (!strncmp(p, "${description}", 14))
            manage_description(comment->text(), p, pp);
        else if (!strncmp(p, "${name}", 7)) {
            p += 7;
            s += edname->text();
        }
        else if (!strncmp(p, "${value}", 8)) {
            QString i = edinit->text().trimmed();

            if (need_equal(p, i, FALSE))
                s += " = ";

            s += edinit->text();
            p += 8;
        }
        else if (*p == '\n') {
            s += *p++;

            if (*p && (*p != '#'))
                s += indent;
        }
        else if (idl_in_enum)
            s += *p++;
        else if (idl_in_union && !strncmp(p, "${case}", 7)) {
            p += 7;
            s += edcase->currentText().trimmed();
        }
        else if (!strncmp(p, "${attribut}", 11)) {
            // old version
            p += 11;

            if (!idl_in_struct)
                s += "attribute ";
        }
        else if (!strncmp(p, "${attribute}", 12)) {
            p += 12;

            if (!idl_in_struct)
                s += "attribute ";
        }
        else if (!strncmp(p, "${visibility}", 13)) {
            p += 13;

            switch (uml_visibility.value()) {
            case UmlPublic:
            case UmlPackageVisibility:
                s += "public ";

            default:
                s += "private ";
            }
        }
        else if (!strncmp(p, "${readonly}", 11)) {
            p += 11;

            if (constattribute_cb->isChecked())
                s += "readonly ";
        }
        else if (!strncmp(p, "${type}", 7)) {
            p += 7;
            s += get_idl_name(the_type(edtype->currentText().trimmed(),
                                       list, nodes));
        }
        else if (!strncmp(p, "${stereotype}", 13)) {
            p += 13;
            s += GenerationSettings::idl_relationattribute_stereotype(fromUnicode(edstereotype->currentText().trimmed()));
        }
        else if (!strncmp(p, "${multiplicity}", 15)) {
            p += 15;
            s += multiplicity->currentText().trimmed();
        }
        else if (*p == '@')
            manage_alias(att->browser_node, p, s, kvtable);
        else
            s += *p++;
    }
    showidldecl->setText(s);
}

QString AttributeDialog::idl_decl(const BrowserAttribute * at,
                                  ShowContextMode mode)
{
    QString s;
    AttributeData * d = (AttributeData *) at->get_data();
    WrapperStr decl = d->idl_decl;
    QString stereotype = ((BrowserNode *) at->parent())->get_data()->get_stereotype();
    bool in_enum = (stereotype == "enum") ||
                   (GenerationSettings::idl_class_stereotype(stereotype) == "enum");
    remove_comments(decl);

    const char * p = decl;

    while ((*p == ' ') || (*p == '\t'))
        p += 1;

    while (*p) {
        if (!strncmp(p, "${comment}", 10))
            p += 10;
        else if (!strncmp(p, "${description}", 14))
            p += 14;
        else if (!strncmp(p, "${name}", 7)) {
            p += 7;
            s += at->get_name();
        }
        else if (!strncmp(p, "${value}", 8))
            break;
        else if (!strncmp(p, "${case}", 7)) {
            p += 7;
            s += d->get_idlcase();
        }
        else if (!strncmp(p, "${attribut}", 11))
            // old version
            p += 11;
        else if (!strncmp(p, "${attribute}", 12))
            p += 12;
        else if (!strncmp(p, "${visibility}", 13))
            p += 13;
        else if (!strncmp(p, "${readonly}", 11))
            p += 11;
        else if (!strncmp(p, "${type}", 7)) {
            p += 7;
            s += get_idl_name(d->type, mode);
        }
        else if (!strncmp(p, "${stereotype}", 13)) {
            p += 13;
            s += GenerationSettings::idl_relationattribute_stereotype(d->get_stereotype());
        }
        else if (!strncmp(p, "${multiplicity}", 15)) {
            p += 15;
            s += d->get_multiplicity();
        }
        else if (*p == '\n') {
            s += " ";

            do
                p += 1;

            while ((*p == ' ') || (*p == '\t'));
        }
        else if ((*p == ';') || (in_enum && (*p == ',')))
            break;
        else if (*p == '@')
            manage_alias(at, p, s, static_cast<KeyValuesTable*>(0));
        else
            s += *p++;
    }
    return s;
}
