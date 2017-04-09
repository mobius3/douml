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

#ifndef ATYPE_H
#define ATYPE_H

#include "UmlEnum.h"
#include "mystr.h"
//Added by qt3to4:
#include <QTextStream>

class QTextStream;
class BrowserClass;
class ToolCom;

class AType
{
public:
    WrapperStr explicit_type;
    BrowserClass * type = nullptr;

public:
    AType(){}
    QString get_type() const;
    void set_explicit_type(QString value){explicit_type = value;}
    void set_type(BrowserClass* value){type = value;}
    QString get_type(ShowContextMode mode) const;
    QString get_full_type() const;

    void send_def(ToolCom * com) const;
    void save(QTextStream & st, QString & warning,
              const char * t, const char * ex) const;
    void read(char *& st, const char * t, const char * ex);
    void read(char *& st, const char * t, const char * ex, const char * k);
    friend bool operator==(const AType & s1, const AType & s2);
    friend bool operator!=(const AType & s1, const AType & s2);
};
bool operator==(const AType & s1, const AType & s2);
bool operator!=(const AType & s1, const AType & s2);
#endif

