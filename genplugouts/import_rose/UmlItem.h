#ifndef _UMLITEM_H
#define _UMLITEM_H


#include "UmlBaseItem.h"
#include <q3cstring.h>
#include <q3dict.h>
#include "anItemKind.h"
#include <q3asciidict.h>

// This class is a mother class for all the other Uml* classes, this
// allows to generalize their management, declare virtual operations etc ...
//
// You can modify it as you want (except the constructor)
class UmlItem : public UmlBaseItem
{
public:
    UmlItem(void * id, const Q3CString & n) : UmlBaseItem(id, n) {};

    virtual ~UmlItem();

    virtual void roseImport();

    virtual Q3CString fullName();

    void setProperties(Q3Dict<Q3CString> & d);

    static void newItem(UmlItem * x, const char * id);

    static UmlItem * findItem(const char * id, anItemKind k);

    static void statistic();

    static bool scanning;


protected:
    static Q3AsciiDict<UmlItem> all_items[aPackage + 1];

    static int cpt[128];

};

#endif
