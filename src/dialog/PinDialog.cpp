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
#include <vvbox.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <bbuttongroup.h>
#include <qcheckbox.h>
#include <qradiobutton.h>
#include <qpushbutton.h>
#include <qcursor.h>
#include "PinDialog.h"
#include "PinData.h"
#include "BrowserClass.h"
#include "BrowserPin.h"
#include "BrowserView.h"
#include "KeyValueTable.h"
#include "UmlWindow.h"
#include "UmlDesktop.h"
#include "DialogUtil.h"
#include "GenerationSettings.h"
#include "strutil.h"
#include "BodyDialog.h"
#include "ProfiledStereotypes.h"
#include "translate.h"
#include "hhbox.h"
#include "menufactory.h"

QSize PinDialog::previous_size;

PinDialog::PinDialog(PinData * pi)
    : TabDialog(0, 0, true, Qt::WA_DeleteOnClose), pin(pi)
{
    pi->browser_node->edit_start();

    if (pi->browser_node->is_writable()) {
        setOkButton(tr("OK"));
        setCancelButton(tr("Cancel"));
    }
    else {
        setOkButton(QString());
        setCancelButton(tr("Close"));
    }

    visit = !hasOkButton();
    setWindowTitle(tr("Pin dialog"));

    GridBox * grid;
    HHBox * htab;
    QString s;

    // general tab

    grid = new GridBox(2, this);
    umltab = grid;
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(tr("name :"), grid));
    grid->addWidget(edname = new LineEdit(pi->name(), grid));
    edname->setReadOnly(visit);

    QFont font = edname->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);

    grid->addWidget(new QLabel(tr("stereotype : "), grid));
    grid->addWidget(edstereotype = new QComboBox( grid));
    edstereotype->setEditable(!visit);
    edstereotype->addItem(toUnicode(pi->stereotype));

    if (! visit) {
        edstereotype->addItems(BrowserPin::default_stereotypes());
        edstereotype->addItems(ProfiledStereotypes::defaults(UmlActivityPin));
        edstereotype->setAutoCompletion(completion());
    }

    edstereotype->setCurrentIndex(0);

    QSizePolicy sp = edstereotype->sizePolicy();

    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    edstereotype->setSizePolicy(sp);
    SmallPushButton* sButton;
    connect(sButton = new SmallPushButton(tr("type :"), grid), SIGNAL(clicked()),
            this, SLOT(menu_type()));
    grid->addWidget(sButton);

    grid->addWidget(edtype = new QComboBox(grid));
    edtype->setEditable(!visit);
    edtype->addItem(pi->get_type().get_full_type());

    if (!visit) {
        BrowserClass::instances(nodes);
        nodes.full_names(list);

        edtype->addItems(GenerationSettings::basic_types());
        offset = edtype->count();
        edtype->addItems(list);
        edtype->setAutoCompletion(completion());
        view = pi->browser_node->container(UmlClass);
    }

    edtype->setCurrentIndex(0);
    edtype->setSizePolicy(sp);

    grid->addWidget(new QLabel(tr("direction :"), grid));
    grid->addWidget(htab = new HHBox(grid));
    htab->addWidget(eddir = new QComboBox(htab));

    UmlParamDirection dir = pi->get_dir();

    eddir->addItem(stringify(dir));

    if (! visit) {
        // note : inout not allowed
        if (dir != UmlIn)
            eddir->addItem(stringify(UmlIn));

        if (dir != UmlOut)
            eddir->addItem(stringify(UmlOut));

        if (dir != UmlReturn)
            eddir->addItem(stringify(UmlReturn));
    }

    htab->addWidget(new QLabel(tr("   multiplicity : "), htab));
    htab->addWidget(edmultiplicity = new QComboBox( htab));
    edmultiplicity->setEditable(!visit);
    edmultiplicity->setSizePolicy(sp);
    edmultiplicity->addItem(pi->get_multiplicity());

    if (!visit) {
        edmultiplicity->addItem("1");
        edmultiplicity->addItem("0..1");
        edmultiplicity->addItem("*");
        edmultiplicity->addItem("1..*");
    }

    htab->addWidget(new QLabel(tr("   ordering : "), htab));
    htab->addWidget(edordering = new QComboBox(htab));

    UmlOrderingKind o = pi->get_ordering();

    edordering->addItem(stringify(o));

    if (!visit) {
        if (o != UmlUnordered)
            edordering->addItem(stringify(UmlUnordered));

        if (o != UmlOrdered)
            edordering->addItem(stringify(UmlOrdered));

        if (o != UmlLifo)
            edordering->addItem(stringify(UmlLifo));

        if (o != UmlFifo)
            edordering->addItem(stringify(UmlFifo));
    }

    htab->addWidget(new QLabel(tr("   effect : "), htab));
    htab->addWidget(edeffect = new QComboBox(htab));

    UmlParamEffect e = pi->get_effect();

    edeffect->addItem(stringify(e));

    if (!visit) {
        if (e != UmlNoEffect)
            edeffect->addItem(stringify(UmlNoEffect));

        if (e != UmlCreate)
            edeffect->addItem(stringify(UmlCreate));

        if (e != UmlRead)
            edeffect->addItem(stringify(UmlRead));

        if (e != UmlUpdate)
            edeffect->addItem(stringify(UmlUpdate));

        if (e != UmlDelete)
            edeffect->addItem(stringify(UmlDelete));
    }

    grid->addWidget(new QLabel(tr("in state : "), grid));
    grid->addWidget(edin_state = new LineEdit(pi->in_state, grid));
    edin_state->setReadOnly(visit);

    grid->addWidget(new QLabel(grid));
    grid->addWidget(htab = new HHBox(grid));
    BButtonGroup * bg;
    htab->addWidget(bg = new BButtonGroup(2, Qt::Horizontal, QString(), htab));

    bg->addWidget(is_control_cb = new QCheckBox(tr("is_control"), bg));

    if (pi->is_control)
        is_control_cb->setChecked(TRUE);

    is_control_cb->setDisabled(visit);

    bg->addWidget(unique_cb = new QCheckBox(tr("unique"), bg));

    if (pi->unique)
        unique_cb->setChecked(TRUE);

    unique_cb->setDisabled(visit);

    htab->addWidget(bg = new BButtonGroup(3, Qt::Horizontal, QString(), htab));
    bg->setExclusive(TRUE);

    bg->addWidget(standard_rb = new QRadioButton(tr("standard"), bg));
    bg->addWidget(exception_rb = new QRadioButton(tr("exception"), bg));
    bg->addWidget(stream_rb = new QRadioButton(tr("stream"), bg));

    if (pi->exception)
        exception_rb->setChecked(TRUE);
    else if (pi->stream)
        stream_rb->setChecked(TRUE);
    else
        standard_rb->setChecked(TRUE);

    VVBox * vtab;
    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(tr("description :"), vtab));

    if (! visit) {
        connect(sButton = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_description()));
        vtab->addWidget(sButton);
    }

    grid->addWidget(comment = new MultiLineEdit(grid));
    comment->setReadOnly(visit);
    comment->setText(pi->browser_node->get_comment());
    comment->setFont(font);

    addTab(grid, "Uml");

    init_tab(ocltab, eduml_selection, pin->uml_selection, "Ocl",
             SLOT(edit_uml_selection()), TRUE);

    // C++
    init_tab(cppTab, edcpp_selection, pin->cpp_selection, "C++",
             SLOT(edit_cpp_selection()),
             GenerationSettings::cpp_get_default_defs());

    // Java
    init_tab(javatab, edjava_selection, pin->java_selection, "Java",
             SLOT(edit_java_selection()),
             GenerationSettings::java_get_default_defs());

    // USER : list key - value

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(kvtable = new KeyValuesTable(pi->browser_node, grid, visit));
    addTab(grid, tr("Properties"));

    //

    connect(this, SIGNAL(currentChanged(QWidget *)),
            this, SLOT(change_tabs(QWidget *)));

    open_dialog(this);
}

PinDialog::~PinDialog()
{
    pin->browser_node->edit_end();
    previous_size = size();

    foreach (BodyDialog *dialog, edits)
        dialog->close();
    edits.clear();

    close_dialog(this);
}

void PinDialog::change_tabs(QWidget * w)
{
    if (hasOkButton()) {
        if (w == umltab)
            edname->setFocus();
        else if (w == ocltab)
            eduml_selection->setFocus();
        else if (w == cppTab)
            edcpp_selection->setFocus();
        else if (w == javatab)
            edjava_selection->setFocus();
    }
}

void PinDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::limitsize_center(this, previous_size, 0.8, 0.8);
}

void PinDialog::init_tab(QWidget *& tab, MultiLineEdit *& ed, const char * v,
                         const char * lbl, const char * sl, bool enabled)
{
    bool visit = !hasOkButton();
    GridBox * grid = new GridBox(2, this);

    tab = grid;
    grid->setMargin(5);
    grid->setSpacing(5);

    VVBox * vtab;
    grid->addWidget(vtab = new VVBox(grid));

    vtab->addWidget(new QLabel(tr("selection : "), vtab));
            SmallPushButton *sButton;
    if (! visit)
    {
        connect(sButton = new SmallPushButton(tr("Editor"), vtab), SIGNAL(clicked()), this, sl);
        vtab->addWidget(sButton);
    }

    grid->addWidget(ed = new MultiLineEdit(grid));

    QFont font = ed->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);
    ed->setFont(font);
    ed->setText(v);

    if (visit)
        ed->setReadOnly(TRUE);

    addTab(grid, lbl);

    if (! enabled)
        removePage(grid);
}

void PinDialog::menu_type()
{
    QMenu m(0);

    MenuFactory::addItem(m, tr("Choose"), -1);
    m.addSeparator();

    int index = list.indexOf(edtype->currentText().trimmed());

    if (index != -1)
        MenuFactory::addItem(m, tr("Select in browser"), 0);

    BrowserNode * bn = 0;

    if (! visit) {
        bn = BrowserView::selected_item();

        if ((bn != 0) && (bn->get_type() == UmlClass) && !bn->deletedp())
            MenuFactory::addItem(m, tr("Choose class selected in browser"), 1);
        else
            bn = 0;

        MenuFactory::addItem(m, tr("Create class and choose it"), 2);
    }

    if (!visit || (index != -1) || (bn != 0)) {
        QAction* retAction = m.exec(QCursor::pos());
        if(retAction)
        {
        switch (retAction->data().toInt()) {
        case 0:
            nodes.at(index)->select_in_browser();
            break;

        case 2:
            bn = BrowserClass::add_class(true, view,"");

            if (bn == 0)
                return;

            bn->select_in_browser();

            // no break
        case 1: {
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
                edtype->insertItem(index + offset,s);
            }
        }

        edtype->setCurrentIndex(index + offset);
        break;

        default:
            break;
        }
        }
    }
}

#define DEF_EDIT(lang, Lang) \
void PinDialog::edit_##lang##_selection() {	\
  edit(ed##lang##_selection->text(), "object_"#lang"_selection", pin, Lang,  \
       this, (post_edit) post_edit_##lang##_##selection, edits);	\
} \
  \
void PinDialog::post_edit_##lang##_selection(PinDialog * d, QString s) \
{ \
  d->ed##lang##_selection->setText(s); \
}

DEF_EDIT(uml, TxtEdit)
DEF_EDIT(cpp, CppEdit)
DEF_EDIT(java, JavaEdit)

void PinDialog::accept()
{
    if (!check_edits(edits) || !kvtable->check_unique())
        return;

    BrowserNode * bn = pin->browser_node;
    QString s;

    s = edname->text().trimmed();

    if ((s != pin->name()) &&
        ((BrowserNode *) bn->parent())->wrong_child_name(s, UmlActivityPin,
                bn->allow_spaces(),
                bn->allow_empty()))
        msg_critical(tr("Error"), s + tr("\n\nillegal name or already used"));
    else {
        // check consistency
        UmlParamDirection dir = direction(eddir->currentText());
        bool exception = exception_rb->isChecked();
        UmlParamEffect effect = ::effect(edeffect->currentText());
        QString err;

        if ((dir == UmlIn) && exception)
            err = tr("An input pin cannot be an exception.\n");

        switch (effect) {
        case UmlDelete:
            if ((dir != UmlIn) && (dir != UmlInOut))
                err += tr("Only in and inout pin may have a delete effect.");

            break;

        case UmlCreate:
            if ((dir != UmlOut) && (dir != UmlInOut) && (dir != UmlReturn))
                err += tr("Only out, inout and return pin may have a create effect.");

            break;

        default:
            break;
        }

        if (!err.isEmpty())
            msg_critical(tr("Error"), err);
        else {
            bn->set_name(s);

            bool newst = pin->set_stereotype(fromUnicode(edstereotype->currentText().trimmed()));
            AType t;

            s = edtype->currentText().trimmed();

            if (!s.isEmpty()) {
                int index = list.indexOf(s);

                if (index >= 0)
                    t.type = (BrowserClass *) nodes.at(index);
                else
                    t.explicit_type = s;
            }

            pin->set_type(t);
            pin->dir = dir;
            pin->multiplicity =
                edmultiplicity->currentText().trimmed();
            pin->ordering = ordering(edordering->currentText());
            pin->effect = effect;
            pin->is_control = is_control_cb->isChecked();
            pin->unique = unique_cb->isChecked();
            pin->in_state = edin_state->text().trimmed();
            pin->exception = exception;
            pin->stream = stream_rb->isChecked();
            pin->uml_selection = eduml_selection->text().trimmed();
            pin->cpp_selection = edcpp_selection->text().trimmed();
            pin->java_selection = edjava_selection->text().trimmed();

            bn->set_comment(comment->text());
            UmlWindow::update_comment_if_needed(bn);

            kvtable->updateNodeFromThis(bn);

            ProfiledStereotypes::modified(bn, newst);

            bn->modified();
            bn->package_modified();
            pin->modified();

            TabDialog::accept();
        }
    }
}

void PinDialog::edit_description()
{
    edit(comment->text(), edname->text().trimmed() + "_description",
         pin, TxtEdit, this, (post_edit) post_edit_description, edits);
}

void PinDialog::post_edit_description(PinDialog * d, QString s)
{
    d->comment->setText(s);
}
