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





#include "ParamData.h"
#include "BrowserClass.h"
#include "myio.h"
#include "ToolCom.h"
//Added by qt3to4:
#include <QTextStream>

ParamData::ParamData() : dir(UmlInOut)
{
}

void ParamData::set_name(const char * s)
{
    name = s;
}

void ParamData::set_dir(UmlParamDirection d)
{
    dir = d;
}

void ParamData::set_type(const AType & t)
{
    type = t;
}

void ParamData::set_default_value(WrapperStr str)
{
    default_value = str;
}

QString ParamData::definition(bool withdir, bool withname,
                              ShowContextMode mode) const
{
    WrapperStr t;

    if (type.type == 0)
        t = (const char *) type.explicit_type;
    else
        t = type.type->contextual_name(mode);

    if (withdir) {
        WrapperStr r = stringify(dir) + QString(" ");

        if (withname)
            r += name + " : ";

        r += t;

        QString v = default_value;

        v = v.simplifyWhiteSpace();

        return ((dir == UmlOut) || v.isEmpty())
               ? r
               : r + " = " + v;
    }
    else if (withname)
        return name + QString(" : ") + t;
    else
        return t;
}

void ParamData::send_uml_def(ToolCom * com)
{
    com->write_char(dir);
    type.send_def(com);
    com->write_string(name);
    com->write_string(default_value);
}

void ParamData::save(QTextStream & st, QString & warning) const
{
    nl_indent(st);
    st << "  param " << stringify(dir) << " name ";
    save_string(name, st);
    type.save(st, warning, " type ", " explicit_type ");

    if (!default_value.isEmpty()) {
        nl_indent(st);
        st << "    defaultvalue ";
        save_string(default_value, st);
    }
}

void ParamData::read(char *& st, char *& k)
{
    if (strcmp(k, "param"))
        wrong_keyword(k, "param");

    dir = direction(read_keyword(st));

    read_keyword(st, "name");
    name = read_string(st);
    type.read(st, "type", "explicit_type");
    k = read_keyword(st);

    if (!strcmp(k, "defaultvalue")) {
        default_value = read_string(st);
        k = read_keyword(st);
    }
}
bool operator==(const ParamData & first, const ParamData & second)
{
    return first.name == second.name &&
    first.dir == second.dir &&
    first.type == second.type &&
    first.default_value == second.default_value;
}

bool operator!=(const ParamData & first, const ParamData & second)
{
    return !(first == second);
}
