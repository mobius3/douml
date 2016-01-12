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





#include <stdio.h>

//#include <gridbox.h>
//#include <q3vbox.h>
#include <qlabel.h>

#include "StereotypesDialog.h"
#include "BrowserPackage.h"
#include "BrowserClass.h"
#include "BrowserUseCase.h"
#include "BrowserAttribute.h"
#include "BrowserOperation.h"
#include "BrowserState.h"
#include "BrowserActivity.h"
#include "BrowserInterruptibleActivityRegion.h"
#include "BrowserExpansionRegion.h"
#include "BrowserExpansionNode.h"
#include "BrowserActivityNode.h"
#include "BrowserActivityAction.h"
#include "BrowserActivityObject.h"
#include "BrowserActivityPartition.h"
#include "BrowserPin.h"
#include "BrowserFlow.h"
#include "BrowserParameter.h"
#include "BrowserParameterSet.h"
#include "BrowserPseudoState.h"
#include "BrowserStateAction.h"
#include "BrowserComponent.h"
#include "BrowserArtifact.h"
#include "BrowserDeploymentNode.h"
#include "BrowserClassView.h"
#include "BrowserUseCaseView.h"
#include "BrowserComponentView.h"
#include "BrowserDeploymentView.h"
#include "BrowserClassDiagram.h"
#include "BrowserObjectDiagram.h"
#include "BrowserColDiagram.h"
#include "BrowserSeqDiagram.h"
#include "BrowserUseCaseDiagram.h"
#include "BrowserStateDiagram.h"
#include "BrowserActivityDiagram.h"
#include "BrowserComponentDiagram.h"
#include "BrowserDeploymentDiagram.h"
#include "UmlDesktop.h"
#include "DialogUtil.h"
#include "MyTable.h"
#include "UmlPixmap.h"
#include "strutil.h"
#include "translate.h"
#include "widgetwithlayout.h"
#include <QLayout>
#include <QHeaderView>
#include "gridbox.h"
QSize StereotypesDialog::previous_size;

StereotypesDialog::StereotypesDialog()
    : TabDialog(0, "Default stereotypes dialog", TRUE)
{
    setWindowTitle(tr("Default stereotypes dialog"));

    setOkButton(tr("OK"));
    setCancelButton(tr("Cancel"));

    const QString space(" ");
    GridBox * grid;

    // package tab

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(tr("package\nstereotypes : "), grid));
    package_list = new LineEdit("",grid);
    grid->addWidget(package_list);
    package_list->setTheText(BrowserPackage::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("relations\nstereotypes : "), grid));
    packagetable = new MyTable(1, 1, grid);
    grid->addWidget(packagetable);
    packagetable->setHorizontalHeaderLabels(QStringList()<<tr("Stereotypes"));

    packagetable->setVerticalHeaderLabel(0, QIcon(*dependencyButton), "");
    packagetable->setText(0, 0, BrowserPackage::relation_default_stereotypes.join(space));
    packagetable->setColumnStretchable(0, TRUE);
    packagetable->setRowStretchable(0, TRUE);

    addTab(grid, QObject::tr("Package"));

    // class tab

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(tr("class\nstereotypes : "), grid));
    class_list = new LineEdit(grid);
    grid->addWidget(class_list);
    class_list->setTheText(BrowserClass::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("attribute\nstereotypes : "), grid));
    attribute_list = new LineEdit(grid);
    grid->addWidget(attribute_list);
    attribute_list->setTheText(BrowserAttribute::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("operation\nstereotypes : "), grid));
    operation_list = new LineEdit(grid);
    grid->addWidget(operation_list);
    operation_list->setTheText(BrowserOperation::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("relations\nstereotypes : "), grid));
    classtable = new MyTable(9, 1, grid);
    grid->addWidget(classtable);
    classtable->setHorizontalHeaderLabel(0, QObject::tr("Stereotypes"));
    classtable->setVerticalHeaderLabel(0, QIcon(*generalisationButton), "");
    classtable->setText(0, 0, BrowserClass::relations_default_stereotypes[UmlGeneralisation].join(space));
    classtable->setVerticalHeaderLabel(1, QIcon(*directionalAssociationButton), "");
    classtable->setText(1, 0, BrowserClass::relations_default_stereotypes[UmlDirectionalAssociation].join(space));
    classtable->setVerticalHeaderLabel(2, QIcon(*associationButton), "");
    classtable->setText(2, 0, BrowserClass::relations_default_stereotypes[UmlAssociation].join(space));
    classtable->setVerticalHeaderLabel(3, QIcon(*aggregationButton), "");
    classtable->setText(3, 0, BrowserClass::relations_default_stereotypes[UmlAggregation].join(space));
    classtable->setVerticalHeaderLabel(4, QIcon(*aggregationByValueButton), "");
    classtable->setText(4, 0, BrowserClass::relations_default_stereotypes[UmlAggregationByValue].join(space));
    classtable->setVerticalHeaderLabel(5, QIcon(*directionalAggregationButton), "");
    classtable->setText(5, 0, BrowserClass::relations_default_stereotypes[UmlDirectionalAggregation].join(space));
    classtable->setVerticalHeaderLabel(6, QIcon(*directionalAggregationByValueButton), "");
    classtable->setText(6, 0, BrowserClass::relations_default_stereotypes[UmlDirectionalAggregationByValue].join(space));
    classtable->setVerticalHeaderLabel(7, QIcon(*dependencyButton), "");
    classtable->setText(7, 0, BrowserClass::relations_default_stereotypes[UmlDependency].join(space));
    classtable->setVerticalHeaderLabel(8, QIcon(*realizeButton), "");
    classtable->setText(8, 0, BrowserClass::relations_default_stereotypes[UmlRealize].join(space));
    classtable->setColumnStretchable(0, TRUE);

    addTab(grid, QObject::tr("Class"));

    // Use case

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(tr("use case\nstereotypes : "), grid));
    usecase_list = new LineEdit(grid);
    grid->addWidget(usecase_list);
    usecase_list->setTheText(BrowserUseCase::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("relations\nstereotypes : "), grid));
    usecasetable = new MyTable(3, 1, grid);
    grid->addWidget(usecasetable);

    usecasetable->setHorizontalHeaderLabel(0, QObject::tr("Stereotypes"));
    usecasetable->setVerticalHeaderLabel(0, QIcon(*generalisationButton), "");
    usecasetable->setText(0, 0, BrowserUseCase::relations_default_stereotypes[UmlGeneralisation].join(space));
    usecasetable->setVerticalHeaderLabel(1, QIcon(*associationButton), "");
    usecasetable->setText(1, 0, BrowserUseCase::relations_default_stereotypes[UmlAssociation].join(space));
    usecasetable->setVerticalHeaderLabel(2, QIcon(*dependencyButton), "");
    usecasetable->setText(2, 0, BrowserUseCase::relations_default_stereotypes[UmlDependency].join(space));
    usecasetable->setColumnStretchable(0, TRUE);
    usecasetable->setRowStretchable(0, TRUE);
    usecasetable->setRowStretchable(1, TRUE);
    usecasetable->setRowStretchable(2, TRUE);

    addTab(grid, QObject::tr("Use Case"));

    // artifact tab

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(tr("artifact\nstereotypes : "), grid));
    artifact_list = new LineEdit(grid);
    grid->addWidget(artifact_list);
    artifact_list->setTheText(BrowserArtifact::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("relations\nstereotypes : "), grid));
    artifacttable = new MyTable(1, 1, grid);
    grid->addWidget(artifacttable);
    artifacttable->setHorizontalHeaderLabel(0, QObject::tr("Stereotypes"));
    artifacttable->setVerticalHeaderLabel(0, QIcon(*dependencyButton), "");
    artifacttable->setText(0, 0, BrowserArtifact::relation_default_stereotypes.join(space));
    artifacttable->setColumnStretchable(0, TRUE);
    artifacttable->setRowStretchable(0, TRUE);

    addTab(grid, QObject::tr("Artifact"));

    // view

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(tr("class view\nstereotypes : "), grid));
    grid->addWidget(classview_list = new LineEdit(grid));
    classview_list->setTheText(BrowserClassView::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("use case view\nstereotypes : "), grid));
    grid->addWidget(usecaseview_list = new LineEdit(grid));
    usecaseview_list->setTheText(BrowserUseCaseView::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("component view\nstereotypes : "), grid));
    grid->addWidget(componentview_list = new LineEdit(grid));
    componentview_list->setTheText(BrowserComponentView::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("deployment view\nstereotypes : "), grid));
    grid->addWidget(deploymentview_list = new LineEdit(grid));
    deploymentview_list->setTheText(BrowserDeploymentView::its_default_stereotypes.join(space));

    addTab(grid, QObject::tr("Views"));

    // diagrams

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(tr("class diagram\nstereotypes : "), grid));
    grid->addWidget(classdiagram_list = new LineEdit(grid));
    classdiagram_list->setTheText(BrowserClassDiagram::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("object diagram\nstereotypes : "), grid));
    grid->addWidget(objectdiagram_list = new LineEdit(grid));
    objectdiagram_list->setTheText(BrowserObjectDiagram::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("communication diagram\nstereotypes : "), grid));
    grid->addWidget(coldiagram_list = new LineEdit(grid));
    coldiagram_list->setTheText(BrowserColDiagram::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("sequence diagram\nstereotypes : "), grid));
    grid->addWidget(seqdiagram_list = new LineEdit(grid));
    seqdiagram_list->setTheText(BrowserSeqDiagram::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("use case diagram\nstereotypes : "), grid));
    grid->addWidget(usecasediagram_list = new LineEdit(grid));
    usecasediagram_list->setTheText(BrowserUseCaseDiagram::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("state diagram\nstereotypes : "), grid));
    grid->addWidget(statediagram_list = new LineEdit(grid));
    statediagram_list->setTheText(BrowserStateDiagram::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("activity diagram\nstereotypes : "), grid));
    grid->addWidget(activitydiagram_list = new LineEdit(grid));
    activitydiagram_list->setTheText(BrowserActivityDiagram::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("component diagram\nstereotypes : "), grid));
    grid->addWidget(componentdiagram_list = new LineEdit(grid));
    componentdiagram_list->setTheText(BrowserComponentDiagram::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("deployment diagram\nstereotypes : "), grid));
    grid->addWidget(deploymentdiagram_list = new LineEdit(grid));
    deploymentdiagram_list->setTheText(BrowserDeploymentDiagram::its_default_stereotypes.join(space));

    addTab(grid, QObject::tr("Diagrams"));

    // activities

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(tr("activity\nstereotypes : "), grid));
    grid->addWidget(activity_list = new LineEdit(grid));
    activity_list->setTheText(BrowserActivity::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("interruptible activity\nregion stereotypes : "), grid));
    grid->addWidget(interruptibleactivityregion_list = new LineEdit(grid));
    interruptibleactivityregion_list->setTheText(BrowserInterruptibleActivityRegion::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("expansion region\nstereotypes : "), grid));
    grid->addWidget(expansionregion_list = new LineEdit(grid));

    expansionregion_list->setTheText(BrowserExpansionRegion::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("partition\nstereotypes : "), grid));
    grid->addWidget(activitypartition_list = new LineEdit(grid));
    activitypartition_list->setTheText(BrowserActivityPartition::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("parameter\nstereotypes : "), grid));
    grid->addWidget(parameter_list = new LineEdit(grid));
    parameter_list->setTheText(BrowserParameter::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("parameter set\nstereotypes : "), grid));
    grid->addWidget(parameterset_list = new LineEdit(grid));
    parameterset_list->setTheText(BrowserParameterSet::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("activity control node\nstereotypes : "), grid));
    grid->addWidget(activitynode_list = new LineEdit(grid));
    activitynode_list->setTheText(BrowserActivityNode::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("activity action\nstereotypes : "), grid));
    grid->addWidget(activityaction_list = new LineEdit(grid));
    activityaction_list->setTheText(BrowserActivityAction::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("activity object node\nstereotypes : "), grid));
    grid->addWidget(activityobject_list = new LineEdit(grid));
    activityobject_list->setTheText(BrowserActivityObject::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("pin\nstereotypes : "), grid));
    grid->addWidget(pin_list = new LineEdit(grid));
    pin_list->setTheText(BrowserPin::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("expansion node\nstereotypes : "), grid));
    grid->addWidget(expansionnode_list = new LineEdit(grid));

    expansionnode_list->setTheText(BrowserExpansionNode::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("flow\nstereotypes : "), grid));
    grid->addWidget(flow_list = new LineEdit(grid));
    flow_list->setTheText(BrowserFlow::its_default_stereotypes.join(space));

    addTab(grid, QObject::tr("Activities"));

    // others

    grid = new GridBox(2, this);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(tr("state\nstereotypes : "), grid));
    grid->addWidget(state_list = new LineEdit(grid));
    state_list->setTheText(BrowserState::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("pseudostate\nstereotypes : "), grid));
    grid->addWidget(pseudostate_list = new LineEdit(grid));
    pseudostate_list->setTheText(BrowserPseudoState::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("state action\nstereotypes : "), grid));
    grid->addWidget(stateaction_list = new LineEdit(grid));
    stateaction_list->setTheText(BrowserStateAction::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("component\nstereotypes : "), grid));
    grid->addWidget(component_list = new LineEdit(grid));
    component_list->setTheText(BrowserComponent::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("node\nstereotypes : "), grid));
    grid->addWidget(node_list = new LineEdit(grid));
    node_list->setTheText(BrowserDeploymentNode::its_default_stereotypes.join(space));

    grid->addWidget(new QLabel(tr("message\nstereotypes : "), grid));
    grid->addWidget(msg_list = new LineEdit(grid));
    msg_list->setTheText(BrowserSeqDiagram::message_default_stereotypes.join(space));

    addTab(grid, QObject::tr("Others"));
}

StereotypesDialog::~StereotypesDialog()
{
    previous_size = size();
}

void StereotypesDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::limitsize_move(this, previous_size, 0.8, 0.8);
}

void StereotypesDialog::accept()
{
    packagetable->forceUpdateCells();
    classtable->forceUpdateCells();
    usecasetable->forceUpdateCells();
    artifacttable->forceUpdateCells();

    const QString space(" ");

    BrowserPackage::its_default_stereotypes =
        package_list->theText().split(space);

    BrowserPackage::relation_default_stereotypes =
        packagetable->text(0, 0).split(space);

    BrowserClass::its_default_stereotypes =
        class_list->theText().split(space);

    BrowserClass::relations_default_stereotypes[UmlGeneralisation] =
        classtable->text(0, 0).split(space);
    BrowserClass::relations_default_stereotypes[UmlDirectionalAssociation] =
        classtable->text(1, 0).split(space);
    BrowserClass::relations_default_stereotypes[UmlAssociation] =
        classtable->text(2, 0).split(space);
    BrowserClass::relations_default_stereotypes[UmlAggregation] =
        classtable->text(3, 0).split(space);
    BrowserClass::relations_default_stereotypes[UmlAggregationByValue] =
        classtable->text(4, 0).split(space);
    BrowserClass::relations_default_stereotypes[UmlDirectionalAggregation] =
        classtable->text(5, 0).split(space);
    BrowserClass::relations_default_stereotypes[UmlDirectionalAggregationByValue] =
        classtable->text(6, 0).split(space);
    BrowserClass::relations_default_stereotypes[UmlDependency] =
        classtable->text(7, 0).split(space);
    BrowserClass::relations_default_stereotypes[UmlRealize] =
        classtable->text(8, 0).split(space);

    BrowserUseCase::its_default_stereotypes =
        usecase_list->theText().split(space);

    BrowserUseCase::relations_default_stereotypes[UmlGeneralisation] =
        usecasetable->text(0, 0).split(space);
    BrowserUseCase::relations_default_stereotypes[UmlAssociation] =
        usecasetable->text(1, 0).split(space);
    BrowserUseCase::relations_default_stereotypes[UmlDependency] =
        usecasetable->text(2, 0).split(space);

    BrowserArtifact::its_default_stereotypes =
        artifact_list->theText().split(space);

    BrowserArtifact::relation_default_stereotypes =
        artifacttable->text(0, 0).split(space);

    BrowserAttribute::its_default_stereotypes =
        attribute_list->theText().split(space);

    BrowserOperation::its_default_stereotypes =
        operation_list->theText().split(space );

    BrowserState::its_default_stereotypes =
        state_list->theText().split(space );

    BrowserPseudoState::its_default_stereotypes =
        pseudostate_list->theText().split(space );

    BrowserStateAction::its_default_stereotypes =
        stateaction_list->theText().split(space );

    BrowserActivity::its_default_stereotypes =
        activity_list->theText().split(space );

    BrowserInterruptibleActivityRegion::its_default_stereotypes =
        interruptibleactivityregion_list->theText().split(space );

    BrowserExpansionRegion::its_default_stereotypes =
        expansionregion_list->theText().split(space );

    BrowserActivityPartition::its_default_stereotypes =
        activitypartition_list->theText().split(space );

    BrowserParameter::its_default_stereotypes =
        parameter_list->theText().split(space );

    BrowserParameterSet::its_default_stereotypes =
        parameterset_list->theText().split(space );

    BrowserActivityNode::its_default_stereotypes =
        activitynode_list->theText().split(space );

    BrowserActivityAction::its_default_stereotypes =
        activityaction_list->theText().split(space );

    BrowserActivityObject::its_default_stereotypes =
        activityobject_list->theText().split(space );

    BrowserPin::its_default_stereotypes =
        pin_list->theText().split(space );

    BrowserExpansionNode::its_default_stereotypes =
        expansionnode_list->theText().split(space );

    BrowserFlow::its_default_stereotypes =
        flow_list->theText().split(space );

    BrowserComponent::its_default_stereotypes =
        component_list->theText().split(space );

    BrowserDeploymentNode::its_default_stereotypes =
        node_list->theText().split(space );

    BrowserSeqDiagram::message_default_stereotypes =
        msg_list->theText().split(space );

    BrowserClassView::its_default_stereotypes =
        classview_list->theText().split(space );

    BrowserUseCaseView::its_default_stereotypes =
        usecaseview_list->theText().split(space );

    BrowserComponentView::its_default_stereotypes =
        componentview_list->theText().split(space );

    BrowserDeploymentView::its_default_stereotypes =
        deploymentview_list->theText().split(space );

    BrowserClassDiagram::its_default_stereotypes =
        classdiagram_list->theText().split(space );

    BrowserObjectDiagram::its_default_stereotypes =
        objectdiagram_list->theText().split(space );

    BrowserColDiagram::its_default_stereotypes =
        coldiagram_list->theText().split(space );

    BrowserSeqDiagram::its_default_stereotypes =
        seqdiagram_list->theText().split(space );

    BrowserUseCaseDiagram::its_default_stereotypes =
        usecasediagram_list->theText().split(space );

    BrowserStateDiagram::its_default_stereotypes =
        statediagram_list->theText().split(space );

    BrowserActivityDiagram::its_default_stereotypes =
        activitydiagram_list->theText().split(space );

    BrowserComponentDiagram::its_default_stereotypes =
        componentdiagram_list->theText().split(space );

    BrowserDeploymentDiagram::its_default_stereotypes =
        deploymentdiagram_list->theText().split(space );

    TabDialog::accept();
}
