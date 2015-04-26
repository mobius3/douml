#ifndef _UMLITEM_H
#define _UMLITEM_H

#include "UmlBaseItem.h"
#include <QVector>

// This class is a mother class for all the other Uml* classes, this
// allows to generalize their management, declare virtual operations etc ...
//
// You can modify it as you want (except the constructor)
class UmlItem : public UmlBaseItem
{
public:
    UmlItem(void * id, const QByteArray & n) : UmlBaseItem(id, n) {};

    virtual ~UmlItem();

    virtual void sort();

    virtual int orderWeight();

    void sortChildren();

};

class VectorOfUmlItem : public QVector<UmlItem*>
{
public:
    int compareItems(UmlItem *d1, UmlItem *d2);

};

#endif
