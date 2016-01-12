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
#include "DeploymentDiagramWindow.h"
#include "DeploymentDiagramView.h"
#include "BrowserDeploymentDiagram.h"
#include "UmlPixmap.h"
#include "myio.h"
#include "translate.h"
#include "toolbarfactory.h"

QString adddeploymentnodeText()
{
    return  QObject::tr("Click this button to add a <i>node</i> in the diagram. <br><br>"
              "You can also drop the node from the <b>browser</b>.");
}
extern QString addpackageText();
extern QString addfragmentText();
QString networkText()
{
    return  QObject::tr("Click this button to add a <i>network</i> in the diagram.");
}
QString hubText()
{
    return  QObject::tr("Click this button to add a <i>network connexion/ending</i> in the diagram.");
}
QString addartifactText()
{
    return  QObject::tr("Click this button to add an <i>artifact</i> in the diagram.");
}
extern QString addcomponentText();
extern QString dependencyText();
extern QString associationText();
extern QString inheritText();
extern QString noteText();
extern QString anchorText();
extern QString textText();
extern QString imageText();

// id is an old ident in case of an import
DeploymentDiagramWindow::DeploymentDiagramWindow(const QString & s, BrowserDeploymentDiagram * b, int id)
    : DiagramWindow(b, s), view(0)
{
    QToolBar * toolbar = new QToolBar("deployment operations", this);
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
        = ToolBarFactory::createToolButton(*packageButton, tr("Add Package"), QString(),
                          this, SLOT(hit_package()), toolbar, "add package");
    addPackage->setCheckable(TRUE);
    addPackage->setWhatsThis(addpackageText());

    addFragment
        = ToolBarFactory::createToolButton(*fragmentButton, tr("Add Fragment"), QString(),
                          this, SLOT(hit_fragment()), toolbar, "add fragment");
    addFragment->setCheckable(TRUE);
    addFragment->setWhatsThis(addfragmentText());

    addDeploymentNode =
        ToolBarFactory::createToolButton(*deploymentNodeButton, tr("Add Deployment Node"), QString(),
                        this, SLOT(hit_deploymentnode()), toolbar, "add deployment node");
    addDeploymentNode->setCheckable(TRUE);
    addDeploymentNode->setWhatsThis(adddeploymentnodeText());

    addArtifact =
        ToolBarFactory::createToolButton(*artifactButton, tr("Add Artifact"), QString(),
                        this, SLOT(hit_artifact()), toolbar, "add artifact");
    addArtifact->setCheckable(TRUE);
    addArtifact->setWhatsThis(addartifactText());

    addComponent =
        ToolBarFactory::createToolButton(*componentButton, tr("Add Component"), QString(),
                        this, SLOT(hit_component()), toolbar, "add component");
    addComponent->setCheckable(TRUE);
    addComponent->setWhatsThis(addcomponentText());

    hub =
        ToolBarFactory::createToolButton(*hubButton, tr("Network connexion/ending"), QString(),
                        this, SLOT(hit_hub()), toolbar, "network connexion/ending");
    hub->setCheckable(TRUE);
    hub->setWhatsThis(hubText());

    network =
        ToolBarFactory::createToolButton(*associationButton, tr("Network"), QString(),
                        this, SLOT(hit_network()), toolbar, "network");
    network->setCheckable(TRUE);
    network->setWhatsThis(networkText());

    inherit =
        ToolBarFactory::createToolButton(*generalisationButton, tr("Inheritance"), QString(),
                        this, SLOT(hit_inherit()), toolbar, "inheritance");
    inherit->setCheckable(TRUE);
    inherit->setWhatsThis(inheritText());

    association =
        ToolBarFactory::createToolButton(*directionalAssociationButton, tr("Association"), QString(),
                        this, SLOT(hit_association()), toolbar, "association");
    association->setCheckable(TRUE);
    association->setWhatsThis(associationText());

    dependency =
        ToolBarFactory::createToolButton(*dependencyButton, tr("Dependency"), QString(),
                        this, SLOT(hit_dependency()), toolbar, "dependency");
    dependency->setCheckable(TRUE);
    dependency->setWhatsThis(dependencyText());

    note =
        ToolBarFactory::createToolButton(*noteButton, tr("Note"), QString(),
                        this, SLOT(hit_note()), toolbar, "note");
    note->setCheckable(TRUE);
    note->setWhatsThis(noteText());

    anchor =
        ToolBarFactory::createToolButton(*anchorButton, tr("Anchor"), QString(),
                        this, SLOT(hit_anchor()), toolbar, "anchor");
    anchor->setCheckable(TRUE);
    anchor->setWhatsThis(anchorText());

    text =
        ToolBarFactory::createToolButton(*textButton, tr("Text"), QString(),
                        this, SLOT(hit_text()), toolbar, "text");
    text->setCheckable(TRUE);
    text->setWhatsThis(textText());

    image =
        ToolBarFactory::createToolButton(*imageButton, tr("Image"), QString(),
                        this, SLOT(hit_image()), toolbar, "image");
    image->setCheckable(TRUE);
    image->setWhatsThis(imageText());

    toolbar->addSeparator();

    add_scale_cmd(toolbar);

    //

    view = new DeploymentDiagramView(this, canvas, (id != -1) ? id : b->get_ident());
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

DeploymentDiagramWindow::~DeploymentDiagramWindow()
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

DiagramView * DeploymentDiagramWindow::get_view() const
{
    return view;
}

void DeploymentDiagramWindow::hit_button(UmlCode c, QToolButton * b)
{
    view->abort_line_construction();

    select->setChecked(FALSE);
    addPackage->setChecked(FALSE);
    addFragment->setChecked(FALSE);
    addDeploymentNode->setChecked(FALSE);
    addArtifact->setChecked(FALSE);
    addComponent->setChecked(FALSE);
    hub->setChecked(FALSE);
    network->setChecked(FALSE);
    inherit->setChecked(FALSE);
    association->setChecked(FALSE);
    dependency->setChecked(FALSE);
    note->setChecked(FALSE);
    anchor->setChecked(FALSE);
    text->setChecked(FALSE);
    image->setChecked(FALSE);

    b->setChecked(TRUE);
    current_button = c;
}

void DeploymentDiagramWindow::hit_package()
{
    hit_button(UmlPackage, addPackage);
}

void DeploymentDiagramWindow::hit_fragment()
{
    hit_button(UmlFragment, addFragment);
}

void DeploymentDiagramWindow::hit_deploymentnode()
{
    hit_button(UmlDeploymentNode, addDeploymentNode);
}

void DeploymentDiagramWindow::hit_artifact()
{
    hit_button(UmlArtifact, addArtifact);
}

void DeploymentDiagramWindow::hit_component()
{
    hit_button(UmlComponent, addComponent);
}

void DeploymentDiagramWindow::hit_hub()
{
    hit_button(UmlHub, hub);
}

void DeploymentDiagramWindow::hit_network()
{
    hit_button(UmlAssociation, network);
}

void DeploymentDiagramWindow::hit_inherit()
{
    hit_button(UmlGeneralisation, inherit);
}

void DeploymentDiagramWindow::hit_association()
{
    hit_button(UmlContain, association);
}

void DeploymentDiagramWindow::hit_dependency()
{
    hit_button(UmlDependency, dependency);
}

void DeploymentDiagramWindow::hit_note()
{
    hit_button(UmlNote, note);
}

void DeploymentDiagramWindow::hit_anchor()
{
    hit_button(UmlAnchor, anchor);
}

void DeploymentDiagramWindow::hit_text()
{
    hit_button(UmlText, text);
}

void DeploymentDiagramWindow::hit_image()
{
    hit_button(UmlImage, image);
}
