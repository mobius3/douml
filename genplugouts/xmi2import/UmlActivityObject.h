#ifndef _UMLACTIVITYOBJECT_H
#define _UMLACTIVITYOBJECT_H


#include "UmlBaseActivityObject.h"


class FileIn;
class Token;
class UmlItem;

class UmlActivityObject : public UmlBaseActivityObject
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityObject(void * id, const WrapperStr & s) : UmlBaseActivityObject(id, s) {
    }

    static void init();

    //import the activity object starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);


protected:
    void setType(WrapperStr idref);

    void setType(Token & token);

    void setOrdering(WrapperStr s, FileIn & in);

    void setSelection(WrapperStr idref);

    void setInState(WrapperStr s);

    //import the lower multiplicity starting by 'tk' inside 'where'
    void importMultiplicity(FileIn & in, Token & token, bool upper);

    //  finish to read activity object and sub classes definition

    void import_it(FileIn & in, Token & token);


public:
    //  call at end of import : try to solve type or state
    virtual void solve(int context, WrapperStr idref);

};

#endif
