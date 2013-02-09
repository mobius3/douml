#ifndef _UMLDEPLOYMENTVIEW_H
#define _UMLDEPLOYMENTVIEW_H


#include "UmlBaseDeploymentView.h"

#include <q3ptrlist.h>

class FileOut;
class UmlItem;

// This class manages 'deployment view'
//
// You can modify it as you want (except the constructor)
class UmlDeploymentView : public UmlBaseDeploymentView
{
public:
    UmlDeploymentView(void * id, const WrapperStr & n) : UmlBaseDeploymentView(id, n) {};

    virtual void write(FileOut & out);

    //Memorize the relation in the package (or the view in case the views
    //are generated as package) containing the current element, to generate
    //the relation at the package/view level

    virtual void memo_relation(UmlItem * r);


protected:
    Q3PtrList<UmlItem> _relations;

};

#endif
