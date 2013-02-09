#ifndef _UMLSTEREOTYPE_H
#define _UMLSTEREOTYPE_H


#include <q3cstring.h>

//  Internal class used to know how what code is produced for a stereotype in each language

struct UmlStereotype {
    Q3CString uml;

#ifdef WITHCPP
    Q3CString cpp;
#endif

#ifdef WITHJAVA
    Q3CString java;
#endif

#ifdef WITHPHP
    Q3CString php;
#endif

#ifdef WITHPHP
    Q3CString python;
#endif

#ifdef WITHIDL
    Q3CString idl;
#endif

};

#endif
