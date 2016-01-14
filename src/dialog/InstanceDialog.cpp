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
#include <gridbox.h>
#include <qcursor.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "InstanceDialog.h"
#include "Instance.h"
#include "DialogUtil.h"
#include "UmlDesktop.h"
#include "BrowserView.h"
#include "translate.h"
#include "menufactory.h"

QSize InstanceDialog::previous_size;

InstanceDialog::InstanceDialog(Instance * i, QString w, UmlCode k)
    : QDialog(0/*, w + " instance dialog", TRUE*/),
      inst(i), what(w), kind(k)
{
    setWindowTitle((what + " instance dialog"));

    QVBoxLayout * vbox = new QVBoxLayout(this);

    vbox->setMargin(5);

    GridBox * grid = new GridBox(2, this);

    vbox->addWidget(grid);
    grid->addWidget(new QLabel(tr("name : "), grid));
    grid->addWidget(edname = new LineEdit(inst->get_name(), grid));
    edname->setFocus();

    grid->addWidget(new QLabel("", grid));
    grid->addWidget(new QLabel("", grid));

    SmallPushButton * b;
    grid->addWidget(b = new SmallPushButton((what) + " :", grid));

    connect(b, SIGNAL(clicked()), this, SLOT(menu_type()));

    grid->addWidget(edtype = new QComboBox(grid));
    inst->get_types(nodes);
    nodes.full_names(list);
    edtype->addItems(list);
    edtype->setCurrentIndex(nodes.indexOf(inst->get_type()));

    grid->addWidget(new QLabel("", grid));
    grid->addWidget(new QLabel("", grid));

    QHBoxLayout * hbox = new QHBoxLayout();
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

    open_dialog(this);
}

void InstanceDialog::polish()
{
    QDialog::ensurePolished();
    UmlDesktop::limitsize_move(this, previous_size, 0.8, 0.8);
}

InstanceDialog::~InstanceDialog()
{
    previous_size = size();
    close_dialog(this);
}

void InstanceDialog::menu_type()
{
    QMenu m(0);

    MenuFactory::addItem(m, tr("Choose"), -1);
    m.addSeparator();

    int index = list.indexOf(edtype->currentText().trimmed());

    if (index != -1)
        MenuFactory::addItem(m, tr("Select in browser"), 0);

    BrowserNode * bn = BrowserView::selected_item();

    if ((bn != 0) &&
        (bn->get_type() == kind) && !bn->deletedp())
        MenuFactory::addItem(m, tr("Choose ") + what + tr(" selected in browser"), 1);
    else
        bn = 0;

    bool new_available = inst->new_type_available();

    if (new_available)
        MenuFactory::addItem(m, tr("Create ") + what + tr(" and choose it"), 2);

    if (new_available || (index != -1) || (bn != 0)) {
        QAction* retAction = m.exec(QCursor::pos());
        if(retAction)
        {
        switch (retAction->data().toInt()) {
        case 0:
            nodes.at(index)->select_in_browser();
            break;

        case 2:
            bn = inst->new_type();

            if (bn == 0)
                return;

            bn->select_in_browser();

            // no break
        case 1:

        {
            QString s = bn->full_name(TRUE);

            if ((index = list.indexOf(s)) == -1) {
                // new class, may be created through an other dialog
                index = 0;
                QStringList::Iterator iter = list.begin();
                QStringList::Iterator iter_end = list.end();

                while ((iter != iter_end) && (*iter < s)) {
                    ++iter;
                    index += 1;
                }

                nodes.insert((unsigned) index, bn);
                list.insert(iter, s);
                edtype->addItem(s, index);
            }
        }

        edtype->setCurrentIndex(index);
        }
        }
    }
}

void InstanceDialog::accept()
{
    inst->set_name(edname->text().trimmed());
    inst->set_type(nodes.at(edtype->currentIndex()));

    QDialog::accept();
}
