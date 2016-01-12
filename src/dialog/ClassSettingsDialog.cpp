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
#include <qlabel.h>
#include <qcombobox.h>
#include <qpushbutton.h>
//Added by qt3to4:
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "ClassSettingsDialog.h"
#include "Settings.h"
#include "UmlDesktop.h"
#include "translate.h"


class ComboVisibility : public QComboBox
{
public:
    ComboVisibility(QWidget * parent, UmlVisibility v, bool nodefault);
};

ComboVisibility::ComboVisibility(QWidget * parent, UmlVisibility v, bool nodefault)
    : QComboBox(parent)
{
    setEditable(false);
    // the last value MUST be default
    for (int i = 0; i != (int) UmlDefaultVisibility; i += 1)
        addItem(stringify((UmlVisibility) i));

    if (!nodefault)
        addItem(stringify(UmlDefaultVisibility));

    setCurrentIndex(v);
}

QSize ClassSettingsDialog::previous_size;

ClassSettingsDialog::ClassSettingsDialog(ClassSettings * se, bool nodefault)
    : QDialog(0/*, "Class Settings dialog", TRUE*/), settings(se)
{
    setWindowTitle(tr("Class Settings dialog"));

    QVBoxLayout * vbox = new QVBoxLayout(this);
    QHBoxLayout * hbox;
    QString s;

    vbox->setMargin(5);

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);
    hbox->addWidget(new QLabel(tr("default attributes visibility : "), this), 1000);
    cbattribute = new ComboVisibility(this, settings->attribute_visibility, nodefault);
    hbox->addWidget(cbattribute);

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);
    hbox->addWidget(new QLabel(tr("default relations visibility : "), this), 1000);
    cbrelation = new ComboVisibility(this, settings->relation_visibility, nodefault);
    hbox->addWidget(cbrelation);

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);
    hbox->addWidget(new QLabel(tr("default operations visibility : "), this), 1000);
    cboperation = new ComboVisibility(this, settings->operation_visibility, nodefault);
    hbox->addWidget(cboperation);

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);
    QPushButton * accept = new QPushButton(tr("&OK"), this);
    QPushButton * cancel = new QPushButton(tr("&Cancel"), this);
    QSize bs(cancel->sizeHint());

    accept->setDefault(TRUE);
    accept->setFixedSize(bs);
    cancel->setFixedSize(bs);

    hbox->addWidget(accept);
    hbox->addWidget(cancel);

    connect(accept, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

void ClassSettingsDialog::polish()
{
    QDialog::ensurePolished();
    UmlDesktop::limitsize_move(this, previous_size, 0.8, 0.8);
}

ClassSettingsDialog::~ClassSettingsDialog()
{
    previous_size = size();
}

void ClassSettingsDialog::accept()
{
    settings->attribute_visibility = (UmlVisibility) cbattribute->currentIndex();
    settings->relation_visibility = (UmlVisibility) cbrelation->currentIndex();
    settings->operation_visibility = (UmlVisibility) cboperation->currentIndex();

    QDialog::accept();
}
