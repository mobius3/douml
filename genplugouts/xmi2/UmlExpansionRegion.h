#ifndef _UMLEXPANSIONREGION_H
#define _UMLEXPANSIONREGION_H


#include "UmlBaseExpansionRegion.h"
#include <q3cstring.h>

class FileOut;

class UmlExpansionRegion : public UmlBaseExpansionRegion {
  public:
    //  the constructor, do not call it yourself !!!!!!!!!!
     UmlExpansionRegion(void * id, const Q3CString & s) : UmlBaseExpansionRegion(id, s) {
    }

    //write the definition if it is not empty for the target language
    virtual void write(FileOut & out);

};

#endif
