#ifndef _UMLENTRYPOINTPSEUDOSTATE_H
#define _UMLENTRYPOINTPSEUDOSTATE_H


#include "UmlBaseEntryPointPseudoState.h"
#include "misc/mystr.h"

class UmlEntryPointPseudoState : public UmlBaseEntryPointPseudoState
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlEntryPointPseudoState(void * id, const WrapperStr & s) : UmlBaseEntryPointPseudoState(id, s) {
    }

};

#endif
