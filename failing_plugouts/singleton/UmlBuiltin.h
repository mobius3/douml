#ifndef _UMLBUILTIN_H
#define _UMLBUILTIN_H


#include <q3cstring.h>

//  Internal class used to memorize the types defined through the first 'generation settings' tab

struct UmlBuiltin {
    Q3CString uml;

#ifdef WITHCPP
    Q3CString cpp;

    Q3CString cpp_in;

    Q3CString cpp_out;

    Q3CString cpp_inout;
#endif

#ifdef WITHJAVA
    Q3CString java;
#endif

#ifdef WITHIDL
    Q3CString idl;
#endif

};

#endif
