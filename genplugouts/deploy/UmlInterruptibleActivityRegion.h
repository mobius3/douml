#ifndef _UMLINTERRUPTIBLEACTIVITYREGION_H
#define _UMLINTERRUPTIBLEACTIVITYREGION_H


#include "UmlBaseInterruptibleActivityRegion.h"
#include <q3cstring.h>

class UmlInterruptibleActivityRegion : public UmlBaseInterruptibleActivityRegion
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlInterruptibleActivityRegion(void * id, const Q3CString & s) : UmlBaseInterruptibleActivityRegion(id, s) {
    }

};

#endif
