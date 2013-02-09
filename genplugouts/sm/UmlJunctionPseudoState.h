#ifndef _UMLJUNCTIONPSEUDOSTATE_H
#define _UMLJUNCTIONPSEUDOSTATE_H


#include "UmlBaseJunctionPseudoState.h"
#include <q3cstring.h>

class UmlClass;
class UmlState;

class UmlJunctionPseudoState : public UmlBaseJunctionPseudoState
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlJunctionPseudoState(void * id) : UmlBaseJunctionPseudoState(id, "") {
    }

    //  generate code for this pseudo state

    virtual void generate(UmlClass * machine, UmlClass * anystate, UmlState * state);

    //  is the target of a transition

    virtual void generate(UmlClass * machine, UmlClass * anystate, UmlState * state, Q3CString & body, Q3CString indent);


protected:
    //  the name of the operation implementing the junction

    Q3CString _oper;

    //  to have different name for the operation implementing the junction

    static int _rank;

};

#endif
