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

#include "TreeItem.h"
//Added by qt3to4:
#include <Q3CString>
#include <Q3PtrCollection>
#include <Q3PtrList>

#ifndef REVERSE
class BrowserView;
#endif

class Q3CString;
class QDataStream;
class Class;

class BrowserNode : public TreeItem {
  public:
    BrowserNode(BrowserNode * parent, const char * n);
    virtual ~BrowserNode() {};	// to avoid compiler warning
  
    virtual bool isa_package() const;
    
#ifndef REVERSE
    BrowserNode(BrowserView * parent, const char * n);
    
    void select_in_browser();
    
    virtual void activated();
    virtual void selected();
    virtual void menu() = 0;
    virtual void refer(const QString & name) = 0;
    virtual void backup(QDataStream  & dt) const = 0;
    virtual QString get_path() const = 0;
#endif
};


#ifndef REVERSE

// a sortable list of BrowserNode

#include <q3ptrlist.h>

class BrowserNodeList : public Q3PtrList<BrowserNode> {
  public:
    void search(BrowserNode * bn, int k, const QString & s, bool cs);
    virtual int compareItems(Q3PtrCollection::Item item1, Q3PtrCollection::Item item2);
};

#endif

#endif
