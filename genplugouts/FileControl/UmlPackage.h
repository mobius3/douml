#ifndef _UMLPACKAGE_H
#define _UMLPACKAGE_H


#include "UmlBasePackage.h"



// This class manages a 'package', notes that the project itself is a package
//
// You can modify it as you want (except the constructor)
class UmlPackage : public UmlBasePackage
{
public:
    UmlPackage(void * id, const QByteArray & n) : UmlBasePackage(id, n) {};

    //Entry point
    //Ask for the way to do check-in/out, execute the check-in/out command on the files

    virtual void fileControl(bool ci);

    //Put files list in 'files' if 'rec' is not null.
    virtual void getFiles(QHash<QString,void*> & files, unsigned rec);

    //Add auxiliary files in 'files'
    //must be applied on the project
    virtual void getAuxFiles(QHash<QString,void*> & files);

};

#endif
