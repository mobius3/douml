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

#ifndef UMLOPERATION_H
#define UMLOPERATION_H

#include "UmlBaseOperation.h"
#include "UmlClass.h"
#include "Namespace.h"
//Added by qt3to4:
#include <Q3CString>
#include <Q3ValueList>
#include <Q3PtrList>

class ClassContainer;
class Package;
class Class;

class UmlOperation : public UmlBaseOperation {
  public:
    UmlOperation(void * id, const Q3CString & n);
    virtual ~UmlOperation();
  
    static bool new_one(Class * cl, const Q3CString & name,
			const Q3ValueList<FormalParameterList> & tmplt,
			Q3CString type, const Q3CString & modifier,
			const Q3CString & pretype, aVisibility visibility,
			bool inlinep, bool virtualp, bool staticp, bool constp,
			bool volatilep, bool typenamep,	bool explicitp,
			bool friendp, Q3CString friend_template,
			Q3CString comment, Q3CString description, bool pfunc
#ifdef ROUNDTRIP
			, bool roundtrip, Q3PtrList<UmlItem> & expected_order
#endif
			);
    static void reverse_definition(Package * pack, Q3CString name, Q3CString type,
				   Q3ValueList<FormalParameterList> & tmplt,
				   bool inlinep, const Q3CString & comment,
				   const Q3CString & description);

#ifdef REVERSE
    virtual bool need_source();
#ifdef ROUNDTRIP
    static void force_defs();
# endif
#endif
  
    static void skip_body(int level = 0);
    static void skip_expr(Q3CString end, bool allow_templ = FALSE);
    static bool pfunc(BooL & func, Q3CString & name, Q3CString & type,
		      const char * namespec);
  private:
#ifdef ROUNDTRIP
    static Q3PtrDict<Q3CString> DefNotYetSet;
#endif
    static NDict< Q3PtrList<UmlOperation> > friends;
    FormalParameterList * formals;
    Q3CString def0;	// for template operations
  
    static bool read_param(ClassContainer * container, unsigned rank, 
			   UmlParameter & param, Q3CString & decl,
			   const Q3ValueList<FormalParameterList> & tmplt,
			   BooL & on_error, bool add_defaultvalue);
    static void friend_operations(Q3PtrList<UmlOperation> & candidates,
				  const Q3ValueList<FormalParameterList> & tmplt,
				  const Q3CString & name);
    static bool operations(Q3PtrList<UmlOperation> & candidates, UmlClass * cl,
			   const Q3ValueList<FormalParameterList> & tmplt,
			   const FormalParameterList *& oper_tmplt,
			   const Q3CString & name);
    static bool read_throw_elt(ClassContainer * container,
			       UmlTypeSpec & typespec,
			       const Q3ValueList<FormalParameterList> & tmplts);
    bool reverse_if_def(Package * pack,
			Q3ValueList<FormalParameterList> & tmplts,
			const FormalParameterList * oper_tmplt,
			bool inlinep, bool pfct, const Q3CString & comment,
			const Q3CString & description, BooL & on_error,
			unsigned & nargs, Q3CString oper_name);

    void update_param_names(Q3ValueList<UmlParameter> & params);
#ifdef ROUNDTRIP
    void update_params(Class * cl, Q3ValueList<UmlParameter> & params);
    void update_exceptions(Class * cl, const Q3ValueList<UmlTypeSpec> & exceptions);
    
    static void clean_body(Q3CString & body);
    static UmlOperation * already_exist(Class * container, const Q3CString & name,
					Q3ValueList<UmlParameter> & params,
					bool empty_decl);
#endif
};

#endif
