#ifndef _UMLTERMINATEPSEUDOSTATE_H
#define _UMLTERMINATEPSEUDOSTATE_H


#include <q3cstring.h>
#include "UmlBaseTerminatePseudoState.h"

class UmlTerminatePseudoState : public UmlBaseTerminatePseudoState
{
public:
    //returns a string indicating the king of the element
    virtual Q3CString sKind();

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlTerminatePseudoState(void * id) : UmlBaseTerminatePseudoState(id, "") {
    }

};

#endif
