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
#include "ExpansionRegionDialog.h"
#include "ExpansionRegionData.h"
#include "BrowserExpansionRegion.h"
#include "UmlWindow.h"
#include "DialogUtil.h"
#include "KeyValueTable.h"
#include "UmlDesktop.h"
#include "BodyDialog.h"
#include "strutil.h"
#include "ProfiledStereotypes.h"
#include "translate.h"
#include "hhbox.h"
QSize ExpansionRegionDialog::previous_size;

ExpansionRegionDialog::ExpansionRegionDialog(ExpansionRegionData * nd)
    : TabDialog(0, 0, FALSE, Qt::WA_DeleteOnClose), data(nd)
{
    nd->browser_node->edit_start();

    if (nd->browser_node->is_writable()) {
        setOkButton(TR("OK"));
        setCancelButton(TR("Cancel"));
    }
    else {
        setOkButton(QString());
        setCancelButton(TR("Close"));
    }

    setWindowTitle(TR("Expansion Region dialog"));

    bool visit = !hasOkButton();

    // general tab

    BrowserNode * bn = data->get_browser_node();
    GridBox * grid = new GridBox(2, this);

    umltab = grid;
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(TR("name : "), grid));
    grid->addWidget(edname = new LineEdit(bn->get_name(), grid));
    edname->setReadOnly(visit);

    grid->addWidget(new QLabel(TR("stereotype : "), grid));
    grid->addWidget(edstereotype = new QComboBox(grid));
    edstereotype->setEditable(!visit);
    edstereotype->addItem(toUnicode(data->get_stereotype()));

    if (! visit) {
        edstereotype->addItems(BrowserExpansionRegion::default_stereotypes());
        edstereotype->addItems(ProfiledStereotypes::defaults(UmlExpansionRegion));
        edstereotype->setAutoCompletion(completion());
    }

    edstereotype->setCurrentIndex(0);
    QSizePolicy sp = edstereotype->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    edstereotype->setSizePolicy(sp);

    HHBox * htab;

    grid->addWidget(new QLabel(TR("mode :"), grid));
    grid->addWidget(htab = new HHBox(grid));
    htab->addWidget(edmode = new QComboBox(htab));

    UmlExpansionKind m = data->get_mode();

    edmode->addItem(stringify(m));

    if (! visit) {
        if (m != UmlParallel)
            edmode->addItem(stringify(UmlParallel));

        if (m != UmlIterative)
            edmode->addItem(stringify(UmlIterative));

        if (m != UmlStream)
            edmode->addItem(stringify(UmlStream));
    }

    htab->addWidget(new QLabel("  ", htab));
    htab->addWidget(must_isolate_cb = new QCheckBox(TR("must isolate"), htab));

    if (data->must_isolate)
        must_isolate_cb->setChecked(TRUE);

    must_isolate_cb->setDisabled(visit);
    htab->addWidget(new QLabel("", htab));

    VVBox * vtab;
    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(TR("description :"), vtab));

    SmallPushButton* b;
    if (! visit)
    {
        connect(b = new SmallPushButton(TR("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_description()));
        vtab->addWidget(b);
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

    grid->addWidget(kvtable = new KeyValuesTable(bn, grid, visit));
    addTab(grid, TR("Properties"));

    //

    connect(this, SIGNAL(currentChanged(QWidget *)),
            this, SLOT(change_tabs(QWidget *)));

    open_dialog(this);
}

void ExpansionRegionDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::limitsize_move(this, previous_size, 0.8, 0.8);
}

ExpansionRegionDialog::~ExpansionRegionDialog()
{
    data->browser_node->edit_end();
    previous_size = size();

    foreach (BodyDialog *dialog, edits)
        dialog->close();
    edits.clear();

    close_dialog(this);
}

void ExpansionRegionDialog::change_tabs(QWidget * w)
{
    if (hasOkButton() && (w == umltab))
        edname->setFocus();
}

void ExpansionRegionDialog::edit_description()
{
    edit(comment->text(),
         (edname == 0) ? QString(TR("description"))
         : edname->text().trimmed() + "_description",
         data, TxtEdit, this, (post_edit) post_edit_description, edits);
}

void ExpansionRegionDialog::post_edit_description(ExpansionRegionDialog * d, QString s)
{
    d->comment->setText(s);
}

void ExpansionRegionDialog::accept()
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
            msg_critical(TR("Error"), edname->text() + TR("\n\nillegal name or already used"));
            return;
        }
        else
            bn->set_name(s);
    }

    data->must_isolate = must_isolate_cb->isChecked();
    data->mode = expansion_mode_kind(edmode->currentText().toLatin1().constData());

    bool newst = data->set_stereotype(fromUnicode(edstereotype->currentText().trimmed()));

    bn->set_comment(comment->text());
    UmlWindow::update_comment_if_needed(bn);

    kvtable->updateNodeFromThis(bn);

    ProfiledStereotypes::modified(bn, newst);

    bn->package_modified();
    data->modified();

    TabDialog::accept();
}
