#ifndef UMLDEPLOYMENTVIEW_H
#define UMLDEPLOYMENTVIEW_H

#include "UmlBaseDeploymentView.h"
//Added by qt3to4:
#include "misc/mystr.h"

// This class manages 'deployment view'
// You can modify it as you want (except the constructor)

class UmlDeploymentView : public UmlBaseDeploymentView
{
public:
    UmlDeploymentView(void * id, const WrapperStr & n)
        : UmlBaseDeploymentView(id, n) {};
};

#endif
