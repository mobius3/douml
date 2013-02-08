#ifndef _UMLCLASSMEMBER_H
#define _UMLCLASSMEMBER_H


#include <q3cstring.h>
#include "UmlBaseClassMember.h"

// This class globaly manages class's relations, attributes, operations
// and sub-classes
//
// You can modify it as you want (except the constructor)
class UmlClassMember : public UmlBaseClassMember
{
public:
    UmlClassMember(void * id, const Q3CString & n) : UmlBaseClassMember(id, n) {};

    void annotation_constraint();

};

#endif
