#ifndef _UMLACTIVITYCONTROLNODE_H
#define _UMLACTIVITYCONTROLNODE_H


#include "UmlBaseActivityControlNode.h"
#include <QByteArray>

class UmlActivityControlNode : public UmlBaseActivityControlNode
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityControlNode(void * id, const QByteArray & s) : UmlBaseActivityControlNode(id, s) {
    }

};

#endif
