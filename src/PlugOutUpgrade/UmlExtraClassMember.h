#ifndef UMLEXTRACLASSMEMBER_H
#define UMLEXTRACLASSMEMBER_H

#include "UmlBaseExtraClassMember.h"
//Added by qt3to4:
#include <Q3CString>

// This class allows to manage extra class member, it may be used
// to insert C++ pre-processor directive (even they may be placed
// in the other member definition/declaration) etc ...
// You can modify it as you want (except the constructor)

class UmlExtraClassMember : public UmlBaseExtraClassMember {
  public:
    UmlExtraClassMember(void * id, const Q3CString & n)
      : UmlBaseExtraClassMember(id, n) {};
};

#endif
