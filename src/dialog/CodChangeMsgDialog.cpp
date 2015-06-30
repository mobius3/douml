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
#include <hhbox.h>
#include <qpushbutton.h>
#include <qcursor.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "CodChangeMsgDialog.h"
#include "ColMsg.h"
#include "CodMsgSupport.h"
#include "CodObjCanvas.h"
#include "BrowserClass.h"
#include "OperationData.h"
#include "UmlDesktop.h"
#include "DialogUtil.h"
#include "BrowserView.h"
#include "translate.h"
#include "menufactory.h"

QSize CodChangeMsgDialog::previous_size;

CodChangeMsgDialog::CodChangeMsgDialog(QWidget * parent, ColMsg * m)
    : QDialog(parent/*, "Communication message dialog", TRUE*/), msg(m)
{
    setWindowTitle(TR("Communicationg message dialog"));

    QVBoxLayout * vbox = new QVBoxLayout(this);
    QHBoxLayout * hbox;

    vbox->setMargin(5);

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);

    SmallPushButton * b = new SmallPushButton(TR("message :"), this);

    hbox->addWidget(b);
    connect(b, SIGNAL(clicked()), this, SLOT(menu_op()));

    edoper = new QComboBox(this);
    edoper->setEditable(true);
    edoper->setAutoCompletion(completion());

    if (msg->operation == 0)
        edoper->addItem(msg->explicit_operation);
    else
        edoper->addItem(msg->operation->definition(TRUE, FALSE));

    CodObjCanvas * from;
    CodObjCanvas * to;

    msg->in->get_from_to(from, to, msg->is_forward);

    // gets operations
    cl = to->get_class();

    if (cl != 0) {
        cl->get_opers(opers, list);
        edoper->addItems(list);

        if (!cl->is_writable())
            cl = 0;
    }

    edoper->setCurrentIndex(0);

    QSizePolicy sp = edoper->sizePolicy();

    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    edoper->setSizePolicy(sp);

    hbox->addWidget(edoper);

    // ok & cancel

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

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

void CodChangeMsgDialog::polish()
{
    QDialog::ensurePolished();
    UmlDesktop::limitsize_move(this, previous_size, 0.8, 0.8);
}

CodChangeMsgDialog::~CodChangeMsgDialog()
{
    previous_size = size();
}

void CodChangeMsgDialog::menu_op()
{
    QMenu m(0);

    MenuFactory::addItem(m, TR("Choose"), -1);
    m.addSeparator();

    int index = list.indexOf(edoper->currentText().trimmed());

    if (index != -1)
        MenuFactory::addItem(m, TR("Select in browser"), 0);

    BrowserNode * bn = BrowserView::selected_item();

    if ((bn != 0) &&
        (bn->get_type() == UmlOperation) &&
        !bn->deletedp() &&
        (opers.indexOf((OperationData *) bn->get_data()) != -1))
        MenuFactory::addItem(m, TR("Choose operation selected in browser"), 1);
    else
        bn = 0;

    if (cl != 0)
        MenuFactory::addItem(m, TR("Create operation and choose it"), 2);

    if ((index != -1) || (bn != 0) || (cl != 0)) {
        QAction* retAction = m.exec(QCursor::pos());
        if(retAction)
        {
        switch (retAction->data().toInt()) {
        case 0:
            opers[index]->get_browser_node()->select_in_browser();
            break;

        case 2:
            bn = cl->add_operation();

            if (bn == 0)
                return;

            bn->select_in_browser();

            // no break
        case 1: {
            OperationData * od = (OperationData *) bn->get_data();

            if ((index = opers.indexOf(od)) == -1) {
                index = opers.count();
                opers.append(od);

                QString s = od->definition(TRUE, FALSE);

                list.append(s);
                edoper->addItem(s);
            }
        }

        edoper->setCurrentIndex(index + 1);
        }
        }
    }
}

void CodChangeMsgDialog::accept()
{
    QString s = edoper->currentText().trimmed();

    if (s.isEmpty())
        return;

    int index = list.indexOf(s);

    if (index >= 0) {
        msg->operation = opers[index];
        msg->explicit_operation = QString();
    }
    else {
        msg->operation = 0;
        msg->explicit_operation = s;
    }

    QDialog::accept();
}
