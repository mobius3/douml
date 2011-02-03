#ifndef UMLCOMPONENT_H
#define UMLCOMPONENT_H

#include "UmlBaseComponent.h"
//Added by qt3to4:
#include <Q3CString>

// This class manages 'components'
// You can modify it as you want (except the constructor)

class UmlComponent : public UmlBaseComponent {
  public:
    UmlComponent(void * id, const Q3CString & n)
      : UmlBaseComponent(id, n) {};
};

#endif
