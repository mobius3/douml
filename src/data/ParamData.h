// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
// Copyright 2012-2013 Nikolai Marchenko.
// Copyright 2012-2013 Leonardo Guilherme.
//
// This file is part of the DOUML Uml Toolkit.
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
// e-mail : enmarantispam@gmail.com
// home   : http://sourceforge.net/projects/douml
//
// *************************************************************************

#ifndef PARAMDATA_H
#define PARAMDATA_H

#include <QTextStream>

#include "UmlEnum.h"
#include "AType.h"

class ParamData
{
protected:
    WrapperStr name;
    UmlParamDirection dir;
    AType type;
    WrapperStr default_value;

public:
    ParamData();

    void set_name(const char *);
    const char * get_name() const {
        return name;
    };
    UmlParamDirection get_dir() const {
        return dir;
    };
    void set_dir(UmlParamDirection d);
    const AType & get_type() const {
        return type;
    };
    void set_type(const AType & t);
    const char * get_default_value() const {
        return default_value;
    };
    void set_default_value(const char * s);

    QString definition(bool withdir, bool withname,
                       ShowContextMode mode = noContext) const;

    void send_uml_def(ToolCom * com);

    void save(QTextStream &, QString & warning) const;
    void read(char *& , char *&);
    friend bool operator==(const ParamData &, const ParamData &);
    friend bool operator!=(const ParamData & first, const ParamData & second);
};
bool operator==(const ParamData &, const ParamData &);
bool operator!=(const ParamData & first, const ParamData & second);
#endif
