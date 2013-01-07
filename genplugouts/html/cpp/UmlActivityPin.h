#ifndef _UMLACTIVITYPIN_H
#define _UMLACTIVITYPIN_H


#include "UmlBaseActivityPin.h"
#include <q3cstring.h>

class UmlActivityPin : public UmlBaseActivityPin
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityPin(void * id, const Q3CString & s) : UmlBaseActivityPin(id, s) {
    }

    //returns a string indicating the king of the element
    virtual Q3CString sKind();

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(Q3CString pfix, unsigned int rank, unsigned int level);

};

#endif
