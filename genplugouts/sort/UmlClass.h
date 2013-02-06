#ifndef _UMLCLASS_H
#define _UMLCLASS_H


#include "UmlBaseClass.h"
#include <q3cstring.h>

// This class manages 'classes', notes that the class 'ClassItem'
// is a mother class of the class's children.
//
// You can modify it as you want (except the constructor)
class UmlClass : public UmlBaseClass
{
public:
    UmlClass(void * id, const Q3CString & n) : UmlBaseClass(id, n) {};

    virtual int orderWeight();

};

#endif
