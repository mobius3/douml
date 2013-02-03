#ifndef _UMLSTEREOTYPE_H
#define _UMLSTEREOTYPE_H


#include "misc/mystr.h"

//  Internal class used to know how what code is produced for a stereotype in each language

struct UmlStereotype {
    WrapperStr uml;

#ifdef WITHCPP
    WrapperStr cpp;
#endif

#ifdef WITHJAVA
    WrapperStr java;
#endif

#ifdef WITHPHP
    WrapperStr php;
#endif

#ifdef WITHPYTHON
    WrapperStr python;
#endif

#ifdef WITHIDL
    WrapperStr idl;
#endif

};

#endif
