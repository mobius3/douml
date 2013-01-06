#ifndef _UMLACTIVITY_H
#define _UMLACTIVITY_H


#include "UmlBaseActivity.h"
#include <q3cstring.h>

class UmlActivity : public UmlBaseActivity
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivity(void * id, const Q3CString & s) : UmlBaseActivity(id, s) {
    }

};

#endif
