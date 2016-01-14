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
#include <QMdiArea>
#include <QToolBar>
#include <qtoolbutton.h>
#include <qwhatsthis.h>
#include <qlayout.h>
#include <qspinbox.h>
#include "UmlWindow.h"
#include "ActivityDiagramWindow.h"
#include "ActivityDiagramView.h"
#include "BrowserActivityDiagram.h"
#include "UmlPixmap.h"
#include "myio.h"
#include "translate.h"
#include "toolbarfactory.h"

QString addactivityText()
{
    return  QObject::tr("Click this button to add an <i>activity</i> in the diagram. <br><br>"
              "You can also drop the activity from the <b>browser</b>.");
}
QString addinterruptibleactivityregionText()
{
    return  QObject::tr("Click this button to add an <i>interruptible activity region</i> in the diagram. <br><br>"
              "You can also drop the interruptible activity region from the <b>browser</b>.");
}
QString addexpansionregionText()
{
    return  QObject::tr("Click this button to add an <i>expansion region</i> in the diagram. <br><br>"
              "You can also drop the expansion region from the <b>browser</b>.");
}
QString addactivitypartitionText()
{
    return  QObject::tr("Click this button to add an <i>activity partition</i> in the diagram. <br><br>"
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
    return  QObject::tr("Click this button to add an <i>initial node</i> in the diagram. <br><br>"
              "You can also drop the <i>initial node</i> from the <b>browser</b>.");
}
static QString addactivityfinalText()
{
    return  QObject::tr("Click this button to add an <i>activity final node</i> in the diagram. <br><br>"
              "You can also drop the <i>activity final node</i> from the <b>browser</b>.");
}
static QString addflowfinalText()
{
    return  QObject::tr("Click this button to add a <i>flow final node</i> in the diagram. <br><br>"
              "You can also drop the <i>flow final node</i> from the <b>browser</b>.");
}
static QString adddecisionText()
{
    return  QObject::tr("Click this button to add a <i>decision node</i> in the diagram. <br><br>"
              "You can also drop the <i>decision node</i> from the <b>browser</b>.");
}
static QString addmergeText()
{
    return  QObject::tr("Click this button to add a <i>merge node</i> in the diagram. <br><br>"
              "You can also drop the <i>merge node</i> from the <b>browser</b>.");
}
extern QString addforkText();
extern QString addjoinText();
static QString addactionText()
{
    return  QObject::tr("Click this button to add an <i>action</i> in the diagram.");
}
static QString addobjectText()
{
    return  QObject::tr("Click this button to add an <i>object node</i> in the diagram.");
}
QString addflowText()
{
    return  QObject::tr("Click this button to add a <i>flow</i> in the diagram. <br><br>"
              "You can also drop the <i>flow</i> from the <b>browser</b>.");
}
extern QString imageText();

// id is an old ident in case of an import
ActivityDiagramWindow::ActivityDiagramWindow(const QString & s, BrowserActivityDiagram * b, int id)
    : DiagramWindow(b, s), view(0)
{
    QToolBar * toolbar = new QToolBar( "activity operations", this);
    toolbar->setMinimumHeight(50);
    toolbar->setOrientation(Qt::Horizontal);
    addToolBar(Qt::TopToolBarArea, toolbar);

    add_edit_button(toolbar);

    select =
        ToolBarFactory::createToolButton(*selectButton, tr("Select"), QString(),
                        this, SLOT(hit_select()), toolbar, "select");
    select->setCheckable(TRUE);
    select->setChecked(TRUE);
    current_button = UmlSelect;

    addPackage
        = ToolBarFactory::createToolButton(*packageButton, tr("New Package"), QString(),
                          this, SLOT(hit_package()), toolbar, "add package");
    addPackage->setCheckable(TRUE);
    addPackage->setWhatsThis(addpackageText());

    addFragment
        = ToolBarFactory::createToolButton(*fragmentButton, tr("New Fragment"), QString(),
                          this, SLOT(hit_fragment()), toolbar, "add fragment");
    addFragment->setCheckable(TRUE);
    addFragment->setWhatsThis( addfragmentText());

    addActivity =
        ToolBarFactory::createToolButton(*activityButton, tr("New Activity"), QString(),
                        this, SLOT(hit_activity()), toolbar, "add activity");
    addActivity->setCheckable(TRUE);
    addActivity->setWhatsThis( addactivityText());

    addInterruptibleActivityRegion =
        ToolBarFactory::createToolButton(*interruptibleactivityregionButton,
                        tr("New Interruptible Activity Region"), QString(),
                        this, SLOT(hit_interruptibleactivityregion()),
                        toolbar, "add interruptible activity region");
    addInterruptibleActivityRegion->setCheckable(TRUE);
    addActivity->setWhatsThis(
                     addinterruptibleactivityregionText());

    addExpansionRegion =
        ToolBarFactory::createToolButton(*expansionregionButton,
                        tr("New Expansion Region"), QString(),
                        this, SLOT(hit_expansionregion()),
                        toolbar, "add expansion region");
    addExpansionRegion->setCheckable(TRUE);
    addActivity->setWhatsThis(
                     addexpansionregionText());

    addActivityPartition =
        ToolBarFactory::createToolButton(*activitypartitionButton,
                        tr("New Activity Partition"), QString(),
                        this, SLOT(hit_activitypartition()),
                        toolbar, "add activity partition");
    addActivityPartition->setCheckable(TRUE);
    addActivityPartition->setWhatsThis(
                     addactivitypartitionText());

    addAction =
        ToolBarFactory::createToolButton(*activityactionButton, tr("New Action"), QString(),
                        this, SLOT(hit_action()), toolbar, "add action");
    addAction->setCheckable(TRUE);
    addAction->setWhatsThis( addactionText());

    addObject =
        ToolBarFactory::createToolButton(*actionButton, tr("New Object Node"), QString(),
                        this, SLOT(hit_object()), toolbar, "add object node");
    addObject->setCheckable(TRUE);
    addObject->setWhatsThis( addobjectText());

    addInitial =
        ToolBarFactory::createToolButton(*initialButton, tr("New Initial node"), QString(),
                        this, SLOT(hit_initial()), toolbar, "add initial");
    addInitial->setCheckable(TRUE);
    addInitial->setWhatsThis( addinitialText());

    addActivityFinal =
        ToolBarFactory::createToolButton(*finalButton, tr("New Activity Final"), QString(),
                        this, SLOT(hit_activityfinal()), toolbar, "add activity final");
    addActivityFinal->setCheckable(TRUE);
    addActivityFinal->setWhatsThis( addactivityfinalText());

    addFlowFinal =
        ToolBarFactory::createToolButton(*exitpointButton, tr("New Flow Final"), QString(),
                        this, SLOT(hit_flowfinal()), toolbar, "add flow final");
    addFlowFinal->setCheckable(TRUE);
    addFlowFinal->setWhatsThis( addflowfinalText());

    addMerge =
        ToolBarFactory::createToolButton(*mergeButton, tr("New Merge"), QString(),
                        this, SLOT(hit_merge()), toolbar, "add merge");
    addMerge->setCheckable(TRUE);
    addMerge->setWhatsThis( addmergeText());

    addDecision =
        ToolBarFactory::createToolButton(*decisionButton, tr("New Decision"), QString(),
                        this, SLOT(hit_decision()), toolbar, "add decision");
    addDecision->setCheckable(TRUE);
    addDecision->setWhatsThis( adddecisionText());

    addFork =
        ToolBarFactory::createToolButton(*forkButton, tr("New Fork"), QString(),
                        this, SLOT(hit_fork()), toolbar, "add fork");
    addFork->setCheckable(TRUE);
    addFork->setWhatsThis( addforkText());

    addJoin =
        ToolBarFactory::createToolButton(*joinButton, tr("New Join"), QString(),
                        this, SLOT(hit_join()), toolbar, "add join");
    addJoin->setCheckable(TRUE);
    addJoin->setWhatsThis( addjoinText());

    addFlow =
        ToolBarFactory::createToolButton(*directionalAssociationButton, tr("New Flow"), QString(),
                        this, SLOT(hit_flow()), toolbar, "add flow");
    addFlow->setCheckable(TRUE);
    addFlow->setWhatsThis( addflowText());

    dependency =
        ToolBarFactory::createToolButton(*dependencyButton, tr("Dependency"), QString(),
                        this, SLOT(hit_dependency()), toolbar, "dependency");
    dependency->setCheckable(TRUE);
    dependency->setWhatsThis( dependencyText());

    note =
        ToolBarFactory::createToolButton(*noteButton, tr("Note"), QString(),
                        this, SLOT(hit_note()), toolbar, "note");
    note->setCheckable(TRUE);
    note->setWhatsThis( noteText());

    anchor =
        ToolBarFactory::createToolButton(*anchorButton, tr("Anchor"), QString(),
                        this, SLOT(hit_anchor()), toolbar, "anchor");
    anchor->setCheckable(TRUE);
    anchor->setWhatsThis( anchorText());

    text =
        ToolBarFactory::createToolButton(*textButton, tr("Text"), QString(),
                        this, SLOT(hit_text()), toolbar, "text");
    text->setCheckable(TRUE);
    text->setWhatsThis( textText());

    image =
        ToolBarFactory::createToolButton(*imageButton, tr("Image"), QString(),
                        this, SLOT(hit_image()), toolbar, "image");
    image->setCheckable(TRUE);
    image->setWhatsThis( imageText());

    toolbar->addSeparator();

    add_scale_cmd(toolbar);

    //

    view = new ActivityDiagramView(this, canvas, (id != -1) ? id : b->get_ident());
    setFocusProxy(view);
    setCentralWidget(view);

    //qApp->setMainWidget(this);

    QMdiArea * w = UmlWindow::get_workspace();

    m_containingSubWindow->resize((w->width() * 4) / 5, (w->height() * 4) / 5);

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

    select->setChecked(FALSE);
    addPackage->setChecked(FALSE);
    addFragment->setChecked(FALSE);
    addActivity->setChecked(FALSE);
    addInterruptibleActivityRegion->setChecked(FALSE);
    addExpansionRegion->setChecked(FALSE);
    addActivityPartition->setChecked(FALSE);
    addInitial->setChecked(FALSE);
    addActivityFinal->setChecked(FALSE);
    addFlowFinal->setChecked(FALSE);
    addDecision->setChecked(FALSE);
    addMerge->setChecked(FALSE);
    addFork->setChecked(FALSE);
    addJoin->setChecked(FALSE);
    addAction->setChecked(FALSE);
    addObject->setChecked(FALSE);
    addFlow->setChecked(FALSE);
    dependency->setChecked(FALSE);
    note->setChecked(FALSE);
    anchor->setChecked(FALSE);
    text->setChecked(FALSE);
    image->setChecked(FALSE);

    b->setChecked(TRUE);
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
