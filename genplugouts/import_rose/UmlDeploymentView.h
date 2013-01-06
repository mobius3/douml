#ifndef _UMLDEPLOYMENTVIEW_H
#define _UMLDEPLOYMENTVIEW_H


#include "UmlBaseDeploymentView.h"
#include <q3cstring.h>

class File;
class UmlPackage;

// This class manages 'deployment view'
//
// You can modify it as you want (except the constructor)
class UmlDeploymentView : public UmlBaseDeploymentView
{
public:
    UmlDeploymentView(void * id, const Q3CString & n) : UmlBaseDeploymentView(id, n) {
        cpt[kind()] += 1;
    };

    void import(File & f);

    void readObjects(File & f);

    static UmlDeploymentView * create(UmlPackage * parent, const char * s, Q3CString bn);

    static void import(UmlPackage * parent, File & f);


protected:
    Q3CString _base_name;


public:
    const Q3CString baseName() const;

};

inline const Q3CString UmlDeploymentView::baseName() const
{
    return _base_name;
}

#endif
