#ifndef _UMLINTERRUPTIBLEACTIVITYREGION_H
#define _UMLINTERRUPTIBLEACTIVITYREGION_H


#include "UmlBaseInterruptibleActivityRegion.h"
#include <q3cstring.h>

class FileOut;

class UmlInterruptibleActivityRegion : public UmlBaseInterruptibleActivityRegion {
  public:
    //  the constructor, do not call it yourself !!!!!!!!!!
     UmlInterruptibleActivityRegion(void * id, const Q3CString & s) : UmlBaseInterruptibleActivityRegion(id, s) {
    }

    //write the definition if it is not empty for the target language
    virtual void write(FileOut & out);

};

#endif
