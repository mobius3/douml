#ifndef _UMLTRANSITION_H
#define _UMLTRANSITION_H


#include "UmlBaseTransition.h"
#include "UmlStateItem.h"
#include <QByteArray>

class UmlTransition : public UmlBaseTransition, public UmlStateItem
{
public:
    UmlTransition(void * id, const QByteArray & n) : UmlBaseTransition(id, n) {
    }

};

#endif
