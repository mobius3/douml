#ifndef _UMLBASECLASSDIAGRAM_H
#define _UMLBASECLASSDIAGRAM_H


#include "UmlDiagram.h"
#include "anItemKind.h"
#include <qcstring.h>

class UmlClassDiagram;
class UmlClassView;

// Manage the class diagrams
class UmlBaseClassDiagram : public UmlDiagram {
  public:
    // returns a new class diagram named 'name' created under 'parent'
    //
    // In case it cannot be created (the name is already used or
    // invalid, 'parent' cannot contain it etc ...) return 0 in C++
    // and produce a RuntimeException in Java
    static UmlClassDiagram * create(UmlClassView * parent, const char * s);

    // returns the kind of the item
    virtual anItemKind kind();


  protected:
    // the constructor, do not call it yourself !!!!!!!!!!
    UmlBaseClassDiagram(void * id, const QCString & n) : UmlDiagram(id, n) {};

};

#endif
