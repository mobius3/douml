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

#ifndef MULTIPLEDEPENDENCY_H
#define MULTIPLEDEPENDENCY_H

#include <qmap.h>

class BasicData;
template <class K> class MultipleDependencyIterator;

#ifdef __SUNPRO_CC
#define TYPENAME
#else
#define TYPENAME typename
#endif

template <class K>
class MultipleDependency
{
    friend class MultipleDependencyIterator<K>;

protected:
    QMap<const K *, unsigned> map;

public:
    MultipleDependency() {};

    bool subscribe(const K *);
    bool unsubscribe(const K *);
    void unsubscribe_all() {
        map.clear();
    };
};

template <class K>
bool MultipleDependency<K>::subscribe(const K * k)
{
    if (map.contains(k)) {
        map[k] += 1;
        return FALSE;
    }
    else {
        map.insert(k, 1);
        return TRUE;
    }
}

template <class K>
bool MultipleDependency<K>::unsubscribe(const K * k)
{
    if (map.contains(k) && ((map[k] -= 1) == 0)) {
        map.remove(k);
        return TRUE;
    }
    else
        return FALSE;
}

template <class K>
class MultipleDependencyIterator
{
protected:
    QMap<const K *, unsigned> & map;
    typedef TYPENAME QMap<const K *, unsigned>::Iterator Iter;
    Iter iter;

public:
    MultipleDependencyIterator(MultipleDependency<K> * m)
        : map(m->map), iter(m->map.begin()) {
    };
    const K * current() const {
        return (iter == map.end()) ? 0 : iter.key();
    };
    void operator++() {
        iter++;
    };
};

#endif
