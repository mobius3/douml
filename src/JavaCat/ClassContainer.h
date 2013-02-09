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

#ifndef _CLASS_CONTAINER_H
#define _CLASS_CONTAINER_H

#include <q3dict.h>
//Added by qt3to4:
#include "misc/mystr.h"
#include <Q3ValueList>
#include "UmlClass.h"

class Class;
class UmlTypeSpec;

class ClassContainer
{
public:
    ClassContainer() {};
    virtual ~ClassContainer();

    virtual void compute_type(WrapperStr type, UmlTypeSpec & typespec,
                              const Q3ValueList<FormalParameterList> & tmplts,
                              Class ** need_object = 0) = 0;
    virtual Class * define(const WrapperStr & name, char st) = 0;

    bool read_type(UmlTypeSpec & typespec, Class ** cl,
                   const Q3ValueList<FormalParameterList> & tmplts,
                   Q3ValueList<UmlTypeSpec> * actuals,
                   WrapperStr & str_actual, WrapperStr s,
                   UmlClass ** first_actual_class, WrapperStr & def,
                   WrapperStr & genericname);
#ifdef ROUNDTRIP
    virtual Class * upload_define(UmlClass *) = 0;
#endif

protected:
    Q3Dict<Class> Defined;
};

#endif
