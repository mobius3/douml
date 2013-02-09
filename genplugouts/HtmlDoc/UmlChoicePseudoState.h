#ifndef _UMLCHOICEPSEUDOSTATE_H
#define _UMLCHOICEPSEUDOSTATE_H


#include <q3cstring.h>
#include "UmlBaseChoicePseudoState.h"

class UmlChoicePseudoState : public UmlBaseChoicePseudoState
{
public:
    //returns a string indicating the king of the element
    virtual Q3CString sKind();

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlChoicePseudoState(void * id) : UmlBaseChoicePseudoState(id, "") {
    }

};

#endif
