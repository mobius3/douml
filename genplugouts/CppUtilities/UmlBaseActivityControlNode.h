#ifndef _UMLBASEACTIVITYCONTROLNODE_H
#define _UMLBASEACTIVITYCONTROLNODE_H


#include "UmlActivityNode.h"
#include <q3cstring.h>

class UmlBaseActivityControlNode : public UmlActivityNode
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlBaseActivityControlNode(void * id, const Q3CString & s) : UmlActivityNode(id, s) {
    }

};

#endif
