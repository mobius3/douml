#ifndef _UMLITEM_H
#define _UMLITEM_H


#include "UmlBaseItem.h"
#include <q3cstring.h>
#include "anItemKind.h"

class UmlClass;
class UmlState;

// This class is a mother class for all the other Uml* classes, this
// allows to generalize their management, declare virtual operations etc ...
//
// You can modify it as you want (except the constructor)
class UmlItem : public UmlBaseItem
{
public:
    UmlItem(void * id, const Q3CString & n) : UmlBaseItem(id, n) {};

    virtual ~UmlItem();

    UmlItem * getChild(anItemKind k, Q3CString s);

    //  return name modified to only contains a-ZA-Z0-9_

    Q3CString quotedName();

    //  initialization, does nothing at this level

    virtual void init(UmlClass * mother, Q3CString path, Q3CString pretty_path, UmlState * state);

    //  program entry point, correspond to a wrong Tools configuration

    virtual void generate();

    //  for state & transition, can't be called

    virtual void generate(UmlClass *, UmlClass *, UmlState *);

    //  if the target of a transition, can't be called

    virtual void generate(UmlClass * machine, UmlClass * anystate, UmlState * state, Q3CString & body, Q3CString indent);

    //  does nothing at this level

    virtual void setComment(Q3CString s);

    // if the element was produced by a previous use of the plug-out mark it useless to may delete it at end
    // iterate on children
    void setUseless();

    //  mark the element  is usefull
    virtual void setUsed();

    //delete useless classes, operations and attributes

    virtual void deleteUseless();

};

#endif
