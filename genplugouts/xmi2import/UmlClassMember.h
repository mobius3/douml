#ifndef _UMLCLASSMEMBER_H
#define _UMLCLASSMEMBER_H



#include "UmlBaseClassMember.h"

// This class globaly manages class's relations, attributes, operations
// and sub-classes
//
// You can modify it as you want (except the constructor)
class UmlClassMember : public UmlBaseClassMember
{
public:
    UmlClassMember(void * id, const WrapperStr & n) : UmlBaseClassMember(id, n) {};

    void setVisibility(WrapperStr v);

};

#endif
