#ifndef _UMLINTERRUPTIBLEACTIVITYREGION_H
#define _UMLINTERRUPTIBLEACTIVITYREGION_H


#include "UmlBaseInterruptibleActivityRegion.h"
#include <QByteArray>

class UmlInterruptibleActivityRegion : public UmlBaseInterruptibleActivityRegion
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlInterruptibleActivityRegion(void * id, const QByteArray & s) : UmlBaseInterruptibleActivityRegion(id, s) {
    }

};

#endif
