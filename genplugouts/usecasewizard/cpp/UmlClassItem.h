#ifndef _UMLCLASSITEM_H
#define _UMLCLASSITEM_H


#include "UmlBaseClassItem.h"
#include <q3cstring.h>

// This class globaly manages class's children including UmlClassExtraMember
//
// You can modify it as you want (except the constructor)
class UmlClassItem : public UmlBaseClassItem
{
public:
    UmlClassItem(void * id, const Q3CString & n) : UmlBaseClassItem(id, n) {};

};

#endif
