
#include "UmlItem.h"

#include "UmlCom.h"
#include "util.h"
//Added by qt3to4:
#include <QByteArray>
UmlItem::~UmlItem()
{
}

void UmlItem::roseImport()
{
}

QByteArray UmlItem::fullName()
{
    return parent()->fullName() + "::" + name();
}

void UmlItem::setProperties(QHash<QByteArray, QByteArray*> & d)
{
    QHashIterator<QByteArray, QByteArray*> it(d);

    while (it.hasNext()) {
        it.next();
        set_PropertyValue(QByteArray(it.key()), *(it.value()));//[jasa] QString to QByteArray conversion
        //++it;
    }

    d.clear();
}

void UmlItem::newItem(UmlItem * x, const char * id)
{
    QHash<QString,UmlItem*> & d = all_items[x->kind()];
    if (d.value(id,0) != 0) {
        UmlCom::trace(QByteArray("<br>id '") + id + "' used for several objects");
        throw 0;
    }

    d.insert(id, x);

    if (d.size() < (d.count() >> 3))
        d.reserve(d.size() << 4);

    x->set_PropertyValue("rose/quid", id);
}

UmlItem * UmlItem::findItem(const char * id, anItemKind k)
{
    UmlItem* it = all_items[k].value(id);
    return it;
}

void UmlItem::statistic()
{
    QByteArray msg = "<br>";

#define add_nbr(x, str) \
  if (cpt[x] != 0) { \
    QByteArray s; \
    \
    s= QString("%1 %2<br>").arg(cpt[x]).arg(str).toLatin1(); \
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

QHash<QString,UmlItem*> UmlItem::all_items[aPackage + 1];

int UmlItem::cpt[128];

