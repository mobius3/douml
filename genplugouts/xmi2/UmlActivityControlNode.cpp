
#include "UmlActivityControlNode.h"
#include "FileOut.h"

void UmlActivityControlNode::write(FileOut & out)
{
    out.indent();
    out << ((parent()->kind() == anActivity) ? "<node" : "<containedNode")
        << " xmi:type=\"uml:" << sKind() << '"';
    out.id(this);

    if (!name().isEmpty()) {
        out << " name=\"";
        out.quote((const char *)name()); //[jasa] ambiguous call
        out << '"';
    }

    out << ">\n";
    out.indent(+1);

    write_description_properties(out);

    const Q3PtrVector<UmlItem> ch = children();
    unsigned n = ch.size();

    for (unsigned i = 0; i != n; i += 1)
        ch[i]->write(out);

    write_incoming_flows(out);

    out.indent(-1);
    out.indent();
    out << ((parent()->kind() == anActivity) ? "</node>\n" : "</containedNode>\n");

    unload();
}

