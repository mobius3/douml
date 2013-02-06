#ifndef _UMLCOMPONENTVIEW_H
#define _UMLCOMPONENTVIEW_H


#include "UmlBaseComponentView.h"
#include <q3cstring.h>

// This class manages 'component view'
//
// You can modify it as you want (except the constructor)
class UmlComponentView : public UmlBaseComponentView
{
public:
    virtual void sort();

    UmlComponentView(void * id, const Q3CString & n) : UmlBaseComponentView(id, n) {};

    virtual int orderWeight();

};

#endif
