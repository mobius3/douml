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

#ifndef CODSELFLINKCANVAS_H
#define CODSELFLINKCANVAS_H

#include "DiagramCanvas.h"
#include "MultipleDependency.h"
#include "CodMsgSupport.h"
//Added by qt3to4:
#include <QTextStream>

class CodObjCanvas;
class LabelCanvas;
class ColMsg;

#define SELF_LINK_RADIUS 16

class CodSelfLinkCanvas : public QObject, public DiagramCanvas, public CodMsgSupport,
    public MultipleDependency<BasicData>
{
    Q_OBJECT

protected:
    int delta_x;
    int delta_y;
    double angle;
    CodObjCanvas * obj;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
public:
    CodSelfLinkCanvas(UmlCanvas * canvas, CodObjCanvas * o,
                      const QPoint & p, int id);
    virtual ~CodSelfLinkCanvas();

    void update_pos();
    void compute_pos(QPoint p);
    void update_label_pos();
    virtual void update_msgs() override;
    virtual void get_from_to(CodObjCanvas *& from, CodObjCanvas *& to,
                             bool forward) override;
    virtual bool copyable() const override;

    virtual void delete_it() override;
    virtual void remove_it(ColMsg * msg) override;

    virtual void draw(QPainter & p);
    virtual void moveBy(double dx, double dy) override;

    virtual UmlCode typeUmlCode() const override;
    virtual void delete_available(BooL & in_model, BooL & out_model) const override;
    virtual void open() override;
    virtual void menu(const QPoint &) override;
    virtual QString may_start(UmlCode &) const override;
    virtual QString may_connect(UmlCode & l, const DiagramItem * dest) const override;
    virtual bool represents(BrowserNode *) override;
    virtual void save(QTextStream & st, bool ref, QString & warning) const override;
    static CodSelfLinkCanvas * read(char *& st, UmlCanvas * canvas, char *& k);
    virtual void history_save(QBuffer &) const override;
    virtual void history_load(QBuffer &) override;
    virtual void history_hide() override;

protected slots:
    void modified();
};

#endif
