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
#include <vvbox.h>

#include "SimpleRelationDialog.h"
#include "SimpleRelationData.h"
#include "BrowserSimpleRelation.h"
#include "UmlWindow.h"
#include "KeyValueTable.h"
#include "UmlPixmap.h"
#include "DialogUtil.h"
#include "strutil.h"
#include "UmlDesktop.h"
#include "BodyDialog.h"
#include "ProfiledStereotypes.h"
#include "translate.h"

QSize SimpleRelationDialog::previous_size;

SimpleRelationDialog::SimpleRelationDialog(SimpleRelationData * r)
    : TabDialog(0, 0, FALSE, Qt::WA_DeleteOnClose), rel(r)
{
    r->browser_node->edit_start();

    if (r->browser_node->is_writable()) {
        setOkButton(TR("OK"));
        setCancelButton(TR("Cancel"));
    }
    else {
        setOkButton(QString());
        setCancelButton(TR("Close"));
    }

    bool visit = !hasOkButton();

    // general tab

    BrowserNode * bn = rel->get_browser_node();
    GridBox * grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    switch (rel->get_type()) {
    case UmlInherit:
        setWindowTitle(TR("Generalisation dialog"));
        break;

    case UmlDependOn:
        setWindowTitle(TR("Dependency dialog"));
        break;

    default:
        setWindowTitle(TR("unknown relation dialog"));
        break;
    }

    grid->addWidget(new QLabel(TR("from : "), grid));
    grid->addWidget(new QLabel(rel->get_start_node()->full_name(TRUE), grid));
    grid->addWidget(new QLabel(TR("to : "), grid));
    grid->addWidget(new QLabel(rel->get_end_node()->full_name(TRUE), grid));

    grid->addWidget(new QLabel(TR("stereotype : "), grid));
    grid->addWidget(edstereotype = new QComboBox(grid));
    edstereotype->setEditable(!visit);
    edstereotype->addItem(toUnicode(rel->get_stereotype()));

    if (! visit) {
        edstereotype->addItems(rel->get_start_node()
                                       ->default_stereotypes(rel->get_type(),
                                               rel->get_end_node()));
        edstereotype->addItems(ProfiledStereotypes::defaults(UmlRelations));
        edstereotype->setAutoCompletion(completion());
    }

    edstereotype->setCurrentIndex(0);
    QSizePolicy sp = edstereotype->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    edstereotype->setSizePolicy(sp);

    VVBox * vtab;
    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(TR("description :"), vtab));
            SmallPushButton* sButton;
    if (! visit)
    {
        connect(sButton = new SmallPushButton(TR("Editor"), vtab), SIGNAL(clicked()),
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

    grid->addWidget(kvtable = new KeyValuesTable(bn, grid, visit));
    addTab(grid, TR("Properties"));

    open_dialog(this);
}

void SimpleRelationDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::limitsize_move(this, previous_size, 0.8, 0.8);
}

SimpleRelationDialog::~SimpleRelationDialog()
{
    rel->browser_node->edit_end();
    previous_size = size();

    foreach (BodyDialog *dialog, edits)
        dialog->close();
    edits.clear();

    close_dialog(this);
}

void SimpleRelationDialog::edit_description()
{
    edit(comment->text(), "simplerelation_description",
         rel, TxtEdit, this, (post_edit) post_edit_description, edits);
}

void SimpleRelationDialog::post_edit_description(SimpleRelationDialog * d, QString s)
{
    d->comment->setText(s);
}

void SimpleRelationDialog::accept()
{
    if (!check_edits(edits) || !kvtable->check_unique())
        return;

    BrowserNode * bn = rel->get_browser_node();
    bool newst = rel->set_stereotype(fromUnicode(edstereotype->currentText().trimmed().toLatin1().constData()));

    bn->set_comment(comment->text());
    UmlWindow::update_comment_if_needed(bn);

    kvtable->updateNodeFromThis(bn);

    ProfiledStereotypes::modified(bn, newst);

    bn->package_modified();
    rel->modified();

    TabDialog::accept();
}
