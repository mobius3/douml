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

#ifndef TRANSITIONDATA_H
#define TRANSITIONDATA_H

#include "SimpleData.h"
#include "UmlEnum.h"
//Added by qt3to4:
#include <QTextStream>

class QTextStream;

class BrowserTransition;
class BrowserNode;

struct TransDef {
    WrapperStr trigger;
    WrapperStr guard;
    WrapperStr expr;

    QString str(bool horiz) const;
    void save(QTextStream & st, const char * lang) const;
    void read(char *& st, char *& k, const char * lang);

    void send_def(ToolCom * com);
};

class TransitionData : public SimpleData
{
    Q_OBJECT

    friend class TransitionDialog;

protected:
    bool is_internal;
    BrowserNode * end;
    TransDef uml;
    TransDef cpp;
    TransDef java;

    virtual void send_uml_def(ToolCom * com, BrowserNode * bn,
                              const QString & comment);
    virtual void send_cpp_def(ToolCom * com);
    virtual void send_java_def(ToolCom * com);

public:
    TransitionData();
    TransitionData(const BrowserTransition * model, BrowserTransition * r);
    virtual ~TransitionData();

    virtual void delete_it();

    void set_start_end(BrowserTransition * s, BrowserNode * e);
    void edit();
    BrowserNode * get_start_node() const;
    BrowserNode * get_end_node() const {
        return end;
    }
    BrowserTransition * get_start() const {
        return (BrowserTransition *) browser_node;
    }
    bool internal() const {
        return is_internal;
    }
    void set_internal(bool y) {
        is_internal = y;
    }
    QString str(bool horiz, DrawingLanguage) const;

    virtual bool tool_cmd(ToolCom * com, const char * args,
                          BrowserNode * bn, const QString & comment);

    void save(QTextStream &, QString & warning) const;
    static TransitionData * read(char *& , char *& k);

protected slots:
    void end_deleted();
};

#endif
