#ifndef _UMLACCESSVARIABLEVALUEACTION_H
#define _UMLACCESSVARIABLEVALUEACTION_H


#include "UmlBaseAccessVariableValueAction.h"


class FileIn;
class Token;

class UmlAccessVariableValueAction : public UmlBaseAccessVariableValueAction
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlAccessVariableValueAction(void * id, const WrapperStr & s) : UmlBaseAccessVariableValueAction(id, s) {
    }

    virtual void import_it(FileIn & in, Token & token);

    void setVariable(WrapperStr idref);


public:
    //  call at end of import : try to solve var
    virtual void solve(WrapperStr idref);

};

#endif
