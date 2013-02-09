#ifndef _UMLACTIVITY_H
#define _UMLACTIVITY_H


#include "UmlBaseActivity.h"
#include "misc/mystr.h"

class UmlActivity : public UmlBaseActivity
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivity(void * id, const WrapperStr & s) : UmlBaseActivity(id, s) {
    }

};

#endif
