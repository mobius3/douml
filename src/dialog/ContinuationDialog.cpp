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
#include <qpushbutton.h>
//Added by qt3to4:
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "ContinuationDialog.h"
#include "DialogUtil.h"
#include "UmlDesktop.h"
#include "translate.h"

QSize ContinuationDialog::previous_size;

ContinuationDialog::ContinuationDialog(QString & s)
    : QDialog(0/*, "continuation dialog", TRUE*/), name(s)
{
    setWindowTitle(tr("stereotype/continuation dialog"));

    QVBoxLayout * vbox = new QVBoxLayout(this);
    QHBoxLayout * hbox;
    QLabel * label;

    vbox->setMargin(5);

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);
    hbox->addWidget(label = new QLabel(tr("label : "), this));
    ed = new LineEdit(name, this);
    hbox->addWidget(ed);
    ed->setFocus();

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

void ContinuationDialog::polish()
{
    QDialog::ensurePolished();
    UmlDesktop::limitsize_move(this, previous_size, 0.8, 0.8);
}

ContinuationDialog::~ContinuationDialog()
{
    previous_size = size();
}

void ContinuationDialog::accept()
{
    name = ed->text();

    QDialog::accept();
}
