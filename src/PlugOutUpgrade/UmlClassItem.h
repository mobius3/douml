#ifndef UMLCLASSITEM_H
#define UMLCLASSITEM_H

#include <q3ptrlist.h>
//Added by qt3to4:
#include "misc/mystr.h"

#include "UmlBaseClassItem.h"

// This class globaly manages class's children including UmlClassExtraMember
// You can modify it as you want (except the constructor)

class UmlClassItem : public UmlBaseClassItem
{
public:
    UmlClassItem(void * id, const WrapperStr & n)
        : UmlBaseClassItem(id, n) {};
};

#endif
