#ifndef _UMLACTIVITYPIN_H
#define _UMLACTIVITYPIN_H


#include "UmlBaseActivityPin.h"
#include <q3cstring.h>

class UmlActivityPin : public UmlBaseActivityPin
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityPin(void * id, const Q3CString & s) : UmlBaseActivityPin(id, s) {
    }

};

#endif
