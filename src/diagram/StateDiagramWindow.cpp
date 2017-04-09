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
#include <qmdiarea.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qwhatsthis.h>
#include <qlayout.h>
#include <qspinbox.h>
#include "UmlWindow.h"
#include "StateDiagramWindow.h"
#include "StateDiagramView.h"
#include "BrowserStateDiagram.h"
#include "UmlPixmap.h"
#include "myio.h"
#include "translate.h"
#include "toolbarfactory.h"

QString addstateText()
{
    return QObject::tr("Click this button to add a <i>state</i> in the diagram. <br><br>"
              "You can also drop the state from the <b>browser</b>.");
}
extern QString addpackageText();
extern QString addfragmentText();
extern QString noteText();
extern QString anchorText();
extern QString textText();
QString addentrypointText()
{
    return QObject::tr("Click this button to add a <i>entry point</i> in the diagram. <br><br>"
              "You can also drop the <i>entry point</i> from the <b>browser</b>.");
}
QString addexitpointText()
{
    return QObject::tr("Click this button to add a <i>exit point</i> in the diagram. <br><br>"
              "You can also drop the <i>exit point</i> from the <b>browser</b>.");
}
QString addinitialText()
{
    return QObject::tr("Click this button to add a <i>initial pseudo state</i> in the diagram. <br><br>"
              "You can also drop the <i>initial pseudo state</i> from the <b>browser</b>.");
}
QString addfinalText()
{
    return QObject::tr("Click this button to add a <i>final state</i> in the diagram. <br><br>"
              "You can also drop the <i>final state</i> from the <b>browser</b>.");
}
QString addterminateText()
{
    return QObject::tr("Click this button to add a <i>terminate node</i> in the diagram. <br><br>"
              "You can also drop the <i>terminate node</i> from the <b>browser</b>.");
}
QString adddeephistoryText()
{
    return QObject::tr("Click this button to add a <i>deep history</i> in the diagram. <br><br>"
              "You can also drop the <i>deep history</i> from the <b>browser</b>.");
}
QString addshallowhistoryText()
{
    return QObject::tr("Click this button to add a <i>shallow history</i> in the diagram. <br><br>"
              "You can also drop the <i></i> from the <b>browser</b>.");
}
QString addjunctionText()
{
    return QObject::tr("Click this button to add a <i>junction</i> in the diagram. <br><br>"
              "You can also drop the <i>junction</i> from the <b>browser</b>.");
}
QString addchoiceText()
{
    return QObject::tr("Click this button to add a <i>choice</i> in the diagram. <br><br>"
              "You can also drop the <i>choice</i> from the <b>browser</b>.");
}
QString addforkText()
{
    return QObject::tr("Click this button to add a <i>fork</i> in the diagram. <br><br>"
              "You can also drop the <i>foek</i> from the <b>browser</b>.");
}
QString addjoinText()
{
    return QObject::tr("Click this button to add a <i>join</i> in the diagram. <br><br>"
              "You can also drop the <i>join</i> from the <b>browser</b>.");
}
QString addtransitionText()
{
    return QObject::tr("Click this button to add a <i>transition</i> in the diagram. <br><br>"
              "You can also drop the <i>transition</i> from the <b>browser</b>.");
}
QString addregionText()
{
    return QObject::tr("Click this button to add a <i>region</i> in a <i>state</i>.");
}
QString addactionText()
{
    return QObject::tr("Click this button to add an <i>action</i> in a <i>state</i>.");
}
QString addsignalinText()
{
    return QObject::tr("Click this button to add a <i>receive signal action</i> in a <i>state</i>.");
}
QString addsignaloutText()
{
    return QObject::tr("Click this button to add a <i>send signal action</i> in a <i>state</i>.");
}
extern QString imageText();

// id is an old ident in case of an import
StateDiagramWindow::StateDiagramWindow(const QString & s, BrowserStateDiagram * b, int id)
    : DiagramWindow(b, s), view(0)
{
    QToolBar * toolbar = new QToolBar("state operations",this);
    toolbar->setMinimumHeight(50);
    toolbar->setOrientation(Qt::Horizontal);
    addToolBar(Qt::TopToolBarArea, toolbar);

    add_edit_button(toolbar);

    select =
        ToolBarFactory::createToolButton(*selectButton, TR("Select"), QString(),
                        this, SLOT(hit_select()), toolbar, "select");
    select->setCheckable(TRUE);
    select->setChecked(TRUE);
    current_button = UmlSelect;

    addPackage
        = ToolBarFactory::createToolButton(*packageButton, TR("Add Package"), QString(),
                          this, SLOT(hit_package()), toolbar, "add package");
    addPackage->setCheckable(TRUE);
    addPackage->setWhatsThis(addpackageText());

    addFragment
        = ToolBarFactory::createToolButton(*fragmentButton, TR("Add Fragment"), QString(),
                          this, SLOT(hit_fragment()), toolbar, "add fragment");
    addFragment->setCheckable(TRUE);
    addFragment->setWhatsThis( addfragmentText());

    addState =
        ToolBarFactory::createToolButton(*stateButton, TR("Add State"), QString(),
                        this, SLOT(hit_state()), toolbar, "add state");
    addState->setCheckable(TRUE);
    addState->setWhatsThis( addstateText());

    addRegion =
        ToolBarFactory::createToolButton(*regionButton, TR("Add Region"), QString(),
                        this, SLOT(hit_region()), toolbar, "add region");
    addRegion->setCheckable(TRUE);
    addRegion->setWhatsThis( addregionText());

    addInitial =
        ToolBarFactory::createToolButton(*initialButton, TR("Add Initial pseudo state"), QString(),
                        this, SLOT(hit_initial()), toolbar, "add initial");
    addInitial->setCheckable(TRUE);
    addInitial->setWhatsThis( addinitialText());

    addEntryPoint =
        ToolBarFactory::createToolButton(*entrypointButton, TR("Add Entry Point"), QString(),
                        this, SLOT(hit_entryPoint()), toolbar, "add entry point");
    addEntryPoint->setCheckable(TRUE);
    addEntryPoint->setWhatsThis( addentrypointText());

    addFinal =
        ToolBarFactory::createToolButton(*finalButton, TR("Add Final state"), QString(),
                        this, SLOT(hit_final()), toolbar, "add final");
    addFinal->setCheckable(TRUE);
    addFinal->setWhatsThis( addfinalText());

    addExitPoint =
        ToolBarFactory::createToolButton(*exitpointButton, TR("Add Exit Point"), QString(),
                        this, SLOT(hit_exitPoint()), toolbar, "add exit point");
    addExitPoint->setCheckable(TRUE);
    addExitPoint->setWhatsThis( addexitpointText());

    addTerminate =
        ToolBarFactory::createToolButton(*terminateButton, TR("Add Terminate node"), QString(),
                        this, SLOT(hit_terminate()), toolbar, "add terminate");
    addTerminate->setCheckable(TRUE);
    addTerminate->setWhatsThis( addterminateText());

    addDeepHistory =
        ToolBarFactory::createToolButton(*deephistoryButton, TR("Add Deep History"), QString(),
                        this, SLOT(hit_deepHistory()), toolbar, "add deep history");
    addDeepHistory->setCheckable(TRUE);
    addDeepHistory->setWhatsThis( adddeephistoryText());

    addShallowHistory =
        ToolBarFactory::createToolButton(*shallowhistoryButton, TR("Add Shallow History"), QString(),
                        this, SLOT(hit_shallowHistory()), toolbar, "add shallow history");
    addShallowHistory->setCheckable(TRUE);
    addShallowHistory->setWhatsThis( addshallowhistoryText());

    addJunction =
        ToolBarFactory::createToolButton(*junctionButton, TR("Add Junction"), QString(),
                        this, SLOT(hit_junction()), toolbar, "add junction");
    addJunction->setCheckable(TRUE);
    addJunction->setWhatsThis( addjunctionText());

    addChoice =
        ToolBarFactory::createToolButton(*choiceButton, TR("Add Choice"), QString(),
                        this, SLOT(hit_choice()), toolbar, "add choice");
    addChoice->setCheckable(TRUE);
    addChoice->setWhatsThis( addchoiceText());

    addFork =
        ToolBarFactory::createToolButton(*forkButton, TR("Add Fork"), QString(),
                        this, SLOT(hit_fork()), toolbar, "add fork");
    addFork->setCheckable(TRUE);
    addFork->setWhatsThis( addforkText());

    addJoin =
        ToolBarFactory::createToolButton(*joinButton, TR("Add Join"), QString(),
                        this, SLOT(hit_join()), toolbar, "add join");
    addJoin->setCheckable(TRUE);
    addJoin->setWhatsThis( addjoinText());

    addAction =
        ToolBarFactory::createToolButton(*actionButton, TR("Add Action"), QString(),
                        this, SLOT(hit_action()), toolbar, "add action");
    addAction->setCheckable(TRUE);
    addAction->setWhatsThis( addactionText());

    addSignalIn =
        ToolBarFactory::createToolButton(*signalinButton, TR("Add receive signal action"), QString(),
                        this, SLOT(hit_signalin()), toolbar, "add receive signal action");
    addSignalIn->setCheckable(TRUE);
    addSignalIn->setWhatsThis( addsignalinText());

    addSignalOut =
        ToolBarFactory::createToolButton(*signaloutButton, TR("Add send signal action"), QString(),
                        this, SLOT(hit_signalout()), toolbar, "add send signal action");
    addSignalOut->setCheckable(TRUE);
    addSignalOut->setWhatsThis( addsignaloutText());

    addTransition =
        ToolBarFactory::createToolButton(*directionalAssociationButton, TR("Add Transition"), QString(),
                        this, SLOT(hit_transition()), toolbar, "add transition");
    addTransition->setCheckable(TRUE);
    addTransition->setWhatsThis( addtransitionText());

    /*
    dependency =
      ToolBarFactory::createToolButton(*dependencyButton, "Dependency", QString(),
    	    this, SLOT(hit_dependency()), toolbar, "dependency");
    dependency->setCheckable(TRUE);
    QWhatsThis::add(dependency, dependencyText());
    */

    note =
        ToolBarFactory::createToolButton(*noteButton, TR("Note"), QString(),
                        this, SLOT(hit_note()), toolbar, "note");
    note->setCheckable(TRUE);
    note->setWhatsThis( noteText());

    anchor =
        ToolBarFactory::createToolButton(*anchorButton, TR("Anchor"), QString(),
                        this, SLOT(hit_anchor()), toolbar, "anchor");
    anchor->setCheckable(TRUE);
    anchor->setWhatsThis( anchorText());

    text =
        ToolBarFactory::createToolButton(*textButton, TR("Text"), QString(),
                        this, SLOT(hit_text()), toolbar, "text");
    text->setCheckable(TRUE);
    text->setWhatsThis( textText());

    image =
        ToolBarFactory::createToolButton(*imageButton, TR("Image"), QString(),
                        this, SLOT(hit_image()), toolbar, "image");
    image->setCheckable(TRUE);
    image->setWhatsThis( imageText());

    toolbar->addSeparator();

    add_scale_cmd(toolbar);

    //

    view = new StateDiagramView(this, canvas, (id != -1) ? id : b->get_ident());
    setFocusProxy(view);
    setCentralWidget(view);

    //qApp->setMainWidget(this);

    QMdiArea * w = UmlWindow::get_workspace();

    //resize((w->width() * 4) / 5, (w->height() * 4) / 5);
    m_containingSubWindow->resize((w->width() * 4) / 5, (w->height() * 4) / 5);

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

    select->setChecked(FALSE);
    addPackage->setChecked(FALSE);
    addFragment->setChecked(FALSE);
    addState->setChecked(FALSE);
    addRegion->setChecked(FALSE);
    addEntryPoint->setChecked(FALSE);
    addExitPoint->setChecked(FALSE);
    addInitial->setChecked(FALSE);
    addFinal->setChecked(FALSE);
    addTerminate->setChecked(FALSE);
    addDeepHistory->setChecked(FALSE);
    addShallowHistory->setChecked(FALSE);
    addJunction->setChecked(FALSE);
    addChoice->setChecked(FALSE);
    addFork->setChecked(FALSE);
    addJoin->setChecked(FALSE);
    addAction->setChecked(FALSE);
    addSignalIn->setChecked(FALSE);
    addSignalOut->setChecked(FALSE);
    addTransition->setChecked(FALSE);
    //dependency->setChecked(FALSE);
    note->setChecked(FALSE);
    anchor->setChecked(FALSE);
    text->setChecked(FALSE);
    image->setChecked(FALSE);

    b->setChecked(TRUE);
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

