#ifndef _UMLCOMPONENTDIAGRAM_H
#define _UMLCOMPONENTDIAGRAM_H


#include "UmlBaseComponentDiagram.h"
#include <q3cstring.h>

// This class manages 'ccomponent diagrams', notes that the class 'UmlDiagram'
// is a mother class of all the diagrams, allowing to generalize their
// management
//
// You can modify it as you want (except the constructor)
class UmlComponentDiagram : public UmlBaseComponentDiagram
{
public:
    UmlComponentDiagram(void * id, const Q3CString & n) : UmlBaseComponentDiagram(id, n) {};

    virtual int orderWeight();

};

#endif
