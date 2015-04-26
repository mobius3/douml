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
#include <qlayout.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "OperationListDialog.h"
#include "BrowserOperation.h"
#include "OperationData.h"
#include "UmlDesktop.h"
#include "translate.h"

QSize OperationListDialog::previous_size;

OperationListDialog::OperationListDialog(const char * m,
        QList<BrowserOperation *> & l)
    : QDialog(0)
{
    setWindowTitle(m);
    move(QCursor::pos());

    QVBoxLayout * vbox = new QVBoxLayout(this);
    QHBoxLayout * hbox;

    vbox->setMargin(5);

    cb = new QComboBox(this);
    vbox->addWidget(cb);

    foreach (BrowserOperation *oper, l) {
        QString s = ((BrowserNode *) oper->parent())->get_name() +
                    QString("::") + oper->get_data()->definition(TRUE, FALSE);

        if (((OperationData *) oper->get_data())->get_is_abstract())
            cb->addItem("[a] " + s);
        else
            cb->addItem(s);
    }

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);
    QPushButton * ok = new QPushButton(TR("&OK"), this);
    QPushButton * cancel = new QPushButton(TR("&Cancel"), this);
    QSize bs(cancel->sizeHint());

    ok->setDefault(TRUE);
    ok->setFixedSize(bs);
    cancel->setFixedSize(bs);

    hbox->addWidget(ok);
    hbox->addWidget(cancel);

    UmlDesktop::limitsize_center(this, previous_size, 0.8, 0.8);

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

OperationListDialog::~OperationListDialog()
{
    previous_size = size();
}

int OperationListDialog::choosen()
{
    return cb->currentIndex();
}
