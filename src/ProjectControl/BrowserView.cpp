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





#include "BrowserView.h"
#include "BrowserNode.h"
//Added by qt3to4:
#include <QKeyEvent>

BrowserView * BrowserView::the;
QDir BrowserView::dir;

BrowserView::BrowserView(QWidget * parent) : Q3ListView(parent)
{
    the = this;

    setSorting(-1);		// manual sorting
    addColumn("browser          ");
    addColumn("Owner id");
    addColumn("Owner name");
    addColumn("Revision");
    addColumn("Modified by");
    setColumnWidthMode(0, Maximum);
    setColumnWidthMode(1, Maximum);
    setColumnWidthMode(2, Maximum);
    setColumnWidthMode(3, Maximum);
    setColumnWidthMode(4, Maximum);
    setColumnAlignment(1, ::Qt::AlignHCenter);
    setColumnAlignment(2, ::Qt::AlignHCenter);
    setColumnAlignment(3, ::Qt::AlignHCenter);
    setColumnAlignment(4, ::Qt::AlignHCenter);
    setTreeStepSize(18);

    connect(this, SIGNAL(rightButtonPressed(Q3ListViewItem *, const QPoint &, int)),
            this, SLOT(rightPressed(Q3ListViewItem *)));
}

BrowserView::~BrowserView()
{
}

void BrowserView::close()
{
    if (firstChild() != 0) {
        dir.rmdir("all.lock");
        clear();
    }
}

BrowserNode * BrowserView::get_project()
{
    return (BrowserNode *) the->firstChild();
}

void BrowserView::set_project(QDir di)
{
    dir = di;
    new BrowserNode(the, dir.dirName() + ".prj");
    setRootIsDecorated(TRUE/*FALSE*/);
}

void BrowserView::rightPressed(Q3ListViewItem * item)
{
    if (item != 0)
        ((BrowserNode *) item)->menu();
}

void BrowserView::keyPressEvent(QKeyEvent * e)
{
    switch (e->state()) {
    case ::Qt::ControlModifier:
    case ::Qt::AltModifier:
        switch (e->key()) {
        case ::Qt::Key_A:
        case ::Qt::Key_P:
        case ::Qt::Key_U: {
            Q3ListViewItem * t = selectedItem();

            if (t != 0) {
                ((BrowserNode *) t)->key_event(e);
                return;
            }
        }
        }

        break;

    default:
        break;
    }

    Q3ListView::keyPressEvent(e);
}

void BrowserView::select(Q3ListViewItem * b)
{
    the->ensureItemVisible(b);
    the->setSelected(b, TRUE);
}
