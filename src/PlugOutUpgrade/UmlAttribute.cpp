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

#include "UmlAttribute.h"

#include "UmlClass.h"
#include "UmlCom.h"
#include "util.h"
//Added by qt3to4:
#include "misc/mystr.h"


UmlAttribute * UmlAttribute::java2Php(UmlClass * php, UmlClass * java,
                                      const char * javaname,
                                      const char * phpname)
{
    if (phpname == 0)
        phpname = javaname;

    UmlAttribute * from = java->get_attribute(javaname);

    if (from == 0) {
        WrapperStr err = WrapperStr("cannot find attribute '") +
                        javaname + WrapperStr("' in class '") + java->name()
                        + WrapperStr("'<br>\n");
        UmlCom::trace(err);
        throw 0;
    }

    UmlAttribute * to = UmlBaseAttribute::create(php, phpname);

    if (to == 0) {
        WrapperStr err = WrapperStr("cannot create attribute '") +
                        phpname + WrapperStr("' in class '") + php->name()
                        + WrapperStr("'<br>\n");
        UmlCom::trace(err);
        throw 0;
    }

    UmlCom::trace("add attribute " + php->name() + "::" + phpname + "<br>\n");

    to->set_Type(from->type());
    to->set_isClassMember(from->isClassMember());
    to->set_Visibility(from->visibility());
    to->set_CppVisibility(from->cppVisibility());
    to->set_CppDecl(::java2Php(from->cppDecl()));
    to->set_JavaDecl(from->javaDecl());

    return to;
}

UmlAttribute * UmlAttribute::java2Python(UmlClass * python, UmlClass * java,
        const char * javaname,
        const char * pythonname)
{
    if (pythonname == 0)
        pythonname = javaname;

    UmlAttribute * from = java->get_attribute(javaname);

    if (from == 0) {
        WrapperStr err = WrapperStr("cannot find attribute '") +
                        javaname + WrapperStr("' in class '") + java->name()
                        + WrapperStr("'<br>\n");
        UmlCom::trace(err);
        throw 0;
    }

    UmlAttribute * to = UmlBaseAttribute::create(python, pythonname);

    if (to == 0) {
        WrapperStr err = WrapperStr("cannot create attribute '") +
                        pythonname + WrapperStr("' in class '") + python->name()
                        + WrapperStr("'<br>\n");
        UmlCom::trace(err);
        throw 0;
    }

    UmlCom::trace("add attribute " + python->name() + "::" + pythonname + "<br>\n");

    to->set_Type(from->type());
    to->set_isClassMember(from->isClassMember());
    to->set_Visibility(from->visibility());
    to->set_CppVisibility(from->cppVisibility());
    to->set_CppDecl(::java2Python(from->cppDecl()));
    to->set_JavaDecl(from->javaDecl());

    return to;
}

UmlAttribute * UmlAttribute::cpp2Python(UmlClass * python, UmlClass * cpp,
                                        const char * cppname,
                                        const char * pythonname)
{
    if (pythonname == 0)
        pythonname = cppname;

    UmlAttribute * from = cpp->get_attribute(cppname);

    if (from == 0) {
        WrapperStr err = WrapperStr("cannot find attribute '") +
                        cppname + WrapperStr("' in class '") + cpp->name()
                        + WrapperStr("'<br>\n");
        UmlCom::trace(err);
        throw 0;
    }

    UmlAttribute * to = UmlBaseAttribute::create(python, pythonname);

    if (to == 0) {
        WrapperStr err = WrapperStr("cannot create attribute '") +
                        pythonname + WrapperStr("' in class '") + python->name()
                        + WrapperStr("'<br>\n");
        UmlCom::trace(err);
        throw 0;
    }

    UmlCom::trace("add attribute " + python->name() + "::" + pythonname + "<br>\n");

    to->set_Type(from->type());
    to->set_isClassMember(from->isClassMember());
    to->set_Visibility(from->visibility());
    to->set_CppVisibility(from->cppVisibility());
    to->set_CppDecl(::cpp2Python(from->cppDecl()));
    to->set_JavaDecl(from->javaDecl());

    return to;
}
