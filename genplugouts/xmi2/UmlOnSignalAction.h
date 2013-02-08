#ifndef _UMLONSIGNALACTION_H
#define _UMLONSIGNALACTION_H


#include "UmlBaseOnSignalAction.h"


class FileOut;

class UmlOnSignalAction : public UmlBaseOnSignalAction
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlOnSignalAction(void * id, const WrapperStr & s) : UmlBaseOnSignalAction(id, s) {
    }

    //

    void write_signal(FileOut & out);

};

#endif
