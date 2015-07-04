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
#include <QMdiArea>.h>
#include <QToolBar>
#include <qtoolbutton.h>
#include <qwhatsthis.h>
#include <qlayout.h>
#include <qspinbox.h>
#include "toolbarfactory.h"
#include "UmlWindow.h"
#include "UseCaseDiagramWindow.h"
#include "UseCaseDiagramView.h"
#include "BrowserUseCaseDiagram.h"
#include "UmlPixmap.h"
#include "myio.h"
#include "translate.h"
#include <QHBoxLayout>

QString addactorText()
{
    return QObject::TR("Click this button to add an <i>actor</i> in the diagram. <br><br>"
              "You can also drop the class from the <b>browser</b>.");
}
QString addusecaseText()
{
    return QObject::TR("Click this button to add an <i>use case</i> in the diagram. <br><br>"
              "You can also drop the use case from the <b>browser</b>.");
}
extern QString addpackageText();
QString addfragmentText()
{
    return QObject::TR("Click this button to add a <i>fragment</i>.");
}
QString addsubjectText()
{
    return QObject::TR("Click this button to add a <i>subject</i>.");
}
QString associationText()
{
    return QObject::TR("Click this button to create an <i>association</i>");
}
extern QString dependencyText();
QString inheritText()
{
    return QObject::TR("Click this button to create a <i>generalisation</i>");
}
QString noteText()
{
    return QObject::TR("Click this button to create a <i>note</i>");
}
QString anchorText()
{
    return QObject::TR("Click this button to create a connection between a "
              "<i>note</i> and any other item, or between an <i>association</i> "
              "and a <i>class</i> in case of an <i>association class</i>.");
}
extern QString textText();
QString imageText()
{
    return QObject::TR("Click this button to add an <i>image</i>");
}

// id is an old ident in case of an import
UseCaseDiagramWindow::UseCaseDiagramWindow(const QString & s, BrowserUseCaseDiagram * b, int id)
    : DiagramWindow(b, s), view(0)
{
    QToolBar * toolbar = new QToolBar("use case operations",this);
    toolbar->setMinimumHeight(50);
    toolbar->setOrientation(Qt::Horizontal);
    addToolBar(Qt::TopToolBarArea, toolbar);
    add_edit_button(toolbar);
    select =
        ToolBarFactory::createToolButton(*selectButton, QObject::tr("Select"), QString(),
                        this, SLOT(hit_select()), toolbar, "select");
    select->setCheckable(TRUE);


    current_button = UmlSelect;
    addClass =
        ToolBarFactory::createToolButton(*actorButton, QObject::tr("Actor"), QString(),
                        this, SLOT(hit_class()), toolbar, "actor");
    addClass->setCheckable(TRUE);
    addClass->setWhatsThis(addactorText());

    addUseCase =
        ToolBarFactory::createToolButton(*usecaseButton, QObject::tr("Use Case"), QString(),
                        this, SLOT(hit_usecase()), toolbar, "use case");
    addUseCase->setCheckable(TRUE);
    addUseCase->setWhatsThis( addusecaseText());

    addSubject
        = ToolBarFactory::createToolButton(*subjectButton, QObject::tr("Add Subject"), QString(),
                          this, SLOT(hit_subject()), toolbar, "add subject");
    addSubject->setCheckable(TRUE);
    addSubject->setWhatsThis( addsubjectText());

    addPackage
        = ToolBarFactory::createToolButton(*packageButton, QObject::tr("Add Package"), QString(),
                          this, SLOT(hit_package()), toolbar, "add package");
    addPackage->setCheckable(TRUE);
    addPackage->setWhatsThis( addpackageText());

    addFragment
        = ToolBarFactory::createToolButton(*fragmentButton, QObject::tr("Add Fragment"), QString(),
                          this, SLOT(hit_fragment()), toolbar, "add fragment");
    addFragment->setCheckable(TRUE);
    addFragment->setWhatsThis( addfragmentText());

    association =
        ToolBarFactory::createToolButton(*associationButton, QObject::tr("Association"), QString(),
                        this, SLOT(hit_association()), toolbar, "association");
    association->setCheckable(TRUE);
    association->setWhatsThis( associationText());

    directionalassociation =
        ToolBarFactory::createToolButton(*directionalAssociationButton, QObject::tr("Association"), QString(),
                        this, SLOT(hit_directionalassociation()), toolbar, "association");
    directionalassociation->setCheckable(TRUE);
    directionalassociation->setWhatsThis( associationText());

    dependency =
        ToolBarFactory::createToolButton(*dependencyButton, QObject::tr("Dependency"), QString(),
                        this, SLOT(hit_dependency()), toolbar, "dependency");
    dependency->setCheckable(TRUE);
    dependency->setWhatsThis( dependencyText());

    inherit =
        ToolBarFactory::createToolButton(*generalisationButton, QObject::tr("Generalisation"), QString(),
                        this, SLOT(hit_inherit()), toolbar, "generalisation");
    inherit->setCheckable(TRUE);
    inherit->setWhatsThis( inheritText());

    note =
        ToolBarFactory::createToolButton(*noteButton, QObject::tr("Note"), QString(),
                        this, SLOT(hit_note()), toolbar, "note");
    note->setCheckable(TRUE);
    note->setWhatsThis( noteText());

    anchor =
        ToolBarFactory::createToolButton(*anchorButton, QObject::tr("Anchor"), QString(),
                        this, SLOT(hit_anchor()), toolbar, "anchor");
    anchor->setCheckable(TRUE);
    anchor->setWhatsThis( anchorText());

    text =
        ToolBarFactory::createToolButton(*textButton, QObject::tr("Text"), QString(),
                        this, SLOT(hit_text()), toolbar, "text");
    text->setCheckable(TRUE);
    text->setWhatsThis( textText());

    image =
        ToolBarFactory::createToolButton(*imageButton, QObject::tr("Image"), QString(),
                        this, SLOT(hit_image()), toolbar, "image");
    image->setCheckable(TRUE);

    image->setWhatsThis( imageText());

    toolbar->addSeparator();

    add_scale_cmd(toolbar);

    //

    view = new UseCaseDiagramView(this, canvas, (id != -1) ? id : b->get_ident());
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

UseCaseDiagramWindow::~UseCaseDiagramWindow()
{
    if (! no_save) {
        QString warning = "!";
        BooL is_new = FALSE;

        //habip hidden items means deleted. So delete them not to save
        QList<QGraphicsItem*> itList = canvas->items();
        for(int i= itList.size() -1; i>=0; i--)
        {
            DiagramItem *di = QCanvasItemToDiagramItem(itList.at(i));
            if(di && !itList.at(i)->isVisible())
                delete di;
        }
        save("d", warning, is_new);
        warning.remove(0, 1);	// removes !
        view->hide();
        if (!warning.isEmpty())
            warn(warning);
    }

    browser_node->on_close();
}

DiagramView * UseCaseDiagramWindow::get_view() const
{
    return view;
}

void UseCaseDiagramWindow::hit_button(UmlCode c, QToolButton * b)
{
    view->abort_line_construction();

    select->setChecked(FALSE);
    addClass->setChecked(FALSE);
    addPackage->setChecked(FALSE);
    addFragment->setChecked(FALSE);
    addSubject->setChecked(FALSE);
    addUseCase->setChecked(FALSE);
    association->setChecked(FALSE);
    directionalassociation->setChecked(FALSE);
    dependency->setChecked(FALSE);
    inherit->setChecked(FALSE);
    note->setChecked(FALSE);
    anchor->setChecked(FALSE);
    text->setChecked(FALSE);
    image->setChecked(FALSE);

    b->setChecked(TRUE);
    current_button = c;
}

void UseCaseDiagramWindow::hit_class()
{
    hit_button(UmlClass, addClass);
}

void UseCaseDiagramWindow::hit_usecase()
{
    hit_button(UmlUseCase, addUseCase);
}

void UseCaseDiagramWindow::hit_package()
{
    hit_button(UmlPackage, addPackage);
}

void UseCaseDiagramWindow::hit_fragment()
{
    hit_button(UmlFragment, addFragment);
}

void UseCaseDiagramWindow::hit_subject()
{
    hit_button(UmlSubject, addSubject);
}

void UseCaseDiagramWindow::hit_association()
{
    hit_button(UmlAssociation, association);
}

void UseCaseDiagramWindow::hit_directionalassociation()
{
    hit_button(UmlDirectionalAssociation, directionalassociation);
}

void UseCaseDiagramWindow::hit_dependency()
{
    hit_button(UmlDependency, dependency);
}

void UseCaseDiagramWindow::hit_inherit()
{
    hit_button(UmlGeneralisation, inherit);
}

void UseCaseDiagramWindow::hit_note()
{
    hit_button(UmlNote, note);
}

void UseCaseDiagramWindow::hit_anchor()
{
    hit_button(UmlAnchor, anchor);
}

void UseCaseDiagramWindow::hit_text()
{
    hit_button(UmlText, text);
}

void UseCaseDiagramWindow::hit_image()
{
    hit_button(UmlImage, image);
}

