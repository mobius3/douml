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

BrowserView * BrowserView::the;

BrowserView::BrowserView(QWidget * parent) : QTreeWidget(parent)
{
    the = this;
    //setSorting(-1);		// manual sorting
   // addColumn("browser          ");
    headerItem()->setText(0, QObject::tr("browser          "));
    //setTreeStepSize(18);

    connect(this, SIGNAL(selectionChanged(Q3ListViewItem *)),
            this, SLOT(selected(Q3ListViewItem *)));

    connect(this, SIGNAL(rightButtonPressed(Q3ListViewItem *, const QPoint &, int)),
            this, SLOT(rightPressed(Q3ListViewItem *)));

}

void BrowserView::select(QTreeWidgetItem *b)
{
    //the->ensureItemVisible(b);
    the->scrollToItem(b);
    //the->setSelected(b, TRUE);
    the->select(b);
}

void BrowserView::selected(QTreeWidgetItem * b)
{
    ((BrowserNode *) b)->activated();
}

void BrowserView::rightPressed(QTreeWidgetItem * item)
{
    if (item != 0)
        ((BrowserNode *) item)->menu();
}

void BrowserView::refer(const QString & href)
{
    BrowserNode * bn = nullptr;// = (BrowserNode *) selectedItem();
    if (selectedItems().count())
        bn = (BrowserNode *)selectedItems().at(0);

    if (bn != 0)
        bn->refer(href);
}
