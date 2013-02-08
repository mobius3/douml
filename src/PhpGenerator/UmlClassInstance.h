#ifndef _UMLCLASSINSTANCE_H
#define _UMLCLASSINSTANCE_H


#include "UmlBaseClassInstance.h"
//Added by qt3to4:
#include "misc/mystr.h"

class UmlClassInstance : public UmlBaseClassInstance
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlClassInstance(void * id, const WrapperStr & s) : UmlBaseClassInstance(id, s) {
    }
};

#endif
