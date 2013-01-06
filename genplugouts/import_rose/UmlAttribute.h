#ifndef _UMLATTRIBUTE_H
#define _UMLATTRIBUTE_H


#include "UmlBaseAttribute.h"
#include <q3cstring.h>
#include <q3dict.h>

class File;
class UmlClass;

// This class manages 'attribute', notes that the class 'UmlClassItem'
// is a mother class of the class's children.
//
// You can modify it as you want (except the constructor)
class UmlAttribute : public UmlBaseAttribute
{
public:
    UmlAttribute(void * id, const Q3CString & n) :  UmlBaseAttribute(id, n) {
        cpt[kind()] += 1;
    };


private:
    void import(File & f);


public:
    static void import(File & f, UmlClass * parent);

    static void importIdlConstant(UmlClass * parent, const Q3CString & id, const Q3CString & s, const Q3CString & doc, Q3Dict<Q3CString> & prop);


private:
    void cplusplus(Q3Dict<Q3CString> & prop);

    void oracle8(Q3Dict<Q3CString> & prop);

    void corba(Q3Dict<Q3CString> & prop);

    void java(Q3Dict<Q3CString> & prop);

};

#endif
