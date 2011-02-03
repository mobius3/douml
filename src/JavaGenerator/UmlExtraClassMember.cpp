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

#include <q3textstream.h>
//Added by qt3to4:
#include <Q3CString>
#include <QTextOStream>

#include "UmlExtraClassMember.h"

/*
void UmlExtraClassMember::compute_dependency(Q3PtrList<JavaRefType> &, Q3CString) {
  // does nothing
}
*/

void UmlExtraClassMember::generate(QTextOStream & f, const Q3CString &,
				   Q3CString) {
  f << javaDecl();
}

void UmlExtraClassMember::generate_enum_pattern_item(QTextOStream & f, int &,
						     const Q3CString &,
						     Q3CString) {
  f << javaDecl();
}

void UmlExtraClassMember::generate_enum_pattern_case(QTextOStream & f,
						     Q3CString) {
  f << javaDecl();
}

void UmlExtraClassMember::generate_enum_member(QTextOStream & f, Q3CString) {
  f << javaDecl();
}
