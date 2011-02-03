#ifndef UMLCOMPONENTVIEW_H
#define UMLCOMPONENTVIEW_H

#include "UmlBaseComponentView.h"
//Added by qt3to4:
#include <Q3CString>

// This class manages 'component view'
// You can modify it as you want (except the constructor)

class UmlComponentView : public UmlBaseComponentView {
  public:
    UmlComponentView(void * id, const Q3CString & n)
      : UmlBaseComponentView(id, n) {};
};

#endif
