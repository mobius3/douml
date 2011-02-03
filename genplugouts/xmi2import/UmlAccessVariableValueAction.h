#ifndef _UMLACCESSVARIABLEVALUEACTION_H
#define _UMLACCESSVARIABLEVALUEACTION_H


#include "UmlBaseAccessVariableValueAction.h"
#include <q3cstring.h>

class FileIn;
class Token;

class UmlAccessVariableValueAction : public UmlBaseAccessVariableValueAction {
  protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
     UmlAccessVariableValueAction(void * id, const Q3CString & s) : UmlBaseAccessVariableValueAction(id, s) {
    }

    virtual void import_it(FileIn & in, Token & token);

    void setVariable(Q3CString idref);


  public:
    //  call at end of import : try to solve var
    virtual void solve(Q3CString idref);

};

#endif
