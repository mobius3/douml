#ifndef _UMLCOMPONENT_H
#define _UMLCOMPONENT_H


#include <q3cstring.h>
#include "UmlBaseComponent.h"

// This class manages 'components'
//
// You can modify it as you want (except the constructor)
class UmlComponent : public UmlBaseComponent
{
public:
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(Q3CString pfix, unsigned int rank, unsigned int level);

    virtual Q3CString sKind();

    UmlComponent(void * id, const Q3CString & n) : UmlBaseComponent(id, n) {};

};

#endif
