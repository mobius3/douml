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





#include <qcursor.h>

#include <gridbox.h>
#include <vvbox.h>
#include "hhbox.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <qlabel.h>
//#include <q3popupmenu.h>
#include <qpushbutton.h>
#include <qfiledialog.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qradiobutton.h>
#include <qbuttongroup.h>
#include <qsplitter.h>
#include <qspinbox.h>
#include <QApplication>
//Added by qt3to4:


#include "GenerationSettingsDialog.h"
#include "BrowserView.h"
#include "MLinesItem.h"
#include "DialogUtil.h"
#include "UmlPixmap.h"
#include "UmlDesktop.h"
#include "strutil.h"
#include "translate.h"
#include "Libs/L_UniversalModels/include/ItemController.h"
#include "Libs/L_UniversalModels/include/TableDataInterface.h"
#include "Libs/L_UniversalModels/include/TableDataListHolder.h"
#include "Libs/L_UniversalModels/include/AdaptingTableModel.h"
#include <QGroupBox>
#include <QHeaderView>
#include "bbuttongroup.h"
QSize GenerationSettingsDialog::previous_size;

GenerationSettingsDialog::GenerationSettingsDialog()
    : TabDialog(0, "Generation Settings dialog", TRUE)
{
    setWindowTitle(TR("Generation settings dialog"));
    setOkButton(TR("OK"));
    setCancelButton(TR("Cancel"));
    init_types();
    init_stereotypes();
    init_cpp1();
    init_cpp2();
    init_cpp3();
    init_cpp4();
    init_cpp5();
    init_java1();
    init_java2();
    init_java3();
    init_java4();
    init_php1();
    init_php2();
    init_python1();
    init_python2();
    init_python3();
    init_idl1();
    init_idl2();
    init_idl3();
    init_idl4();
    init_idl5();
    init_descriptions();
    init_dirs();

}

void GenerationSettingsDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::setsize_center(this, previous_size, 29.0 / 30, 19.0 / 29);
}

GenerationSettingsDialog::~GenerationSettingsDialog()
{
    previous_size = size();
}

void GenerationSettingsDialog::init_types()
{
    //QWidget * grid = new GridBox(1, this);

    GridBox *grid = new GridBox(1, this);

    grid->setMargin(3);
    grid->setSpacing(3);

    grid->addWidget(new QLabel(TR("Types correspondence, and C++ operation argument default passing for them :"), grid));
    grid->addWidget(builtinTable = new BuiltinTable(grid));
    grid->addWidget(builtinTable);
    builtinTable->Init();
    this->resize(builtinTable->GetOptimalSize());
    addTab(grid, QObject::tr("Types"));
}

void GenerationSettingsDialog::init_stereotypes()
{

    //QWidget * grid = new GridBox(2, this);
    GridBox *gridW = new GridBox(2, this);


    gridW->setMargin(3);
    gridW->setSpacing(3);

    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    gridW->addWidget(new QLabel(TR("Attributes and \nRelations\nstereotypes \ncorrespondence : "), gridW));
    relation_stereotypes_table =
            new StereotypesTable(gridW, GenerationSettings::nrelattrstereotypes,
                                 GenerationSettings::relattr_stereotypes, FALSE);
    gridW->addWidget(relation_stereotypes_table);
    //new QLabel(grid));
    //new QLabel(grid));

    gridW->addWidget(new QLabel(TR("Classes's \nstereotypes \ncorrespondence : "), gridW));
    class_stereotypes_table =
            new StereotypesTable(gridW, GenerationSettings::nclassstereotypes,
                                 GenerationSettings::class_stereotypes, TRUE);
    gridW->addWidget(class_stereotypes_table);
    addTab(gridW, QObject::tr("Stereotypes"));
}

static void init_indent(QComboBox * cb, const char * v)
{
    cb->addItem(QObject::TR("empty"));
    cb->addItem(QObject::TR("1 space"));

    QString f = "%1 spaces";
    QString s = "2";

    for (int c = 2; c != 9; c += 1) {
        s.setNum(c);
        cb->addItem(f.arg(s));
    }

    cb->addItem(QObject::TR("1 tab"));

    if (*v == '\t')
        cb->setCurrentIndex(9);
    else {
        int n = strlen(v);

        cb->setCurrentIndex((n > 8) ? 8 : n);
    }
}

void GenerationSettingsDialog::init_cpp1()
{

    VVBox * vtab = new VVBox(this);
    GridBox * grid;
    vtab->addWidget(grid = new GridBox(2, vtab));

    grid->setMargin(3);
    grid->setSpacing(3);

    grid->addWidget(new QLabel(TR("Header file\ndefault content :"), grid));
    grid->addWidget(edcpp_h_content = new MultiLineEdit(grid));
    edcpp_h_content->setText(GenerationSettings::cpp_h_content);
    QFont font = edcpp_h_content->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);
    edcpp_h_content->setFont(font);

    grid->addWidget(new QLabel(TR("Source file\ndefault content :"), grid));
    grid->addWidget(edcpp_src_content = new MultiLineEdit(grid));
    edcpp_src_content->setText(GenerationSettings::cpp_src_content);
    edcpp_src_content->setFont(font);

    vtab->addWidget(new QLabel(vtab));

    HHBox * htab;
    vtab->addWidget(htab = new HHBox(vtab));

    htab->setMargin(3);
    htab->addWidget(new QLabel(TR("generated/reversed \nheader file extension : "), htab));
    htab->addWidget(edcpp_h_extension = new QComboBox(/*TRUE,*/ htab));
    edcpp_h_extension->setEditable(true);
    //htab->addWidget((edcpp_h_extension, 100);
    edcpp_h_extension->addItem(GenerationSettings::cpp_h_extension);
    edcpp_h_extension->setCurrentIndex(0);
    edcpp_h_extension->addItem("h");
    edcpp_h_extension->addItem("hh");

    htab->addWidget(new QLabel(TR("    generated/reversed \n    source file extension : "), htab));
    edcpp_src_extension = new QComboBox(htab);
    edcpp_src_extension->setEditable(true);
    htab->addWidget(edcpp_src_extension);
    edcpp_src_extension->addItem(GenerationSettings::cpp_src_extension);
    edcpp_src_extension->setCurrentIndex(0);
    edcpp_src_extension->addItem("cpp");
    edcpp_src_extension->addItem("cc");

    htab->addWidget(new QLabel("    #include : ", htab));
    htab->addWidget(cpp_include_with_path_cb = new QComboBox(htab));
    cpp_include_with_path_cb->addItem(TR("without path"));
    cpp_include_with_path_cb->addItem(TR("with absolute path"));
    cpp_include_with_path_cb->addItem(TR("with relative path"));
    cpp_include_with_path_cb->addItem(TR("with root relative path"));

    if (!GenerationSettings::cpp_include_with_path)
        cpp_include_with_path_cb->setCurrentIndex(0);
    else if (GenerationSettings::cpp_relative_path)
        cpp_include_with_path_cb->setCurrentIndex(2);
    else if (GenerationSettings::cpp_root_relative_path)
        cpp_include_with_path_cb->setCurrentIndex(3);
    else
        cpp_include_with_path_cb->setCurrentIndex(1);

    vtab->addWidget(htab =new HHBox(vtab));
    vtab->addWidget(htab);
    htab->setMargin(3);

    htab->addWidget(new QLabel(TR("force namespace \nprefix generation : "), htab));
    htab->addWidget(cpp_force_namespace_gen_cb = new QCheckBox(htab));
    cpp_force_namespace_gen_cb->setChecked(GenerationSettings::cpp_force_namespace_gen);

    htab->addWidget(new QLabel(TR("            inline operation force \n            includes in header : "), htab));
    htab->addWidget(cpp_inline_force_incl_in_h_cb = new QCheckBox(htab));
    cpp_inline_force_incl_in_h_cb->setChecked(GenerationSettings::cpp_inline_force_incl_in_h);

    htab->addWidget(new QLabel(TR("            generate Javadoc \n            style comment : "), htab));
    htab->addWidget(cpp_javadoc_cb = new QCheckBox(htab));
    cpp_javadoc_cb->setChecked(GenerationSettings::cpp_javadoc_comment);

    htab->addWidget(new QLabel(TR("            visibility indent : "), htab));
    htab->addWidget(indentvisi_cb = new QComboBox(htab));
    init_indent(indentvisi_cb, GenerationSettings::cpp_indent_visibility);

    htab->addWidget(new QLabel(htab));

    addTab(vtab, "C++[1]");

    if (!GenerationSettings::cpp_get_default_defs())
        removePage(vtab);
}

void GenerationSettingsDialog::init_cpp2()
{
    GridBox * grid = new GridBox(2, this);

    grid->setMargin(3);
    grid->setSpacing(3);

    grid->addWidget(new QLabel(TR("Class default \ndeclaration :"), grid));
    grid->addWidget(edcpp_class_decl = new MultiLineEdit(grid));
    edcpp_class_decl->setText(GenerationSettings::cpp_class_decl);
    QFont font = edcpp_class_decl->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);
    edcpp_class_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Struct default \ndeclaration :"), grid));
    grid->addWidget(edcpp_struct_decl = new MultiLineEdit(grid));
    edcpp_struct_decl->setText(GenerationSettings::cpp_struct_decl);
    edcpp_struct_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Union default \ndeclaration :"), grid));
    grid->addWidget(edcpp_union_decl = new MultiLineEdit(grid));
    edcpp_union_decl->setText(GenerationSettings::cpp_union_decl);
    edcpp_union_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Enum default \ndeclaration :"), grid));
    grid->addWidget(edcpp_enum_decl = new MultiLineEdit(grid));
    edcpp_enum_decl->setText(GenerationSettings::cpp_enum_decl);
    edcpp_enum_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Typedef default \ndeclaration :"), grid));
    grid->addWidget(edcpp_typedef_decl = new MultiLineEdit(grid));
    edcpp_typedef_decl->setText(GenerationSettings::cpp_typedef_decl);
    edcpp_typedef_decl->setFont(font);

    addTab(grid, "C++[2]");

    if (!GenerationSettings::cpp_get_default_defs())
        removePage(grid);
}

void GenerationSettingsDialog::init_cpp3()
{
    GridBox * grid = new GridBox(2, this);
    GridBox * grid2;
    HHBox * htab;

    grid->setMargin(3);
    grid->setSpacing(3);

    grid->addWidget(new QLabel(TR("Attribute \ndefault \ndeclaration :"), grid));

    grid->addWidget(grid2 = new GridBox(2, grid));
    QLabel *label = new QLabel(TR("Multiplicity"), grid2);
    label->setAlignment(Qt::AlignCenter);
    grid2->addWidget(label);
    grid2->addWidget(new QLabel(grid2));
    grid2->addWidget(new QLabel(TR("unspecified,\nor 1"), grid2));
    grid2->addWidget(edcpp_attr_decl[0] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("* or a..b"), grid2));
    grid2->addWidget(edcpp_attr_decl[1] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("X (means [X])\nor [...]...[...]"), grid2));
    grid2->addWidget(edcpp_attr_decl[2] = new MultiLineEdit(grid2));

    QFont font = edcpp_attr_decl[0]->font();
    int i, j;

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);

    for (i = 0; i != 3; i += 1) {
        edcpp_attr_decl[i]->setText(GenerationSettings::cpp_attr_decl[i]);
        edcpp_attr_decl[i]->setFont(font);
    }

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    grid->addWidget(new QLabel(TR("Association\nand\naggregation\ndefault\ndeclaration :"), grid));
    grid->addWidget(grid2 = new GridBox(2, grid));
    grid2->addWidget(label = new QLabel(TR("Multiplicity"), grid2));
    label->setAlignment(Qt::AlignCenter);
    grid2->addWidget(htab =new HHBox(grid2));
    htab->addWidget( new QLabel(htab));
    htab->addWidget(( label = new QLabel(TR("Association "), htab)));
    label->setAlignment(Qt::AlignCenter);
    htab->addWidget((label = new QLabel(htab)));
    label->setPixmap(*associationButton);
    htab->addWidget((label =  new QLabel(TR("  and aggregation "), htab)));
    label->setAlignment(Qt::AlignCenter);
    htab->addWidget((label = new QLabel(htab)));
    label->setPixmap(*aggregationButton);
    htab->addWidget(new QLabel(htab));
    grid2->addWidget(new QLabel(TR("unspecified,\n1 or 0..1"), grid2));
    grid2->addWidget(edcpp_rel_decl[0][0] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("* or a..b"), grid2));
    grid2->addWidget(edcpp_rel_decl[0][1] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("X (means [X])\nor [...]...[...]"), grid2));
    grid2->addWidget(edcpp_rel_decl[0][2] = new MultiLineEdit(grid2));

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    grid->addWidget(new QLabel(TR("Composition\ndefault\ndeclaration :"), grid));
    grid->addWidget(grid2 = new GridBox(2, grid));
    grid2->addWidget(label = new QLabel(TR("Multiplicity"), grid2));
    label->setAlignment(Qt::AlignCenter);
    grid2->addWidget(htab =new HHBox(grid2));
    htab->addWidget(new QLabel(htab));
    htab->addWidget((label = new QLabel(TR("Composition "), htab)));
    label->setAlignment(Qt::AlignCenter);
    htab->addWidget((label =new QLabel("",htab)));
    label->setPixmap(*aggregationByValueButton);
    htab->addWidget(new QLabel("",htab));
    grid2->addWidget(new QLabel(TR("unspecified\nor 1"), grid2));
    grid2->addWidget(edcpp_rel_decl[1][0] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("* or a..b"), grid2));
    grid2->addWidget(edcpp_rel_decl[1][1] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("X (means [X])\nor [...]...[...]"), grid2));
    grid2->addWidget(edcpp_rel_decl[1][2] = new MultiLineEdit(grid2));

    for (i = 0; i != 2; i += 1) {
        for (j = 0; j != 3; j += 1) {
            edcpp_rel_decl[i][j]->setText(GenerationSettings::cpp_rel_decl[i][j]);
            edcpp_rel_decl[i][j]->setFont(font);
        }
    }

    addTab(grid, "C++[3]");

    if (!GenerationSettings::cpp_get_default_defs())
        removePage(grid);
}

void GenerationSettingsDialog::init_cpp4()
{
    GridBox * grid = new GridBox(2, this);
    VVBox * vtab;
    HHBox * htab;
    BButtonGroup * bg;

    grid->setMargin(3);
    grid->setSpacing(3);

    grid->addWidget(new QLabel(TR("Get operation\ndefault definition : "), grid));

    grid->addWidget(vtab = new VVBox(grid));

    vtab->addWidget(htab =new HHBox(vtab));
    htab->addWidget(cpp_get_visibility.init(htab, GenerationSettings::cpp_get_visibility,
                            FALSE, tr("Visibility").toLatin1().constData()));

    //bg = new QGroupBox(3, Qt::Horizontal, QObject::tr("Modifiers"), htab));
    htab->addWidget(bg = new BButtonGroup(/*3, Qt::Horizontal, */TR("Modifiers"), htab));
    ////bg->setExclusive(FALSE);
    bg->addWidget(cpp_get_inline_cb = new QCheckBox("inline", bg));
    bg->addWidget(cpp_get_value_const_cb = new QCheckBox(TR("const value"), bg));
    bg->addWidget(cpp_get_const_cb = new QCheckBox("const", bg));
    cpp_get_inline_cb->setChecked(GenerationSettings::cpp_get_inline);
    cpp_get_value_const_cb->setChecked(GenerationSettings::cpp_get_value_const);
    cpp_get_const_cb->setChecked(GenerationSettings::cpp_get_const);

    htab->addWidget(new QLabel(TR("  name : "), htab));
    htab->addWidget(edcpp_get_name = new LineEdit(htab));
    edcpp_get_name->setText(GenerationSettings::cpp_get_name);
    QFont font = edcpp_get_name->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);
    edcpp_get_name->setFont(font);

    htab->addWidget(new QLabel("  ", htab));
    htab->addWidget(uml_follow_cpp_get_name = new QCheckBox(TR("also in uml"), htab));

    if (GenerationSettings::uml_get_name == CppView)
        uml_follow_cpp_get_name->setChecked(TRUE);

    connect(uml_follow_cpp_get_name, SIGNAL(toggled(bool)),
            this, SLOT(follow_cpp_get_name()));

    grid->addWidget(new QLabel(TR("Set operation\ndefault definition : "), grid));

    grid->addWidget(vtab = new VVBox(grid));

    vtab->addWidget(htab =new HHBox(vtab));
    htab->addWidget(cpp_set_visibility.init(htab, GenerationSettings::cpp_get_visibility,
                                            FALSE, tr("Visibility").toLatin1().constData()));

    htab->addWidget(bg = new BButtonGroup(/*4, Qt::Horizontal, */TR("Modifiers"), htab));
    ////bg->setExclusive(FALSE);
    bg->addWidget(cpp_set_inline_cb = new QCheckBox("inline", bg));
    bg->addWidget(cpp_set_param_const_cb = new QCheckBox(TR("const param"), bg));
    bg->addWidget(cpp_set_param_ref_cb = new QCheckBox(TR("by ref"), bg));
    cpp_set_inline_cb->setChecked(GenerationSettings::cpp_set_inline);
    cpp_set_param_const_cb->setChecked(GenerationSettings::cpp_set_param_const);
    cpp_set_param_ref_cb->setChecked(GenerationSettings::cpp_set_param_ref);

    htab->addWidget(new QLabel(TR("  name : "), htab));
    htab->addWidget(edcpp_set_name = new LineEdit(htab));
    edcpp_set_name->setText(GenerationSettings::cpp_set_name);
    edcpp_set_name->setFont(font);

    htab->addWidget(new QLabel("  ", htab));
    htab->addWidget(uml_follow_cpp_set_name = new QCheckBox(TR("also in uml"), htab));

    if (GenerationSettings::uml_set_name == CppView)
        uml_follow_cpp_set_name->setChecked(TRUE);

    connect(uml_follow_cpp_set_name, SIGNAL(toggled(bool)),
            this, SLOT(follow_cpp_set_name()));

    //new QLabel(grid));
    //new QLabel(grid));

    grid->addWidget(new QLabel(TR("Enumeration item \ndefault definition :"), grid));
    grid->addWidget(edcpp_enum_item_decl = new MultiLineEdit(grid));
    edcpp_enum_item_decl->setText(GenerationSettings::cpp_enum_item_decl);
    edcpp_enum_item_decl->setFont(font);

    //new QLabel(grid));
    //new QLabel(grid));

    grid->addWidget(new QLabel(TR("Default type forms\nfor the enums :"), grid));
    grid->addWidget(htab =new HHBox(grid));
    htab->setMargin(3);
    htab->addWidget(new QLabel(TR("input\nparameter : "), htab));
    htab->addWidget(cpp_enum_in = new LineEdit(htab));
    cpp_enum_in->setText(GenerationSettings::cpp_enum_in);
    cpp_enum_in->setFont(font);
    htab->addWidget(new QLabel(TR("   output\n   parameter : "), htab));
    htab->addWidget(cpp_enum_out = new LineEdit(htab));
    cpp_enum_out->setText(GenerationSettings::cpp_enum_out);
    cpp_enum_out->setFont(font);
    htab->addWidget(new QLabel(TR("   input output \n   parameter : "), htab));
    htab->addWidget(cpp_enum_inout = new LineEdit(htab));
    cpp_enum_inout->setText(GenerationSettings::cpp_enum_inout);
    cpp_enum_inout->setFont(font);
    htab->addWidget(new QLabel(TR("   operation \n   return : "), htab));
    htab->addWidget(cpp_enum_return = new LineEdit(htab));
    cpp_enum_return->setText(GenerationSettings::cpp_enum_return);
    cpp_enum_return->setFont(font);

    grid->addWidget(new QLabel(TR("Default type forms for\nthe types not given\nin the first tab:"), grid));
    grid->addWidget(htab =new HHBox(grid));
    htab->setMargin(3);
    htab->addWidget(new QLabel(TR("input\nparameter : "), htab));
    htab->addWidget(cpp_in = new LineEdit(htab));
    cpp_in->setText(GenerationSettings::cpp_in);
    cpp_in->setFont(font);
    htab->addWidget(new QLabel(TR("   output\n   parameter : "), htab));
    htab->addWidget(cpp_out = new LineEdit(htab));
    cpp_out->setText(GenerationSettings::cpp_out);
    cpp_out->setFont(font);
    htab->addWidget(new QLabel(TR("   input output \n   parameter : "), htab));
    htab->addWidget(cpp_inout = new LineEdit(htab));
    cpp_inout->setText(GenerationSettings::cpp_inout);
    cpp_inout->setFont(font);
    htab->addWidget(new QLabel(TR("   operation \n   return : "), htab));
    htab->addWidget(cpp_return = new LineEdit(htab));
    cpp_return->setText(GenerationSettings::cpp_return);
    cpp_return->setFont(font);

    //new QLabel(grid));
    //new QLabel(grid));

    grid->addWidget(new QLabel(TR("Operation default \ndeclaration :"), grid));
    grid->addWidget(edcpp_oper_decl = new MultiLineEdit(grid));
    edcpp_oper_decl->setText(GenerationSettings::cpp_oper_decl);
    edcpp_oper_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Operation default \ndefinition :"), grid));
    grid->addWidget(htab =new HHBox(grid));
    htab->addWidget(edcpp_oper_def = new MultiLineEdit(htab));
    edcpp_oper_def->setText(GenerationSettings::cpp_oper_def);
    edcpp_oper_def->setFont(font);
    htab->addWidget(new QLabel("  ", htab));
    htab->addWidget(cpp_force_throw_cb = new QCheckBox("throw()", htab));
    cpp_force_throw_cb->setChecked(GenerationSettings::cpp_force_throw);


    addTab(grid, "C++[4]");

    if (!GenerationSettings::cpp_get_default_defs())
        removePage(grid);
}

void GenerationSettingsDialog::init_cpp5()
{
    QSplitter * split = new QSplitter(Qt::Vertical, this);

    split->setOpaqueResize(TRUE);

    HHBox * htab;

    htab =new HHBox(split);
    htab->setMargin(3);
    QLabel * lbl1;
    htab->addWidget(lbl1 = new QLabel(TR("External classes : \nname making\n#include, using"), htab));
    htab->addWidget(edcpp_external_class_decl = new MultiLineEdit(htab));
    edcpp_external_class_decl->setText(GenerationSettings::cpp_external_class_decl);
    htab =new HHBox(split);
    htab->setMargin(3);
    QLabel * lbl2 = new QLabel(TR("External types :\n#include form(s),\nusing, etc..."), htab);
    htab->addWidget(lbl2);
    htab->addWidget(cpp_include_table =
            new IncludeTable(htab, GenerationSettings::cpp_includes,
                             tr("Include etc...").toLatin1().constData(), "#include <>"));

    same_width(lbl1, lbl2);

    addTab(split, "C++[5]");

    if (!GenerationSettings::cpp_get_default_defs())
        removePage(split);

}

void GenerationSettingsDialog::init_java1()
{
    GridBox * grid = new GridBox(2, this);

    grid->setMargin(3);
    grid->setSpacing(3);

    grid->addWidget(new QLabel(TR("file default \ncontent :"), grid));
    HHBox * htab;
    grid->addWidget(htab =new HHBox(grid));

    htab->setMargin(3);

    htab->addWidget(edjava_src_content = new MultiLineEdit(htab));
    edjava_src_content->setText(GenerationSettings::java_src_content);
    QFont font = edjava_src_content->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);
    edjava_src_content->setFont(font);
    VVBox * vtab;
    htab->addWidget(vtab = new VVBox(htab));
    HHBox * htab2;
    vtab->addWidget(htab2 = new HHBox(vtab));

    vtab->setMargin(3);
    htab2->setMargin(3);

    htab2->addWidget(new QLabel(TR("    generated/reversed file extension "), htab2));
    htab2->addWidget(edjava_extension = new QComboBox(htab2));
    edjava_extension->setEditable(true);
    edjava_extension->addItem(GenerationSettings::java_extension);
    edjava_extension->setCurrentIndex(0);
    edjava_extension->addItem("java");

    vtab->addWidget(htab2 = new HHBox(vtab));
    htab2->setMargin(3);
    htab2->addWidget(new QLabel(TR("    generate Javadoc style comment "), htab2));
    htab2->addWidget(java_javadoc_cb = new QCheckBox(htab2));
    java_javadoc_cb->setChecked(GenerationSettings::java_javadoc_comment);

    vtab->addWidget(htab2 = new HHBox(vtab));
    htab2->setMargin(3);
    htab2->addWidget(new QLabel(TR("    force package prefix generation "), htab2));
    htab2->addWidget(java_force_package_gen_cb = new QCheckBox(htab2));
    java_force_package_gen_cb->setChecked(GenerationSettings::java_force_package_gen);

    grid->addWidget(new QLabel(TR("Class default \ndeclaration :"), grid));
    grid->addWidget(edjava_class_decl = new MultiLineEdit(grid));
    edjava_class_decl->setText(GenerationSettings::java_class_decl);
    edjava_class_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Interface default \ndeclaration :"), grid));
    grid->addWidget(edjava_interface_decl = new MultiLineEdit(grid));
    edjava_interface_decl->setText(GenerationSettings::java_interface_decl);
    edjava_interface_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Enum default \ndeclaration :"), grid));
    grid->addWidget(edjava_enum_decl = new MultiLineEdit(grid));
    edjava_enum_decl->setText(GenerationSettings::java_enum_decl);
    edjava_enum_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Enum pattern \ndefault declaration :"), grid));
    grid->addWidget(edjava_enum_pattern_decl = new MultiLineEdit(grid));
    edjava_enum_pattern_decl->setText(GenerationSettings::java_enum_pattern_decl);
    edjava_enum_pattern_decl->setFont(font);

    addTab(grid, "Java[1]");

    if (!GenerationSettings::java_get_default_defs())
        removePage(grid);
}

void GenerationSettingsDialog::init_java2()
{

    GridBox * grid = new GridBox(2, this);
    GridBox * grid2;

    grid->setMargin(3);
    grid->setSpacing(3);

    grid->addWidget(new QLabel(TR("Attribute \ndefault \ndeclaration :"), grid));

    grid->addWidget(grid2 = new GridBox(2, grid));
    grid2->addWidget(new QLabel(TR("multiplicity '1'\nor unspecified"), grid2));
    grid2->addWidget(edjava_attr_decl[0] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("multiplicity '*'\nor 'a..b'"), grid2));
    grid2->addWidget(edjava_attr_decl[1] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("X (probably a\nnumber)"), grid2));
    grid2->addWidget(edjava_attr_decl[2] = new MultiLineEdit(grid2));

    QFont font = edjava_attr_decl[0]->font();
    int i;

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);

    for (i = 0; i != 3; i += 1) {
        edjava_attr_decl[i]->setText(GenerationSettings::java_attr_decl[i]);
        edjava_attr_decl[i]->setFont(font);
    }

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    grid->addWidget(new QLabel(TR("Association and\naggregation\ndefault\ndeclaration :"), grid));
    grid->addWidget(grid2 = new GridBox(2, grid));
    grid2->addWidget(new QLabel(TR("multiplicity '1'\nor unspecified"), grid2));
    grid2->addWidget(edjava_rel_decl[0] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("multiplicity '*'\nor 'a..b'"), grid2));
    grid2->addWidget(edjava_rel_decl[1] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("X (probably a\nnumber)"), grid2));
    grid2->addWidget(edjava_rel_decl[2] = new MultiLineEdit(grid2));

    for (i = 0; i != 3; i += 1) {
        edjava_rel_decl[i]->setText(GenerationSettings::java_rel_decl[i]);
        edjava_rel_decl[i]->setFont(font);
    }

    addTab(grid, "Java[2]");

    if (!GenerationSettings::java_get_default_defs())
        removePage(grid);

}

void GenerationSettingsDialog::init_java3()
{

    GridBox * grid = new GridBox(2, this);
    HHBox * htab;
    BButtonGroup * bg;

    grid->setMargin(3);
    grid->setSpacing(3);

    grid->addWidget(new QLabel(TR("Enumeration item \ndefault definition :"), grid));
    grid->addWidget(edjava_enum_item_decl = new MultiLineEdit(grid));
    edjava_enum_item_decl->setText(GenerationSettings::java_enum_item_decl);

    QFont font = edjava_enum_item_decl->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);
    edjava_enum_item_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Enum pattern item \ndefault definition :"), grid));
    grid->addWidget(edjava_enum_pattern_item_decl = new MultiLineEdit(grid));
    edjava_enum_pattern_item_decl->setText(GenerationSettings::java_enum_pattern_item_decl);
    edjava_enum_pattern_item_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Enum pattern item \n'case' in 'from_int' :"), grid));
    grid->addWidget(edjava_enum_pattern_item_case = new MultiLineEdit(grid));
    edjava_enum_pattern_item_case->setText(GenerationSettings::java_enum_pattern_item_case);
    edjava_enum_pattern_item_case->setFont(font);

    grid->addWidget(new QLabel(TR("Get operation\ndefault definition : "), grid));
    grid->addWidget(htab =new HHBox(grid));
    htab->setMargin(3);
    htab->addWidget(java_get_visibility.init(htab, GenerationSettings::noncpp_get_visibility,
                                             TRUE, tr("Visibility (shared with Php)").toLatin1().constData()));
    java_get_visibility.connect(SIGNAL(clicked(int)), this, SLOT(java_get_visi_changed(int)));

    htab->addWidget(bg = new BButtonGroup(/*1, Qt::Horizontal, */TR("Modifiers"), htab));
    ////bg->setExclusive(FALSE);
    bg->addWidget(java_get_final_cb = new QCheckBox("final", bg));
    java_get_final_cb->setChecked(GenerationSettings::java_get_final);

    htab->addWidget(new QLabel(TR("  name : "), htab));
    htab->addWidget(edjava_get_name = new LineEdit(htab));
    edjava_get_name->setText(GenerationSettings::java_get_name);
    edjava_get_name->setFont(font);

    htab->addWidget(new QLabel("  ", htab));
    htab->addWidget(uml_follow_java_get_name = new QCheckBox(TR("also in uml"), htab));

    if (GenerationSettings::uml_get_name == JavaView)
        uml_follow_java_get_name->setChecked(TRUE);

    connect(uml_follow_java_get_name, SIGNAL(toggled(bool)),
            this, SLOT(follow_java_get_name()));

    grid->addWidget(new QLabel(TR("Set operation\ndefault definition : "), grid));
    grid->addWidget(htab =new HHBox(grid));
    htab->setMargin(3);
    htab->addWidget(java_set_visibility.init(htab, GenerationSettings::noncpp_set_visibility,
                                             TRUE, tr("Visibility (shared with Php)").toLatin1().constData()));
    java_set_visibility.connect(SIGNAL(clicked(int)), this, SLOT(java_set_visi_changed(int)));

    htab->addWidget(bg = new BButtonGroup(/*2, Qt::Horizontal,*/ QObject::tr("Modifiers"), htab));
    ////bg->setExclusive(FALSE);
    bg->addWidget(java_set_final_cb = new QCheckBox("final", bg));
    bg->addWidget(java_set_param_final_cb = new QCheckBox(TR("final parameter"), bg));
    java_set_final_cb->setChecked(GenerationSettings::java_set_final);
    java_set_param_final_cb->setChecked(GenerationSettings::java_set_param_final);

    htab->addWidget(new QLabel(TR("  name : "), htab));
    htab->addWidget(edjava_set_name = new LineEdit(htab));
    edjava_set_name->setText(GenerationSettings::java_set_name);
    edjava_set_name->setFont(font);

    htab->addWidget(new QLabel("  ", htab));
    htab->addWidget(uml_follow_java_set_name = new QCheckBox(TR("also in uml"), htab));

    if (GenerationSettings::uml_set_name == JavaView)
        uml_follow_java_set_name->setChecked(TRUE);

    connect(uml_follow_java_set_name, SIGNAL(toggled(bool)),
            this, SLOT(follow_java_set_name()));

    //new QLabel(grid));
    //new QLabel(grid));

    grid->addWidget(new QLabel(TR("Operation\ndefault definition :"), grid));
    grid->addWidget(edjava_oper_def = new MultiLineEdit(grid));
    edjava_oper_def->setText(GenerationSettings::java_oper_def);
    edjava_oper_def->setFont(font);

    addTab(grid, "Java[3]");

    if (!GenerationSettings::java_get_default_defs())
        removePage(grid);

}

void GenerationSettingsDialog::init_java4()
{

    QSplitter * split = new QSplitter(Qt::Vertical, this);

    split->setOpaqueResize(TRUE);

    HHBox * htab;

    htab =new HHBox(split);
    htab->setMargin(3);
    QLabel * lbl1;
    htab->addWidget(lbl1 =
            new QLabel(TR("External classes : \nname making"), htab));
    htab->addWidget(edjava_external_class_decl = new LineEdit(htab));
    edjava_external_class_decl->setText(GenerationSettings::java_external_class_decl);

    htab =new HHBox(split);
    htab->setMargin(3);
    QLabel * lbl2;
    htab->addWidget(lbl2 =
            new QLabel(TR("External types :\nimport form(s) etc..."), htab));
    htab->addWidget(java_import_table =
            new IncludeTable(htab, GenerationSettings::java_imports,
                             "Import etc...", "import "));

    same_width(lbl1, lbl2);
    addTab(split, "Java[4]");

    if (!GenerationSettings::java_get_default_defs())
        removePage(split);

}

void GenerationSettingsDialog::init_php1()
{

    GridBox * grid = new GridBox(2, this);

    grid->setMargin(3);
    grid->setSpacing(3);

    grid->addWidget(new QLabel(TR("file default \ncontent :"), grid));

    HHBox * htab;
    grid->addWidget(htab =new HHBox(grid));

    htab->setMargin(3);

    htab->addWidget(edphp_src_content = new MultiLineEdit(htab));
    edphp_src_content->setText(GenerationSettings::php_src_content);
    QFont font = edphp_src_content->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);
    edphp_src_content->setFont(font);

    VVBox* vtab;
    HHBox * htab2;
    htab->addWidget(vtab = new VVBox(htab));
    vtab->addWidget(htab2 = new HHBox(vtab));

    vtab->setMargin(3);
    htab2->setMargin(3);

    htab2->addWidget(new QLabel(TR("    generated / reversed file extension : "), htab2));
    htab2->addWidget(edphp_extension = new QComboBox(htab2));
    edphp_extension->setEditable(true);
    edphp_extension->addItem(GenerationSettings::php_extension);
    edphp_extension->setCurrentIndex(0);
    edphp_extension->addItem("php");

    vtab->addWidget(htab2 = new HHBox(vtab));
    htab2->setMargin(3);
    htab2->addWidget(new QLabel(TR("    generate Javadoc style comment : "), htab2));
    htab2->addWidget(php_javadoc_cb = new QCheckBox(htab2));
    php_javadoc_cb->setChecked(GenerationSettings::php_javadoc_comment);

    vtab->addWidget(htab2 = new HHBox(vtab));
    htab2->setMargin(3);
    htab2->addWidget(new QLabel(TR("    require_once : "), htab2));
    htab2->addWidget(php_require_with_path_cb = new QComboBox( htab2));
    php_require_with_path_cb->addItem(TR("without path"));
    php_require_with_path_cb->addItem(TR("with absolute path"));
    php_require_with_path_cb->addItem(TR("with relative path"));
    php_require_with_path_cb->addItem(TR("with root relative path"));

    if (!GenerationSettings::php_req_with_path)
        php_require_with_path_cb->setCurrentIndex(0);
    else if (GenerationSettings::php_relative_path)
        php_require_with_path_cb->setCurrentIndex(2);
    else if (GenerationSettings::php_root_relative_path)
        php_require_with_path_cb->setCurrentIndex(3);
    else
        php_require_with_path_cb->setCurrentIndex(1);

    vtab->addWidget(htab2 = new HHBox(vtab));
    htab2->setMargin(3);
    htab2->addWidget(new QLabel(TR("    force namespace prefix generation : "), htab2));
    htab2->addWidget(php_force_namespace_gen_cb = new QCheckBox(htab2));
    php_force_namespace_gen_cb->setChecked(GenerationSettings::php_force_namespace_gen);

    grid->addWidget(new QLabel(TR("Class default \ndeclaration :"), grid));
    grid->addWidget(edphp_class_decl = new MultiLineEdit(grid));
    edphp_class_decl->setText(GenerationSettings::php_class_decl);
    edphp_class_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Interface default \ndeclaration :"), grid));
    grid->addWidget(edphp_interface_decl = new MultiLineEdit(grid));
    edphp_interface_decl->setText(GenerationSettings::php_interface_decl);
    edphp_interface_decl->setFont(font);

    grid->addWidget( new QLabel(TR("Enum default \ndeclaration :"), grid));
    grid->addWidget(edphp_enum_decl = new MultiLineEdit(grid));
    edphp_enum_decl->setText(GenerationSettings::php_enum_decl);
    edphp_enum_decl->setFont(font);

    addTab(grid, "Php[1]");

    if (!GenerationSettings::php_get_default_defs())
        removePage(grid);

}

void GenerationSettingsDialog::init_php2()
{

    GridBox * grid = new GridBox(2, this);

    grid->setMargin(3);
    grid->setSpacing(3);

    grid->addWidget(new QLabel(TR("Attribute default \ndeclaration :"), grid));
    grid->addWidget(edphp_attr_decl = new MultiLineEdit(grid));

    QFont font = edphp_attr_decl->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);

    edphp_attr_decl->setText(GenerationSettings::php_attr_decl);
    edphp_attr_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Association and\naggregation\ndefault\ndeclaration :"), grid));
    grid->addWidget(edphp_rel_decl = new MultiLineEdit(grid));
    edphp_rel_decl->setText(GenerationSettings::php_rel_decl);
    edphp_rel_decl->setFont(font);

    HHBox * htab;
    BButtonGroup * bg;

    grid->addWidget(new QLabel(TR("Enumeration item \ndefault definition :"), grid));
    grid->addWidget(edphp_enum_item_decl = new MultiLineEdit(grid));
    edphp_enum_item_decl->setText(GenerationSettings::php_enum_item_decl);

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);
    edphp_enum_item_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Get operation\ndefault definition : "), grid));
    grid->addWidget(htab =new HHBox(grid));
    htab->setMargin(3);
    htab->addWidget(php_get_visibility.init(htab, GenerationSettings::noncpp_get_visibility,
                                            FALSE, tr("Visibility (shared with Java)").toLatin1().constData()));
    php_get_visibility.connect(SIGNAL(clicked(int)), this, SLOT(php_get_visi_changed(int)));

    htab->addWidget(bg = new BButtonGroup(/*1, Qt::Horizontal,*/ QObject::tr("Modifiers"), htab));
    ////bg->setExclusive(FALSE);
    bg->addWidget(php_get_final_cb = new QCheckBox("final", bg));
    php_get_final_cb->setChecked(GenerationSettings::php_get_final);

    htab->addWidget(new QLabel(TR("  name : "), htab));
    htab->addWidget(edphp_get_name = new LineEdit(htab));
    edphp_get_name->setText(GenerationSettings::php_get_name);
    edphp_get_name->setFont(font);

    htab->addWidget(new QLabel("  ", htab));
    htab->addWidget(uml_follow_php_get_name = new QCheckBox(TR("also in uml"), htab));

    if (GenerationSettings::uml_get_name == PhpView)
        uml_follow_php_get_name->setChecked(TRUE);

    connect(uml_follow_php_get_name, SIGNAL(toggled(bool)),
            this, SLOT(follow_php_get_name()));

    grid->addWidget(new QLabel(TR("Set operation\ndefault definition : "), grid));
    grid->addWidget(htab =new HHBox(grid));
    htab->setMargin(3);
    htab->addWidget(php_set_visibility.init(htab, GenerationSettings::noncpp_set_visibility,
                                            FALSE, tr("Visibility (shared with Java)").toLatin1().constData()));
    php_set_visibility.connect(SIGNAL(clicked(int)), this, SLOT(php_set_visi_changed(int)));

    htab->addWidget(bg = new BButtonGroup(/*2, Qt::Horizontal,*/ QObject::tr("Modifiers"), htab));
    //bg->setExclusive(FALSE);
    bg->addWidget(php_set_final_cb = new QCheckBox("final", bg));
    php_set_final_cb->setChecked(GenerationSettings::php_set_final);

    htab->addWidget(new QLabel(TR("  name : "), htab));
    htab->addWidget(edphp_set_name = new LineEdit(htab));
    edphp_set_name->setText(GenerationSettings::php_set_name);
    edphp_set_name->setFont(font);

    htab->addWidget(new QLabel("  ", htab));
    htab->addWidget(uml_follow_php_set_name = new QCheckBox(TR("also in uml"), htab));

    if (GenerationSettings::uml_set_name == PhpView)
        uml_follow_php_set_name->setChecked(TRUE);

    connect(uml_follow_php_set_name, SIGNAL(toggled(bool)),
            this, SLOT(follow_php_set_name()));

    //new QLabel(grid));
    //new QLabel(grid));

    grid->addWidget(new QLabel(TR("Operation\ndefault definition :"), grid));
    grid->addWidget(edphp_oper_def = new MultiLineEdit(grid));
    edphp_oper_def->setText(GenerationSettings::php_oper_def);
    edphp_oper_def->setFont(font);

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    grid->addWidget(new QLabel(TR("External classes : \nname making"), grid));
    grid->addWidget(edphp_external_class_decl = new LineEdit(grid));
    edphp_external_class_decl->setText(GenerationSettings::php_external_class_decl);

    addTab(grid, "Php[2]");

    if (!GenerationSettings::php_get_default_defs())
        removePage(grid);

}

void GenerationSettingsDialog::init_python1()
{

    GridBox * grid = new GridBox(2, this);

    grid->setMargin(3);
    grid->setSpacing(3);

    grid->addWidget(new QLabel(TR("indent step :"), grid));

    HHBox * htab;
    grid->addWidget(htab =new HHBox(grid));

    htab->setMargin(3);
    htab->addWidget(indentstep_cb = new QComboBox(htab));
    init_indent(indentstep_cb, GenerationSettings::python_indent_step);

    QLabel * lbl;
    htab->addWidget(lbl = new QLabel(htab));
    QSizePolicy sp = lbl->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    lbl->setSizePolicy(sp);

    grid->addWidget(new QLabel(TR("file default \ncontent :"), grid));

    grid->addWidget(htab =new HHBox(grid));
    htab->setMargin(3);
    htab->addWidget(edpython_src_content = new MultiLineEdit(htab));
    edpython_src_content->setText(GenerationSettings::python_src_content);
    QFont font = edpython_src_content->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);
    edpython_src_content->setFont(font);

    htab->addWidget(new QLabel(TR("    generated /\n    reversed\n    file extension : "), htab));
    htab->addWidget(edpython_extension = new QComboBox(htab));
    edpython_extension->setEditable(true);
    edpython_extension->addItem(GenerationSettings::python_extension);
    edpython_extension->setCurrentIndex(0);
    edpython_extension->addItem("py");

    grid->addWidget(new QLabel(TR("Class default \ndeclaration :"), grid));

    grid->addWidget(htab =new HHBox(grid));
    htab->setMargin(3);
    htab->addWidget(edpython_class_decl = new MultiLineEdit(htab));
    edpython_class_decl->setText(GenerationSettings::python_class_decl);
    edpython_class_decl->setFont(font);

    htab->addWidget(new QLabel(TR("    classes of Python 2.2 "), htab));
    htab->addWidget(python_2_2_cb = new QCheckBox(htab));
    python_2_2_cb->setChecked(GenerationSettings::python_2_2);

    grid->addWidget(new QLabel(TR("Enum default \ndeclaration :"), grid));
    grid->addWidget(edpython_enum_decl = new MultiLineEdit(grid));
    edpython_enum_decl->setText(GenerationSettings::python_enum_decl);
    edpython_enum_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Enumeration item \ndefault definition :"), grid));
    grid->addWidget(edpython_enum_item_decl = new MultiLineEdit(grid));
    edpython_enum_item_decl->setText(GenerationSettings::python_enum_item_decl);
    edpython_enum_item_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Attribute \ndefault \ndeclaration :"), grid));

    GridBox * grid2;
    grid->addWidget(grid2 = new GridBox(2, grid));

    grid2->addWidget(new QLabel(TR("multiplicity '1'\nor unspecified"), grid2));
    grid2->addWidget(edpython_attr_decl[0] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("other\nmultiplicity"), grid2));
    grid2->addWidget(edpython_attr_decl[1] = new MultiLineEdit(grid2));

    int i;

    for (i = 0; i != 2; i += 1) {
        edpython_attr_decl[i]->setText(GenerationSettings::python_attr_decl[i]);
        edpython_attr_decl[i]->setFont(font);
    }

    addTab(grid, "Python[1]");

    if (!GenerationSettings::python_get_default_defs())
        removePage(grid);

}

void GenerationSettingsDialog::init_python2()
{

    GridBox * grid = new GridBox(2, this);
    GridBox * grid2;

    grid->setMargin(3);
    grid->setSpacing(3);

    grid->addWidget(new QLabel(TR("Association and\naggregation\ndefault\ndeclaration :"), grid));
    grid->addWidget(grid2 = new GridBox(2, grid));
    grid2->addWidget(new QLabel(TR("multiplicity '1'\nor unspecified"), grid2));
    grid2->addWidget(edpython_rel_decl[0][0] = new MultiLineEdit(grid2));

    QFont font = edpython_rel_decl[0][0]->font();
    int i;

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);

    grid2->addWidget(new QLabel(TR("other\nmultiplicity"), grid2));
    grid2->addWidget(edpython_rel_decl[0][1] = new MultiLineEdit(grid2));

    for (i = 0; i != 2; i += 1) {
        edpython_rel_decl[0][i]->setText(GenerationSettings::python_rel_decl[0][i]);
        edpython_rel_decl[0][i]->setFont(font);
    }

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    grid->addWidget(new QLabel(TR("Composition\ndefault\ndeclaration :"), grid));
    grid->addWidget(grid2 = new GridBox(2, grid));
    grid2->addWidget(new QLabel(TR("multiplicity '1'\nor unspecified"), grid2));
    grid2->addWidget(edpython_rel_decl[1][0] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("other\nmultiplicity"), grid2));
    grid2->addWidget(edpython_rel_decl[1][1] = new MultiLineEdit(grid2));

    for (i = 0; i != 2; i += 1) {
        edpython_rel_decl[1][i]->setText(GenerationSettings::python_rel_decl[1][i]);
        edpython_rel_decl[1][i]->setFont(font);
    }

    HHBox * htab;

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    grid->addWidget(new QLabel(TR("Get operation\ndefault definition : "), grid));
    grid->addWidget(htab =new HHBox(grid));
    htab->setMargin(3);
    htab->addWidget(new QLabel(TR("  name : "), htab));
    htab->addWidget(edpython_get_name = new LineEdit(htab));
    edpython_get_name->setText(GenerationSettings::python_get_name);
    edpython_get_name->setFont(font);

    htab->addWidget(new QLabel("  ", htab));
    htab->addWidget(uml_follow_python_get_name = new QCheckBox(TR("also in uml"), htab));

    if (GenerationSettings::uml_get_name == PythonView)
        uml_follow_python_get_name->setChecked(TRUE);

    connect(uml_follow_python_get_name, SIGNAL(toggled(bool)),
            this, SLOT(follow_python_get_name()));

    grid->addWidget(new QLabel(TR("Set operation\ndefault definition : "), grid));
    grid->addWidget(htab =new HHBox(grid));
    htab->setMargin(3);
    htab->addWidget(new QLabel(TR("  name : "), htab));
    htab->addWidget(edpython_set_name = new LineEdit(htab));
    edpython_set_name->setText(GenerationSettings::python_set_name);
    edpython_set_name->setFont(font);

    htab->addWidget(new QLabel("  ", htab));
    htab->addWidget(uml_follow_python_set_name = new QCheckBox(TR("also in uml"), htab));

    if (GenerationSettings::uml_set_name == PythonView)
        uml_follow_python_set_name->setChecked(TRUE);

    connect(uml_follow_python_set_name, SIGNAL(toggled(bool)),
            this, SLOT(follow_python_set_name()));

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    grid->addWidget(new QLabel(TR("Operation\ndefault definition :"), grid));
    grid->addWidget(htab =new HHBox(grid));
    htab->setMargin(3);
    htab->addWidget(edpython_oper_def = new MultiLineEdit(htab));
    edpython_oper_def->setText(GenerationSettings::python_oper_def);
    edpython_oper_def->setFont(font);
    htab->addWidget(new QLabel(TR("    operation of Python 3 (pep-3107) "), htab));
    htab->addWidget(python_3_operation_cb = new QCheckBox(htab));
    python_3_operation_cb->setChecked(GenerationSettings::python_3_operation);

    grid->addWidget(new QLabel(TR("Operation __init__\ndefault definition :"), grid));
    grid->addWidget(edpython_initoper_def = new MultiLineEdit(grid));
    edpython_initoper_def->setText(GenerationSettings::python_initoper_def);
    edpython_initoper_def->setFont(font);

    addTab(grid, "Python[2]");

    if (!GenerationSettings::python_get_default_defs())
        removePage(grid);

}

void GenerationSettingsDialog::init_python3()
{

    QSplitter * split = new QSplitter(Qt::Vertical, this);

    split->setOpaqueResize(TRUE);

    HHBox * htab;

    htab =new HHBox(split);
    htab->setMargin(3);
    QLabel * lbl1;
    htab->addWidget(lbl1 =
            new QLabel(TR("External classes : \nname making\nimport"), htab));
    htab->addWidget(edpython_external_class_decl = new MultiLineEdit(htab));
    edpython_external_class_decl->setText(GenerationSettings::python_external_class_decl);

    htab =new HHBox(split);
    htab->setMargin(3);
    QLabel * lbl2;
    htab->addWidget(lbl2 =
            new QLabel(TR("External types :\nimport form(s)"), htab));
    htab->addWidget(python_import_table =
            new IncludeTable(htab, GenerationSettings::python_imports,
                             "Import", "import "));

    same_width(lbl1, lbl2);
    addTab(split, "Python[3]");

    if (!GenerationSettings::python_get_default_defs())
        removePage(split);

}

void GenerationSettingsDialog::init_idl1()
{

    QSplitter * split = new QSplitter(Qt::Vertical, this);

    split->setOpaqueResize(TRUE);

    HHBox * htab;

    htab =new HHBox(split);
    htab->setMargin(3);
    QLabel * lbl1;
    htab->addWidget(lbl1 =
            new QLabel(TR("file default \ncontent :"), htab));
    htab->addWidget(edidl_src_content = new MultiLineEdit(htab));
    edidl_src_content->setText(GenerationSettings::idl_src_content);
    QFont font = edidl_src_content->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);
    edidl_src_content->setFont(font);

    htab->addWidget(new QLabel(TR("    file extension : "), htab));
    htab->addWidget(edidl_extension = new QComboBox( htab));
    edidl_extension->setEditable(true);
    edidl_extension->addItem(GenerationSettings::idl_extension);
    edidl_extension->setCurrentIndex(0);
    edidl_extension->addItem("Idl");

    GridBox * grid = new GridBox(2, split);

    grid->setMargin(3);
    grid->setSpacing(3);

    grid->addWidget(new QLabel(TR("Interface default \ndeclaration :"), grid));
    grid->addWidget(edidl_interface_decl = new MultiLineEdit(grid));
    edidl_interface_decl->setText(GenerationSettings::idl_interface_decl);
    edidl_interface_decl->setFont(font);

    QLabel * lbl2;
    grid->addWidget( lbl2 = new QLabel(TR("Valuetype default \ndeclaration :"), grid));
    same_width(lbl1, lbl2);
    grid->addWidget(edidl_valuetype_decl = new MultiLineEdit(grid));
    edidl_valuetype_decl->setText(GenerationSettings::idl_valuetype_decl);
    edidl_valuetype_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Struct default \ndeclaration :"), grid));
    grid->addWidget(edidl_struct_decl = new MultiLineEdit(grid));
    edidl_struct_decl->setText(GenerationSettings::idl_struct_decl);
    edidl_struct_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Union default \ndeclaration :"), grid));
    grid->addWidget(edidl_union_decl = new MultiLineEdit(grid));
    edidl_union_decl->setText(GenerationSettings::idl_union_decl);
    edidl_union_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Enum default \ndeclaration :"), grid));
    grid->addWidget(edidl_enum_decl = new MultiLineEdit(grid));
    edidl_enum_decl->setText(GenerationSettings::idl_enum_decl);
    edidl_enum_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Typedef default \ndeclaration :"), grid));
    grid->addWidget(edidl_typedef_decl = new MultiLineEdit(grid));
    edidl_typedef_decl->setText(GenerationSettings::idl_typedef_decl);
    edidl_typedef_decl->setFont(font);

    grid->addWidget(new QLabel(TR("Exception default \ndeclaration :"), grid));
    grid->addWidget(edidl_exception_decl = new MultiLineEdit(grid));
    edidl_exception_decl->setText(GenerationSettings::idl_exception_decl);
    edidl_exception_decl->setFont(font);

    addTab(split, "Idl[1]");

    if (!GenerationSettings::idl_get_default_defs())
        removePage(split);

}

void GenerationSettingsDialog::init_idl2()
{

    GridBox * grid = new GridBox(2, this);
    GridBox * grid2;

    grid->setMargin(3);
    grid->setSpacing(3);

    grid->addWidget(new QLabel(TR("Attribute default \ndeclaration :"), grid));
    grid->addWidget(grid2 = new GridBox(2, grid));
    grid2->addWidget(new QLabel(TR("multiplicity '1'\nor unspecified"), grid2));
    grid2->addWidget(edidl_attr_decl[0] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("multiplicity '*'\nor 'a..b'"), grid2));
    grid2->addWidget(edidl_attr_decl[1] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("X (probably a\nnumber)"), grid2));
    grid2->addWidget(edidl_attr_decl[2] = new MultiLineEdit(grid2));

    QFont font = edjava_attr_decl[0]->font();
    int i;

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);

    for (i = 0; i != 3; i += 1) {
        edidl_attr_decl[i]->setText(GenerationSettings::idl_attr_decl[i]);
        edidl_attr_decl[i]->setFont(font);
    }

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    grid->addWidget(new QLabel(TR("Attribute default \ndeclaration in\nvaluetype :"), grid));
    grid->addWidget(grid2 = new GridBox(2, grid));
    grid2->addWidget(new QLabel(TR("multiplicity '1'\nor unspecified"), grid2));
    grid2->addWidget(edidl_valuetype_attr_decl[0] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("multiplicity '*'\nor 'a..b'"), grid2));
    grid2->addWidget(edidl_valuetype_attr_decl[1] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("X (probably a\nnumber)"), grid2));
    grid2->addWidget(edidl_valuetype_attr_decl[2] = new MultiLineEdit(grid2));

    for (i = 0; i != 3; i += 1) {
        edidl_valuetype_attr_decl[i]->setText(GenerationSettings::idl_valuetype_attr_decl[i]);
        edidl_valuetype_attr_decl[i]->setFont(font);
    }

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    grid->addWidget(new QLabel(TR("Constant default \ndeclaration :"), grid));
    grid->addWidget(grid2 = new GridBox(2, grid));
    grid2->addWidget(new QLabel(TR("multiplicity '1'\nor unspecified"), grid2));
    grid2->addWidget(edidl_const_decl[0] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("multiplicity '*'\nor 'a..b'"), grid2));
    grid2->addWidget(edidl_const_decl[1] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("X (probably a\nnumber)"), grid2));
    grid2->addWidget(edidl_const_decl[2] = new MultiLineEdit(grid2));

    for (i = 0; i != 3; i += 1) {
        edidl_const_decl[i]->setText(GenerationSettings::idl_const_decl[i]);
        edidl_const_decl[i]->setFont(font);
    }

    addTab(grid, "Idl[2]");

    if (!GenerationSettings::idl_get_default_defs())
        removePage(grid);

}

void GenerationSettingsDialog::init_idl3()
{

    GridBox * grid = new GridBox(2, this);
    GridBox * grid2;
    int i;

    grid->setMargin(3);
    grid->setSpacing(3);

    grid->addWidget(new QLabel(TR("Association and\naggregation\ndefault\ndeclaration :"), grid));
    grid->addWidget(grid2 = new GridBox(2, grid));
    grid2->addWidget(new QLabel(TR("multiplicity '1'\nor unspecified"), grid2));
    grid2->addWidget(edidl_rel_decl[0] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("multiplicity '*'\nor 'a..b'"), grid2));
    grid2->addWidget(edidl_rel_decl[1] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("X (probably a\nnumber)"), grid2));
    grid2->addWidget(edidl_rel_decl[2] = new MultiLineEdit(grid2));
    QFont font = edidl_rel_decl[0]->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);

    for (i = 0; i != 3; i += 1) {
        edidl_rel_decl[i]->setText(GenerationSettings::idl_rel_decl[i]);
        edidl_rel_decl[i]->setFont(font);
    }

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    grid->addWidget(new QLabel(TR("Association and\naggregation\ndefault\ndeclaration in\nvaluetype :"), grid));
    grid->addWidget(grid2 = new GridBox(2, grid));
    grid2->addWidget(new QLabel(TR("multiplicity '1'\nor unspecified"), grid2));
    grid2->addWidget(edidl_valuetype_rel_decl[0] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("multiplicity '*'\nor 'a..b'"), grid2));
    grid2->addWidget(edidl_valuetype_rel_decl[1] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("X (probably a\nnumber)"), grid2));
    grid2->addWidget(edidl_valuetype_rel_decl[2] = new MultiLineEdit(grid2));

    for (i = 0; i != 3; i += 1) {
        edidl_valuetype_rel_decl[i]->setText(GenerationSettings::idl_valuetype_rel_decl[i]);
        edidl_valuetype_rel_decl[i]->setFont(font);
    }

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    grid->addWidget(new QLabel(TR("Association and\naggregation\ndefault\ndeclaration in\nunion:"), grid));
    grid->addWidget(grid2 = new GridBox(2, grid));
    grid2->addWidget(new QLabel(TR("multiplicity '1'\nor unspecified"), grid2));
    grid2->addWidget(edidl_union_rel_decl[0] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("multiplicity '*'\nor 'a..b'"), grid2));
    grid2->addWidget(edidl_union_rel_decl[1] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("X (probably a\nnumber)"), grid2));
    grid2->addWidget(edidl_union_rel_decl[2] = new MultiLineEdit(grid2));

    for (i = 0; i != 3; i += 1) {
        edidl_union_rel_decl[i]->setText(GenerationSettings::idl_union_rel_decl[i]);
        edidl_union_rel_decl[i]->setFont(font);
    }

    addTab(grid, "Idl[3]");

    if (!GenerationSettings::idl_get_default_defs())
        removePage(grid);

}

void GenerationSettingsDialog::init_idl4()
{

    GridBox * grid = new GridBox(2, this);
    GridBox * grid2;
    HHBox * htab;

    grid->setMargin(3);
    grid->setSpacing(3);

    grid->addWidget(new QLabel(TR("Union item \ndefault \ndeclaration :"), grid));
    grid->addWidget(grid2 = new GridBox(2, grid));
    grid2->addWidget(new QLabel(TR("multiplicity '1'\nor unspecified"), grid2));
    grid2->addWidget(edidl_union_item_decl[0] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("multiplicity '*'\nor 'a..b'"), grid2));
    grid2->addWidget(edidl_union_item_decl[1] = new MultiLineEdit(grid2));
    grid2->addWidget(new QLabel(TR("X (probably a\nnumber)"), grid2));
    grid2->addWidget(edidl_union_item_decl[2] = new MultiLineEdit(grid2));

    QFont font = edidl_union_item_decl[0]->font();
    int i;

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);

    for (i = 0; i != 3; i += 1) {
        edidl_union_item_decl[i]->setText(GenerationSettings::idl_union_item_decl[i]);
        edidl_union_item_decl[i]->setFont(font);
    }

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    grid->addWidget(new QLabel(TR("Enumeration item \ndefault declaration :"), grid));
    grid->addWidget(edidl_enum_item_decl = new MultiLineEdit(grid));
    edidl_enum_item_decl->setText(GenerationSettings::idl_enum_item_decl);
    edidl_enum_item_decl->setFont(font);

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    grid->addWidget(new QLabel(TR("Get operation\ndefault definition : "), grid));
    grid->addWidget(htab =new HHBox(grid));
    htab->addWidget(new QLabel(TR("name : "), htab));
    htab->addWidget(edidl_get_name = new LineEdit(htab));
    edidl_get_name->setText(GenerationSettings::idl_get_name);
    edidl_get_name->setFont(font);

    htab->addWidget(new QLabel("  ", htab));
    htab->addWidget(uml_follow_idl_get_name = new QCheckBox(TR("also in uml"), htab));

    if (GenerationSettings::uml_get_name == IdlView)
        uml_follow_idl_get_name->setChecked(TRUE);

    connect(uml_follow_idl_get_name, SIGNAL(toggled(bool)),
            this, SLOT(follow_idl_get_name()));

    grid->addWidget(new QLabel(TR("Set operation\ndefault definition : "), grid));
    grid->addWidget(htab =new HHBox(grid));
    htab->addWidget(idl_set_oneway_cb = new QCheckBox("oneway", htab));
    idl_set_oneway_cb->setChecked(GenerationSettings::idl_set_oneway);

    htab->addWidget(new QLabel(TR("  name : "), htab));
    htab->addWidget(edidl_set_name = new LineEdit(htab));
    edidl_set_name->setText(GenerationSettings::idl_set_name);
    edidl_set_name->setFont(font);

    htab->addWidget(new QLabel("  ", htab));
    htab->addWidget(uml_follow_idl_set_name = new QCheckBox(TR("also in uml"), htab));

    if (GenerationSettings::uml_set_name == IdlView)
        uml_follow_idl_set_name->setChecked(TRUE);

    connect(uml_follow_idl_set_name, SIGNAL(toggled(bool)),
            this, SLOT(follow_idl_set_name()));

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    grid->addWidget(new QLabel(TR("Operation default \ndeclaration : "), grid));
    grid->addWidget(edidl_oper_decl = new MultiLineEdit(grid));
    edidl_oper_decl->setText(GenerationSettings::idl_oper_decl);
    edidl_oper_decl->setFont(font);

    addTab(grid, "Idl[4]");

    if (!GenerationSettings::idl_get_default_defs())
        removePage(grid);

}

void GenerationSettingsDialog::init_idl5()
{

    QSplitter * split = new QSplitter(Qt::Vertical, this);

    split->setOpaqueResize(TRUE);

    HHBox * htab;

    htab =new HHBox(split);
    htab->setMargin(3);
    QLabel * lbl1;
    htab->addWidget(lbl1 =
            new QLabel(TR("External classes : \nname making\n#include"), htab));
    htab->addWidget(edidl_external_class_decl = new MultiLineEdit(htab));
    edidl_external_class_decl->setText(GenerationSettings::idl_external_class_decl);
    htab =new HHBox(split);
    htab->setMargin(3);
    QLabel * lbl2;
    htab->addWidget(lbl2 =
            new QLabel(TR("External types :\n#include form(s)\netc..."), htab));
    htab->addWidget(idl_include_table =
            new IncludeTable(htab, GenerationSettings::idl_includes,
                             "Include etc...", "#include \"\""));

    same_width(lbl1, lbl2);

    addTab(split, "Idl[5]");

    if (!GenerationSettings::idl_get_default_defs())
        removePage(split);

}

void GenerationSettingsDialog::init_descriptions()
{

    QSplitter * split = new QSplitter(Qt::Vertical, this);

    split->setOpaqueResize(TRUE);

    HHBox * htab;

    htab =new HHBox(split);
    htab->setMargin(3);
    htab->addWidget(new QLabel(TR("Artifact\ndefault\ndescription : "), htab));
    htab->addWidget(edartifact_default_description = new MultiLineEdit(htab));
    edartifact_default_description->setText(GenerationSettings::artifact_default_description);

    htab =new HHBox(split);
    htab->setMargin(3);
    htab->addWidget(new QLabel(TR("Class\ndefault\ndescription : "), htab));
    htab->addWidget(edclass_default_description = new MultiLineEdit(htab));
    edclass_default_description->setText(GenerationSettings::class_default_description);

    htab =new HHBox(split);
    htab->setMargin(3);
    htab->addWidget(new QLabel(TR("Operation\ndefault\ndescription : "), htab));
    htab->addWidget(edoperation_default_description = new MultiLineEdit(htab));
    edoperation_default_description->setText(GenerationSettings::operation_default_description);

    htab =new HHBox(split);
    htab->setMargin(3);
    htab->addWidget(new QLabel(TR("Attribute\ndefault\ndescription : "), htab));
    htab->addWidget(edattribute_default_description = new MultiLineEdit(htab));
    edattribute_default_description->setText(GenerationSettings::attribute_default_description);

    htab =new HHBox(split);
    htab->setMargin(3);
    htab->addWidget(new QLabel(TR("Relation\ndefault\ndescription : "), htab));
    htab->addWidget(edrelation_default_description = new MultiLineEdit(htab));
    edrelation_default_description->setText(GenerationSettings::relation_default_description);

    addTab(split, QObject::tr("Description"));

}

static QString Relative;
static QString Absolute;

void GenerationSettingsDialog::init_dirs()
{

    Relative = QObject::tr("Set it relative");
    Absolute = QObject::tr("Set it absolute");

    QPushButton * button;
    VVBox * vtab = new VVBox(this);
    HHBox * htab;

    vtab->setMargin(3);

    vtab->addWidget(htab =new HHBox(vtab));
    htab->setMargin(3);
    htab->addWidget(new QLabel(TR("Defining a project root directory allows to specify \
                                  packages's generation directory relative to the root directory rather \
                                  than absolute.\n"
                                                  "A root directory may itself be relative to the project path"),
                               htab));

    vtab->addWidget(htab =new HHBox(vtab));
    htab->setMargin(3);
    QLabel * lbl1;
    htab->addWidget(lbl1 = new QLabel(TR("C++ root dir : "), htab));
    htab->addWidget(edcpproot = new LineEdit(GenerationSettings::cpp_root_dir, htab));
    htab->addWidget(new QLabel(" ", htab));
    htab->addWidget(button = new SmallPushButton(TR("Browse"), htab));
    connect(button, SIGNAL(clicked()), this, SLOT(cpproot_browse()));
    htab->addWidget(new QLabel("", htab));
    htab->addWidget(cpprelbutton = new SmallPushButton((GenerationSettings::cpp_root_dir.isEmpty() ||
                                                        QDir::isRelativePath(GenerationSettings::cpp_root_dir))
                                                       ? Absolute : Relative, htab));
    connect(cpprelbutton, SIGNAL(clicked()), this, SLOT(cpp_relative()));
    htab->addWidget(new QLabel("", htab));

    vtab->addWidget(htab =new HHBox(vtab));
    htab->setMargin(3);
    htab->addWidget(new QLabel("", htab));

    vtab->addWidget(htab =new HHBox(vtab));
    htab->setMargin(3);
    QLabel * lbl2;
    htab->addWidget(lbl2 = new QLabel(TR("Java root dir : "), htab));
    htab->addWidget(lbl2);
    htab->addWidget(edjavaroot = new LineEdit(GenerationSettings::java_root_dir, htab));
    htab->addWidget(new QLabel(" ", htab));
    htab->addWidget(button = new SmallPushButton(TR("Browse"), htab));
    connect(button, SIGNAL(clicked()), this, SLOT(javaroot_browse()));
    htab->addWidget(new QLabel("", htab));
    htab->addWidget(javarelbutton = new SmallPushButton((GenerationSettings::java_root_dir.isEmpty() ||
                                                         QDir::isRelativePath(GenerationSettings::java_root_dir))
                                                        ? Absolute : Relative, htab));
    connect(javarelbutton, SIGNAL(clicked()), this, SLOT(java_relative()));
    htab->addWidget(new QLabel("", htab));

    vtab->addWidget(htab =new HHBox(vtab));
    htab->setMargin(3);
    htab->addWidget(new QLabel("", htab));

    vtab->addWidget(htab =new HHBox(vtab));
    htab->setMargin(3);
    QLabel * lbl3;
    htab->addWidget(lbl3 = new QLabel(TR("Php root dir : "), htab));
    htab->addWidget(edphproot = new LineEdit(GenerationSettings::php_root_dir, htab));
    htab->addWidget(new QLabel(" ", htab));
    htab->addWidget(button = new SmallPushButton(TR("Browse"), htab));
    connect(button, SIGNAL(clicked()), this, SLOT(phproot_browse()));
    htab->addWidget(new QLabel("", htab));
    htab->addWidget(phprelbutton = new SmallPushButton((GenerationSettings::php_root_dir.isEmpty() ||
                                                        QDir::isRelativePath(GenerationSettings::php_root_dir))
                                                       ? Absolute : Relative, htab));
    connect(phprelbutton, SIGNAL(clicked()), this, SLOT(php_relative()));
    htab->addWidget(new QLabel("", htab));

    vtab->addWidget(htab =new HHBox(vtab));
    htab->setMargin(3);
    htab->addWidget(new QLabel("", htab));

    vtab->addWidget(htab =new HHBox(vtab));
    htab->setMargin(3);
    QLabel * lbl4;
    htab->addWidget( lbl4 = new QLabel(TR("Python root dir : "), htab));
    htab->addWidget(edpythonroot = new LineEdit(GenerationSettings::python_root_dir, htab));
    htab->addWidget(new QLabel(" ", htab));
    htab->addWidget(button = new SmallPushButton(TR("Browse"), htab));
    connect(button, SIGNAL(clicked()), this, SLOT(pythonroot_browse()));
    htab->addWidget(new QLabel("", htab));
    htab->addWidget(pythonrelbutton = new SmallPushButton((GenerationSettings::python_root_dir.isEmpty() ||
                                                           QDir::isRelativePath(GenerationSettings::python_root_dir))
                                                          ? Absolute : Relative, htab));
    connect(pythonrelbutton, SIGNAL(clicked()), this, SLOT(python_relative()));
    htab->addWidget(new QLabel("", htab));

    vtab->addWidget(htab =new HHBox(vtab));
    htab->setMargin(3);
    htab->addWidget(new QLabel("", htab));

    vtab->addWidget(htab =new HHBox(vtab));
    htab->setMargin(3);
    QLabel * lbl5;
    htab->addWidget(lbl5 = new QLabel(TR("Idl root dir : "), htab));
    htab->addWidget(edidlroot = new LineEdit(GenerationSettings::idl_root_dir, htab));
    htab->addWidget(new QLabel(" ", htab));
    htab->addWidget(button = new SmallPushButton(TR("Browse"), htab));
    connect(button, SIGNAL(clicked()), this, SLOT(idlroot_browse()));
    htab->addWidget(new QLabel("", htab));
    htab->addWidget(idlrelbutton = new SmallPushButton((GenerationSettings::idl_root_dir.isEmpty() ||
                                                        QDir::isRelativePath(GenerationSettings::idl_root_dir))
                                                       ? Absolute : Relative, htab));
    connect(idlrelbutton, SIGNAL(clicked()), this, SLOT(idl_relative()));
    htab->addWidget(new QLabel("", htab));

    same_width(lbl1, lbl2, lbl3, lbl4, lbl5);

    ((QVBoxLayout*)vtab->layout())->setStretchFactor(new HHBox(vtab), 1000);

    addTab(vtab, QObject::tr("Directory"));

}

static QString add_last_slash(QString s)
{

    if (!s.isEmpty()) {
        int i = s.length() - 1;

        switch (s.at(i).toLatin1()) {
        case '/':
        case '\\':
            break;

        default:
            return QDir::toNativeSeparators(s + "/");
        }
    }

    return s;
}

void GenerationSettingsDialog::follow_cpp_get_name()
{
    if (uml_follow_cpp_get_name->isChecked()) {
        uml_follow_java_get_name->setChecked(FALSE);
        uml_follow_php_get_name->setChecked(FALSE);
        uml_follow_python_get_name->setChecked(FALSE);
        uml_follow_idl_get_name->setChecked(FALSE);
    }
}

void GenerationSettingsDialog::follow_cpp_set_name()
{
    if (uml_follow_cpp_set_name->isChecked()) {
        uml_follow_java_set_name->setChecked(FALSE);
        uml_follow_php_set_name->setChecked(FALSE);
        uml_follow_python_set_name->setChecked(FALSE);
        uml_follow_idl_set_name->setChecked(FALSE);
    }
}

void GenerationSettingsDialog::follow_java_get_name()
{
    if (uml_follow_java_get_name->isChecked()) {
        uml_follow_cpp_get_name->setChecked(FALSE);
        uml_follow_php_get_name->setChecked(FALSE);
        uml_follow_python_get_name->setChecked(FALSE);
        uml_follow_idl_get_name->setChecked(FALSE);
    }
}

void GenerationSettingsDialog::follow_java_set_name()
{
    if (uml_follow_java_set_name->isChecked()) {
        uml_follow_cpp_set_name->setChecked(FALSE);
        uml_follow_php_set_name->setChecked(FALSE);
        uml_follow_python_set_name->setChecked(FALSE);
        uml_follow_idl_set_name->setChecked(FALSE);
    }
}

void GenerationSettingsDialog::follow_php_get_name()
{
    if (uml_follow_php_get_name->isChecked()) {
        uml_follow_cpp_get_name->setChecked(FALSE);
        uml_follow_java_get_name->setChecked(FALSE);
        uml_follow_python_get_name->setChecked(FALSE);
        uml_follow_idl_get_name->setChecked(FALSE);
    }
}

void GenerationSettingsDialog::follow_php_set_name()
{
    if (uml_follow_php_set_name->isChecked()) {
        uml_follow_cpp_set_name->setChecked(FALSE);
        uml_follow_java_set_name->setChecked(FALSE);
        uml_follow_python_set_name->setChecked(FALSE);
        uml_follow_idl_set_name->setChecked(FALSE);
    }
}

void GenerationSettingsDialog::follow_python_get_name()
{
    if (uml_follow_php_get_name->isChecked()) {
        uml_follow_cpp_get_name->setChecked(FALSE);
        uml_follow_java_get_name->setChecked(FALSE);
        uml_follow_php_get_name->setChecked(FALSE);
        uml_follow_idl_get_name->setChecked(FALSE);
    }
}

void GenerationSettingsDialog::follow_python_set_name()
{
    if (uml_follow_php_set_name->isChecked()) {
        uml_follow_cpp_set_name->setChecked(FALSE);
        uml_follow_java_set_name->setChecked(FALSE);
        uml_follow_php_set_name->setChecked(FALSE);
        uml_follow_idl_set_name->setChecked(FALSE);
    }
}

void GenerationSettingsDialog::follow_idl_get_name()
{
    if (uml_follow_idl_get_name->isChecked()) {
        uml_follow_cpp_get_name->setChecked(FALSE);
        uml_follow_java_get_name->setChecked(FALSE);
        uml_follow_php_get_name->setChecked(FALSE);
        uml_follow_python_get_name->setChecked(FALSE);
    }
}

void GenerationSettingsDialog::follow_idl_set_name()
{
    if (uml_follow_idl_set_name->isChecked()) {
        uml_follow_cpp_set_name->setChecked(FALSE);
        uml_follow_java_set_name->setChecked(FALSE);
        uml_follow_php_set_name->setChecked(FALSE);
        uml_follow_python_set_name->setChecked(FALSE);
    }
}

static const char * get_indent(QComboBox * cb)
{
    int n = cb->currentIndex();

    return (n == 9)
            ? "\t"
            : "        " + (8 - n);
}

void GenerationSettingsDialog::accept()
{
    if (builtinTable->ValidateTypes())
    {
        GenerationSettings::builtins = builtinTable->GetBuiltins();
        GenerationSettings::nbuiltins = GenerationSettings::builtins.size();
        QString enum_in = cpp_enum_in->text().trimmed();
        QString enum_out = cpp_enum_out->text().trimmed();
        QString enum_inout = cpp_enum_inout->text().trimmed();
        QString enum_return = cpp_enum_return->text().trimmed();

        if (enum_in.indexOf("${type}") == -1) {
            msg_critical(TR("Error"), QObject::tr("C++ 'in' enum argument default passing must contains ${type}"));
            return;
        }

        if (enum_out.indexOf("${type}") == -1) {
            msg_critical(TR("Error"), QObject::tr("C++ 'out' enum argument default passing must contains ${type}"));
            return;
        }

        if (enum_inout.indexOf("${type}") == -1) {
            msg_critical(TR("Error"), QObject::tr("C++ 'inout' enum argument default passing must contains ${type}"));
            return;
        }

        if (enum_return.indexOf("${type}") == -1) {
            msg_critical(TR("Error"), QObject::tr("C++ 'return' enum argument default passing must contains ${type}"));
            return;
        }

        QString in = cpp_in->text().trimmed();
        QString out = cpp_out->text().trimmed();
        QString inout = cpp_inout->text().trimmed();
        QString opreturn = cpp_return->text().trimmed();

        if (in.indexOf("${type}") == -1) {
            msg_critical(TR("Error"), QObject::tr("C++ 'in' argument default passing must contains ${type}"));
            return;
        }

        if (out.indexOf("${type}") == -1) {
            msg_critical(TR("Error"), QObject::tr("C++ 'out' argument default passing must contains ${type}"));
            return;
        }

        if (inout.indexOf("${type}") == -1) {
            msg_critical(TR("Error"), QObject::tr("C++ 'inout' argument default passing must contains ${type}"));
            return;
        }

        if (opreturn.indexOf("${type}") == -1) {
            msg_critical(TR("Error"), QObject::tr("C++ 'return' argument default passing must contains ${type}"));
            return;
        }

        //types_table->update();
        relation_stereotypes_table->update(GenerationSettings::nrelattrstereotypes,
                                           GenerationSettings::relattr_stereotypes);
        class_stereotypes_table->update(GenerationSettings::nclassstereotypes,
                                        GenerationSettings::class_stereotypes);
        cpp_include_table->update();
        java_import_table->update();
        python_import_table->update();
        idl_include_table->update();

        GenerationSettings::cpp_enum_in = enum_in;
        GenerationSettings::cpp_enum_out = enum_out;
        GenerationSettings::cpp_enum_inout = enum_inout;
        GenerationSettings::cpp_enum_return = enum_return;

        GenerationSettings::cpp_in = in;
        GenerationSettings::cpp_out = out;
        GenerationSettings::cpp_inout = inout;
        GenerationSettings::cpp_return = opreturn;

        GenerationSettings::cpp_h_extension = edcpp_h_extension->currentText().trimmed();
        GenerationSettings::cpp_src_extension = edcpp_src_extension->currentText().trimmed();
        GenerationSettings::java_extension = edjava_extension->currentText().trimmed();
        GenerationSettings::php_extension = edphp_extension->currentText().trimmed();
        GenerationSettings::python_extension = edpython_extension->currentText().trimmed();
        GenerationSettings::idl_extension = edidl_extension->currentText().trimmed();

        GenerationSettings::cpp_h_content = edcpp_h_content->text();
        GenerationSettings::cpp_src_content = edcpp_src_content->text();
        GenerationSettings::java_src_content = edjava_src_content->text();
        GenerationSettings::php_src_content = edphp_src_content->text();
        GenerationSettings::python_src_content = edpython_src_content->text();
        GenerationSettings::idl_src_content = edidl_src_content->text();

        switch (cpp_include_with_path_cb->currentIndex()) {
        case 0:
            GenerationSettings::cpp_include_with_path = FALSE;
            GenerationSettings::cpp_relative_path = FALSE;
            GenerationSettings::cpp_root_relative_path = FALSE;
            break;

        case 1:
            GenerationSettings::cpp_include_with_path = TRUE;
            GenerationSettings::cpp_relative_path = FALSE;
            GenerationSettings::cpp_root_relative_path = FALSE;
            break;

        case 2:
            GenerationSettings::cpp_include_with_path = TRUE;
            GenerationSettings::cpp_relative_path = TRUE;
            GenerationSettings::cpp_root_relative_path = FALSE;
            break;

        default:
            GenerationSettings::cpp_include_with_path = TRUE;
            GenerationSettings::cpp_relative_path = FALSE;
            GenerationSettings::cpp_root_relative_path = TRUE;
        }

        GenerationSettings::cpp_force_namespace_gen =
                cpp_force_namespace_gen_cb->isChecked();

        GenerationSettings::cpp_inline_force_incl_in_h =
                cpp_inline_force_incl_in_h_cb->isChecked();

        GenerationSettings::cpp_javadoc_comment = cpp_javadoc_cb->isChecked();

        int i;

        GenerationSettings::cpp_class_decl = edcpp_class_decl->text();
        GenerationSettings::cpp_external_class_decl = edcpp_external_class_decl->text();
        GenerationSettings::cpp_struct_decl = edcpp_struct_decl->text();
        GenerationSettings::cpp_typedef_decl = edcpp_typedef_decl->text();
        GenerationSettings::cpp_union_decl = edcpp_union_decl->text();
        GenerationSettings::cpp_enum_decl = edcpp_enum_decl->text();

        for (i = 0; i != 3; i += 1)
            GenerationSettings::cpp_attr_decl[i] = edcpp_attr_decl[i]->text();

        GenerationSettings::cpp_enum_item_decl = edcpp_enum_item_decl->text();
        GenerationSettings::cpp_oper_decl = edcpp_oper_decl->text();
        GenerationSettings::cpp_oper_def = edcpp_oper_def->text();
        GenerationSettings::cpp_force_throw = cpp_force_throw_cb->isChecked();
        GenerationSettings::cpp_indent_visibility = get_indent(indentvisi_cb);

        GenerationSettings::java_class_decl = edjava_class_decl->text();
        GenerationSettings::java_external_class_decl = edjava_external_class_decl->text();
        GenerationSettings::java_interface_decl = edjava_interface_decl->text();
        GenerationSettings::java_enum_decl = edjava_enum_decl->text();
        GenerationSettings::java_enum_pattern_decl = edjava_enum_pattern_decl->text();
        GenerationSettings::java_enum_item_decl = edjava_enum_item_decl->text();
        GenerationSettings::java_enum_pattern_item_decl = edjava_enum_pattern_item_decl->text();
        GenerationSettings::java_enum_pattern_item_case = edjava_enum_pattern_item_case->text();

        for (i = 0; i != 3; i += 1)
            GenerationSettings::java_attr_decl[i] = edjava_attr_decl[i]->text();

        GenerationSettings::java_oper_def = edjava_oper_def->text();
        GenerationSettings::java_javadoc_comment = java_javadoc_cb->isChecked();
        GenerationSettings::java_force_package_gen = java_force_package_gen_cb->isChecked();

        GenerationSettings::php_class_decl = edphp_class_decl->text();
        GenerationSettings::php_external_class_decl = edphp_external_class_decl->text();
        GenerationSettings::php_interface_decl = edphp_interface_decl->text();
        GenerationSettings::php_enum_decl = edphp_enum_decl->text();
        GenerationSettings::php_enum_item_decl = edphp_enum_item_decl->text();
        GenerationSettings::php_attr_decl = edphp_attr_decl->text();
        GenerationSettings::php_oper_def = edphp_oper_def->text();
        GenerationSettings::php_javadoc_comment = php_javadoc_cb->isChecked();

        switch (php_require_with_path_cb->currentIndex()) {
        case 0:
            GenerationSettings::php_req_with_path = FALSE;
            GenerationSettings::php_relative_path = FALSE;
            GenerationSettings::php_root_relative_path = FALSE;
            break;

        case 1:
            GenerationSettings::php_req_with_path = TRUE;
            GenerationSettings::php_relative_path = FALSE;
            GenerationSettings::php_root_relative_path = FALSE;
            break;

        case 2:
            GenerationSettings::php_req_with_path = TRUE;
            GenerationSettings::php_relative_path = TRUE;
            GenerationSettings::php_root_relative_path = FALSE;
            break;

        default:
            GenerationSettings::php_req_with_path = TRUE;
            GenerationSettings::php_relative_path = FALSE;
            GenerationSettings::php_root_relative_path = TRUE;
        }

        GenerationSettings::php_force_namespace_gen =
                php_force_namespace_gen_cb->isChecked();

        GenerationSettings::python_indent_step = get_indent(indentstep_cb);
        GenerationSettings::python_2_2 = python_2_2_cb->isChecked();
        GenerationSettings::python_3_operation = python_3_operation_cb->isChecked();
        GenerationSettings::python_class_decl = edpython_class_decl->text();
        GenerationSettings::python_external_class_decl = edpython_external_class_decl->text();
        GenerationSettings::python_enum_decl = edpython_enum_decl->text();
        GenerationSettings::python_enum_item_decl = edpython_enum_item_decl->text();
        GenerationSettings::python_attr_decl[0] = edpython_attr_decl[0]->text();
        GenerationSettings::python_attr_decl[1] = edpython_attr_decl[1]->text();
        GenerationSettings::python_oper_def = edpython_oper_def->text();
        GenerationSettings::python_initoper_def = edpython_initoper_def->text();

        GenerationSettings::idl_interface_decl = edidl_interface_decl->text();
        GenerationSettings::idl_valuetype_decl = edidl_valuetype_decl->text();
        GenerationSettings::idl_struct_decl = edidl_struct_decl->text();
        GenerationSettings::idl_union_decl = edidl_union_decl->text();
        GenerationSettings::idl_enum_decl = edidl_enum_decl->text();
        GenerationSettings::idl_exception_decl = edidl_exception_decl->text();
        GenerationSettings::idl_typedef_decl = edidl_typedef_decl->text();
        GenerationSettings::idl_external_class_decl = edidl_external_class_decl->text();

        for (i = 0; i != 3; i += 1) {
            GenerationSettings::idl_attr_decl[i] = edidl_attr_decl[i]->text();
            GenerationSettings::idl_valuetype_attr_decl[i] = edidl_valuetype_attr_decl[i]->text();
            GenerationSettings::idl_const_decl[i] = edidl_const_decl[i]->text();
            GenerationSettings::idl_union_item_decl[i] = edidl_union_item_decl[i]->text();
        }

        GenerationSettings::idl_enum_item_decl = edidl_enum_item_decl->text();
        GenerationSettings::idl_oper_decl = edidl_oper_decl->text();

        int j;

        for (i = 0; i != 2; i += 1)
            for (j = 0; j != 3; j += 1)
                GenerationSettings::cpp_rel_decl[i][j] =
                        edcpp_rel_decl[i][j]->text();

        for (i = 0; i != 3; i += 1)
            GenerationSettings::java_rel_decl[i] =
                    edjava_rel_decl[i]->text();

        GenerationSettings::php_rel_decl = edphp_rel_decl->text();

        for (i = 0; i != 3; i += 1) {
            GenerationSettings::idl_rel_decl[i] =
                    edidl_rel_decl[i]->text();
            GenerationSettings::idl_valuetype_rel_decl[i] =
                    edidl_valuetype_rel_decl[i]->text();
            GenerationSettings::idl_union_rel_decl[i] =
                    edidl_union_rel_decl[i]->text();
        }

        for (i = 0; i != 2; i += 1)
            for (j = 0; j != 2; j += 1)
                GenerationSettings::python_rel_decl[i][j] =
                        edpython_rel_decl[i][j]->text();

        //

        GenerationSettings::cpp_get_visibility = cpp_get_visibility.value();
        GenerationSettings::cpp_get_name = edcpp_get_name->text();
        GenerationSettings::cpp_get_inline = cpp_get_inline_cb->isChecked();
        GenerationSettings::cpp_get_const = cpp_get_const_cb->isChecked();
        GenerationSettings::cpp_get_value_const = cpp_get_value_const_cb->isChecked();
        GenerationSettings::cpp_set_visibility = cpp_set_visibility.value();
        GenerationSettings::cpp_set_name = edcpp_set_name->text();
        GenerationSettings::cpp_set_inline = cpp_set_inline_cb->isChecked();
        GenerationSettings::cpp_set_param_const = cpp_set_param_const_cb->isChecked();
        GenerationSettings::cpp_set_param_ref = cpp_set_param_ref_cb->isChecked();

        GenerationSettings::noncpp_get_visibility = java_get_visibility.value();
        GenerationSettings::java_get_name = edjava_get_name->text();
        GenerationSettings::java_get_final = java_get_final_cb->isChecked();
        GenerationSettings::noncpp_set_visibility = java_set_visibility.value();
        GenerationSettings::java_set_name = edjava_set_name->text();
        GenerationSettings::java_set_final = java_set_final_cb->isChecked();
        GenerationSettings::java_set_param_final = java_set_param_final_cb->isChecked();

        GenerationSettings::php_get_name = edphp_get_name->text();
        GenerationSettings::php_get_final = php_get_final_cb->isChecked();
        GenerationSettings::php_set_name = edphp_set_name->text();
        GenerationSettings::php_set_final = php_set_final_cb->isChecked();

        GenerationSettings::python_get_name = edpython_get_name->text();
        GenerationSettings::python_set_name = edpython_set_name->text();

        GenerationSettings::idl_get_name = edidl_get_name->text();
        GenerationSettings::idl_set_name = edidl_set_name->text();
        GenerationSettings::idl_set_oneway = idl_set_oneway_cb->isChecked();

        //

        GenerationSettings::umltypes.clear();

        for (i = 0; i != GenerationSettings::nbuiltins; i += 1)
            GenerationSettings::umltypes.append(GenerationSettings::builtins[i].uml);

        //

        GenerationSettings::artifact_default_description = edartifact_default_description->text();
        GenerationSettings::class_default_description = edclass_default_description->text();
        GenerationSettings::operation_default_description = edoperation_default_description->text();
        GenerationSettings::attribute_default_description = edattribute_default_description->text();
        GenerationSettings::relation_default_description = edrelation_default_description->text();

        //

        if (uml_follow_cpp_get_name->isChecked())
            GenerationSettings::uml_get_name = CppView;
        else if (uml_follow_java_get_name->isChecked())
            GenerationSettings::uml_get_name = JavaView;
        else if (uml_follow_php_get_name->isChecked())
            GenerationSettings::uml_get_name = PhpView;
        else if (uml_follow_python_get_name->isChecked())
            GenerationSettings::uml_get_name = PythonView;
        else if (uml_follow_idl_get_name->isChecked())
            GenerationSettings::uml_get_name = IdlView;
        else
            GenerationSettings::uml_get_name = UmlView;

        if (uml_follow_cpp_set_name->isChecked())
            GenerationSettings::uml_set_name = CppView;
        else if (uml_follow_java_set_name->isChecked())
            GenerationSettings::uml_set_name = JavaView;
        else if (uml_follow_php_set_name->isChecked())
            GenerationSettings::uml_set_name = PhpView;
        else if (uml_follow_python_set_name->isChecked())
            GenerationSettings::uml_set_name = PythonView;
        else if (uml_follow_idl_set_name->isChecked())
            GenerationSettings::uml_set_name = IdlView;
        else
            GenerationSettings::uml_set_name = UmlView;

        //

        GenerationSettings::cpp_root_dir = add_last_slash(edcpproot->text());
        GenerationSettings::java_root_dir = add_last_slash(edjavaroot->text());
        GenerationSettings::php_root_dir = add_last_slash(edphproot->text());
        GenerationSettings::python_root_dir = add_last_slash(edpythonroot->text());
        GenerationSettings::idl_root_dir = add_last_slash(edidlroot->text());

        //

        QDialog::accept();
    }
}

void GenerationSettingsDialog::reject()
{
    builtinTable->RollBack();
    QDialog::reject();
}

void GenerationSettingsDialog::cpproot_browse()
{
    QString dir =
            QFileDialog::getExistingDirectory( this, QObject::tr("C++ root directory"), edcpproot->text(), 0);

    if (! dir.isNull()) {
        edcpproot->setText(dir);
        cpprelbutton->setText(Relative);
    }
}

void GenerationSettingsDialog::javaroot_browse()
{
    QString dir =
            QFileDialog::getExistingDirectory(this, QObject::tr("Java root directory"),edjavaroot->text(), 0);

    if (! dir.isNull()) {
        edjavaroot->setText(dir);
        javarelbutton->setText(Relative);
    }
}

void GenerationSettingsDialog::phproot_browse()
{
    QString dir =
            QFileDialog::getExistingDirectory(this, QObject::tr("Php root directory"), edphproot->text(), 0);

    if (! dir.isNull()) {
        edphproot->setText(dir);
        phprelbutton->setText(Relative);
    }
}

void GenerationSettingsDialog::pythonroot_browse()
{
    QString dir =
            QFileDialog::getExistingDirectory(this,  QObject::tr("Python root directory"), edpythonroot->text(), 0);

    if (! dir.isNull()) {
        edpythonroot->setText(dir);
        pythonrelbutton->setText(Relative);
    }
}

void GenerationSettingsDialog::idlroot_browse()
{
    QString dir =
            QFileDialog::getExistingDirectory(this, QObject::tr("Idl root directory"), edidlroot->text(), 0);

    if (! dir.isNull()) {
        edidlroot->setText(dir);
        idlrelbutton->setText(Relative);
    }
}

void GenerationSettingsDialog::relative(LineEdit * ed, QPushButton * button)
{
    QString root = BrowserView::get_dir().absolutePath();
    const QString s = ed->text();

    if (root.at(root.length() - 1) != QChar('/'))
        root += '/';

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

void GenerationSettingsDialog::cpp_relative()
{
    relative(edcpproot, cpprelbutton);
}

void GenerationSettingsDialog::java_relative()
{
    relative(edjavaroot, javarelbutton);
}

void GenerationSettingsDialog::php_relative()
{
    relative(edphproot, phprelbutton);
}

void GenerationSettingsDialog::python_relative()
{
    relative(edpythonroot, pythonrelbutton);
}

void GenerationSettingsDialog::idl_relative()
{
    relative(edidlroot, idlrelbutton);
}

//

void GenerationSettingsDialog::java_get_visi_changed(int)
{
    php_get_visibility.follow(java_get_visibility);
    python_get_visibility.follow(java_get_visibility);
}

void GenerationSettingsDialog::java_set_visi_changed(int)
{
    php_set_visibility.follow(java_set_visibility);
    python_set_visibility.follow(java_set_visibility);
}

void GenerationSettingsDialog::php_get_visi_changed(int)
{
    java_get_visibility.follow(php_get_visibility);
    python_get_visibility.follow(php_get_visibility);
}

void GenerationSettingsDialog::php_set_visi_changed(int)
{
    java_get_visibility.follow(php_set_visibility);
    python_set_visibility.follow(php_set_visibility);
}

// TypesTable
// todo need to implement this in new table
//bool TypesTable::check()
//{
//    int n = rowCount();
//    int index;

//    if (text(n - 1, 0).isEmpty())
//        n -= 1;

//    for (index = 0; index != n; index += 1) {
//        int col;

//        for (col = 0; col != 4; col += 1) {
//            if (text(index, col).trimmed().isEmpty()) {
//                char n[16];

//                sprintf(n, "%d", index + 1);
//                msg_critical(TR("Error"),
//                             QObject::tr("row %1 : ", n) +
//                             QObject::tr("%1 specification is mandatory", horizontalHeader()->label(col)));
//                return FALSE;
//            }
//        }

//        for (col = 4; col != 8; col += 1) {
//            if (text(index, col).indexOf("${type}") == -1) {
//                char n[16];

//                sprintf(n, "%d", index + 1);
//                msg_critical(TR("Error"),
//                             QObject::tr("row %1 : ", n) +
//                             QObject::tr("%1 '%2' argument default passing does not contains ${type}",
//                                (const char *) text(index, 0),
//                                (const char *) horizontalHeader()->label(col)));

//                return FALSE;
//            }
//        }
//    }

//    return TRUE;
//}

// StereotypesTable

StereotypesTable::StereotypesTable(QWidget * parent, int nst,
                                   Stereotype * st, bool php)
    : StringTable(nst + 1, (php) ? 7 : 6, parent, FALSE), with_php(php)
{
    QStringList headerLabels;
    /*horizontalHeaderItem(0)->setText("Uml");
    horizontalHeaderItem(1)->setText("C++");
    horizontalHeaderItem(2)->setText("Java");*/
    headerLabels<<"Uml"<<"C++"<<"Java";

    if (with_php) {
        /*horizontalHeaderItem(3)->setText("Php");
        horizontalHeaderItem(4)->setText("Python");
        horizontalHeaderItem(5)->setText("Idl");
        horizontalHeaderItem(6)->setText(TR("do"));*/
        headerLabels<<"Php"<<"Python"<<"Idl"<<TR("do");

        int index;

        for (index = 0; index < nst; index += 1) {
            Stereotype & s = st[index];

            setText(index, 0, s.uml);
            setText(index, 1, s.cpp);
            setText(index, 2, s.java);
            setText(index, 3, s.php);
            setText(index, 4, s.python);
            setText(index, 5, s.idl);
            setText(index, 6, QString());
        }

        init_row(index);

        for (index = 0; index != 6; index += 1)
        {
            //setColumnStretchable(index, TRUE);
            horizontalHeader()->setSectionResizeMode(index, QHeaderView::Stretch);
        }

        adjustColumn(6);
        //setColumnStretchable(6, FALSE);
        horizontalHeader()->setSectionResizeMode(index, QHeaderView::Fixed);
    }
    else {
        /*horizontalHeaderItem(3)->setText("Python");
        horizontalHeaderItem(4)->setText("Idl");
        horizontalHeaderItem(5)->setText(TR("do"));*/
        headerLabels<<"Python"<<"Idl"<<TR("do");
        int index;

        for (index = 0; index < nst; index += 1) {
            Stereotype & s = st[index];

            setText(index, 0, s.uml);
            setText(index, 1, s.cpp);
            setText(index, 2, s.java);
            setText(index, 3, s.python);
            setText(index, 4, s.idl);
            setText(index, 5, QString());
        }

        init_row(index);

        for (index = 0; index != 5; index += 1)
        {
            //setColumnStretchable(index, TRUE);
            horizontalHeader()->setSectionResizeMode(index, QHeaderView::Stretch);
        }

        adjustColumn(5);
        //setColumnStretchable(5, FALSE);
        horizontalHeader()->setSectionResizeMode(5, QHeaderView::Fixed);
    }
    setHorizontalHeaderLabels( headerLabels);
}

void StereotypesTable::init_row(int index)
{
    setText(index, 0, QString());
    setText(index, 1, QString());
    setText(index, 2, QString());
    setText(index, 3, QString());
    setText(index, 4, QString());
    setText(index, 5, QString());

    if (with_php)
        setText(index, 6, QString());
}

void StereotypesTable::update(int & nst, Stereotype *& st)
{
    forceUpdateCells();
    int n = rowCount();
    int index;

    if (/*text(n - 1, 0)*/text(n-1,0).isEmpty())
        n -= 1;

    delete [] st;
    nst = n;
    st = new Stereotype[n];

    if (with_php) {
        for (index = 0; index != n; index += 1) {
            Stereotype & s = st[index];

            s.uml = text(index, 0).trimmed();
            s.cpp = text(index, 1).trimmed();
            s.java = text(index, 2).trimmed();
            s.php = text(index, 3).trimmed();
            s.python = text(index, 4).trimmed();
            s.idl = text(index, 5).trimmed();
        }
    }
    else {
        for (index = 0; index != n; index += 1) {
            Stereotype & s = st[index];

            s.uml = text(index, 0).trimmed();
            s.cpp = text(index, 1).trimmed();
            s.java = text(index, 2).trimmed();
            s.python = text(index, 3).trimmed();
            s.idl = text(index, 4).trimmed();
        }
    }
}

// IncludeTable

IncludeTable::IncludeTable(QWidget * parent, IncludesSpec & spc,
                           const char * title, const char * df)
    : StringTable(spc.types.count() + 1, 3, parent, FALSE),
      spec(spc), dflt(df)
{
    QStringList headerLabels;
    headerLabels<<TR("External type")<<title<<TR("do");
    setHorizontalHeaderLabels(headerLabels);
    int index;
    int sup = spc.types.count();
    QStringList::Iterator it_type = spc.types.begin();
    QStringList::Iterator it_incl = spc.includes.begin();
    m_delegate = new TableWidgetItemDelegate(this, true);
    setItemDelegateForColumn(1,m_delegate);
    for (index = 0; index < sup; index += 1, it_type++, it_incl++) {
        setText(index, 0, *it_type);
        setItem(index, 1, new MLinesItem(this, *it_incl));
        setText(index, 2, QString());
        verticalHeader()->setSectionResizeMode(index, QHeaderView::Stretch);
        //adjustRow(index);
    }

    setText(index, 0, QString());
    setItem(index, 1, new MLinesItem(this, dflt));
    setText(index, 2, QString());
    verticalHeader()->setSectionResizeMode(index, QHeaderView::Stretch);

    adjustColumn(0);
    //setColumnStretchable(1, TRUE);
    horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    adjustColumn(2);
    //setColumnStretchable(2, FALSE);
    horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);

    connect(this, SIGNAL(pressed(QModelIndex)),
            this, SLOT(button_pressed(QModelIndex)));
    connect(this, SIGNAL(cellChanged(int, int)),
            this, SLOT(value_changed(int, int)));
}

void IncludeTable::init_row(int index)
{
    setText(index, 0, QString());
    setItem(index, 1, new MLinesItem(this, QString()));
    setText(index, 2, QString());
    verticalHeader()->setSectionResizeMode(index, QHeaderView::Stretch);
}

void IncludeTable::update()
{
    forceUpdateCells();
    int n = rowCount();
    int index;

    spec.types.clear();
    spec.includes.clear();

    for (index = 0; index != n; index += 1) {
        QString t = text(index, 0).trimmed();

        if (! t.isEmpty()) {
            spec.types.append(t);
            spec.includes.append(text(index, 1));
        }
    }
}

