// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
//
// This file is part of the BOUML Uml Toolkit.
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
// e-mail : bouml@free.fr
// home   : http://bouml.free.fr
//
// *************************************************************************

#ifndef CLASSCONTAINER
#define CLASSCONTAINER

#include "UmlClass.h"
#include "Namespace.h"
//Added by qt3to4:
#include <Q3CString>
#include <Q3ValueList>
#include <Q3PtrList>

class Class;
class UmlTypeSpec;

class ClassContainer {
  public:
    virtual ~ClassContainer();	// just to not have warning
  
    virtual Class * declare_if_needed(const Q3CString & name,
				      Q3CString stereotype = 0) = 0;
    virtual Class * define(const Q3CString & name, Q3CString stereotype = 0) = 0;
    virtual void declare_if_needed(Q3CString name, Class * cl) = 0;
    virtual void define(Q3CString name, Class * cl) = 0;
    virtual Class * new_class(const Q3CString & name,
			      const Q3CString & stereotype,
			      bool declaration) = 0;
    virtual bool find_type(Q3CString type, UmlTypeSpec & typespec) = 0;
    virtual void declaration(const Q3CString & name, const Q3CString & stereotype,
			     const Q3CString & decl
#ifdef ROUNDTRIP
			     , bool roundtrip, Q3PtrList<UmlItem> & expected_order
#endif
			     ) = 0;
    
    void compute_type(Q3CString type, UmlTypeSpec & typespec,
		      Q3CString & typeform, bool get_first_template_actual = FALSE,
		      const Q3ValueList<FormalParameterList> & tmplts = empty);
    bool find_type(Q3CString type, UmlTypeSpec & typespec,
		   NDict<Class> & defined);
#ifdef ROUNDTRIP
    virtual Class * upload_define(UmlClass *) = 0;
#endif
    
    static bool get_template(FormalParameterList & tmplt);
    
  protected:
    Class * declare_if_needed(const Q3CString & name,
			      const Q3CString & stereotype,
			      const FormalParameterList & formals,
			      NDict<Class> & declared, 
			      NDict<Class> & defined);
    Class * define(const Q3CString & name, const Q3CString & stereotype,
		   NDict<Class> & declared, NDict<Class> & defined);
    
    static Q3ValueList<FormalParameterList> empty;
};

#endif
