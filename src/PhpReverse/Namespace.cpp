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

#include "Namespace.h"
//Added by qt3to4:
#include <Q3CString>

// namespace stack, namespaces.last() = current namespace full name + "\",
// i.e. "A\B...\Z\"
QStringList Namespace::Stack;

// namespace and class aliases
QMap<Q3CString,Q3CString> Namespace::Aliases;

void Namespace::enter(Q3CString s)
{
  for (;;) {
    Stack.prepend(s + "\\");
    
    int p = s.findRev('\\');
    
    if (p == -1)
      return;
    
    s = s.left(p - 1);
  }
}

void Namespace::exit()
{
  // no really nested namespaces
  Stack.clear();
  Aliases.clear();
}

QString Namespace::namespacify(Q3CString s) {
  int index = s.find("\\");
  
  if (index == 0)
    // absolute path
    return ((const char *) s) + 1;
  
  QMap<Q3CString,Q3CString>::ConstIterator it;
  
  if (index == -1) {
    if ((it = Aliases.find(s)) != Aliases.end())
      // a class alias
      return ((*it)[0] == '\\')
	? QString(((const char *) *it) + 1)
	: QString(*it);
  }
  else if ((it = Aliases.find(s.left(index))) != Aliases.end())
    s.replace(0, index, *it);
  else if (s.left(index) == "namespace")
    s.remove(0, index + 1);
  
  return (Stack.isEmpty())
    ? QString(s)
    : Stack.last() + QString(s);
}

Q3CString Namespace::current() {
  if (Stack.isEmpty())
    return 0;
  
  QString & s = Stack.last();
  
  return Q3CString(s.left(s.length() - 1).toAscii().constData());
}
