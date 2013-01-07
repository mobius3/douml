#ifndef _UMLSTATEACTION_H
#define _UMLSTATEACTION_H


#include <q3cstring.h>
#include "UmlBaseStateAction.h"
#include "UmlStateItem.h"

class UmlStateAction : public UmlBaseStateAction, public UmlStateItem
{
public:
    //returns a string indicating the king of the element
    virtual Q3CString sKind();

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(Q3CString pfix, unsigned int rank, unsigned int level);

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlStateAction(void * id) : UmlBaseStateAction(id, "") {
    }

};

#endif
