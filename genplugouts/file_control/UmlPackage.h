#ifndef _UMLPACKAGE_H
#define _UMLPACKAGE_H


#include "UmlBasePackage.h"
#include <q3cstring.h>
#include <q3dict.h>

// This class manages a 'package', notes that the project itself is a package
//
// You can modify it as you want (except the constructor)
class UmlPackage : public UmlBasePackage
{
public:
    UmlPackage(void * id, const Q3CString & n) : UmlBasePackage(id, n) {};

    //Entry point
    //Ask for the way to do check-in/out, execute the check-in/out command on the files

    virtual void fileControl(bool ci);

    //Put files list in 'files' if 'rec' is not null.
    virtual void getFiles(Q3Dict<void> & files, unsigned rec);

    //Add auxiliary files in 'files'
    //must be applied on the project
    virtual void getAuxFiles(Q3Dict<void> & files);

};

#endif
