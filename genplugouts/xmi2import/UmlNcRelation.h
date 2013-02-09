#ifndef _UMLNCRELATION_H
#define _UMLNCRELATION_H


#include "UmlBaseNcRelation.h"


//This class manages 'relations' between non class objects
//
// You can modify it as you want (except the constructor)
class UmlNcRelation : public UmlBaseNcRelation
{
public:
    UmlNcRelation(void * id, const WrapperStr & n) : UmlBaseNcRelation(id, n) {};

};

#endif
