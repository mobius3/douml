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

#include "ClassViewDialog.h"
#include "BasicData.h"
#include "BrowserClassView.h"
#include "BrowserDeploymentView.h"
#include "UmlWindow.h"
#include "DialogUtil.h"
#include "KeyValueTable.h"
#include "UmlDesktop.h"
#include "BodyDialog.h"
#include "strutil.h"
#include "ProfiledStereotypes.h"
#include "translate.h"

QSize ClassViewDialog::previous_size;

ClassViewDialog::ClassViewDialog(BasicData * nd)
    : TabDialog(0, 0, FALSE, Qt::WA_DeleteOnClose), data(nd)
{
    nd->get_browser_node()->edit_start();

    if (nd->get_browser_node()->is_writable()) {
        setOkButton(TR("OK"));
        setCancelButton(TR("Cancel"));
    }
    else {
        setOkButton(QString());
        setCancelButton(TR("Close"));
    }

    setWindowTitle(TR("class view dialog"));

    bool visit = !hasOkButton();

    // general tab

    BrowserClassView * bn = (BrowserClassView *) data->get_browser_node();
    GridBox * grid = new GridBox(2, this);

    umltab = grid;
    grid->setMargin(1);
    grid->setSpacing(1);

    grid->addWidget(new QLabel(TR("name : "), grid));
    grid->addWidget(edname = new LineEdit(bn->get_name(), grid));
    edname->setReadOnly(visit);

    grid->addWidget(new QLabel(TR("stereotype : "), grid));
    grid->addWidget(edstereotype = new QComboBox( grid));
    edstereotype->setEditable(!visit);
    edstereotype->addItem(toUnicode(data->get_stereotype()));

    if (!visit) {
        edstereotype->addItems(BrowserClassView::default_stereotypes());
        edstereotype->addItems(ProfiledStereotypes::defaults(UmlClassView));
        edstereotype->setAutoCompletion(completion());
    }

    edstereotype->setCurrentIndex(0);
    QSizePolicy sp = edstereotype->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    edstereotype->setSizePolicy(sp);

    BrowserNode * bcv = bn->get_associated();

    if (visit) {
        if ((bcv != 0) && !bcv->deletedp()) {
            grid->addWidget(new QLabel(TR("deployment\nview : "), grid));
            grid->addWidget(deploymentview = new QComboBox( grid));

            BrowserNode * bcv = bn->get_associated();

            deploymentview->addItem(bcv->full_name(TRUE));
            deploymentview->setCurrentIndex(0);
        }
        else
            deploymentview = 0;
    }
    else {
        BrowserDeploymentView::instances(deploymentviews);

        if (!deploymentviews.isEmpty()) {
            QStringList deploymentview_names;

            deploymentviews.full_names(deploymentview_names);
            grid->addWidget(new QLabel(TR("deployment\nview : "), grid));
            grid->addWidget(deploymentview = new QComboBox(grid));
            deploymentview->addItem("");
            deploymentview->addItems(deploymentview_names);

            if (bcv != 0) {
                if (bcv->deletedp()) {
                    QString fn = bcv->full_name(TRUE);

                    deploymentview->addItem(fn);
                    deploymentviews.append(bcv);
                    deploymentview->setCurrentIndex(deploymentviews.count());
                }
                else
                    deploymentview->setCurrentIndex(deploymentviews.indexOf(bcv) + 1);
            }
            else
                deploymentview->setCurrentIndex(0);
        }
        else
            deploymentview = 0;
    }

    VVBox * vtab = new VVBox(grid);
    grid->addWidget(vtab);
    vtab->addWidget(new QLabel(TR("description :"), vtab));

    SmallPushButton *sButton;
    if (!visit)
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

    kvtable = new KeyValuesTable(bn, grid, visit);
    grid->addWidget(kvtable);
    addTab(grid, TR("Properties"));

    //

    connect(this, SIGNAL(currentChanged(QWidget *)),
            this, SLOT(change_tabs(QWidget *)));

    open_dialog(this);
}

void ClassViewDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::limitsize_move(this, previous_size, 0.8, 0.8);
}

ClassViewDialog::~ClassViewDialog()
{
    data->get_browser_node()->edit_end();
    previous_size = size();

    foreach (BodyDialog *dialog, edits)
        dialog->close();
    edits.clear();

    close_dialog(this);
}

void ClassViewDialog::change_tabs(QWidget * w)
{
    if (hasOkButton() && (w == umltab))
        edname->setFocus();
}

void ClassViewDialog::edit_description()
{
    edit(comment->text(), edname->text().trimmed() + "_description",
         data, TxtEdit, this, (post_edit) post_edit_description, edits);
}

void ClassViewDialog::post_edit_description(ClassViewDialog * d, QString s)
{
    d->comment->setText(s);
}

void ClassViewDialog::accept()
{
    if (!check_edits(edits) || !kvtable->check_unique())
        return;

    QString s = edname->text().trimmed();
    BrowserClassView * bn = (BrowserClassView *) data->get_browser_node();

    if ((s != bn->get_name()) &&
        ((BrowserNode *) bn->parent())->wrong_child_name(s, bn->get_type(),
                bn->allow_spaces(),
                bn->allow_empty()))
        msg_critical(TR("Error"), edname->text() + TR("\n\nillegal name or already used"));
    else {
        bn->set_name(s);

        bool newst = data->set_stereotype(fromUnicode(edstereotype->currentText().trimmed()));

        if (deploymentview != 0) {
            int index = deploymentview->currentIndex();

            bn->set_associated_deploymentview((index == 0)
                                              ? 0 // "" : no deploymentview
                                              : ((BrowserDeploymentView *) deploymentviews.at(index - 1)));
        }

        bn->set_comment(comment->text());
        UmlWindow::update_comment_if_needed(bn);

        kvtable->updateNodeFromThis(bn);

        ProfiledStereotypes::modified(bn, newst);

        data->modified();
        bn->package_modified();

        TabDialog::accept();
    }
}
