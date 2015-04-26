#ifndef _UMLACTIVITYPIN_H
#define _UMLACTIVITYPIN_H


#include "UmlBaseActivityPin.h"


class UmlActivityPin : public UmlBaseActivityPin
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityPin(void * id, const QByteArray & s) : UmlBaseActivityPin(id, s) {
    }
    virtual ~UmlActivityPin(){}

};

#endif
