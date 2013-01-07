#ifndef _UMLVIEW_H
#define _UMLVIEW_H


#include "UmlBaseView.h"
#include <q3cstring.h>

class UmlView : public UmlBaseView
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlView(void * id, const Q3CString & s) : UmlBaseView(id, s) {
    }

};

#endif
