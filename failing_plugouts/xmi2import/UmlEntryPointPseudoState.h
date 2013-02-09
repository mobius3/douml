#ifndef _UMLENTRYPOINTPSEUDOSTATE_H
#define _UMLENTRYPOINTPSEUDOSTATE_H


#include "UmlBaseEntryPointPseudoState.h"


class UmlEntryPointPseudoState : public UmlBaseEntryPointPseudoState
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlEntryPointPseudoState(void * id, const WrapperStr & s) : UmlBaseEntryPointPseudoState(id, s) {
    }

    //  call at end of import : try to solve referenced entry point

    virtual void solve(WrapperStr idref);

};

#endif
