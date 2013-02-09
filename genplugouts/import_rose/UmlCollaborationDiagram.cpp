
#include "UmlCollaborationDiagram.h"
#include "File.h"
#include "UmlItem.h"

#include "UmlCom.h"
//Added by qt3to4:
#include <Q3CString>
void UmlCollaborationDiagram::import(File & f, UmlItem * p)
{
    Q3CString s;

    if (f.read(s) != STRING)
        f.syntaxError(s, "collaboration diagram's name");

    Q3CString id;
    Q3CString ste;
    Q3CString doc;
    Q3Dict<Q3CString> prop;
    Q3CString s2;
    int k;

    do {
        k = f.readDefinitionBeginning(s2, id, ste, doc, prop);
    }
    while (id.isEmpty());

    UmlCollaborationDiagram * x;

    if (scanning) {
        if ((x = UmlBaseCollaborationDiagram::create(p, s)) == 0) {
            UmlCom::trace("<br>cannot create collaboration diagram '" + s + "' in " +
                          p->fullName());
            throw 0;
        }

        newItem(x, id);

        if (!doc.isEmpty())
            x->set_Description(doc);

        x->setProperties(prop);
    }
    else if ((x = (UmlCollaborationDiagram *) findItem(id, aCollaborationDiagram)) == 0) {
        UmlCom::trace("<br>unknown collaboration diagram '" + s + "' in " +
                      p->fullName());
        throw 0;
    }

    f.unread(k, s2);
    //!!!!!!!!!!!!!!!!!!
    f.skipBlock();
}

