#ifndef _UMLBUILTIN_H
#define _UMLBUILTIN_H
#include <QByteArray>



//  Internal class used to memorize the types defined through the first 'generation settings' tab

struct UmlBuiltin {
    QByteArray uml;

#ifdef WITHCPP
    QByteArray cpp;

    QByteArray cpp_in;

    QByteArray cpp_out;

    QByteArray cpp_inout;
#endif

    QByteArray cpp_return;

#ifdef WITHJAVA
    QByteArray java;
#endif

#ifdef WITHIDL
    QByteArray idl;
#endif

};

#endif
