#ifndef _UMLDEPLOYMENTVIEW_H
#define _UMLDEPLOYMENTVIEW_H


#include "UmlBaseDeploymentView.h"


class Context;

// This class manages 'deployment view'
//
// You can modify it as you want (except the constructor)
class UmlDeploymentView : public UmlBaseDeploymentView
{
public:
    UmlDeploymentView(void * id, const QByteArray & n) : UmlBaseDeploymentView(id, n) {};

    virtual void change(Context & ctx);

};

#endif
