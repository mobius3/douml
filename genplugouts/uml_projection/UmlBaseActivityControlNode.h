#ifndef _UMLBASEACTIVITYCONTROLNODE_H
#define _UMLBASEACTIVITYCONTROLNODE_H


#include "UmlActivityNode.h"
#include <QByteArray>

class UmlBaseActivityControlNode : public UmlActivityNode
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlBaseActivityControlNode(void * id, const QByteArray & s) : UmlActivityNode(id, s) {
    }

};

#endif
