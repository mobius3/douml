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





#include <qcursor.h>
#include <qpainter.h>
#include <QTextStream>
#include "SdContinuationCanvas.h"
#include "ContinuationDialog.h"
#include "UmlGlobal.h"
#include "UmlCanvas.h"
#include "BrowserDiagram.h"
#include "Settings.h"
#include "SettingsDialog.h"
#include "myio.h"
#include "ui/menufactory.h"
#include "DialogUtil.h"
#include "ToolCom.h"
#include "strutil.h"
#include "translate.h"

SdContinuationCanvas::SdContinuationCanvas(UmlCanvas * canvas, int x, int y, int id)
    : DiagramCanvas(0, canvas, x, y, CONTINUATION_CANVAS_MIN_SIZE,
                    CONTINUATION_CANVAS_MIN_SIZE, id)
{
    browser_node = canvas->browser_diagram();
    itscolor = UmlDefaultColor;
    check_size();
    connect(DrawingSettings::instance(), SIGNAL(changed()), this, SLOT(modified()));
}

SdContinuationCanvas::~SdContinuationCanvas()
{
}

void SdContinuationCanvas::delete_it()
{
    disconnect(DrawingSettings::instance(), SIGNAL(changed()), this, SLOT(modified()));
    DiagramCanvas::delete_it();
}


void SdContinuationCanvas::draw(QPainter & p)
{
    if (! isVisible()) return;

    p.setRenderHint(QPainter::Antialiasing, true);
    QRect r = rect();
    QColor bckgrnd = p.background().color();
    QBrush brsh = p.brush();
    QBrush backBrush = p.background();

    p.setBackgroundMode((used_color == UmlTransparent) ? ::Qt::TransparentMode : ::Qt::OpaqueMode);

    QColor co = color(used_color);
    FILE * fp = svg();

    if (fp != 0)
        fputs("<g>\n", fp);

    backBrush.setColor(co);
    p.setBackground(backBrush);

    if (used_color != UmlTransparent)
        p.setBrush(co);

    if (fp != 0)
        fprintf(fp, "\t<rect fill=\"%s\" stroke=\"black\" stroke-width=\"1\" stroke-opacity=\"1\""
                " x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" rx=\"10\" />\n",
                svg_color(used_color),
                r.x(), r.y(), r.width() - 1, r.height() - 1);

    p.drawRoundRect(r, 50, 50);

    p.setFont(the_canvas()->get_font(UmlNormalFont));
    p.drawText(r, ::Qt::AlignCenter, name);

    if (fp != 0) {
        draw_text(r, ::Qt::AlignCenter, name,
                  p.font(), fp);
        fputs("</g>\n", fp);
    }

    backBrush.setColor(bckgrnd);
    p.setBackground(backBrush);
    p.setBrush(brsh);

    if (selected())
        show_mark(p, r);
}

void SdContinuationCanvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    draw(*painter);
}

UmlCode SdContinuationCanvas::typeUmlCode() const
{
    return UmlContinuation;
}

void SdContinuationCanvas::delete_available(BooL &, BooL & out_model) const
{
    out_model |= TRUE;
}

bool SdContinuationCanvas::alignable() const
{
    return TRUE;
}

bool SdContinuationCanvas::copyable() const
{
    return selected();
}

void SdContinuationCanvas::open()
{
    ContinuationDialog d(name);

    d.exec();
    modified();
}

void SdContinuationCanvas::check_size()
{
    QFontMetrics fm(the_canvas()->get_font(UmlNormalFont));

    min_height = fm.height() * 2;
    min_width = fm.width((name.isEmpty()) ? QString("X") : name) + min_height;

    int min = (int)(CONTINUATION_CANVAS_MIN_SIZE * the_canvas()->zoom());

    if (min_width < min)
        min_width  = min;

    if (min_height < min)
        min_height  = min;

    // warning : do NOT check if (width() < w)
    // because te resize must be done to set data on scale change
    DiagramCanvas::resize((width() > min_width) ? width() : min_width,
                          (height() > min_height) ? height() : min_height);

    used_color = (itscolor == UmlDefaultColor)
                 ?  the_canvas()->browser_diagram()->get_color(UmlContinuation)
                 : itscolor;
}

void SdContinuationCanvas::change_scale()
{
    double scale = the_canvas()->zoom();

    QGraphicsRectItem::setVisible(FALSE);
    setRect(0,0,(int)(width_scale100 * scale), (int)(height_scale100 * scale));
    check_size();
    recenter();
    QGraphicsRectItem::setVisible(TRUE);
}

void SdContinuationCanvas::modified()
{
    // force son reaffichage
    hide();
    check_size();
    show();
    canvas()->update();
    package_modified();
}

void SdContinuationCanvas::menu(const QPoint &)
{
    QMenu m(0);

    MenuFactory::createTitle(m, tr("Continuation"));
    m.addSeparator();
    MenuFactory::addItem(m, tr("Upper"), 0);
    MenuFactory::addItem(m, tr("Lower"), 1);
    MenuFactory::addItem(m, tr("Go up"), 6);
    MenuFactory::addItem(m, tr("Go down"), 7);
    m.addSeparator();
    MenuFactory::addItem(m, tr("Edit"), 2);
    m.addSeparator();
    MenuFactory::addItem(m, tr("Edit drawing settings"), 3);

    if (linked()) {
        m.addSeparator();
        MenuFactory::addItem(m, tr("Select linked items"), 4);
    }

    m.addSeparator();
    MenuFactory::addItem(m, tr("Remove from diagram"), 5);

    QAction* retAction = m.exec(QCursor::pos());
    if(retAction)
    {
    int index = retAction->data().toInt();

    switch (index) {
    case 0:
        upper();
        modified();	// call package_modified()
        return;

    case 1:
        lower();
        modified();	// call package_modified()
        return;

    case 6:
        z_up();
        modified();	// call package_modified()
        return;

    case 7:
        z_down();
        modified();	// call package_modified()
        return;

    case 2:
        open();
        // modified then package_modified already called
        return;

    case 3:
        edit_drawing_settings();
        return;

    case 4:
        the_canvas()->unselect_all();
        select_associated();
        return;

    case 5:
        delete_it();
        break;

    default:
        return;
    }
    }

    package_modified();
}

void SdContinuationCanvas::apply_shortcut(const QString & s)
{
    if (s == "Upper")
        upper();
    else if (s == "Lower")
        lower();
    else if (s == "Go up")
        z_up();
    else if (s == "Go down")
        z_down();
    else if (s == "Edit drawing settings") {
        edit_drawing_settings();
        return;
    }
    else if (s == "Edit") {
        open();  // call modified then package_modified
        return;
    }
    else
        return;

    modified();
}

void SdContinuationCanvas::edit_drawing_settings()
{
    for (;;) {
        ColorSpecVector co(1);

        co[0].set(tr("continuation color"), &itscolor);

        SettingsDialog dialog(0, &co, FALSE);

        dialog.raise();

        if (dialog.exec() == QDialog::Accepted)
            modified();

        if (!dialog.redo())
            break;
    }
}

bool SdContinuationCanvas::has_drawing_settings() const
{
    return TRUE;
}

void SdContinuationCanvas::edit_drawing_settings(QList<DiagramItem *> & l)
{
    for (;;) {
        ColorSpecVector co(1);
        UmlColor itscolor;

        co[0].set(tr("continuation color"), &itscolor);

        SettingsDialog dialog(0, &co, FALSE, TRUE);

        dialog.raise();

        if ((dialog.exec() == QDialog::Accepted) && !co[0].name.isEmpty()) {
            foreach (DiagramItem *item, l) {
                SdContinuationCanvas *canvas = (SdContinuationCanvas *)item;
                canvas->itscolor = itscolor;
                canvas->modified();
            }
        }

        if (!dialog.redo())
            break;
    }
}

void SdContinuationCanvas::clone_drawing_settings(const DiagramItem *src)
{
    const SdContinuationCanvas * x = (const SdContinuationCanvas *) src;
    itscolor = x->itscolor;
    modified();
}

QString SdContinuationCanvas::may_start(UmlCode & l) const
{
    return (l == UmlAnchor) ? QString() : tr("illegal");
}

QString SdContinuationCanvas::may_connect(UmlCode & l, const DiagramItem * dest) const
{
    return (l == UmlAnchor) ? dest->may_start(l) : tr("illegal");
}

aCorner SdContinuationCanvas::on_resize_point(const QPoint & p)
{
    return ::on_resize_point(p, rect());
}

void SdContinuationCanvas::resize(aCorner c, int dx, int dy, QPoint & o)
{
    DiagramCanvas::resize(c, dx, dy, o, min_width, min_height);
}

void SdContinuationCanvas::resize(const QSize & sz, bool w, bool h)
{
    DiagramCanvas::resize(sz, w, h, min_width, min_height);
}

void SdContinuationCanvas::save(QTextStream & st, bool ref, QString &) const
{
    if (ref) {
        st << "continuation_ref " << get_ident();
    }
    else {
        nl_indent(st);

        st << "continuation " << get_ident() << " ";
        save_string(name.toLatin1().constData(), st);
        nl_indent(st);

        if (itscolor != UmlDefaultColor)
            st << "  color " << stringify(itscolor);

        save_xyzwh(st, this, "  xyzwh");
    }
}

SdContinuationCanvas * SdContinuationCanvas::read(char *& st, UmlCanvas * canvas, char * k)
{
    if (!strcmp(k, "continuation_ref"))
        return (SdContinuationCanvas *) dict_get(read_id(st), "continuation", canvas);
    else if (!strcmp(k, "continuation")) {
        int id = read_id(st);
        SdContinuationCanvas * result = new SdContinuationCanvas(canvas, 0, 0, id);

        result->name = read_string(st);

        k = read_keyword(st);
        read_color(st, "color", result->itscolor, k);

        if (strcmp(k, "xyzwh"))
            wrong_keyword(k, "xyzwh");

        read_xyzwh(st, result);
        result->check_size();
        result->width_scale100 = result->width();
        result->height_scale100 = result->height();
        result->set_center100();
        result->show();
        return result;
    }
    else
        return 0;
}

void SdContinuationCanvas::history_save(QBuffer & b) const
{
    DiagramCanvas::history_save(b);
    ::save(min_width, b);
    ::save(min_height, b);
    ::save(width_scale100, b);
    ::save(height_scale100, b);
    ::save(width(), b);
    ::save(height(), b);
}

void SdContinuationCanvas::history_load(QBuffer & b)
{
    DiagramCanvas::history_load(b);
    ::load(min_width, b);
    ::load(min_height, b);
    ::load(width_scale100, b);
    ::load(height_scale100, b);

    int w, h;

    ::load(w, b);
    ::load(h, b);
    QGraphicsRectItem::setRect(rect().x(), rect().y(), w, h);

    connect(DrawingSettings::instance(), SIGNAL(changed()), this, SLOT(modified()));
}

void SdContinuationCanvas::history_hide()
{
    QGraphicsItem::setVisible(FALSE);
    disconnect(DrawingSettings::instance(), SIGNAL(changed()), this, SLOT(modified()));
}

// for plug-out

void SdContinuationCanvas::send(ToolCom * com, QList<QGraphicsItem*> & all)
{
    if (com->api_format() < 41)
        return;

    QList<QGraphicsItem*>::Iterator cit;

    for (cit = all.begin(); (cit != all.end()); ++cit) {
        DiagramItem * di = QCanvasItemToDiagramItem(*cit);

        if ((di != 0) && (*cit)->isVisible() && (di->typeUmlCode() == UmlContinuation)) {
            WrapperStr s = fromUnicode(((SdContinuationCanvas *) di)->name);

            com->write_bool(TRUE);	// one more
            com->write_string((const char *) s);
            com->write(((SdContinuationCanvas *) di)->rect());
        }
    }

    com->write_bool(FALSE);	// done
}
