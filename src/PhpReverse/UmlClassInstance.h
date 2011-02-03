#ifndef _UMLCLASSINSTANCE_H
#define _UMLCLASSINSTANCE_H


#include "UmlBaseClassInstance.h"
//Added by qt3to4:
#include <Q3CString>

class UmlClassInstance : public UmlBaseClassInstance {
  public:
    //  the constructor, do not call it yourself !!!!!!!!!!
     UmlClassInstance(void * id, const Q3CString & s) : UmlBaseClassInstance(id, s) {
    }
};

#endif
