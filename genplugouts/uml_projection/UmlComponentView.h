#ifndef _UMLCOMPONENTVIEW_H
#define _UMLCOMPONENTVIEW_H


#include "UmlBaseComponentView.h"
#include <QByteArray>

// This class manages 'component view'
//
// You can modify it as you want (except the constructor)
class UmlComponentView : public UmlBaseComponentView
{
public:
    UmlComponentView(void * id, const QByteArray & n) : UmlBaseComponentView(id, n) {};

};

#endif
