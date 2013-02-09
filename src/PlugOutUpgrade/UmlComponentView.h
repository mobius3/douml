#ifndef UMLCOMPONENTVIEW_H
#define UMLCOMPONENTVIEW_H

#include "UmlBaseComponentView.h"
//Added by qt3to4:
#include "misc/mystr.h"

// This class manages 'component view'
// You can modify it as you want (except the constructor)

class UmlComponentView : public UmlBaseComponentView
{
public:
    UmlComponentView(void * id, const WrapperStr & n)
        : UmlBaseComponentView(id, n) {};
};

#endif
