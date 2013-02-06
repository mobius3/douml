#ifndef _UMLCOMPONENT_H
#define _UMLCOMPONENT_H


#include "UmlBaseComponent.h"
#include <q3cstring.h>

// This class manages 'components'
//
// You can modify it as you want (except the constructor)
class UmlComponent : public UmlBaseComponent
{
public:
    UmlComponent(void * id, const Q3CString & n) : UmlBaseComponent(id, n) {};

    virtual int orderWeight();

};

#endif
