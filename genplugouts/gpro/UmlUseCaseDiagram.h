#ifndef _UMLUSECASEDIAGRAM_H
#define _UMLUSECASEDIAGRAM_H


#include "UmlBaseUseCaseDiagram.h"
#include <q3cstring.h>

// This class manages 'use case diagrams', notes that the class 'UmlDiagram'
// is a mother class of all the diagrams, allowing to generalize their
// management
//
// You can modify it as you want (except the constructor)
class UmlUseCaseDiagram : public UmlBaseUseCaseDiagram
{
public:
    UmlUseCaseDiagram(void * id, const Q3CString & n) : UmlBaseUseCaseDiagram(id, n) {};

};

#endif
