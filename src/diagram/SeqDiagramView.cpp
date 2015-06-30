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





#include <qfont.h>
//#include <q3popupmenu.h>
//Added by qt3to4:
#include <QTextStream>
#include <QDropEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDragEnterEvent>

#include "SeqDiagramWindow.h"
#include "SeqDiagramView.h"
#include "BrowserSeqDiagram.h"
#include "BrowserClassInstance.h"
#include "BrowserClass.h"
#include "DiagramCanvas.h"
#include "SdClassInstCanvas.h"
#include "SdDurationCanvas.h"
#include "SdMsgCanvas.h"
#include "SdSelfMsgCanvas.h"
#include "SdLostFoundMsgSupportCanvas.h"
#include "ArrowCanvas.h"
#include "IconCanvas.h"
#include "FragmentCanvas.h"
#include "SdContinuationCanvas.h"
#include "SdLifeLineCanvas.h"
#include "NoteCanvas.h"
#include "TextCanvas.h"
#include "ImageCanvas.h"
#include "UmlPixmap.h"
#include "UmlDrag.h"
#include "myio.h"
#include "ui/menufactory.h"
#include "DialogUtil.h"
#include "translate.h"

SeqDiagramView::SeqDiagramView(QWidget * parent, UmlCanvas * canvas, int id)
    : DiagramView(parent, canvas, id)
{
    load("Sequence");
}

void SeqDiagramView::menu(const QPoint &)
{
    QMenu m(0);

    MenuFactory::createTitle(m, TR("Sequence diagram menu"));

    if ((((UmlCanvas *) canvas())->browser_diagram())->is_writable()) {
        BrowserSeqDiagram * sd = (BrowserSeqDiagram *) window()->browser_diagram();
        bool overlapping = sd->is_overlapping_bars();

        MenuFactory::addItem(m, (overlapping) ? TR("Transform to flat activity bars")
                                              : TR("Transform to overlapping activity bars"),
                             29);
        m.addSeparator();

        switch (default_menu(m, 30)) {
        case EDIT_DRAWING_SETTING_CMD:
            ((BrowserSeqDiagram *) the_canvas()->browser_diagram())->edit_settings();
            return;

        case RELOAD_CMD:
            // pure drawing modifications are lost
            // mark the diagram modified because the undid modifications
            // may be saved in the file are not saved in memory
            load("Sequence");
            window()->package_modified();
            break;

        case 29:
            unselect_all();
            sd->set_overlapping_bars(!overlapping);

            if (overlapping)
                toFlat();
            else
                toOverlapping();

            canvas()->update();
            window()->package_modified();
            break;
        }
    }
    else
        (void) default_menu(m, 30);
}

void SeqDiagramView::toFlat()
{
    QList<QGraphicsItem*> all = canvas()->items();
    QList<QGraphicsItem*>::Iterator cit;
    for (cit = all.begin(); cit != all.end(); ++cit) {
        DiagramItem * it = QCanvasItemToDiagramItem(*cit);

        if ((it != 0) && // an uml canvas item
                (*cit)->isVisible() &&
                (it->typeUmlCode() == UmlLifeLine))
            ((SdLifeLineCanvas *) it)->toFlat();
    }
}

void SeqDiagramView::toOverlapping()
{
    QList<QGraphicsItem*> all = canvas()->items();
    QList<QGraphicsItem*>::Iterator cit;
    for (cit = all.begin(); cit != all.end(); ++cit) {
        DiagramItem * it = QCanvasItemToDiagramItem(*cit);

        if ((it != 0) && // an uml canvas item
                (*cit)->isVisible() &&
                (it->typeUmlCode() == UmlLifeLine))
            ((SdLifeLineCanvas *) it)->toOverlapping();
    }
}

void SeqDiagramView::mousePressEvent(QMouseEvent * e)
{
    if (!window()->frozen()) {
        if (e->button() == ::Qt::RightButton)
            DiagramView::mousePressEvent(e);
        else {
            QPoint diagramPoint(e->x(), e->y());
            QPointF scenePoint = mapToScene(diagramPoint);
            UmlCode c = window()->buttonOn();

            switch (c) {
            case UmlClass: {
                history_protected = FALSE;
                unselect_all();
                window()->selectOn();
                history_save();

                BrowserNode * parent =
                        ((BrowserNode *) window()->browser_diagram()->parent());
                BrowserClass * b =
                        BrowserClass::get_class(parent);
                if (b != 0) {
                    SdClassInstCanvas * cli =
                            new SdClassInstCanvas(b, the_canvas(), scenePoint.x(), 0);

                    cli->show();
                    cli->moveBy(scenePoint.x() - cli->center().x(), 0);
                    cli->upper();
                    window()->package_modified();
                }
            }
                break;

            case UmlClassInstance: {
                history_protected = TRUE;
                unselect_all();
                window()->selectOn();
                history_save();

                BrowserNode * parent =
                        ((BrowserNode *) window()->browser_diagram()->parent());
                BrowserClassInstance * b =
                        BrowserClassInstance::get_classinstance(parent);
                if (b != 0) {
                    SdClassInstCanvas * cli =
                            new SdClassInstCanvas(b, the_canvas(), scenePoint.x(), 0);

                    cli->show();
                    cli->moveBy(scenePoint.x() - cli->center().x(), 0);
                    cli->upper();
                    window()->package_modified();
                }
            }
                break;

            case UmlSyncSelfMsg:
            case UmlAsyncSelfMsg:
            case UmlSelfReturnMsg: {
                history_protected = TRUE;
                unselect_all();
                window()->selectOn();
                history_save();

                QGraphicsItem * ci = the_canvas()->collision(scenePoint.toPoint());

                if (ci != 0) {
                    DiagramItem * i = QCanvasItemToDiagramItem(ci);

                    if (i != 0) {
                        QString err = i->may_start(c);

                        if (!err.isEmpty())
                            msg_critical("Douml" , err);
                        else {
                            i->connexion(c, i, scenePoint.toPoint(), scenePoint.toPoint());
                            window()->package_modified();
                        }
                    }
                }
            }
                break;

            case UmlContinuation: {
                history_protected = TRUE;
                unselect_all();
                window()->selectOn();
                history_save();
                SdContinuationCanvas * cont =
                        new SdContinuationCanvas(the_canvas(), scenePoint.x(), scenePoint.y(), 0);
                cont->show();
                cont->upper();
                window()->package_modified();
            }
                break;

            default:
                DiagramView::mousePressEvent(e);
                return;
            }

            canvas()->update();
            history_protected = FALSE;
        }
    }
    else
        DiagramView::mousePressEvent(e);
}

void SeqDiagramView::mouseMoveEvent(QMouseEvent * e)
{
    if (!window()->frozen()) {
        DiagramView::mouseMoveEvent(e);

        QList<QGraphicsItem*> all = canvas()->items();
        QList<QGraphicsItem*>::Iterator cit;

        for (cit = all.begin(); cit != all.end(); ++cit) {
            DiagramItem * it = QCanvasItemToDiagramItem(*cit);

            if ((it != 0) && // an uml canvas item
                    (*cit)->isVisible())
                it->update();
        }
    }
}

void SeqDiagramView::keyPressEvent(QKeyEvent * e)
{
    if (!window()->frozen()) {
        DiagramView::keyPressEvent(e);

        if (e->modifiers() != ::Qt::ControlModifier) {
            switch (e->key()) {
            case ::Qt::Key_Left:
            case ::Qt::Key_Up:
            case ::Qt::Key_Right:
            case ::Qt::Key_Down: {
                QList<QGraphicsItem*> all = canvas()->items();
                QList<QGraphicsItem*>::Iterator cit;

                for (cit = all.begin(); cit != all.end(); ++cit) {
                    DiagramItem * it = QCanvasItemToDiagramItem(*cit);

                    if ((it != 0) && // an uml canvas item
                            (*cit)->isVisible())
                        it->update();
                }
            }
                break;

            default:
                break;
            }
        }
    }
}

void SeqDiagramView::dragEnterEvent(QDragEnterEvent * e)
{
    if (!window()->frozen() &&
            (UmlDrag::canDecode(e, UmlClass, TRUE, TRUE) ||
             UmlDrag::canDecode(e, UmlClassInstance, TRUE, TRUE) ||
             UmlDrag::canDecode(e, UmlClassDiagram, FALSE, TRUE) ||
             UmlDrag::canDecode(e, UmlUseCaseDiagram, FALSE, TRUE) ||
             UmlDrag::canDecode(e, UmlSeqDiagram, FALSE, TRUE) ||
             UmlDrag::canDecode(e, UmlColDiagram, FALSE, TRUE) ||
             UmlDrag::canDecode(e, UmlObjectDiagram, FALSE, TRUE) ||
             UmlDrag::canDecode(e, UmlComponentDiagram, FALSE, TRUE) ||
             UmlDrag::canDecode(e, UmlDeploymentDiagram, FALSE, TRUE) ||
             UmlDrag::canDecode(e, UmlActivityDiagram, TRUE, TRUE) ||
             UmlDrag::canDecode(e, UmlStateDiagram, TRUE, TRUE)))
        e->accept();
    else
        e->ignore();
}

void SeqDiagramView::dragMoveEvent(QDragMoveEvent * e)
{
    if (!window()->frozen() &&
            (UmlDrag::canDecode(e, UmlClass, TRUE, TRUE) ||
             UmlDrag::canDecode(e, UmlClassInstance, TRUE, TRUE) ||
             UmlDrag::canDecode(e, UmlClassDiagram, FALSE, TRUE) ||
             UmlDrag::canDecode(e, UmlUseCaseDiagram, FALSE, TRUE) ||
             UmlDrag::canDecode(e, UmlSeqDiagram, FALSE, TRUE) ||
             UmlDrag::canDecode(e, UmlColDiagram, FALSE, TRUE) ||
             UmlDrag::canDecode(e, UmlObjectDiagram, FALSE, TRUE) ||
             UmlDrag::canDecode(e, UmlComponentDiagram, FALSE, TRUE) ||
             UmlDrag::canDecode(e, UmlDeploymentDiagram, FALSE, TRUE) ||
             UmlDrag::canDecode(e, UmlActivityDiagram, TRUE, TRUE) ||
             UmlDrag::canDecode(e, UmlStateDiagram, TRUE, TRUE)))
        e->accept();
    else
        e->ignore();
}
void SeqDiagramView::dropEvent(QDropEvent * e)
{
    BrowserNode * bn;
    QPointF p = mapToScene(e->pos());
    if ((bn = UmlDrag::decode(e, UmlClassInstance)) != 0) {
        history_save();
        SdClassInstCanvas * cli =
                new SdClassInstCanvas((BrowserClassInstance *) bn,
                                      the_canvas(), p.x(), 0);

        history_protected = TRUE;
        cli->show();
        cli->moveBy(p.x() - cli->center().x(), 0);
        canvas()->update();
        history_protected = FALSE;
        window()->package_modified();
    }
    else if ((bn = UmlDrag::decode(e, UmlClass)) != 0) {
        history_save();
        SdClassInstCanvas * cli =
                new SdClassInstCanvas(bn, the_canvas(), p.x(), 0);

        history_protected = TRUE;
        cli->show();
        cli->moveBy(p.x() - cli->center().x(), 0);
        canvas()->update();
        history_protected = FALSE;
        window()->package_modified();
    }
    else if (((bn = UmlDrag::decode(e, UmlClassDiagram)) != 0) ||
             ((bn = UmlDrag::decode(e, UmlUseCaseDiagram)) != 0) ||
             ((bn = UmlDrag::decode(e, UmlSeqDiagram)) != 0) ||
             ((bn = UmlDrag::decode(e, UmlColDiagram)) != 0) ||
             ((bn = UmlDrag::decode(e, UmlObjectDiagram)) != 0) ||
             ((bn = UmlDrag::decode(e, UmlComponentDiagram)) != 0) ||
             ((bn = UmlDrag::decode(e, UmlDeploymentDiagram)) != 0) ||
             ((bn = UmlDrag::decode(e, UmlStateDiagram, TRUE)) != 0) ||
             ((bn = UmlDrag::decode(e, UmlActivityDiagram, TRUE)) != 0)) {
        history_save();
        IconCanvas * ic = new IconCanvas(bn, the_canvas(), p.x(), p.y(), 0);

        history_protected = TRUE;
        ic->show();
        ic->upper();
        canvas()->update();
        history_protected = FALSE;
        window()->package_modified();
    }
}

void SeqDiagramView::save(QTextStream & st, QString & warning,
                          bool copy) const
{
    DiagramItemList items(canvas()->items());

    if (!copy)
        // sort is useless for a copy
        items.sort();

    st << "format " << api_format() << "\n";

    // save first the fragments, continuation, actors, classes instances, notes, icons and text

    foreach (DiagramItem *di, items) {
        switch (di->typeUmlCode()) {
        case UmlFragment:
        case UmlContinuation:
        case UmlClass:
        case UmlClassInstance:
        case UmlNote:
        case UmlText:
        case UmlImage:
        case UmlIcon:
            if (!copy || di->copyable())
                di->save(st, FALSE, warning);

            // no break
        default:
            break;
        }
    }

    // then save durations

    foreach (DiagramItem *di, items)
        if ((!copy || di->copyable()) &&
                (di->typeUmlCode() == UmlActivityDuration))
            di->save(st, FALSE, warning);

    // then save lost/found start/end

    foreach (DiagramItem *di, items)
        if ((!copy || di->copyable()) &&
                (di->typeUmlCode() == UmlLostFoundMsgSupport))
            di->save(st, FALSE, warning);

    // then save messages

    foreach (DiagramItem *di, items) {
        switch (di->typeUmlCode()) {
        case UmlSyncMsg:
        case UmlAsyncMsg:
        case UmlFoundSyncMsg:
        case UmlFoundAsyncMsg:
        case UmlLostSyncMsg:
        case UmlLostAsyncMsg:
        case UmlSyncSelfMsg:
        case UmlAsyncSelfMsg:
        case UmlReturnMsg:
        case UmlSelfReturnMsg:
            if (!copy || di->copyable())
                di->save(st, FALSE, warning);

        default:
            break;
        }
    }

    // then save anchors

    foreach (DiagramItem *di, items)
        if ((!copy || di->copyable()) && (di->typeUmlCode() == UmlAnchor))
            di->save(st, FALSE, warning);

    if (!copy && (preferred_zoom != 0)) {
        nl_indent(st);
        st << "preferred_whz " << preferred_size.width() << " "
           << preferred_size.height() << " " << preferred_zoom;
    }

    nl_indent(st);
    st << "end\n";
}

void SeqDiagramView::read(char * st, char * k)
{
    UmlCanvas * canvas = the_canvas();
    // reads first the actors, classes instances, notes, icons text and images
    while (NoteCanvas::read(st, canvas, k) ||
           TextCanvas::read(st, canvas, k) ||
           IconCanvas::read(st, canvas, k) ||
           FragmentCanvas::read(st, canvas, k) ||
           SdClassInstCanvas::read(st, canvas, k) ||
           SdContinuationCanvas::read(st, canvas, k) ||
           ImageCanvas::read(st, canvas, k))
        k = read_keyword(st);

    // then reads durations
    while (SdDurationCanvas::read(st, canvas, k))
        k = read_keyword(st);

    // then reads lost/found start/end
    while (SdLostFoundMsgSupportCanvas::read(st, canvas, k))
        k = read_keyword(st);

    // then reads msgs
    while (SdMsgCanvas::read(st, canvas, k) ||
           SdSelfMsgCanvas::read(st, canvas, k))
        k = read_keyword(st);
    // then reads anchors
    while (ArrowCanvas::read(st, canvas, k))
        k = read_keyword(st);

    if (!strcmp(k, "preferred_whz") || !strcmp(k, "prefered_whz")) {
        preferred_size.setWidth(read_unsigned(st));
        preferred_size.setHeight(read_unsigned(st));
        preferred_zoom = read_double(st);
        k = read_keyword(st);
    }

    if (strcmp(k, "end"))
        wrong_keyword(k, "end");
}

// for plug-out

void SeqDiagramView::send(ToolCom * com)
{
    QList<QGraphicsItem*> l = canvas()->items();
    QList<FragmentCanvas *> fragments;
    QList<FragmentCanvas *> refs;
    FragmentCanvas::send(com, l, fragments, refs);
    SdClassInstCanvas::send(com, l);
    SdLifeLineCanvas::send(com, l, fragments, refs);
    SdContinuationCanvas::send(com, l);
    TextCanvas::send(com, l);

}
