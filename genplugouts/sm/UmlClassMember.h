#ifndef _UMLCLASSMEMBER_H
#define _UMLCLASSMEMBER_H


#include <QByteArray>
#include "UmlBaseClassMember.h"

// This class globaly manages class's relations, attributes, operations
// and sub-classes
//
// You can modify it as you want (except the constructor)
class UmlClassMember : public UmlBaseClassMember
{
public:
    UmlClassMember(void * id, const QByteArray & n) : UmlBaseClassMember(id, n) {};

    //  set the description, depending on the  or  keyword
    virtual void setComment(QByteArray s);

};

#endif
