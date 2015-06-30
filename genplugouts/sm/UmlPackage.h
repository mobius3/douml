#ifndef _UMLPACKAGE_H
#define _UMLPACKAGE_H


#include "UmlBasePackage.h"
#include <QByteArray>

// This class manages a 'package', notes that the project itself is a package
//
// You can modify it as you want (except the constructor)
class UmlPackage : public UmlBasePackage
{
public:
    UmlPackage(void * id, const QByteArray & n) : UmlBasePackage(id, n) {};

};

#endif
