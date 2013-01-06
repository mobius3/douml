#ifndef _UMLBASEDIAGRAM_H
#define _UMLBASEDIAGRAM_H


#include "UmlItem.h"
#include <q3cstring.h>

//  Mother class of all the classes managing the diagrams
class UmlBaseDiagram : public UmlItem
{
public:
    // saves the diagram picture in the file whose pathname is given
    // in argument, the produced file is a PNG file.
    // The aspect of the diagram is :
    // - its visible part in case it is open
    // - the aspect specified by its prefered size and scale in case
    //   these last are specified (see menu on a diagram view)
    // - else the default diagram aspect, which is probably not as you want
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool saveIn(const Q3CString & s) const;


protected:
    // the constructor, do not call it yourself !!!!!!!!!!
    UmlBaseDiagram(void * id, const Q3CString & n) : UmlItem(id, n) {};

};

#endif
