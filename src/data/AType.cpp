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





#include <QTextStream>

#include "AType.h"
#include "BrowserClass.h"
#include "ToolCom.h"
#include "myio.h"

QString AType::get_type() const
{
    QString result;
    if(type != 0)
        result = type->get_name();
    result = explicit_type.operator QString();
    return result;
}

QString AType::get_type(ShowContextMode mode) const
{
    return (type == 0)
           ? QString((const char *) explicit_type)
           : type->contextual_name(mode);
}

QString AType::get_full_type() const
{
    return (type != 0) ? type->full_name(TRUE)
           : QString((const char *) explicit_type);
}

void AType::send_def(ToolCom * com) const
{
    if (type == 0) {
        com->write_id(0);
        com->write_string(explicit_type);
    }
    else if (type->deletedp()) {
        com->write_id(0);
        com->write_string(0);
    }
    else
        type->write_id(com);
}

// returns FALSE on error

void AType::save(QTextStream & st, QString & warning,
                 const char * t, const char * ex) const
{
    if (type != 0) {
        if (type->deletedp()) {
            // theo not possible
            st << ex;
            save_string(type->get_name(), st);
        }
        else {
            st << t;
            type->save(st, TRUE, warning);
        }
    }
    else {
        st << ex;
        save_string(explicit_type, st);
    }
}

void AType::read(char *& st, const char * t, const char * ex)
{
    char * k = read_keyword(st);

    if (!strcmp(k, t)) {
        type = BrowserClass::read_ref(st);
        explicit_type = QString();
    }
    else if (!strcmp(k, ex)) {
        type = 0;
        explicit_type = read_string(st);
    }
    else
        wrong_keyword(k, QString(t) + '/' + ex);
}

void AType::read(char *& st, const char * t, const char * ex, const char * k)
{
    if (!strcmp(k, t)) {
        type = BrowserClass::read_ref(st);
        explicit_type = QString();
    }
    else if (!strcmp(k, ex)) {
        type = 0;
        explicit_type = read_string(st);
    }
    else
        wrong_keyword(k, QString(t) + '/' + ex);
}
bool operator==(const AType & s1, const AType & s2)
{
    bool typeResult = false;
    if(!s1.type && !s2.type)
        typeResult = true;
    else if(s1.type != s2.type)
    {
        if(s1.type == nullptr)
            return false;
        else if(s2.type == nullptr)
            return false;
         typeResult = *s1.type->get_name() == *s2.type->get_name();
    }


    return s1.explicit_type == s2.explicit_type && typeResult;
}
bool operator!=(const AType & s1, const AType & s2)
{
    return !(s1==s2);
}
