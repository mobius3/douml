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





#include <qpainter.h>
//#include <q3popupmenu.h>
//Added by qt3to4:
#include <QTextStream>

#include "TemplateCanvas.h"
#include "BrowserClass.h"
#include "ClassData.h"
#include "UmlCanvas.h"
#include "myio.h"
#include "translate.h"

TemplateCanvas::TemplateCanvas(DiagramCanvas * c)
    : DiagramCanvas(c->the_canvas(), -1), cl(c)
{
    update();
}

TemplateCanvas::~TemplateCanvas()
{
}

void TemplateCanvas::update()
{
    setZValue(cl->zValue() + 0.5);

    const ClassData * d = (ClassData *) cl->get_bn()->get_data();
    int i, n;

    text = d->get_formalparam_name(0);

    for (i = 1, n = d->get_n_formalparams(); i != n; i += 1)
        text += QString(", ") + d->get_formalparam_name(i);

    QRectF r = cl->sceneBoundingRect();
    QFontMetrics fm(the_canvas()->get_font(UmlNormalFont));
    int eight = (int)(8 * the_canvas()->zoom());
    int wi = fm.width(text) + eight;

    if (wi <= (r.width() / 2))
        wi = r.width() / 2;

    resize(wi, fm.height() + eight);


    //do not use setPos here. let moveby hangle other stuff
    QPointF targetPos;
    targetPos.setX((double)(cl->x() + (cl->sceneRect().width()) / 3));
    targetPos.setY((double)(cl->y() - height() / 2));
    moveBy(targetPos.x()-x() + 100000,
           targetPos.y()- y());

    //moveBy(r.right() -  r.width() / 3 + 100000, r.top() - height() / 2);
}

void TemplateCanvas::change_scale()
{
    // does nothing, update is called by its class
}

void TemplateCanvas::moveBy(double dx, double dy)
{
    if (dx < 80000) {
        // hand moving
        if (!the_canvas()->do_zoom() && !cl->selected())
            // will move the template
            cl->moveBy(dx, dy);
    }
    else {
        // from update_pos
        QGraphicsRectItem::moveBy(dx - 100000, dy);

        if (!the_canvas()->do_zoom() && !cl->selected())
            set_center100();
    }
}

void TemplateCanvas::upper()
{
    cl->upper(); // will update the template z
}

void TemplateCanvas::lower()
{
    cl->lower(); // will update the template z
}

void TemplateCanvas::z_up()
{
    cl->z_up(); // will update the template z
}

void TemplateCanvas::z_down()
{
    cl->z_down(); // will update the template z
}

bool TemplateCanvas::primaryItem() const
{
    return FALSE;
}

void TemplateCanvas::set_z(double)
{
    // does nothing, cl z modification call update
}

void TemplateCanvas::draw(QPainter & p)
{
    if (! visible()) return;

    p.setRenderHint(QPainter::Antialiasing, true);
    p.setBackgroundMode(::Qt::OpaqueMode);

    QRect r = rect();

    p.fillRect(r, ::Qt::white);
    p.setPen(::Qt::DotLine);
    p.drawRect(r);
    p.setPen(::Qt::SolidLine);

    p.setFont(the_canvas()->get_font(UmlNormalFont));
    p.drawText(r, ::Qt::AlignCenter, text);

    FILE * fp = svg();

    if (fp != 0) {
        fputs("<g>\n", fp);
        fprintf(fp, "\t<rect fill=\"white\" stroke-dasharray=\"4,4\" stroke=\"black\" stroke-width=\"1\" stroke-opacity=\"1\""
                " x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" />\n",
                r.x(), r.y(), r.width() - 1, r.height() - 1);
        draw_text(r, ::Qt::AlignCenter, text,
                  p.font(), fp);
        fputs("</g>\n", fp);
    }

}

void TemplateCanvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    draw(*painter);
}

UmlCode TemplateCanvas::typeUmlCode() const
{
    return UmlTemplate;
}

void TemplateCanvas::open()
{
    cl->open();
}

void TemplateCanvas::menu(const QPoint & p)
{
    cl->menu(p);
}

QString TemplateCanvas::may_start(UmlCode &) const
{
    return  QObject::tr("illegal");
}

QString TemplateCanvas::may_connect(UmlCode &, const DiagramItem *) const
{
    return  QObject::tr("illegal");
}

void TemplateCanvas::save(QTextStream &, bool, QString &) const
{
    // does nothing
}

