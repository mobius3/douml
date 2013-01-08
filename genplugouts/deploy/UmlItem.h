#ifndef _UMLITEM_H
#define _UMLITEM_H


#include "UmlBaseItem.h"
#include <q3cstring.h>

class UmlDeploymentView;

// This class is a mother class for all the other Uml* classes, this
// allows to generalize their management, declare virtual operations etc ...
//
// You can modify it as you want (except the constructor)
class UmlItem : public UmlBaseItem
{
public:
    UmlItem(void * id, const Q3CString & n) : UmlBaseItem(id, n) {};

    virtual ~UmlItem();

    virtual void deploy();

    virtual void deploy(UmlDeploymentView * view);

    virtual int deployable();

};

#endif
