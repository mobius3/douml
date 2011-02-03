#ifndef _UMLTRANSITION_H
#define _UMLTRANSITION_H


#include "UmlBaseTransition.h"
#include "UmlStateItem.h"
#include <q3cstring.h>
#include <q3valuelist.h>

class FileIn;
class Token;
class UmlItem;

class UmlTransition : public UmlBaseTransition, public UmlStateItem {
  public:
     UmlTransition(void * id, const Q3CString & n) : UmlBaseTransition(id, n) {
    }

    static void init();

    static void solveThem();

    //import the transition starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

    struct Transition {
        Q3CString id;

        Q3CString name;

        Q3CString source;

        Q3CString target;

        Q3CString guard;

        Q3CString effect;

        Q3CString trigger;

        Q3CString triggerRef;

        Q3CString kind;

    };
    
    

  protected:
    static Q3ValueList<Transition> All;

};

#endif
