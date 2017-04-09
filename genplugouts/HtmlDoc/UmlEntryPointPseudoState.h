#ifndef _UMLENTRYPOINTPSEUDOSTATE_H
#define _UMLENTRYPOINTPSEUDOSTATE_H



#include "UmlBaseEntryPointPseudoState.h"

class UmlEntryPointPseudoState : public UmlBaseEntryPointPseudoState
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind();

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlEntryPointPseudoState(void * id, const QByteArray & s) : UmlBaseEntryPointPseudoState(id, s) {
    }

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level);

};

#endif
