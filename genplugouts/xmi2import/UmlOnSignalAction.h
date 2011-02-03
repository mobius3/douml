#ifndef _UMLONSIGNALACTION_H
#define _UMLONSIGNALACTION_H


#include "UmlBaseOnSignalAction.h"
#include <q3cstring.h>

class FileIn;
class Token;

class UmlOnSignalAction : public UmlBaseOnSignalAction {
  protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
     UmlOnSignalAction(void * id, const Q3CString & s) : UmlBaseOnSignalAction(id, s) {
    }


  public:
    //  call at end of import : try to solve signal
    
    virtual void solve(Q3CString idref);


  protected:
    //import the activity signal action starting by 'tk'
    
    virtual void import_it(FileIn & in, Token & token);

};

#endif
