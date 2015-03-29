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





#include "ToolDialog.h"
#include "Tool.h"
#include "UmlPixmap.h"
#include "UmlDesktop.h"
#include "translate.h"
#include <QHeaderView>
static const ToolColumnDef Classes[] = {
    { UmlClass, &classButton },
    { UmlOperation, &PublicOperationIcon },
    { UmlAttribute, &PublicAttributeIcon },
    { UmlGeneralisation, &generalisationButton },
    { UmlRealize, &realizeButton },
    { UmlDependency, &dependencyButton },
    { UmlAssociation, &associationButton },
    { UmlDirectionalAssociation, &directionalAssociationButton },
    { UmlAggregation, &aggregationButton },
    { UmlAggregationByValue, &aggregationByValueButton },
    { UmlDirectionalAggregation, &directionalAggregationButton },
    { UmlDirectionalAggregationByValue, &directionalAggregationByValueButton },
    { UmlExtraMember, &ExtraMemberIcon },
    { UmlClassInstance, &classinstanceButton },
};

static const ToolColumnDef States[] = {
    { UmlState, &StateIcon },
    { UmlRegion, &RegionIcon },
    { UmlStateAction, &ActionIcon },
    { InitialPS, &InitialIcon },
    { EntryPointPS, &EntryPointIcon },
    { FinalPS, &FinalIcon },
    { TerminatePS, &TerminateIcon },
    { ExitPointPS, &ExitPointIcon },
    { DeepHistoryPS, &DeepHistoryIcon },
    { ShallowHistoryPS, &ShallowHistoryIcon },
    { JunctionPS, &JunctionIcon },
    { ChoicePS, &ChoiceIcon },
    { ForkPS, &ForkIcon },
    { JoinPS, &JoinIcon },
    { UmlTransition, &directionalAssociationButton }
};

static const ToolColumnDef Activities[] = {
    { UmlActivity, &ActivityIcon },
    { UmlInterruptibleActivityRegion, &InterruptibleActivityRegionIcon },
    { UmlExpansionRegion, &ExpansionRegionIcon },
    { UmlActivityObject, &ActionIcon },
    { UmlActivityAction, &ActivityActionIcon },
    { UmlParameter, &ParameterIcon },
    { UmlParameterSet, &ParameterSetIcon },
    { UmlActivityPin, &PinIcon },
    { UmlExpansionNode, &ExpansionNodeIcon },
    { InitialAN, &InitialIcon },
    { ActivityFinalAN, &FinalIcon },
    { FlowFinalAN, &ExitPointIcon },
    { DecisionAN, &DecisionIcon },
    { MergeAN, &MergeIcon },
    { ForkAN, &ForkIcon },
    { JoinAN, &JoinIcon },
    { UmlFlow, &directionalAssociationButton },
};

static const ToolColumnDef Others[] = {
    { UmlProject, 0 }, // Prj
    { UmlPackage, &PackageIcon },
    { UmlUseCaseView, &UseCaseViewIcon },
    { UmlClassView, &ClassViewIcon },
    { UmlComponentView, &ComponentViewIcon },
    { UmlDeploymentView, &DeploymentViewIcon },
    { UmlUseCaseDiagram, &UseCaseDiagramIcon },
    { UmlSeqDiagram, &SeqDiagramIcon },
    { UmlColDiagram, &ColDiagramIcon },
    { UmlClassDiagram, &ClassDiagramIcon },
    { UmlObjectDiagram, &ObjectDiagramIcon },
    { UmlStateDiagram, &StateDiagramIcon },
    { UmlActivityDiagram, &ActivityDiagramIcon },
    { UmlComponentDiagram, &ComponentDiagramIcon },
    { UmlDeploymentDiagram, &DeploymentDiagramIcon },
    { UmlUseCase, &usecaseButton },
    { UmlComponent, &ComponentIcon },
    { UmlDeploymentNode, &DeploymentNodeIcon },
    { UmlArtifact, &ArtifactIcon },
    { UmlInherit, &generalisationButton },
    { UmlDependOn, &dependencyButton },
};

struct Tbl {
    const ToolColumnDef * cd;

    const

    unsigned ncol;
    const char * label;
    ToolTable * tbl;
};

static Tbl Tables[] = {
    { &Classes[0], sizeof(Classes) / sizeof(ToolColumnDef), "Class", 0},
    { &States[0], sizeof(States) / sizeof(ToolColumnDef), "State", 0 },
    { &Activities[0], sizeof(Activities) / sizeof(ToolColumnDef), "Activity", 0 },
    { &Others[0], sizeof(Others) / sizeof(ToolColumnDef), "Others", 0 },
};

//

QSize ToolDialog::previous_size;

ToolDialog::ToolDialog() : TabDialog(0, "ToolDialog", TRUE)
{
    setWindowTitle(TR("Tools dialog"));
    setOkButton(TR("OK"));
    setCancelButton(TR("Cancel"));

    for (unsigned i = 0; i != sizeof(Tables) / sizeof(Tbl); i += 1) {
        Tables[i].tbl = new ToolTable(this, Tables[i].cd, Tables[i].ncol);
        addTab(Tables[i].tbl, TR(Tables[i].label));
    }
}

ToolDialog::~ToolDialog()
{
    previous_size = size();
}

void ToolDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::limitsize_center(this, previous_size, 0.9, 0.9);
}

void ToolDialog::accept()
{
    unsigned n = 0;
    unsigned i;

    for (i = 0; i != sizeof(Tables) / sizeof(Tbl); i += 1)
        n += Tables[i].tbl->ntools();

    Tool::set_ntools(n);

    n = 0;

    for (i = 0; i != sizeof(Tables) / sizeof(Tbl); i += 1)
        n = Tables[i].tbl->update(n);

    TabDialog::accept();
}

// ToolTable

ToolTable::ToolTable(QWidget * parent,
                     const ToolColumnDef * tcd, unsigned ncols)
    : StringTable(1, ncols + 3, parent, FALSE), cd(tcd)
{
    unsigned nrows = 1;
    unsigned rank;
    unsigned col;

    for (rank = 0; rank != Tool::ntools; rank += 1) {
        ATool & tool = Tool::tools[rank];

        for (col = 0; col != ncols; col += 1) {
            if (tool.applicable[cd[col].kind]) {
                nrows += 1;
                break;
            }
        }
    }

    setRowCount(nrows);

    setHorizontalHeaderLabel(0, QObject::tr("executable"));
    setHorizontalHeaderLabel(1, QObject::tr("display"));
    setColumnStretchable(0, FALSE);
    setColumnStretchable(1, FALSE);

    for (col = 0; col != ncols; col += 1) {
        if (cd[col].pixmap == 0) {
            setHorizontalHeaderLabel(col + 2, "Prj");
            resizeColumnToContents(col + 2);
        }
        else
        {
            setHorizontalHeaderLabel(col + 2, QIcon(**(cd[col].pixmap)), ""/*, 24*/);
            resizeColumnToContents(col + 2);
        }

        setColumnStretchable(col, FALSE);
    }

    setHorizontalHeaderLabel(ncols + 2, QObject::tr("do"));
    resizeColumnToContents(ncols + 2);
    setColumnStretchable(ncols + 2, FALSE);

    nrows = 0;
    init_row(0);

    for (rank = 0; rank != Tool::ntools; rank += 1) {
        ATool & tool = Tool::tools[rank];

        for (col = 0; col != ncols; col += 1) {
            if (tool.applicable[cd[col].kind]) {
                setText(nrows, 0, tool.cmd);
                setText(nrows, 1, tool.display);
                setText(nrows, col + 2, " X");

                while (++col != ncols)
                    if (tool.applicable[cd[col].kind])
                        setText(nrows, col + 2, " X");

                nrows += 1;
                init_row(nrows);
                break;
            }
        }
    }

    resizeColumnToContents(0);
    resizeColumnToContents(1);
}

void ToolTable::init_row(int row)
{
    int index;
    int n = columnCount();

    setText(row, 0, QString());
    setText(row, 1, QString());

    for (index = 2; index != n; index += 1)
        setItem(row, index,
                new TableItem(this, TableItem::Never, "", TableItem::TableItemType));
}

void ToolTable::button_pressed(const QModelIndex &index)
{
    int col = index.column();
    int row = index.row();
    if ((col >= 2) && (col != (columnCount() - 1))) {
        item(row, col)->setText(text(row, col).isEmpty() ? " X" : "");
    }
    else
        StringTable::button_pressed( this->model()->index(row,  col)/* b, p*/);
}

unsigned ToolTable::ntools()
{
    forceUpdateCells();

    int n = rowCount();

    return (text(n - 1, 0).isEmpty() || text(n - 1, 1).isEmpty())
           ? (unsigned) n - 1 : (unsigned) n;
}

unsigned ToolTable::update(unsigned rank)
{
    int n = rowCount();
    int ncol = columnCount();

    if (text(n - 1, 0).isEmpty() || text(n - 1, 1).isEmpty())
        n -= 1;

    for (int row = 0; row != n; row += 1) {
        ATool & tool = Tool::tools[rank];

        tool.cmd = text(row, 0).trimmed();
        tool.display = text(row, 1).trimmed();

        for (int index = 2; index != ncol - 1; index += 1)
            tool.applicable[cd[index - 2].kind] =
                !text(row, index).trimmed().isEmpty();

        rank += 1;
    }

    return rank;
}
