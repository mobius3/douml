#ifndef _UMLINTERRUPTIBLEACTIVITYREGION_H
#define _UMLINTERRUPTIBLEACTIVITYREGION_H


#include "UmlBaseInterruptibleActivityRegion.h"
#include <q3cstring.h>

class UmlInterruptibleActivityRegion : public UmlBaseInterruptibleActivityRegion
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlInterruptibleActivityRegion(void * id, const Q3CString & s) : UmlBaseInterruptibleActivityRegion(id, s) {
    }

    //returns a string indicating the king of the element
    virtual Q3CString sKind();

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(Q3CString pfix, unsigned int rank, unsigned int level);

};

#endif
