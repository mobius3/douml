#ifndef _UMLPARAMETER_H
#define _UMLPARAMETER_H


#include "UmlBaseParameter.h"
#include <q3cstring.h>

//  Represent an operation's parameter

struct UmlParameter : public UmlBaseParameter {
    Q3CString cpp(unsigned rank) const;

};

#endif
