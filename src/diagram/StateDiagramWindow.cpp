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





#include <qapplication.h>
#include <qworkspace.h>
#include <q3toolbar.h>
#include <qtoolbutton.h>
#include <q3whatsthis.h>
#include <qlayout.h>
#include <qspinbox.h>

#include "UmlWindow.h"
#include "StateDiagramWindow.h"
#include "StateDiagramView.h"
#include "BrowserStateDiagram.h"
#include "UmlPixmap.h"
#include "myio.h"
#include "translate.h"

QString addstateText()
{
    return TR("Click this button to add a <i>state</i> in the diagram. <br><br>"
              "You can also drop the state from the <b>browser</b>.");
}
extern QString addpackageText();
extern QString addfragmentText();
extern QString noteText();
extern QString anchorText();
extern QString textText();
QString addentrypointText()
{
    return TR("Click this button to add a <i>entry point</i> in the diagram. <br><br>"
              "You can also drop the <i>entry point</i> from the <b>browser</b>.");
}
QString addexitpointText()
{
    return TR("Click this button to add a <i>exit point</i> in the diagram. <br><br>"
              "You can also drop the <i>exit point</i> from the <b>browser</b>.");
}
QString addinitialText()
{
    return TR("Click this button to add a <i>initial pseudo state</i> in the diagram. <br><br>"
              "You can also drop the <i>initial pseudo state</i> from the <b>browser</b>.");
}
QString addfinalText()
{
    return TR("Click this button to add a <i>final state</i> in the diagram. <br><br>"
              "You can also drop the <i>final state</i> from the <b>browser</b>.");
}
QString addterminateText()
{
    return TR("Click this button to add a <i>terminate node</i> in the diagram. <br><br>"
              "You can also drop the <i>terminate node</i> from the <b>browser</b>.");
}
QString adddeephistoryText()
{
    return TR("Click this button to add a <i>deep history</i> in the diagram. <br><br>"
              "You can also drop the <i>deep history</i> from the <b>browser</b>.");
}
QString addshallowhistoryText()
{
    return TR("Click this button to add a <i>shallow history</i> in the diagram. <br><br>"
              "You can also drop the <i></i> from the <b>browser</b>.");
}
QString addjunctionText()
{
    return TR("Click this button to add a <i>junction</i> in the diagram. <br><br>"
              "You can also drop the <i>junction</i> from the <b>browser</b>.");
}
QString addchoiceText()
{
    return TR("Click this button to add a <i>choice</i> in the diagram. <br><br>"
              "You can also drop the <i>choice</i> from the <b>browser</b>.");
}
QString addforkText()
{
    return TR("Click this button to add a <i>fork</i> in the diagram. <br><br>"
              "You can also drop the <i>foek</i> from the <b>browser</b>.");
}
QString addjoinText()
{
    return TR("Click this button to add a <i>join</i> in the diagram. <br><br>"
              "You can also drop the <i>join</i> from the <b>browser</b>.");
}
QString addtransitionText()
{
    return TR("Click this button to add a <i>transition</i> in the diagram. <br><br>"
              "You can also drop the <i>transition</i> from the <b>browser</b>.");
}
QString addregionText()
{
    return TR("Click this button to add a <i>region</i> in a <i>state</i>.");
}
QString addactionText()
{
    return TR("Click this button to add an <i>action</i> in a <i>state</i>.");
}
QString addsignalinText()
{
    return TR("Click this button to add a <i>receive signal action</i> in a <i>state</i>.");
}
QString addsignaloutText()
{
    return TR("Click this button to add a <i>send signal action</i> in a <i>state</i>.");
}
extern QString imageText();

// id is an old ident in case of an import
StateDiagramWindow::StateDiagramWindow(const QString & s, BrowserStateDiagram * b, int id)
    : DiagramWindow(b, s), view(0)
{
    Q3ToolBar * toolbar = new Q3ToolBar(this, "state operations");
    addToolBar(toolbar, TR("Toolbar"), Qt::DockTop, TRUE);

    add_edit_button(toolbar);

    select =
        new QToolButton(*selectButton, TR("Select"), QString(),
                        this, SLOT(hit_select()), toolbar, "select");
    select->setToggleButton(TRUE);
    select->setOn(TRUE);
    current_button = UmlSelect;

    addPackage
        = new QToolButton(*packageButton, TR("Add Package"), QString(),
                          this, SLOT(hit_package()), toolbar, "add package");
    addPackage->setToggleButton(TRUE);
    Q3WhatsThis::add(addPackage, addpackageText());

    addFragment
        = new QToolButton(*fragmentButton, TR("Add Fragment"), QString(),
                          this, SLOT(hit_fragment()), toolbar, "add fragment");
    addFragment->setToggleButton(TRUE);
    Q3WhatsThis::add(addFragment, addfragmentText());

    addState =
        new QToolButton(*stateButton, TR("Add State"), QString(),
                        this, SLOT(hit_state()), toolbar, "add state");
    addState->setToggleButton(TRUE);
    Q3WhatsThis::add(addState, addstateText());

    addRegion =
        new QToolButton(*regionButton, TR("Add Region"), QString(),
                        this, SLOT(hit_region()), toolbar, "add region");
    addRegion->setToggleButton(TRUE);
    Q3WhatsThis::add(addRegion, addregionText());

    addInitial =
        new QToolButton(*initialButton, TR("Add Initial pseudo state"), QString(),
                        this, SLOT(hit_initial()), toolbar, "add initial");
    addInitial->setToggleButton(TRUE);
    Q3WhatsThis::add(addInitial, addinitialText());

    addEntryPoint =
        new QToolButton(*entrypointButton, TR("Add Entry Point"), QString(),
                        this, SLOT(hit_entryPoint()), toolbar, "add entry point");
    addEntryPoint->setToggleButton(TRUE);
    Q3WhatsThis::add(addEntryPoint, addentrypointText());

    addFinal =
        new QToolButton(*finalButton, TR("Add Final state"), QString(),
                        this, SLOT(hit_final()), toolbar, "add final");
    addFinal->setToggleButton(TRUE);
    Q3WhatsThis::add(addFinal, addfinalText());

    addExitPoint =
        new QToolButton(*exitpointButton, TR("Add Exit Point"), QString(),
                        this, SLOT(hit_exitPoint()), toolbar, "add exit point");
    addExitPoint->setToggleButton(TRUE);
    Q3WhatsThis::add(addExitPoint, addexitpointText());

    addTerminate =
        new QToolButton(*terminateButton, TR("Add Terminate node"), QString(),
                        this, SLOT(hit_terminate()), toolbar, "add terminate");
    addTerminate->setToggleButton(TRUE);
    Q3WhatsThis::add(addTerminate, addterminateText());

    addDeepHistory =
        new QToolButton(*deephistoryButton, TR("Add Deep History"), QString(),
                        this, SLOT(hit_deepHistory()), toolbar, "add deep history");
    addDeepHistory->setToggleButton(TRUE);
    Q3WhatsThis::add(addDeepHistory, adddeephistoryText());

    addShallowHistory =
        new QToolButton(*shallowhistoryButton, TR("Add Shallow History"), QString(),
                        this, SLOT(hit_shallowHistory()), toolbar, "add shallow history");
    addShallowHistory->setToggleButton(TRUE);
    Q3WhatsThis::add(addShallowHistory, addshallowhistoryText());

    addJunction =
        new QToolButton(*junctionButton, TR("Add Junction"), QString(),
                        this, SLOT(hit_junction()), toolbar, "add junction");
    addJunction->setToggleButton(TRUE);
    Q3WhatsThis::add(addJunction, addjunctionText());

    addChoice =
        new QToolButton(*choiceButton, TR("Add Choice"), QString(),
                        this, SLOT(hit_choice()), toolbar, "add choice");
    addChoice->setToggleButton(TRUE);
    Q3WhatsThis::add(addChoice, addchoiceText());

    addFork =
        new QToolButton(*forkButton, TR("Add Fork"), QString(),
                        this, SLOT(hit_fork()), toolbar, "add fork");
    addFork->setToggleButton(TRUE);
    Q3WhatsThis::add(addFork, addforkText());

    addJoin =
        new QToolButton(*joinButton, TR("Add Join"), QString(),
                        this, SLOT(hit_join()), toolbar, "add join");
    addJoin->setToggleButton(TRUE);
    Q3WhatsThis::add(addJoin, addjoinText());

    addAction =
        new QToolButton(*actionButton, TR("Add Action"), QString(),
                        this, SLOT(hit_action()), toolbar, "add action");
    addAction->setToggleButton(TRUE);
    Q3WhatsThis::add(addAction, addactionText());

    addSignalIn =
        new QToolButton(*signalinButton, TR("Add receive signal action"), QString(),
                        this, SLOT(hit_signalin()), toolbar, "add receive signal action");
    addSignalIn->setToggleButton(TRUE);
    Q3WhatsThis::add(addSignalIn, addsignalinText());

    addSignalOut =
        new QToolButton(*signaloutButton, TR("Add send signal action"), QString(),
                        this, SLOT(hit_signalout()), toolbar, "add send signal action");
    addSignalOut->setToggleButton(TRUE);
    Q3WhatsThis::add(addSignalOut, addsignaloutText());

    addTransition =
        new QToolButton(*directionalAssociationButton, TR("Add Transition"), QString(),
                        this, SLOT(hit_transition()), toolbar, "add transition");
    addTransition->setToggleButton(TRUE);
    Q3WhatsThis::add(addTransition, addtransitionText());

    /*
    dependency =
      new QToolButton(*dependencyButton, "Dependency", QString(),
    	    this, SLOT(hit_dependency()), toolbar, "dependency");
    dependency->setToggleButton(TRUE);
    QWhatsThis::add(dependency, dependencyText());
    */

    note =
        new QToolButton(*noteButton, TR("Note"), QString(),
                        this, SLOT(hit_note()), toolbar, "note");
    note->setToggleButton(TRUE);
    Q3WhatsThis::add(note, noteText());

    anchor =
        new QToolButton(*anchorButton, TR("Anchor"), QString(),
                        this, SLOT(hit_anchor()), toolbar, "anchor");
    anchor->setToggleButton(TRUE);
    Q3WhatsThis::add(anchor, anchorText());

    text =
        new QToolButton(*textButton, TR("Text"), QString(),
                        this, SLOT(hit_text()), toolbar, "text");
    text->setToggleButton(TRUE);
    Q3WhatsThis::add(text, textText());

    image =
        new QToolButton(*imageButton, TR("Image"), QString(),
                        this, SLOT(hit_image()), toolbar, "image");
    image->setToggleButton(TRUE);
    Q3WhatsThis::add(image, imageText());

    toolbar->addSeparator();

    add_scale_cmd(toolbar);

    //

    view = new StateDiagramView(this, canvas, (id != -1) ? id : b->get_ident());
    setFocusProxy(view);
    setCentralWidget(view);

    //qApp->setMainWidget(this);

    QWorkspace * w = UmlWindow::get_workspace();

    resize((w->width() * 4) / 5, (w->height() * 4) / 5);

    /*if (w->windowList().isEmpty())
      showMaximized();
    else*/
    show();

    view->preferred_size_zoom();

    //qApp->setMainWidget(0);
}

StateDiagramWindow::~StateDiagramWindow()
{
    if (! no_save) {
        QString warning = "!";
        BooL is_new = FALSE;

        save("d", warning, is_new);
        warning.remove(0, 1);	// removes !
        view->hide();

        if (!warning.isEmpty())
            warn(warning);
    }

    browser_node->on_close();
}

DiagramView * StateDiagramWindow::get_view() const
{
    return view;
}

void StateDiagramWindow::hit_button(UmlCode c, QToolButton * b)
{
    view->abort_line_construction();

    select->setOn(FALSE);
    addPackage->setOn(FALSE);
    addFragment->setOn(FALSE);
    addState->setOn(FALSE);
    addRegion->setOn(FALSE);
    addEntryPoint->setOn(FALSE);
    addExitPoint->setOn(FALSE);
    addInitial->setOn(FALSE);
    addFinal->setOn(FALSE);
    addTerminate->setOn(FALSE);
    addDeepHistory->setOn(FALSE);
    addShallowHistory->setOn(FALSE);
    addJunction->setOn(FALSE);
    addChoice->setOn(FALSE);
    addFork->setOn(FALSE);
    addJoin->setOn(FALSE);
    addAction->setOn(FALSE);
    addSignalIn->setOn(FALSE);
    addSignalOut->setOn(FALSE);
    addTransition->setOn(FALSE);
    //dependency->setOn(FALSE);
    note->setOn(FALSE);
    anchor->setOn(FALSE);
    text->setOn(FALSE);
    image->setOn(FALSE);

    b->setOn(TRUE);
    current_button = c;
}

void StateDiagramWindow::hit_package()
{
    hit_button(UmlPackage, addPackage);
}

void StateDiagramWindow::hit_fragment()
{
    hit_button(UmlFragment, addFragment);
}

void StateDiagramWindow::hit_state()
{
    hit_button(UmlState, addState);
}

void StateDiagramWindow::hit_region()
{
    hit_button(UmlRegion, addRegion);
}

void StateDiagramWindow::hit_entryPoint()
{
    hit_button(EntryPointPS, addEntryPoint);
}

void StateDiagramWindow::hit_exitPoint()
{
    hit_button(ExitPointPS, addExitPoint);
}

void StateDiagramWindow::hit_initial()
{
    hit_button(InitialPS, addInitial);
}

void StateDiagramWindow::hit_final()
{
    hit_button(FinalPS, addFinal);
}

void StateDiagramWindow::hit_terminate()
{
    hit_button(TerminatePS, addTerminate);
}

void StateDiagramWindow::hit_deepHistory()
{
    hit_button(DeepHistoryPS, addDeepHistory);
}

void StateDiagramWindow::hit_shallowHistory()
{
    hit_button(ShallowHistoryPS, addShallowHistory);
}

void StateDiagramWindow::hit_junction()
{
    hit_button(JunctionPS, addJunction);
}

void StateDiagramWindow::hit_choice()
{
    hit_button(ChoicePS, addChoice);
}

void StateDiagramWindow::hit_fork()
{
    hit_button(ForkPS, addFork);
}

void StateDiagramWindow::hit_join()
{
    hit_button(JoinPS, addJoin);
}

void StateDiagramWindow::hit_action()
{
    hit_button(UmlStateAction, addAction);
}

void StateDiagramWindow::hit_signalin()
{
    hit_button(UmlSignalIn, addSignalIn);
}

void StateDiagramWindow::hit_signalout()
{
    hit_button(UmlSignalOut, addSignalOut);
}

void StateDiagramWindow::hit_transition()
{
    hit_button(UmlTransition, addTransition);
}

/*
void StateDiagramWindow::hit_dependency() {
  hit_button(UmlDependOn, dependency);
}
*/

void StateDiagramWindow::hit_note()
{
    hit_button(UmlNote, note);
}

void StateDiagramWindow::hit_anchor()
{
    hit_button(UmlAnchor, anchor);
}

void StateDiagramWindow::hit_text()
{
    hit_button(UmlText, text);
}

void StateDiagramWindow::hit_image()
{
    hit_button(UmlImage, image);
}

