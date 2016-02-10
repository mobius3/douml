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

#ifndef SDMSGCANVAS_H
#define SDMSGCANVAS_H

#include "SdMsgBaseCanvas.h"
//Added by qt3to4:
#include <QTextStream>

#define MSG_HEIGHT 11

class SdMsgCanvas : public SdMsgBaseCanvas
{
    Q_OBJECT
protected:
    SdMsgSupport * start;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
public:
    SdMsgCanvas(UmlCanvas * canvas, SdMsgSupport * s,
                SdMsgSupport * d, UmlCode l, int v, int id);
    virtual ~SdMsgCanvas();

    virtual void delete_it() override;

    SdMsgSupport * get_start()  const {
        return start;
    };

    virtual void draw(QPainter & p);
    virtual void set_z(double) override;
    virtual void update_hpos() override;
    virtual void check_vpos(const QRect &) override;
    virtual double min_y() const override;
    virtual void change_duration(SdDurationCanvas * oldone,
                                 SdDurationCanvas * newone) override;
    virtual int overlap_dir(SdDurationCanvas *) const override;
    virtual void update() override;
    virtual void menu(const QPoint &) override;
    virtual void select_associated() override;
    virtual bool copyable() const override;

    virtual bool has_drawing_settings() const override;
    virtual void edit_drawing_settings(QList<DiagramItem *> &) override;
    virtual void clone_drawing_settings(const DiagramItem *src) override;

    virtual void apply_shortcut(const QString & s) override;
    void edit_drawing_settings();

    virtual void save(QTextStream &, bool ref, QString & warning) const override;
    static SdMsgCanvas * read(char *& , UmlCanvas *, char *);
};

#endif

