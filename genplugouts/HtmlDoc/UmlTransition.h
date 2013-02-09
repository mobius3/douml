#ifndef _UMLTRANSITION_H
#define _UMLTRANSITION_H


#include <q3cstring.h>
#include "UmlBaseTransition.h"
#include "UmlStateItem.h"

class UmlTransition : public UmlBaseTransition, public UmlStateItem
{
public:
    //returns a string indicating the king of the element
    virtual Q3CString sKind();

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(Q3CString pfix, unsigned int rank, unsigned int level);

    UmlTransition(void * id, const Q3CString & n) : UmlBaseTransition(id, n) {
    }

};

#endif
