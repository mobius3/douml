#ifndef _UMLSEQUENCEDIAGRAM_H
#define _UMLSEQUENCEDIAGRAM_H


#include "UmlBaseSequenceDiagram.h"
#include <q3cstring.h>

// This class manages 'sequence diagrams', notes that the class 'UmlDiagram'
// is a mother class of all the diagrams, allowing to generalize their
// management
//
// You can modify it as you want (except the constructor)
class UmlSequenceDiagram : public UmlBaseSequenceDiagram
{
public:
    UmlSequenceDiagram(void * id, const Q3CString & n) : UmlBaseSequenceDiagram(id, n) {};

};

#endif
