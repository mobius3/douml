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

#include "Namespace.h"
//Added by qt3to4:
#include "misc/mystr.h"

// namespace stack, namespaces.last() = current namespace full name + "\",
// i.e. "A\B...\Z\"
QStringList Namespace::Stack;

// namespace and class aliases
QMap<QString, WrapperStr> Namespace::Aliases;

void Namespace::enter(WrapperStr s)
{
    for (;;) {
        Stack.prepend(s + "\\");

        int p = s.operator QString().lastIndexOf('\\');

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

QString Namespace::namespacify(WrapperStr s)
{
    int index = s.find("\\");

    if (index == 0)
        // absolute path
        return ((const char *) s) + 1;

    QMap<QString, WrapperStr>::ConstIterator it;

    if (index == -1) {
        if ((it = Aliases.find(s)) != Aliases.end())
            // a class alias
            return ((*it)[0] == '\\')
                   ?  *(it + 1)
                   : *it;
    }
    else if ((it = Aliases.find(s.left(index))) != Aliases.end())
        s.replace(0, index, *it);
    else if (s.left(index) == "namespace")
        s.remove(0, index + 1);

    return (Stack.isEmpty())
           ? s
           : Stack.last() + s;
}

WrapperStr Namespace::current()
{
    if (Stack.isEmpty())
        return 0;

    QString & s = Stack.last();

    return WrapperStr(s.left(s.length() - 1).toAscii().constData());
}
