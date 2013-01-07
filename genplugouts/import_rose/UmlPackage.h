#ifndef _UMLPACKAGE_H
#define _UMLPACKAGE_H


#include "UmlBasePackage.h"
#include <q3cstring.h>
//#include <q3ptrlist.h> //[rageek] incomplete qt3to4
#include <q3ptrlist.h>

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
    UmlPackage(void * id, const Q3CString & n) : UmlBasePackage(id, n) {
        cpt[kind()] += 1;
    };

    virtual void roseImport();

    virtual Q3CString fullName();

    void subArtifacts(Q3PtrList<UmlArtifact> & l, Q3CString name, Q3CString deplview_name);

    void subDeplViews(Q3PtrList<UmlDeploymentView> & l, Q3CString s);

    UmlPackage * addPackage(Q3CString s);

    UmlDeploymentView * addDeplView(Q3CString s, UmlPackage * p);


private:
    bool import(File & f);

    void readUseCaseView(File & f);

    void readClassView(File & f);

    void readComponentView(File & f);

    void readDeploymentView(File & f);


protected:
    Q3PtrList<UmlDeploymentView> _deplviews;

};

#endif
