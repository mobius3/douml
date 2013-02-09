#ifndef _UMLBASECOLLABORATIONMESSAGE_H
#define _UMLBASECOLLABORATIONMESSAGE_H



#include <q3ptrdict.h>
#include "UmlMessage.h"

class UmlClassInstanceReference;

// this class manages messages in a collaboration diagram
class UmlBaseCollaborationMessage : public UmlMessage
{
public:
    // return the global rank of the message
    int rank() const {
        return _rank;
    }

    // return the hierarchical rank of the message
    const WrapperStr & hrank() const {
        return _hrank;
    }


private:
    int _rank;

    WrapperStr _hrank;

    // internal, don't call it
    void read_(const Q3PtrDict<UmlClassInstanceReference> & instances);

    friend class UmlBaseCollaborationDiagramDefinition;
};

#endif
