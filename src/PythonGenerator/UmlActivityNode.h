#ifndef _UMLACTIVITYNODE_H
#define _UMLACTIVITYNODE_H


#include "UmlBaseActivityNode.h"
#include "UmlActivityItem.h"
#include <q3cstring.h>

class UmlActivityNode : public UmlBaseActivityNode, public UmlActivityItem
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityNode(void * id, const Q3CString & s) : UmlBaseActivityNode(id, s) {
    }

};

#endif
