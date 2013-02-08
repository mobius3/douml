#ifndef _UMLBASEPARAMETERSET_H
#define _UMLBASEPARAMETERSET_H


#include "UmlItem.h"
#include "anItemKind.h"

#include <q3ptrvector.h>

class UmlActivityParameter;
class UmlActivityAction;
class UmlActivityPin;

class UmlBaseParameterSet : public UmlItem
{
public:
    //  returns a new parameter set named 's' created under 'parent'
    //
    // In case it cannot be created (the name is already used or
    // invalid, 'parent' cannot contain it etc ...) return 0 in C++
    // and produce a RuntimeException in Java
    static UmlActivityParameter * create(UmlActivityAction * parent, const char * s);

    // returns the kind of the item
    virtual anItemKind kind();


protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlBaseParameterSet(void * id, const WrapperStr & s) : UmlItem(id, s) {
    }


public:
    // return the pins part of the parameter set
    const Q3PtrVector<UmlActivityPin> & pins();

    // set the pins
    bool set_Pins(const Q3PtrVector<UmlActivityPin> & v);

    // to unload the object to free memory, it will be reloaded automatically
    // if needed. Recursively done for the sub items if 'rec' is TRUE.
    //
    // if 'del' is true the sub items are deleted in C++, and removed from the
    // internal dictionnary in C++ and Java (to allow it to be garbaged),
    // you will have to call Children() to re-access to them
    virtual void unload(bool = FALSE, bool = FALSE);


private:
    Q3PtrVector<UmlActivityPin> _pins;


protected:
    virtual void read_uml_();

};

#endif
