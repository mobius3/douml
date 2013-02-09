#ifndef _UMLCLASS_H
#define _UMLCLASS_H


#include "UmlBaseClass.h"

#include <q3valuelist.h>

class FileOut;
class UmlRelation;

// This class manages 'classes', notes that the class 'ClassItem'
// is a mother class of the class's children.
//
// You can modify it as you want (except the constructor)

class UmlClass : public UmlBaseClass
{
public:
    UmlClass(void * id, const WrapperStr & n) : UmlBaseClass(id, n), _assoc(0) {};

    virtual void write(FileOut & out);


private:
    void write_formals(FileOut & out);


public:
    void write_actuals(FileOut & out);

    virtual void search_class_assoc();

    //return 0 in case the class is already an association class
    UmlClass * set_assoc(UmlRelation * rel);

    //  the class is a stereotype, computes the list of extended meta classes
    void get_extended(Q3ValueList<WrapperStr> & r);


protected:
    //relation when the class is an association class
    UmlRelation * _assoc;

};

#endif
