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

#ifndef UMLCLASS_H
#define UMLCLASS_H

#include <q3ptrlist.h>
//Added by qt3to4:
#include "misc/mystr.h"
#include <QTextStream>

#include "UmlBaseClass.h"
#include "UmlTypeSpec.h"

class QTextStream;

class UmlPackage;
class UmlClass;

class UmlClass : public UmlBaseClass
{
private:
    bool managed;

public:
    UmlClass(void * id, const WrapperStr & n)
        : UmlBaseClass(id, n), managed(FALSE) {};

    WrapperStr java_stereotype();
    void generate(QTextStream &, WrapperStr indent);

    virtual void generate();
    virtual void generate(QTextStream & f, const WrapperStr & cl_stereotype,
                          WrapperStr indent);
    virtual void generate_enum_pattern_item(QTextStream &, int &, const WrapperStr &, WrapperStr);
    virtual void generate_enum_pattern_case(QTextStream &, WrapperStr);
    virtual void generate_enum_member(QTextStream &, WrapperStr);
    virtual void generate_import(QTextStream & f, const WrapperStr & indent);
    void generate_formals(QTextStream & f);
    void import(QTextStream & f, const WrapperStr & indent);

    void write(QTextStream &);
    static void write(QTextStream &, const UmlTypeSpec &);
};

#endif
