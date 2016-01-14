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





//#include <QMenu.h>
#include <qcursor.h>
#include <qdir.h>
//Added by qt3to4:
#include <QTextStream>
#include <QList>
#include <QPixmap>
#include <QDragMoveEvent>
#include <QDropEvent>

#include "BrowserComponent.h"
#include "SimpleData.h"
#include "BrowserComponentDiagram.h"
#include "BrowserDeploymentDiagram.h"
#include "BrowserSimpleRelation.h"
#include "SimpleRelationData.h"
#include "BrowserClass.h"
#include "PackageData.h"
#include "UmlPixmap.h"
#include "myio.h"
#include "ToolCom.h"
#include "Tool.h"
#include "ui/menufactory.h"
#include "ClassListDialog.h"
#include "ComponentDialog.h"
#include "UmlDrag.h"
#include "GenerationSettings.h"
#include "ReferenceDialog.h"

#include "mu.h"

#include "DialogUtil.h"
#include "ProfiledStereotypes.h"
#include "translate.h"

IdDict<BrowserComponent> BrowserComponent::all(257, __FILE__);
QStringList BrowserComponent::its_default_stereotypes;	// unicode

BrowserComponent::BrowserComponent(QString s, BrowserNode * p, int id)
    : BrowserNode(s, p), Labeled<BrowserComponent>(all, id)
{
    def = new SimpleData;
    def->set_browser_node(this);

    associated_diagram = 0;
}

BrowserComponent::BrowserComponent(const BrowserComponent * model,
                                   BrowserNode * p)
    : BrowserNode(model->name, p), Labeled<BrowserComponent>(all, 0)
{
    def = new SimpleData(model->def);
    def->set_browser_node(this);
    comment = model->comment;
    associated_diagram = 0;
}

BrowserComponent::BrowserComponent(int id)
    : BrowserNode(), Labeled<BrowserComponent>(all, id)
{
    // not yet read
    def = new SimpleData;
    def->set_browser_node(this);

    associated_diagram = 0;
}

BrowserComponent::~BrowserComponent()
{
    all.remove(get_ident());
    delete def;
}

BrowserNode * BrowserComponent::duplicate(BrowserNode * p, QString name)
{
    BrowserComponent * result = new BrowserComponent(this, p);

    result->set_name((name.isEmpty()) ? get_name() : name);
    result->update_stereotype();

    return result;
}

void BrowserComponent::clear(bool old)
{
    all.clear(old);
}

void BrowserComponent::update_idmax_for_root()
{
    all.update_idmax_for_root();
}

void BrowserComponent::prepare_update_lib() const
{
    all.memo_id_oid(get_ident(), original_id);
    for (BrowserNode * child = firstChild();
         child != 0;
         child = child->nextSibling())
        ((BrowserNode *) child)->prepare_update_lib();
}

void BrowserComponent::referenced_by(QList<BrowserNode *> & l, bool ondelete)
{
    BrowserNode::referenced_by(l, ondelete);

    if (! ondelete) {
        BrowserComponentDiagram::compute_referenced_by(l, this, "componentcanvas", "component_ref");
        BrowserDeploymentDiagram::compute_referenced_by(l, this, "componentcanvas", "component_ref");
    }
}

void BrowserComponent::compute_referenced_by(QList<BrowserNode *> & l,
        BrowserClass * target)
{
    IdIterator<BrowserComponent> it(all);

    while(it.hasNext()){
        it.next();
        if(it.value()) {
        if (!it.value()->deletedp() &&
            ((it.value()->realizing_classes.indexOf(target) != -1) ||
             (it.value()->provided_classes.indexOf(target) != -1) ||
             (it.value()->required_classes.indexOf(target) != -1)))
            l.append(it.value());
}
    }
}

void BrowserComponent::renumber(int phase)
{
    if (phase != -1)
        new_ident(phase, all);
}

const QPixmap * BrowserComponent::pixmap(int) const
{
    if (deletedp())
        return DeletedComponentIcon;
    const QPixmap * px = ProfiledStereotypes::browserPixmap(def->get_stereotype());

    return (px != 0) ? px : ComponentIcon;
}

void BrowserComponent::iconChanged()
{
    repaint();
    def->modified();
}

QString BrowserComponent::full_name(bool rev, bool) const
{
    return fullname(rev);
}

// just check if the inheritance already exist
QString BrowserComponent::check_inherit(const BrowserNode * new_parent) const
{
    BrowserNode * child;

    for (child = firstChild(); child != 0; child = child->nextSibling()) {
        BrowserNode * ch = ((BrowserNode *) child);

        if ((ch->get_type() == UmlInherit) &&
            ((((SimpleRelationData *) ch->get_data())->get_end_node())
             == new_parent))
            return QObject::tr("already exist");
    }
    return (new_parent != this) ? QString() : QObject::tr("circular inheritance");
}

static void make_clsubm(QMenu & m, QMenu & sm,
                        QList<BrowserClass *> & l, int bias,
                        BooL & need_sep, QString s)
{
    int n = 0;
    QList<BrowserClass *>::ConstIterator it;

    for (it = l.begin(); it != l.end(); ++it)
        if (!(*it)->deletedp())
            n += 1;

    if (n == 1) {
        if (need_sep) {
            m.addSeparator();
            need_sep = FALSE;
        }

        MenuFactory::addItem(m, QObject::tr("Select the %1 class").arg(s), bias + 1,
                       QObject::tr("to select the %1 <i>class</i>").arg(s));
    }
    else if (n > 20) {
        if (need_sep) {
            m.addSeparator();
            need_sep = FALSE;
        }

        MenuFactory::addItem(m, QObject::tr("Select a %1 class").arg(s), bias,
                       QObject::tr("to select a %1 <i>class</i>").arg(s));
    }
    else if (n != 0) {
        if (need_sep) {
            m.addSeparator();
            need_sep = FALSE;
        }

        MenuFactory::createTitle(sm, QObject::tr("Choose class"));
        sm.addSeparator();

        for (it = l.begin(), n = bias + 1; it != l.end(); ++it)
            if (!(*it)->deletedp())
                MenuFactory::addItem(sm, (*it)->full_name(TRUE), n++);

        MenuFactory::insertItem(m, QObject::tr("Select a %1 class").arg(s), &sm,
                       QObject::tr("to select a %1 <i>class</i>").arg(s));
    }
}

static bool select_associated(int rank, int bias,
                              QList<BrowserClass *> & l)
{
    if (rank < bias)
        return FALSE;

    if (rank == bias) {
        ClassListDialog dialog( QObject::tr("Choose class").toLatin1().constData(), l);

        dialog.raise();

        if (dialog.exec() != QDialog::Accepted)
            return TRUE;

        rank = dialog.choosen() + bias + 1;
    }

    QList<BrowserClass *>::ConstIterator it;
    int n;

    for (it = l.begin(), n = bias + 1;
         (*it)->deletedp() || (n++ != rank);
         ++it)
        ;

    (*it)->select_in_browser();
    return TRUE;
}


void BrowserComponent::menu()
{
    QMenu m(name,0);
    QMenu rqsubm(0);
    QMenu prsubm(0);
    QMenu rzsubm(0);
    QMenu toolm(0);

    MenuFactory::createTitle(m, def->definition(FALSE, TRUE));
    m.addSeparator();

    if (!deletedp()) {
        if (!is_edited) {
            MenuFactory::addItem(m, QObject::tr("New nested component"), 4,
                           QObject::tr("to add an <i>nested component</i> to the <i>component</i>"));
            m.addSeparator();
            MenuFactory::addItem(m, QObject::tr("Edit"), 0,
                           QObject::tr("to edit the <i>component</i>, \
a double click with the left mouse button does the same thing"));

            if (!is_read_only && (edition_number == 0)) {
                m.addSeparator();
                MenuFactory::addItem(m, QObject::tr("Delete"), 1,
                               QObject::tr("to delete the <i>component</i>. \
Note that you can undelete it after"));
            }
        }

        m.addSeparator();
        MenuFactory::addItem(m, QObject::tr("Referenced by"), 3,
                       QObject::tr("to know who reference the <i>component</i> \
through a relation"));
        mark_menu(m, QObject::tr("the component").toLatin1().constData(), 90);
        ProfiledStereotypes::menu(m, this, 99990);

        if ((edition_number == 0) &&
            Tool::menu_insert(&toolm, get_type(), 100)) {
            m.addSeparator();
            toolm.setTitle(QObject::tr("Tool"));
            m.addMenu(&toolm);
        }
    }
    else if (!is_read_only && (edition_number == 0)) {
        MenuFactory::addItem(m, QObject::tr("Undelete"), 2,
                       QObject::tr("to undelete the <i>component</i>"));

        BrowserNode * child;

        for (child = firstChild(); child != 0; child = child->nextSibling()) {
            if (((BrowserNode *) child)->deletedp()) {
                MenuFactory::addItem(m, QObject::tr("Undelete recursively"), 22,
                               QObject::tr("undelete the <i>component</i> and its \
nested <i>components</i> and <i>relations</i> \
(except if the component at the other side is also deleted)"));
                break;
            }
        }
    }

    BooL need_sep = TRUE;

    make_clsubm(m, rqsubm, required_classes, 9999, need_sep, "required");
    make_clsubm(m, prsubm, provided_classes, 19999, need_sep, "provided");
    make_clsubm(m, rzsubm, realizing_classes, 29999, need_sep, "realization");

    QAction *resultAction = m.exec(QCursor::pos());
    if(resultAction)
        exec_menu_choice(resultAction->data().toInt());
}

void BrowserComponent::exec_menu_choice(int rank)
{
    switch (rank) {
    case 0:
        open(TRUE);
        return;

    case 1:
        delete_it();
        break;

    case 2:
        undelete(FALSE);
        break;

    case 22:
        undelete(TRUE);
        break;

    case 3:
        ReferenceDialog::show(this);
        return;

    case 4: {
        BrowserComponent * cp = add_component(this);

        if (cp != 0)
            cp->select_in_browser();
    }
    break;

    default:
        if (select_associated(rank, 29999, realizing_classes) ||
            select_associated(rank, 19999, provided_classes) ||
            select_associated(rank, 9999, required_classes))
            return;
        if (rank >= 99990)
            ProfiledStereotypes::choiceManagement(this, rank - 99990);
        else if (rank >= 100)
            ToolCom::run(Tool::command(rank - 100), this);
        else
            mark_management(rank - 90);
        return;
    }

    package_modified();
}

void BrowserComponent::apply_shortcut(QString s)
{
    int choice = -1;

    if (!deletedp()) {
        if (!is_edited) {
            if (s == "New nested component")
                choice = 4;
            else if (s == "Edit")
                choice = 0;

            if (!is_read_only && (edition_number == 0)) {
                if (s == "Delete")
                    choice = 1;
            }
        }

        if (s == "Referenced by")
            choice = 3;

        mark_shortcut(s, choice, 90);

        if (edition_number == 0)
            Tool::shortcut(s, choice, get_type(), 100);
    }
    else if (!is_read_only && (edition_number == 0)) {
        if (s == "Undelete")
            choice = 2;
        BrowserNode * child;

        for (child = firstChild(); child != 0; child = child->nextSibling()) {
            if (((BrowserNode *) child)->deletedp()) {
                if (s == "Undelete recursively")
                    choice = 22;

                break;
            }
        }
    }

    exec_menu_choice(choice);
}

void BrowserComponent::open(bool force_edit)
{
    if (!force_edit &&
        (associated_diagram != 0) &&
        !associated_diagram->deletedp())
        associated_diagram->open(FALSE);
    else if (!is_edited) {
        def->setName(get_name());
        (new ComponentDialog(def))->show();
    }
}

void BrowserComponent::modified()
{
    repaint();
    ((BrowserNode *) parent())->modified();
    // to update regions drawing
    def->modified();
}

UmlCode BrowserComponent::get_type() const
{
    return UmlComponent;
}

QString BrowserComponent::get_stype() const
{
    return QObject::tr("component");
}

int BrowserComponent::get_identifier() const
{
    return get_ident();
}

const char * BrowserComponent::help_topic() const
{
    return "component";
}

void BrowserComponent::DragMoveEvent(QDragMoveEvent * e)
{
    if (UmlDrag::canDecode(e, UmlComponent) ||
        UmlDrag::canDecode(e, BrowserSimpleRelation::drag_key(this))) {
        if (!is_read_only)
            e->accept();
        else
            e->ignore();
    }
    else
        ((BrowserNode *) parent())->DragMoveInsideEvent(e);
}

void BrowserComponent::DragMoveInsideEvent(QDragMoveEvent * e)
{
    if (!is_read_only &&
        (UmlDrag::canDecode(e, UmlComponent) ||
         UmlDrag::canDecode(e, BrowserSimpleRelation::drag_key(this))))
        e->accept();
    else
        e->ignore();
}

void BrowserComponent::DropEvent(QDropEvent * e)
{
    DropAfterEvent(e, 0);
}

void BrowserComponent::DropAfterEvent(QDropEvent * e, BrowserNode * after)
{
    BrowserNode * bn;
    if ((((bn = UmlDrag::decode(e, UmlComponent)) != 0) ||
         ((bn = UmlDrag::decode(e, BrowserSimpleRelation::drag_key(this))) != 0)) &&
        (bn != after) && (bn != this)) {
        bool a_comp = (bn->get_type() == UmlComponent);

        if (may_contains(bn, a_comp)) {
            BrowserNode * old = ((BrowserNode *) bn->parent());

            if ((after == 0) &&
                a_comp &&
                old->may_contains(bn, TRUE)) {
                // have choice
                QMenu m(0);

                MenuFactory::createTitle(m, QObject::tr("move ") + bn->get_name());
                m.addSeparator();
                MenuFactory::addItem(m, QObject::tr("In ") + QString(get_name()), 1);
                 MenuFactory::addItem(m, QObject::tr("After ") + QString(get_name()), 2);

                QAction* act = m.exec(QCursor::pos());
                if(act)
                switch (act->data().toInt()) {
                case 1:
                    break;

                case 2:
                    ((BrowserNode *) parent())->DropAfterEvent(e, this);
                    return;

                default:
                    e->ignore();
                    return;
                }
            }

            if (after)
                bn->moveItem(after);
            else {
                ((BrowserNode *)bn->parent())->takeItem(bn);
                insertItem(bn);
            }

            if (old != this) {
                old->modified();
                old->package_modified();
                bn->modified();
            }

            modified();
            package_modified();
        }
        else {
            msg_critical( QObject::tr("Error"), QObject::tr("Forbidden"));
            e->ignore();
        }
    }
    else if ((bn == 0) && (after == 0))
        ((BrowserNode *) parent())->DropAfterEvent(e, this);
    else
        e->ignore();
}

BrowserComponent * BrowserComponent::get_component(BrowserNode * future_parent,
        bool existing)
{
    BrowserNode * old;
    QString name;
    BrowserNodeList nodes;
    if (!future_parent->enter_child_name(name,
                                         (existing) ? QObject::tr("choose existing component")
                                         : QObject::tr("enter component's name : "),
                                         UmlComponent, instances(nodes), &old,
                                         TRUE, FALSE, existing))
        return 0;

    if (old != 0)
        return ((BrowserComponent *) old);

    future_parent->setOpen(TRUE);
    future_parent->package_modified();
    return new BrowserComponent(name, future_parent);
}

BrowserComponent * BrowserComponent::add_component(BrowserNode * future_parent)
{
    QString name;
    if (!future_parent->enter_child_name(name, QObject::tr("enter component's name : "),
                                         UmlComponent, TRUE, FALSE))
        return 0;

    future_parent->setOpen(TRUE);
    future_parent->package_modified();
    return new BrowserComponent(name, future_parent);
}

BasicData * BrowserComponent::get_data() const
{
    return def;
}

BrowserNodeList & BrowserComponent::instances(BrowserNodeList & result,
        const char * st, bool non_nested)
{
    IdIterator<BrowserComponent> it(all);

    if ((st == 0) || (*st == 0)) {
        while(it.hasNext()){
            it.next();
        if (it.value() != 0)
            if (!it.value()->deletedp() &&
                (!non_nested || !it.value()->nestedp()))
                result.append(it.value());

        }
    }
    else {
        while(it.hasNext()){
            it.next();
        if (it.value() != 0)
            if (!it.value()->deletedp() &&
                (!non_nested || !it.value()->nestedp()) &&
                !strcmp(it.value()->get_data()->get_stereotype(), st))
                result.append(it.value());

        }
    }

    result.sort_it();
    return result;
}

BrowserNode * BrowserComponent::get_associated() const
{
    return associated_diagram;
}

void BrowserComponent::set_associated_diagram(BrowserNode * dg,
        bool on_read)
{
    if (associated_diagram != dg) {
        if (associated_diagram != 0)
            QObject::disconnect(associated_diagram->get_data(), SIGNAL(deleted()),
                                def, SLOT(on_delete()));

        if ((associated_diagram = dg) != 0)
            QObject::connect(associated_diagram->get_data(), SIGNAL(deleted()),
                             def, SLOT(on_delete()));

        if (!on_read)
            package_modified();
    }
}

void BrowserComponent::on_delete()
{
    bool modif = FALSE;
    if (associated_diagram && associated_diagram->deletedp()) {
        associated_diagram = 0;
        modif = TRUE;
    }

    QList<BrowserClass *>::Iterator it;

    it = realizing_classes.begin();

    while (it != realizing_classes.end()) {
        if ((*it)->deletedp()) {
            it = realizing_classes.erase(it);
            modif = TRUE;
        }
        else
            ++it;
    }

    it = provided_classes.begin();

    while (it != provided_classes.end()) {
        if ((*it)->deletedp()) {
            it = provided_classes.erase(it);
            modif = TRUE;
        }
        else
            ++it;
    }

    it = required_classes.begin();

    while (it != required_classes.end()) {
        if ((*it)->deletedp()) {
            it = required_classes.erase(it);
            modif = TRUE;
        }
        else
            ++it;
    }
    if (modif)
        package_modified();
}

void BrowserComponent::remove_associated_class(BrowserClass * c)
{
    bool done = FALSE;
    QList<BrowserClass *>::Iterator it;
    if (realizing_classes.contains(c)) {
        realizing_classes.removeOne(c);
        QObject::disconnect(c->get_data(), SIGNAL(deleted()),
                            def, SLOT(on_delete()));
        package_modified();
        done = TRUE;
    }

    if (provided_classes.contains(c)) {
        provided_classes.removeOne(c);

        if (! done) {
            QObject::disconnect(c->get_data(), SIGNAL(deleted()),
                                def, SLOT(on_delete()));
            package_modified();
            done = TRUE;
        }
    }

    if (required_classes.contains(c)) {
        required_classes.removeOne(c);

        if (! done) {
            QObject::disconnect(c->get_data(), SIGNAL(deleted()),
                                def, SLOT(on_delete()));
            package_modified();
        }
    }
}

void BrowserComponent::get_all_provided_classes(QList<BrowserClass *> & r) const
{
    QList<BrowserClass *>::ConstIterator it;
    for (it = provided_classes.begin() ; it != provided_classes.end(); it++)
        if (r.indexOf(*it) == -1)
            r.append(*it);

    BrowserNode * child;

    for (child = firstChild(); child != 0; child = child->nextSibling())
        if (((BrowserNode *) child)->get_type() == UmlComponent)
            ((BrowserComponent *) child)->get_all_provided_classes(r);
}

void BrowserComponent::get_all_provided_classes(QList<BrowserClass *> & r,
        bool sorted) const
{
    r = provided_classes;
    BrowserNode * child;

    for (child = firstChild(); child != 0; child = child->nextSibling())
        if (((BrowserNode *) child)->get_type() == UmlComponent)
            ((BrowserComponent *) child)->get_all_provided_classes(r);

    if (sorted) {
        BrowserNodeList nl;
        QList<BrowserClass *>::Iterator it;

        for (it = r.begin() ; it != r.end(); it++)
            nl.append(*it);

        r.clear();
        nl.sort_it();

        foreach (BrowserNode *node, nl)
            r.append((BrowserClass *) node);
    }
}

void BrowserComponent::get_all_required_classes(QList<BrowserClass *> & r) const
{
    QList<BrowserClass *>::ConstIterator it;
    for (it = required_classes.begin() ; it != required_classes.end(); it++)
        if (!r.contains(*it))
            r.append(*it);

    BrowserNode * child;

    for (child = firstChild(); child != 0; child = child->nextSibling())
        if (((BrowserNode *) child)->get_type() == UmlComponent)
            ((BrowserComponent *) child)->get_all_required_classes(r);
}

void BrowserComponent::get_all_required_classes(QList<BrowserClass *> & r,
        bool sorted) const
{
    r = required_classes;
    BrowserNode * child;

    for (child = firstChild(); child != 0; child = child->nextSibling())
        if (((BrowserNode *) child)->get_type() == UmlComponent)
            ((BrowserComponent *) child)->get_all_required_classes(r);
    if (sorted) {
        BrowserNodeList nl;
        QList<BrowserClass *>::Iterator it;

        for (it = r.begin() ; it != r.end(); it++)
            nl.append(*it);

        r.clear();
        nl.sort_it();

        foreach (BrowserNode *node, nl)
            r.append((BrowserClass *) node);
    }
}

void BrowserComponent::set_associated_classes(const QList<BrowserClass *> & rz,
        const QList<BrowserClass *> & pr,
        const QList<BrowserClass *> & rq,
        bool on_read)
{
    QList<BrowserClass *>::Iterator it;

    if (! on_read) {
        // manage removed classes
        it = realizing_classes.begin();

        while (it != realizing_classes.end()) {
            QObject::disconnect((*it)->get_data(), SIGNAL(deleted()),
                                def, SLOT(on_delete()));
            if (rz.indexOf(*it) == -1) {
                // stop to be realizing
                realizing_classes.removeOne(*it);
            }
            else
                ++it;

        }

        it = provided_classes.begin();

        while (it != provided_classes.end()) {
            QObject::disconnect((*it)->get_data(), SIGNAL(deleted()),
                                def, SLOT(on_delete()));
            if (pr.indexOf(*it) == -1) {
                // stop to be provided
                provided_classes.removeOne(*it);
            }
            else
                ++it;
        }

        it = required_classes.begin();

        while (it != required_classes.end()) {
            QObject::disconnect((*it)->get_data(), SIGNAL(deleted()),
                                def, SLOT(on_delete()));
            if (rq.indexOf(*it) == -1) {
                // stop to be required
                required_classes.removeOne(*it);
            }
            else
                ++it;
        }
    }

    // manage added classes
    realizing_classes = rz;

    for (it = realizing_classes.begin(); it != realizing_classes.end(); ++it) {
        BrowserClass * cl = *it;

        QObject::connect(cl->get_data(), SIGNAL(deleted()),
                         def, SLOT(on_delete()));
    }

    provided_classes = pr;
    for (it = provided_classes.begin(); it != provided_classes.end(); ++it) {
        BrowserClass * cl = *it;

        if (cl->get_associated_components().indexOf(this) == -1)
            cl->add_associated_component(this);

        if (rz.indexOf(cl) == -1) {
            QObject::connect(cl->get_data(), SIGNAL(deleted()),
                             def, SLOT(on_delete()));
        }
    }

    required_classes = rq;

    for (it = required_classes.begin(); it != required_classes.end(); ++it) {
        BrowserClass * cl = *it;

        if ((rz.indexOf(cl) == -1) && (pr.indexOf(cl) == -1)) {
            QObject::connect(cl->get_data(), SIGNAL(deleted()),
                             def, SLOT(on_delete()));
        }
    }
    if (!on_read)
        package_modified();
}

void BrowserComponent::init()
{
    its_default_stereotypes.clear();
    its_default_stereotypes.append("buildComponent");
    its_default_stereotypes.append("entity");
    its_default_stereotypes.append("implement");
    its_default_stereotypes.append("process");
    its_default_stereotypes.append("service");
    its_default_stereotypes.append("subsystem");
}

// unicode
const QStringList & BrowserComponent::default_stereotypes()
{
    return its_default_stereotypes;
}

bool BrowserComponent::tool_cmd(ToolCom * com, const char * args)
{
    switch ((unsigned char) args[-1]) {
    case getDefCmd:
    case getUmlDefCmd:
    case getCppDefCmd:
    case getJavaDefCmd:
    case getPhpDefCmd:
    case getPythonDefCmd:
    case getIdlDefCmd:
        BrowserNode::tool_cmd(com, args);

        if (com->api_format() > 13) {
            QList<BrowserClass *>::Iterator it;

            com->write_unsigned(realizing_classes.count());

            for (it = realizing_classes.begin(); it != realizing_classes.end(); ++it)
                (*it)->write_id(com);

            com->write_unsigned(provided_classes.count());

            for (it = provided_classes.begin(); it != provided_classes.end(); ++it)
                (*it)->write_id(com);

            com->write_unsigned(required_classes.count());

            for (it = required_classes.begin(); it != required_classes.end(); ++it)
                (*it)->write_id(com);
        }

        return TRUE;

    default:
        if (((unsigned char) args[-1]) >= firstSetCmd) {
            if (is_read_only && !root_permission())
                com->write_ack(FALSE);
            else {
                switch ((unsigned char) args[-1]) {
                case setAssocDiagramCmd:
                    set_associated_diagram((BrowserNode *) com->get_id(args));
                    break;

                case createCmd: {
                    bool ok = TRUE;

                    switch (com->get_kind(args)) {
                    case UmlSimpleRelations: {
                        UmlCode c;

                        if (!com->get_relation_kind(c, args))
                            ok = FALSE;
                        else {
                            BrowserNode * end = (BrowserNode *) com->get_id(args);

                            switch (c) {
                            case UmlDependency:
                                switch (end->get_type()) {
                                case UmlPackage:
                                case UmlComponent:
                                    add_relation(UmlDependOn, end)->get_browser_node()->write_id(com);
                                    break;

                                default:
                                    ok = FALSE;
                                }

                                break;

                            case UmlGeneralisation:
                                if ((end->get_type() == UmlComponent) &&
                                    check_inherit(end).isEmpty())
                                    add_relation(UmlInherit, end)->get_browser_node()->write_id(com);
                                else
                                    ok = FALSE;

                                break;

                            default:
                                ok = FALSE;
                            }
                        }
                    }
                    break;

                    case UmlComponent:
                        if (wrong_child_name(args, UmlComponent, FALSE, FALSE))
                            ok = FALSE;
                        else
                            (new BrowserComponent(args, this))->write_id(com);

                        break;

                    default:
                        ok = FALSE;
                    }

                    if (! ok)
                        com->write_id(0);
                    else
                        package_modified();

                    break;
                }

                case setAssocClassesCmd: {
                    // check redondency
                    QList<BrowserClass *> rz;
                    QList<BrowserClass *> pr;
                    QList<BrowserClass *> rq;
                    QList<BrowserClass *>::ConstIterator it;
                    unsigned n;

                    n = com->get_unsigned(args);

                    while (n--)
                        rz.append((BrowserClass *) com->get_id(args));

                    n = com->get_unsigned(args);

                    while (n--)
                        pr.append((BrowserClass *) com->get_id(args));

                    n = com->get_unsigned(args);

                    while (n--)
                        rq.append((BrowserClass *) com->get_id(args));

                    it = rz.begin();

                    while (it != rz.end()) {
                        BrowserClass * cl = *it;
                        if ((pr.contains(cl)) ||
                            (rq.contains(cl)) ||
                            (rz.contains(cl))) {
                            com->write_ack(FALSE);
                            return TRUE;
                        }
                        ++it;
                    }

                    it = pr.begin();

                    while (it != pr.end()) {
                        BrowserClass * cl = *it;
                        if ((rz.contains(cl)) ||
                            (rq.contains(cl)) ||
                            (pr.contains( cl))) {
                            com->write_ack(FALSE);
                            return TRUE;
                        }
                        ++it;
                    }

                    it = rq.begin();

                    while (it != rq.end()) {
                        BrowserClass * cl = *it;
                        if ((rz.contains(cl)) ||
                            (pr.contains(cl)) ||
                            (rq.contains( cl))) {
                            com->write_ack(FALSE);
                            return TRUE;
                        }
                        ++it;
                    }

                    set_associated_classes(rz, pr, rq);
                    com->write_ack(TRUE);
                }

                return TRUE;

                default:
                    return (def->tool_cmd(com, args, this, comment) ||
                            BrowserNode::tool_cmd(com, args));
                }
            }
        }
        else
            return (def->tool_cmd(com, args, this, comment) ||
                    BrowserNode::tool_cmd(com, args));
    }

    return TRUE;
}

void BrowserComponent::save_stereotypes(QTextStream & st)
{
    nl_indent(st);
    st << "component_stereotypes ";
    save_unicode_string_list(its_default_stereotypes, st);
}

void BrowserComponent::read_stereotypes(char *& st, char *& k)
{
    if (!strcmp(k, "component_stereotypes")) {
        read_unicode_string_list(its_default_stereotypes, st);
        k = read_keyword(st);
    }
    else
        init();
}

void BrowserComponent::save(QTextStream & st, bool ref, QString & warning)
{
    if (ref)
        st << "component_ref " << get_ident() << " // " << get_name();
    else {
        nl_indent(st);
        st << "component " << get_ident() << " ";
        save_string(name.toLatin1().constData(), st);
        indent(+1);
        def->save(st, warning);

        if (associated_diagram != 0) {
            nl_indent(st);
            st << "associated_diagram ";
            associated_diagram->save(st, TRUE, warning);
        }

        QList<BrowserClass *>::ConstIterator it;

        if (! realizing_classes.isEmpty()) {
            nl_indent(st);
            st << "realizing_classes";
            indent(+1);

            for (it = realizing_classes.begin(); it != realizing_classes.end(); ++it) {
                nl_indent(st);
                (*it)->save(st, TRUE, warning);
            }

            indent(-1);
            nl_indent(st);
            st << "end";
        }

        if (! provided_classes.isEmpty()) {
            nl_indent(st);
            st << "provided_classes";
            indent(+1);

            for (it = provided_classes.begin(); it != provided_classes.end(); ++it) {
                nl_indent(st);
                (*it)->save(st, TRUE, warning);
            }

            indent(-1);
            nl_indent(st);
            st << "end";
        }

        if (! required_classes.isEmpty()) {
            nl_indent(st);
            st << "required_classes";
            indent(+1);

            for (it = required_classes.begin(); it != required_classes.end(); ++it) {
                nl_indent(st);
                (*it)->save(st, TRUE, warning);
            }

            indent(-1);
            nl_indent(st);
            st << "end";
        }

        BrowserNode::save(st);

        // saves the sub elts

        BrowserNode * child = firstChild();

        if (child != 0) {
            for (;;) {
                if (!((BrowserNode *) child)->deletedp()) {
                    ((BrowserNode *) child)->save(st, FALSE, warning);
                    child = child->nextSibling();

                    if (child != 0)
                        st << '\n';
                    else
                        break;
                }
                else if ((child = child->nextSibling()) == 0)
                    break;
            }
        }

        indent(-1);
        nl_indent(st);
        st << "end";

        // for saveAs
        if (!is_from_lib() && !is_api_base())
            is_read_only = FALSE;
    }
}

BrowserComponent * BrowserComponent::read_ref(char *& st, const char * k)
{
    if (strcmp(k, "component_ref"))
        wrong_keyword(k, "component_ref");

    int id = read_id(st);
    BrowserComponent * result = all[id];

    return (result == 0)
           ? new BrowserComponent(id)
           : result;
}

BrowserComponent * BrowserComponent::read(char *& st, char * k,
        BrowserNode * parent)
{
    BrowserComponent * result;
    int id;

    if (!strcmp(k, "component_ref")) {
        if ((result = all[id = read_id(st)]) == 0)
            result = new BrowserComponent(id);

        return result;
    }
    else if (!strcmp(k, "component")) {
        id = read_id(st);

        QString s = read_string(st);

        k = read_keyword(st);

        if ((result = all[id]) == 0) {
            result = new BrowserComponent(s, parent, id);
            result->def->read(st, k);	// updates k
        }
        else if (result->is_defined) {
            BrowserComponent * already_exist = result;

            result = new BrowserComponent(s, parent, id);
            result->def->read(st, k);	// updates k

            already_exist->must_change_id(all);
            already_exist->unconsistent_fixed("component", result);
        }
        else {
            result->def->read(st, k);	// updates k
            result->set_parent(parent);
            result->set_name(s);
        }

        result->is_defined = TRUE;

        result->is_read_only = (!in_import() && read_only_file()) ||
                               ((user_id() != 0) && result->is_api_base());

        if (!strcmp(k, "associated_diagram")) {
            k = read_keyword(st);

            BrowserNode * diag;
            if (((diag = BrowserComponentDiagram::read(st, k, 0)) == 0) &&
                ((diag = BrowserDeploymentDiagram::read(st, k, 0)) == 0))
                wrong_keyword(k, "component/deployment diagram ref");
            result->set_associated_diagram(diag, TRUE);
            k = read_keyword(st);
        }

        QList<BrowserClass *> rz;
        QList<BrowserClass *> pr;
        QList<BrowserClass *> rq;

        if (!strcmp(k, "realized_classes") || !strcmp(k, "realizing_classes")) {
            while (strcmp((k = read_keyword(st)), "end"))
                rz.append(BrowserClass::read_ref(st, k));

            k = read_keyword(st);
        }

        if (!strcmp(k, "provided_classes")) {
            while (strcmp((k = read_keyword(st)), "end"))
                pr.append(BrowserClass::read_ref(st, k));

            k = read_keyword(st);
        }

        if (!strcmp(k, "required_classes")) {
            while (strcmp((k = read_keyword(st)), "end"))
                rq.append(BrowserClass::read_ref(st, k));

            k = read_keyword(st);
        }

        result->set_associated_classes(rz, pr, rq, TRUE);

        result->BrowserNode::read(st, k, id);	// updates k

        if (strcmp(k, "end")) {
            while (BrowserComponent::read(st, k, result) ||
                   BrowserSimpleRelation::read(st, k, result))
                k = read_keyword(st);

            if (strcmp(k, "end"))
                wrong_keyword(k, "end");
        }

        return result;
    }
    else
        return 0;
}

BrowserNode * BrowserComponent::get_it(const char * k, int id)
{
    // simple relation managed in use case
    return (!strcmp(k, "component_ref")) ? all[id] : 0;
}
