#ifndef _UMLSTEREOTYPE_H
#define _UMLSTEREOTYPE_H

#include <QByteArray>


//  Internal class used to know how what code is produced for a stereotype in each language

struct UmlStereotype {
    QByteArray uml;

#ifdef WITHCPP
    QByteArray cpp;
#endif

#ifdef WITHJAVA
    QByteArray java;
#endif

#ifdef WITHIDL
    QByteArray idl;
#endif

};

#endif
