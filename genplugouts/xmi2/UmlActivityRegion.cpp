
#include "UmlActivityRegion.h"

#include "UmlFlow.h"
void UmlActivityRegion::memo_incoming_flow()
{
    const Q3PtrVector<UmlItem> ch = children();
    unsigned n = ch.size();
    unsigned i;

    for (i = 0; i != n; i += 1)
        (dynamic_cast<UmlActivityItem *>(ch[i]))->memo_incoming_flow();
}

