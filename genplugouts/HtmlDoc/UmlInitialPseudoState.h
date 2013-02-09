#ifndef _UMLINITIALPSEUDOSTATE_H
#define _UMLINITIALPSEUDOSTATE_H


#include <q3cstring.h>
#include "UmlBaseInitialPseudoState.h"

class UmlInitialPseudoState : public UmlBaseInitialPseudoState
{
public:
    //returns a string indicating the king of the element
    virtual Q3CString sKind();

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlInitialPseudoState(void * id) : UmlBaseInitialPseudoState(id, "") {
    }

};

#endif
