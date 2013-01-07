#ifndef _UMLBASEACTIVITYNODE_H
#define _UMLBASEACTIVITYNODE_H


#include "UmlItem.h"
#include <q3cstring.h>

class UmlBaseActivityNode : public UmlItem
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlBaseActivityNode(void * id, const Q3CString & s) : UmlItem(id, s) {
    }

};

#endif
