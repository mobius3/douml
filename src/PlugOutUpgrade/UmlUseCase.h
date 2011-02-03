#ifndef UMLUSECASE_H
#define UMLUSECASE_H

#include "UmlBaseUseCase.h"
//Added by qt3to4:
#include <Q3CString>

// This class manages 'use case'
// You can modify it as you want (except the constructor)

class UmlUseCase : public UmlBaseUseCase {
  public:
    UmlUseCase(void * id, const Q3CString & n)
      : UmlBaseUseCase(id, n) {};
  
};

#endif
