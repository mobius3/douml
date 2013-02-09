#ifndef _UMLBASECLASSINSTANCE_H
#define _UMLBASECLASSINSTANCE_H


#include "SlotAttribute.h"
#include "SlotRelation.h"
#include "UmlItem.h"
#include "anItemKind.h"
#include <q3valuelist.h>
#include <q3ptrvector.h>
#include <q3cstring.h>

class UmlClassInstance;
class UmlClass;
struct SlotAttribute;
struct SlotRelation;
class UmlAttribute;
class UmlRelation;
class UmlObjectDiagram;

class UmlBaseClassInstance : public UmlItem
{
public:
    // returns the kind of the item
    virtual anItemKind kind();

    // Returns a new class instance
    //
    // In case it cannot be created ('parent' cannot contain it etc ...) return 0
    //  in C++ and produce a RuntimeException in Java

    static UmlClassInstance * create(UmlItem * parent, const char * name, UmlClass * type);

    // return the type
    UmlClass * type();

    // set the type
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_Type(UmlClass * v);

    // Returns the attributes having a value
    void attributesValue(Q3ValueList<SlotAttribute> & result);

    // Returns the attributes having a value
    void relationsValue(Q3ValueList<SlotRelation> & result);

    // Returns all the attributes of the class instance,
    // including the inherited
    void availableAttributes(Q3PtrVector<UmlAttribute> & result);

    // Returns all the possible relations from the current instance to 'other', including the inherited
    void availableRelations(UmlClassInstance * other, Q3PtrVector<UmlRelation> & result);

    // Remove the slot if the value is null.
    // Else set the value for the given attribute, replacing it
    // if the slot already exist.
    // On error : return FALSE in C++, produce a RuntimeException in Java
    bool set_AttributeValue(UmlAttribute * attribute, const char * value);

    // Add the slot (does nothing if it already exist)
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    bool add_Relation(UmlRelation * relation, UmlClassInstance * other);

    // Remove the slot (does nothing if it doesn't exist)
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    bool remove_Relation(UmlRelation * relation, UmlClassInstance * other);

    // returns the optional associated diagram
    UmlObjectDiagram * associatedDiagram();

    // sets the associated diagram, arg may be null to unset it
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_AssociatedDiagram(UmlObjectDiagram * d);


private:
    UmlClass * _type;

    UmlObjectDiagram * _assoc_diagram;


protected:
    virtual void read_uml_();

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlBaseClassInstance(void * id, const Q3CString & s) : UmlItem(id, s) {
    }

};

#endif
