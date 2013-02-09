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
#include <q3combobox.h>
#include <qpushbutton.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3HBoxLayout>

#include "ClassSettingsDialog.h"
#include "Settings.h"
#include "UmlDesktop.h"
#include "translate.h"


class ComboVisibility : public Q3ComboBox
{
public:
    ComboVisibility(QWidget * parent, UmlVisibility v, bool nodefault);
};

ComboVisibility::ComboVisibility(QWidget * parent, UmlVisibility v, bool nodefault)
    : Q3ComboBox(FALSE, parent)
{
    // the last value MUST be default
    for (int i = 0; i != (int) UmlDefaultVisibility; i += 1)
        insertItem(stringify((UmlVisibility) i));

    if (!nodefault)
        insertItem(stringify(UmlDefaultVisibility));

    setCurrentItem(v);
}

QSize ClassSettingsDialog::previous_size;

ClassSettingsDialog::ClassSettingsDialog(ClassSettings * se, bool nodefault)
    : QDialog(0, "Class Settings dialog", TRUE), settings(se)
{
    setCaption(TR("Class Settings dialog"));

    Q3VBoxLayout * vbox = new Q3VBoxLayout(this);
    Q3HBoxLayout * hbox;
    QString s;

    vbox->setMargin(5);

    hbox = new Q3HBoxLayout(vbox);
    hbox->setMargin(5);
    hbox->addWidget(new QLabel(TR("default attributes visibility : "), this), 1000);
    cbattribute = new ComboVisibility(this, settings->attribute_visibility, nodefault);
    hbox->addWidget(cbattribute);

    hbox = new Q3HBoxLayout(vbox);
    hbox->setMargin(5);
    hbox->addWidget(new QLabel(TR("default relations visibility : "), this), 1000);
    cbrelation = new ComboVisibility(this, settings->relation_visibility, nodefault);
    hbox->addWidget(cbrelation);

    hbox = new Q3HBoxLayout(vbox);
    hbox->setMargin(5);
    hbox->addWidget(new QLabel(TR("default operations visibility : "), this), 1000);
    cboperation = new ComboVisibility(this, settings->operation_visibility, nodefault);
    hbox->addWidget(cboperation);

    hbox = new Q3HBoxLayout(vbox);
    hbox->setMargin(5);
    QPushButton * accept = new QPushButton(TR("&OK"), this);
    QPushButton * cancel = new QPushButton(TR("&Cancel"), this);
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
    QDialog::polish();
    UmlDesktop::limitsize_move(this, previous_size, 0.8, 0.8);
}

ClassSettingsDialog::~ClassSettingsDialog()
{
    previous_size = size();
}

void ClassSettingsDialog::accept()
{
    settings->attribute_visibility = (UmlVisibility) cbattribute->currentItem();
    settings->relation_visibility = (UmlVisibility) cbrelation->currentItem();
    settings->operation_visibility = (UmlVisibility) cboperation->currentItem();

    QDialog::accept();
}
