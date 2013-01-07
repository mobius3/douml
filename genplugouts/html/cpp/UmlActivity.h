#ifndef _UMLACTIVITY_H
#define _UMLACTIVITY_H


#include "UmlBaseActivity.h"
#include <q3cstring.h>
#include "Vector.h"

class UmlActivity : public UmlBaseActivity
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivity(void * id, const Q3CString & s) : UmlBaseActivity(id, s) {
    }

    //returns a string indicating the king of the element
    virtual Q3CString sKind();

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(Q3CString pfix, unsigned int rank, unsigned int level);

    //set the html ref
    //set the activity list
    virtual void memo_ref();

    static void ref_index();

    static void generate_index();

    virtual bool chapterp();


protected:
    static Vector activities;

};

#endif
