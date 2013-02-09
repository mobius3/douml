#ifndef _UMLACTIVITYPARAMETER_H
#define _UMLACTIVITYPARAMETER_H


#include "UmlBaseActivityParameter.h"
#include <q3cstring.h>

class UmlActivityParameter : public UmlBaseActivityParameter
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityParameter(void * id, const Q3CString & s) : UmlBaseActivityParameter(id, s) {
    }

};

#endif
