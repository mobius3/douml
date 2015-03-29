#ifndef _UMLCHOICEPSEUDOSTATE_H
#define _UMLCHOICEPSEUDOSTATE_H


#include "UmlBaseChoicePseudoState.h"
#include <QByteArray>

class UmlClass;
class UmlState;

class UmlChoicePseudoState : public UmlBaseChoicePseudoState
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlChoicePseudoState(void * id) : UmlBaseChoicePseudoState(id, "") {
    }

    //  is the target of a transition
    virtual void generate(UmlClass * machine, UmlClass * anystate, UmlState * state, QByteArray & body, QByteArray indent);

};

#endif
