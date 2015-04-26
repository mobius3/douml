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
#include <qpushbutton.h>
#include <qcursor.h>
#include "ActivityActionDialog.h"
#include "BrowserActivityAction.h"
#include "BrowserClass.h"
#include "BrowserOperation.h"
#include "OperationData.h"
#include "BrowserState.h"
#include "BrowserActivity.h"
#include "KeyValueTable.h"
#include "UmlPixmap.h"
#include "DialogUtil.h"
#include "strutil.h"
#include "UmlDesktop.h"
#include "BodyDialog.h"
#include "UmlWindow.h"
#include "BrowserView.h"
#include "GenerationSettings.h"
#include "ProfiledStereotypes.h"
#include "translate.h"
#include "menufactory.h"

QSize ActivityActionDialog::previous_size;

static QString pretty_kind(UmlActionKind k)
{
    QString s = stringify(k);
    int index = 0;

    while ((index = s.indexOf('_', index)) != -1)
        s.replace(index, 1, " ");

    return s;
}

static GridBox * mkgrid(TabDialog * d, QString name = QString())
{
    GridBox * grid = new GridBox(2, d, name);
    grid->setMargin(5);
    grid->setSpacing(5);

    return grid;
}

ActivityActionDialog::ActivityActionDialog(ActivityActionData * a)
    : TabDialog(0, 0, FALSE, Qt::WA_DeleteOnClose), act(a)
{
    a->browser_node->edit_start();

    if (a->browser_node->is_writable()) {
        setOkButton(TR("OK"));
        setCancelButton(TR("Cancel"));
    }
    else {
        setOkButton(QString());
        setCancelButton(TR("Close"));
    }

    setWindowTitle(TR("Activity Action dialog"));
    visit = !hasOkButton();

    current_type = act->get_action_kind();

    BrowserActivityAction * action =
            (BrowserActivityAction *) a->get_browser_node();
    GridBox * grid;

    //
    // general tab
    //

    grid = mkgrid(this);
    umltab = grid;

    grid->addWidget(new QLabel(TR("name : "), grid));
    grid->addWidget(edname = new LineEdit(action->get_name(), grid));
    edname->setReadOnly(visit);

    grid->addWidget(new QLabel(TR("stereotype : "), grid));
    grid->addWidget(edstereotype = new QComboBox(grid));
    edstereotype->setEditable(!visit);
    edstereotype->addItem(toUnicode(action->get_stereotype()));

    if (!visit) {
        edstereotype->addItems(BrowserActivityAction::default_stereotypes());
        edstereotype->addItems(ProfiledStereotypes::defaults(UmlActivityAction));
        edstereotype->setAutoCompletion(completion());
    }

    edstereotype->setCurrentIndex(0);
    QSizePolicy sp = edstereotype->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    edstereotype->setSizePolicy(sp);

    grid->addWidget(new QLabel(TR("kind : "), grid));
    grid->addWidget(edtype = new QComboBox(grid));

    if (visit) {
        // action kind cannot be changed
        edtype->addItem(pretty_kind(current_type));
    }
    else {
        int index;

        for (index = UmlOpaqueAction; index <= UmlReduceAction; index += 1) {
            edtype->addItem(pretty_kind((UmlActionKind) index));

            if (index == (int) current_type)
                edtype->setCurrentIndex(index);
        }

        connect(edtype, SIGNAL(activated(int)), this, SLOT(edTypeActivated(int)));
    }

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
    comment->setText(action->get_comment());

    grid->addWidget(vtab = new VVBox(grid));
    vtab->addWidget(new QLabel(TR("constraint :"), vtab));

    if (! visit) {
        connect(sButton = new SmallPushButton(TR("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_constraint()));
        vtab->addWidget(sButton);
    }

    grid->addWidget(constraint = new MultiLineEdit(grid));
    constraint->setReadOnly(visit);
    constraint->setText(act->constraint);

    addTab(grid, "Uml");

    //
    // action kind specific
    //

    BrowserClass::instances(classes);
    classes.full_names(class_names);

    BrowserState::instances(behaviors, FALSE);
    BrowserActivity::instances(behaviors, TRUE);
    behaviors.full_names(behavior_names);

    BrowserNode * bn = a->browser_node;

    do {
        // search for the view containing the activity
        bn = (BrowserNode *) bn->parent();
    }
    while (bn->get_type() != UmlActivity);

    bn = (BrowserNode *) bn->parent();

#define K(k) (current_type == Uml##k) ? ((k *) act->action) : 0

    opaque.init(this, act, K(OpaqueAction), edits, visit);
    acceptevent.init(this, act, K(AcceptEventAction), visit);
    sendobject.init(this, act, K(SendObjectAction), visit);
    unmarshall.init(this, act, K(UnmarshallAction), visit);
    valuespecification.init(this, act, K(ValueSpecificationAction), edits, visit);
    sendsignal.init(this, act, K(SendSignalAction), visit);
    broadcastsignal.init(this, act, K(BroadcastSignalAction), visit);
    readvariablevalue.init(this, act, K(ReadVariableValueAction),
                           classes, class_names, visit);
    clearvariablevalue.init(this, act, K(ClearVariableValueAction),
                            classes, class_names, visit);
    writevariablevalue.init(this, act, K(WriteVariableValueAction),
                            classes, class_names, visit);
    addvariablevalue.init(this, act, K(AddVariableValueAction),
                          classes, class_names, visit);
    removevariablevalue.init(this, act, K(RemoveVariableValueAction),
                             classes, class_names, visit);
    calloperation.init(this, act, K(CallOperationAction),
                       classes, class_names, visit);
    callbehavior.init(this, act, K(CallBehaviorAction),
                      behaviors, behavior_names, bn, visit);
    acceptcall.init(this, act, K(AcceptCallAction), visit);
    reply.init(this, act, K(ReplyAction), visit);
    createobject.init(this, act, K(CreateObjectAction), visit);
    destroyobject.init(this, act, K(DestroyObjectAction), visit);
    testidentity.init(this, act, K(TestIdentityAction), visit);
    raiseexception.init(this, act, K(RaiseExceptionAction), visit);
    reduce.init(this, act, K(ReduceAction),
                behaviors, behavior_names, bn, visit);

#undef K

    //
    // USER : list key - value
    //

    grid = mkgrid(this);

    grid->addWidget(kvtable = new KeyValuesTable(action, grid, visit));
    addTab(grid, TR("Properties"));

    //

    connect(this, SIGNAL(currentChanged(QWidget *)),
            this, SLOT(change_tabs(QWidget *)));

    open_dialog(this);
}

void ActivityActionDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::limitsize_center(this, previous_size, 0.8, 0.8);
}

ActivityActionDialog::~ActivityActionDialog()
{
    act->browser_node->edit_end();
    previous_size = size();

    foreach (BodyDialog *dialog, edits)
        dialog->close();
    edits.clear();

    close_dialog(this);
}

void ActivityActionDialog::change_tabs(QWidget * w)
{
    if (!visit && (w == umltab))
        edname->setFocus();
}

void ActivityActionDialog::edit_description()
{
    edit(comment->text(), "activity_action_description", act, TxtEdit,
         this, (post_edit) post_edit_description, edits);
}

void ActivityActionDialog::post_edit_description(ActivityActionDialog * d,
                                                 QString s)
{
    d->comment->setText(s);
}

void ActivityActionDialog::edit_constraint()
{
    edit(constraint->text(), edname->text().trimmed() + "_constraint",
         act, TxtEdit, this, (post_edit) post_edit_constraint, edits);
}

void ActivityActionDialog::post_edit_constraint(ActivityActionDialog * d, QString s)
{
    d->constraint->setText(s);
}

AnyActionDialog & ActivityActionDialog::get_dialog(int k)
{
    switch (k) {
    case UmlOpaqueAction:
        return opaque;

    case UmlAcceptEventAction:
        return acceptevent;

    case UmlReadVariableValueAction:
        return readvariablevalue;

    case UmlClearVariableValueAction:
        return clearvariablevalue;

    case UmlWriteVariableValueAction:
        return writevariablevalue;

    case UmlAddVariableValueAction:
        return addvariablevalue;

    case UmlRemoveVariableValueAction:
        return removevariablevalue;

    case UmlCallBehaviorAction:
        return callbehavior;

    case UmlCallOperationAction:
        return calloperation;

    case UmlSendObjectAction:
        return sendobject;

    case UmlSendSignalAction:
        return sendsignal;

    case UmlBroadcastSignalAction:
        return broadcastsignal;

    case UmlUnmarshallAction:
        return unmarshall;

    case UmlValueSpecificationAction:
        return valuespecification;

    case UmlAcceptCallAction:
        return acceptcall;

    case UmlReplyAction:
        return reply;

    case UmlCreateObjectAction:
        return createobject;

    case UmlDestroyObjectAction:
        return destroyobject;

    case UmlTestIdentityAction:
        return testidentity;

    case UmlRaiseExceptionAction:
        return raiseexception;

    default: // UmlReduceAction
        return reduce;
    }
}

void ActivityActionDialog::edTypeActivated(int k)
{
    get_dialog(k).goes(get_dialog(current_type));
    current_type = (UmlActionKind) k;
}

void ActivityActionDialog::accept()
{
    if (!check_edits(edits) || !kvtable->check_unique())
        return;

    BrowserActivityAction * bn = (BrowserActivityAction *) act->browser_node;
    QString s;

    s = edname->text().trimmed();

    if ((s != bn->get_name()) &&
            ((BrowserNode *) bn->parent())->wrong_child_name(s, UmlActivityAction,
                                                             bn->allow_spaces(),
                                                             bn->allow_empty()))
        msg_critical(TR("Error"), s + TR("\n\nillegal name or already used"));
    else {
        act->undepend();
        bn->set_name(s);

        bool newst = act->set_stereotype(fromUnicode(edstereotype->currentText().trimmed()));

        QString ocl_pre;
        QString ocl_post;
        QString cpp_pre;
        QString cpp_post;
        QString java_pre;
        QString java_post;
        bool changed = (act->get_action_kind() != current_type);

        if (changed)
            act->set_action_kind(current_type);

        switch (current_type) {
#define CASE(t, v)  \
        case Uml##t :   \
    v.get_cond(ocl_pre, ocl_post, cpp_pre, cpp_post, java_pre, java_post);  \
    if (v.update((t *) act->action) || changed) { \
    /* pins changed */	\
    bn->set_pins(); \
        }	\
    break

        CASE(OpaqueAction, opaque);
        CASE(AcceptEventAction, acceptevent);
        CASE(SendObjectAction, sendobject);
        CASE(UnmarshallAction, unmarshall);
        CASE(ValueSpecificationAction, valuespecification);
        CASE(SendSignalAction, sendsignal);
        CASE(BroadcastSignalAction, broadcastsignal);
        CASE(ReadVariableValueAction, readvariablevalue);
        CASE(ClearVariableValueAction, clearvariablevalue);
        CASE(WriteVariableValueAction, writevariablevalue);
        CASE(AddVariableValueAction, addvariablevalue);
        CASE(RemoveVariableValueAction, removevariablevalue);
        CASE(CallOperationAction, calloperation);
        CASE(CallBehaviorAction, callbehavior);
        CASE(AcceptCallAction, acceptcall);
        CASE(ReplyAction, reply);
        CASE(CreateObjectAction, createobject);
        CASE(DestroyObjectAction, destroyobject);
        CASE(TestIdentityAction, testidentity);
        CASE(RaiseExceptionAction, raiseexception);
        CASE(ReduceAction, reduce);

#undef CASE

        default:
            break;
        }

        act->uml_condition.first = ocl_pre;
        act->uml_condition.second = ocl_post;
        act->cpp_condition.first = cpp_pre;
        act->cpp_condition.second = cpp_post;
        act->java_condition.first = java_pre;
        act->java_condition.second = java_post;

        act->update_depend();

        bn->set_comment(comment->text());
        UmlWindow::update_comment_if_needed(bn);

        act->constraint = constraint->trimmedText();

        kvtable->updateNodeFromThis(bn);

        ProfiledStereotypes::modified(bn, newst);

        bn->modified();   // call action->modified()
        bn->package_modified();

        TabDialog::accept();
    }
}

// ActionCondDialog

void ActionCondDialog::init(GridBox * grid, ActivityActionData * d,
                            DrawingLanguage lang, bool visit)
{
    grid->addWidget(new QLabel(QObject::tr("Pre\ncondition : "), grid));
    grid->addWidget(edpre = new MultiLineEdit(grid));
    edpre->setText(d->get_precond(lang));

    grid->addWidget(new QLabel(QObject::tr("Post\ncondition : "), grid));
    grid->addWidget(edpost = new MultiLineEdit(grid));
    edpost->setText(d->get_postcond(lang));

    if (visit) {
        edpre->setReadOnly(TRUE);
        edpost->setReadOnly(TRUE);
    }
}

void ActionCondDialog::get(QString & pre, QString & post) const
{
    pre = edpre->text().trimmed();
    post = edpost->text().trimmed();
}

void ActionCondDialog::set(QString pre, QString post)
{
    edpre->setText(pre);
    edpost->setText(post);
}


// AnyActionDialog

AnyActionDialog::AnyActionDialog()
    : ocl_grid(0), cpp_grid(0), java_grid(0)
{
}

void AnyActionDialog::init(TabDialog * t, ActivityActionData * act,
                           void * d, bool visit)
{
    // just add the pre/post condition
    td = t;

    // ocl

    ocl_grid = mkgrid(t);
    ocl_cond.init(ocl_grid, act, UmlView, visit);

    if (d != 0)
        ocl_cond.set(act->get_precond(UmlView), act->get_postcond(UmlView));

    // note : must add then remove rather than doing nothing
    // else some sub widget will be wrong placed
    t->addTab(ocl_grid, "Ocl");

    if (d == 0)
        t->removePage(ocl_grid);

    // cpp & java
    init_cpp(t, act, d, visit);
    init_java(t, act, d, visit);
}

void AnyActionDialog::init_cpp(TabDialog * t, ActivityActionData * act,
                               void * d, bool visit)
{
    // cpp

    cpp_grid = mkgrid(t);
    cpp_cond.init(cpp_grid, act, CppView, visit);

    if (d != 0)
        cpp_cond.set(act->get_precond(CppView), act->get_postcond(CppView));

    // note : must add then remove rather than doing nothing
    // else some sub widget will be wrong placed
    t->addTab(cpp_grid, "C++");

    if ((d == 0) || !GenerationSettings::cpp_get_default_defs())
        t->removePage(cpp_grid);
}

void AnyActionDialog::init_java(TabDialog * t, ActivityActionData * act,
                                void * d, bool visit)
{
    // java

    java_grid = mkgrid(t);
    java_cond.init(java_grid, act, JavaView, visit);

    if (d != 0)
        java_cond.set(act->get_precond(JavaView), act->get_postcond(JavaView));

    // note : must add then remove rather than doing nothing
    // else some sub widget will be wrong placed
    t->addTab(java_grid, "Java");

    if ((d == 0) || !GenerationSettings::java_get_default_defs())
        t->removePage(java_grid);
}

bool AnyActionDialog::update(void *)
{
    // do nothing
    return FALSE;
}

void AnyActionDialog::goes(AnyActionDialog & previous)
{
    QString pre;
    QString post;

    previous.ocl_cond.get(pre, post);
    ocl_cond.set(pre, post);
    td->insertTab(ocl_grid, ocl_grid->name("Ocl"), 1);
    td->removePage(previous.ocl_grid);

    previous.cpp_cond.get(pre, post);
    cpp_cond.set(pre, post);
    td->insertTab(cpp_grid, cpp_grid->name("C++"), 2);
    td->removePage(previous.cpp_grid);

    previous.java_cond.get(pre, post);
    java_cond.set(pre, post);
    td->insertTab(java_grid, java_grid->name("Java"), 3);
    td->removePage(previous.java_grid);
}

void AnyActionDialog::get_cond(QString & ocl_pre, QString & ocl_post,
                               QString & cpp_pre, QString & cpp_post,
                               QString & java_pre, QString & java_post) const
{
    ocl_cond.get(ocl_pre, ocl_post);
    cpp_cond.get(cpp_pre, cpp_post);
    java_cond.get(java_pre, java_post);
}

// opaque

void OpaqueDialog::init(TabDialog * t, ActivityActionData * act,
                        OpaqueAction * d, QList<BodyDialog *> & e, bool visit)
{
    edits = &e;
    td = t;

    // ocl

    ocl_grid = mkgrid(t);

    VVBox * vtab;
    ocl_grid->addWidget(vtab = new VVBox(ocl_grid));

    vtab->addWidget(new QLabel(TR("Behavior : "), vtab));
    SmallPushButton* sButton;
    if (! visit)
    {
        connect(sButton = new SmallPushButton(TR("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_ocl()));
        vtab->addWidget(sButton);
    }

    ocl_grid->addWidget(ocl_beh = new MultiLineEdit(ocl_grid));

    if (visit)
        ocl_beh->setReadOnly(TRUE);

    ocl_cond.init(ocl_grid, act, UmlView, visit);

    if (d != 0) {
        ocl_cond.set(act->get_precond(UmlView), act->get_postcond(UmlView));
        ocl_beh->setText(d->uml_behavior);
    }

    t->addTab(ocl_grid, "Ocl");

    if (d == 0)
        t->removePage(ocl_grid);

    // cpp

    cpp_grid = mkgrid(t);

    cpp_grid->addWidget(vtab = new VVBox(cpp_grid));
    vtab->addWidget(new QLabel(TR("Behavior : "), vtab));

    if (! visit)
    {
        connect(sButton = new SmallPushButton(TR("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_cpp()));
        vtab->addWidget(sButton);
    }

    cpp_grid->addWidget(cpp_beh = new MultiLineEdit(cpp_grid));

    if (visit)
        cpp_beh->setReadOnly(TRUE);

    cpp_cond.init(cpp_grid, act, CppView, visit);

    if (d != 0) {
        cpp_cond.set(act->get_precond(CppView), act->get_postcond(CppView));
        cpp_beh->setText(d->cpp_behavior);
    }

    t->addTab(cpp_grid, "C++");

    if ((d == 0) || !GenerationSettings::cpp_get_default_defs())
        t->removePage(cpp_grid);

    // java

    java_grid = mkgrid(t);

    java_grid->addWidget(vtab = new VVBox(java_grid));
    vtab->addWidget(new QLabel(TR("Behavior : "), vtab));

    if (! visit)
    {
        connect(sButton = new SmallPushButton(TR("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_java()));
        vtab->addWidget(sButton);
    }

    java_grid->addWidget(java_beh = new MultiLineEdit(java_grid));

    if (visit)
        java_beh->setReadOnly(TRUE);

    java_cond.init(java_grid, act, JavaView, visit);

    if (d != 0) {
        java_cond.set(act->get_precond(JavaView), act->get_postcond(JavaView));
        java_beh->setText(d->java_behavior);
    }

    t->addTab(java_grid, "Java");

    if ((d == 0) || !GenerationSettings::java_get_default_defs())
        t->removePage(java_grid);
}

bool OpaqueDialog::update(OpaqueAction * a)
{
    a->uml_behavior = ocl_beh->text().trimmed();
    a->cpp_behavior = cpp_beh->text().trimmed();
    a->java_behavior = java_beh->text().trimmed();

    return FALSE;
}

void OpaqueDialog::edit_ocl()
{
    edit(ocl_beh->text(), "activity_action_ocl_behavior", this, TxtEdit,
         td, (post_edit) post_edit_ocl, *edits);
}

void OpaqueDialog::post_edit_ocl(ActivityActionDialog * d, QString s)
{
    d->opaque_dialog().ocl_beh->setText(s);
}

void OpaqueDialog::edit_cpp()
{
    edit(cpp_beh->text(), "activity_action_cpp_behavior", this, TxtEdit,
         td, (post_edit) post_edit_cpp, *edits);
}

void OpaqueDialog::post_edit_cpp(ActivityActionDialog * d, QString s)
{
    d->opaque_dialog().cpp_beh->setText(s);
}

void OpaqueDialog::edit_java()
{
    edit(java_beh->text(), "activity_action_java_behavior", this, TxtEdit,
         td, (post_edit) post_edit_java, *edits);
}

void OpaqueDialog::post_edit_java(ActivityActionDialog * d, QString s)
{
    d->opaque_dialog().java_beh->setText(s);
}

// Accept Event

void AcceptEventDialog::init(TabDialog * t, ActivityActionData * act,
                             AcceptEventAction * d, bool visit)
{
    td = t;

    // ocl

    ocl_grid = mkgrid(t, QObject::tr("trigger - Ocl"));

    ocl_grid->addWidget(new QLabel("", ocl_grid));
    BButtonGroup * grp;
    ocl_grid->addWidget(grp = new BButtonGroup(2, Qt::Horizontal, QString(), ocl_grid));

    grp->addWidget(unmarshall_cb = new QCheckBox(QObject::tr("unmarshall"), grp));
    unmarshall_cb->setDisabled(visit);

    grp->addWidget(timeevent_cb = new QCheckBox(QObject::tr("time event"), grp));
    timeevent_cb->setDisabled(visit);

    ocl_grid->addWidget(new QLabel(QObject::tr("trigger : "), ocl_grid));
    ocl_grid->addWidget(uml_trigger = new LineEdit(ocl_grid));
    uml_trigger->setReadOnly(visit);

    ocl_cond.init(ocl_grid, act, UmlView, visit);

    if (d != 0) {
        ocl_cond.set(act->get_precond(UmlView), act->get_postcond(UmlView));
        unmarshall_cb->setChecked(d->unmarshall);
        timeevent_cb->setChecked(d->timeevent);
        uml_trigger->setText(d->uml_trigger);
    }

    t->addTab(ocl_grid, QObject::tr("trigger - Ocl"));

    if (d == 0)
        t->removePage(ocl_grid);

    // cpp

    cpp_grid = mkgrid(t, QObject::tr("trigger - C++"));

    cpp_grid->addWidget(new QLabel(QObject::tr("trigger : "), cpp_grid));
    cpp_grid->addWidget(cpp_trigger = new LineEdit(cpp_grid));

    cpp_cond.init(cpp_grid, act, CppView, visit);

    if (d != 0) {
        cpp_cond.set(act->get_precond(CppView), act->get_postcond(CppView));
        cpp_trigger->setText(d->cpp_trigger);
    }

    t->addTab(cpp_grid, QObject::tr("trigger - C++"));

    if ((d == 0) || !GenerationSettings::cpp_get_default_defs())
        t->removePage(cpp_grid);

    // java

    java_grid = mkgrid(t, QObject::tr("trigger - Java"));

    java_grid->addWidget(new QLabel(QObject::tr("trigger : "), java_grid));
    java_grid->addWidget(java_trigger = new LineEdit(java_grid));

    java_cond.init(java_grid, act, JavaView, visit);

    if (d != 0) {
        java_cond.set(act->get_precond(JavaView), act->get_postcond(JavaView));
        java_trigger->setText(d->java_trigger);
    }

    t->addTab(java_grid, QObject::tr("trigger - Java"));

    if ((d == 0) || !GenerationSettings::java_get_default_defs())
        t->removePage(java_grid);
}

bool AcceptEventDialog::update(AcceptEventAction * a)
{
    a->unmarshall = unmarshall_cb->isChecked();
    a->timeevent = timeevent_cb->isChecked();
    a->uml_trigger = uml_trigger->text().trimmed();
    a->cpp_trigger = cpp_trigger->text().trimmed();
    a->java_trigger = java_trigger->text().trimmed();

    return FALSE;
}

// value specification

void ValueSpecificationDialog::init(TabDialog * t, ActivityActionData * act,
                                    ValueSpecificationAction * d,
                                    QList<BodyDialog *> & e, bool visit)
{
    edits = &e;
    td = t;

    // ocl

    ocl_grid = mkgrid(t, TR("value - Ocl"));

    VVBox * vtab;
    ocl_grid->addWidget(vtab = new VVBox(ocl_grid));

    vtab->addWidget(new QLabel(TR("Value : "), vtab));

    SmallPushButton* sButton;
    if (! visit)
    {
        connect(sButton = new SmallPushButton(TR("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_ocl()));
        vtab->addWidget(sButton);
    }

    ocl_grid->addWidget(ocl_val = new MultiLineEdit(ocl_grid));

    if (visit)
        ocl_val->setReadOnly(TRUE);

    ocl_cond.init(ocl_grid, act, UmlView, visit);

    if (d != 0) {
        ocl_cond.set(act->get_precond(UmlView), act->get_postcond(UmlView));
        ocl_val->setText(d->uml_value);
    }

    t->addTab(ocl_grid, TR("value - Ocl"));

    if (d == 0)
        t->removePage(ocl_grid);

    // cpp

    cpp_grid = mkgrid(t, TR("value - C++"));

    cpp_grid->addWidget(vtab = new VVBox(cpp_grid));
    vtab->addWidget(new QLabel(TR("Value : "), vtab));

    if (! visit)
    {
        connect(sButton = new SmallPushButton(TR("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_cpp()));
        vtab->addWidget(sButton);
    }

    cpp_grid->addWidget(cpp_val = new MultiLineEdit(cpp_grid));

    if (visit)
        cpp_val->setReadOnly(TRUE);

    cpp_cond.init(cpp_grid, act, CppView, visit);

    if (d != 0) {
        cpp_cond.set(act->get_precond(CppView), act->get_postcond(CppView));
        cpp_val->setText(d->cpp_value);
    }

    t->addTab(cpp_grid, TR("value - C++"));

    if ((d == 0) || !GenerationSettings::cpp_get_default_defs())
        t->removePage(cpp_grid);

    // java

    java_grid = mkgrid(t, TR("value - Java"));

    java_grid->addWidget(vtab = new VVBox(java_grid));
    vtab->addWidget(new QLabel(TR("Value : "), vtab));

    if (! visit)
    {
        connect(sButton = new SmallPushButton(TR("Editor"), vtab), SIGNAL(clicked()),
                this, SLOT(edit_java()));
        vtab->addWidget(sButton);
    }

    java_grid->addWidget(java_val = new MultiLineEdit(java_grid));

    if (visit)
        java_val->setReadOnly(TRUE);

    java_cond.init(java_grid, act, JavaView, visit);

    if (d != 0) {
        java_cond.set(act->get_precond(JavaView), act->get_postcond(JavaView));
        java_val->setText(d->java_value);
    }

    t->addTab(java_grid, TR("value - Java"));

    if ((d == 0) || !GenerationSettings::java_get_default_defs())
        t->removePage(java_grid);
}

bool ValueSpecificationDialog::update(ValueSpecificationAction * a)
{
    a->uml_value = ocl_val->text().trimmed();
    a->cpp_value = cpp_val->text().trimmed();
    a->java_value = java_val->text().trimmed();

    return FALSE;
}

void ValueSpecificationDialog::edit_ocl()
{
    edit(ocl_val->text(), "activity_action_ocl_value", this, TxtEdit,
         td, (post_edit) post_edit_ocl, *edits);
}

void ValueSpecificationDialog::post_edit_ocl(ActivityActionDialog * d, QString s)
{
    d->valuespecification_dialog().ocl_val->setText(s);
}

void ValueSpecificationDialog::edit_cpp()
{
    edit(cpp_val->text(), "activity_action_cpp_value", this, TxtEdit,
         td, (post_edit) post_edit_cpp, *edits);
}

void ValueSpecificationDialog::post_edit_cpp(ActivityActionDialog * d, QString s)
{
    d->valuespecification_dialog().cpp_val->setText(s);
}

void ValueSpecificationDialog::edit_java()
{
    edit(java_val->text(), "activity_action_java_value", this, TxtEdit,
         td, (post_edit) post_edit_java, *edits);
}

void ValueSpecificationDialog::post_edit_java(ActivityActionDialog * d, QString s)
{
    d->valuespecification_dialog().java_val->setText(s);
}

// Send signal

void SendSignalDialog::init(TabDialog * t, ActivityActionData * act,
                            SendSignalAction * d, bool visit)
{
    td = t;

    // ocl

    ocl_grid = mkgrid(t, QObject::tr("signal - Ocl"));

    ocl_grid->addWidget(new QLabel(QObject::tr("signal : "), ocl_grid));
    ocl_grid->addWidget(ocl_signal = new LineEdit(ocl_grid));
    ocl_signal->setReadOnly(visit);

    ocl_cond.init(ocl_grid, act, UmlView, visit);

    if (d != 0) {
        ocl_cond.set(act->get_precond(UmlView), act->get_postcond(UmlView));
        ocl_signal->setText(d->ocl_signal);
    }

    t->addTab(ocl_grid, QObject::tr("signal - Ocl"));

    if (d == 0)
        t->removePage(ocl_grid);

    // cpp

    cpp_grid = mkgrid(t, QObject::tr("signal - C++"));

    cpp_grid->addWidget(new QLabel(QObject::tr("signal : "), cpp_grid));
    cpp_grid->addWidget(cpp_signal = new LineEdit(cpp_grid));

    cpp_cond.init(cpp_grid, act, CppView, visit);

    if (d != 0) {
        cpp_cond.set(act->get_precond(CppView), act->get_postcond(CppView));
        cpp_signal->setText(d->cpp_signal);
    }

    t->addTab(cpp_grid, QObject::tr("signal - C++"));

    if ((d == 0) || !GenerationSettings::cpp_get_default_defs())
        t->removePage(cpp_grid);

    // java

    java_grid = mkgrid(t, QObject::tr("signal - Java"));

    java_grid->addWidget(new QLabel(QObject::tr("signal : "), java_grid));
    java_grid->addWidget(java_signal = new LineEdit(java_grid));

    java_cond.init(java_grid, act, JavaView, visit);

    if (d != 0) {
        java_cond.set(act->get_precond(JavaView), act->get_postcond(JavaView));
        java_signal->setText(d->java_signal);
    }

    t->addTab(java_grid, QObject::tr("signal - Java"));

    if ((d == 0) || !GenerationSettings::java_get_default_defs())
        t->removePage(java_grid);
}

bool SendSignalDialog::update(SendSignalAction * a)
{
    a->ocl_signal = ocl_signal->text().trimmed();
    a->cpp_signal = cpp_signal->text().trimmed();
    a->java_signal = java_signal->text().trimmed();

    return FALSE;
}

// access & change variable value working classes

void AccessVariableValueDialog::init(TabDialog * t, ActivityActionData * act,
                                     AccessVariableValueAction * d,
                                     BrowserNodeList & cl,
                                     QStringList & clstr, bool ro)
{
    td = t;
    classes = &cl;
    class_names = &clstr;
    visit = ro;

    // ocl

    if (ocl_grid == 0)
        ocl_grid = mkgrid(t, TR("variable - Ocl"));

    ocl_grid->addWidget(new QLabel(TR("class : "), ocl_grid));
    ocl_grid->addWidget(class_co = new QComboBox(ocl_grid));
    SmallPushButton* sButton;
    connect(sButton = new SmallPushButton(TR("variable :"), ocl_grid), SIGNAL(clicked()),
            this, SLOT(menu_var()));
    ocl_grid->addWidget(sButton);
    ocl_grid->addWidget(var_co = new QComboBox(ocl_grid));

    ocl_cond.init(ocl_grid, act, UmlView, visit);

    if (!visit) {
        class_co->addItem("");
        var_co->addItem("");
        class_co->setAutoCompletion(completion());
        var_co->setAutoCompletion(completion());

        class_co->addItems(*class_names);
        connect(class_co, SIGNAL(activated(int)), this, SLOT(classChanged(int)));
    }

    if ((d != 0) && (d->variable != 0)) {
        if (visit) {
            class_co->addItem(((BrowserNode *) d->variable->parent())->full_name(TRUE));
            var_co->addItem(*(d->variable->pixmap(0)), d->variable->get_name());
            class_co->setCurrentIndex(0);
            var_co->setCurrentIndex(0);
        }
        else
            set(d->variable);

        ocl_cond.set(act->get_precond(UmlView), act->get_postcond(UmlView));
    }

    // note : must add then remove rather than doing nothing
    // else some sub widget will be wrong placed
    t->addTab(ocl_grid, TR("variable - Ocl"));

    if (d == 0)
        t->removePage(ocl_grid);

    // cpp & java
    init_cpp(t, act, d, visit);
    init_java(t, act, d, visit);
}

void AccessVariableValueDialog::classChanged(int)
{
    var_co->clear();
    var_co->addItem("");

    int index = class_names->indexOf(class_co->currentText());

    if (index != -1)
        insert_vars((BrowserClass *) classes->at(index));
}

void AccessVariableValueDialog::insert_vars(BrowserClass * c)
{
    // var_co contains "" and optionally a var's name
    vars.clear();
    var_names.clear();

    BrowserNode * child;

    for (child = c->firstChild(); child; child = child->nextSibling()) {
        if (!((BrowserNode *) child)->deletedp()) {
            switch (((BrowserNode *) child)->get_type()) {
            case UmlAssociation:
            case UmlDirectionalAssociation:
            case UmlAggregation:
            case UmlAggregationByValue:
            case UmlDirectionalAggregation:
            case UmlDirectionalAggregationByValue:
            case UmlAttribute:
                vars.append((BrowserNode *) child);
                var_names.append(((BrowserNode *) child)->get_name());
                var_co->addItem(*(((BrowserNode *) child)->pixmap(0)),
                                ((BrowserNode *) child)->get_name());
                break;

            default:
                break;
            }
        }
    }
}

bool AccessVariableValueDialog::update(AccessVariableValueAction * a)
{
    int index = var_names.indexOf(var_co->currentText());

    BrowserNode * old = a->variable;

    a->variable = (index != -1) ? vars.at(index) : 0;

    return old != a->variable;
}

void AccessVariableValueDialog::menu_var()
{
    QMenu m(0);

    MenuFactory::addItem(m, TR("Choose"), -1);
    m.addSeparator();

    int index = var_names.indexOf(var_co->currentText());

    if (index != -1)
        MenuFactory::addItem(m, TR("Select in browser"), 0);

    BrowserNode * bn = 0;
    BrowserClass * cl = 0;

    if (! visit) {
        bn = BrowserView::selected_item();

        if (bn != 0) {
            switch (bn->get_type()) {
            case UmlAssociation:
            case UmlDirectionalAssociation:
            case UmlAggregation:
            case UmlAggregationByValue:
            case UmlDirectionalAggregation:
            case UmlDirectionalAggregationByValue:
            case UmlAttribute:
                if (!bn->deletedp()) {
                    MenuFactory::addItem(m, TR("Choose variable selected in browser"), 1);
                    break;
                }

                // no break
            default:
                bn = 0;
            }
        }

        int index_cl = class_names->indexOf(class_co->currentText());

        if (index_cl != -1) {
            cl = (BrowserClass *) classes->at(index_cl);

            if (!cl->is_writable())
                cl = 0;
            else
                MenuFactory::addItem(m, TR("Create attribute and choose it"), 2);
        }
    }

    if ((index != -1) || (bn != 0) || (cl != 0)) {
        QAction *retActon = m.exec(QCursor::pos());
        if(retActon)
        {
            switch (retActon->data().toInt()) {
            case 0:
                vars.at(index)->select_in_browser();
                break;

            case 2: {
                const char * stereotype = cl->get_data()->get_stereotype();

                bn = cl->add_attribute(0,
                                       !strcmp(stereotype, "enum") ||
                                       !strcmp(stereotype, "enum_pattern"));

                if (bn == 0)
                    break;

                bn->select_in_browser();
            }

                // no break;
            case 1:
                var_co->clear();
                var_co->addItem("");
                set(bn);
                break;
            }
        }
    }
}

void AccessVariableValueDialog::set(BrowserNode * bn)
{
    BrowserClass * cl = (BrowserClass *) bn->parent();
    int index;

    if ((index = class_names->indexOf(cl->full_name(TRUE))) == -1)
        // new class, not managed
        return;

    class_co->setCurrentIndex(index + 1);
    insert_vars(cl);

    // var is in var_names
    var_co->setCurrentIndex(var_names.indexOf(bn->get_name()) + 1);
}

void ChangeVariableValueDialog::init(TabDialog * t, ActivityActionData * act,
                                     ChangeVariableValueAction * d,
                                     QString flg_name, BrowserNodeList & cl,
                                     QStringList & clstr, bool visit)
{
    ocl_grid = mkgrid(t, TR("variable - Ocl"));

    ocl_grid->addWidget(new QLabel("", ocl_grid));
    BButtonGroup * grp;
    ocl_grid->addWidget(grp = new BButtonGroup(2, Qt::Horizontal, QString(), ocl_grid));

    grp->addWidget(flag_cb = new QCheckBox(flg_name, grp));
    flag_cb->setDisabled(visit);

    AccessVariableValueDialog::init(t, act, d, cl, clstr, visit);

    if ((d != 0) && (d->variable != 0))
        flag_cb->setChecked(d->flag);
}

bool ChangeVariableValueDialog::update(ChangeVariableValueAction * a)
{
    a->flag = flag_cb->isChecked();
    return AccessVariableValueDialog::update(a);
}

// add variable value

void AddVariableValueDialog::init(TabDialog * t, ActivityActionData * act,
                                  AddVariableValueAction * d, BrowserNodeList & cl,
                                  QStringList & clstr, bool visit)
{
    ChangeVariableValueDialog::init(t, act, d, TR("replace all"), cl, clstr, visit);
}

// remove variable value

void RemoveVariableValueDialog::init(TabDialog * t, ActivityActionData * act,
                                     RemoveVariableValueAction * d, BrowserNodeList & cl,
                                     QStringList & clstr, bool visit)
{
    ChangeVariableValueDialog::init(t, act, d, TR("remove duplicates"), cl, clstr, visit);
}

// call operation

void CallOperationDialog::init(TabDialog * t, ActivityActionData * act,
                               CallOperationAction * d, BrowserNodeList & cl,
                               QStringList & clstr, bool ro)
{
    td = t;
    classes = &cl;
    class_names = &clstr;
    visit = ro;

    // ocl

    ocl_grid = mkgrid(t, TR("operation - Ocl"));

    ocl_grid->addWidget(new QLabel("", ocl_grid));
    BButtonGroup * grp;
    ocl_grid->addWidget(grp = new BButtonGroup(2, Qt::Horizontal, QString(), ocl_grid));

    grp->addWidget(synchronous_cb = new QCheckBox(TR("synchronous"), grp));
    synchronous_cb->setDisabled(visit);

    ocl_grid->addWidget(new QLabel(TR("class : "), ocl_grid));
    ocl_grid->addWidget(class_co = new QComboBox(ocl_grid));
    SmallPushButton* sButton;
    connect(sButton = new SmallPushButton(TR("operation :"), ocl_grid), SIGNAL(clicked()),
            this, SLOT(menu_oper()));
    ocl_grid->addWidget(sButton);
    ocl_grid->addWidget(oper_co = new QComboBox(ocl_grid));

    ocl_cond.init(ocl_grid, act, UmlView, visit);

    if (! visit) {
        class_co->addItem("");
        oper_co->addItem("");
        class_co->setAutoCompletion(completion());
        oper_co->setAutoCompletion(completion());

        class_co->addItems(*class_names);
        connect(class_co, SIGNAL(activated(int)), this, SLOT(classChanged(int)));
    }

    if ((d != 0) && (d->operation != 0)) {
        synchronous_cb->setChecked(d->synchronous);

        if (visit) {
            class_co->addItem(((BrowserNode *) d->operation->parent())->full_name(TRUE));
            oper_co->addItem(((OperationData *) d->operation->get_data())->definition(TRUE, FALSE));
            class_co->setCurrentIndex(0);
            oper_co->setCurrentIndex(0);
        }
        else
            set(d->operation);

        ocl_cond.set(act->get_precond(UmlView), act->get_postcond(UmlView));
    }

    // note : must add then remove rather than doing nothing
    // else some sub widget will be wrong placed
    t->addTab(ocl_grid, TR("operation - Ocl"));

    if (d == 0)
        t->removePage(ocl_grid);

    // cpp & java
    init_cpp(t, act, d, visit);
    init_java(t, act, d, visit);
}

void CallOperationDialog::classChanged(int)
{
    oper_co->clear();
    oper_co->addItem("");

    int index = class_names->indexOf(class_co->currentText());

    if (index != -1)
        insert_opers((BrowserClass *) classes->at(index));
}

void CallOperationDialog::insert_opers(BrowserClass * c)
{
    // oper_co contains "" and optionally an oper's name
    opers.clear();
    oper_names.clear();

    BrowserNode * child;

    for (child = c->firstChild(); child; child = child->nextSibling()) {
        if (!((BrowserNode *) child)->deletedp() &&
                (((BrowserNode *) child)->get_type() == UmlOperation)) {
            QString s = ((OperationData *)((BrowserNode *) child)->get_data())->definition(TRUE, FALSE);

            opers.append((BrowserNode *) child);
            oper_names.append(s);
            oper_co->addItem(s);
        }
    }
}

bool CallOperationDialog::update(CallOperationAction * a)
{
    a->synchronous = synchronous_cb->isChecked();

    int index = oper_names.indexOf(oper_co->currentText());

    BrowserNode * old = a->operation;

    a->operation = (index != -1) ? (BrowserOperation *) opers.at(index) : 0;

    return old != a->operation;
}

void CallOperationDialog::set(BrowserNode * bn)
{
    BrowserClass * cl = (BrowserClass *) bn->parent();
    int index = class_names->indexOf(cl->full_name(TRUE));

    if (index == -1)
        // new class, not managed
        return;

    class_co->setCurrentIndex(index + 1);
    insert_opers(cl);

    // the operation is in oper_names
    oper_co->setCurrentIndex(oper_names.indexOf(((OperationData *) bn->get_data())->definition(TRUE, FALSE)) + 1);
}

void CallOperationDialog::menu_oper()
{
    QMenu m(0);

    MenuFactory::addItem(m, TR("Choose"), -1);
    m.addSeparator();

    int index = oper_names.indexOf(oper_co->currentText());

    if (index != -1)
        MenuFactory::addItem(m, TR("Select in browser"), 0);

    BrowserNode * bn = 0;
    BrowserClass * cl = 0;

    if (! visit) {
        bn = BrowserView::selected_item();

        if ((bn != 0) && (bn->get_type() == UmlOperation) && !bn->deletedp())
            MenuFactory::addItem(m, TR("Choose operation selected in browser"), 1);
        else
            bn = 0;

        int index_cl = class_names->indexOf(class_co->currentText());

        if (index_cl != -1) {
            cl = (BrowserClass *) classes->at(index_cl);

            if (!cl->is_writable())
                cl = 0;
            else
                MenuFactory::addItem(m, TR("Create operation and choose it"), 2);
        }
    }

    if ((index != -1) || (bn != 0) || (cl != 0)) {
        QAction *retActon = m.exec(QCursor::pos());
        if(retActon)
        {
            switch (retActon->data().toInt()) {
            case 0:
                opers.at(index)->select_in_browser();
                break;

            case 2:
                bn = cl->add_operation();

                if (bn == 0)
                    break;

                bn->select_in_browser();

                // no break;
            case 1:
                oper_co->clear();
                oper_co->addItem("");
                set(bn);
            }
        }
    }
}

// call behavior

void WithBehaviorDialog::init(BrowserNode * beh)
{
    if (!visit) {
        behavior_co->addItem("");
        behavior_co->setAutoCompletion(completion());

        QStringList::Iterator iter_str = node_names->begin();
        foreach (BrowserNode *node, *nodes) {
            behavior_co->addItem(*(node->pixmap(0)), *iter_str);
            ++iter_str;
        }

        if (beh != 0)
            behavior_co->setCurrentIndex(node_names->indexOf(beh->full_name(TRUE)) + 1);
    }
    else if (beh != 0) {
        behavior_co->addItem(*(beh->pixmap(0)), beh->full_name(TRUE));
        behavior_co->setCurrentIndex(0);
    }
}

void WithBehaviorDialog::menu_behavior()
{
    QMenu m(0);

    MenuFactory::addItem(m, QObject::tr("Choose"), -1);
    m.addSeparator();

    int index = node_names->indexOf(behavior_co->currentText());

    if (index != -1)
        MenuFactory::addItem(m, QObject::tr("Select in browser"), 0);

    BrowserNode * bn = 0;

    if (! visit) {
        bn = BrowserView::selected_item();

        if (bn != 0) {
            switch (bn->get_type()) {
            case UmlState:
            case UmlActivity:
                if (!bn->deletedp()) {
                    MenuFactory::addItem(m, QObject::tr("Choose behavior selected in browser"), 1);
                    break;
                }

                // no break
            default:
                bn = 0;
            }
        }

        MenuFactory::addItem(m, QObject::tr("Create activity and choose it"), 2);
        MenuFactory::addItem(m, QObject::tr("Create state machine and choose it"), 3);
    }

    if (!visit || (index != -1) || (bn != 0)) {
        QAction *retActon = m.exec(QCursor::pos());
        if(retActon)
        {
            switch (retActon->data().toInt()) {
            case 0:
                nodes->at(index)->select_in_browser();
                return;

            case 1:
                break;

            case 2:
                bn = BrowserActivity::add_activity(view);

                if (bn == 0)
                    return;

                bn->select_in_browser();
                break;

            case 3:
                bn = BrowserState::add_state(view, (bool) TRUE);

                if (bn == 0)
                    return;

                bn->select_in_browser();
                break;

            default:
                return;
            }
        }

        // here the behavior bn was choosen
        QString s = bn->full_name(TRUE);

        index = node_names->indexOf(s);

        if (index == -1) {
            // new behavior, may be created through an other dialog, add it
            index = 0;
            QStringList::Iterator iter = node_names->begin();
            QStringList::Iterator iter_end = node_names->end();

            while ((iter != iter_end) && (*iter < s)) {
                ++iter;
                index += 1;
            }

            nodes->insert((unsigned) index, bn);
            node_names->insert(iter, s);
            behavior_co->insertItem(index + 1,*(bn->pixmap(0)), s);
        }

        behavior_co->setCurrentIndex(index + 1);
    }
}

//

void CallBehaviorDialog::init(TabDialog * t, ActivityActionData * act,
                              CallBehaviorAction * d, BrowserNodeList & beh,
                              QStringList & behstr, BrowserNode * v, bool ro)
{
    td = t;
    nodes = &beh;
    node_names = &behstr;
    view = v;
    visit = ro;

    // ocl

    ocl_grid = mkgrid(t, TR("behavior - Ocl"));

    ocl_grid->addWidget(new QLabel("", ocl_grid));
    BButtonGroup * grp;
    ocl_grid->addWidget(grp = new BButtonGroup(2, Qt::Horizontal, QString(), ocl_grid));

    grp->addWidget(synchronous_cb = new QCheckBox(TR("synchronous"), grp));
    synchronous_cb->setDisabled(visit);
    SmallPushButton* sButton;
    connect(sButton = new SmallPushButton(TR("behavior :"), ocl_grid), SIGNAL(clicked()),
            this, SLOT(menu_beh()));
    ocl_grid->addWidget(sButton);
    ocl_grid->addWidget(behavior_co = new QComboBox(ocl_grid));

    ocl_cond.init(ocl_grid, act, UmlView, visit);

    WithBehaviorDialog::init((d != 0) ? d->behavior : 0);

    if (d != 0) {
        synchronous_cb->setChecked(d->synchronous);
        ocl_cond.set(act->get_precond(UmlView), act->get_postcond(UmlView));
    }

    // note : must add then remove rather than doing nothing
    // else some sub widget will be wrong placed
    t->addTab(ocl_grid, TR("behavior - Ocl"));

    if (d == 0)
        t->removePage(ocl_grid);

    // cpp & java
    init_cpp(t, act, d, visit);
    init_java(t, act, d, visit);
}

bool CallBehaviorDialog::update(CallBehaviorAction * a)
{
    a->synchronous = synchronous_cb->isChecked();

    int index = node_names->indexOf(behavior_co->currentText());

    BrowserNode * old = a->behavior;

    a->behavior = (index != -1) ? nodes->at(index) : 0;

    return old != a->behavior;
}

void CallBehaviorDialog::menu_beh()
{
    WithBehaviorDialog::menu_behavior();
}

// Accept Call

void AcceptCallDialog::init(TabDialog * t, ActivityActionData * act,
                            AcceptCallAction * d, bool visit)
{
    td = t;

    // ocl

    ocl_grid = mkgrid(t, QObject::tr("trigger - Ocl"));

    ocl_grid->addWidget(new QLabel(QObject::tr("trigger : "), ocl_grid));
    ocl_grid->addWidget(uml_trigger = new LineEdit(ocl_grid));
    uml_trigger->setReadOnly(visit);

    ocl_cond.init(ocl_grid, act, UmlView, visit);

    if (d != 0) {
        ocl_cond.set(act->get_precond(UmlView), act->get_postcond(UmlView));
        uml_trigger->setText(d->uml_trigger);
    }

    t->addTab(ocl_grid, QObject::tr("trigger - Ocl"));

    if (d == 0)
        t->removePage(ocl_grid);

    // cpp

    cpp_grid = mkgrid(t, QObject::tr("trigger - C++"));

    cpp_grid->addWidget(new QLabel(QObject::tr("trigger : "), cpp_grid));
    cpp_grid->addWidget(cpp_trigger = new LineEdit(cpp_grid));

    cpp_cond.init(cpp_grid, act, CppView, visit);

    if (d != 0) {
        cpp_cond.set(act->get_precond(CppView), act->get_postcond(CppView));
        cpp_trigger->setText(d->cpp_trigger);
    }

    t->addTab(cpp_grid, QObject::tr("trigger - C++"));

    if ((d == 0) || !GenerationSettings::cpp_get_default_defs())
        t->removePage(cpp_grid);

    // java

    java_grid = mkgrid(t, QObject::tr("trigger - Java"));

    java_grid->addWidget(new QLabel(QObject::tr("trigger : "), java_grid));
    java_grid->addWidget(java_trigger = new LineEdit(java_grid));

    java_cond.init(java_grid, act, JavaView, visit);

    if (d != 0) {
        java_cond.set(act->get_precond(JavaView), act->get_postcond(JavaView));
        java_trigger->setText(d->java_trigger);
    }

    t->addTab(java_grid, QObject::tr("trigger - Java"));

    if ((d == 0) || !GenerationSettings::java_get_default_defs())
        t->removePage(java_grid);
}

bool AcceptCallDialog::update(AcceptCallAction * a)
{
    a->uml_trigger = uml_trigger->text().trimmed();
    a->cpp_trigger = cpp_trigger->text().trimmed();
    a->java_trigger = java_trigger->text().trimmed();

    return FALSE;
}

// Reply

void ReplyDialog::init(TabDialog * t, ActivityActionData * act,
                       ReplyAction * d, bool visit)
{
    td = t;

    // ocl

    ocl_grid = mkgrid(t, QObject::tr("trigger - Ocl"));

    ocl_grid->addWidget(new QLabel(QObject::tr("trigger : "), ocl_grid));
    ocl_grid->addWidget(uml_trigger = new LineEdit(ocl_grid));
    uml_trigger->setReadOnly(visit);

    ocl_cond.init(ocl_grid, act, UmlView, visit);

    if (d != 0) {
        ocl_cond.set(act->get_precond(UmlView), act->get_postcond(UmlView));
        uml_trigger->setText(d->uml_trigger);
    }

    t->addTab(ocl_grid, QObject::tr("trigger - Ocl"));

    if (d == 0)
        t->removePage(ocl_grid);

    // cpp

    cpp_grid = mkgrid(t, QObject::tr("trigger - C++"));

    cpp_grid->addWidget(new QLabel(QObject::tr("trigger : "), cpp_grid));
    cpp_grid->addWidget(cpp_trigger = new LineEdit(cpp_grid));

    cpp_cond.init(cpp_grid, act, CppView, visit);

    if (d != 0) {
        cpp_cond.set(act->get_precond(CppView), act->get_postcond(CppView));
        cpp_trigger->setText(d->cpp_trigger);
    }

    t->addTab(cpp_grid, QObject::tr("trigger - C++"));

    if ((d == 0) || !GenerationSettings::cpp_get_default_defs())
        t->removePage(cpp_grid);

    // java

    java_grid = mkgrid(t, QObject::tr("trigger - Java"));

    java_grid->addWidget(new QLabel(QObject::tr("trigger : "), java_grid));
    java_grid->addWidget(java_trigger = new LineEdit(java_grid));

    java_cond.init(java_grid, act, JavaView, visit);

    if (d != 0) {
        java_cond.set(act->get_precond(JavaView), act->get_postcond(JavaView));
        java_trigger->setText(d->java_trigger);
    }

    t->addTab(java_grid, QObject::tr("trigger - Java"));

    if ((d == 0) || !GenerationSettings::java_get_default_defs())
        t->removePage(java_grid);
}

bool ReplyDialog::update(ReplyAction * a)
{
    a->uml_trigger = uml_trigger->text().trimmed();
    a->cpp_trigger = cpp_trigger->text().trimmed();
    a->java_trigger = java_trigger->text().trimmed();

    return FALSE;
}

// Create Object

void CreateObjectDialog::init(TabDialog * t, ActivityActionData * act,
                              CreateObjectAction * d, bool visit)
{
    td = t;

    // ocl

    ocl_grid = mkgrid(t, QObject::tr("classifier - Ocl"));

    ocl_grid->addWidget(new QLabel(QObject::tr("classifier : "), ocl_grid));
    ocl_grid->addWidget(classifier = new LineEdit(ocl_grid));
    classifier->setReadOnly(visit);

    ocl_cond.init(ocl_grid, act, UmlView, visit);

    if (d != 0) {
        ocl_cond.set(act->get_precond(UmlView), act->get_postcond(UmlView));
        classifier->setText(d->classifier);
    }

    t->addTab(ocl_grid, QObject::tr("classifier - Ocl"));

    if (d == 0)
        t->removePage(ocl_grid);

    // cpp & java
    init_cpp(t, act, d, visit);
    init_java(t, act, d, visit);
}

bool CreateObjectDialog::update(CreateObjectAction * a)
{
    a->classifier = classifier->text().trimmed();

    return FALSE;
}

// Destroy Object

void DestroyObjectDialog::init(TabDialog * t, ActivityActionData * act,
                               DestroyObjectAction * d, bool visit)
{
    td = t;

    // ocl

    ocl_grid = mkgrid(t, QObject::tr("flags - Ocl"));

    ocl_grid->addWidget(new QLabel("", ocl_grid));
    BButtonGroup * grp;
    ocl_grid->addWidget(grp = new BButtonGroup(2, Qt::Horizontal, QString(), ocl_grid));

    grp->addWidget(is_destroy_links_cb = new QCheckBox(QObject::tr("links"), grp));
    is_destroy_links_cb->setDisabled(visit);

    grp->addWidget(is_destroy_owned_objects_cb = new QCheckBox(QObject::tr("owned objects"), grp));
    is_destroy_owned_objects_cb->setDisabled(visit);

    ocl_cond.init(ocl_grid, act, UmlView, visit);

    if (d != 0) {
        ocl_cond.set(act->get_precond(UmlView), act->get_postcond(UmlView));
        is_destroy_links_cb->setChecked(d->is_destroy_links);
        is_destroy_owned_objects_cb->setChecked(d->is_destroy_owned_objects);
    }

    t->addTab(ocl_grid, QObject::tr("flags - Ocl"));

    if (d == 0)
        t->removePage(ocl_grid);

    // cpp & java
    init_cpp(t, act, d, visit);
    init_java(t, act, d, visit);
}

bool DestroyObjectDialog::update(DestroyObjectAction * a)
{
    a->is_destroy_links = is_destroy_links_cb->isChecked();
    a->is_destroy_owned_objects = is_destroy_owned_objects_cb->isChecked();

    return FALSE;
}

// test identity action

void TestIdentityDialog::init(TabDialog * t, ActivityActionData * act,
                              TestIdentityAction * d, bool visit)
{
    td = t;

    // ocl

    ocl_grid = mkgrid(t, "Ocl");

    ocl_cond.init(ocl_grid, act, UmlView, visit);

    // note : must add then remove rather than doing nothing
    // else some sub widget will be wrong placed
    t->addTab(ocl_grid, "Ocl");

    if (d == 0)
        t->removePage(ocl_grid);

    // cpp & java
    init_cpp(t, act, d, visit);
    init_java(t, act, d, visit);
}

bool TestIdentityDialog::update(TestIdentityAction *)
{
    return FALSE;
}

// raise exception action

void RaiseExceptionDialog::init(TabDialog * t, ActivityActionData * act,
                                RaiseExceptionAction * d, bool visit)
{
    td = t;

    // ocl

    ocl_grid = mkgrid(t, "Ocl");

    ocl_cond.init(ocl_grid, act, UmlView, visit);

    // note : must add then remove rather than doing nothing
    // else some sub widget will be wrong placed
    t->addTab(ocl_grid, "Ocl");

    if (d == 0)
        t->removePage(ocl_grid);

    // cpp & java
    init_cpp(t, act, d, visit);
    init_java(t, act, d, visit);
}

bool RaiseExceptionDialog::update(RaiseExceptionAction *)
{
    return FALSE;
}

// reduce action

void ReduceDialog::init(TabDialog * t, ActivityActionData * act,
                        ReduceAction * d, BrowserNodeList & beh,
                        QStringList & behstr, BrowserNode * v, bool ro)
{
    td = t;
    nodes = &beh;
    node_names = &behstr;
    view = v;
    visit = ro;

    // ocl

    ocl_grid = mkgrid(t, TR("reducer - Ocl"));

    ocl_grid->addWidget(new QLabel("", ocl_grid));
    BButtonGroup * grp;
    ocl_grid->addWidget(grp = new BButtonGroup(2, Qt::Horizontal, QString(), ocl_grid));

    grp->addWidget(is_ordered_cb = new QCheckBox(TR("ordered"), grp));
    is_ordered_cb->setDisabled(visit);
    SmallPushButton* sButton;
    connect(sButton = new SmallPushButton(TR("reducer :"), ocl_grid), SIGNAL(clicked()),
            this, SLOT(menu_beh()));
    ocl_grid->addWidget(sButton);
    ocl_grid->addWidget(behavior_co = new QComboBox(ocl_grid));

    ocl_cond.init(ocl_grid, act, UmlView, visit);

    WithBehaviorDialog::init((d != 0) ? d->reducer : 0);

    if (d != 0) {
        is_ordered_cb->setChecked(d->is_ordered);
        ocl_cond.set(act->get_precond(UmlView), act->get_postcond(UmlView));
    }

    // note : must add then remove rather than doing nothing
    // else some sub widget will be wrong placed
    t->addTab(ocl_grid, TR("reducer - Ocl"));

    if (d == 0)
        t->removePage(ocl_grid);

    // cpp & java
    init_cpp(t, act, d, visit);
    init_java(t, act, d, visit);
}

bool ReduceDialog::update(ReduceAction * a)
{
    a->is_ordered = is_ordered_cb->isChecked();

    int index = node_names->indexOf(behavior_co->currentText());

    a->reducer = (index != -1) ? nodes->at(index) : 0;

    return FALSE;
}

void ReduceDialog::menu_beh()
{
    WithBehaviorDialog::menu_behavior();
}
