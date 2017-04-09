#ifndef _UMLEXITPOINTPSEUDOSTATE_H
#define _UMLEXITPOINTPSEUDOSTATE_H


#include "UmlBaseExitPointPseudoState.h"


class UmlExitPointPseudoState : public UmlBaseExitPointPseudoState
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlExitPointPseudoState(void * id, const QByteArray & s) : UmlBaseExitPointPseudoState(id, s) {
    }

};

#endif
