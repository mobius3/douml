#ifndef _UMLARTIFACT_H
#define _UMLARTIFACT_H


#include "UmlBaseArtifact.h"


class Context;

// This class manages 'artifacts'
//
// You can modify it as you want (except the constructor)
class UmlArtifact : public UmlBaseArtifact
{
public:
    UmlArtifact(void * id, const QByteArray & n) : UmlBaseArtifact(id, n) {};

    virtual void change(Context & ctx);

};

#endif
