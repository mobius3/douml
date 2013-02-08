#ifndef _UMLONSIGNALACTION_H
#define _UMLONSIGNALACTION_H


#include <q3cstring.h>
#include "UmlBaseOnSignalAction.h"

class UmlOnSignalAction : public UmlBaseOnSignalAction
{
public:
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(Q3CString pfix, unsigned int rank, unsigned int level);


protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlOnSignalAction(void * id, const Q3CString & s) : UmlBaseOnSignalAction(id, s) {
    }

};

#endif
