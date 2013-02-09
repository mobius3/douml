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

#ifndef SEQDIAGRAMVIEW_H
#define SEQDIAGRAMVIEW_H

#include "DiagramView.h"
//Added by qt3to4:
#include <QTextStream>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDropEvent>
#include <QDragEnterEvent>

class SeqDiagramWindow;
class DiagramItem;
class UmlCanvas;
class ToolCom;

class SeqDiagramView : public DiagramView
{
public:
    SeqDiagramView(QWidget * parent, UmlCanvas * canvas, int id);

    virtual void menu(const QPoint &);
    virtual void read(char *, char * k);
    virtual void save(QTextStream & st, QString & warning, bool copy) const;

    void send(ToolCom * com);

private:
    SeqDiagramWindow * window() {
        return (SeqDiagramWindow *) parent();
    }
    void toFlat();
    void toOverlapping();

protected:
    virtual void contentsMousePressEvent(QMouseEvent *);
    virtual void contentsMouseMoveEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent * e);
    virtual void dragEnterEvent(QDragEnterEvent *);
    virtual void dropEvent(QDropEvent *);
};

#endif
