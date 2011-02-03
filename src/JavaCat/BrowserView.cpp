// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
//
// This file is part of the BOUML Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// e-mail : bouml@free.fr
// home   : http://bouml.free.fr
//
// *************************************************************************

#include "BrowserView.h"
#include "BrowserNode.h"

BrowserView * BrowserView::the;

BrowserView::BrowserView(QWidget * parent) : Q3ListView(parent) {
  the = this;
  
  setSorting(-1);		// manual sorting
  addColumn("browser          ");
  setTreeStepSize(18);
  
  connect(this, SIGNAL(selectionChanged(Q3ListViewItem*)),
	  this, SLOT(selected(Q3ListViewItem*)));
  
  connect(this, SIGNAL(rightButtonPressed(Q3ListViewItem *, const QPoint &, int)),
	  this, SLOT(rightPressed(Q3ListViewItem *)));

}

void BrowserView::select(Q3ListViewItem * b)
{
  the->ensureItemVisible(b);
  the->setSelected(b, TRUE);
}

void BrowserView::selected(Q3ListViewItem * b)
{
  ((BrowserNode *) b)->activated();
}

void BrowserView::rightPressed(Q3ListViewItem * item) {
  if (item != 0)
    ((BrowserNode *) item)->menu();
}

void BrowserView::refer(const QString & href) {
  BrowserNode * bn = (BrowserNode *) selectedItem();
  
  if (bn != 0)
    bn->refer(href);
}
