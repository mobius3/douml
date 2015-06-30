#ifndef _UMLREGION_H
#define _UMLREGION_H


#include "UmlBaseRegion.h"
#include "UmlStateItem.h"
#include <QByteArray>

class UmlRegion : public UmlBaseRegion, public UmlStateItem
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlRegion(void * id, const QByteArray & s) : UmlBaseRegion(id, s) {
    }

};

#endif
