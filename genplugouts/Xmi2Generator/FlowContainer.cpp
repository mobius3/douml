
#include "FlowContainer.h"
#include "UmlFlow.h"
#include "FileOut.h"

FlowContainer::~FlowContainer()
{
}

void FlowContainer::memo_flow(UmlFlow * flow)
{
    _flows.append(flow);
}

void FlowContainer::write_flows(FileOut & out)
{
    while (! _flows.isEmpty())
        _flows.takeAt(0)->write_it(out);
}

