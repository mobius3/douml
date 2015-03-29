#ifndef _UMLENTRYPOINTPSEUDOSTATE_H
#define _UMLENTRYPOINTPSEUDOSTATE_H


#include "UmlBaseEntryPointPseudoState.h"
#include <QByteArray>

class UmlClass;
class UmlState;

class UmlEntryPointPseudoState : public UmlBaseEntryPointPseudoState
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlEntryPointPseudoState(void * id, const QByteArray & s) : UmlBaseEntryPointPseudoState(id, s) {
    }

    virtual void generate(UmlClass * machine, UmlClass * anystate, UmlState * state, QByteArray & body, QByteArray indent);

};

#endif
