#ifndef _UMLRELATION_H
#define _UMLRELATION_H



#include <QByteArray>
#include "aVisibility.h"
#include "aRelationKind.h"
#include "UmlBaseRelation.h"

class UmlClass;
class File;

// This class manages 'relations', notes that the class 'UmlClassItem'
// is a mother class of all the class's children.
//
// You can modify it as you want (except the constructor)
class UmlRelation : public UmlBaseRelation
{
public:
    struct Role {
        QHash<QByteArray, QByteArray*> prop;

        QByteArray doc;

        QByteArray id;

        QByteArray name;

        UmlClass * target;

        QByteArray target_id;

        QByteArray cardinality;

        aVisibility visibility;

        bool is_byvalue;

        bool is_navigable;

        bool is_aggregate;

        bool is_static;

        void import(File & f);

        aRelationKind rel_kind(bool bidir);

    };


    UmlRelation(void * id, const QByteArray & n) : UmlBaseRelation(id, n) {
        cpt[kind()] += 1;
    };

    static void import(File & f);


private:
    void import(Role * role);

    void cplusplus(Role * role);

    void oracle8(Role * role);

    void corba(Role * role);

    void java(Role * role);

};

#endif
