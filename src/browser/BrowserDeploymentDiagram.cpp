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





//#include <q3popupmenu.h>
#include <qcursor.h>
#include <qfileinfo.h>
//Added by qt3to4:
#include <QTextStream>
#include <QList>
#include <QPixmap>

#include "BrowserDeploymentDiagram.h"
#include "SimpleData.h"
#include "DeploymentDiagramWindow.h"
#include "BrowserDeploymentView.h"
#include "DiagramView.h"
#include "UmlPixmap.h"
#include "SettingsDialog.h"
#include "myio.h"
#include "strutil.h"
#include "ToolCom.h"
#include "Tool.h"
#include "ui/menufactory.h"
#include "BrowserView.h"
#include "ProfiledStereotypes.h"
#include "mu.h"
#include "translate.h"

QList<BrowserDeploymentDiagram *> BrowserDeploymentDiagram::imported;
QList<int> BrowserDeploymentDiagram::imported_ids;
QStringList BrowserDeploymentDiagram::its_default_stereotypes;	// unicode

BrowserDeploymentDiagram::BrowserDeploymentDiagram(const QString & s, BrowserNode * p, int id)
    : BrowserDiagram(s, p, id), window(0), used_settings(0)
{
    make();
    is_modified = (id == 0);
}

BrowserDeploymentDiagram::BrowserDeploymentDiagram(int id)
    : BrowserDiagram(id), window(0), used_settings(0)
{
    // not yet read
    make();
    is_modified = (id == 0);
}

BrowserDeploymentDiagram::BrowserDeploymentDiagram(BrowserDeploymentDiagram * model, BrowserNode * p)
    : BrowserDiagram(p->get_name(), p, 0), window(0), used_settings(0)
{
    def = new SimpleData(model->def);
    def->set_browser_node(this);
    comment = model->comment;
    settings = model->settings;
    deploymentnode_color = model->deploymentnode_color;
    artifact_color = model->artifact_color;
    component_color = model->component_color;
    note_color = model->note_color;
    package_color = model->package_color;
    fragment_color = model->fragment_color;
    canvas_size = model->canvas_size;
    is_modified = TRUE;

    if (model->window != 0)
    {
        model->window->duplicate(get_ident(), "diagram");
    }
    else {
        char * diagram;

        if ((diagram = read_definition(model->get_ident(), "diagram")) != 0) {
            save_definition(get_ident(), "diagram", diagram, is_new);
            delete [] diagram;
        }
    }
}

BrowserDeploymentDiagram::~BrowserDeploymentDiagram()
{
    if (deletedp() && !modifiedp()) {
        QString fn;

        fn.sprintf("%d.diagram", get_ident());

        QDir d = BrowserView::get_dir();

        QFile::remove(d.absoluteFilePath(fn));
    }

    all.remove(get_ident());
    delete def;
}

void BrowserDeploymentDiagram::make()
{
    def = new SimpleData;
    def->set_browser_node(this);
    deploymentnode_color = UmlDefaultColor;
    artifact_color = UmlDefaultColor;
    component_color = UmlDefaultColor;
    note_color = UmlDefaultColor;
    package_color = UmlDefaultColor;
    fragment_color = UmlDefaultColor;
}

BrowserDeploymentDiagram * BrowserDeploymentDiagram::add_deployment_diagram(BrowserNode * future_parent)
{
    QString name;

    if (future_parent->enter_child_name(name, QObject::tr("enter deployment diagram's name : "),
                                        UmlDeploymentDiagram, TRUE, FALSE))
        return new BrowserDeploymentDiagram(name, future_parent);
    else
        return 0;
}

void BrowserDeploymentDiagram::set_name(const QString & s)
{
    BrowserDiagram::set_name(s);

    if (window != 0)
    {
        window->setWindowTitle(s);
    }
}

void BrowserDeploymentDiagram::import()
{
    QList<int>::Iterator it = imported_ids.begin();
    foreach (BrowserDeploymentDiagram *d, imported) {
        (new DeploymentDiagramWindow(d->full_name(), d, *it))->close();
        it = imported_ids.erase(it);
        d->is_modified = TRUE;
    }
    imported.clear();
}

void BrowserDeploymentDiagram::renumber(int phase)
{
    if (phase == -1)
        open(FALSE);
    else {
        new_ident(phase, all);
        window->get_view()->renumber(get_ident());
        is_modified = TRUE;
    }
}

void BrowserDeploymentDiagram::delete_it()
{
    if (window)
        delete window;
    window = 0;
    BrowserNode::delete_it();
}

BrowserNode * BrowserDeploymentDiagram::duplicate(BrowserNode * p, const QString & name)
{
    BrowserDeploymentDiagram * result = new BrowserDeploymentDiagram(this, p);

    result->set_name((name.isEmpty()) ? get_name() : name);
    result->update_stereotype();

    return result;
}

const QPixmap * BrowserDeploymentDiagram::pixmap(int) const
{
    if (deletedp())
        return DeletedDeploymentDiagramIcon;

    const QPixmap * px = ProfiledStereotypes::browserPixmap(def->get_stereotype());

    return (px != 0) ? px : DeploymentDiagramIcon;
}

void BrowserDeploymentDiagram::draw_svg() const
{
    fputs("\t<rect fill=\"white\" stroke=\"black\" stroke-width=\"1\" stroke-opacity=\"1\" x=\"0\" y=\"0\" width=\"15\" height=\"15\" />\n"
          "\t<path fill=\"none\" stroke=\"black\" stroke-width=\"1\" stroke-opacity=\"1\" "
          "d=\"M 5 1 L 11 1 L 11 6 L 8 9 L 2 9 L 2 4 L 5 1 "
          "M 2 4 L 8 4 L 8 9 "
          "M 8 4 L 11 1 "
          "M 5 9 L 5 12 L 10 12 "
          "M 10 15 L 10 10 L 13 7 L 15 7 "
          "M 10 10 L 15 10\" />\n",
          svg());
}

void BrowserDeploymentDiagram::menu()
{
    QMenu m(name,0);
    QMenu toolm(0);

    MenuFactory::createTitle(m, def->definition(FALSE, TRUE));
    m.addSeparator();

    if (!deletedp()) {
        MenuFactory::addItem(m, QObject::tr("Show"), 0,
                             QObject::tr("to show and edit the <i>deployment diagram</i>"));

        if (!is_edited) {
            MenuFactory::addItem(m, QObject::tr("Edit"), 1,
                                 QObject::tr("to edit the <i>deployment diagram</i>"));

            if (!is_read_only) {
                MenuFactory::addItem(m, QObject::tr("Edit drawing settings"), 2,
                                     QObject::tr("to set how the <i>deployment diagram</i>'s items must be drawn"));
                m.addSeparator();
                MenuFactory::addItem(m, QObject::tr("Duplicate"), 3,
                                     QObject::tr("to duplicate the <i>deployment diagram</i>"));

                if (edition_number == 0) {
                    m.addSeparator();
                    MenuFactory::addItem(m, QObject::tr("Delete"), 4,
                                         QObject::tr("to delete the <i>deployment diagram</i>. \
                                                     Note that you can undelete it after"));
                }
            }
        }

        mark_menu(m, QObject::tr("the deployment diagram"), 90);
        ProfiledStereotypes::menu(m, this, 99990);

        if ((edition_number == 0) &&
                Tool::menu_insert(&toolm, get_type(), 100)) {
            m.addSeparator();
            toolm.setTitle( QObject::tr("Tool"));
            m.addMenu(&toolm);
        }
    }
    else if (!is_read_only && (edition_number == 0))
        MenuFactory::addItem(m, QObject::tr("Undelete"), 5,
                             QObject::tr("to undelete the <i>deployment diagram</i>"));

    QAction *resultAction = m.exec(QCursor::pos());
    if(resultAction)
        exec_menu_choice(resultAction->data().toInt());
}

void BrowserDeploymentDiagram::exec_menu_choice(int rank)
{
    switch (rank) {
    case 0:
        open(FALSE);
        return;

    case 1:
        edit( QObject::tr("Deployment diagram"), its_default_stereotypes);
        return;

    case 2:
        edit_settings();
        return;

    case 3: {
        QString name;

        if (((BrowserNode *)parent())->enter_child_name(name, QObject::tr("enter deployment diagram's name : "),
                                                        UmlDeploymentDiagram, TRUE, FALSE))
            duplicate((BrowserNode *) parent(), name)->select_in_browser();
        else
            return;
    }
        break;

    case 4:
        delete_it();
        break;

    case 5:
        undelete(FALSE);
        break;

    default:
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

void BrowserDeploymentDiagram::apply_shortcut(const QString & s)
{
    int choice = -1;

    if (!deletedp()) {
        if (s == "Show")
            choice = 0;

        if (!is_edited) {
            if (s == "Edit")
                choice = 1;

            if (!is_read_only) {
                if (s == "Edit drawing settings")
                    choice = 2;
                else if (s == "Duplicate")
                    choice = 3;

                if (edition_number == 0) {
                    if (s == "Delete")
                        choice = 4;
                }
            }
        }

        mark_shortcut(s, choice, 90);

        if (edition_number == 0)
            Tool::shortcut(s, choice, get_type(), 100);
    }
    else if (!is_read_only && (edition_number == 0))
        if (s == "Undelete")
            choice = 5;

    exec_menu_choice(choice);
}

void BrowserDeploymentDiagram::open(bool)
{
    if (window == 0 || windowDestroyed)
        window = new DeploymentDiagramWindow(full_name(TRUE), this);
    else
        window->raise();
    windowDestroyed = false;
    window->setFocus();
}

void BrowserDeploymentDiagram::edit_settings()
{
    for (;;) {
        StateSpecVector st;
        ColorSpecVector co(6);

        settings.complete(st, TRUE);

        co[0].set( QObject::tr("note color"), &note_color);
        co[1].set( QObject::tr("artifact color"), &artifact_color);
        co[2].set( QObject::tr("node color"), &deploymentnode_color);
        co[3].set( QObject::tr("component color"), &component_color);
        co[4].set( QObject::tr("package color"), &package_color);
        co[5].set( QObject::tr("fragment color"), &fragment_color);

        SettingsDialog dialog(&st, &co, FALSE);

        dialog.raise();

        if (dialog.exec() == QDialog::Accepted) {
            DrawingSettings::modified();
            package_modified();
        }

        if (!dialog.redo())
            break;
    }
}

void BrowserDeploymentDiagram::on_close()
{
    window = 0;

    if (used_settings != 0) {
        delete used_settings;
        used_settings = 0;
    }
}

void BrowserDeploymentDiagram::read_session(char *& st)
{
    window->read_session(st);
}

UmlCode BrowserDeploymentDiagram::get_type() const
{
    return UmlDeploymentDiagram;
}

QString BrowserDeploymentDiagram::get_stype() const
{
    return QObject::tr("deployment diagram");
}

int BrowserDeploymentDiagram::get_identifier() const
{
    return get_ident();
}

const char * BrowserDeploymentDiagram::help_topic() const
{
    return "deploymentdiagram";
}

void BrowserDeploymentDiagram::update_drawing_settings()
{
    if (used_settings == 0)
        used_settings = new DeploymentDiagramSettings;

    *used_settings = settings;
    ((BrowserNode *) parent())->get_deploymentdiagramsettings(*used_settings);
}

void BrowserDeploymentDiagram::get_deploymentdiagramsettings(DeploymentDiagramSettings & r) const
{
    r.assign(*used_settings);
}

void BrowserDeploymentDiagram::get_componentdrawingsettings(ComponentDrawingSettings & r) const
{
    r.assign(used_settings->componentdrawingsettings);
}

void BrowserDeploymentDiagram::package_settings(BooL & name_in_tab,
                                                ShowContextMode & show_context) const
{
    name_in_tab = used_settings->package_name_in_tab == UmlYes;
    show_context = used_settings->show_context_mode;
}

UmlColor BrowserDeploymentDiagram::get_color(UmlCode who) const
{
    UmlColor c;

    switch (who) {
    case UmlDeploymentNode:
        c = deploymentnode_color;
        break;

    case UmlArtifact:
        c = artifact_color;
        break;

    case UmlComponent:
        c = component_color;
        break;

    case UmlNote:
        c = note_color;
        break;

    case UmlFragment:
        c = fragment_color;
        break;

    default:
        c = package_color;
    }

    return (c != UmlDefaultColor)
            ? c
            : ((BrowserNode *) parent())->get_color(who);
}

bool BrowserDeploymentDiagram::get_shadow() const
{
    return used_settings->shadow == UmlYes;
}

bool BrowserDeploymentDiagram::get_draw_all_relations() const
{
    return used_settings->draw_all_relations == UmlYes;
}

void BrowserDeploymentDiagram::dont_draw_all_relations()
{
    settings.draw_all_relations =
            used_settings->draw_all_relations = UmlNo;
}

bool BrowserDeploymentDiagram::get_show_stereotype_properties() const
{
    return used_settings->componentdrawingsettings.show_stereotype_properties
            == UmlYes;
}

bool BrowserDeploymentDiagram::get_auto_label_position() const
{
    return used_settings->auto_label_position == UmlYes;
}

BasicData * BrowserDeploymentDiagram::get_data() const
{
    return def;
}

bool BrowserDeploymentDiagram::tool_cmd(ToolCom * com, const char * args)
{
    switch ((unsigned char) args[-1]) {
    case supportFileCmd: {
        QString fn;

        fn.sprintf("%d.diagram", get_ident());

        QDir d = BrowserView::get_dir();

        com->write_string(d.absoluteFilePath(fn));
    }

        return TRUE;
    case saveInCmd:
        if (window != 0)
            com->write_ack(window->get_view()->save_pict(args, TRUE, FALSE));
        else {
            DeploymentDiagramWindow * w = new DeploymentDiagramWindow(full_name(), this);

            com->write_ack(w->get_view()->save_pict(args,
                                                    !w->get_view()->has_preferred_size_zoom(),
                                                    TRUE));
            w->dont_save();
            w->close();
        }

        return TRUE;
    default:
        return (def->tool_cmd(com, args, this, comment) ||
                BrowserNode::tool_cmd(com, args));
    }
}

void BrowserDeploymentDiagram::compute_referenced_by(QList<BrowserNode *> & l,
                                                     BrowserNode * bn,
                                                     char const * kc,
                                                     char const * kr)
{
    int id = bn->get_identifier();
    IdIterator<BrowserDiagram> it(all);
    BrowserDiagram * d;

    while (it.hasNext()) {
        it.next();
        if((d = it.value()) != 0)
        {
            if (!d->deletedp() && (d->get_type() == UmlDeploymentDiagram)) {
                if ((((BrowserDeploymentDiagram *) d)->window != 0)
                        ? ((BrowserDeploymentDiagram *) d)->window->get_view()->is_present(bn)
                        : is_referenced(read_definition(d->get_ident(), "diagram"), id, kc, kr))
                    l.append((BrowserDeploymentDiagram *) d);
            }
        }
    }
}

void BrowserDeploymentDiagram::save_stereotypes(QTextStream & st)
{
    nl_indent(st);
    st << "deploymentdiagram_stereotypes ";
    save_unicode_string_list(its_default_stereotypes, st);
}

void BrowserDeploymentDiagram::read_stereotypes(char *& st, char *& k)
{
    if (!strcmp(k, "deploymentdiagram_stereotypes")) {
        read_unicode_string_list(its_default_stereotypes, st);
        k = read_keyword(st);
    }
}

void BrowserDeploymentDiagram::save(QTextStream & st, bool ref, QString & warning)
{
    if (ref)
        st << "deploymentdiagram_ref " << get_ident() << " // " << get_name();
    else {
        nl_indent(st);
        st << "deploymentdiagram " << get_ident() << " ";
        save_string(name, st);
        indent(+1);
        def->save(st, warning);
        settings.save(st);

        BooL nl = FALSE;

        save_color(st, "deploymentnode_color", deploymentnode_color, nl);
        save_color(st, "component_color", component_color, nl);
        save_color(st, "note_color", note_color, nl);
        save_color(st, "artifact_color", artifact_color, nl);
        save_color(st, "package_color", package_color, nl);
        save_color(st, "fragment_color", fragment_color, nl);

        BrowserNode::save(st);

        if (is_modified) {
            is_modified = FALSE;

            if (window)
            {
                window->save("diagram", warning, is_new);
            }
            else
                BrowserDiagram::save();
        }

        nl_indent(st);
        st << "size " << stringify(get_format());

        indent(-1);
        nl_indent(st);
        st << "end";

        // for saveAs
        if (!is_from_lib() && !is_api_base())
            is_read_only = FALSE;
    }
}

BrowserDeploymentDiagram * BrowserDeploymentDiagram::read_ref(char *& st, const char * k)
{
    if (strcmp(k, "deploymentdiagram_ref") &&
            ((read_file_format() >= 20) || strcmp(k, "componentdiagram_ref")))
        wrong_keyword(k, "deploymentdiagram_ref");

    int id = read_id(st);
    BrowserDeploymentDiagram * result =
            (BrowserDeploymentDiagram *) all[id];

    return (result == 0)
            ? new BrowserDeploymentDiagram(id)
            : result;
}

BrowserDeploymentDiagram *
BrowserDeploymentDiagram::read(char *& st, char * k,
                               BrowserNode * parent)
{
    BrowserDeploymentDiagram * r;
    int id;

    if (!strcmp(k, "deploymentdiagram_ref") ||
            ((read_file_format() < 20) && !strcmp(k, "componentdiagram_ref"))) {
        if ((r = (BrowserDeploymentDiagram *) all[id = read_id(st)]) == 0)
            r = new BrowserDeploymentDiagram(id);

        return r;
    }

    bool from_component =
            // component -> artifact
            (read_file_format() < 20) && !strcmp(k, "componentdiagram");

    if (!strcmp(k, "deploymentdiagram") || from_component) {
        id = read_id(st);

        QString s = read_string(st);

        if ((r = (BrowserDeploymentDiagram *) all[id]) == 0)
            r = new BrowserDeploymentDiagram(s, parent, id);
        else if (r->is_defined) {
            BrowserDeploymentDiagram * already_exist = r;

            r = new BrowserDeploymentDiagram(s, parent, id);

            already_exist->must_change_id(all);
            already_exist->unconsistent_fixed("deployment diagram", r);
        }
        else {
            r->set_parent(parent);
            r->set_name(s);
        }

        r->is_defined = TRUE;

        r->is_read_only = (!in_import() && read_only_file()) ||
                ((user_id() != 0) && r->is_api_base());

        QFileInfo fi(BrowserView::get_dir(), QString::number(id) + ".diagram");

        if (!in_import() && fi.exists() && !fi.isWritable())
            r->is_read_only = TRUE;

        k = read_keyword(st);

        r->def->read(st, k);					// updates k
        r->settings.read(st, k);					// updates k

        if (read_file_format() < 30)
            r->settings.draw_all_relations = UmlNo;

        if (from_component) {
            read_color(st, "note_color", r->note_color, k);		// updates k
            read_color(st, "component_color", r->component_color, k);	// updates k
            read_color(st, "package_color", r->package_color, k);	// updates k
        }
        else {
            read_color(st, "deploymentnode_color", r->deploymentnode_color, k);	// updates k
            read_color(st, "component_color", r->component_color, k);	// updates k
            read_color(st, "note_color", r->note_color, k);		// updates k
            read_color(st, "artifact_color", r->artifact_color, k);	// updates k
            read_color(st, "package_color", r->package_color, k);	// updates k
            read_color(st, "fragment_color", r->fragment_color, k);	// updates k
        }

        r->BrowserNode::read(st, k, id);	// updates k

        if (!strcmp(k, "size")) {
            r->set_format(canvas_format(read_keyword(st)));
            k = read_keyword(st);
        }
        else
            r->set_format(IsoA4);

        if (strcmp(k, "end"))
            wrong_keyword(k, "end");

        if (in_import()) {
            imported.append(r);
            imported_ids.append(id);
        }

        return r;
    }
    else
        return 0;
}

BrowserNode * BrowserDeploymentDiagram::get_it(const char * k, int id)
{
    return (!strcmp(k, "deploymentdiagram_ref")) ? all[id] : 0;
}
