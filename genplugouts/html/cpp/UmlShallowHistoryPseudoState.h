#ifndef _UMLSHALLOWHISTORYPSEUDOSTATE_H
#define _UMLSHALLOWHISTORYPSEUDOSTATE_H


#include <q3cstring.h>
#include "UmlBaseShallowHistoryPseudoState.h"

class UmlShallowHistoryPseudoState : public UmlBaseShallowHistoryPseudoState
{
public:
    //returns a string indicating the king of the element
    virtual Q3CString sKind();

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlShallowHistoryPseudoState(void * id) : UmlBaseShallowHistoryPseudoState(id, "") {
    }

};

#endif
