#ifndef UMLCLASSMEMBER_H
#define UMLCLASSMEMBER_H

#include "UmlBaseClassMember.h"
//Added by qt3to4:
#include <Q3CString>

// This class globaly manages class's operations, relations, attributes
// and sub-classes
// You can modify it as you want (except the constructor)

class UmlClassMember : public UmlBaseClassMember {
  public:
    UmlClassMember(void * id, const Q3CString & n)
      : UmlBaseClassMember(id, n) {};
};

#endif
