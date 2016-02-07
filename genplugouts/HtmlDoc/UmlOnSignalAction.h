#ifndef _UMLONSIGNALACTION_H
#define _UMLONSIGNALACTION_H



#include "UmlBaseOnSignalAction.h"

class UmlOnSignalAction : public UmlBaseOnSignalAction
{
public:
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level) override;


protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlOnSignalAction(void * id, const QByteArray & s) : UmlBaseOnSignalAction(id, s) {
    }

};

#endif
