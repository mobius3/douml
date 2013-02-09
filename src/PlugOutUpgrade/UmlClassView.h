#ifndef UMLCLASSVIEW_H
#define UMLCLASSVIEW_H

#include "UmlBaseClassView.h"
//Added by qt3to4:
#include "misc/mystr.h"

// This class manages 'class view'
// You can modify it as you want (except the constructor)

class UmlClassView : public UmlBaseClassView
{
public:
    UmlClassView(void * id, const WrapperStr & n)
        : UmlBaseClassView(id, n) {};

    virtual void replace_friend();
};

#endif
