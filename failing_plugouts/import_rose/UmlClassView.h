#ifndef _UMLCLASSVIEW_H
#define _UMLCLASSVIEW_H


#include "UmlBaseClassView.h"
#include <q3cstring.h>

class UmlPackage;
class File;
class UmlUseCaseView;

// This class manages 'class view'
//
// You can modify it as you want (except the constructor)
class UmlClassView : public UmlBaseClassView
{
public:
    UmlClassView(void * id, const Q3CString & n);

    static void import(UmlPackage * parent, File & f);


private:
    void import(File & f);

    void readObjects(File & f);


public:
    UmlUseCaseView * useCaseView();


protected:
    UmlUseCaseView * ucv;

};

#endif
