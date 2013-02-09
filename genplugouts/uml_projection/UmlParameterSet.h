#ifndef _UMLPARAMETERSET_H
#define _UMLPARAMETERSET_H


#include "UmlBaseParameterSet.h"
#include "UmlActivityItem.h"
#include <q3cstring.h>

class UmlParameterSet : public UmlBaseParameterSet, public UmlActivityItem
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlParameterSet(void * id, const Q3CString & s) : UmlBaseParameterSet(id, s) {
    }

};

#endif
