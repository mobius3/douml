#ifndef _UMLACTIVITYOBJECT_H
#define _UMLACTIVITYOBJECT_H


#include "UmlBaseActivityObject.h"
#include <q3cstring.h>

class UmlActivityObject : public UmlBaseActivityObject
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityObject(void * id, const Q3CString & s) : UmlBaseActivityObject(id, s) {
    }

    //returns a string indicating the king of the element
    virtual Q3CString sKind();

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(Q3CString pfix, unsigned int rank, unsigned int level);

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html_internal(Q3CString pfix, unsigned int rank, unsigned int level);

};

#endif
