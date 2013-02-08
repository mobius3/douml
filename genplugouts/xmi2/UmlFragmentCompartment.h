#ifndef _UMLFRAGMENTCOMPARTMENT_H
#define _UMLFRAGMENTCOMPARTMENT_H


#include "UmlBaseFragmentCompartment.h"
#include <q3ptrlist.h>


class FileOut;
class UmlItem;
class UmlSequenceMessage;

// this class manages fragments compartments,
// a fragment without separator contains one compartment you can modify it
class UmlFragmentCompartment : public UmlBaseFragmentCompartment
{
public:
    // called for the first message of a fragment compartment and its parents recursively

    void write(FileOut & out, UmlItem * diagram, Q3PtrList< UmlSequenceMessage > & msgs);

    //

    void write(FileOut & out, UmlItem * diagram, Q3PtrList< UmlSequenceMessage > & msgs, WrapperStr oper);

    //

    void bypass(Q3PtrList< UmlSequenceMessage > & msgs);

};

#endif
