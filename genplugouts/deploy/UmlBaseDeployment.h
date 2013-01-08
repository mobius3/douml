#ifndef _UMLBASEDEPLOYMENT_H
#define _UMLBASEDEPLOYMENT_H


#include "UmlItem.h"
#include <q3cstring.h>

//  Manage the deployments
class UmlBaseDeployment : public UmlItem
{
protected:
    UmlBaseDeployment(void * id, Q3CString n) : UmlItem(id, n) {};

};

#endif
