#ifndef _UMLACCESSVARIABLEVALUEACTION_H
#define _UMLACCESSVARIABLEVALUEACTION_H


#include "UmlBaseAccessVariableValueAction.h"
#include "misc/mystr.h"

class UmlAccessVariableValueAction : public UmlBaseAccessVariableValueAction
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlAccessVariableValueAction(void * id, const WrapperStr & s) : UmlBaseAccessVariableValueAction(id, s) {
    }

};

#endif
