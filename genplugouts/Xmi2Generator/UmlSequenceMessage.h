#ifndef _UMLSEQUENCEMESSAGE_H
#define _UMLSEQUENCEMESSAGE_H


#include "UmlBaseSequenceMessage.h"
#include <q3ptrvector.h>
#include <q3ptrlist.h>

class FileOut;
class UmlItem;

// this class manages messages in a sequence diagram,
// you can modify it
class UmlSequenceMessage : public UmlBaseSequenceMessage
{
public:
    UmlSequenceMessage();

    static void write(FileOut & out, UmlItem * diagram, const Q3PtrVector< UmlSequenceMessage > & msgs);

    void write_fragment(FileOut & out, UmlItem * diagram, Q3PtrList< UmlSequenceMessage > & msgs);

    static void write_them(FileOut & out, UmlItem * diagram, const Q3PtrVector< UmlSequenceMessage > & msgs);


private:
    static void set_reverses(const Q3PtrVector<UmlSequenceMessage> & msgs);

    UmlSequenceMessage * reverse;

    bool used;

};

#endif
