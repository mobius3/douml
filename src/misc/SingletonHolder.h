// *************************************************************************
//
// Copyright 2012-2012 Nikolai Marchenko  .
//
// This file is part of the BreezeUML Uml Toolkit.
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
// e-mail : enmarantispam@gmail.com
//
// *************************************************************************
#ifndef DOUML_SINGLETONHOLDER_H
#define DOUML_SINGLETONHOLDER_H
#include <exception>
#include <stdexcept>
#include <typeinfo>

template<typename T>
struct An {
    An()                                {
        clear();
    }

    T * operator->()                     {
        return get0();
    }
    const T * operator->() const         {
        return get0();
    }
    void operator=(T * t)                {
        data = t;
    }

    bool isEmpty() const                {
        return data == 0;
    }
    void clear()                        {
        data = 0;
    }
    void init()                         {
        if (isEmpty()) reinit();
    }
    void reinit()                       {
        anFill(*this);
    }
    T * getData() {
        const_cast<An *>(this)->init();
        return data;
    }
private:
    T * get0() const {
        const_cast<An *>(this)->init();
        return data;
    }

    T * data;
};

template<typename T>
inline void anFill(An<T> & a)
{
    throw std::runtime_error(std::string("Cannot find implementation for interface: ")
                             + typeid(T).name());
}

template<typename T>
inline T & single()
{
    static T t;
    return t;
}
#define PROTO_IFACE(D_iface) template<> inline void anFill<D_iface>(An<D_iface>& a)

#define DECLARE_IMPL(D_iface) PROTO_IFACE(D_iface);

#define BIND_TO_IMPL_SINGLE(D_iface, D_impl) PROTO_IFACE(D_iface) { a = &single<D_impl>(); }

#define BIND_TO_SELF_SINGLE(D_impl) BIND_TO_IMPL_SINGLE(D_impl, D_impl)

#endif
