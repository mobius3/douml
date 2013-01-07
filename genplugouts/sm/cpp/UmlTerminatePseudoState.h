#ifndef _UMLTERMINATEPSEUDOSTATE_H
#define _UMLTERMINATEPSEUDOSTATE_H


#include "UmlBaseTerminatePseudoState.h"
#include <q3cstring.h>

class UmlClass;
class UmlState;

class UmlTerminatePseudoState : public UmlBaseTerminatePseudoState
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlTerminatePseudoState(void * id) : UmlBaseTerminatePseudoState(id, "") {
    }

    virtual void generate(UmlClass * machine, UmlClass * anystate, UmlState * state, Q3CString & body, Q3CString indent);

};

#endif
