#ifndef _UMLBASECOLLABORATIONDIAGRAMDEFINITION_H
#define _UMLBASECOLLABORATIONDIAGRAMDEFINITION_H


// to avoid compiler warning
#include "UmlCollaborationMessage.h"
#include "UmlClassInstanceReference.h"

#include <q3ptrvector.h>

class UmlClassInstanceReference;
class UmlCollaborationMessage;

// this class manages collaboration diagram definition
class UmlBaseCollaborationDiagramDefinition
{
public:
    // return the instances present in the diagram
    const Q3PtrVector<UmlClassInstanceReference> & instances() const {
        return _instances;
    }

    // return the messages present in the diagram,
    // ordonned following their rank
    const Q3PtrVector<UmlCollaborationMessage> & messages() const {
        return _messages;
    }


private:
    Q3PtrVector<UmlClassInstanceReference> _instances;

    Q3PtrVector<UmlCollaborationMessage> _messages;

    // internal, don't call it
    void read_();


public:
    //  to avoid compiler warning, don't call it
    ~UmlBaseCollaborationDiagramDefinition();

    friend class UmlBaseCollaborationDiagram;
};

#endif
