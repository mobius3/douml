#ifndef _UMLONSIGNALACTION_H
#define _UMLONSIGNALACTION_H


#include "UmlBaseOnSignalAction.h"
#include <q3cstring.h>

class FileOut;

class UmlOnSignalAction : public UmlBaseOnSignalAction {
  protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
     UmlOnSignalAction(void * id, const Q3CString & s) : UmlBaseOnSignalAction(id, s) {
    }

    //
    
    void write_signal(FileOut & out);

};

#endif
