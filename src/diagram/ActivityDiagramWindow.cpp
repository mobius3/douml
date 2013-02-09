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
#include "ActivityDiagramWindow.h"
#include "ActivityDiagramView.h"
#include "BrowserActivityDiagram.h"
#include "UmlPixmap.h"
#include "myio.h"
#include "translate.h"

QString addactivityText()
{
    return TR("Click this button to add an <i>activity</i> in the diagram. <br><br>"
              "You can also drop the activity from the <b>browser</b>.");
}
QString addinterruptibleactivityregionText()
{
    return TR("Click this button to add an <i>interruptible activity region</i> in the diagram. <br><br>"
              "You can also drop the interruptible activity region from the <b>browser</b>.");
}
QString addexpansionregionText()
{
    return TR("Click this button to add an <i>expansion region</i> in the diagram. <br><br>"
              "You can also drop the expansion region from the <b>browser</b>.");
}
QString addactivitypartitionText()
{
    return TR("Click this button to add an <i>activity partition</i> in the diagram. <br><br>"
              "You can also drop the activity partition from the <b>browser</b>.");
}
extern QString addpackageText();
extern QString addfragmentText();
extern QString noteText();
extern QString anchorText();
extern QString textText();
extern QString dependencyText();
static QString addinitialText()
{
    return TR("Click this button to add an <i>initial node</i> in the diagram. <br><br>"
              "You can also drop the <i>initial node</i> from the <b>browser</b>.");
}
static QString addactivityfinalText()
{
    return TR("Click this button to add an <i>activity final node</i> in the diagram. <br><br>"
              "You can also drop the <i>activity final node</i> from the <b>browser</b>.");
}
static QString addflowfinalText()
{
    return TR("Click this button to add a <i>flow final node</i> in the diagram. <br><br>"
              "You can also drop the <i>flow final node</i> from the <b>browser</b>.");
}
static QString adddecisionText()
{
    return TR("Click this button to add a <i>decision node</i> in the diagram. <br><br>"
              "You can also drop the <i>decision node</i> from the <b>browser</b>.");
}
static QString addmergeText()
{
    return TR("Click this button to add a <i>merge node</i> in the diagram. <br><br>"
              "You can also drop the <i>merge node</i> from the <b>browser</b>.");
}
extern QString addforkText();
extern QString addjoinText();
static QString addactionText()
{
    return TR("Click this button to add an <i>action</i> in the diagram.");
}
static QString addobjectText()
{
    return TR("Click this button to add an <i>object node</i> in the diagram.");
}
QString addflowText()
{
    return TR("Click this button to add a <i>flow</i> in the diagram. <br><br>"
              "You can also drop the <i>flow</i> from the <b>browser</b>.");
}
extern QString imageText();

// id is an old ident in case of an import
ActivityDiagramWindow::ActivityDiagramWindow(const QString & s, BrowserActivityDiagram * b, int id)
    : DiagramWindow(b, s), view(0)
{
    Q3ToolBar * toolbar = new Q3ToolBar(this, "activity operations");
    addToolBar(toolbar, TR("Toolbar"), Qt::DockTop, TRUE);

    add_edit_button(toolbar);

    select =
        new QToolButton(*selectButton, TR("Select"), QString(),
                        this, SLOT(hit_select()), toolbar, "select");
    select->setToggleButton(TRUE);
    select->setOn(TRUE);
    current_button = UmlSelect;

    addPackage
        = new QToolButton(*packageButton, TR("New Package"), QString(),
                          this, SLOT(hit_package()), toolbar, "add package");
    addPackage->setToggleButton(TRUE);
    Q3WhatsThis::add(addPackage, addpackageText());

    addFragment
        = new QToolButton(*fragmentButton, TR("New Fragment"), QString(),
                          this, SLOT(hit_fragment()), toolbar, "add fragment");
    addFragment->setToggleButton(TRUE);
    Q3WhatsThis::add(addFragment, addfragmentText());

    addActivity =
        new QToolButton(*activityButton, TR("New Activity"), QString(),
                        this, SLOT(hit_activity()), toolbar, "add activity");
    addActivity->setToggleButton(TRUE);
    Q3WhatsThis::add(addActivity, addactivityText());

    addInterruptibleActivityRegion =
        new QToolButton(*interruptibleactivityregionButton,
                        TR("New Interruptible Activity Region"), QString(),
                        this, SLOT(hit_interruptibleactivityregion()),
                        toolbar, "add interruptible activity region");
    addInterruptibleActivityRegion->setToggleButton(TRUE);
    Q3WhatsThis::add(addInterruptibleActivityRegion,
                     addinterruptibleactivityregionText());

    addExpansionRegion =
        new QToolButton(*expansionregionButton,
                        TR("New Expansion Region"), QString(),
                        this, SLOT(hit_expansionregion()),
                        toolbar, "add expansion region");
    addExpansionRegion->setToggleButton(TRUE);
    Q3WhatsThis::add(addExpansionRegion,
                     addexpansionregionText());

    addActivityPartition =
        new QToolButton(*activitypartitionButton,
                        TR("New Activity Partition"), QString(),
                        this, SLOT(hit_activitypartition()),
                        toolbar, "add activity partition");
    addActivityPartition->setToggleButton(TRUE);
    Q3WhatsThis::add(addActivityPartition,
                     addactivitypartitionText());

    addAction =
        new QToolButton(*activityactionButton, TR("New Action"), QString(),
                        this, SLOT(hit_action()), toolbar, "add action");
    addAction->setToggleButton(TRUE);
    Q3WhatsThis::add(addAction, addactionText());

    addObject =
        new QToolButton(*actionButton, TR("New Object Node"), QString(),
                        this, SLOT(hit_object()), toolbar, "add object node");
    addObject->setToggleButton(TRUE);
    Q3WhatsThis::add(addObject, addobjectText());

    addInitial =
        new QToolButton(*initialButton, TR("New Initial node"), QString(),
                        this, SLOT(hit_initial()), toolbar, "add initial");
    addInitial->setToggleButton(TRUE);
    Q3WhatsThis::add(addInitial, addinitialText());

    addActivityFinal =
        new QToolButton(*finalButton, TR("New Activity Final"), QString(),
                        this, SLOT(hit_activityfinal()), toolbar, "add activity final");
    addActivityFinal->setToggleButton(TRUE);
    Q3WhatsThis::add(addActivityFinal, addactivityfinalText());

    addFlowFinal =
        new QToolButton(*exitpointButton, TR("New Flow Final"), QString(),
                        this, SLOT(hit_flowfinal()), toolbar, "add flow final");
    addFlowFinal->setToggleButton(TRUE);
    Q3WhatsThis::add(addFlowFinal, addflowfinalText());

    addMerge =
        new QToolButton(*mergeButton, TR("New Merge"), QString(),
                        this, SLOT(hit_merge()), toolbar, "add merge");
    addMerge->setToggleButton(TRUE);
    Q3WhatsThis::add(addMerge, addmergeText());

    addDecision =
        new QToolButton(*decisionButton, TR("New Decision"), QString(),
                        this, SLOT(hit_decision()), toolbar, "add decision");
    addDecision->setToggleButton(TRUE);
    Q3WhatsThis::add(addDecision, adddecisionText());

    addFork =
        new QToolButton(*forkButton, TR("New Fork"), QString(),
                        this, SLOT(hit_fork()), toolbar, "add fork");
    addFork->setToggleButton(TRUE);
    Q3WhatsThis::add(addFork, addforkText());

    addJoin =
        new QToolButton(*joinButton, TR("New Join"), QString(),
                        this, SLOT(hit_join()), toolbar, "add join");
    addJoin->setToggleButton(TRUE);
    Q3WhatsThis::add(addJoin, addjoinText());

    addFlow =
        new QToolButton(*directionalAssociationButton, TR("New Flow"), QString(),
                        this, SLOT(hit_flow()), toolbar, "add flow");
    addFlow->setToggleButton(TRUE);
    Q3WhatsThis::add(addFlow, addflowText());

    dependency =
        new QToolButton(*dependencyButton, TR("Dependency"), QString(),
                        this, SLOT(hit_dependency()), toolbar, "dependency");
    dependency->setToggleButton(TRUE);
    Q3WhatsThis::add(dependency, dependencyText());

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

    view = new ActivityDiagramView(this, canvas, (id != -1) ? id : b->get_ident());
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

ActivityDiagramWindow::~ActivityDiagramWindow()
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

DiagramView * ActivityDiagramWindow::get_view() const
{
    return view;
}

void ActivityDiagramWindow::hit_button(UmlCode c, QToolButton * b)
{
    view->abort_line_construction();

    select->setOn(FALSE);
    addPackage->setOn(FALSE);
    addFragment->setOn(FALSE);
    addActivity->setOn(FALSE);
    addInterruptibleActivityRegion->setOn(FALSE);
    addExpansionRegion->setOn(FALSE);
    addActivityPartition->setOn(FALSE);
    addInitial->setOn(FALSE);
    addActivityFinal->setOn(FALSE);
    addFlowFinal->setOn(FALSE);
    addDecision->setOn(FALSE);
    addMerge->setOn(FALSE);
    addFork->setOn(FALSE);
    addJoin->setOn(FALSE);
    addAction->setOn(FALSE);
    addObject->setOn(FALSE);
    addFlow->setOn(FALSE);
    dependency->setOn(FALSE);
    note->setOn(FALSE);
    anchor->setOn(FALSE);
    text->setOn(FALSE);
    image->setOn(FALSE);

    b->setOn(TRUE);
    current_button = c;
}

void ActivityDiagramWindow::hit_package()
{
    hit_button(UmlPackage, addPackage);
}

void ActivityDiagramWindow::hit_fragment()
{
    hit_button(UmlFragment, addFragment);
}

void ActivityDiagramWindow::hit_activity()
{
    hit_button(UmlActivity, addActivity);
}

void ActivityDiagramWindow::hit_interruptibleactivityregion()
{
    hit_button(UmlInterruptibleActivityRegion,
               addInterruptibleActivityRegion);
}

void ActivityDiagramWindow::hit_expansionregion()
{
    hit_button(UmlExpansionRegion,
               addExpansionRegion);
}

void ActivityDiagramWindow::hit_activitypartition()
{
    hit_button(UmlActivityPartition,
               addActivityPartition);
}

void ActivityDiagramWindow::hit_initial()
{
    hit_button(InitialAN, addInitial);
}

void ActivityDiagramWindow::hit_activityfinal()
{
    hit_button(ActivityFinalAN, addActivityFinal);
}

void ActivityDiagramWindow::hit_flowfinal()
{
    hit_button(FlowFinalAN, addFlowFinal);
}

void ActivityDiagramWindow::hit_decision()
{
    hit_button(DecisionAN, addDecision);
}

void ActivityDiagramWindow::hit_merge()
{
    hit_button(MergeAN, addMerge);
}

void ActivityDiagramWindow::hit_fork()
{
    hit_button(ForkAN, addFork);
}

void ActivityDiagramWindow::hit_join()
{
    hit_button(JoinAN, addJoin);
}

void ActivityDiagramWindow::hit_action()
{
    hit_button(UmlActivityAction, addAction);
}

void ActivityDiagramWindow::hit_object()
{
    hit_button(UmlActivityObject, addObject);
}

void ActivityDiagramWindow::hit_flow()
{
    hit_button(UmlFlow, addFlow);
}

void ActivityDiagramWindow::hit_dependency()
{
    hit_button(UmlDependOn, dependency);
}

void ActivityDiagramWindow::hit_note()
{
    hit_button(UmlNote, note);
}

void ActivityDiagramWindow::hit_anchor()
{
    hit_button(UmlAnchor, anchor);
}

void ActivityDiagramWindow::hit_text()
{
    hit_button(UmlText, text);
}

void ActivityDiagramWindow::hit_image()
{
    hit_button(UmlImage, image);
}
