#ifndef _UMLJOINPSEUDOSTATE_H
#define _UMLJOINPSEUDOSTATE_H



#include "UmlBaseJoinPseudoState.h"

class UmlJoinPseudoState : public UmlBaseJoinPseudoState
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind();

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlJoinPseudoState(void * id) : UmlBaseJoinPseudoState(id, "") {
    }

};

#endif
