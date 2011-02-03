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

#ifndef CLASS_H
#define CLASS_H

#include "BrowserNode.h"
#include "ClassContainer.h"
#include "UmlClass.h"
#include "Namespace.h"
//Added by qt3to4:
#include <QPixmap>
#include <Q3CString>
#include <Q3ValueList>
#include <Q3PtrList>

class Class : public BrowserNode, public ClassContainer {
  protected:
    Q3CString filename;
    Q3CString stereotype;
    Q3CString its_namespace;
    UmlClass * uml;
    bool reversedp;
    bool stereotype_declared;
#ifdef REVERSE
    bool from_lib;
# ifdef ROUNDTRIP
    bool updated;
# endif
    FormalParameterList formals;
#else
    bool have_formals;
#endif
    NDict<Class> declared;
    NDict<Class> defined;
    
    void manage_member(Q3CString s, aVisibility visibility,
		       ClassContainer * container, const Q3CString & path
#ifdef ROUNDTRIP
		       , bool roundtrip, Q3PtrList<UmlItem> & expected_order
#endif
		       );
    
  public:
    Class(BrowserNode * parent, const char * name, const Q3CString & st);
#ifdef ROUNDTRIP
    Class(BrowserNode * parent, UmlClass * ucl);
#endif
    virtual ~Class();	// just to not have warning
  
    bool set_stereotype(const Q3CString & st);
    
    virtual bool find_type(Q3CString type, UmlTypeSpec & typespec);
    virtual Class * declare_if_needed(const Q3CString & name,
				      Q3CString stereotype = 0);
    virtual Class * define(const Q3CString & name, Q3CString stereotype = 0);
    virtual void declare_if_needed(Q3CString name, Class * cl);
    virtual void define(Q3CString name, Class * cl);
    virtual Class * new_class(const Q3CString & name,
			      const Q3CString & stereotype,
			      bool declaration);
    virtual void declaration(const Q3CString & name, const Q3CString & stereotype,
			     const Q3CString & decl
#ifdef ROUNDTRIP
			     , bool roundtrip, Q3PtrList<UmlItem> & expected_order
#endif
			     );
    
    virtual bool isa_package() const;
    const Q3CString & get_namespace() const { return its_namespace; }
    UmlClass * get_uml();
    void set_uml(UmlClass *);
    bool reversed() const { return reversedp; };
    bool already_in_bouml();
    virtual QString get_path() const;
#ifdef ROUNDTRIP
    virtual Class * upload_define(UmlClass *);
    void set_updated() { updated = TRUE; }
    bool is_roundtrip_expected() const;
#endif

#ifdef REVERSE
    bool from_libp() { return from_lib; };
#else
    const Q3CString & get_description() const { return description; };
    
    virtual void selected();
    virtual void activated();
    virtual void menu();
    virtual void refer(const QString & name);

    const QPixmap * pixmap(int) const;
    void paintCell(QPainter * p, const QColorGroup & cg, int column,
		   int width, int alignment);

        
    virtual void backup(QDataStream & dt) const;
#endif
    
    static Class * reverse(ClassContainer * container,
			   Q3CString stereotype, 
			   const Q3ValueList<FormalParameterList> & tmplt,
			   const Q3CString & path, Q3CString name
#ifdef ROUNDTRIP
			   , bool rndtrp, Q3PtrList<UmlItem> & expectedorder
#endif
			   );
    static Class * reverse_enum(ClassContainer * container,
				const Q3CString & path, Q3CString name
#ifdef ROUNDTRIP
				, bool rndtrp, Q3PtrList<UmlItem> & expectedorder
#endif
			   );
    static bool reverse_typedef(ClassContainer * container, const Q3CString & path,
				Q3ValueList<FormalParameterList> & tmplts
#ifdef ROUNDTRIP
				, bool rndtrp, Q3PtrList<UmlItem> & expectedorder
#endif
				);
};

#endif
