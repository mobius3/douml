#ifndef _UMLACTIVITYACTION_H
#define _UMLACTIVITYACTION_H


#include "UmlBaseActivityAction.h"
#include <q3cstring.h>

class UmlActivityAction : public UmlBaseActivityAction
{
public:
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html();


protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityAction(void * id, const Q3CString & s) : UmlBaseActivityAction(id, s) {
    }

};

#endif
