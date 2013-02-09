#ifndef _UMLBASEPARAMETER_H
#define _UMLBASEPARAMETER_H


#include <q3cstring.h>
#include "UmlTypeSpec.h"
#include "aDirection.h"

//  Represent an operation's parameter

struct UmlBaseParameter {
    Q3CString name;

    Q3CString default_value;

    UmlTypeSpec type;

    aDirection dir;

};

#endif
