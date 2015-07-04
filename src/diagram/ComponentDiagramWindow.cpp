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
#include "ComponentDiagramWindow.h"
#include "ComponentDiagramView.h"
#include "BrowserComponentDiagram.h"
#include "UmlPixmap.h"
#include "myio.h"
#include "translate.h"
#include "toolbarfactory.h"

QString addcomponentText()
{
    return QObject::tr("Click this button to add a <i>component</i> in the diagram. <br><br>"
              "You can also drop the component from the <b>browser</b>.");
}
extern QString addpackageText();
extern QString addfragmentText();
extern QString dependencyText();
extern QString inheritText();
extern QString noteText();
extern QString anchorText();
extern QString textText();
static QString requiredText()
{
    return  QObject::tr("Click this button to show an interface required by a <i>component</i>.");
}
static QString providedText()
{
    return  QObject::tr("Click this button to show an interface provided by a <i>component</i>.");
}
extern QString imageText();

// id is an old ident in case of an import
ComponentDiagramWindow::ComponentDiagramWindow(const QString & s, BrowserComponentDiagram * b, int id)
    : DiagramWindow(b, s), view(0)
{
    QToolBar * toolbar = new QToolBar("component operations", this);
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
    addFragment->setWhatsThis(addfragmentText());

    addComponent =
        ToolBarFactory::createToolButton(*componentButton, TR("Add Component"), QString(),
                        this, SLOT(hit_component()), toolbar, "add component");
    addComponent->setCheckable(TRUE);
    addComponent->setWhatsThis(addcomponentText());

    inherit =
        ToolBarFactory::createToolButton(*generalisationButton, TR("Inheritance"), QString(),
                        this, SLOT(hit_inherit()), toolbar, "inheritance");
    inherit->setCheckable(TRUE);
    inherit->setWhatsThis(inheritText());

    dependency =
        ToolBarFactory::createToolButton(*dependencyButton, TR("Dependency"), QString(),
                        this, SLOT(hit_dependency()), toolbar, "dependency");
    dependency->setCheckable(TRUE);
    dependency->setWhatsThis(dependencyText());

    required =
        ToolBarFactory::createToolButton(*requiredButton, TR("Required interface"), QString(),
                        this, SLOT(hit_required()), toolbar, "required interface");
    required->setCheckable(TRUE);
    required->setWhatsThis(requiredText());

    provided =
        ToolBarFactory::createToolButton(*providedButton, TR("Provided interface"), QString(),
                        this, SLOT(hit_provided()), toolbar, "provided interface");
    provided->setCheckable(TRUE);
    provided->setWhatsThis(providedText());

    note =
        ToolBarFactory::createToolButton(*noteButton, TR("Note"), QString(),
                        this, SLOT(hit_note()), toolbar, "note");
    note->setCheckable(TRUE);
    note->setWhatsThis(noteText());

    anchor =
        ToolBarFactory::createToolButton(*anchorButton, TR("Anchor"), QString(),
                        this, SLOT(hit_anchor()), toolbar, "anchor");
    anchor->setCheckable(TRUE);
    anchor->setWhatsThis(anchorText());

    text =
        ToolBarFactory::createToolButton(*textButton, TR("Text"), QString(),
                        this, SLOT(hit_text()), toolbar, "text");
    text->setCheckable(TRUE);
    text->setWhatsThis(textText());

    image =
        ToolBarFactory::createToolButton(*imageButton, TR("Image"), QString(),
                        this, SLOT(hit_image()), toolbar, "image");
    image->setCheckable(TRUE);
    image->setWhatsThis(imageText());

    toolbar->addSeparator();

    add_scale_cmd(toolbar);

    //

    view = new ComponentDiagramView(this, canvas, (id != -1) ? id : b->get_ident());
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

ComponentDiagramWindow::~ComponentDiagramWindow()
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

DiagramView * ComponentDiagramWindow::get_view() const
{
    return view;
}

void ComponentDiagramWindow::hit_button(UmlCode c, QToolButton * b)
{
    view->abort_line_construction();

    select->setChecked(FALSE);
    addPackage->setChecked(FALSE);
    addFragment->setChecked(FALSE);
    addComponent->setChecked(FALSE);
    inherit->setChecked(FALSE);
    dependency->setChecked(FALSE);
    required->setChecked(FALSE);
    provided->setChecked(FALSE);
    note->setChecked(FALSE);
    anchor->setChecked(FALSE);
    text->setChecked(FALSE);
    image->setChecked(FALSE);

    b->setChecked(TRUE);
    current_button = c;
}

void ComponentDiagramWindow::hit_package()
{
    hit_button(UmlPackage, addPackage);
}

void ComponentDiagramWindow::hit_fragment()
{
    hit_button(UmlFragment, addFragment);
}

void ComponentDiagramWindow::hit_component()
{
    hit_button(UmlComponent, addComponent);
}

void ComponentDiagramWindow::hit_inherit()
{
    hit_button(UmlGeneralisation, inherit);
}

void ComponentDiagramWindow::hit_dependency()
{
    hit_button(UmlDependency, dependency);
}

void ComponentDiagramWindow::hit_required()
{
    hit_button(UmlRequired, required);
}

void ComponentDiagramWindow::hit_provided()
{
    hit_button(UmlProvided, provided);
}

void ComponentDiagramWindow::hit_note()
{
    hit_button(UmlNote, note);
}

void ComponentDiagramWindow::hit_anchor()
{
    hit_button(UmlAnchor, anchor);
}

void ComponentDiagramWindow::hit_text()
{
    hit_button(UmlText, text);
}

void ComponentDiagramWindow::hit_image()
{
    hit_button(UmlImage, image);
}

