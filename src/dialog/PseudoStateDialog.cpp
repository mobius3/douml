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
#include <qcursor.h>
#include <vvbox.h>
#include "PseudoStateDialog.h"
#include "BrowserPseudoState.h"
#include "BrowserState.h"
#include "BrowserView.h"
#include "PseudoStateData.h"
#include "StateData.h"
#include "UmlWindow.h"
#include "DialogUtil.h"
#include "KeyValueTable.h"
#include "UmlDesktop.h"
#include "BodyDialog.h"
#include "strutil.h"
#include "ProfiledStereotypes.h"
#include "translate.h"
#include "menufactory.h"
QSize PseudoStateDialog::previous_size;

PseudoStateDialog::PseudoStateDialog(PseudoStateData * ps)
    : TabDialog(0, 0, FALSE, Qt::WA_DeleteOnClose), pst(ps)
{
    BrowserPseudoState * bn = (BrowserPseudoState *) pst->browser_node;
    BrowserState * refst;
    SmallPushButton* sButton;

    switch (bn->get_type()) {
    case EntryPointPS:
    case ExitPointPS:
        if (((BrowserNode *) bn->parent())->get_type() == UmlState) {
            refst = ((StateData *)((BrowserNode *) bn->parent())->get_data())->get_reference();
            break;
        }

        // no break
    default:
        refst = 0;
    }

    bn->edit_start();

    if (bn->is_writable()) {
        setOkButton(tr("OK"));
        setCancelButton(tr("Cancel"));
    }
    else {
        setOkButton(QString());
        setCancelButton(tr("Close"));
    }

    QString s = stringify(bn->get_type());
    int index = s.indexOf("_");

    if (index != -1)
        s.replace(index, 1, " ");

    setCaption((s + " dialog"));

    visit = !hasOkButton();

    // general tab

    GridBox * grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(tr("name : "), grid));
    grid->addWidget(edname = new LineEdit(bn->get_name(), grid));
    edname->setReadOnly(visit);

    grid->addWidget(new QLabel(tr("stereotype : "), grid));
    grid->addWidget(edstereotype = new QComboBox(grid));
    edstereotype->setEditable(!visit);
    edstereotype->addItem(toUnicode(pst->get_stereotype()));

    if (! visit) {
        edstereotype->addItems(BrowserPseudoState::default_stereotypes());
        edstereotype->addItems(ProfiledStereotypes::defaults(bn->get_type()));
        edstereotype->setAutoCompletion(completion());
    }

    edstereotype->setCurrentIndex(0);
    QSizePolicy sp = edstereotype->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    edstereotype->setSizePolicy(sp);

    if (refst != 0) {
        connect(new SmallPushButton(tr("reference :"), grid), SIGNAL(clicked()),
                this, SLOT(menu_reference()));
        grid->addWidget(edreference = new QComboBox(grid));
        edreference->setSizePolicy(sp);

        BrowserNode * ref = ((pst->get_reference() == 0) ||
                             !bn->can_reference(pst->get_reference()))
                            ? 0 : pst->get_reference();

        if (visit) {
            if (ref == 0)
                edreference->addItem("");
            else
                edreference->addItem(ref->full_name(TRUE));
        }
        else {
            edreference->addItem("");
            edreference->setAutoCompletion(completion());

            BrowserNode * child;
            UmlCode k = bn->get_type();

            for (child = refst->firstChild();
                 child != 0;
                 child = child->nextSibling()) {
                if (!((BrowserNode *) child)->deletedp()) {
                    UmlCode kk = ((BrowserNode *) child)->get_type();

                    if (kk == k)
                        pseudostates.append((BrowserNode *) child);
                    else if (kk == UmlRegion) {
                        for (BrowserNode * schild = child->firstChild();
                             schild != 0;
                             schild = schild->nextSibling()) {
                            if (!((BrowserNode *) schild)->deletedp() &&
                                (((BrowserNode *) schild)->get_type() == k))
                                pseudostates.append((BrowserNode *) schild);
                        }
                    }
                }
            }

            pseudostates.sort();
            pseudostates.full_names(reflist);
            edreference->addItems(reflist);
            edreference->setCurrentIndex((ref == 0)
                                        ? 0
                                        : pseudostates.indexOf(ref) + 1);
        }
    }
    else
        edreference = 0;

    VVBox * vtab;
    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(tr("description :"), vtab));

    if (! visit)
    {
        connect(sButton = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
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
    addTab(grid, tr("Properties"));

    open_dialog(this);
}

void PseudoStateDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::limitsize_move(this, previous_size, 0.8, 0.8);
}

PseudoStateDialog::~PseudoStateDialog()
{
    pst->browser_node->edit_end();
    previous_size = size();

    foreach (BodyDialog *dialog, edits)
        dialog->close();
    edits.clear();

    close_dialog(this);
}

void PseudoStateDialog::menu_reference()
{
    QMenu m(0);

    MenuFactory::addItem(m, tr("Choose"), -1);
    m.addSeparator();

    int index = reflist.indexOf(edreference->currentText());

    if (index != -1)
        MenuFactory::addItem(m, tr("Select in browser"), 0);

    BrowserNode * bn = 0;

    if (! visit) {
        bn = BrowserView::selected_item();

        if ((bn != 0) &&
            !bn->deletedp() &&
            ((BrowserPseudoState *) pst->browser_node)->can_reference(bn))
            MenuFactory::addItem(m, tr("Choose pseudo state selected in browser"), 1);
        else
            bn = 0;
    }

    if ((index != -1) || (bn != 0)) {
        QAction* retAction = m.exec(QCursor::pos());
        if(retAction)
        {
        switch (retAction->data().toInt()) {
        case 0:
            pseudostates.at(index)->select_in_browser();
            break;

        case 1: {
            QString s = bn->full_name(TRUE);

            if ((index = reflist.indexOf(s)) == -1) {
                // new state, may be created through an other dialog
                index = 0;
                QStringList::Iterator iter = reflist.begin();
                QStringList::Iterator iter_end = reflist.end();

                while ((iter != iter_end) && (*iter < s)) {
                    ++iter;
                    index += 1;
                }

                pseudostates.insert((unsigned) index, bn);
                reflist.insert(iter, s);
                edreference->insertItem(index + 1, s);
            }
        }

        edreference->setCurrentIndex(index + 1);
        break;

        default:
            break;
        }
        }
    }
}

void PseudoStateDialog::edit_description()
{
    edit(comment->text(),
         (edname == 0) ? QString("description")
         : edname->text().trimmed() + "_description",
         pst, TxtEdit, this, (post_edit) post_edit_description, edits);
}

void PseudoStateDialog::post_edit_description(PseudoStateDialog * d, QString s)
{
    d->comment->setText(s);
}

void PseudoStateDialog::accept()
{
    if (!check_edits(edits) || !kvtable->check_unique())
        return;

    QString s = edname->text().trimmed();
    BrowserPseudoState * bn = (BrowserPseudoState *) pst->browser_node;

    if ((s != bn->get_name()) &&
        ((BrowserNode *) bn->parent())->wrong_child_name(s, UmlPseudoState,
                bn->allow_spaces(),
                bn->allow_empty())) {
        msg_critical(tr("Error"), edname->text() + tr("\n\nillegal name or already used"));
        return;
    }
    else
        bn->set_name(s);

    bool newst = pst->set_stereotype(fromUnicode(edstereotype->currentText().trimmed()));

    bn->set_comment(comment->text());
    UmlWindow::update_comment_if_needed(bn);

    kvtable->updateNodeFromThis(bn);

    if (edreference != 0) {
        int index = reflist.indexOf(edreference->currentText());
        BrowserPseudoState * ps;

        if (index != -1) {
            ps = (BrowserPseudoState *) pseudostates.at(index);

            if (! bn->can_reference(ps))
                ps = 0;
        }
        else
            ps = 0;

        pst->set_reference(ps);
    }

    ProfiledStereotypes::modified(bn, newst);

    bn->modified();
    bn->package_modified();
    pst->modified();

    TabDialog::accept();
}
