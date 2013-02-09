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

#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <q3valuelist.h>
#include <qstringlist.h>
#include "misc/mystr.h"
#include <q3dict.h>
#include <qmap.h>

#include "Lex.h"

// it is a singleton but I prefer static members
// Namespace::instance() is too long to hit

class Namespace
{
public:
    static void set(const WrapperStr & s);
    static void unset();
    static void enter(const WrapperStr & s);
    static void exit();
    static void enter_anonymous() {
        AnonymousLevel += 1;
    }
    static void exit_anonymous() {
        AnonymousLevel -= 1;
    }
    static bool underAnonymous() {
        return AnonymousLevel != 0;
    }

    static void save_using_scope() {
        UsingScope.prepend(Usings);
    }
    static void restore_using_scope();
    static const QStringList stack() {
        return Stack;
    }

    static void add_using(const WrapperStr & s) {
        Usings.append(s + "::");
    }
    static void clear_usings() {
        Usings.clear();
    }
    static const QStringList & usings() {
        return Usings;
    }

    static void add_alias(const WrapperStr & a, const WrapperStr & s) {
        Aliases.replace(a, s);
    }
    static void clear_aliases() {
        Aliases.clear();
    }

    static QString namespacify(WrapperStr s, bool local);
    static WrapperStr current();

private:
    static QStringList Stack;
    static int AnonymousLevel;
    static QStringList Usings;
    static Q3ValueList<QStringList> UsingScope;
    static QMap<QString, WrapperStr> Aliases;
};

// does not not inherit QDict to not allow to use directly
// a QDict operation, to force to take into account the namespace
// management

template<class T>
class NDict
{
public:
    NDict() : hasAnonymous(FALSE) {}
    NDict(unsigned n) : hasAnonymous(FALSE) {
        d.resize(n);
    }

    void insert(const WrapperStr & key, const T * item);
    void replace(const WrapperStr & key, const T * item);
    bool remove(const WrapperStr & key);
    T * operator[](const WrapperStr & key) const;

private:
    bool hasAnonymous;
    Q3Dict<T> d;
};

template<class T>
void NDict<T>::insert(const WrapperStr & key, const T * item)
{
    hasAnonymous |= Namespace::underAnonymous();
    d.insert(Namespace::namespacify(key, Namespace::underAnonymous()), item);
}

template<class T>
void NDict<T>::replace(const WrapperStr & key, const T * item)
{
    hasAnonymous |= Namespace::underAnonymous();
    d.replace(Namespace::namespacify(key, Namespace::underAnonymous()), item);
}

template<class T>
bool NDict<T>::remove(const WrapperStr & key)
{
    return d.remove(Namespace::namespacify(key, Namespace::underAnonymous()));
}

template<class T>
T * NDict<T>::operator[](const WrapperStr & key) const
{
    QString k = Namespace::namespacify(key, FALSE);
    T * r = d[k];

    if (r != 0)
        return r;

    QString s;

    if ((((const char *) key)[0] != ':') ||
        (((const char *) key)[1] != ':')) {
        QStringList::ConstIterator it;

        s = key.operator QString();

        for (it = Namespace::usings().begin();
             it != Namespace::usings().end();
             ++it)
            if ((r = d[*it + s]) != 0)
                return r;

        for (it = Namespace::stack().begin();
             it != Namespace::stack().end();
             ++it)
            if ((r = d[*it + s]) != 0)
                return r;
    }

    if (hasAnonymous) {
        k += "\n" + Lex::filename();
        r = d[k];

        if ((r == 0) &&
            ((((const char *) key)[0] != ':') ||
             (((const char *) key)[1] != ':'))) {
            QStringList::ConstIterator it;

            s += "\n" + Lex::filename();

            for (it = Namespace::usings().begin();
                 it != Namespace::usings().end();
                 ++it)
                if ((r = d[*it + s]) != 0)
                    return r;

            for (it = Namespace::stack().begin();
                 it != Namespace::stack().end();
                 ++it)
                if ((r = d[*it + s]) != 0)
                    return r;
        }
    }

    return r;
}

#endif
