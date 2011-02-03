#ifndef _UMLFLOW_H
#define _UMLFLOW_H


#include "UmlBaseFlow.h"
#include "UmlActivityItem.h"
#include <q3cstring.h>
#include <q3valuelist.h>

class FileIn;
class Token;
class UmlItem;

class UmlFlow : public UmlBaseFlow, public UmlActivityItem {
  public:
     UmlFlow(void * id, const Q3CString & n) : UmlBaseFlow(id, n) {
    }

    static void init();

    static void solveThem();

    //import the flow starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

    struct Flow {
        Q3CString id;

        Q3CString name;

        bool interrupt;

        Q3CString source;

        Q3CString target;

        Q3CString selection;

        Q3CString transformation;

        Q3CString weight;

        Q3CString guard;

    };
    
    

  protected:
    static Q3ValueList<Flow> All;

};

#endif
