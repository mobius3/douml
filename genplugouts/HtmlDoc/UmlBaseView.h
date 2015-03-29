#ifndef _UMLBASEVIEW_H
#define _UMLBASEVIEW_H


#include "UmlItem.h"


class UmlBaseView : public UmlItem
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlBaseView(void * id, const QByteArray & s) : UmlItem(id, s) {
    }

};

#endif
