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





#include <gridbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <vvbox.h>
#include <qcursor.h>
#include "ActivityPartitionDialog.h"
#include "ActivityPartitionData.h"
#include "BrowserActivityPartition.h"
#include "UmlWindow.h"
#include "DialogUtil.h"
#include "KeyValueTable.h"
#include "UmlDesktop.h"
#include "BodyDialog.h"
#include "strutil.h"
#include "ProfiledStereotypes.h"
#include "BrowserView.h"
#include "translate.h"
#include "hhbox.h"
#include "menufactory.h"
QSize ActivityPartitionDialog::previous_size;

ActivityPartitionDialog::ActivityPartitionDialog(ActivityPartitionData * d)
    : TabDialog(0, 0, FALSE, Qt::WA_DeleteOnClose), data(d)
{
    d->browser_node->edit_start();

    if (d->browser_node->is_writable()) {
        setOkButton(tr("OK"));
        setCancelButton(tr("Cancel"));
    }
    else {
        setOkButton(QString());
        setCancelButton(tr("Close"));
    }

    setWindowTitle(tr("Activity Partition dialog"));

    bool visit = !hasOkButton();

    // general tab

    BrowserNode * bn = data->get_browser_node();
    GridBox * grid = new GridBox(2, this);

    umltab = grid;
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(tr("name : "), grid));
    grid->addWidget(edname = new LineEdit(bn->get_name(), grid));
    edname->setReadOnly(visit);

    grid->addWidget(new QLabel(tr("stereotype : "), grid));
    grid->addWidget(edstereotype = new QComboBox(grid));
    edstereotype->setEditable(!visit);
    edstereotype->addItem(toUnicode(data->get_stereotype()));

    if (! visit) {
        edstereotype->addItems(BrowserActivityPartition::default_stereotypes());
        edstereotype->addItems(ProfiledStereotypes::defaults(UmlActivityPartition));
        edstereotype->setAutoCompletion(completion());
    }

    edstereotype->setCurrentIndex(0);
    QSizePolicy sp = edstereotype->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    edstereotype->setSizePolicy(sp);

    SmallPushButton *sButton;
    connect(sButton = new SmallPushButton(tr("represents :"), grid), SIGNAL(clicked()),
            this, SLOT(menu_represents()));
    grid->addWidget(sButton);
    grid->addWidget(edrepresents = new QComboBox(grid));

    if ((data->represents != 0) && !data->represents->deletedp()) {
        represented = data->represents;
        edrepresents->addItem(*(data->represents->pixmap(0)),
                              data->represents->full_name(TRUE));
    }
    else {
        represented = 0;
        edrepresents->addItem("");
    }

    if (! visit)
        edrepresents->addItem("");

    edrepresents->setCurrentIndex(0);
    edrepresents->setSizePolicy(sp);

    HHBox * htab;

    grid->addWidget(new QLabel(grid));
    grid->addWidget(htab = new HHBox(grid));
    htab->addWidget(new QLabel("  ", htab));
    htab->addWidget(dimension_cb = new QCheckBox(tr("is dimension"), htab));

    if (data->is_dimension)
        dimension_cb->setChecked(TRUE);

    dimension_cb->setDisabled(visit);
    htab->addWidget(new QLabel("", htab));
    htab->addWidget(external_cb = new QCheckBox(tr("is external"), htab));

    if (data->is_external)
        external_cb->setChecked(TRUE);

    external_cb->setDisabled(visit);
    htab->addWidget(new QLabel("", htab));

    VVBox * vtab;
    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(tr("description :"), vtab));

    if (! visit)
    {
        connect(sButton =  new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_description()));
        vtab->addWidget(sButton);
    }

    grid->addWidget(comment = new MultiLineEdit(grid));
    comment->setReadOnly(visit);
    comment->setText(bn->get_comment());
    QFont font = comment->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);
    comment->setFont(font);

    addTab(grid, "Uml");

    // USER : list key - value

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

   grid->addWidget( kvtable = new KeyValuesTable(bn, grid, visit));
    addTab(grid, tr("Properties"));

    //

    connect(this, SIGNAL(currentChanged(QWidget *)),
            this, SLOT(change_tabs(QWidget *)));

    open_dialog(this);
}

void ActivityPartitionDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::limitsize_move(this, previous_size, 0.8, 0.8);
}

ActivityPartitionDialog::~ActivityPartitionDialog()
{
    data->browser_node->edit_end();
    previous_size = size();

    foreach (BodyDialog *dialog, edits)
        dialog->close();
    edits.clear();

    close_dialog(this);
}

void ActivityPartitionDialog::change_tabs(QWidget * w)
{
    if (hasOkButton() && (w == umltab))
        edname->setFocus();
}

void ActivityPartitionDialog::edit_description()
{
    edit(comment->text(),
         (edname == 0) ? QString("description")
                       : edname->text().trimmed() + "_description",
         data, TxtEdit, this, (post_edit) post_edit_description, edits);
}

void ActivityPartitionDialog::post_edit_description(ActivityPartitionDialog * d, QString s)
{
    d->comment->setText(s);
}

static bool allowed(BrowserNode * bn)
{
    if (!bn->deletedp()) {
        switch (bn->get_type()) {
        case UmlClassView:
        case UmlUseCaseView:
        case UmlComponentView:
        case UmlDeploymentView:
            break;

        case UmlPackage:
            if (bn->parent() == 0)
                // project
                break;

            // no break
        default:
            return TRUE;
        }
    }

    return FALSE;
}

void ActivityPartitionDialog::menu_represents()
{
    if (!hasOkButton() && (represented == 0))
        return;

    QMenu m(0);

    MenuFactory::addItem(m, tr("Choose"), -1);
    m.addSeparator();

    if (represented != 0)
        MenuFactory::addItem(m, tr("Select in browser"), 0);

    BrowserNode * bn = BrowserView::selected_item();

    if ((bn != 0) && allowed(bn))
        MenuFactory::addItem(m, tr("Choose element selected in browser"), 1);

    const QList<BrowserNode *> & l = BrowserNode::marked_nodes();

    if ((l.count() == 1) && allowed(l.first()))
        MenuFactory::addItem(m, tr("Choose element marked in browser"), 2);

    QAction* retAction = m.exec(QCursor::pos());
    if(retAction)
    {
        switch (retAction->data().toInt()) {
        case 0:
            represented->select_in_browser();
            return;

        case 1:
            represented = bn;
            break;

        case 2:
            represented = l.first();
            break;

        default:
            return;
        }
    }

    edrepresents->setItemText(0, represented->full_name(TRUE));
    edrepresents->setItemIcon(0, *(represented->pixmap(0)));
}

void ActivityPartitionDialog::accept()
{
    if (!check_edits(edits) || !kvtable->check_unique())
        return;

    BrowserNode * bn = data->get_browser_node();

    if (edname != 0) {
        QString s = edname->text().trimmed();

        if ((s != bn->get_name()) &&
                ((BrowserNode *) bn->parent())->wrong_child_name(s, bn->get_type(),
                                                                 bn->allow_spaces(),
                                                                 bn->allow_empty())) {
            msg_critical(tr("Error"), edname->text() + tr("\n\nillegal name or already used"));
            return;
        }
        else
            bn->set_name(s);
    }

    data->represents = (edrepresents->currentText().isEmpty())
            ? 0 : represented;
    data->is_dimension = dimension_cb->isChecked();
    data->is_external = external_cb->isChecked();

    bool newst = data->set_stereotype(fromUnicode(edstereotype->currentText().trimmed()));

    bn->set_comment(comment->text());
    UmlWindow::update_comment_if_needed(bn);

    kvtable->updateNodeFromThis(bn);

    ProfiledStereotypes::modified(bn, newst);

    bn->package_modified();
    data->modified();

    TabDialog::accept();
}
