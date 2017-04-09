#ifndef _UMLBASEACTIVITYNODE_H
#define _UMLBASEACTIVITYNODE_H


#include "UmlItem.h"
#include <QByteArray>

class UmlBaseActivityNode : public UmlItem
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlBaseActivityNode(void * id, const QByteArray & s) : UmlItem(id, s) {
    }

};

#endif
