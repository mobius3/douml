#ifndef _UMLPARAMETERSET_H
#define _UMLPARAMETERSET_H


#include "UmlBaseParameterSet.h"
#include <q3cstring.h>

class UmlParameterSet : public UmlBaseParameterSet
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlParameterSet(void * id, const Q3CString & s) : UmlBaseParameterSet(id, s) {
    }

};

#endif
