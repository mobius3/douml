#ifndef _UMLBASEDEPLOYMENT_H
#define _UMLBASEDEPLOYMENT_H


#include "UmlItem.h"


//  Manage the deployments
class UmlBaseDeployment : public UmlItem
{
protected:
    UmlBaseDeployment(void * id, QByteArray n) : UmlItem(id, n) {};

};

#endif
