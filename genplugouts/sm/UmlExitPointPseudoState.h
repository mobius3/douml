#ifndef _UMLEXITPOINTPSEUDOSTATE_H
#define _UMLEXITPOINTPSEUDOSTATE_H


#include "UmlBaseExitPointPseudoState.h"
#include <QByteArray>

class UmlClass;
class UmlState;

class UmlExitPointPseudoState : public UmlBaseExitPointPseudoState
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlExitPointPseudoState(void * id, const QByteArray & s) : UmlBaseExitPointPseudoState(id, s) {
    }

    virtual void init(UmlClass * mother, QByteArray path, QByteArray pretty_path, UmlState * state);

    //  generate code for this pseudo state

    virtual void generate(UmlClass * machine, UmlClass * anystate, UmlState * state);

    //  is the target of a transition

    virtual void generate(UmlClass * machine, UmlClass * anystate, UmlState * state, QByteArray & body, QByteArray indent);


protected:
    //  the name of the operation implementing the exit point

    QByteArray _oper;

    //  to have different name for the operation implementing the exit point

    static int _rank;

};

#endif
