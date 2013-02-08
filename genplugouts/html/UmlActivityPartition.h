#ifndef _UMLACTIVITYPARTITION_H
#define _UMLACTIVITYPARTITION_H


#include <q3cstring.h>
#include "UmlBaseActivityPartition.h"
#include "UmlActivityItem.h"

class UmlActivityPartition : public UmlBaseActivityPartition, public UmlActivityItem
{
public:
    virtual bool chapterp();

    //returns a string indicating the king of the element
    virtual Q3CString sKind();

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(Q3CString pfix, unsigned int rank, unsigned int level);

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityPartition(void * id, const Q3CString & s) : UmlBaseActivityPartition(id, s) {
    }

};

#endif
