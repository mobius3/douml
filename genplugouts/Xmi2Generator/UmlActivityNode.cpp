
#include "UmlActivityNode.h"
#include "FileOut.h"

void UmlActivityNode::memo_incoming_flow()
{
    const QVector<UmlItem*> ch = children();
    unsigned n = ch.size();
    unsigned i;

    for (i = 0; i != n; i += 1) {
        UmlActivityItem * x = dynamic_cast<UmlActivityItem *>(ch[i]);

        if (x != 0)
            x->memo_incoming_flow();
    }
}

void UmlActivityNode::add_incoming_flow(UmlFlow * flow)
{
    _incoming_flows.append(flow);
}

void UmlActivityNode::write_incoming_flows(FileOut & out)
{
    QList<UmlFlow*>::Iterator it = _incoming_flows.begin();

    while (it != _incoming_flows.end()) {
        out.indent();
        out << "<incoming";
        out.idref(*it);
        out << "/>\n";
        ++it;
    }

}

