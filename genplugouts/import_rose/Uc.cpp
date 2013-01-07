
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
//Added by qt3to4:
#include <Q3CString>
void Uc::import(File & f)
{
    for (;;) {
        Q3CString s;

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
        Q3CString s;

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
                //UmlCom::trace("<br>" + s + " in " + Q3CString(f.name()) + " NOT MANAGED by UseCaseView::readObject()");//[jasa] original line
                UmlCom::trace("<br>" + s + " in " + Q3CString(f.name().toAscii()) + " NOT MANAGED by UseCaseView::readObject()");//[jasa] conversion from QString to Q3CString

            f.skipBlock();
        }
    }
}

Uc::~Uc()
{
}

