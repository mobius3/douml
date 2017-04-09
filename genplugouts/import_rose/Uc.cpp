
#include "Uc.h"
#include "UmlItem.h"
#include "File.h"

#include "UmlClass.h"
#include "UmlUseCase.h"
#include "UmlUseCaseView.h"
#include "UmlUseCaseDiagram.h"
#include "UmlSequenceDiagram.h"
#include "UmlCollaborationDiagram.h"
#include "UmlCom.h"
#include "UmlClassDiagram.h"
//Added by qt3to4:
#include <QByteArray>
void Uc::import(File & f)
{
    for (;;) {
        QByteArray s;

        switch (f.read(s)) {
        case -1:
            f.eof();
            throw 0;

        case ')':
            return;

        case ATOM:
            if ((s == "logical_models") ||
                (s == "logical_presentations")) {
                f.read("(");
                f.read("list");
                f.read("unit_reference_list");
                readObjects(f);
            }
            else
                readObject(f, s);

            break;

        default:
            f.syntaxError(s);
        }
    }
}

void Uc::readObjects(File & f)
{
    for (;;) {
        QByteArray s;

        switch (f.read(s)) {
        case ')':
            return;

        case '(':
            break;

        default:
            f.syntaxError(s);
        }

        f.read("object");

        if (f.read(s) != ATOM)
            f.syntaxError(s, "an atom");

        if ((s == "Class") || (s == "Metaclass") ||
            (s == "Instantiated_Class") || (s == "Parameterized_Class"))
            UmlClass::import(f, item(), s);
        else if (s == "UseCase")
            UmlUseCase::import(f, item());
        else if (s == "UseCaseDiagram")
            UmlUseCaseDiagram::import(f, item());
        /*else if (s == "ClassDiagram")
            UmlClassDiagram::import(f, item());*/
        else if (s == "InteractionDiagram")
            UmlSequenceDiagram::import(f, item());
        else if (s == "ObjectDiagram")
            UmlCollaborationDiagram::import(f, item());
        else if (s == "Class_Category")
            UmlUseCaseView::import(item(), f);
        else if (s == "logical_presentations") {
            f.read("(");
            f.read("list");
            f.read("unit_reference_list");
            readObjects(f);
        }
        else {
            if ((s != "Association") &&	// actor -----> UC ...
                (s != "Mechanism"))		// seq/col diagram
                //UmlCom::trace("<br>" + s + " in " + QByteArray(f.name()) + " NOT MANAGED by UseCaseView::readObject()");//[jasa] original line
                UmlCom::trace("<br>" + s + " in " + QByteArray(f.fileName().toLatin1()) + " NOT MANAGED by UseCaseView::readObject()");//[jasa] conversion from QString to QByteArray

            f.skipBlock();
        }
    }
}

Uc::~Uc()
{
}

