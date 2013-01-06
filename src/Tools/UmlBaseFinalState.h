#ifndef _UMLBASEFINALSTATE_H
#define _UMLBASEFINALSTATE_H


#include "UmlPseudoState.h"
#include "anItemKind.h"
#include <q3cstring.h>

class UmlFinalState;
class UmlItem;

class UmlBaseFinalState : public UmlPseudoState
{
public:
    // returns a new final state created under 'parent'
    //
    // In case it cannot be created ('parent' cannot contain it etc ...)
    // return 0 in C++ and produce a RuntimeException in Java

    static UmlFinalState * create(UmlItem * parent);

    // returns the kind of the item
    virtual anItemKind kind();


protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlBaseFinalState(void * id, const Q3CString & s) : UmlPseudoState(id, s) {
    }

};

#endif
