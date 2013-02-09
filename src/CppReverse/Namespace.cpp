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
#include <Q3ValueList>

// namespace stack, namespaces.last() = current namespace full name + "::",
// i.e. A::B...::Z:: in case it is embeded in other one(s)
QStringList Namespace::Stack;

// using list, each element ended by "::"
QStringList Namespace::Usings;

// level of nested anonymous namespace
int Namespace::AnonymousLevel;

// to lost usings defined under a namespace/class block
Q3ValueList<QStringList> Namespace::UsingScope;

// namespace aliases
QMap<QString, WrapperStr> Namespace::Aliases;

void Namespace::set(const WrapperStr & s)
{
    // for upload only
    Stack.append(s + "::");
}

void Namespace::unset()
{
    // for upload only
    Stack.remove(Stack.last());
}

void Namespace::enter(const WrapperStr & s)
{
    save_using_scope();
    Stack.append((Stack.isEmpty())
                 ? s + "::"
                 : Stack.last() + s + "::");
}

void Namespace::exit()
{
    Stack.remove(Stack.last());
    restore_using_scope();
}

void Namespace::restore_using_scope()
{
    Usings = UsingScope.first();
    UsingScope.remove(UsingScope.begin());
}

QString Namespace::namespacify(WrapperStr s, bool local)
{
    QString r;
    int index = s.find("::");

    if (index == 0)
        r = ((const char *) s) + 2;
    else {
        if (index != -1) {
            QMap<QString, WrapperStr>::ConstIterator it =
                Aliases.find(s.left(index));

            if (it != Aliases.end())
                s.replace(0, index, *it);
        }

        r = (Stack.isEmpty())
            ? s.operator QString()
            : Stack.last() + s.operator QString();
    }

    return (local)
           ? r + "\n" + Lex::filename()
           : r;
}

WrapperStr Namespace::current()
{
    if (Stack.isEmpty())
        return 0;

    QString & s = Stack.last();

    QByteArray temp = (s.left(s.length() - 2)).toAscii();
    const char * c = temp.constData();
    return WrapperStr(c);
}
