#ifndef _UMLITEM_H
#define _UMLITEM_H


#include "UmlBaseItem.h"
#include <q3cstring.h>
#include <q3ptrvector.h>
//Added by qt3to4:
#include <Q3PtrCollection>


// This class is a mother class for all the other Uml* classes, this
// allows to generalize their management, declare virtual operations etc ...
//
// You can modify it as you want (except the constructor)
class UmlItem : public UmlBaseItem
{
public:
    UmlItem(void * id, const Q3CString & n) : UmlBaseItem(id, n) {};

    virtual ~UmlItem();

    virtual void sort();

    virtual int orderWeight();

    void sortChildren();

};

class VectorOfUmlItem : public Q3PtrVector<UmlItem>
{
public:
    int compareItems(Q3PtrCollection::Item d1, Q3PtrCollection::Item d2);

};

#endif
