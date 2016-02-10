//Added by qt3to4:

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

#ifndef TREEITEM_H
#define TREEITEM_H

#ifndef REVERSE

#include <QTreeWidget>
#include <qstring.h>

#define TreeItem QTreeWidgetItem

#else

#include <QList>
#include <QString>
#include <QVariant>

class TreeItem
{
private:
    TreeItem * its_parent;
    QList<TreeItem *> its_children;
    QString its_name;	// java_classes share it in case of a java classes

public:
    TreeItem(TreeItem * parent, const char * n);

    QString text(int) {
        return its_name;
    };
    void setText(int, QString s) {
        its_name = s;
    };
    void setText(QString s) {
        its_name = s;
    };
    TreeItem * parent() {
        return its_parent;
    };

    const QList<TreeItem *> &children() const {
        return its_children;
    }
    
    virtual QVariant data(int column, int role) const = 0;
};

#endif

#endif
