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
#include "ColDiagramWindow.h"
#include "ColDiagramView.h"
#include "BrowserColDiagram.h"
#include "UmlPixmap.h"
#include "myio.h"
#include "translate.h"

extern QString addmodeledclassinstanceText();
extern QString addclassinstanceText();
extern QString addpackageText();
extern QString addfragmentText();
extern QString noteText();
extern QString anchorText();
static QString linkText()
{
    return TR("Click this button to add a <i>link</i>");
}
static QString selflinkText()
{
    return TR("Click this button to add a <i>self link</i>");
}
extern QString textText();
extern QString imageText();

// id is an old ident in case of an import
ColDiagramWindow::ColDiagramWindow(const QString & s, BrowserColDiagram * b, int id)
    : DiagramWindow(b, s), view(0)
{
    Q3ToolBar * toolbar = new Q3ToolBar(this, "communication diagram operations");
    addToolBar(toolbar, TR("Toolbar"), Qt::DockTop, TRUE);

    add_edit_button(toolbar);

    select =
        new QToolButton(*selectButton, TR("Select"), QString(),
                        this, SLOT(hit_select()), toolbar, "select");
    select->setToggleButton(TRUE);
    select->setOn(TRUE);
    current_button = UmlSelect;

    addPackage
        = new QToolButton(*packageButton, TR("Add Package"), QString(),
                          this, SLOT(hit_package()), toolbar, "add package");
    addPackage->setToggleButton(TRUE);
    Q3WhatsThis::add(addPackage, addpackageText());

    addFragment
        = new QToolButton(*fragmentButton, TR("Add Fragment"), QString(),
                          this, SLOT(hit_fragment()), toolbar, "add fragment");
    addFragment->setToggleButton(TRUE);
    Q3WhatsThis::add(addFragment, addfragmentText());

    addClassInstance
        = new QToolButton(*classinstanceButton, TR("Add modeled Class instance"), QString(),
                          this, SLOT(hit_classinstance()), toolbar, "add modeled class instance");
    addClassInstance->setToggleButton(TRUE);
    Q3WhatsThis::add(addClassInstance, addmodeledclassinstanceText());

    addClass
        = new QToolButton(*classButton, TR("Add Class instance"), QString(),
                          this, SLOT(hit_class()), toolbar, "add class instance");
    addClass->setToggleButton(TRUE);
    Q3WhatsThis::add(addClass, addclassinstanceText());

    addLink =
        new QToolButton(*associationButton, TR("Add Link"), QString(),
                        this, SLOT(hit_link()), toolbar, "add link");
    addLink->setToggleButton(TRUE);
    Q3WhatsThis::add(addLink, linkText());

    addSelfLink =
        new QToolButton(*selflinkButton, TR("Add Self Link"), QString(),
                        this, SLOT(hit_selflink()), toolbar, "add self link");
    addSelfLink->setToggleButton(TRUE);
    Q3WhatsThis::add(addSelfLink, selflinkText());

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

    view = new ColDiagramView(this, canvas, (id != -1) ? id : b->get_ident());
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

    select->setOn(FALSE);
    addPackage->setOn(FALSE);
    addFragment->setOn(FALSE);
    addClass->setOn(FALSE);
    addClassInstance->setOn(FALSE);
    addLink->setOn(FALSE);
    addSelfLink->setOn(FALSE);
    note->setOn(FALSE);
    anchor->setOn(FALSE);
    text->setOn(FALSE);
    image->setOn(FALSE);

    b->setOn(TRUE);
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

