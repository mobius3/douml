#ifndef _UMLONSIGNALACTION_H
#define _UMLONSIGNALACTION_H


#include "UmlBaseOnSignalAction.h"
#include <QByteArray>

class UmlOnSignalAction : public UmlBaseOnSignalAction
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlOnSignalAction(void * id, const QByteArray & s) : UmlBaseOnSignalAction(id, s) {
    }

};

#endif
