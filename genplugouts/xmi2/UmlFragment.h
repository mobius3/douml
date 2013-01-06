#ifndef _UMLFRAGMENT_H
#define _UMLFRAGMENT_H


#include "UmlBaseFragment.h"
#include <q3ptrlist.h>

class FileOut;
class UmlItem;
class UmlSequenceMessage;
class UmlClassInstanceReference;

// this class manages fragments, you can modify it
class UmlFragment : public UmlBaseFragment
{
public:
    //

    void write(FileOut & out, UmlItem * diagram, Q3PtrList<UmlSequenceMessage> & msgs);

    void cover(UmlSequenceMessage * msg);


private:
    //

    void write_ref(FileOut & out, UmlItem * diagram, Q3PtrList< UmlSequenceMessage > & msgs);

    Q3PtrList<UmlClassInstanceReference> covered;

};

#endif
