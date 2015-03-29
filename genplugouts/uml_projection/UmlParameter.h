#ifndef _UMLPARAMETER_H
#define _UMLPARAMETER_H


#include "UmlBaseParameter.h"
#include <QByteArray>

//  Represent an operation's parameter

struct UmlParameter : public UmlBaseParameter {
    QByteArray cpp(unsigned rank) const;

};

#endif
