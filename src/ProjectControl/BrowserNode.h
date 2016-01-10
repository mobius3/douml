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

#ifndef BROWSERNODE_H
#define BROWSERNODE_H
#include <QKeyEvent>
#include <QPixmap>
#include <QTreeWidgetItem>


class QDir;
class QKeyEvent;
class BrowserView;

class BrowserNode : public QTreeWidgetItem
{
public:
    BrowserNode(BrowserView * parent, QString fn);
    BrowserNode(BrowserNode * parent, QString fn);
    virtual ~BrowserNode() {};	// to avoid compiler warning

    virtual const QPixmap * pixmap(int) const;

    void menu();
    QString get_path() const {
        return path;
    }
    bool load(QDir & dir);
    void key_event(QKeyEvent *);
    BrowserNode* firstChild() const {return (BrowserNode*)this->child(0);}

    BrowserNode *nextSibling();
    void repaint(){ /*doldurulacak*/}
    void moveItem(BrowserNode *after);
    QVariant data(int column, int role) const;
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



class BrowserNodeList : public QList<BrowserNode *>
{
public:
    void search(BrowserNode * bn, const QString & s, bool cs);
    static int compareItems(void *item1, void *item2);
};

#endif
