#ifndef _UMLPARAMETER_H
#define _UMLPARAMETER_H


#include "aDirection.h"
#include "UmlTypeSpec.h"


//  Represent an operation's parameter

struct UmlParameter {
    aDirection dir;

    UmlTypeSpec type;

    QByteArray name;

    QByteArray default_value;

};

#endif
