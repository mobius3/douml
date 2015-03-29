#ifndef _UMLTRANSITION_H
#define _UMLTRANSITION_H


#include "UmlBaseTransition.h"
#include "UmlStateItem.h"
#include <QByteArray>


class UmlClass;
class UmlState;

class UmlTransition : public UmlBaseTransition, public UmlStateItem
{
public:
    UmlTransition(void * id, const QByteArray & n) : UmlBaseTransition(id, n), _already_managed(FALSE) {
    }

    //  return the name of the trigger

    QByteArray triggerName();

    //  initialization before generation

    virtual void init(UmlClass * mother, QByteArray path, QByteArray pretty_path, UmlState * state);

    //   manage transition from a state or an initial pseudo state

    virtual void generate(UmlClass * machine, UmlClass * anystate, UmlState * state);

    //  manage transition from a pseudo state

    virtual void generate(UmlClass * machine, UmlClass * anystate, UmlState * state, QByteArray & body, QByteArray indent);

    //  generate all the transition in trs, for a state, junction or choice

    static void generate(QList<UmlTransition*> trs, UmlClass * machine, UmlClass * anystate, UmlState * state, QByteArray & body, QByteArray indent, bool completion);


protected:
    //  to know that the transition was already managed because
    //  it has the same trigger of an other transition
    bool _already_managed;

};

#endif
