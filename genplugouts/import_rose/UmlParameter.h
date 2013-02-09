#ifndef _UMLPARAMETER_H
#define _UMLPARAMETER_H


#include "aDirection.h"
#include "UmlTypeSpec.h"
#include <q3cstring.h>

//  Represent an operation's parameter

struct UmlParameter {
    aDirection dir;

    UmlTypeSpec type;

    Q3CString name;

    Q3CString default_value;

};

#endif
