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
//#include <qworkspace.h>
#include <QToolBar>
#include <qtoolbutton.h>
#include <qwhatsthis.h>
#include <qlayout.h>

#include "UmlWindow.h"
#include "ClassDiagramWindow.h"
#include "ClassDiagramView.h"
#include "BrowserClassDiagram.h"
#include "UmlPixmap.h"
#include "myio.h"
#include "translate.h"
#include "toolbarfactory.h"
QString addclassText()
{
    return  QObject::TR("Click this button to add a <i>class</i> in the diagram. <br><br>"
              "You can also drop the class from the <b>browser</b>.");
}
QString addpackageText()
{
    return  QObject::TR("Click this button to add a <i>package</i> in the diagram. <br><br>"
              "You can also drop the package from the <b>browser</b>.");
}
extern QString addfragmentText();
extern QString inheritText();
extern QString noteText();
extern QString anchorText();
QString dependencyText()
{
    return  QObject::TR("Click this button to create a <i>dependency</i>");
}
extern QString associationText();
QString directionalassociationextensionText()
{
    return  QObject::TR("Click this button to create an <i>unidirectional association</i> or an <i>extension</i>");
}
QString aggregationText()
{
    return  QObject::TR("Click this button to create an <i>aggregation</i>");
}
QString aggregationbyvalueText()
{
    return  QObject::TR("Click this button to create a <i>composition</i>");
}
QString directionalaggregationText()
{
    return  QObject::TR("Click this button to create a <i>directional aggregation</i>");
}
QString directionalaggregationbyvalueText()
{
    return  QObject::TR("Click this button to create a <i>directional composition</i>");
}
QString realizeText()
{
    return  QObject::TR("Click this button to create a <i>realization</i>");
}
extern QString textText();
extern QString imageText();

// id is an old ident in case of an import
ClassDiagramWindow::ClassDiagramWindow(const QString & s, BrowserClassDiagram * b, int id)
    : DiagramWindow(b, s), view(0)
{

    QToolBar * toolbar = new QToolBar("class diagram operations",this);
    toolbar->setMinimumHeight(50);
    toolbar->setOrientation(Qt::Horizontal);
    addToolBar(Qt::TopToolBarArea, toolbar);

    add_edit_button(toolbar);

    select =
        ToolBarFactory::createToolButton(*selectButton,  QObject::TR("Select"), QString(),
                        this, SLOT(hit_select()), toolbar, "select");
    select->setCheckable(TRUE);
    select->setChecked(TRUE);
    current_button = UmlSelect;
    b->set_diagram_window(this);
    addClass
        = ToolBarFactory::createToolButton(*classButton,  QObject::TR("Add Class"), QString(),
                          this, SLOT(hit_class()), toolbar, "add class");
    addClass->setCheckable(TRUE);
    addClass->setWhatsThis( addclassText());

    addPackage
        = ToolBarFactory::createToolButton(*packageButton,  QObject::TR("Add Package"), QString(),
                          this, SLOT(hit_package()), toolbar, "add package");
    addPackage->setCheckable(TRUE);
    addPackage->setWhatsThis( addpackageText());

    addFragment
        = ToolBarFactory::createToolButton(*fragmentButton,  QObject::TR("Add Fragment"), QString(),
                          this, SLOT(hit_fragment()), toolbar, "add fragment");
    addFragment->setCheckable(TRUE);
    addFragment->setWhatsThis(addfragmentText());

    inherit =
        ToolBarFactory::createToolButton(*generalisationButton,  QObject::TR("Generalisation"), QString(),
                        this, SLOT(hit_inherit()), toolbar, "generalisation");
    inherit->setCheckable(TRUE);
    inherit->setWhatsThis( inheritText());

    realize =
        ToolBarFactory::createToolButton(*realizeButton,  QObject::TR("Realize"), QString(),
                        this, SLOT(hit_realize()), toolbar, "realize");
    realize->setCheckable(TRUE);
    realize->setWhatsThis( realizeText());

    dependency =
        ToolBarFactory::createToolButton(*dependencyButton,  QObject::TR("Dependency"), QString(),
                        this, SLOT(hit_dependency()), toolbar, "dependency");
    dependency->setCheckable(TRUE);
    dependency->setWhatsThis( dependencyText());

    association =
        ToolBarFactory::createToolButton(*associationButton,  QObject::TR("Association"), QString(),
                        this, SLOT(hit_association()), toolbar, "association");
    association->setCheckable(TRUE);
    association->setWhatsThis( associationText());

    directionalassociation =
        ToolBarFactory::createToolButton(*directionalAssociationExtensionButton,  QObject::TR("Directional Association / Extension"), QString(),
                        this, SLOT(hit_directionalassociation()), toolbar, "directional association");
    directionalassociation->setCheckable(TRUE);
    directionalassociation->setWhatsThis( directionalassociationextensionText());

    aggregation =
        ToolBarFactory::createToolButton(*aggregationButton,  QObject::TR("Aggregation"), QString(),
                        this, SLOT(hit_aggregation()), toolbar, "aggregation");
    aggregation->setCheckable(TRUE);
    aggregation->setWhatsThis( aggregationText());

    aggregationbyvalue =
        ToolBarFactory::createToolButton(*aggregationByValueButton,  QObject::TR("Composition"), QString(),
                        this, SLOT(hit_aggregationbyvalue()), toolbar, "composition");
    aggregationbyvalue->setCheckable(TRUE);
    aggregationbyvalue->setWhatsThis( aggregationbyvalueText());

    directionalaggregation =
        ToolBarFactory::createToolButton(*directionalAggregationButton,  QObject::TR("Directional Aggregation"), QString(),
                        this, SLOT(hit_directionalaggregation()), toolbar, "directional aggregation");
    directionalaggregation->setCheckable(TRUE);
    directionalaggregation->setWhatsThis( directionalaggregationText());

    directionalaggregationbyvalue =
        ToolBarFactory::createToolButton(*directionalAggregationByValueButton,  QObject::TR("Directional Composition"), QString(),
                        this, SLOT(hit_directionalaggregationbyvalue()), toolbar, "directional composition");
    directionalaggregationbyvalue->setCheckable(TRUE);
    directionalaggregationbyvalue->setWhatsThis( directionalaggregationbyvalueText());

    note =
        ToolBarFactory::createToolButton(*noteButton,  QObject::TR("Note"), QString(),
                        this, SLOT(hit_note()), toolbar, "note");
    note->setCheckable(TRUE);
    note->setWhatsThis( noteText());

    anchor =
        ToolBarFactory::createToolButton(*anchorButton,  QObject::TR("Anchor / Class association"), QString(),
                        this, SLOT(hit_anchor()), toolbar, "anchor");
    anchor->setCheckable(TRUE);
    anchor->setWhatsThis( anchorText());

    text =
        ToolBarFactory::createToolButton(*textButton,  QObject::TR("Text"), QString(),
                        this, SLOT(hit_text()), toolbar, "text");
    text->setCheckable(TRUE);
    text->setWhatsThis( textText());

    image =
        ToolBarFactory::createToolButton(*imageButton,  QObject::TR("Image"), QString(),
                        this, SLOT(hit_image()), toolbar, "image");
    image->setCheckable(TRUE);
    image->setWhatsThis( imageText());

    toolbar->addSeparator();

    add_scale_cmd(toolbar);

    //

    view = new ClassDiagramView(this, canvas, (id != -1) ? id : b->get_ident());
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

ClassDiagramWindow::~ClassDiagramWindow()
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
//    if(browser_node)
//        browser_node->set_diagram_window(0);

  if(browser_node)
    browser_node->on_close();
}

DiagramView * ClassDiagramWindow::get_view() const
{
    return view;
}

void ClassDiagramWindow::hit_button(UmlCode c, QToolButton * b)
{
    view->abort_line_construction();
    select->setChecked(FALSE);
    addClass->setChecked(FALSE);
    addPackage->setChecked(FALSE);
    addFragment->setChecked(FALSE);
    inherit->setChecked(FALSE);
    dependency->setChecked(FALSE);
    association->setChecked(FALSE);
    directionalassociation->setChecked(FALSE);
    aggregation->setChecked(FALSE);
    aggregationbyvalue->setChecked(FALSE);
    directionalaggregation->setChecked(FALSE);
    directionalaggregationbyvalue->setChecked(FALSE);
    realize->setChecked(FALSE);
    note->setChecked(FALSE);
    anchor->setChecked(FALSE);
    text->setChecked(FALSE);
    image->setChecked(FALSE);

    b->setChecked(TRUE);
    current_button = c;
}

void ClassDiagramWindow::hit_class()
{
    hit_button(UmlClass, addClass);
}

void ClassDiagramWindow::hit_package()
{
    hit_button(UmlPackage, addPackage);
}

void ClassDiagramWindow::hit_fragment()
{
    hit_button(UmlFragment, addFragment);
}

void ClassDiagramWindow::hit_inherit()
{
    hit_button(UmlGeneralisation, inherit);
}

void ClassDiagramWindow::hit_dependency()
{
    hit_button(UmlDependency, dependency);
}

void ClassDiagramWindow::hit_association()
{
    hit_button(UmlAssociation, association);
}

void ClassDiagramWindow::hit_directionalassociation()
{
    hit_button(UmlDirectionalAssociation, directionalassociation);
}

void ClassDiagramWindow::hit_aggregation()
{
    hit_button(UmlAggregation, aggregation);
}

void ClassDiagramWindow::hit_aggregationbyvalue()
{
    hit_button(UmlAggregationByValue, aggregationbyvalue);
}

void ClassDiagramWindow::hit_directionalaggregation()
{
    hit_button(UmlDirectionalAggregation, directionalaggregation);
}

void ClassDiagramWindow::hit_directionalaggregationbyvalue()
{
    hit_button(UmlDirectionalAggregationByValue, directionalaggregationbyvalue);
}

void ClassDiagramWindow::hit_realize()
{
    hit_button(UmlRealize, realize);
}

void ClassDiagramWindow::hit_note()
{
    hit_button(UmlNote, note);
}

void ClassDiagramWindow::hit_anchor()
{
    hit_button(UmlAnchor, anchor);
}

void ClassDiagramWindow::hit_text()
{
    hit_button(UmlText, text);
}

void ClassDiagramWindow::hit_image()
{
    hit_button(UmlImage, image);
}

