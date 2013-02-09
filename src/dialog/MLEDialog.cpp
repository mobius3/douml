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
#include <q3hbox.h>
#include <qlabel.h>
//Added by qt3to4:
#include <Q3VBoxLayout>

#include "MLEDialog.h"
#include "DialogUtil.h"
#include "translate.h"

MLEDialog::MLEDialog(QString t, bool buttons) : QDialog(0, "Uml", TRUE, 0)
{
    Q3VBoxLayout * vbox = new Q3VBoxLayout(this);

    e = new MultiLineEdit(this);
    vbox->addWidget(e);

    Q3HBox * hbox = new Q3HBox(this);

    vbox->addWidget(hbox);
    hbox->setMargin(5);

    if (buttons) {
        new QLabel(hbox);
        ok = new QPushButton(TR("OK"), hbox);
        new QLabel(hbox);
        cancel = new QPushButton(TR("Cancel"), hbox);
        new QLabel(hbox);

        connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
        connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
    }

    e->setText(t);
}

MLEDialog::~MLEDialog()
{
}

void MLEDialog::get(QString & t, const QPoint & p, QSize & sz)
{
    MLEDialog d(t, TRUE);

    d.move(p);

    if (sz.isValid())
        d.resize(sz);

    d.e->setFocus();

    if (d.exec() == QDialog::Accepted)
        t = d.e->text();

    sz = d.size();
}

QString MLEDialog::text()
{
    return e->text();
}

