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





#include <qlayout.h>
#include <gridbox.h>
#include <vvbox.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qtextedit.h>
//Added by qt3to4:
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "RevSettingsDialog.h"
#include "HelpRegexpDialog.h"
#include "GenerationSettingsDialog.h"
#include "DialogUtil.h"
#include "UmlDesktop.h"
#include "translate.h"
#include "hhbox.h"


QSize RevSettingsDialog::previous_size;

RevSettingsDialog::RevSettingsDialog()
    : QDialog(0/*, "Reverse/Roundtrip Settings dialog", TRUE*/)
{
    setWindowTitle(tr("Reverse/Roundtrip Settings dialog"));

    QVBoxLayout * vbox = new QVBoxLayout(this);

    vbox->setMargin(5);

    GridBox * grid = new GridBox(3, this);
    HHBox * htab;

    vbox->addWidget(grid);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(tr("To specify through regular expression the directories\n"
                  "and/or files to bypass during reverse and roundtrip"), grid));

    SmallPushButton * help;
    grid->addWidget(help = new SmallPushButton(tr("Help regexp"), grid));

    connect(help, SIGNAL(clicked()), this, SLOT(show_regexp_help()));

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    grid->addWidget(new QLabel(tr("C++ directory : "), grid));
    grid->addWidget(cpp_dir = new LineEdit(grid));
    cpp_dir->setText(GenerationSettings::cpp_dir_filter.regexp);
    grid->addWidget(cpp_dir_case_sensitive = new QCheckBox(tr("case sensitive"), grid));

    if (GenerationSettings::cpp_dir_filter.case_sensitive)
        cpp_dir_case_sensitive->setChecked(TRUE);

    grid->addWidget(new QLabel(tr("C++ file : "), grid));
    grid->addWidget(cpp_file = new LineEdit(grid));
    cpp_file->setText(GenerationSettings::cpp_file_filter.regexp);
    grid->addWidget(cpp_file_case_sensitive = new QCheckBox(tr("case sensitive"), grid));

    if (GenerationSettings::cpp_file_filter.case_sensitive)
        cpp_file_case_sensitive->setChecked(TRUE);

    grid->addWidget(new QLabel(grid));
    grid->addWidget(htab = new HHBox(grid));
    grid->addWidget(new QLabel(grid));

    htab->setMargin(3);
    htab->setStretchFactor(new QLabel(tr("generated/reversed \nheader file extension : "), htab), 0);
    edcpp_h_extension = new QComboBox(htab);
    edcpp_h_extension->setEditable(true);
    htab->setStretchFactor(edcpp_h_extension, 100);
    edcpp_h_extension->addItem(GenerationSettings::cpp_h_extension);
    edcpp_h_extension->setCurrentIndex(0);
    edcpp_h_extension->addItem("h");
    edcpp_h_extension->addItem("hh");

    htab->setStretchFactor(new QLabel(tr("    generated/reversed \n    source file extension : "), htab), 0);
    edcpp_src_extension = new QComboBox(htab);
    edcpp_src_extension->setEditable(true);
    htab->setStretchFactor(edcpp_src_extension, 100);
    edcpp_src_extension->addItem(GenerationSettings::cpp_src_extension);
    edcpp_src_extension->setCurrentIndex(0);
    edcpp_src_extension->addItem("cpp");
    edcpp_src_extension->addItem("cc");

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    grid->addWidget(new QLabel(tr("Java directory : "), grid));
    grid->addWidget(java_dir = new LineEdit(grid));
    java_dir->setText(GenerationSettings::java_dir_filter.regexp);
    grid->addWidget(java_dir_case_sensitive = new QCheckBox(tr("case sensitive"), grid));

    if (GenerationSettings::java_dir_filter.case_sensitive)
        java_dir_case_sensitive->setChecked(TRUE);

    grid->addWidget(new QLabel(tr("Java file : "), grid));
    grid->addWidget(java_file = new LineEdit(grid));
    java_file->setText(GenerationSettings::java_file_filter.regexp);
    grid->addWidget(java_file_case_sensitive = new QCheckBox(tr("case sensitive"), grid));

    if (GenerationSettings::java_file_filter.case_sensitive)
        java_file_case_sensitive->setChecked(TRUE);

    grid->addWidget(new QLabel(grid));
    grid->addWidget(htab = new HHBox(grid));
    grid->addWidget(new QLabel(grid));

    htab->setMargin(3);
    htab->setStretchFactor(new QLabel(tr("generated/reversed file extension : "), htab), 0);
    edjava_extension = new QComboBox(htab);
    edjava_extension->setEditable(true);
    htab->setStretchFactor(edjava_extension, 100);
    edjava_extension->addItem(GenerationSettings::java_extension);
    edjava_extension->setCurrentIndex(0);
    edjava_extension->addItem("java");

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    grid->addWidget(new QLabel(tr("Php directory : "), grid));
    grid->addWidget(php_dir = new LineEdit(grid));
    php_dir->setText(GenerationSettings::php_dir_filter.regexp);
    grid->addWidget(php_dir_case_sensitive = new QCheckBox(tr("case sensitive"), grid));

    if (GenerationSettings::php_dir_filter.case_sensitive)
        php_dir_case_sensitive->setChecked(TRUE);

    grid->addWidget(new QLabel(tr("Php file : "), grid));
    grid->addWidget(php_file = new LineEdit(grid));
    php_file->setText(GenerationSettings::php_file_filter.regexp);
    grid->addWidget(php_file_case_sensitive = new QCheckBox(tr("case sensitive"), grid));

    if (GenerationSettings::php_file_filter.case_sensitive)
        php_file_case_sensitive->setChecked(TRUE);

    grid->addWidget(new QLabel(grid));
    grid->addWidget(htab = new HHBox(grid));
    grid->addWidget(new QLabel(grid));

    htab->setMargin(3);
    htab->setStretchFactor(new QLabel(tr("generated / reversed file extension : "), htab), 0);
    edphp_extension = new QComboBox(htab);
    edphp_extension->setEditable(true);
    htab->setStretchFactor(edphp_extension, 100);
    edphp_extension->addItem(GenerationSettings::php_extension);
    edphp_extension->setCurrentIndex(0);
    edphp_extension->addItem("php");

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    QPushButton * accept = new QPushButton(tr("&OK"), this);
    QPushButton * cancel = new QPushButton(tr("&Cancel"), this);
    QSize bs(cancel->sizeHint());

    accept->setDefault(TRUE);
    accept->setFixedSize(bs);
    cancel->setFixedSize(bs);

    QHBoxLayout * hbox = new QHBoxLayout();
    vbox->addLayout(hbox);

    hbox->addWidget(accept);
    hbox->addWidget(cancel);

    connect(accept, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

void RevSettingsDialog::polish()
{
    QDialog::ensurePolished();
    UmlDesktop::limitsize_center(this, previous_size, 0.8, 0.8);
}

RevSettingsDialog::~RevSettingsDialog()
{
    previous_size = size();
}

void RevSettingsDialog::accept()
{
    GenerationSettings::cpp_dir_filter.regexp = cpp_dir->text();
    GenerationSettings::cpp_dir_filter.case_sensitive = cpp_dir_case_sensitive->isChecked();
    GenerationSettings::cpp_file_filter.regexp = cpp_file->text();
    GenerationSettings::cpp_file_filter.case_sensitive = cpp_file_case_sensitive->isChecked();
    GenerationSettings::cpp_h_extension = edcpp_h_extension->currentText().trimmed();
    GenerationSettings::cpp_src_extension = edcpp_src_extension->currentText().trimmed();

    GenerationSettings::java_dir_filter.regexp = java_dir->text();
    GenerationSettings::java_dir_filter.case_sensitive = java_dir_case_sensitive->isChecked();
    GenerationSettings::java_file_filter.regexp = java_file->text();
    GenerationSettings::java_file_filter.case_sensitive = java_file_case_sensitive->isChecked();
    GenerationSettings::java_extension = edjava_extension->currentText().trimmed();

    GenerationSettings::php_dir_filter.regexp = php_dir->text();
    GenerationSettings::php_dir_filter.case_sensitive = php_dir_case_sensitive->isChecked();
    GenerationSettings::php_file_filter.regexp = php_file->text();
    GenerationSettings::php_file_filter.case_sensitive = php_file_case_sensitive->isChecked();
    GenerationSettings::php_extension = edphp_extension->currentText().trimmed();

    QDialog::accept();
}

void RevSettingsDialog::show_regexp_help()
{
    HelpRegexpDialog d;

    d.raise();
    d.exec();
}

//

QSize HelpRegexpDialog::previous_size;

HelpRegexpDialog::HelpRegexpDialog()
    : QDialog(0/*, "Help, regular expression", TRUE*/)
{
    setWindowTitle(tr("Help regular expression"));

    QVBoxLayout * vbox = new QVBoxLayout(this);

    QTextEdit * txt = new QTextEdit(this);

    txt->setText("<p>Extracted from the QT documentation :</p><hr>"
                 "<ul>"
                 "<li><b>c</b> matches the character <i>c</i></li>"
                 "<li><b>?</b> matches any character </li>"
                 "<li><b>*</b> matches any sequence of characters</li>"
                 "<li><b>[]</b> matches a defined set of characters.</li>"
                 "</ul>"
                 "<p>A character set matches a defined set of characters. "
                 "For example, <b>[BSD]</b> matches any of <i>B</i>, <i>D</i> and <i>S</i>. "
                 "Within a character set, the special characters <i>*</i>, <i>?</i>, and <i>[</i> loose their special meanings. "
                 "The following special characters apply:</p>"
                 "<ul>"
                 "<li><b>^</b> When placed first in the list, changes the character set to match any character not in the list. To include the character <i>^</i> itself in the set, escape it or place it anywhere but first. </li>"
                 "<li><b>-</b> Defines a range of characters. To include the character <i>-</i> itself in the set, escape it or place it last. </li>"
                 "<li><b>]</b> Ends the character set definition. To include the character ']' itself in the set, escape it or place it first (but after the negation operator '^', if present)</li>"
                 "</ul>"
                 "<p>Thus, <i>[a-zA-Z0-9.]</i> matches upper and lower case ASCII letters, digits and dot.</p>");
    vbox->addWidget(txt);

    QHBoxLayout * hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);

    QPushButton * close = new QPushButton(tr("Close"), this);

    close->setDefault(TRUE);

    hbox->addWidget(close);

    connect(close, SIGNAL(clicked()), this, SLOT(accept()));

    // not done in polish else the initial size is too small
    UmlDesktop::setsize_center(this, previous_size, 0.5, 0.5);
}

HelpRegexpDialog::~HelpRegexpDialog()
{
    previous_size = size();
}
