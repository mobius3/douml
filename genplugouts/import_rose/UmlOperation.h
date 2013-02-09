#ifndef _UMLOPERATION_H
#define _UMLOPERATION_H


#include "UmlBaseOperation.h"
#include <q3cstring.h>
#include <q3dict.h>

class File;
class UmlClass;

// This class manages 'operations', notes that the class 'UmlClassItem'
// is a mother class of all the class's children.
//
// You can modify it as you want (except the constructor)
class UmlOperation : public UmlBaseOperation
{
public:
    UmlOperation(void * id, const Q3CString & n) : UmlBaseOperation(id, n) {
        cpt[kind()] += 1;
    };

    static void import(File & f, UmlClass * parent);


private:
    void import(File & f);

    void importParameters(File & f);

    void importExceptions(File & f);

    void cplusplus(Q3Dict<Q3CString> & prop);

    void oracle8(Q3Dict<Q3CString> & prop);

    void corba(Q3Dict<Q3CString> & prop);

    void java(Q3Dict<Q3CString> & prop);

};

#endif
