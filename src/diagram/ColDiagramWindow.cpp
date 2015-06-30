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
#include <QToolBar.h>
#include <qtoolbutton.h>
#include <qwhatsthis.h>
#include <qlayout.h>
#include <qspinbox.h>

#include "UmlWindow.h"
#include "ColDiagramWindow.h"
#include "ColDiagramView.h"
#include "BrowserColDiagram.h"
#include "UmlPixmap.h"
#include "myio.h"
#include "translate.h"
#include "toolbarfactory.h"

extern QString addmodeledclassinstanceText();
extern QString addclassinstanceText();
extern QString addpackageText();
extern QString addfragmentText();
extern QString noteText();
extern QString anchorText();
static QString linkText()
{
    return  QObject::tr("Click this button to add a <i>link</i>");
}
static QString selflinkText()
{
    return  QObject::tr("Click this button to add a <i>self link</i>");
}
extern QString textText();
extern QString imageText();

// id is an old ident in case of an import
ColDiagramWindow::ColDiagramWindow(const QString & s, BrowserColDiagram * b, int id)
    : DiagramWindow(b, s), view(0)
{
    QToolBar * toolbar = new QToolBar("communication diagram operations", this);
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

    addClassInstance
        = ToolBarFactory::createToolButton(*classinstanceButton, TR("Add modeled Class instance"), QString(),
                          this, SLOT(hit_classinstance()), toolbar, "add modeled class instance");
    addClassInstance->setCheckable(TRUE);
    addClassInstance->setWhatsThis(addmodeledclassinstanceText());

    addClass
        = ToolBarFactory::createToolButton(*classButton, TR("Add Class instance"), QString(),
                          this, SLOT(hit_class()), toolbar, "add class instance");
    addClass->setCheckable(TRUE);
    addClass->setWhatsThis(addclassinstanceText());

    addLink =
        ToolBarFactory::createToolButton(*associationButton, TR("Add Link"), QString(),
                        this, SLOT(hit_link()), toolbar, "add link");
    addLink->setCheckable(TRUE);
    addLink->setWhatsThis(linkText());

    addSelfLink =
        ToolBarFactory::createToolButton(*selflinkButton, TR("Add Self Link"), QString(),
                        this, SLOT(hit_selflink()), toolbar, "add self link");
    addSelfLink->setCheckable(TRUE);
    addSelfLink->setWhatsThis(selflinkText());

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

    view = new ColDiagramView(this, canvas, (id != -1) ? id : b->get_ident());
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

ColDiagramWindow::~ColDiagramWindow()
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

DiagramView * ColDiagramWindow::get_view() const
{
    return view;
}

void ColDiagramWindow::hit_button(UmlCode c, QToolButton * b)
{
    view->abort_line_construction();

    select->setChecked(FALSE);
    addPackage->setChecked(FALSE);
    addFragment->setChecked(FALSE);
    addClass->setChecked(FALSE);
    addClassInstance->setChecked(FALSE);
    addLink->setChecked(FALSE);
    addSelfLink->setChecked(FALSE);
    note->setChecked(FALSE);
    anchor->setChecked(FALSE);
    text->setChecked(FALSE);
    image->setChecked(FALSE);

    b->setChecked(TRUE);
    current_button = c;
}

void ColDiagramWindow::hit_package()
{
    hit_button(UmlPackage, addPackage);
}

void ColDiagramWindow::hit_fragment()
{
    hit_button(UmlFragment, addFragment);
}

void ColDiagramWindow::hit_classinstance()
{
    hit_button(UmlClassInstance, addClassInstance);
}

void ColDiagramWindow::hit_class()
{
    hit_button(UmlClass, addClass);
}

void ColDiagramWindow::hit_link()
{
    hit_button(UmlLink, addLink);
}

void ColDiagramWindow::hit_selflink()
{
    hit_button(UmlSelfLink, addSelfLink);
}

void ColDiagramWindow::hit_note()
{
    hit_button(UmlNote, note);
}

void ColDiagramWindow::hit_anchor()
{
    hit_button(UmlAnchor, anchor);
}

void ColDiagramWindow::hit_text()
{
    hit_button(UmlText, text);
}

void ColDiagramWindow::hit_image()
{
    hit_button(UmlImage, image);
}

