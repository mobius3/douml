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
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qwhatsthis.h>
#include <qlayout.h>
#include <qspinbox.h>
#include "UmlWindow.h"
#include "SeqDiagramWindow.h"
#include "SeqDiagramView.h"
#include "BrowserSeqDiagram.h"
#include "UmlPixmap.h"
#include "myio.h"
#include "translate.h"
#include "toolbarfactory.h"
QString addmodeledclassinstanceText()
{
    return QObject::TR("Click this button to add a modeled <i>class instance</i> in the diagram. <br><br>"
              "You can also drop the class instance from the <b>browser</b>.");
}
QString addclassinstanceText()
{
    return QObject::TR("Click this button to add a <i>class instance</i> in the diagram. <br><br>"
              "You can also drop the class from the <b>browser</b>.");
}
extern QString addfragmentText();
extern QString noteText();
extern QString anchorText();
QString syncmsgText()
{
    return QObject::TR("Click this button to send a <i>synchronous message</i>");
}
QString asyncmsgText()
{
    return QObject::TR("Click this button to send an <i>asynchronous message</i>");
}
QString syncselfmsgText()
{
    return QObject::TR("Click this button to send a <i>reflexive synchronous message</i>");
}
QString asyncselfmsgText()
{
    return QObject::TR("Click this button to send a <i>reflexive asynchronous message</i>");
}
QString lostsyncmsgText()
{
    return QObject::TR("Click this button to send a <i>synchronous lost message</i>");
}
QString lostasyncmsgText()
{
    return QObject::TR("Click this button to send a <i>asynchronous lost message</i>");
}
QString foundsyncmsgText()
{
    return QObject::TR("Click this button to add a <i>synchronous found message</i>");
}
QString foundasyncmsgText()
{
    return QObject::TR("Click this button to add a <i>asynchronous found message</i>");
}
QString returnmsgText()
{
    return QObject::TR("Click this button to add an <i>explicitly return</i>");
}
QString selfreturnmsgText()
{
    return QObject::TR("Click this button to add an <i>explicit reflexive return</i>");
}
QString textText()
{
    return QObject::TR("Click this button to add a <i>text</i>");
}
QString addcontinuationText()
{
    return QObject::TR("Click this button to add a <i>continuation</i>");
}
extern QString imageText();

// id is an old ident in case of an import
SeqDiagramWindow::SeqDiagramWindow(const QString & s, BrowserSeqDiagram * b, int id)
    : DiagramWindow(b, s), view(0)
{
    QToolBar * toolbar = new QToolBar("sequence diagram operations",this);
    addToolBar(Qt::TopToolBarArea,toolbar);

    add_edit_button(toolbar);

    select =
        ToolBarFactory::createToolButton(*selectButton, QObject::TR("Select"), QString(),
                        this, SLOT(hit_select()), toolbar,
                        "select");
    select->setCheckable(TRUE);
    select->setChecked(TRUE);
    current_button = UmlSelect;

    addFragment
        = ToolBarFactory::createToolButton(*fragmentButton, QObject::TR("Add Fragment"), QString(),
                          this, SLOT(hit_fragment()), toolbar,
                          "add fragment");
    addFragment->setCheckable(TRUE);
    addFragment->setWhatsThis(addfragmentText());

    addClassInstance
        = ToolBarFactory::createToolButton(*classinstanceButton, QObject::TR("Add modeled Class instance"), QString(),
                          this, SLOT(hit_classinstance()), toolbar,
                          "add modeled class instance");
    addClassInstance->setCheckable(TRUE);
    addClassInstance->setWhatsThis( addmodeledclassinstanceText());

    addClass
        = ToolBarFactory::createToolButton(*classButton, QObject::TR("Add Class instance"), QString(),
                          this, SLOT(hit_class()), toolbar,
                          "add class");
    addClass->setCheckable(TRUE);
    addClass->setWhatsThis( addclassinstanceText());

    addContinuation
        = ToolBarFactory::createToolButton(*continuationButton, QObject::TR("Add Continuation"), QString(),
                          this, SLOT(hit_continuation()), toolbar,
                          "add continuation");
    addContinuation->setCheckable(TRUE);
    addContinuation->setWhatsThis( addcontinuationText());

    syncMsg =
        ToolBarFactory::createToolButton(*syncmsgButton, QObject::TR("Synchronous message"), QString(),
                        this, SLOT(hit_syncmsg()), toolbar,
                        "synchronous message");
    syncMsg->setCheckable(TRUE);
    syncMsg->setWhatsThis( syncmsgText());

    asyncMsg =
        ToolBarFactory::createToolButton(*directionalAssociationButton, QObject::TR("Asynchronous message"), QString(),
                        this, SLOT(hit_asyncmsg()), toolbar,
                        "asynchronous message");
    asyncMsg->setCheckable(TRUE);
    asyncMsg->setWhatsThis( asyncmsgText());

    syncSelfMsg =
        ToolBarFactory::createToolButton(*syncselfmsgButton, QObject::TR("Synchronous Reflexive message"), QString(),
                        this, SLOT(hit_syncselfmsg()), toolbar,
                        "synchronous reflexive message");
    syncSelfMsg->setCheckable(TRUE);
    syncSelfMsg->setWhatsThis( syncselfmsgText());

    asyncSelfMsg =
        ToolBarFactory::createToolButton(*asyncselfmsgButton, QObject::TR("Asynchronous Reflexive message"), QString(),
                        this, SLOT(hit_asyncselfmsg()), toolbar,
                        "asynchronous reflexive message");
    asyncSelfMsg->setCheckable(TRUE);
    asyncSelfMsg->setWhatsThis( asyncselfmsgText());

    foundsyncMsg =
        ToolBarFactory::createToolButton(*foundsyncmsgButton, QObject::TR("Synchronous found message"), QString(),
                        this, SLOT(hit_foundsyncmsg()), toolbar,
                        "synchronous found message");
    foundsyncMsg->setCheckable(TRUE);
    foundsyncMsg->setWhatsThis( foundsyncmsgText());

    foundasyncMsg =
        ToolBarFactory::createToolButton(*foundasyncmsgButton, QObject::TR("Asynchronous found message"), QString(),
                        this, SLOT(hit_foundasyncmsg()), toolbar,
                        "asynchronous found message");
    foundasyncMsg->setCheckable(TRUE);
    foundasyncMsg->setWhatsThis( foundasyncmsgText());

    lostsyncMsg =
        ToolBarFactory::createToolButton(*lostsyncmsgButton, QObject::TR("Synchronous lost message"), QString(),
                        this, SLOT(hit_lostsyncmsg()), toolbar,
                        "synchronous lost message");
    lostsyncMsg->setCheckable(TRUE);
    lostsyncMsg->setWhatsThis( lostsyncmsgText());

    lostasyncMsg =
        ToolBarFactory::createToolButton(*lostasyncmsgButton, QObject::TR("Asynchronous lost message"), QString(),
                        this, SLOT(hit_lostasyncmsg()), toolbar,
                        "asynchronous lost message");
    lostasyncMsg->setCheckable(TRUE);
    lostasyncMsg->setWhatsThis( lostasyncmsgText());

    returnMsg =
        ToolBarFactory::createToolButton(*returnmsgButton, QObject::TR("Explicit return"), QString(),
                        this, SLOT(hit_returnmsg()), toolbar,
                        "explicit return");
    returnMsg->setCheckable(TRUE);
    returnMsg->setWhatsThis( returnmsgText());

    selfreturnMsg =
        ToolBarFactory::createToolButton(*selfreturnmsgButton, QObject::TR("Explicit reflexive return"), QString(),
                        this, SLOT(hit_selfreturnmsg()), toolbar,
                        "explicit reflexive return");
    selfreturnMsg->setCheckable(TRUE);
    selfreturnMsg->setWhatsThis( selfreturnmsgText());

    note =
        ToolBarFactory::createToolButton(*noteButton, QObject::TR("Note"), QString(),
                        this, SLOT(hit_note()), toolbar,
                        "note");
    note->setCheckable(TRUE);
    note->setWhatsThis(noteText());

    anchor =
        ToolBarFactory::createToolButton(*anchorButton, QObject::TR("Anchor"), QString(),
                        this, SLOT(hit_anchor()), toolbar,
                        "anchor");
    anchor->setCheckable(TRUE);
    anchor->setWhatsThis(anchorText());

    text =
        ToolBarFactory::createToolButton(*textButton, QObject::TR("Text"), QString(),
                        this, SLOT(hit_text()), toolbar,
                        "text");
    text->setCheckable(TRUE);
    text->setWhatsThis( textText());

    image =
        ToolBarFactory::createToolButton(*imageButton, QObject::TR("Image"), QString(),
                        this, SLOT(hit_image()), toolbar, "image");
    image->setCheckable(TRUE);
    image->setWhatsThis( imageText());

    toolbar->addSeparator();

    add_scale_cmd(toolbar);

    //

    view = new SeqDiagramView(this, canvas, (id != -1) ? id : b->get_ident());
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

SeqDiagramWindow::~SeqDiagramWindow()
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

DiagramView * SeqDiagramWindow::get_view() const
{
    return view;
}

void SeqDiagramWindow::hit_button(UmlCode c, QToolButton * b)
{
    view->abort_line_construction();
    select->setChecked(FALSE);
    addFragment->setChecked(FALSE);
    addClass->setChecked(FALSE);
    addClassInstance->setChecked(FALSE);
    addContinuation->setChecked(FALSE);
    syncMsg->setChecked(FALSE);
    asyncMsg->setChecked(FALSE);
    foundsyncMsg->setChecked(FALSE);
    foundasyncMsg->setChecked(FALSE);
    lostsyncMsg->setChecked(FALSE);
    lostasyncMsg->setChecked(FALSE);
    syncSelfMsg->setChecked(FALSE);
    asyncSelfMsg->setChecked(FALSE);
    selfreturnMsg->setChecked(FALSE);
    returnMsg->setChecked(FALSE);
    note->setChecked(FALSE);
    anchor->setChecked(FALSE);
    text->setChecked(FALSE);
    image->setChecked(FALSE);

    b->setChecked(TRUE);
    current_button = c;
}

void SeqDiagramWindow::hit_fragment()
{
    hit_button(UmlFragment, addFragment);
}

void SeqDiagramWindow::hit_classinstance()
{
    hit_button(UmlClassInstance, addClassInstance);
}

void SeqDiagramWindow::hit_class()
{
    hit_button(UmlClass, addClass);
}

void SeqDiagramWindow::hit_continuation()
{
    hit_button(UmlContinuation, addContinuation);
}

void SeqDiagramWindow::hit_syncmsg()
{
    hit_button(UmlSyncMsg, syncMsg);
}

void SeqDiagramWindow::hit_asyncmsg()
{
    hit_button(UmlAsyncMsg, asyncMsg);
}

void SeqDiagramWindow::hit_lostsyncmsg()
{
    hit_button(UmlLostSyncMsg, lostsyncMsg);
}

void SeqDiagramWindow::hit_lostasyncmsg()
{
    hit_button(UmlLostAsyncMsg, lostasyncMsg);
}

void SeqDiagramWindow::hit_foundsyncmsg()
{
    hit_button(UmlFoundSyncMsg, foundsyncMsg);
}

void SeqDiagramWindow::hit_foundasyncmsg()
{
    hit_button(UmlFoundAsyncMsg, foundasyncMsg);
}

void SeqDiagramWindow::hit_syncselfmsg()
{
    hit_button(UmlSyncSelfMsg, syncSelfMsg);
}

void SeqDiagramWindow::hit_asyncselfmsg()
{
    hit_button(UmlAsyncSelfMsg, asyncSelfMsg);
}

void SeqDiagramWindow::hit_returnmsg()
{
    hit_button(UmlReturnMsg, returnMsg);
}

void SeqDiagramWindow::hit_selfreturnmsg()
{
    hit_button(UmlSelfReturnMsg, selfreturnMsg);
}

void SeqDiagramWindow::hit_note()
{
    hit_button(UmlNote, note);
}

void SeqDiagramWindow::hit_anchor()
{
    hit_button(UmlAnchor, anchor);
}

void SeqDiagramWindow::hit_text()
{
    hit_button(UmlText, text);
}

void SeqDiagramWindow::hit_image()
{
    hit_button(UmlImage, image);
}

