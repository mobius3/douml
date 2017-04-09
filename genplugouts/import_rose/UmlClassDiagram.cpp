
#include "UmlClassDiagram.h"
#include "File.h"
#include "UmlClassView.h"

#include "UmlCom.h"
//Added by qt3to4:
#include <QByteArray>
void UmlClassDiagram::import(File & f, UmlItem * p)
{
    QByteArray s;

    if (f.read(s) != STRING)
        f.syntaxError(s, "class diagram's name");

    QByteArray id;
    QByteArray ste;
    QByteArray doc;
    QHash<QByteArray, QByteArray*> prop;
    QByteArray s2;
    int k;

    do {
        k = f.readDefinitionBeginning(s2, id, ste, doc, prop);
    }
    while (id.isEmpty());

    UmlClassDiagram * x;

    if (scanning) {
        if ((x = UmlBaseClassDiagram::create(p, s)) == 0) {
            UmlCom::trace("<br>cannot create class diagram '" + s + "' in " +
                          p->fullName());
            throw 0;
        }

        newItem(x, id);

        if (!doc.isEmpty())
            x->set_Description(doc);

        x->setProperties(prop);
    }
    else if ((x = (UmlClassDiagram *) findItem(id, aClassDiagram)) == 0) {
        UmlCom::trace("<br>unknown class diagram '" + s + "' in " +
                      p->fullName());
        throw 0;
    }

    f.unread(k, s2);
    x->import(f);
}

void UmlClassDiagram::import(File & f)
{
    //!!!!!!!!!!!!!!!!!!
    f.skipBlock();
}

