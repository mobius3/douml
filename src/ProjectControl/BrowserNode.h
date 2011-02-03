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

#ifndef BROWSERNODE_H
#define BROWSERNODE_H

#include <q3listview.h>
//Added by qt3to4:
#include <QKeyEvent>
#include <Q3PtrCollection>
#include <QPixmap>
//Added by qt3to4:
#include <Q3PtrList>

class QDir;
class QKeyEvent;
class BrowserView;

class BrowserNode : public Q3ListViewItem {
  public:
    BrowserNode(BrowserView * parent, QString fn);
    BrowserNode(BrowserNode * parent, QString fn);
    virtual ~BrowserNode() {};	// to avoid compiler warning
    
    virtual const QPixmap * pixmap(int) const;
    
    void menu();
    QString get_path() const { return path; }
    bool load(QDir & dir);
    void key_event(QKeyEvent *);
    
  private:
    void assign(int);
    void assign_mine(int);
    void assign_unassigned(int);
    void assign_all(int);

  private:
    QString filename;
    QString path;
    QString modifier_name;
    int modifier_id;
    int owner;
    int format;
    int offset;
    BooL ro;
};

// a sortable list of BrowserNode

#include <q3ptrlist.h>

class BrowserNodeList : public Q3PtrList<BrowserNode> {
  public:
    void search(BrowserNode * bn, const QString & s, bool cs);
    virtual int compareItems(Q3PtrCollection::Item item1, Q3PtrCollection::Item item2);
};

#endif
