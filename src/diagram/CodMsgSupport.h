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

#ifndef CODMSGSUPPORT_H
#define CODMSGSUPPORT_H

#include <qlist.h>

#include "Settings.h"
#include "ColMsg.h"

class QString;
class QTextStream;

class CodObjCanvas;
class BrowserNode;

class CodMsgSupport
{
protected:
    ColMsgList msgs;
    CollaborationDiagramSettings settings;

public:
    CodMsgSupport() {};
    virtual ~CodMsgSupport();

    ColMsgList & get_msgs() {
        return msgs;
    };

    void delete_it(ColMsgList & top);
    virtual void remove_it(ColMsg * msg) = 0;
    virtual void save(QTextStream & st, bool ref, QString & warning) const = 0;
    virtual void get_from_to(CodObjCanvas *& from, CodObjCanvas *& to,
                             bool forward) = 0;
    virtual void update_msgs() = 0;
    virtual bool copyable() const = 0;

    bool supports(BrowserNode *);
};

#endif
