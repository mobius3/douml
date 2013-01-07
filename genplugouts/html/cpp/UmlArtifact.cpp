
#include "UmlArtifact.h"

#include "UmlCom.h"
#include "UmlClass.h"
#include "UmlDeploymentDiagram.h"
//Added by qt3to4:
#include <Q3CString>
void UmlArtifact::html(Q3CString, unsigned int, unsigned int)
{
    UmlCom::message(name());

    UmlItem::html("Artifact", (UmlDiagram *) associatedDiagram());

    const char * sep = " associated with : ";

    if (stereotype() == "source") {
        fw.write("<p>Artifact <i>source</i>");

        const Q3PtrVector<UmlClass> l = associatedClasses();

        for (unsigned i = 0; i != l.size(); i += 1) {
            fw.write(sep);
            l[i]->write();
            sep = ", ";
        }
    }
    else {
        fw.write("<p><i>");
        writeq(stereotype());
        fw.write("</i>");

        const Q3PtrVector<UmlArtifact> l = associatedArtifacts();

        for (unsigned i = 0; i != l.size(); i += 1) {
            fw.write(sep);
            l[i]->write();
            sep = ", ";
        }
    }

    fw.write("</p>\n");

    unload(FALSE, FALSE);
}

Q3CString UmlArtifact::sKind()
{
    return "artifact";
}

