#ifndef _UMLDEPLOYMENTVIEW_H
#define _UMLDEPLOYMENTVIEW_H


#include "UmlBaseDeploymentView.h"
#include <QByteArray>

class File;
class UmlPackage;

// This class manages 'deployment view'
//
// You can modify it as you want (except the constructor)
class UmlDeploymentView : public UmlBaseDeploymentView
{
public:
    UmlDeploymentView(void * id, const QByteArray & n) : UmlBaseDeploymentView(id, n) {
        cpt[kind()] += 1;
    };

    void import(File & f);

    void readObjects(File & f);

    static UmlDeploymentView * create(UmlPackage * parent, const char * s, QByteArray bn);

    static void import(UmlPackage * parent, File & f);


protected:
    QByteArray _base_name;


public:
    const QByteArray baseName() const;

};

inline const QByteArray UmlDeploymentView::baseName() const
{
    return _base_name;
}

#endif
