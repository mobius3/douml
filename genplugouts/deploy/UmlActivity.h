#ifndef _UMLACTIVITY_H
#define _UMLACTIVITY_H


#include "UmlBaseActivity.h"


class UmlActivity : public UmlBaseActivity
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivity(void * id, const QByteArray & s) : UmlBaseActivity(id, s) {
    }

};

#endif
