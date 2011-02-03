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

#ifndef CPPREFTYPE_H
#define CPPREFTYPE_H

#include <q3ptrlist.h>
//Added by qt3to4:
#include <Q3CString>
#include <QTextOStream>
#include <Q3PtrList>

#include "UmlTypeSpec.h"

class QTextOStream;
class UmlArtifact;

class CppRefType {
  public:
    enum Weight { Low, Medium, High, Strong };
      
    static bool add(UmlClass *, Q3PtrList<CppRefType> &, bool incl, bool hight = FALSE);
    static bool add(const Q3CString &, Q3PtrList<CppRefType> &, bool incl);
    static bool add(const UmlTypeSpec & t, Q3PtrList<CppRefType> & l, bool incl);
    static void remove(UmlClass *, Q3PtrList<CppRefType> & l);
    static void remove(const Q3CString &, Q3PtrList<CppRefType> & l);
    static void force_ref(UmlClass * cl, Q3PtrList<CppRefType> & l);
    static void compute(Q3PtrList<CppRefType> & dependencies,
			const Q3CString & hdef, const Q3CString & srcdef,
			Q3CString & h_incl,  Q3CString & decl, Q3CString & src_incl,
			UmlArtifact * who);
    
  protected:
    UmlTypeSpec type;
    bool included;
    Weight weight;
    
    CppRefType(UmlClass * cl, bool i, Weight w)
      : included(i), weight(w) { type.type = cl; };
    CppRefType(const Q3CString & t, bool i, Weight w)
      : included(i), weight(w) { type.explicit_type = t; };
    
};

#endif
