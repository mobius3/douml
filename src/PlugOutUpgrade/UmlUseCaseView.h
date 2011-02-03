#ifndef UMLUSECASEVIEW_H
#define UMLUSECASEVIEW_H

#include "UmlBaseUseCaseView.h"
//Added by qt3to4:
#include <Q3CString>

// This class manages 'use case view'
// You can modify it as you want (except the constructor)

class UmlUseCaseView : public UmlBaseUseCaseView {
  public:
    UmlUseCaseView(void * id, const Q3CString & n)
      : UmlBaseUseCaseView(id, n) {};
  
};

#endif
