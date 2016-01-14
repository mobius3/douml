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
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "StereotypeDialog.h"
#include "DialogUtil.h"
#include "UmlDesktop.h"
#include "translate.h"

QSize StereotypeDialog::previous_size;

StereotypeDialog::StereotypeDialog(const QStringList & defaults,
                                   QString & st, QString & la,
                                   QString cap, QString lbl)
    : QDialog(0/*, cap, TRUE*/), ste(st), lab(la)
{
    setWindowTitle(cap);

    if (! ste.isEmpty())
        // removes << and >>
        ste = ste.mid(2, ste.length() - 4);

    QVBoxLayout * vbox = new QVBoxLayout(this);
    QHBoxLayout * hbox;
    QLabel * label1;
    QLabel * label2;

    vbox->setMargin(5);

    vbox->addLayout(hbox = new QHBoxLayout());
    hbox->setMargin(5);
    hbox->addWidget(label1 = new QLabel(lbl, this));
    ed = new LineEdit(la, this);
    hbox->addWidget(ed);

    vbox->addLayout(hbox = new QHBoxLayout());
    hbox->setMargin(5);
    hbox->addWidget(label2 = new QLabel(tr("stereotype : "), this));
    cb = new QComboBox(this);
    cb->setEditable(true);
    cb->addItem(ste);
    cb->setCurrentIndex(0);
    cb->addItems(defaults);
    cb->setAutoCompletion(completion());
    hbox->addWidget(cb);

    QSizePolicy sp = cb->sizePolicy();

    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    cb->setSizePolicy(sp);

    same_width(label1, label2);

    vbox->addLayout(hbox = new QHBoxLayout());
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

StereotypeDialog::~StereotypeDialog()
{
    previous_size = size();
}

void StereotypeDialog::polish()
{
    QDialog::ensurePolished();
    UmlDesktop::limitsize_move(this, previous_size, 0.8, 0.8);
}

void StereotypeDialog::accept()
{
    ste = cb->currentText().trimmed();

    if (!ste.isEmpty())
        ste = QString("<<") + ste + ">>";

    lab = ed->text();

    QDialog::accept();
}
