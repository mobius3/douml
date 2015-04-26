#ifndef _UMLCOMPONENT_H
#define _UMLCOMPONENT_H



#include "UmlBaseComponent.h"

// This class manages 'components'
//
// You can modify it as you want (except the constructor)
class UmlComponent : public UmlBaseComponent
{
public:
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level);

    virtual QByteArray sKind();

    UmlComponent(void * id, const QByteArray & n) : UmlBaseComponent(id, n) {};

};

#endif
