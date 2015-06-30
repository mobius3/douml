#ifndef _UMLARTIFACT_H
#define _UMLARTIFACT_H


#include "UmlBaseArtifact.h"
#include <QByteArray>
#include <qstring.h>

// This class manages 'artifacts'
//
// You can modify it as you want (except the constructor)
class UmlArtifact : public UmlBaseArtifact
{
public:
    UmlArtifact(void * id, const QByteArray & n) : UmlBaseArtifact(id, n) {};

    virtual void genpro();

    void gen_app(const QByteArray & path);

    QString way(QString pro_dir, bool header);

};

#endif
