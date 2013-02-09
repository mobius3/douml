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

#ifndef STATEDATA_H
#define STATEDATA_H

#include "SimpleData.h"
#include "UmlEnum.h"
//Added by qt3to4:
#include <QTextStream>

class QTextStream;

class BrowserState;
class StateDialog;
class BrowserOperation;

struct StateBehavior {
    WrapperStr on_entry;
    WrapperStr on_exit;
    WrapperStr do_activity;

    void save(QTextStream &, const char * lang) const;
    void read(char *& st, char *& k, const char * lang);

    void send_def(ToolCom * com);
};

class StateData : public SimpleData
{
    Q_OBJECT

    friend class StateDialog;

protected:
    bool is_active;
    StateBehavior uml;
    StateBehavior cpp;
    StateBehavior java;
    BrowserOperation * specification;
    BrowserState * reference;

    virtual void send_uml_def(ToolCom * com, BrowserNode * bn,
                              const QString & comment);
    virtual void send_cpp_def(ToolCom * com);
    virtual void send_java_def(ToolCom * com);

public:
    StateData();
    StateData(StateData * model, BrowserNode * br);
    virtual ~StateData();

    const StateBehavior & get_behavior(DrawingLanguage) const;
    bool get_is_active() const {
        return is_active;
    }
    BrowserOperation * get_specification() const {
        return specification;
    }
    void set_specification(BrowserOperation *);
    BrowserState * get_reference() const {
        return reference;
    }
    void set_reference(BrowserState *);

    void edit();

    virtual bool tool_cmd(ToolCom * com, const char * args,
                          BrowserNode * bn, const QString & comment);

    void save(QTextStream &, QString & warning) const;
    void read(char *& st, char *& k);

protected slots:
    void on_delete();
};

#endif
