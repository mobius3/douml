#ifndef _UMLDEPLOYMENTVIEW_H
#define _UMLDEPLOYMENTVIEW_H


#include "UmlBaseDeploymentView.h"
#include <q3cstring.h>

// This class manages 'deployment view'
//
// You can modify it as you want (except the constructor)
class UmlDeploymentView : public UmlBaseDeploymentView
{
public:
    UmlDeploymentView(void * id, const Q3CString & n) : UmlBaseDeploymentView(id, n) {};

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(Q3CString pfix, unsigned int rank, unsigned int level);

    //returns a string indicating the king of the element
    virtual Q3CString sKind();

    virtual bool chapterp();

};

#endif
