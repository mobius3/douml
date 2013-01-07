#ifndef _UMLBASEVIEW_H
#define _UMLBASEVIEW_H


#include "UmlItem.h"
#include <q3cstring.h>

class UmlBaseView : public UmlItem
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlBaseView(void * id, const Q3CString & s) : UmlItem(id, s) {
    }

};

#endif
