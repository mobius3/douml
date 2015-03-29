#ifndef _UMLACTIVITYACTION_H
#define _UMLACTIVITYACTION_H


#include "UmlBaseActivityAction.h"
#include <QByteArray>

class UmlActivityAction : public UmlBaseActivityAction
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityAction(void * id, const QByteArray & s) : UmlBaseActivityAction(id, s) {
    }

};

#endif
