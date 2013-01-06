#ifndef _UMLFINALSTATE_H
#define _UMLFINALSTATE_H


#include "UmlBaseFinalState.h"
#include <q3cstring.h>

class UmlClass;
class UmlState;

class UmlFinalState : public UmlBaseFinalState
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlFinalState(void * id) : UmlBaseFinalState(id, "") {
    }

    //  is the target of a transition

    virtual void generate(UmlClass * machine, UmlClass * anystate, UmlState * state, Q3CString & body, Q3CString indent);

};

#endif
