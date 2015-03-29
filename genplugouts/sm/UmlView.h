#ifndef _UMLVIEW_H
#define _UMLVIEW_H


#include "UmlBaseView.h"
#include <QByteArray>

class UmlView : public UmlBaseView
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlView(void * id, const QByteArray & s) : UmlBaseView(id, s) {
    }

};

#endif
