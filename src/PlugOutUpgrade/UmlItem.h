#ifndef UMLITEM_H
#define UMLITEM_H

#include "UmlBaseItem.h"
//Added by qt3to4:
#include "misc/mystr.h"

// This class is a mother class for all the other Uml* classes, this
// allows to generalize their management, declare virtual operations etc ...
// You can modify it as you want (except the constructor)

class UmlItem : public UmlBaseItem
{
public:
    UmlItem(void * id, const WrapperStr & n)
        : UmlBaseItem(id, n) {};
    virtual ~UmlItem();

    virtual void rename_jdk5();
    void move_after(anItemKind k, const char * name);
    virtual void replace_friend();
};

#endif
