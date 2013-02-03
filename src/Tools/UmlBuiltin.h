#ifndef _UMLBUILTIN_H
#define _UMLBUILTIN_H


#include "misc/mystr.h"

//  Internal class used to memorize the types defined through the first 'generation settings' tab

struct UmlBuiltin {
    WrapperStr uml;

#ifdef WITHCPP
    WrapperStr cpp;

    WrapperStr cpp_in;

    WrapperStr cpp_out;

    WrapperStr cpp_inout;
#endif

    WrapperStr cpp_return;

#ifdef WITHJAVA
    WrapperStr java;
#endif

#ifdef WITHIDL
    WrapperStr idl;
#endif

};

#endif
