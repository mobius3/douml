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





#ifndef QT_NO_PRINTER
#include <qpainter.h>
#include <qprinter.h>
#endif
#include <qcursor.h>
#include <qapplication.h>
#include <qclipboard.h>
#include <qfiledialog.h>
#include <qbuffer.h>
#if defined(WIN32) || (QT_VERSION != 230)
#include <qtimer.h>
//Added by qt3to4:
#include <QWheelEvent>
#include <QPixmap>
#include <QMouseEvent>
#include <QList>
#include <QTextStream>
#include <QKeyEvent>

#endif

#include "DiagramView.h"
#include "DiagramWindow.h"
#include "DiagramCanvas.h"
#include "BrowserView.h"
#include "RelationData.h"
#include "RelationCanvas.h"
#include "SimpleRelationCanvas.h"
#include "FlowCanvas.h"
#include "TransitionCanvas.h"
#include "ObjectLinkCanvas.h"
#include "CodLinkCanvas.h"
#include "AssocContainCanvas.h"
#include "FragmentCanvas.h"
#include "PackageCanvas.h"
#include "ImageCanvas.h"
#include "TextCanvas.h"
#include "SelectAreaCanvas.h"
#include "ArrowCanvas.h"
#include "ArrowPointCanvas.h"
#include "LabelCanvas.h"
#include "NoteCanvas.h"
#include "BrowserPackage.h"
#include "BrowserDiagram.h"
#include "UmlWindow.h"
#include "Shortcut.h"
#include "ui/menufactory.h"
#include "DialogUtil.h"
#include "myio.h"
#include "err.h"
#include "translate.h"
#include <QScrollBar>
#include "align_top.xpm"
#include "align_bottom.xpm"
#include "align_left.xpm"
#include "align_right.xpm"
#include "align_center.xpm"
#include "align_vcenter.xpm"
#include "align_hcenter.xpm"
#include <QGraphicsScene>
#include <QImage>

WrapperStr DiagramView::clipboard;
UmlCode DiagramView::copied_from;

DiagramView::DiagramView(QWidget * parent, UmlCanvas * canvas, int i)
    : QGraphicsView(canvas, parent), id(i), pressedButton(-1), selectArea(0), start(0),
      line(0), arrowBeginning(0), preferred_zoom(0), draw_line(FALSE),
      do_resize(NoCorner), history_protected(FALSE), history_frozen(FALSE),
      first_move(FALSE), on_arrow_decenter(FALSE), history_index(~0u)
{
    // enableClipper(TRUE); => probleme d'affichage
    preferred_size.setWidth(0);
    preferred_size.setHeight(0);
    setAcceptDrops(TRUE);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setFocusPolicy(Qt::StrongFocus);
    //setFocusPolicy(QWidget::WheelFocus);
    QBrush backBrush = canvas->backgroundBrush();
    backBrush.setColor(::Qt::white);
    canvas->setBackgroundBrush(backBrush);
    setCacheMode(QGraphicsView::CacheBackground);
    canvas->set_view(this);
    ensureVisible(0,0,1,1);
    //to set the default cursor
    this->viewport()->unsetCursor();
}

void DiagramView::init()
{
    clipboard = 0;
}

UmlCanvas * DiagramView::the_canvas() const
{
    return (UmlCanvas *) scene();
}

QGraphicsScene* DiagramView::canvas() const
{
    return scene();
}

void DiagramView::mouseDoubleClickEvent(QMouseEvent * e)
{
    setFocus();
    unselect_all();
    QPointF scenePoint = mapToScene(e->pos());
    if (draw_line)
        abort_line_construction();
    else {
        QGraphicsItem * ci = the_canvas()->collision(scenePoint.toPoint());

        if (ci != 0) {
            DiagramItem * di = QCanvasItemToDiagramItem(ci);

            if (di != 0)
                di->open();
        }
    }
}

bool DiagramView::multiple_selection_for_menu(BooL & in_model, BooL & out_model,
                                              BooL & alignable, int & n_resize,
                                              QList<DiagramItem *> & l_drawing_settings,
                                              const QList<QGraphicsItem*> & selected)
{
    QList<QGraphicsItem*>::ConstIterator it;
    int n_targets = 0;
    UmlCode k = UmlCodeSup;

    in_model = FALSE;
    out_model = FALSE;
    alignable = FALSE;
    l_drawing_settings.clear();
    n_resize = 0;

    for (it = selected.begin(); it != selected.end(); ++it) {
        if (! isa_label(*it)) {
            n_targets += 1;

            DiagramItem * item = QCanvasItemToDiagramItem(*it);

            item->delete_available(in_model, out_model);
            alignable |= item->alignable();

            if (item->has_drawing_settings()) {
                // note : relations doesn't have drawing setting, transition and flow have
                switch (k) {
                case UmlCodeSup:
                    // first case
                    k = item->typeUmlCode();
                    l_drawing_settings.append(item);
                    break;

                case UmlArrowPoint:
                    // mark for several types
                    break;

                default:
                    if (item->typeUmlCode() == k)
                        l_drawing_settings.append(item);
                    else {
                        // several types
                        l_drawing_settings.clear();
                        k = UmlArrowPoint;	// mark for several types
                    }
                }
            }

            if (item->on_resize_point(item->rect().topLeft()) != NoCorner)
                n_resize += 1;
        }
    }
    return (n_targets > 1);
}

void DiagramView::mousePressEvent(QMouseEvent * e)
{
    first_move = TRUE;
    pressedButton = e->button();
    setFocus();
    QPoint diagramPoint(e->x(), e->y());
    QPointF scenePoint = mapToScene(diagramPoint);


    if (pressedButton == ::Qt::MidButton) {
        mousePressPos = scenePoint.toPoint();
        QApplication::setOverrideCursor(QCursor(::Qt::SizeAllCursor));
    }
    else if (!window()->frozen()) {
        QGraphicsItem * ci = the_canvas()->collision(scenePoint.toPoint());

        if (pressedButton == ::Qt::RightButton) {
            // menu on several objects (excluding labels)

            if (! draw_line) {
                const QList<QGraphicsItem*> selected = selection();
                BooL in_model;
                BooL out_model;
                BooL alignable;
                QList<DiagramItem *> l_drawing_settings;
                int n_resize;

                if (multiple_selection_for_menu(in_model, out_model, alignable,
                                                n_resize, l_drawing_settings, selected)) {
                    multiple_selection_menu(in_model, out_model, alignable,
                                            n_resize, l_drawing_settings);
                    return;
                }
            }

            unselect_all();

            if (draw_line)
                abort_line_construction();
            else if (! BrowserNode::popupMenuActive()) {	// Qt bug
                BrowserNode::setPopupMenuActive(TRUE);

                if (ci != 0) {
                    DiagramItem * di = QCanvasItemToDiagramItem(ci);

                    if (di != 0)
                        di->menu(scenePoint.toPoint());
                    BrowserNode::setPopupMenuActive(FALSE);
                }
                else  {
                    menu(scenePoint.toPoint());
                    BrowserNode::setPopupMenuActive(FALSE);
                    // here the window & view may be deleted
                    return;
                }
            }
        }
        else if (draw_line)
            history_protected = TRUE;
        else {
            history_protected = TRUE;

            UmlCode & action = window()->buttonOn();

            switch (action) {
            case UmlSelect:
                mousePressPos = scenePoint.toPoint();

                if (ci == 0) {
                    // ne designe pas d objet, vide la selection
                    unselect_all();
                }
                else {
                    const QList<QGraphicsItem*> selected = selection();
                    //QList<QGraphicsItem*>::ConstIterator it = selected.find(ci);
                    bool isContaining = selected.contains(ci);

                    if ((e->modifiers() & ::Qt::ControlModifier) == 0) {
                        if (/*it == selected.end()*/!isContaining) {
                            // ne designe pas un objet selectionne, vide la selection
                            unselect_all();

                            // l objet est selectionne
                            select(ci);
                        }

                        // sinon on ne fait rien, l utilisateur veut probablement
                        // deplacer les objets selectionnes
                    }
                    else if (/*it != selected.end()*/isContaining)
                        // l objet etait selectionne
                        unselect(ci);
                    else
                        // l objet n etait pas selectionne
                        select(ci);
                    DiagramItem * di = QCanvasItemToDiagramItem(ci);

                    if (di != 0)
                    {
                        QPointF itemPoint = ci->mapFromScene(scenePoint.toPoint());
                        do_resize = di->on_resize_point(itemPoint.toPoint());
                    }
                }

                break;

            case UmlNote: {
                unselect_all();
                window()->selectOn();
                history_save();
                NoteCanvas * note =
                        new NoteCanvas(the_canvas(), scenePoint.x(), scenePoint.y(), 0);

                note->show();
                note->upper();
                note->open();
                window()->package_modified();
            }
                break;

            case UmlText: {
                unselect_all();
                window()->selectOn();
                history_save();
                TextCanvas * text =
                        new TextCanvas(the_canvas(), scenePoint.x(), scenePoint.y(), 0);

                text->show();
                text->upper();
                text->open();
                window()->package_modified();
            }
                break;

            case UmlImage: {
                unselect_all();
                window()->selectOn();
                history_save();
                ImageCanvas * image = ImageCanvas::add(the_canvas(), scenePoint.x(), scenePoint.y());

                if (image != 0) {
                    image->show();
                    image->upper();
                    window()->package_modified();
                }
            }
                break;

            case UmlPackage:
                unselect_all();
                window()->selectOn();
            {
                BrowserPackage * p = BrowserPackage::get_package();

                if (p != 0) {
                    history_save();
                    PackageCanvas * pk =
                            new PackageCanvas(p, the_canvas(), scenePoint.x(), scenePoint.y(), 0);

                    pk->show();
                    pk->upper();
                    window()->package_modified();
                }
            }
                break;

            case UmlFragment: {
                unselect_all();
                window()->selectOn();
                history_save();
                FragmentCanvas * f =
                        new FragmentCanvas(the_canvas(), scenePoint.x(), scenePoint.y(), 0);

                f->show();
                f->upper();
                window()->package_modified();
            }
                break;

            case UmlFoundSyncMsg:
            case UmlFoundAsyncMsg:
                unselect_all();
                history_save();
                this->viewport()->setCursor(QCursor(::Qt::PointingHandCursor));
                arrowBeginning = start = 0;
                draw_line = TRUE;
                mousePressPos = scenePoint.toPoint();
                break;

            default:
                // lines
                unselect_all();
                if ((ci != 0) && isa_label(ci))
                    ci = the_canvas()->collision(scenePoint.toPoint(), RTTI_LABEL);
                if (ci != 0) {

                    DiagramItem * i = QCanvasItemToDiagramItem(ci);

                    if (i != 0) {
                        QString err = i->may_start(action);

                        if (!err.isEmpty()) {
                            msg_critical("Douml" , err);
                            window()->selectOn();
                        }
                        else {
                            history_save();
                            this->viewport()->setCursor(QCursor(::Qt::PointingHandCursor));
                            arrowBeginning = start = i;
                            draw_line = TRUE;
                            mousePressPos = scenePoint.toPoint();
                        }

                    }
                    else
                        window()->selectOn();
                }
                else
                    window()->selectOn();
            }
        }

        canvas()->update();
        history_protected = FALSE;
    }
    else if ((pressedButton == ::Qt::RightButton) &&
             ! BrowserNode::popupMenuActive()) {	// Qt bug
        BrowserNode::setPopupMenuActive(TRUE);

        menu(scenePoint.toPoint());
        BrowserNode::setPopupMenuActive(FALSE);
    }
}

void DiagramView::mouseReleaseEvent(QMouseEvent * e)
{
    int button = pressedButton;
    pressedButton = -1;
    QPoint diagramPoint(e->x(), e->y());
    QPointF scenePoint = mapToScene(diagramPoint);

    if (button == ::Qt::MidButton)
        QApplication::restoreOverrideCursor();
    else if (!window()->frozen()) {
        if (do_resize != NoCorner) {
            do_resize = NoCorner;
            previousResizeCorrection.clear();
        }
        else if (on_arrow_decenter)
            on_arrow_decenter = FALSE;
        else if (line != 0) {
            history_protected = TRUE;
            the_canvas()->del(line);
            line = 0;

            QGraphicsItem * ci = the_canvas()->collision(scenePoint.toPoint(), RTTI_LABEL);
            UmlCode action = window()->buttonOn();

            if (ci != 0) {
                DiagramItem * i = QCanvasItemToDiagramItem(ci);

                if (i != 0) {
                    if (start == 0) {
                        if (i->may_connect(action)) {
                            // sequence diagram found msg
                            if (i->connexion(action, mousePressPos, scenePoint.toPoint())) {
                                window()->package_modified();
                                temp.clear();
                                draw_line = FALSE;
                                this->viewport()->unsetCursor();
                            }
                            else
                                abort_line_construction();
                        }
                        else
                            abort_line_construction();
                    }
                    else {
                        UmlCode theo = action;
                        QString err = arrowBeginning->may_connect(action, i);

                        if (err.isEmpty()) {
                            if ((theo != action) && (start != arrowBeginning))
                                relation_to_simplerelation(action);

                            start->connexion(action, i, mousePressPos, scenePoint.toPoint());
                            window()->package_modified();
                            temp.clear();
                            draw_line = FALSE;
                            this->viewport()->unsetCursor();
                            arrowBeginning->post_connexion(action, i);
                        }
                        else if (start->may_connect(action)) {
                            // component required/provided interface
                            // sequence diagram lost msg
                            if (start->connexion(action, mousePressPos, scenePoint.toPoint())) {
                                window()->package_modified();
                                temp.clear();
                                draw_line = FALSE;
                                this->viewport()->unsetCursor();
                            }
                            else
                                abort_line_construction();
                        }
                        else if (err != QObject::tr("illegal")) {
                            msg_critical("Douml", err);
                            abort_line_construction();
                        }
                        else if (arrowBeginning->allowed_direction(action) == DiagramItem::All) {
                            add_point(e);
                            return;
                        }
                        else
                            abort_line_construction();
                    }

                }
                else
                    abort_line_construction();
            }
            else if (start == 0)
                // start/found msg without dest/start specified
                abort_line_construction();
            else if (start->may_connect(action)) {
                // component required/provided interface
                // sequence diagram lost msg
                if (start->connexion(action, mousePressPos, scenePoint.toPoint())) {
                    window()->package_modified();
                    temp.clear();
                    draw_line = FALSE;
                    this->viewport()->unsetCursor();
                }
                else
                    abort_line_construction();
            }
            else if (arrowBeginning->allowed_direction(action) == DiagramItem::All) {
                add_point(e);
                return;
            }
            else
                abort_line_construction();

            history_protected = TRUE;
            canvas()->update();
            history_protected = FALSE;
            window()->selectOn();
        }
        else if ((button == ::Qt::LeftButton) && (selectArea != 0)) {
            // selectionne les objets dans la zone de selection
            QRectF r = selectArea->sceneBoundingRect();
            //possible Qt bug with negative width and heigth values
            if(r.width()<0)
            {
                qreal w = r.width();
                r.setX(r.x() + w);
                r.setWidth(-w);
            }
            if(r.height()<0)
            {
                qreal h = r.height();
                r.setY(r.y() + h);
                r.setHeight(-h);
            }

            the_canvas()->del(selectArea);
            selectArea = 0;

            QList<QGraphicsItem*> l = canvas()->items(r);
            QList<QGraphicsItem*>::Iterator it;
            //habip
            if(l.count()<3)
                printf("not selected\r\n");


            for (it = l.begin(); it != l.end(); ++it)
            {
                QRectF bound = (*it)->sceneBoundingRect();
                if (r.contains((*it)->sceneBoundingRect()/*, TRUE*/) && // completement inclus
                        !isa_alien(*it) &&		// DiagramItem
                        (*it)->isVisible() &&		// pas en attente de destruction
                        !(*it)->isSelected())   	// pas deja selectionne
                    select(*it);
            }

            history_protected = TRUE;
            canvas()->update();
            history_protected = FALSE;
        }
    }
}

void DiagramView::wheelEvent(QWheelEvent * e)
{
    int currentVal;
    switch (e->modifiers()) {
    case ::Qt::ShiftModifier:
        // note : direction doesn't exist with Qt2.3 and to
        // force direction to horizontal doesn't work with Qt3
        currentVal = horizontalScrollBar()->value();
        currentVal += e->delta() / -10;
        horizontalScrollBar()->setValue(currentVal);
        e->accept();
        break;

    case ::Qt::ControlModifier:
        window()->change_zoom(e->delta() / 12);
        e->accept();
        break;

    default:
        // not use QCanvasView::contentsWheelEvent(e)
        // to have the same speed in horiz and vert
        currentVal = verticalScrollBar()->value();
        currentVal += e->delta() / -10;
        verticalScrollBar()->setValue(currentVal);
        e->accept();
        break;
    }
}

void DiagramView::add_point(QMouseEvent * e)
{
    // adds an ArrowPoint and the line to it
    QPoint diagramPoint(e->x(), e->y());
    QPointF scenePoint = mapToScene(diagramPoint);
    history_protected = TRUE;
    ArrowPointCanvas * ap =
            new ArrowPointCanvas(the_canvas(), scenePoint.x(), scenePoint.y());
    UmlCode action = window()->buttonOn();
    UmlCode t = window()->browser_diagram()->get_type();
    ArrowCanvas * a;

    ap->show();
    ap->upper();

    if ((t == UmlClassDiagram) && IsaRelation(action))
        a = new RelationCanvas(the_canvas(), start, ap, 0, action, 0, -1.0, -1.0);
    else if ((t == UmlObjectDiagram) && (action == UmlObjectLink))
        a = new ObjectLinkCanvas(the_canvas(), start, ap, UmlObjectLink, 0, -1.0, -1.0);
    else if ((t == UmlColDiagram) && (action == UmlLink))
        a = new CodLinkCanvas(the_canvas(), start, ap, 0, -1.0, -1.0);
    else if (((t == UmlComponentDiagram) || (t == UmlDeploymentDiagram))
             && (action == UmlContain))
        a = new AssocContainCanvas(the_canvas(), start, ap, 0, -1.0, -1.0);
    else if ((t == UmlStateDiagram) && (action == UmlTransition))
        a = new TransitionCanvas(the_canvas(), start, ap, 0, 0, -1.0, -1.0);
    else if ((t == UmlActivityDiagram) && (action == UmlFlow))
        a = new FlowCanvas(the_canvas(), start, ap, 0, 0, -1.0, -1.0);
    else if (IsaSimpleRelation(action))
        a = new SimpleRelationCanvas(the_canvas(), start, ap, 0, action, 0, -1.0, -1.0);
    else
        a = new ArrowCanvas(the_canvas(), start, ap, action, 0, FALSE, -1.0, -1.0);
    temp.append(a);		// before the point, see abort_line_construction()
    temp.append(ap);

    a->show();

    // re create immediatly the line
    draw_line = TRUE;
    mousePressPos = e->pos();
    start = ap;
    canvas()->addItem(line = new QGraphicsLineItem());
    line->setZValue(TOP_Z);
    line->setLine(scenePoint.x(), scenePoint.y(),
                    scenePoint.x(), scenePoint.y());
    line->setPen(::Qt::DotLine);
    line->show();
    line->setPen(::Qt::SolidLine);

    canvas()->update();
    history_protected = FALSE;
    window()->package_modified();

    // remark : mouse tracking does not work (?)
    this->viewport()->setCursor(::Qt::PointingHandCursor);
}

void DiagramView::mouseMoveEvent(QMouseEvent * e)
{
    QPoint diagramPoint(e->x(), e->y());
    QPointF scenePoint = mapToScene(diagramPoint);
    if (pressedButton == ::Qt::MidButton) {
        scroll(mousePressPos.x() - scenePoint.x(),
               mousePressPos.y() - scenePoint.y());


        mousePressPos = scenePoint.toPoint();
    }
    else if (!window()->frozen()) {
        if (pressedButton == ::Qt::LeftButton) {
            ensureVisible(scenePoint.x(),scenePoint.y(), 10, 10);

            history_protected = TRUE;

            int dx = scenePoint.x() - mousePressPos.x();
            int dy = scenePoint.y() - mousePressPos.y();
            QList<QGraphicsItem*> selected = selection();

            if (! selected.isEmpty()) {
                // deplace/redimentionne les objets selectionnes
                if ((selected.count() == 1) && isa_arrow(selected.first())) {
                    ArrowCanvas * a = ((ArrowCanvas *) selection().first());
                    ArrowPointCanvas * ap;

                    if (on_arrow_decenter) {
                        a->decenter(scenePoint.toPoint(), decenter_start, decenter_horiz);
                        window()->package_modified();
                    }
                    else if (a->is_decenter(mousePressPos, decenter_start, decenter_horiz)) {
                        on_arrow_decenter = TRUE;
                        history_save();
                        a->decenter(scenePoint.toPoint(), decenter_start, decenter_horiz);
                        window()->package_modified();
                    }
                    else if (a->cut_on_move(ap)) {
                        // cuts the line in two adding an ArrowPoint which
                        // becomes the alone selected item allowing to move it
                        history_save();
                        unselect(a);
                        select(a->brk(scenePoint.toPoint()));
                        window()->package_modified();
                        first_move = FALSE;
                    }
                    else if (ap != 0) {
                        // replace the selection by 'ap' to move it
                        unselect(a);
                        select(ap);

                        if (first_move) {
                            history_save();
                            first_move = FALSE;
                            moveSelected(dx, dy, TRUE);
                        }
                        else
                            moveSelected(dx, dy, FALSE);
                    }
                }
                else {
                    if (first_move) {
                        history_save();
                        first_move = FALSE;
                        moveSelected(dx, dy, TRUE);
                    }
                    else if (do_resize)
                        resizeSelected(dx, dy);
                    else
                        moveSelected(dx, dy, FALSE);
                }

                mousePressPos = scenePoint.toPoint();
            }
            else if (draw_line) {
                if (line == 0) {
                    // premier deplacement : cree la ligne
                    canvas()->addItem(line = new QGraphicsLineItem());
                    line->setZValue(TOP_Z);

                    switch ((arrowBeginning == 0)
                            ? DiagramItem::Horizontal
                            : arrowBeginning->allowed_direction(window()->buttonOn())) {
                    case DiagramItem::Horizontal:
                        // horizontal line
                        line->setLine(mousePressPos.x(), mousePressPos.y(),
                                      scenePoint.x(), scenePoint.y());
                        break;

                    default:
                        line->setLine(mousePressPos.x(), mousePressPos.y(),
                                      scenePoint.x(), scenePoint.y());
                        break;
                    }

                    line->setPen(::Qt::DotLine);
                    line->show();
                    line->setPen(::Qt::SolidLine);
                }
                else {
                    QPoint st = line->line().p1().toPoint();

                    switch ((arrowBeginning == 0)
                            ? DiagramItem::Horizontal
                            : arrowBeginning->allowed_direction(window()->buttonOn())) {
                    case DiagramItem::Horizontal:
                        // horizontal line
                        line->setLine(st.x(), st.y(), scenePoint.x(), scenePoint.y());
                        break;

                    default:
                        line->setLine(st.x(), st.y(), scenePoint.x(), scenePoint.y());
                    }
                }
            }
            else {
                // la selection est vide, veut probablement la faire en faisant
                // une zone via la souris, montre cette zone
                if (selectArea == 0) {
                    // premier deplacement : cree la zone
                    selectArea =
                            new SelectAreaCanvas(mousePressPos.x(), mousePressPos.y(), dx, dy, canvas());

                    selectArea->setZValue(TOP_Z);
                    selectArea->show();
                }
                else {
                    // redimensionne la zone
                    selectArea->setRect(scenePoint.x()-dx,scenePoint.y()-dy, dx, dy);
                }
            }

            canvas()->update();
            history_protected = FALSE;
        }
    }
}

void DiagramView::abort_line_construction()
{
    if (draw_line) {
        draw_line = FALSE;
        history_protected = TRUE;
        this->viewport()->unsetCursor();

        if (line != 0) {
            the_canvas()->del(line);
            line = 0;
        }

        if (! temp.isEmpty()) {
            QList<QGraphicsItem*>::Iterator it = temp.begin();

            // remove the line in the start item
            arrowBeginning->remove_line(((ArrowCanvas *) *it));
           do{
                the_canvas()->del(*it);
                /*it = */temp.removeOne(*it);
            }
            while (++it != temp.end());
        }

        canvas()->update();
        history_protected = FALSE;
    }
}

void DiagramView::relation_to_simplerelation(UmlCode k)
{
    QList<QGraphicsItem*>::Iterator it = temp.begin();

    // remove the line in the start item
    arrowBeginning->remove_line(((ArrowCanvas *) *it));

    start = arrowBeginning;
    do {
        // *it = arrow, (*it+1) = arrowpoint
        the_canvas()->del(*it);
        it = temp.erase(it);

        ArrowPointCanvas * ap =
                new ArrowPointCanvas(the_canvas(), (int)(*it)->x(), (int)(*it)->y());

        ap->upper();

        ArrowCanvas * a =
                new SimpleRelationCanvas(the_canvas(), start, ap, 0, k, 0, -1.0, -1.0);

        ap->show();
        a->show();
        start = ap;

        the_canvas()->del(*it);
        it = temp.erase(it);
    }
    while (it != temp.end());
}






void DiagramView::delete_them(bool in_model)
{
    if (!in_model)
        history_save();
    for (;;) {
        const QList<QGraphicsItem*> & selected = selection();

        if (selected.isEmpty())
            break;

        QList<QGraphicsItem*>::ConstIterator it = selected.begin();
        DiagramItem * item = QCanvasItemToDiagramItem(*it);
        BooL in = FALSE;
        BooL out = FALSE;

        item->delete_available(in, out);

        if (in || out)
            item->remove(in_model && in);		// modify selection()
        else
            the_canvas()->unselect(*it);
    }

    window()->package_modified();
}




void DiagramView::alignLeft()
{
    const QList<QGraphicsItem*> selected = selection();
    QList<QGraphicsItem*>::ConstIterator it = selected.begin();
    double ref = (*it)->sceneBoundingRect().left();

    while ((++it)  != selected.end())
    {
        DiagramItem *dItem =  QCanvasItemToDiagramItem((*it));
        if(dItem)
        {
            dItem->moveBy(ref - (*it)->sceneBoundingRect().left(), 0);
        }
        else
            (*it)->moveBy(ref - (*it)->sceneBoundingRect().left(), 0);
    }
}

void DiagramView::alignRight()
{
    const QList<QGraphicsItem*> selected = selection();
    QList<QGraphicsItem*>::ConstIterator it = selected.begin();
    double ref = (*it)->sceneBoundingRect().right();

    while ((++it)  != selected.end())
    {
        DiagramItem *dItem =  QCanvasItemToDiagramItem((*it));
        if(dItem)
        {
            dItem->moveBy(ref - (*it)->sceneBoundingRect().right(), 0);
        }
        else
            (*it)->moveBy(ref - (*it)->sceneBoundingRect().right(), 0);
    }

    window()->package_modified();
}

void DiagramView::alignTop()
{
    const QList<QGraphicsItem*> selected = selection();
    QList<QGraphicsItem*>::ConstIterator it = selected.begin();
    double ref = (*it)->sceneBoundingRect().top();

    while ((++it)  != selected.end())
    {
        DiagramItem *dItem =  QCanvasItemToDiagramItem((*it));
        if(dItem)
        {
            dItem->moveBy(0, ref - (*it)->sceneBoundingRect().top());
        }
        else
            (*it)->moveBy(0, ref - (*it)->sceneBoundingRect().top());
    }
}

void DiagramView::alignBottom()
{

    const QList<QGraphicsItem*> selected = selection();
    QList<QGraphicsItem*>::ConstIterator it = selected.begin();
    double ref = (*it)->sceneBoundingRect().bottom();
    while ((++it)  != selected.end())
    {
        DiagramItem *dItem =  QCanvasItemToDiagramItem((*it));
        if(dItem)
        {
            dItem->moveBy(0, ref - (*it)->sceneBoundingRect().bottom());
        }
        else
            (*it)->moveBy(0, ref - (*it)->sceneBoundingRect().bottom());
    }

    window()->package_modified();

}

void DiagramView::alignHorizontaly()
{
    const QList<QGraphicsItem*> selected = selection();
    QList<QGraphicsItem*>::ConstIterator it = selected.begin();
    QRectF r = (*it)->sceneBoundingRect();
    double ref = (r.top() + r.bottom()) / 2;

    while ((++it)  != selected.end()) {
        r = (*it)->sceneBoundingRect();

        DiagramItem *dItem =  QCanvasItemToDiagramItem((*it));
        if(dItem)
        {
            dItem->moveBy(0, ref - (r.top() + r.bottom()) / 2);
        }
        else
            (*it)->moveBy(0, ref - (r.top() + r.bottom()) / 2);
    }

    window()->package_modified();
}

void DiagramView::alignVerticaly()
{
    const QList<QGraphicsItem*> selected = selection();
    QList<QGraphicsItem*>::ConstIterator it = selected.begin();
    QRectF r = (*it)->sceneBoundingRect();
    double ref = (r.left() + r.right()) / 2;

    while ((++it)  != selected.end()) {
        r = (*it)->sceneBoundingRect();

        DiagramItem *dItem =  QCanvasItemToDiagramItem((*it));
        if(dItem)
        {
            dItem->moveBy(ref - (r.left() + r.right()) / 2, 0);
        }
        else
            (*it)->moveBy(ref - (r.left() + r.right()) / 2, 0);
    }

    window()->package_modified();
}

void DiagramView::alignCenter()
{
    const QList<QGraphicsItem*> selected = selection();
    QList<QGraphicsItem*>::ConstIterator it = selected.begin();
    QRectF r = (*it)->sceneBoundingRect();
    double refx = (r.left() + r.right()) / 2;
    double refy = (r.top() + r.bottom()) / 2;

    while ((++it)  != selected.end()) {
        r = (*it)->sceneBoundingRect();

        DiagramItem *dItem =  QCanvasItemToDiagramItem((*it));
        if(dItem)
        {
            dItem->moveBy(refx - (r.left() + r.right()) / 2,
                          refy - (r.top() + r.bottom()) / 2);
        }
        else
        (*it)->moveBy(refx - (r.left() + r.right()) / 2,
                      refy - (r.top() + r.bottom()) / 2);
    }

    window()->package_modified();
}


void DiagramView::same_size(bool w, bool h)
{
    const QList<QGraphicsItem*> selected = selection();
    QList<QGraphicsItem*>::ConstIterator it;
    bool first = TRUE;
    QSize sz;
    for (it = selected.begin(); it != selected.end(); ++it) {
        if (!isa_label(*it)) {
            DiagramItem * item = QCanvasItemToDiagramItem(*it);

            if (item != 0 && (item->on_resize_point(item->rect().topLeft()) != NoCorner)) {
                if (first) {
                    QRect r = item->rect();

                    first = FALSE;
                    sz.setWidth(r.width());
                    sz.setHeight(r.height());
                }
                else
                    item->resize(sz, w, h);
            }
        }
    }
}

void DiagramView::multiple_selection_menu(bool in_model, bool out_model,
                                          bool alignable, int n_resize,
                                          QList<DiagramItem *> & l_drawing_settings)
{
    const QList<QGraphicsItem*> selected = selection();
    QList<QGraphicsItem*>::ConstIterator it;
    QMenu m(0);
    MenuFactory::createTitle(m, QObject::tr("Multiple selection menu"));
    m.addSeparator();

    for (it = selected.begin(); it != selected.end(); ++it) {
        if (QCanvasItemToDiagramItem(*it)->linked()) {
            MenuFactory::addItem(m, tr("Select linked items"), 1);
            m.addSeparator();
            break;
        }
    }

    QMenu al(0);
    QMenu sz(0);

    if (alignable) {
        QPixmap top((const char **) align_top);
        QPixmap bottom((const char **) align_bottom);
        QPixmap left((const char **) align_left);
        QPixmap right((const char **) align_right);
        QPixmap center((const char **) align_center);
        QPixmap vcenter((const char **) align_vcenter);
        QPixmap hcenter((const char **) align_hcenter);
        al.addAction(QIcon(top), QObject::tr("align top"))->setData(4);
        al.addAction(QIcon(bottom), QObject::tr("align bottom"))->setData(5);
        al.addAction(QIcon(left), QObject::tr("align left"))->setData(6);
        al.addAction(QIcon(right), QObject::tr("align right"))->setData(7);
        al.addAction(QIcon(center), QObject::tr("align center"))->setData(8);
        al.addAction(QIcon(vcenter), QObject::tr("align center verticaly"))->setData(9);
        al.addAction(QIcon(hcenter), QObject::tr("align center horizontaly"))->setData(10);

        MenuFactory::insertItem(m, tr("Align"), &al);
    }

    if (n_resize > 1) {
        MenuFactory::addItem(sz, tr("same width"), 14);
        MenuFactory::addItem(sz, tr("same height"), 15);
        MenuFactory::addItem(sz, tr("same width and height"), 16);

        MenuFactory::insertItem(m, tr("Size"), &sz);
        m.addSeparator();
    }
    else if (alignable)
        m.addSeparator();

    MenuFactory::addItem(m, tr("Copy selected (Ctrl+c)"), 11);

    if (out_model) {
        MenuFactory::addItem(m, tr("Cut selected (Ctrl+x, remove from diagram)"), 12);
        MenuFactory::addItem(m, tr("Remove selected from view (Suppr)"), 2);
    }

    if (in_model)
        MenuFactory::addItem(m, tr("Delete selected (Ctrl+d)"), 3);

    if (l_drawing_settings.count() > 1) {
        m.addSeparator();
        MenuFactory::addItem(m, tr("Edit drawing settings"), 13);
        MenuFactory::addItem(m, tr("Same drawing settings"), 17);
    }

    history_protected = TRUE;

    QAction* retAction = m.exec(QCursor::pos());
    if(retAction)
    {
    switch (retAction->data().toInt()) {
    case 1:
        unselect_all();

        for (it = selected.begin(); it != selected.end(); ++it)
            QCanvasItemToDiagramItem(*it)->select_associated();

        break;

    case 12:
        clipboard = window()->copy_selected();
        copied_from = window()->browser_diagram()->get_type();

        // no break !
    case 2:
        delete_them(FALSE);
        break;

    case 3:
        delete_them(TRUE);
        break;

    case 4:
        history_save();
        alignTop();
        break;

    case 5:
        history_save();
        alignBottom();
        break;

    case 6:
        history_save();
        alignLeft();
        break;

    case 7:
        history_save();
        alignRight();
        break;

    case 8:
        history_save();
        alignCenter();
        break;

    case 9:
        history_save();
        alignVerticaly();
        break;

    case 10:
        history_save();
        alignHorizontaly();
        break;

    case 11:
        clipboard = window()->copy_selected();
        copied_from = window()->browser_diagram()->get_type();
        return;

    case 13:
        history_protected = FALSE;
        l_drawing_settings.first()->edit_drawing_settings(l_drawing_settings);
        break;

    case 14:
        history_save();
        same_size(TRUE, FALSE);
        break;

    case 15:
        history_save();
        same_size(FALSE, TRUE);
        break;

    case 16:
        history_save();
        same_size(TRUE, TRUE);
        break;

    case 17:
        history_protected = FALSE;
        if (!l_drawing_settings.isEmpty()) {
            const DiagramItem *source = l_drawing_settings[0];
            for (int i = 1, n = l_drawing_settings.size(); i < n; ++i)
                l_drawing_settings[i]->clone_drawing_settings(source);
        }

    default:
        return;
    }
    }

    canvas()->update();
    history_protected = FALSE;
}

void DiagramView::moveSelected(int dx, int dy, bool first)
{
    QList<QGraphicsItem*> selected = selection();
    QList<QGraphicsItem*>::ConstIterator it;
    if (first) {
        for (it = selected.begin(); it != selected.end(); ++it)
            QCanvasItemToDiagramItem(*it)
                    ->prepare_for_move(do_resize != NoCorner);

        selected = selection();
    }

    for (it = selected.begin(); it != selected.end(); ++it)
            QCanvasItemToDiagramItem(*it)->moveBy(dx, dy); //arrow canvas bagli item ile de move ediliyor
    window()->package_modified();
}

void DiagramView::resizeSelected(int dx, int dy)
{
    QList<QGraphicsItem*> selected = selection();
    QList<QGraphicsItem*>::ConstIterator it;
    if (previousResizeCorrection.isEmpty()) {
        QPoint p(0, 0);

        for (it = selected.begin(); it != selected.end(); ++it)
            previousResizeCorrection.append(p);
    }

    QList<QPoint>::Iterator it2;

    for (it = selected.begin(), it2 = previousResizeCorrection.begin();
         it != selected.end();
         ++it, ++it2)
        QCanvasItemToDiagramItem(*it)->resize(do_resize, dx, dy, *it2);

    window()->package_modified();
}

void DiagramView::keyPressEvent(QKeyEvent * e)
{
    if (draw_line) {
        abort_line_construction();
        e->ignore();
    }
    else if (!window()->frozen()) {
        QString s = Shortcut::shortcut(e->key(), e->modifiers());

        if (!s.isEmpty()) {
            e->accept();

            if (s == "Move left") {
                history_protected = TRUE;

                if (first_move) {
                    history_save();
                    first_move = FALSE;
                    moveSelected(-1, 0, TRUE);
                }
                else
                    moveSelected(-1, 0, FALSE);
            }
            else if (s == "Move right") {
                history_protected = TRUE;

                if (first_move) {
                    history_save();
                    first_move = FALSE;
                    moveSelected(1, 0, TRUE);
                }
                else
                    moveSelected(1, 0, FALSE);
            }
            else if (s == "Move up") {
                history_protected = TRUE;

                if (first_move) {
                    history_save();
                    first_move = FALSE;
                    moveSelected(0, -1, TRUE);
                }
                else
                    moveSelected(0, -1, FALSE);
            }
            else if (s == "Move down") {
                history_protected = TRUE;

                if (first_move) {
                    history_save();
                    first_move = FALSE;
                    moveSelected(0, 1, TRUE);
                }
                else
                    moveSelected(0, 1, FALSE);
            }
            else if (s == "Delete") {
                history_protected = FALSE;
                delete_them(TRUE);
            }
            else if (s == "Remove from diagram") {
                history_protected = TRUE;
                delete_them(FALSE);
            }
            else if (s == "Select all") {
                history_protected = TRUE;
                select_all();	// clear history_protected
                return;
            }
            else if (s == "Copy") {
                history_protected = TRUE;
                clipboard = window()->copy_selected();
                copied_from = window()->browser_diagram()->get_type();
            }
            else if (s == "Paste") {
                history_protected = TRUE;

                if (!clipboard.isEmpty() &&
                        (copied_from == window()->browser_diagram()->get_type()))
                    paste();
            }
            else if (s == "Cut") {
                history_protected = TRUE;
                clipboard = window()->copy_selected();
                copied_from = window()->browser_diagram()->get_type();
                delete_them(FALSE);
            }
            else if (s == "Undo") {
                history_protected = TRUE;

                if (available_undo())
                    undo();
                else
                    QApplication::beep();

                return;
            }
            else if (s == "Redo") {
                history_protected = TRUE;

                if (available_redo())
                    redo();
                else
                    QApplication::beep();

                return;
            }
            else if (s == "Save") {
                history_protected = TRUE;
                UmlWindow::save_it();
            }
            else if (s == "Save as") {
                if (!UmlWindow::saveas_it())
                    history_protected = TRUE;
                else
                    return;
            }
            else if (s == "Close") {
                UmlWindow::do_close();
                return;
            }
            else if (s == "Quit") {
                UmlWindow::do_quit();
                return;
            }
            else if (s == "Open project") {
                UmlWindow::load_it();
                return;
            }
            else if (s == "Print") {
                history_protected = TRUE;
                UmlWindow::print_it();
            }
            else if (s == "Browser search") {
                history_protected = TRUE;
                UmlWindow::browser_search_it();
            }
            else if (s == "Arrow geometry") {
                history_protected = TRUE;

                const QList<QGraphicsItem*> selected = selection();
                QList<QGraphicsItem*>::ConstIterator it;
                QList<QGraphicsItem*> l;
                // search for arrow beginning
                for (it = selected.begin(); it != selected.end(); ++it) {
                    if (isa_arrow(*it)) {
                        ArrowCanvas * ar = (ArrowCanvas *) *it;
                        DiagramItem * b;
                        DiagramItem * e;

                        while (ar->extremities(b, e), b->typeUmlCode() == UmlArrowPoint)
                            ar = ((ArrowPointCanvas *) b)->get_other(ar);

                        if ((ar->get_start() != ((ArrowCanvas *) *it)->get_end()) &&
                                (!l.contains(ar)))
                            l.append(ar);
                    }
                }
                unselect_all();

                for (it = l.begin(); it != l.end(); ++it) {
                    // warning : the selected arrow may disapear =>
                    // select the returned arrow still present
                    // this allows to do several control-L
                    select(((ArrowCanvas *) *it)->next_geometry());
                }
            }
            else if (s == "Optimal scale") {
                history_protected = TRUE;
                window()->fit_scale();
                return;
            }
            else if (s == "Optimal window size") {
                do_optimal_window_size();
                return;
            }
            else if (s == "Zoom +") {
                window()->change_zoom(10);
                return;
            }
            else if (s == "Zoom -") {
                window()->change_zoom(-10);
                return;
            }
            else if (s == "Zoom 100%") {
                window()->new_scale(100);
                return;
            }
            else if (s == "Diagram menu") {
                if (! BrowserNode::popupMenuActive()) {	// Qt bug
                    BrowserNode::setPopupMenuActive(TRUE);

                    menu(QPoint(0, 0));
                    BrowserNode::setPopupMenuActive(FALSE);
                }

                return;
            }
            else {
                const QList<QGraphicsItem*> selected = selection();
                int nselected = selected.count();

                if (nselected > 1) {
                    if (s == "Select linked items") {
                        history_protected = TRUE;
                        unselect_all();

                        QList<QGraphicsItem*>::ConstIterator it;
                        for (it = selected.begin(); it != selected.end(); ++it)
                            QCanvasItemToDiagramItem(*it)->select_associated();
                    }
                    else if ((s == "Edit drawing settings") ||
                             (s == "Same drawing settings")) {
                        QList<QGraphicsItem*>::ConstIterator it;
                        UmlCode k = UmlCodeSup;
                        QList<DiagramItem *> l;

                        for (it = selected.begin(); it != selected.end(); ++it) {
                            if (! isa_label(*it)) {
                                DiagramItem * item = QCanvasItemToDiagramItem(*it);

                                if (item->has_drawing_settings()) {
                                    // note : relations doesn't have drawing setting, transition and flow have
                                    switch (k) {
                                    case UmlCodeSup:
                                        // first case
                                        k = item->typeUmlCode();
                                        l.append(item);
                                        break;

                                    case UmlArrowPoint:
                                        // mark for several types
                                        break;

                                    default:
                                        if (item->typeUmlCode() == k)
                                            l.append(item);
                                        else {
                                            // several types
                                            l.clear();
                                            k = UmlArrowPoint;	// mark for several types
                                        }
                                    }
                                }
                            }
                        }

                        switch (l.count()) {
                        case 0:
                            break;

                        case 1:
                            history_protected = FALSE;
                            l.first()->apply_shortcut(s);
                            break;

                        default:
                            history_protected = FALSE;

                            if (s == "Edit drawing settings")
                                l.first()->edit_drawing_settings(l);
                            else {
                                history_protected = FALSE;
                                if (!l.isEmpty()) {
                                    const DiagramItem *source = l[0];
                                    for (int i = 1, n = l.size(); i < n; ++i)
                                        l[i]->clone_drawing_settings(source);
                                }
                            }
                        }
                    }
                    else if (s == "Align bottom") {
                        history_protected = TRUE;
                        history_save();
                        alignBottom();
                    }
                    else if (s == "Align center") {
                        history_protected = TRUE;
                        history_save();
                        alignCenter();
                    }
                    else if (s == "Align center horizontaly") {
                        history_protected = TRUE;
                        history_save();
                        alignHorizontaly();
                    }
                    else if (s == "Align center verticaly") {
                        history_protected = TRUE;
                        history_save();
                        alignVerticaly();
                    }
                    else if (s == "Align left") {
                        history_protected = TRUE;
                        history_save();
                        alignLeft();
                    }
                    else if (s == "Align right") {
                        history_protected = TRUE;
                        history_save();
                        alignRight();
                    }
                    else if (s == "Align top") {
                        history_protected = TRUE;
                        history_save();
                        alignTop();
                    }
                    else if (s == "Same width") {
                        history_protected = TRUE;
                        history_save();
                        same_size(TRUE, FALSE);
                    }
                    else if (s == "Same height") {
                        history_protected = TRUE;
                        history_save();
                        same_size(FALSE, TRUE);
                    }
                    else if (s == "Same size") {
                        history_protected = TRUE;
                        history_save();
                        same_size(TRUE, TRUE);
                    }
                    else if (s == "Menu") {
                        BooL in_model;
                        BooL out_model;
                        BooL alignable;
                        QList<DiagramItem *> l_drawing_settings;
                        int n_resize;

                        if (multiple_selection_for_menu(in_model, out_model, alignable,
                                                        n_resize, l_drawing_settings, selected)) {
                            multiple_selection_menu(in_model, out_model, alignable,
                                                    n_resize, l_drawing_settings);
                            return;
                        }
                    }
                }
                else if (nselected == 1) {

                    DiagramItem * item =
                            QCanvasItemToDiagramItem(selected.first());

                    if (item != 0) {
                        if (s == "Select linked items") {
                            history_protected = TRUE;
                            unselect_all();
                            item->select_associated();
                        }
                        else if (s == "Menu") {
                            if (! BrowserNode::popupMenuActive()) {	// Qt bug
                                BrowserNode::setPopupMenuActive(TRUE);

                                item->menu(item->rect().center());
                                BrowserNode::setPopupMenuActive(FALSE);
                            }

                            return;
                        }
                        else if (s == "Edit") {
                            unselect_all();
                            item->open();
                            return;
                        }
                        else {
                            history_protected = FALSE;
                            item->apply_shortcut(s);
                        }
                    }
                    else if (s == "Menu") {
                        if (! BrowserNode::popupMenuActive()) {	// Qt bug
                            BrowserNode::setPopupMenuActive(TRUE);

                            menu(QPoint(0, 0));
                            BrowserNode::setPopupMenuActive(FALSE);
                        }

                        return;
                    }
                }
                else if (s == "Menu") {
                    if (! BrowserNode::popupMenuActive()) {	// Qt bug
                        BrowserNode::setPopupMenuActive(TRUE);

                        menu(QPoint(0, 0));
                        BrowserNode::setPopupMenuActive(FALSE);
                    }

                    return;
                }
            }
            canvas()->update();
            history_protected = FALSE;
        }
        else
            e->ignore();
    }
    else
        e->ignore();
}

void DiagramView::keyReleaseEvent(QKeyEvent *)
{
    first_move = FALSE;
}

void DiagramView::select_all()
{
    QList<QGraphicsItem*> all = canvas()->items();
    QList<QGraphicsItem*>::Iterator cit;

    for (cit = all.begin(); cit != all.end(); ++cit) {
        if ((QCanvasItemToDiagramItem(*cit) != 0) && // an uml canvas item
                !(*cit)->isSelected() &&
                (*cit)->isVisible())
            select(*cit);
    }

    history_protected = TRUE;
    canvas()->update();
    history_protected = FALSE;
}

void DiagramView::set_zoom(double zoom)
{
    if (draw_line)
        abort_line_construction();

    ((UmlCanvas *) canvas())->show_limits(FALSE);
    ((UmlCanvas *) canvas())->set_zoom(zoom);

    QList<QGraphicsItem*> all = canvas()->items();
    QList<QGraphicsItem*>::Iterator cit;

    // hack to freeze arrow's labels position : select all
    QList<QGraphicsItem*> selected = selection();

    for (cit = all.begin(); cit != all.end(); ++cit) {
        if ((QCanvasItemToDiagramItem(*cit) != 0) && // an uml canvas item
                !(*cit)->isSelected() &&
                (*cit)->isVisible())
            select(*cit);
    }

    DiagramItem * di;

    for (cit = all.begin(); cit != all.end(); ++cit)
        if ((*cit)->isVisible() &&
                !isa_arrow(*cit) &&
                ((di = QCanvasItemToDiagramItem(*cit)) != 0))
            di->change_scale();

    for (cit = all.begin(); cit != all.end(); ++cit)
        if ((*cit)->isVisible() && isa_arrow(*cit))
            ((ArrowCanvas *) *cit)->change_scale();

    // hack end
    unselect_all();

    for (cit = selected.begin(); cit != selected.end(); ++cit)
        select(*cit);

    ((UmlCanvas *) canvas())->zoom_end();
    ((UmlCanvas *) canvas())->show_limits(TRUE);

    canvas()->update();

}

void DiagramView::needed_width_height(int & maxx, int & maxy, int &minx, int &miny) const
{
    // search the max used x and y
    QList<QGraphicsItem*> all = canvas()->items();
    QList<QGraphicsItem*>::Iterator cit;

    maxx = 0;
    maxy = 0;
    minx = 10000;
    miny = 10000;

    for (cit = all.begin(); cit != all.end(); ++cit) {
        DiagramItem * di;

        if ((*cit)->isVisible() &&
                ((di = QCanvasItemToDiagramItem(*cit)) != 0)) {
            if (di->typeUmlCode() != UmlLifeLine) {
                QRect r = (*cit)->sceneBoundingRect().toRect();

                if (r.right() > maxx)
                    maxx = r.right();

                if (r.bottom() > maxy)
                    maxy = r.bottom();

                if(r.left() < minx)
                    minx = r.left();
                if(r.top()<miny)
                    miny = r.top();
            }
        }
    }
}

void DiagramView::fit_scale()
{
    if (draw_line)
        abort_line_construction();

    int maxx;
    int maxy;
    int miny;
    int minx;

    needed_width_height(maxx, maxy, minx, miny);
    double scale = the_canvas()->zoom() * viewport()->width() / maxx;
    double scale_y = the_canvas()->zoom() * viewport()->height() / maxy;

    if (scale > scale_y)
        scale = scale_y;

    scale -= 0.02;

    set_zoom((scale < SCALE_MIN / 100.0)
             ? SCALE_MIN / 100.0
             : ((scale > SCALE_MAX / 100.0) ? SCALE_MAX / 100.0 : scale));
}

void DiagramView::do_optimal_window_size()
{
    if (draw_line)
        abort_line_construction();
    history_protected = TRUE;
    optimal_window_size();
    canvas()->update();
    // do it an other time because of the scroll bars
#if defined(WIN32) || (QT_VERSION != 230)
    QTimer::singleShot(1, this, SLOT(optimal_window_size()));
#else
    optimal_window_size();
#endif
}

void DiagramView::optimal_window_size()
{
    int maxx;
    int maxy;
    int minx;
    int miny;

    needed_width_height(maxx, maxy, minx, miny);
    window()->resize(maxx + 10 + window()->width() - viewport()->width(),
                     maxy + 10 + window()->height() - viewport()->height());
}

void DiagramView::preferred_size_zoom()
{
    if (preferred_zoom != 0) {
        if (preferred_size.width() != 0)
            window()->resize(preferred_size);

        window()->new_scale((int)(preferred_zoom * 100));
    }
}

void DiagramView::set_format(int f)
{
    if (f != (int) window()->browser_diagram()->get_format()) {
        window()->browser_diagram()->set_format((CanvasFormat) f);
        the_canvas()->resize((CanvasFormat) f);
    }
}

static bool find_browser_element(QGraphicsScene * canvas, QList<QGraphicsItem*> & r)
{
    BrowserNode * bn = BrowserView::selected_item();

    if (bn == 0)
        return FALSE;

    BasicData * d = bn->get_data();
    UmlCode k = bn->get_type();
    QList<QGraphicsItem*> l = canvas->items();
    QList<QGraphicsItem*>::Iterator it;

    switch (k) {
    case UmlClassDiagram:
    case UmlUseCaseDiagram:
    case UmlSeqDiagram:
    case UmlColDiagram:
    case UmlComponentDiagram:
    case UmlDeploymentDiagram:
    case UmlObjectDiagram:
    case UmlActivityDiagram:
        k = UmlIcon;
        break;

    default:
        break;
    }

    for (it = l.begin(); it != l.end(); ++it) {
        if ((*it)->isVisible()) {
            DiagramItem * di = QCanvasItemToDiagramItem(*it);

            if ((di != 0) && (di->typeUmlCode() == k)) {
                if (di->get_bn() == bn)
                    r.append(*it);
                else {
                    ArrowCanvas * a = dynamic_cast<ArrowCanvas *>(di);

                    if ((a != 0) && (a->get_data() == d))
                        r.append(*it);
                }
            }
        }
    }
    return !r.isEmpty();
}

int DiagramView::default_menu(QMenu & m, int f)
{
    bool wr = (((UmlCanvas *) canvas())->browser_diagram())->is_writable();

    if (draw_line)
        abort_line_construction();

    QMenu formatm(0);
    QMenu formatlandscapem(0);
    QList<QGraphicsItem*> l;

    if (wr) {
        MenuFactory::addItem(m, tr("Edit drawing settings"), EDIT_DRAWING_SETTING_CMD);
        m.addSeparator();
    }

    MenuFactory::addItem(m, tr("Select diagram in browser"), 1);

    if (wr)
        MenuFactory::addItem(m, tr("Select all (Ctrl+a)"), 2);

    if (find_browser_element(canvas(), l))
        MenuFactory::addItem(m, tr("Find selected browser element"), 19);

    m.addSeparator();
    MenuFactory::addItem(m, tr("Copy optimal picture part"), 13);
    MenuFactory::addItem(m, tr("Copy visible picture part"), 3);
    MenuFactory::addItem(m, tr("Save optimal picture part (png)"), 14);
    MenuFactory::addItem(m, tr("Save visible picture part (png)"), 10);
    MenuFactory::addItem(m, tr("Save optimal picture part (svg)"), 15);
    MenuFactory::addItem(m, tr("Save visible picture part (svg)"), 16);

    if (wr && !clipboard.isEmpty() &&
            (copied_from == window()->browser_diagram()->get_type()))
        MenuFactory::addItem(m, tr("Paste copied items (Ctrl+v)"), 9);

    m.addSeparator();
    MenuFactory::addItem(m, tr("Optimal scale"), 7);
    MenuFactory::addItem(m, tr("Optimal window size"), 8);

    if (wr) {
        MenuFactory::addItem(m, tr("Set preferred size and scale"), 4);
        MenuFactory::addItem(m, tr("Set preferred scale (size unset)"), 17);

        if (preferred_zoom != 0) {
            if (preferred_size.width() != 0) {
                MenuFactory::addItem(m, tr("Restore preferred size and scale"), 5);
                MenuFactory::addItem(m, tr("Unset preferred size and scale"), 18);
            }
            else {
                MenuFactory::addItem(m, tr("Restore preferred scale"), 5);
                MenuFactory::addItem(m, tr("Unset preferred scale"), 18);
            }
        }

        init_format_menu(formatm, formatlandscapem, f);
        MenuFactory::insertItem(m, tr("Format"), &formatm);
        m.addSeparator();
        MenuFactory::addItem(m, tr("Undo all changes"), RELOAD_CMD);

        if (available_undo())
            MenuFactory::addItem(m, tr("Undo (Ctrl+z or Ctrl+u)"), 11);

        if (available_redo())
            MenuFactory::addItem(m, tr("Redo (Ctrl+y or Ctrl+r)"), 12);
    }

    m.addSeparator();
    MenuFactory::addItem(m, tr("Close"), 20);

    QAction *retAction = m.exec(QCursor::pos());
    if(retAction)
    {
        int choice = retAction->data().toInt();

        switch (choice) {
        case 1:
            history_protected = TRUE;
            the_canvas()->browser_diagram()->select_in_browser();
            break;

        case 2:
            select_all();
            break;

        case 19:
            history_protected = TRUE;
            unselect_all();

        {
            QList<QGraphicsItem*>::Iterator it;

            for (it = l.begin(); it != l.end(); ++it)
                select(*it);
        }

            ensureVisible((int) l.first()->x(), (int) l.first()->y(),1,1);
            canvas()->update();
            break;

        case 3:
            copy_in_clipboard(FALSE, FALSE);
            break;

        case 13:
            copy_in_clipboard(TRUE, FALSE);
            break;

        case 4:
            history_protected = TRUE;
            preferred_zoom = the_canvas()->zoom();
            preferred_size.setWidth(window()->width());
            preferred_size.setHeight(window()->height());
            window()->package_modified();
            break;

        case 17:
            history_protected = TRUE;
            preferred_zoom = the_canvas()->zoom();
            preferred_size.setWidth(0);
            preferred_size.setHeight(0);
            window()->package_modified();
            break;

        case 18:
            history_protected = TRUE;
            preferred_zoom = 0;
            preferred_size.setWidth(0);
            preferred_size.setHeight(0);
            window()->package_modified();
            break;

        case 5:
            preferred_size_zoom();
            break;

        case 7:
            window()->fit_scale();
            break;

        case 8:
            do_optimal_window_size();
            break;

        case 9:
            history_protected = TRUE;
            history_save();
            paste();
            break;

        case 10:
            history_protected = TRUE;
            save_picture(FALSE, FALSE);
            break;

        case 14:
            history_protected = TRUE;
            save_picture(TRUE, FALSE);
            break;

        case 15:
            history_protected = TRUE;
            save_picture(TRUE, TRUE);
            break;

        case 16:
            history_protected = TRUE;
            save_picture(FALSE, TRUE);
            break;

        case 11:
            undo();
            break;

        case 12:
            redo();
            break;

        case 20:
            window()->close();
            break;

        case EDIT_DRAWING_SETTING_CMD:
        case RELOAD_CMD:
            // to be sure they are not reused
            break;

        default:
            if (choice >= f) {
                set_format(choice - f);
                window()->package_modified();
            }
        }


        return choice;
    }
    return -1;
}

void DiagramView::init_format_menu(QMenu & m, QMenu & lm,
                                   int f) const
{
    int i;

    for (i = 0; i <= IsoA5; i += 1)
        MenuFactory::addItem(m, QString("Iso ") + stringify((CanvasFormat) i), f + i);

    for (; i <= UsE; i += 1)
        MenuFactory::addItem(m, QString("Ansi ") + stringify((CanvasFormat) i), f + i);

    for (; i != IsoA0Landscape; i += 1)
        MenuFactory::addItem(m, stringify((CanvasFormat) i), f + i);

    m.addSeparator();
    foreach (QAction* act, m.actions()) {
        act->setCheckable(true);
    }
    MenuFactory::insertItem(m, tr("Landscape formats"), &lm);

    for (; i <= IsoA5Landscape; i += 1)
        MenuFactory::addItem(lm, QString("Iso ") + stringify((CanvasFormat) i), f + i);

    for (; i <= UsELandscape; i += 1)
        MenuFactory::addItem(lm, QString("Ansi ") + stringify((CanvasFormat) i), f + i);

    for (; i != CanvasFormatSup; i += 1)
        MenuFactory::addItem(lm, stringify((CanvasFormat) i), f + i);

    foreach (QAction* act, lm.actions()) {
        act->setCheckable(true);
    }
    int current = (int) window()->browser_diagram()->get_format();

    if (current < (int) IsoA0Landscape)
        MenuFactory::findAction(m,f + current)->setChecked( TRUE);
    else
        MenuFactory::findAction(lm,f + current)->setChecked( TRUE);
}

void DiagramView::load(const char * pfix)
{
    // for a re-load :
    unselect_all();
    preferred_zoom = 0;
    set_on_load_diagram(TRUE);
    QList<QGraphicsItem*> all = canvas()->items();
    QList<QGraphicsItem*>::Iterator it;
    DiagramItem * di;

    for (it = all.begin(); it != all.end(); ++it)
        if (((di = QCanvasItemToDiagramItem(*it)) != 0) && // an uml canvas item
                (*it)->isVisible())
            di->delete_it();

    ((UmlCanvas *) canvas())->set_zoom(1);
    ((UmlCanvas *) canvas())->zoom_end();

    // load
//recreating  UndefinedNodePackage will cause crash
    BrowserNode::pre_load();
    PRE_TRY;

    try {
        QString t = pfix;

        t += " diagram " + ((QWidget *) parent())->windowTitle();

        read_in(t);
        read();
    }
    catch (int) {
        ;
    }

    POST_TRY;

    ArrowCanvas::post_load();
    BrowserNode::post_load(TRUE);
    DiagramItem::post_load();

    // to managed deleted items present in the browser
    all = canvas()->items();

    for (it = all.begin(); it != all.end(); ++it) {
        if ((*it)->isVisible() &&
                ((di = QCanvasItemToDiagramItem(*it)) != 0) &&
                (di->get_bn() != 0) && // do not manage relations here
                di->get_bn()->deletedp())
            di->delete_it();
    }

    // to fixe release 2.22 bug
    ArrowCanvas::remove_redondant_rels();

    if (window()->get_view() != 0)
        // re-load
        preferred_size_zoom();

    canvas()->update();

    all = canvas()->items();

    for (it = all.begin(); it != all.end(); ++it)
        if ((*it)->isVisible() &&
                ((di = QCanvasItemToDiagramItem(*it)) != 0))
            di->post_loaded();

    canvas()->update();

    set_on_load_diagram(FALSE);
}

void DiagramView::read()
{
    char * s;

    if ((s = read_definition(id, "diagram")) != 0) {
        unsigned format = read_file_format();
        bool error = FALSE;

        PRE_TRY;

        try {
            char * st = s;
            char * k;

            k = read_keyword(st);

            if (!strcmp(k, "format")) {
                set_read_file_format(read_unsigned(st));
                k = read_keyword(st);
            }
            else
                // format saved in diagram since format 4
                set_read_file_format(3);

            the_canvas()->read_old_diagram(read_file_format() < 9);

            read(st, k);
        }
        catch (...) {
            error = TRUE;
        }

        POST_TRY;

        delete [] s;
        the_canvas()->read_old_diagram(FALSE);
        set_read_file_format(format);
        the_canvas()->clear_old_ids();

        if (error) {
            THROW_ERROR 0;
        }
    }
}

void DiagramView::paste()
{
    history_protected = TRUE;
    set_on_load_diagram(TRUE);
    double old_zoom = ((UmlCanvas *) canvas())->zoom();
    char * s = new char[clipboard.length() + 1];

    memcpy(s, (const char *) clipboard, clipboard.length() + 1);

    unselect_all();
    set_zoom(1);
    the_canvas()->set_paste(TRUE);
    read_in("clipboard");

    PRE_TRY;

    try {
        char * st = s;
        char * k;

        k = read_keyword(st);

        if (!strcmp(k, "format")) {
            set_read_file_format(read_unsigned(st));
            k = read_keyword(st);
        }
        else
            // format saved in diagram since format 4
            set_read_file_format(3);

        read(st, k);
    }
    catch (int) {
        ;
    }

    POST_TRY;

    delete [] s;

    the_canvas()->clear_old_ids();
    the_canvas()->set_paste(FALSE);
    DiagramItem::post_load();

    // to managed deleted items present in the browser
    // compute rect containing all the paste items
    QList<QGraphicsItem*> l = selection();
    QList<QGraphicsItem*>::Iterator it;
    DiagramItem * di;
    double minx = 1e10;
    double maxx = 0;
    double miny = 1e10;
    double maxy = 0;

    for (it = l.begin(); it != l.end(); ++it) {
        if ((*it)->isVisible() &&
                ((di = QCanvasItemToDiagramItem(*it)) != 0) &&
                (di->get_bn() != 0) && // do not manage relations here
                di->get_bn()->deletedp())
            di->delete_it();
        else {
            QRectF r = (*it)->sceneBoundingRect();

            if (r.left() < minx)
                minx = r.left();

            if (r.top() < miny)
                miny = r.top();

            if (r.left() > maxx)
                maxx = r.right();

            if (r.top() > maxy)
                maxy = r.bottom();
        }
    }

    // place all paste items in the center of the viewport
    double dx = /*contentsX() +*/ width() / 2 - (minx + maxx) / 2;
    double dy = /*contentsY() + */height() / 2 - (miny + maxy) / 2;

    l = selection();

    for (it = l.begin(); it != l.end(); ++it)
        QCanvasItemToDiagramItem(*it)->prepare_for_move(FALSE);

    l = selection();

    for (it = l.begin(); it != l.end(); ++it)
        (*it)->moveBy(dx, dy);

    set_zoom(old_zoom);
    canvas()->update();

    l = canvas()->items();

    for (it = l.begin(); it != l.end(); ++it)
        if ((*it)->isVisible() &&
                ((di = QCanvasItemToDiagramItem(*it)) != 0))
            di->post_loaded();

    canvas()->update();

    set_on_load_diagram(FALSE);
    history_protected = FALSE;
    window()->package_modified();
}

bool DiagramView::is_present(BrowserNode * bn)
{
    QList<QGraphicsItem*> all = canvas()->items();
    QList<QGraphicsItem*>::Iterator it;

    for (it = all.begin(); it != all.end(); ++it) {
        if ((*it)->isVisible()) {
            DiagramItem * di = QCanvasItemToDiagramItem(*it);

            if ((di != 0) && di->represents(bn))
                return TRUE;
        }
    }
    return FALSE;
}

void DiagramView::add_related_elements(DiagramItem *, QString, bool, bool)
{
    // do nothing
}

bool DiagramView::save_pict(const char * f, bool optimal, bool temporary)
{
    QFileInfo fi(f);

    return (fi.fileName().right(3).toLower() == "svg")
            ? svg_save_in(f, optimal, temporary)
            : save_in(f, optimal, temporary);
}

bool DiagramView::save_in(const char * f, bool optimal, bool temporary)
{
    if (the_canvas()->selection().count() != 0) {
        // unselect element and redraw them to remove selection mark
        history_protected = TRUE;
        unselect_all();
        the_canvas()->update();
        canvas()->update();
        history_protected = TRUE;
    }

    the_canvas()->show_limits(FALSE);

    bool r;
    if (optimal) {
        int x0 = 0;//center();
        int y0 = 0; //contentsY();

        //setContentsPos(0, 0);

        int maxx;
        int maxy;
        int minx;
        int miny;

        needed_width_height(maxx, maxy, minx, miny);
        maxx += 30;
        maxy += 10;
        // add a large margin to be sure to see all in one shot contrarilly
        // to the optimal_window_size whose must have the pretty size
        if ((viewport()->width() >= (maxx + 90)) && (viewport()->height() >= (maxy + 90)))
            r = QPixmap::grabWidget(viewport(), 0, 0, maxx, maxy).save(f, "PNG");
        else {

            int saved_w;
            int saved_h;

            saved_w = window()->width();
            saved_h = window()->height();

            window()->resize(maxx + 90, maxy + 90);
            history_protected = TRUE;
            r = QPixmap::grabWidget(viewport(), 0, 0, maxx, maxy).save(f, "PNG");

            if (! temporary) {
                window()->resize(saved_w, saved_h);
            }
        }

        if (! temporary)
        {
           // setContentsPos(x0, y0);
        }
    }
    else
        r = QPixmap::grabWidget(viewport()).save(f, "PNG");

    the_canvas()->show_limits(TRUE);

    return r;
}

bool DiagramView::svg_save_in(const char * f, bool optimal, bool temporary)
{
    bool result = FALSE;
    the_canvas()->show_limits(FALSE);
    if (optimal) {
        int x0 = 0; //contentsX();
        int y0 = 0;//contentsY();

        //setContentsPos(0, 0);

        int maxx;
        int maxy;
        int minx;
        int miny;

        needed_width_height(maxx, maxy, minx, miny);
        maxx += 30;
        maxy += 10;

        // add a large margin to be sure to see all in one shot contrarilly
        // to the optimal_window_size whose must have the pretty size

        if ((viewport()->width() >= (maxx + 90)) && (viewport()->height() >= (maxy + 90))) {
            if (start_svg(f, maxx, maxy)) {
                result = TRUE;
                history_protected = TRUE;
                the_canvas()->update();
                canvas()->update();
                history_protected = FALSE;
                end_svg();
            }
        }
        else {

            int saved_w;
            int saved_h;

            saved_w = window()->width();
            saved_h = window()->height();

            window()->resize(maxx + 90, maxy + 90);

            if (start_svg(f, maxx, maxy)) {
                result = TRUE;
                history_protected = TRUE;
                the_canvas()->update();
                canvas()->update();
                history_protected = FALSE;
                end_svg();
            }

            if (! temporary) {



                window()->resize(saved_w, saved_h);

            }
        }

        if (! temporary)
        {
            //setContentsPos(x0, y0);
        }
    }
    else if (start_svg(f, viewport()->width(), viewport()->height())) {
        result = TRUE;
        history_protected = TRUE;
        the_canvas()->update();
        canvas()->update();
        history_protected = FALSE;
        end_svg();
    }
    the_canvas()->show_limits(TRUE);
    return result;
}

void DiagramView::copy_in_clipboard(bool optimal, bool temporary)
{
    if (the_canvas()->selection().count() != 0) {
        // unselect element and redraw them to remove selection mark
        history_protected = TRUE;
        unselect_all();
        the_canvas()->update();
        canvas()->update();
    }
    history_protected = TRUE;
    the_canvas()->show_limits(FALSE);

    if (optimal) {
        int x0 = 0;// contentsX();
        int y0 = 0; //contentsY();

        //setContentsPos(0, 0);

        int maxx;
        int maxy;
        int minx;
        int miny;

        needed_width_height(maxx, maxy, minx, miny);
        maxx += 30;
        maxy += 10;

        // add a large margin to be sure to see all in one shot contrarilly
        // to the optimal_window_size whose must have the pretty size

        if ((viewport()->width() >= (maxx + 90)) && (viewport()->height() >= (maxy + 90))) {
            QApplication::clipboard()
                    ->setPixmap(QPixmap::grabWidget(viewport(), 0, 0, maxx, maxy));
        }
        else {

            int saved_w;
            int saved_h;

            saved_w = window()->width();
            saved_h = window()->height();

            window()->resize(maxx + 90, maxy + 90);
            history_protected = TRUE;
            canvas()->update();
            QApplication::clipboard()
                    ->setPixmap(QPixmap::grabWidget(viewport(), 0, 0, maxx, maxy));

            if (! temporary) {



                window()->resize(saved_w, saved_h);

            }
        }

        if (! temporary)
        {
            //setContentsPos(x0, y0);
        }
    }
    else
        QApplication::clipboard()->setPixmap(QPixmap::grabWidget(viewport()));

    the_canvas()->show_limits(TRUE);
}

// not used out of windows, but must be defined because
// this is a 'slot'
void DiagramView::restore_window_size()
{



}

void DiagramView::save_picture(bool optimal, bool svg)
{
    QString filename =
            QFileDialog::getSaveFileName(this,
                                          (svg) ? QObject::tr("SVG file (*.svg)") : QObject::tr("PNG file (*.png)"),
                                         last_used_directory());

    if (!filename.isNull()) {
        set_last_used_directory(filename);

        if (svg) {
            if (filename.right(4).toLower() != ".svg")
                filename += ".svg";

            svg_save_in(filename.toLatin1().constData(), optimal, FALSE);
        }
        else {
            if (filename.right(4).toLower() != ".png")
                filename += ".png";

            save_in(filename.toLatin1().constData(), optimal, FALSE);
        }
    }
}

#ifndef QT_NO_PRINTER
void DiagramView::print(QPrinter & printer, int div)
{
    if (the_canvas()->selection().count() != 0)
        unselect_all();
    double old_zoom = ((UmlCanvas *) canvas())->zoom();

    if (old_zoom < 1)
        set_zoom(1);
    QPainter paint(&printer);
    //Q3PaintDeviceMetrics m(paint.device());
    int devw = printer.width();
    int devh = printer.height();
    double w = viewport()->width();
    double h = viewport()->height();
    double zoom = devh / h;

    if (devw / w < zoom)
        zoom = devw / w;

    zoom *= 0.98 * div;
    w /= div;
    h /= div;
    paint.scale(zoom, zoom);
    ((UmlCanvas *) canvas())->show_limits(FALSE);

    int i = 0;

    for (;;) {
        int j = 0;

        for (;;) {
            //drawContents(&paint, (int)(i * w), (int)(j * h), (int) w, (int) h);
            this->render(&paint, QRectF(i*w,j*h, w, h));

            if (++j == div)
                break;

            printer.newPage();
            paint.translate(0, -h);
        }

        if (++i == div)
            break;

        printer.newPage();
        paint.translate(-w, h * (div - 1));
    }
    ((UmlCanvas *) canvas())->show_limits(TRUE);

    if (old_zoom < 1)
        set_zoom(old_zoom);
}
#endif

void DiagramView::renumber(int ident)
{
    id = ident;
}

void DiagramView::save_session(QTextStream & st)
{
    st << (int)(((UmlCanvas *) canvas())->zoom() * 100)
       << " " << (int) window()->browser_diagram()->get_format() // useless
       << " " << verticalScrollBar()->value()
       << " " << horizontalScrollBar()->value() << '\n';
}

void DiagramView::read_session(char *& st)
{
    // zoom managed by DiagramWindow
    canvas()->update();
    (void) read_unsigned(st); // set_format((int) read_unsigned(st));
    {
        extern QApplication * theApp;
        theApp->processEvents(/*500*/);
    }
    verticalScrollBar()->setValue(read_unsigned(st));
    horizontalScrollBar()->setValue(read_unsigned(st));
    canvas()->update();
    {
        extern QApplication * theApp;
        theApp->processEvents(/*500*/);
    }
}

//history
//
// A new history element is add at the beginning of an action undoable
// A history element is not added if it is equel to the current one
// History may be empty or may heve onlt one element, in these cases
// undo & redo are not available
// history_index indicate the current state, or ~0 if the stack is empty

// save after the current state

void DiagramView::history_save(bool on_undo)
{
    if (history_frozen)
        return;

    // get current state
    QByteArray ba;
    QBuffer b(&ba);

    b.open(QIODevice::WriteOnly);

    /*
    double z = the_canvas()->zoom();

    b.writeBlock((char *) &z, sizeof(z));
    */
    DiagramItemList items(canvas()->items());

    foreach (DiagramItem * di, items) {
        di->history_save(b);
    }

    b.close();

    // update history if something changed
    if (history.isEmpty()) {
        history.append(ba);
        history_index = 0;
    }
    else {
        const QByteArray &current = history.at(history_index);

        if (! on_undo) {
            // remove redo
            while (history.last() != current)
                history.removeLast();
        }

        if (ba != current) {
            history.append(ba);

            // limit history depth to 20
            if (history_index == 19)
                history.removeFirst();
            else
                history_index += 1;
        }
    }
}

// load the state indicated by history_index
void DiagramView::history_load()
{
    history_protected = TRUE;

    // unselect and hide all
    unselect_all();
    DiagramItemList items(canvas()->items());
    foreach (DiagramItem *di, items) {
        di->history_hide();
        di->post_history_hide();
    }

    // load history
    QByteArray &ba = history[history_index];
    QBuffer b(&ba); // [lgfreitas] now qbuffer receives a pointer to a bytearray

    b.open(QIODevice::ReadOnly);

    while (!b.atEnd())
        load_item(b)->history_load(b);

    b.close();
    canvas()->update();
    history_protected = FALSE;
}

// clear history if not undoable
void DiagramView::update_history()
{
    if (!history_protected && !history_frozen) {
        history.clear();
        history_index = ~0u;
    }
}

// want to be the state preceding the state indicated by history_index
void DiagramView::undo()
{
    history_index -= 1;
    history_load();
}
// want to be the state following the state indicated by history_index
void DiagramView::redo()
{
    history_index += 1;
    history_load();
}

bool DiagramView::available_undo()
{
    if (history_index == (history.count() - 1))
        history_save(TRUE);

    return (history_index != 0);
}

bool DiagramView::available_redo()
{
    return (history_index != (history.count() - 1));
}
