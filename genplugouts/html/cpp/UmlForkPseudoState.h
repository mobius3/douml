#ifndef _UMLFORKPSEUDOSTATE_H
#define _UMLFORKPSEUDOSTATE_H


#include <q3cstring.h>
#include "UmlBaseForkPseudoState.h"

class UmlForkPseudoState : public UmlBaseForkPseudoState
{
public:
    //returns a string indicating the king of the element
    virtual Q3CString sKind();

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlForkPseudoState(void * id) : UmlBaseForkPseudoState(id, "") {
    }

};

#endif
