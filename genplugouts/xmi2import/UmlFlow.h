#ifndef _UMLFLOW_H
#define _UMLFLOW_H


#include "UmlBaseFlow.h"
#include "UmlActivityItem.h"

#include <q3valuelist.h>

class FileIn;
class Token;
class UmlItem;

class UmlFlow : public UmlBaseFlow, public UmlActivityItem
{
public:
    UmlFlow(void * id, const WrapperStr & n) : UmlBaseFlow(id, n) {
    }

    static void init();

    static void solveThem();

    //import the flow starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

    struct Flow {
        WrapperStr id;

        WrapperStr name;

        bool interrupt;

        WrapperStr source;

        WrapperStr target;

        WrapperStr selection;

        WrapperStr transformation;

        WrapperStr weight;

        WrapperStr guard;

    };



protected:
    static Q3ValueList<Flow> All;

};

#endif
