#ifndef _UMLVIEW_H
#define _UMLVIEW_H


#include "UmlBaseView.h"
#include "misc/mystr.h"

class UmlView : public UmlBaseView
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlView(void * id, const WrapperStr & s) : UmlBaseView(id, s) {
    }

};

#endif
