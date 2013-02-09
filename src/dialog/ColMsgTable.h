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

#ifndef COLMSGTABLE_H
#define COLMSGTABLE_H

#include <q3ptrdict.h>
//Added by qt3to4:
#include <Q3ValueList>

#include "MyTable.h"

class ColMsg;
class ColMsgList;

class ColDiagramView;

class ColMsgTable : public MyTable
{
    Q_OBJECT

protected:
    bool rec;
    ColDiagramView * view;
    ColMsgList & msgs;
    Q3ValueList<ColMsg *> flat_msg_list;

    void refresh();
    void refresh(ColMsgList & m);
    void edit_msg(int row);
    void change_ranks(int row, int col);

#ifdef NEW_METHOD
    void save_list(ColMsgList & l, Q3PtrDict<ColMsgList> & saved);
#endif

public:
    ColMsgTable(QWidget * parent, ColDiagramView * v, ColMsgList & m);

protected slots:
    virtual void button_pressed(int row, int col, int button, const QPoint & mousePos);
};

#endif
