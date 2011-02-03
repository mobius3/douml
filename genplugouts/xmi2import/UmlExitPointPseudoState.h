#ifndef _UMLEXITPOINTPSEUDOSTATE_H
#define _UMLEXITPOINTPSEUDOSTATE_H


#include "UmlBaseExitPointPseudoState.h"
#include <q3cstring.h>

class UmlExitPointPseudoState : public UmlBaseExitPointPseudoState {
  public:
    //  the constructor, do not call it yourself !!!!!!!!!!
     UmlExitPointPseudoState(void * id, const Q3CString & s) : UmlBaseExitPointPseudoState(id, s) {
    }

    //  call at end of import : try to solve referenced exit point
    
    virtual void solve(Q3CString idref);

};

#endif
