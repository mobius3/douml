
#include "UmlActivityPartition.h"
#include "FileOut.h"

void UmlActivityPartition::write(FileOut & out)
{
    const char * p = (parent()->kind() == aPartition)
                     ? "subpartition" : "group";

    out.indent();
    out << "<" << p << " xmi:type=\"uml:ActivityPartition\" name=\"";
    out.quote((const char *)name()); //[jasa] ambiguous call
    out << '"';
    out.id(this);

    if (isDimension())
        out << " isDimension=\"true\"";

    if (isExternal())
        out << " isExternal=\"true\"";

    if (represents() != 0)
        out.ref(represents(), "represents");

    out << ">\n";
    out.indent(+1);

    write_description_properties(out);

    const QVector<UmlItem*> ch = children();
    unsigned n = ch.size();

    for (unsigned i = 0; i != n; i += 1)
        ch[i]->write(out);

    out.indent(-1);
    out.indent();
    out << "</" << p << ">\n";

    unload();
}

void UmlActivityPartition::memo_incoming_flow()
{
    // nothing to do

}

