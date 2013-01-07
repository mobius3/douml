#ifndef _UMLJUNCTIONPSEUDOSTATE_H
#define _UMLJUNCTIONPSEUDOSTATE_H


#include <q3cstring.h>
#include "UmlBaseJunctionPseudoState.h"

class UmlJunctionPseudoState : public UmlBaseJunctionPseudoState
{
public:
    //returns a string indicating the king of the element
    virtual Q3CString sKind();

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlJunctionPseudoState(void * id) : UmlBaseJunctionPseudoState(id, "") {
    }

};

#endif
