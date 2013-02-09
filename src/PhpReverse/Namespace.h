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
    static void enter(WrapperStr s);
    static void exit();

    static const QStringList stack() {
        return Stack;
    }

    static void add_alias(const WrapperStr & a, const WrapperStr & s) {
        Aliases.replace(a.operator QString(), s);
    }
    static void clear_aliases() {
        Aliases.clear();
    }

    static QString namespacify(WrapperStr s);
    static WrapperStr current();

private:
    static QStringList Stack;
    static QMap<QString, WrapperStr> Aliases;
};

// does not not inherit QDict to not allow to use directly
// a QDict operation, to force to take into account the namespace
// management

template<class T>
class NDict
{
public:
    NDict() {}
    NDict(unsigned n) {
        d.resize(n);
    }

    void insert(const WrapperStr & key, const T * item);
    void replace(const WrapperStr & key, const T * item);
    bool remove(const WrapperStr & key);
    T * operator[](const WrapperStr & key) const;

private:
    Q3Dict<T> d;
};

template<class T>
void NDict<T>::insert(const WrapperStr & key, const T * item)
{
    d.insert(Namespace::namespacify(key), item);
}

template<class T>
void NDict<T>::replace(const WrapperStr & key, const T * item)
{
    d.replace(Namespace::namespacify(key), item);
}

template<class T>
bool NDict<T>::remove(const WrapperStr & key)
{
    return d.remove(Namespace::namespacify(key));
}

template<class T>
T * NDict<T>::operator[](const WrapperStr & key) const
{
    QString k = Namespace::namespacify(key);
    T * r = d[k];

    if (r != 0)
        return r;

    QString s;

    if (((const char *) key)[0] != '\\') {
        QStringList::ConstIterator it;

        s = key.operator QString();

        for (it = Namespace::stack().begin();
             it != Namespace::stack().end();
             ++it)
            if ((r = d[*it + s]) != 0)
                return r;
    }

    return r;
}

#endif
