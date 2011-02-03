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

#ifndef UMLCLASS_H
#define UMLCLASS_H

#include <q3dict.h>
#include <q3ptrlist.h>
//Added by qt3to4:
#include <Q3CString>
#include <QTextOStream>
#include <Q3ValueList>
#include <Q3PtrList>

#include "UmlBaseClass.h"
#include "UmlTypeSpec.h"
#include "UmlFormalParameter.h"
#include "UmlActualParameter.h"

class QTextOStream;

class UmlPackage;
class UmlClass;
class CppRefType;

class UmlClass : public UmlBaseClass {
  private:
    bool managed;
    
    static Q3PtrList<UmlClass> context;
    
    static Q3ValueList<UmlActualParameter> noactuals;
    
  public:
    UmlClass(void * id, const Q3CString & n)
      : UmlBaseClass(id, n), managed(FALSE) {};
  
    Q3CString cpp_stereotype();
    
    void compute_dependencies(Q3PtrList<CppRefType> &, bool all_in_h);
    
    virtual void compute_dependency(Q3PtrList<CppRefType> & dependency,
				    const Q3CString & cl_stereotype,
				    bool all_in_h);
    virtual void generate_decl(aVisibility & current_visibility,
			       QTextOStream & f_h,
			       const Q3CString & cl_stereotype,
			       Q3CString indent,
			       BooL & first, bool last);
    void generate_def(QTextOStream & f, Q3CString indent, bool h);
    virtual void generate_def(QTextOStream & f, Q3CString indent, bool h,
			      Q3CString templates, Q3CString cl_names,
			      Q3CString templates_tmplop, 
			      Q3CString cl_names_tmplop);
				         
    virtual void generate();
    void generate_decl(QTextOStream &, Q3CString indent);
    
    void get_template_prefixes(Q3CString & template1, Q3CString & template2);
    void spec(Q3CString & templates, Q3CString & names,
	      Q3CString & templates_tmplop, Q3CString & names_tmplop);
    Q3CString decl();
    
    void write(QTextOStream &, bool with_formals = TRUE,
	       BooL * is_template = 0,
	       const Q3ValueList<UmlActualParameter> & actuals = noactuals);
    static void write(QTextOStream &, const UmlTypeSpec &,
		      bool with_formals = TRUE,
		      BooL * is_template = 0);
};

#endif
