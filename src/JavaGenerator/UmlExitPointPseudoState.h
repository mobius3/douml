#ifndef _UMLEXITPOINTPSEUDOSTATE_H
#define _UMLEXITPOINTPSEUDOSTATE_H


#include "UmlBaseExitPointPseudoState.h"
#include "misc/mystr.h"

class UmlExitPointPseudoState : public UmlBaseExitPointPseudoState
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlExitPointPseudoState(void * id, const WrapperStr & s) : UmlBaseExitPointPseudoState(id, s) {
    }

};

#endif
