#ifndef _UMLBASEPARAMETER_H
#define _UMLBASEPARAMETER_H


#include "misc/mystr.h"
#include "UmlTypeSpec.h"
#include "aDirection.h"

//  Represent an operation's parameter

struct UmlBaseParameter {
    WrapperStr name;

    WrapperStr default_value;

    UmlTypeSpec type;

    aDirection dir;

};

#endif
