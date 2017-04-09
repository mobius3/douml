#ifndef _UMLBASEPARAMETER_H
#define _UMLBASEPARAMETER_H



#include "UmlTypeSpec.h"
#include "aDirection.h"

//  Represent an operation's parameter

struct UmlBaseParameter {
    QByteArray name;

    QByteArray default_value;

    UmlTypeSpec type;

    aDirection dir;

};

#endif
