#ifndef _UMLACCESSVARIABLEVALUEACTION_H
#define _UMLACCESSVARIABLEVALUEACTION_H


#include "UmlBaseAccessVariableValueAction.h"
#include <q3cstring.h>

class UmlAccessVariableValueAction : public UmlBaseAccessVariableValueAction
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlAccessVariableValueAction(void * id, const Q3CString & s) : UmlBaseAccessVariableValueAction(id, s) {
    }

};

#endif
