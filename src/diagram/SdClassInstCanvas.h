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

#ifndef SDCLASSINSTCANVAS_H
#define SDCLASSINSTCANVAS_H





#include <qobject.h>
//Added by qt3to4:
#include <QTextStream>

#include "SdObjCanvas.h"
#include "ClassInstCanvas.h"

class BrowserNode;
class ToolCom;

class SdClassInstCanvas : public QObject, public SdObjCanvas, public ClassInstCanvas
{
    Q_OBJECT

protected:
    QString iname;	// useless if browser_node is a class instance rather than a class

protected:
    ClassDrawingMode drawing_mode;
    ClassDrawingMode used_drawing_mode;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
public:
    SdClassInstCanvas(BrowserNode * t, UmlCanvas * canvas, int x, int id);
    virtual ~SdClassInstCanvas();

    virtual void delete_it() override;

    virtual void draw(QPainter & p);

    void compute_size();
    virtual UmlCode typeUmlCode() const override;	// -> class or classinstance
    virtual QString get_name() const override;	// all cases
    virtual void set_name(const QString & s) override;	// out of model case
    virtual BrowserNode * get_type() const override;	// return class, all cases
    virtual void set_type(BrowserNode * t) override;	// out of model case
    virtual BrowserNodeList & get_types(BrowserNodeList &) const override;
    virtual BrowserNode * container(UmlCode) const override;
    virtual BrowserClass * get_class() const override;
    virtual void delete_available(BooL & in_model, BooL & out_model) const override;
    virtual void remove(bool from_model) override;
    virtual void open() override;
    virtual void menu(const QPoint &) override;
    virtual void history_load(QBuffer &) override;
    virtual void history_hide() override;

    virtual bool has_drawing_settings() const override;
    virtual void edit_drawing_settings(QList<DiagramItem *> &) override;
    virtual void clone_drawing_settings(const DiagramItem *src) override;
    void edit_drawing_settings();
    virtual bool get_show_stereotype_properties() const override;

    virtual void apply_shortcut(const QString & s) override;

    virtual void save(QTextStream &, bool ref, QString & warning) const override;
    static SdClassInstCanvas * read(char *& , UmlCanvas * canvas, char *);

    static void send(ToolCom * com, QList<QGraphicsItem*> & all);

private slots:
    void modified();	// canvas must be updated
    void deleted();	// the class is deleted
};

#endif
