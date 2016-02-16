#ifndef _UMLACTIVITYACTION_H
#define _UMLACTIVITYACTION_H


#include "UmlBaseActivityAction.h"


class UmlActivityAction : public UmlBaseActivityAction
{
public:
    using UmlBaseActivityAction::html;

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html();


protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityAction(void * id, const QByteArray & s) : UmlBaseActivityAction(id, s) {
    }

};

#endif
