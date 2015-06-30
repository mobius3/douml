#ifndef _UMLPACKAGE_H
#define _UMLPACKAGE_H


#include "UmlBasePackage.h"
#include <QByteArray>
// //[rageek] incomplete qt3to4


#include "UmlDeploymentView.h"
class UmlArtifact;
class UmlDeploymentView;
class File;

// This class manages a 'package', notes that the project itself is a package
//
// You can modify it as you want (except the constructor)
class UmlPackage : public UmlBasePackage
{
public:
    UmlPackage(void * id, const QByteArray & n) : UmlBasePackage(id, n) {
        cpt[kind()] += 1;
    };

    virtual void roseImport();

    virtual QByteArray fullName();

    void subArtifacts(QList<UmlArtifact*> & l, QByteArray name, QByteArray deplview_name);

    void subDeplViews(QList<UmlDeploymentView*> & l, QByteArray s);

    UmlPackage * addPackage(QByteArray s);

    UmlDeploymentView * addDeplView(QByteArray s, UmlPackage * p);


private:
    bool import(File & f);

    void readUseCaseView(File & f);

    void readClassView(File & f);

    void readComponentView(File & f);

    void readDeploymentView(File & f);


protected:
    QList<UmlDeploymentView*> _deplviews;

};

#endif
