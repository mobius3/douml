#ifndef _UMLBASESEQUENCEDIAGRAMDEFINITION_H
#define _UMLBASESEQUENCEDIAGRAMDEFINITION_H


// to avoid compiler warning
#include "UmlFragment.h"
#include "UmlFragmentCompartment.h"
#include "UmlClassInstanceReference.h"
#include "UmlSequenceMessage.h"

#include <q3ptrvector.h>

class UmlClassInstanceReference;
class UmlSequenceMessage;
class UmlFragment;

// this class manages sequence diagram definition
class UmlBaseSequenceDiagramDefinition
{
public:
    // return the instances present in the diagram
    const Q3PtrVector<UmlClassInstanceReference> & instances() const {
        return _instances;
    }

    // return the messages present in the diagram,
    // ordonned following the sending time
    const Q3PtrVector<UmlSequenceMessage> & messages() const {
        return _messages;
    }

    // return the fragments present in the diagram
    const Q3PtrVector<UmlFragment> & fragments() const {
        return _fragments;
    }


private:
    Q3PtrVector<UmlClassInstanceReference> _instances;

    Q3PtrVector<UmlSequenceMessage> _messages;

    Q3PtrVector<UmlFragment> _fragments;

    // internal, don't call it
    void read_();


public:
    //  to avoid compiler warning, don't call it
    ~UmlBaseSequenceDiagramDefinition();

    friend class UmlBaseSequenceDiagram;
};

#endif
