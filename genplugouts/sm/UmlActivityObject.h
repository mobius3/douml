#ifndef _UMLACTIVITYOBJECT_H
#define _UMLACTIVITYOBJECT_H


#include "UmlBaseActivityObject.h"
#include <q3cstring.h>

class UmlActivityObject : public UmlBaseActivityObject
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityObject(void * id, const Q3CString & s) : UmlBaseActivityObject(id, s) {
    }

};

#endif
