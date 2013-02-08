#ifndef _UMLACTIVITYOBJECT_H
#define _UMLACTIVITYOBJECT_H


#include "UmlBaseActivityObject.h"
#include "misc/mystr.h"

class UmlActivityObject : public UmlBaseActivityObject
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityObject(void * id, const WrapperStr & s) : UmlBaseActivityObject(id, s) {
    }

};

#endif
