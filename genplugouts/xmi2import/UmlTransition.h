#ifndef _UMLTRANSITION_H
#define _UMLTRANSITION_H


#include "UmlBaseTransition.h"
#include "UmlStateItem.h"

#include <q3valuelist.h>

class FileIn;
class Token;
class UmlItem;

class UmlTransition : public UmlBaseTransition, public UmlStateItem
{
public:
    UmlTransition(void * id, const WrapperStr & n) : UmlBaseTransition(id, n) {
    }

    static void init();

    static void solveThem();

    //import the transition starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

    struct Transition {
        WrapperStr id;

        WrapperStr name;

        WrapperStr source;

        WrapperStr target;

        WrapperStr guard;

        WrapperStr effect;

        WrapperStr trigger;

        WrapperStr triggerRef;

        WrapperStr kind;

    };



protected:
    static Q3ValueList<Transition> All;

};

#endif
