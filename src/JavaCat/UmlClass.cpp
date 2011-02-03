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

#ifdef REVERSE
# include <qfileinfo.h>
//Added by qt3to4:
#include <Q3CString>
//Added by qt3to4:
#include <Q3PtrList>
#endif
#include "UmlClass.h"
#include "UmlArtifact.h"
#include "Package.h"
#include "UmlDeploymentView.h"
#include "UmlPackage.h"
#include "JavaCatWindow.h"
#include "JavaSettings.h"
#include "Class.h"
#ifdef ROUNDTRIP
# include "UmlRelation.h"
#endif


UmlClass::UmlClass(void * id, const Q3CString & n) 
    : UmlBaseClass(id, n) 
#ifdef ROUNDTRIP
    , created(FALSE), the_class(0)
#endif
{
}

#ifdef REVERSE

void UmlClass::need_artifact(const QStringList & imports,
			     bool remove_java_lang,
			     const QStringList & static_imports,
			     const Q3CString & path, UmlArtifact *& cp) {
  if (parent()->kind() == aClassView) {
    if (cp != 0)
      cp->addAssociatedClass(this);
    else {
      UmlPackage * pack = (UmlPackage *) parent()->parent();
      
      if ((cp = associatedArtifact()) == 0) {
	// create associated artifact
	QFileInfo fi(path);
	Q3CString artname = Q3CString(fi.baseName().toAscii().constData());
	
	if ((cp = UmlBaseArtifact::create(pack->get_deploymentview(), artname)) == 0) {
	  UmlCom::trace(Q3CString("<font face=helvetica><b>cannot create<i> artifact ")
			+ artname + "</i></b></font><br>"); 
	  return;
	}
	cp->addAssociatedClass(this);
      }
      
      cp->set_Stereotype("source");
      
      Q3CString s = JavaSettings::sourceContent();
      int index = s.find("${definition}");
      
      if (index != -1) {
	  

	for (QStringList::const_iterator it = imports.begin(); it != imports.end(); it++) {
	  Q3CString import = Q3CString((*it).toAscii().constData());
	  
	  if (!remove_java_lang || (import != "java.lang.")) {
	    import += (((const char *) import)[import.length() - 1] == '.')
	      ? "*;\n" : ";\n";
	    
	    s.insert(index, (const char *) ("import " + import));
	    index = s.find("${definition}", index);
	  }
	}
	
	for (QStringList::const_iterator it = imports.begin(); it != imports.end(); it++) {
	  s.insert(index, (const char *)("import static" + Q3CString((*it).toAscii().constData()) + '\n'));
	  index = s.find("${definition}", index);
	}
      }
      
      cp->set_JavaSource(Q3CString(s));
    }
  }
}

# ifdef ROUNDTRIP

void UmlClass::upload(ClassContainer * cnt)
{
  the_class = cnt->upload_define(this);
  
  const Q3PtrVector<UmlItem> & ch = UmlItem::children();
  UmlItem ** v = ch.data();
  UmlItem ** const vsup = v + ch.size();
  
  for (;v != vsup; v += 1)
    (*v)->upload(the_class);
}

bool UmlClass::set_roundtrip_expected() {
  if (is_roundtrip_expected() ||
      ((parent()->kind() != aClass) &&
       ((associatedArtifact() == 0) ||
	!associatedArtifact()->set_roundtrip_expected_for_class())))
    return TRUE;
  
  const Q3PtrVector<UmlItem> & ch = UmlItem::children();
  UmlClassItem ** v = (UmlClassItem **) ch.data();
  UmlClassItem ** const vsup = v + ch.size();
  bool result = UmlClassItem::set_roundtrip_expected();
  
  for (;v != vsup; v += 1)
    result &= (*v)->set_roundtrip_expected();
  
  return result;
  
}

void UmlClass::mark_useless(Q3PtrList<UmlItem> & l) {
  UmlClassItem::mark_useless(l);

  Q3PtrVector<UmlItem> ch = UmlItem::children();
  UmlClassItem ** v = (UmlClassItem **) ch.data();
  UmlClassItem ** const vsup = v + ch.size();
    
  for (;v != vsup; v += 1)
    (*v)->mark_useless(l);
}

void UmlClass::scan_it(int & n) {
  if (is_roundtrip_expected())
    associatedArtifact()->scan_it(n);
}

void UmlClass::send_it(int n) {
  if (is_roundtrip_expected())
    associatedArtifact()->send_it(n);
}

UmlItem * UmlClass::search_for_att_rel(const Q3CString & name) {
  const Q3PtrVector<UmlItem> & ch = UmlItem::children();
  UmlItem ** v = ch.data();
  UmlItem ** const vsup = v + ch.size();
  
  for (;v != vsup; v += 1) {
    switch ((*v)->kind()) {
    case anAttribute:
      if ((*v)->name() == name)
	return *v;
      break;
    case aRelation:
      if (((UmlRelation *) *v)->roleName() == name)
	return *v;
      break;
    default:
      break;
    }
  }

  return 0;
}

void UmlClass::reorder(Q3PtrList<UmlItem> & expected_order) {
  if (expected_order.isEmpty())
    return;
  
  Q3PtrVector<UmlItem> ch = UmlItem::children(); // copy
  UmlItem ** v = ch.data();
  
  unload(); // to not reload children each time

  //bool updated = FALSE;
  UmlItem * expected_previous = 0;
  Q3PtrListIterator<UmlItem> expected_it(expected_order);
  UmlItem * expected;
  
  while ((expected = expected_it.current()) != 0) {
    if (*v != expected) {
      //updated = TRUE;
      expected->moveAfter(expected_previous);
      
      UmlItem * x1 = expected;
      
      do {
	UmlItem * x2 = *v;
	
	*v = x1;
	x1 = x2;
      } while (x1 != expected);
    }
    
    expected_previous = expected;
    ++expected_it;
    v += 1;
  }
  
  //if (updated)
  //  get_class()->set_updated();
}

# endif

#endif

void UmlClass::manage_generic(Q3CString & form, UmlTypeSpec & typespec,
			      Q3CString str_actuals, const char * k)
{
  if (typespec.type != 0) {
    int index;
  
    if (!typespec.explicit_type.isEmpty()) {
      if ((index = form.find(k)) != -1)
	form.replace(index, strlen(k), typespec.explicit_type);
    }
    else if (! str_actuals.isEmpty()) {
      if ((index = form.find(k)) != -1)
	form.insert(index + strlen(k), (const char *)str_actuals);
    }
  }
}
