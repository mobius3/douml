#ifndef _UMLSTATE_H
#define _UMLSTATE_H


#include "UmlBaseState.h"
#include "UmlStateItem.h"
#include <QByteArray>

class FileOut;

class UmlState : public UmlBaseState, public UmlStateItem
{
public:
        //  the constructor, do not call it yourself !!!!!!!!!!
    UmlState(void * id, const QByteArray & s) : UmlBaseState(id, s) {
    }

    virtual bool write_if_needed(FileOut & out);

};

#endif
