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
#include <gridbox.h>
#include <qcursor.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "CodAddMsgDialog.h"
#include "ColDiagramView.h"
#include "CodMsgSupport.h"
#include "CodObjCanvas.h"
#include "ColMsg.h"
#include "BrowserClass.h"
#include "BrowserOperation.h"
#include "OperationData.h"
#include "DialogUtil.h"
#include "UmlDesktop.h"
#include "BrowserView.h"
#include "translate.h"
#include "menufactory.h"

QSize CodAddMsgDialog::previous_size;

CodAddMsgDialog::CodAddMsgDialog(CodObjCanvas * from, CodObjCanvas * to,
                                 CodMsgSupport * i, ColDiagramView * v,
                                 bool fo)
    : QDialog(0/*, "add msg dialog", TRUE*/), in(i), view(v), forward(fo)
{
    setWindowTitle(tr("Add message dialog"));

    QVBoxLayout * vbox = new QVBoxLayout(this);
    QHBoxLayout * hbox;

    vbox->setMargin(5);

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(10);
    QLabel * label1 = new QLabel(tr("Add message to %1").arg(to->get_full_name()), this);
    label1->setAlignment(Qt::AlignCenter);
    hbox->addWidget(label1);

    GridBox * grid = new GridBox(2, this);

    vbox->addWidget(grid);
    grid->addWidget(new QLabel(tr("rank : "), grid));
    grid->addWidget(cbrank = new QComboBox(grid));

    ColMsgList all_in;
    ColMsgList all_out;

    from->get_all_in_all_out(all_in, all_out);

    QStringList new_ones;
    foreach (ColMsg *m, all_out) {
        QString s = m->next_hierarchical_rank();

        if ((s.indexOf('.') != - 1) && (ColMsg::find(s, all_out) == 0)) {
            cbrank->addItem(QString::number(m->get_rank() + 1) + " : " + s);
            new_ones.append(s);
        }
    }

    foreach (ColMsg *m, all_in) {
        QString s = m->get_hierarchical_rank() + ".1";

        if ((ColMsg::find(s, all_out) == 0) && (new_ones.indexOf(s) == -1)) {
            cbrank->addItem(QString::number(m->get_rank() + 1) + " : " + s);
            new_ones.append(s);
        }
    }

    // add a the rank for a new toplevel link
    cbrank->addItem(QString::number(ColMsg::last_rank(view->get_msgs()) + 1)
                       + " : "
                       + QString::number(view->get_msgs().count() + 1));

    // the default new one follow the last input or output or view's last msg
    cbrank->setCurrentIndex((cbrank->count() == 1) ? 0 : cbrank->count() - 2);

    QSizePolicy sp = cbrank->sizePolicy();

    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    cbrank->setSizePolicy(sp);

    grid->addWidget(new QLabel("", grid));
    grid->addWidget(new QLabel("", grid));

    // the operations

    SmallPushButton * b;
    grid->addWidget(b = new SmallPushButton(tr("message :"), grid));

    connect(b, SIGNAL(clicked()), this, SLOT(menu_op()));

    grid->addWidget(edoper = new QComboBox(grid));
    edoper->setEditable(true);
    edoper->setAutoCompletion(completion());

    // gets operations
    cl = to->get_class();

    if (cl != 0) {
        cl->get_opers(opers, list);
        edoper->addItems(list);

        if (!cl->is_writable())
            cl = 0;
    }

    edoper->setSizePolicy(sp);

    grid->addWidget(new QLabel("", grid));
    grid->addWidget(new QLabel("", grid));

    // ok & cancel

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);
    QPushButton * ok = new QPushButton(tr("&OK"), this);
    QPushButton * cancel = new QPushButton(tr("&Cancel"), this);
    QSize bs(cancel->sizeHint());

    ok->setDefault(TRUE);
    ok->setFixedSize(bs);
    cancel->setFixedSize(bs);

    hbox->addWidget(ok);
    hbox->addWidget(cancel);

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

void CodAddMsgDialog::polish()
{
    QDialog::ensurePolished();
    UmlDesktop::limitsize_move(this, previous_size, 0.8, 0.8);
}

CodAddMsgDialog::~CodAddMsgDialog()
{
    previous_size = size();
}

void CodAddMsgDialog::menu_op()
{
    QMenu m(0);

    MenuFactory::addItem(m, tr("Choose"), -1);
    m.addSeparator();

    int index = list.indexOf(edoper->currentText().trimmed());

    if (index != -1)
        MenuFactory::addItem(m, tr("Select in browser"), 0);

    BrowserNode * bn = BrowserView::selected_item();

    if ((bn != 0) &&
        (bn->get_type() == UmlOperation) &&
        !bn->deletedp() &&
        (opers.indexOf((OperationData *) bn->get_data()) != -1))
        MenuFactory::addItem(m, tr("Choose operation selected in browser"), 1);
    else
        bn = 0;

    if (cl != 0)
        MenuFactory::addItem(m, tr("Create operation and choose it"), 2);

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

void CodAddMsgDialog::accept()
{
    QString s = edoper->currentText().trimmed();

    if (s.isEmpty())
        return;

    int index = list.indexOf(s);
    const OperationData * d;
    QString e;

    if (index >= 0)
        d = opers[index];
    else {
        d = 0;
        e = s;
    }

    s = cbrank->currentText();

    ColMsg::new_one(d, e, forward, s.mid(s.indexOf(':') + 2), in)
    ->place_in(view->get_msgs());

    view->update_msg_supports();

    QDialog::accept();
}
