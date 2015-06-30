
#include "UmlArtifact.h"

#include "UmlCom.h"
#include "UmlClass.h"
#include "UmlDeploymentDiagram.h"
//Added by qt3to4:
#include <QByteArray>
void UmlArtifact::html(QByteArray, unsigned int, unsigned int)
{
    UmlCom::message(name());

    UmlItem::html("Artifact", (UmlDiagram *) associatedDiagram());

    const char * sep = " associated with : ";

    if (stereotype() == "source") {
        fw.write("<p>Artifact <i>source</i>");

        const QVector<UmlClass*> l = associatedClasses();

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

        const QVector<UmlArtifact*> l = associatedArtifacts();

        for (unsigned i = 0; i != l.size(); i += 1) {
            fw.write(sep);
            l[i]->write();
            sep = ", ";
        }
    }

    fw.write("</p>\n");

    unload(FALSE, FALSE);
}

QByteArray UmlArtifact::sKind()
{
    return "artifact";
}

