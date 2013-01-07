#ifndef _UMLENTRYPOINTPSEUDOSTATE_H
#define _UMLENTRYPOINTPSEUDOSTATE_H


#include "UmlBaseEntryPointPseudoState.h"
#include <q3cstring.h>

class UmlEntryPointPseudoState : public UmlBaseEntryPointPseudoState
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlEntryPointPseudoState(void * id, const Q3CString & s) : UmlBaseEntryPointPseudoState(id, s) {
    }

};

#endif
