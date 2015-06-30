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

#include "BrowserNode.h"
#include "UmlClass.h"
#include "Class.h"
#include "aRelationKind.h"
#include "aDirection.h"
#include "aVisibility.h"
#include "anItemKind.h"
#include "BrowserView.h"
//Added by qt3to4:


BrowserNode::BrowserNode(BrowserView * parent, const char * n)
    : TreeItem(parent)
{
    setText(0,n);
}

BrowserNode::BrowserNode(BrowserNode * parent, const char * n)
    : TreeItem(parent)
{
    // move it at end
    setText(0,n);
    BrowserNode * child = parent->firstChild();

    while (child->nextSibling())
        child = child->nextSibling();

    if (child != this)
    {
        //moveItem(child);
        parent->takeChild(parent->indexOfChild(this));
        parent->insertChild(parent->indexOfChild(child)+1, this);

    }
}

void BrowserNode::activated()
{
}

void BrowserNode::selected()
{
}

//

void BrowserNodeList::search(BrowserNode * bn, int k,
                             const QString & s, bool cs)
{
    BrowserNode * child;

    for (child = bn->firstChild(); child != 0; child = child->nextSibling()) {
        if ((k == aPackage)
            ? (((BrowserNode *) child)->isa_package() &&
               (child->text(0).indexOf(s, 0, (Qt::CaseSensitivity)cs) != -1))
            : (!((BrowserNode *) child)->isa_package() &&
               ((k == aClass)
                ? (child->text(0).indexOf(s, 0, (Qt::CaseSensitivity)cs) != -1)
                : (WrapperStr(((Class *) child)->get_description()).operator QString().indexOf(s, 0,(Qt::CaseSensitivity) cs) != -1))))
            append((BrowserNode *) child);

        search((BrowserNode *) child, k, s, cs);
    }
}

bool BrowserNodeList::lessThan(BrowserNode *a, BrowserNode *b)
{
    return a->text(0) < b->text(0);
}

void BrowserNodeList::sort()
{
    qSort(begin(), end(), lessThan);
}
BrowserNode *BrowserNode::nextSibling()
{
    for(int i = 0; i < parent()->childCount(); i++)
    {
        if(parent()->child(i) == this)
        {
            if((i+1)<parent()->childCount())
                return (BrowserNode *)parent()->child(i+1);
            break;
        }
    }
    return NULL;
}
/*void BrowserNode::paintCell(QPainter * p, const QPalette & cg, int column,
                            int width, int alignment)
{
    BrowserNode::data used instead
    const QColor & bg = p->background().color();
    QBrush backBrush = p->background();
    if (is_marked) {
        p->setBackgroundMode(::Qt::OpaqueMode);
        backBrush.setColor(UmlRedColor);
        p->setBackground(backBrush);
    }

    p->setFont((is_writable()) ? BoldFont : NormalFont);
    QTreeWidgetItem::paintCell(p, cg, column, width, alignment);
    if (is_marked) {
        p->setBackgroundMode(::Qt::TransparentMode);
        backBrush.setColor(bg);
        p->setBackground(backBrush);
    }


}*/
