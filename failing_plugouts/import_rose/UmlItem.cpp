
#include "UmlItem.h"

#include "UmlCom.h"
#include "util.h"
//Added by qt3to4:
#include <Q3CString>
UmlItem::~UmlItem()
{
}

void UmlItem::roseImport()
{
}

Q3CString UmlItem::fullName()
{
    return parent()->fullName() + "::" + name();
}

void UmlItem::setProperties(Q3Dict<Q3CString> & d)
{
    Q3DictIterator<Q3CString> it(d);

    while (it.current()) {
        set_PropertyValue(Q3CString(it.currentKey().toAscii()), *(it.current()));//[jasa] QString to Q3CString conversion
        ++it;
    }

    d.clear();
}

void UmlItem::newItem(UmlItem * x, const char * id)
{
    Q3AsciiDict<UmlItem> & d = all_items[x->kind()];

    if (d[id] != 0) {
        UmlCom::trace(Q3CString("<br>id '") + id + "' used for several objects");
        throw 0;
    }

    d.insert(strdup(id), x);

    if (d.size() < (d.count() >> 3))
        d.resize(d.size() << 4);

    x->set_PropertyValue("rose/quid", id);
}

UmlItem * UmlItem::findItem(const char * id, anItemKind k)
{
    return all_items[k][id];
}

void UmlItem::statistic()
{
    Q3CString msg = "<br>";

#define add_nbr(x, str) \
  if (cpt[x] != 0) { \
    Q3CString s; \
    \
    s.sprintf("%d %s<br>", cpt[x], str); \
    msg += s; \
  }

    add_nbr(aPackage, "Packages");
    add_nbr(anUseCaseView, "Use Case Views");
    add_nbr(aClassView, "Class Views");
    add_nbr(aComponentView, "Component Views");
    add_nbr(aDeploymentView, "Deployment Views");
    add_nbr(anUseCaseDiagram, "Use Case Diagrams");
    add_nbr(aSequenceDiagram, "Sequence Diagrams");
    add_nbr(aCollaborationDiagram, "Collaboration Diagrams");
    add_nbr(aClassDiagram, "Class Diagrams");
    add_nbr(aComponentDiagram, "Component Diagrams");
    add_nbr(aDeploymentDiagram, "Deployment Diagrams");
    add_nbr(anUseCase, "Use Cases");
    add_nbr(aClass, "Classes");
    add_nbr(aRelation, "Relations");
    add_nbr(aNcRelation, "Non Class Relations");
    add_nbr(anAttribute, "Attributes");
    add_nbr(anOperation, "Operations");
    add_nbr(anExtraClassMember, "Extra Class Members");
    add_nbr(aComponent, "Components");
    add_nbr(aNode, "Nodes");

    UmlCom::trace(msg);
}

bool UmlItem::scanning;

Q3AsciiDict<UmlItem> UmlItem::all_items[aPackage + 1];

int UmlItem::cpt[128];

