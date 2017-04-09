#ifndef _UMLACCESSVARIABLEVALUEACTION_H
#define _UMLACCESSVARIABLEVALUEACTION_H


#include "UmlBaseAccessVariableValueAction.h"


class UmlAccessVariableValueAction : public UmlBaseAccessVariableValueAction
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlAccessVariableValueAction(void * id, const QByteArray & s) : UmlBaseAccessVariableValueAction(id, s) {
    }

};

#endif
