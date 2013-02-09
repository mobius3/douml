#ifndef UMLRELATION_H
#define UMLRELATION_H

#include "UmlBaseRelation.h"
//Added by qt3to4:
#include "misc/mystr.h"

class ActualParameter;

// This class manages 'relations', notes that the class 'UmlClassItem'
// is a mother class of the class's children.
// You can modify it as you want (except the constructor)

class UmlRelation : public UmlBaseRelation
{
public:
    UmlRelation(void * id, const WrapperStr & n)
        : UmlBaseRelation(id, n) {};

    static UmlRelation * java2Php(UmlClass * php, UmlClass * java, const char * name);
};

#endif
