#ifndef _UMLACCESSVARIABLEVALUEACTION_H
#define _UMLACCESSVARIABLEVALUEACTION_H


#include <q3cstring.h>
#include "UmlBaseAccessVariableValueAction.h"

class UmlAccessVariableValueAction : public UmlBaseAccessVariableValueAction
{
public:
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(Q3CString pfix, unsigned int rank, unsigned int level);


protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlAccessVariableValueAction(void * id, const Q3CString & s) : UmlBaseAccessVariableValueAction(id, s) {
    }

};

#endif
