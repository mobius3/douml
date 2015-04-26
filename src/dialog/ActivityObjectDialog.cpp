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
#include "ActivityObjectDialog.h"
#include "ActivityObjectData.h"
#include "BrowserActivityObject.h"
#include "BrowserView.h"
#include "BrowserClass.h"
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
QSize ActivityObjectDialog::previous_size;

ActivityObjectDialog::ActivityObjectDialog(ActivityObjectData * d, const char * what,
                                           QStringList & st)
    : TabDialog(0, 0, FALSE, Qt::WA_DeleteOnClose), data(d)
{
    d->browser_node->edit_start();

    if (d->browser_node->is_writable()) {
        setOkButton(TR("OK"));
        setCancelButton(TR("Cancel"));
    }
    else {
        setOkButton(QString());
        setCancelButton(TR("Close"));
    }

    visit = !hasOkButton();
    setWindowTitle((QString(what) + " dialog"));

    GridBox * grid;
    HHBox * htab;
    QString s;

    // general tab

    grid = new GridBox(2, this);
    umltab = grid;
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(TR("name :"), grid));
    grid->addWidget(edname = new LineEdit(data->name(), grid));
    edname->setReadOnly(visit);

    QFont font = edname->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);

    grid->addWidget(new QLabel(TR("stereotype : "), grid));
    grid->addWidget(edstereotype = new QComboBox(grid));
    edstereotype->setEditable(!visit);
    edstereotype->addItem(toUnicode(data->stereotype));

    if (! visit) {
        edstereotype->addItems(st);
        edstereotype->addItems(ProfiledStereotypes::defaults(UmlActivityObject));
        edstereotype->setAutoCompletion(completion());
    }

    edstereotype->setCurrentIndex(0);

    QSizePolicy sp = edstereotype->sizePolicy();

    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    edstereotype->setSizePolicy(sp);

    SmallPushButton* sButton;
    connect( sButton= new SmallPushButton(TR("type :"), grid), SIGNAL(clicked()),
            this, SLOT(menu_type()));
    grid->addWidget(sButton);

    grid->addWidget(edtype = new QComboBox(grid));
    edtype->setEditable(!visit);
    edtype->addItem(data->get_type().get_full_type());

    if (!visit) {
        BrowserClass::instances(nodes);
        nodes.full_names(list);

        edtype->addItems(GenerationSettings::basic_types());
        offset = edtype->count();
        edtype->addItems(list);
        edtype->setAutoCompletion(completion());

        // search for the view containing the activity
        view = d->browser_node;

        do {
            view = (BrowserNode *) view->parent();
        }
        while (view->get_type() != UmlActivity);

        view = (BrowserNode *) view->parent();
    }

    edtype->setCurrentIndex(0);
    edtype->setSizePolicy(sp);

    grid->addWidget(new QLabel(TR("multiplicity : "), grid));
    grid->addWidget(htab = new HHBox(grid));
    htab->addWidget(edmultiplicity = new QComboBox(htab));
    edmultiplicity->setEditable(!visit);
    edmultiplicity->setSizePolicy(sp);
    edmultiplicity->addItem(data->get_multiplicity());

    if (!visit) {
        edmultiplicity->addItem("1");
        edmultiplicity->addItem("0..1");
        edmultiplicity->addItem("*");
        edmultiplicity->addItem("1..*");
    }

    htab->addWidget(new QLabel(TR("   ordering : "), htab));
    htab->addWidget(edordering = new QComboBox(htab));

    UmlOrderingKind o = data->get_ordering();

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

    grid->addWidget(new QLabel(TR("in state : "), grid));
    grid->addWidget(htab = new HHBox(grid));
    htab->addWidget(edin_state = new LineEdit(data->in_state, htab));
    edin_state->setReadOnly(visit);

    htab->addWidget(new QLabel("  ", htab));
    htab->addWidget(is_control_cb = new QCheckBox(TR("is control"), htab));

    if (data->is_control)
        is_control_cb->setChecked(TRUE);

    is_control_cb->setDisabled(visit);

    VVBox * vtab;
    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(TR("description :"), vtab));

    if (! visit) {
        connect(sButton = new SmallPushButton(TR("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_description()));
        vtab->addWidget(sButton);
    }

    grid->addWidget(comment = new MultiLineEdit(grid));
    comment->setReadOnly(visit);
    comment->setText(data->browser_node->get_comment());
    comment->setFont(font);

    addTab(grid, "Uml");

    // UML / OCL
    init_tab(ocltab, eduml_selection, data->uml_selection, "Ocl",
             SLOT(edit_uml_selection()), TRUE);

    // C++
    init_tab(cppTab, edcpp_selection, data->cpp_selection, "C++",
             SLOT(edit_cpp_selection()),
             GenerationSettings::cpp_get_default_defs());

    // Java
    init_tab(javatab, edjava_selection, data->java_selection, "Java",
             SLOT(edit_java_selection()),
             GenerationSettings::java_get_default_defs());

    // USER : list key - value

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(kvtable = new KeyValuesTable(data->browser_node, grid, visit));
    addTab(grid, TR("Properties"));

    //

    connect(this, SIGNAL(currentChanged(QWidget *)),
            this, SLOT(change_tabs(QWidget *)));

    open_dialog(this);
}

void ActivityObjectDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::limitsize_center(this, previous_size, 0.8, 0.8);
}

ActivityObjectDialog::~ActivityObjectDialog()
{
    data->browser_node->edit_end();
    previous_size = size();

    foreach (BodyDialog *dialog, edits)
        dialog->close();
    edits.clear();

    close_dialog(this);
}

void ActivityObjectDialog::change_tabs(QWidget * w)
{
    if (! visit) {
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

void ActivityObjectDialog::init_tab(QWidget *& w, MultiLineEdit *& ed,
                                    const char * v, const char * lbl,
                                    const char * sl, bool enabled)
{
    bool visit = !hasOkButton();
    GridBox * grid = new GridBox(2, this);

    w = grid;
    grid->setMargin(5);
    grid->setSpacing(5);

    VVBox * vtab;
    grid->addWidget(vtab = new VVBox(grid));

    vtab->addWidget(new QLabel(TR("selection : "), vtab));

    SmallPushButton *sButton;
    if (! visit)
    {
        connect(sButton = new SmallPushButton(TR("Editor"), vtab), SIGNAL(clicked()), this, sl);
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

void ActivityObjectDialog::menu_type()
{
    QMenu m(0);

    MenuFactory::addItem(m, TR("Choose"), -1);
    m.addSeparator();

    int index = list.indexOf(edtype->currentText().trimmed());

    if (index != -1)
        MenuFactory::addItem(m, TR("Select in browser"), 0);

    BrowserNode * bn = 0;

    if (! visit) {
        bn = BrowserView::selected_item();

        if ((bn != 0) && (bn->get_type() == UmlClass) && !bn->deletedp())
            MenuFactory::addItem(m, TR("Choose class selected in browser"), 1);
        else
            bn = 0;

        MenuFactory::addItem(m, TR("Create class and choose it"), 2);
    }

    if (!visit || (index != -1) || (bn != 0)) {
        QAction *retActon = m.exec(QCursor::pos());
        if(retActon)
        {
            switch (retActon->data().toInt()) {
            case 0:
                nodes.at(index)->select_in_browser();
                break;

            case 2:
                bn = BrowserClass::add_class(FALSE, view);

                if (bn == 0)
                    return;

                bn->select_in_browser();

                // no break
            case 1: {
                QString s = bn->full_name(TRUE);

                if ((index = list.indexOf(s)) == -1) {
                    // new class, may be created through an other dialog
                    QStringList::Iterator iter = list.begin();
                    QStringList::Iterator iter_end = list.end();

                    index = 0;

                    while ((iter != iter_end) && (*iter < s)) {
                        ++iter;
                        index += 1;
                    }

                    nodes.insert((unsigned) index, bn);
                    list.insert(iter, s);
                    edtype->insertItem(index + offset, s);
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

void ActivityObjectDialog::edit_description()
{
    edit(comment->text(), edname->text().trimmed() + "_description",
         data, TxtEdit, this, (post_edit) post_edit_description, edits);
}

void ActivityObjectDialog::post_edit_description(ActivityObjectDialog * d, QString s)
{
    d->comment->setText(s);
}

#define DEF_EDIT(lang, Lang) \
    void ActivityObjectDialog::edit_##lang##_selection() {	\
    edit(ed##lang##_selection->text(), "object_"#lang"_selection", data, Lang,  \
    this, (post_edit) post_edit_##lang##_##selection, edits);	\
    } \
    \
    void ActivityObjectDialog::post_edit_##lang##_selection(ActivityObjectDialog * d, QString s) \
{ \
    d->ed##lang##_selection->setText(s); \
    }

DEF_EDIT(uml, TxtEdit)
DEF_EDIT(cpp, CppEdit)
DEF_EDIT(java, JavaEdit)

void ActivityObjectDialog::accept()
{
    if (!check_edits(edits))
        return;

    BrowserNode * bn = data->browser_node;
    QString s = edname->text().trimmed();

    bn->set_name(s);

    bool newst = data->set_stereotype(fromUnicode(edstereotype->currentText().trimmed()));
    AType t;

    s = edtype->currentText().trimmed();

    if (!s.isEmpty()) {
        int index = list.indexOf(s);

        if (index >= 0)
            t.type = (BrowserClass *) nodes.at(index);
        else
            t.explicit_type = s;
    }

    data->set_type(t);
    data->multiplicity =
            edmultiplicity->currentText().trimmed();
    data->ordering = ordering(edordering->currentText().toLatin1().constData());
    data->is_control = is_control_cb->isChecked();
    data->in_state = edin_state->text().trimmed();
    data->uml_selection = eduml_selection->text().trimmed();
    data->cpp_selection = edcpp_selection->text().trimmed();
    data->java_selection = edjava_selection->text().trimmed();

    bn->set_comment(comment->text());
    UmlWindow::update_comment_if_needed(bn);

    kvtable->updateNodeFromThis(bn);

    ProfiledStereotypes::modified(bn, newst);

    bn->modified();
    bn->package_modified();
    data->modified();

    TabDialog::accept();
}
