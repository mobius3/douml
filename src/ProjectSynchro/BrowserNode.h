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

#include <q3listview.h>
#include <q3dict.h>
//Added by qt3to4:
#include <QKeyEvent>
#include <QPixmap>

class QDir;
class QKeyEvent;
class BrowserView;

enum State {
    UpToDate, Young, Old, Deleted, Unknown
};

class BrowserNode : public Q3ListViewItem
{
public:
    BrowserNode(BrowserView * parent, QString fn);
    BrowserNode(BrowserNode * parent, QString fn, BrowserView * v);
    virtual ~BrowserNode() {};	// to avoid compiler warning

    virtual const QPixmap * pixmap(int) const;

    bool load(QDir & dir);
    QString file_name() const {
        return filename;
    }

    void set_state(State);
    State get_state() const {
        return state;
    }

    int get_rev() const;

    bool solve();	// solve state and return TRUE if Young
    static void synchronize(QDir & todir, Q3Dict<BrowserNode> & nodes);

private:

    void memo(Q3Dict<void> & useful);

    QString filename;
    QString modifier_name;
    int modifier_id;
    BrowserView * view;
    State state;
    QStringList diagrams;
    QStringList classes;

    static Q3Dict<BrowserNode> Youngs;
};

#endif
