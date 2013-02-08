#ifndef _UMLUSECASEVIEW_H
#define _UMLUSECASEVIEW_H


#include "UmlBaseUseCaseView.h"

#include <q3ptrlist.h>

class FileOut;
class UmlItem;
class UmlUseCaseDiagram;

// This class manages 'use case view'
//
// You can modify it as you want (except the constructor)
class UmlUseCaseView : public UmlBaseUseCaseView
{
public:
    UmlUseCaseView(void * id, const WrapperStr & n) : UmlBaseUseCaseView(id, n) {};

    virtual void write(FileOut & out);

    //Memorize the relation in the package (or the view in case the views
    //are generated as package) containing the current element, to generate
    //the relation at the package/view level

    virtual void memo_relation(UmlItem * r);

    //Memorize the use case diagram in the package (or the view in case the views
    //are generated as package) containing the current element, to generate
    //the association use case / actor at the package/view level

    virtual void memo_ac_uc_assoc(UmlUseCaseDiagram * d);


protected:
    Q3PtrList<UmlItem> _relations;

    Q3PtrList<UmlUseCaseDiagram> _assocs;

};

#endif
