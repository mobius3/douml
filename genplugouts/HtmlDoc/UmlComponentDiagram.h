#ifndef _UMLCOMPONENTDIAGRAM_H
#define _UMLCOMPONENTDIAGRAM_H


#include "UmlBaseComponentDiagram.h"
#include <q3cstring.h>
#include "Vector.h"

// This class manages 'ccomponent diagrams', notes that the class 'UmlDiagram'
// is a mother class of all the diagrams, allowing to generalize their
// management
//
// You can modify it as you want (except the constructor)
class UmlComponentDiagram : public UmlBaseComponentDiagram
{
public:
    UmlComponentDiagram(void * id, const Q3CString & n) : UmlBaseComponentDiagram(id, n) {};

    //returns a string indicating the king of the element
    virtual Q3CString sKind();

    //set he html ref
    //set the diagrams list
    virtual void memo_ref();

    static void ref_index();

    static void generate_index();


protected:
    static Vector diagrams;

};

#endif
