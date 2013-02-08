#ifndef _UMLCLASSINSTANCE_H
#define _UMLCLASSINSTANCE_H


#include "UmlBaseClassInstance.h"


class FileOut;

class UmlClassInstance : public UmlBaseClassInstance
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlClassInstance(void * id, const WrapperStr & s) : UmlBaseClassInstance(id, s) {
    }

    virtual void write(FileOut & out);

};

#endif
