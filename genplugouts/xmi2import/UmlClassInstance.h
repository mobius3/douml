#ifndef _UMLCLASSINSTANCE_H
#define _UMLCLASSINSTANCE_H


#include "UmlBaseClassInstance.h"
#include <q3cstring.h>

class UmlClassInstance : public UmlBaseClassInstance
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlClassInstance(void * id, const Q3CString & s) : UmlBaseClassInstance(id, s) {
    }

};

#endif
