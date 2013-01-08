#ifndef _UMLEXPANSIONREGION_H
#define _UMLEXPANSIONREGION_H


#include "UmlBaseExpansionRegion.h"
#include <q3cstring.h>

class UmlExpansionRegion : public UmlBaseExpansionRegion
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlExpansionRegion(void * id, const Q3CString & s) : UmlBaseExpansionRegion(id, s) {
    }

};

#endif
