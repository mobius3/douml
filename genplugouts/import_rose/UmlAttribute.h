#ifndef _UMLATTRIBUTE_H
#define _UMLATTRIBUTE_H


#include "UmlBaseAttribute.h"
#include <QByteArray>


class File;
class UmlClass;

// This class manages 'attribute', notes that the class 'UmlClassItem'
// is a mother class of the class's children.
//
// You can modify it as you want (except the constructor)
class UmlAttribute : public UmlBaseAttribute
{
public:
    UmlAttribute(void * id, const QByteArray & n) :  UmlBaseAttribute(id, n) {
        cpt[kind()] += 1;
    };


private:
    void import(File & f);


public:
    static void import(File & f, UmlClass * parent);

    static void importIdlConstant(UmlClass * parent, const QByteArray & id, const QByteArray & s, const QByteArray & doc, QHash<QByteArray, QByteArray*> & prop);


private:
    void cplusplus(QHash<QByteArray, QByteArray*> & prop);

    void oracle8(QHash<QByteArray, QByteArray*> & prop);

    void corba(QHash<QByteArray, QByteArray*> & prop);

    void java(QHash<QByteArray, QByteArray*> & prop);

};

#endif
