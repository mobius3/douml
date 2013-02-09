#ifndef _UMLCOMPONENT_H
#define _UMLCOMPONENT_H


#include "UmlBaseComponent.h"

#include "anItemKind.h"

class FileIn;
class Token;
class UmlItem;

// This class manages 'components'
//
// You can modify it as you want (except the constructor)
class UmlComponent : public UmlBaseComponent
{
public:
    UmlComponent(void * id, const WrapperStr & n) : UmlBaseComponent(id, n) {
        NumberOf += 1;
    };

    static void init();

    //import the component starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

    void manageInterface(Token & token, FileIn & in);

    //returns the first container for a 'kind', going up in the browser tree
    virtual UmlItem * container(anItemKind kind, Token & token, FileIn & in);

    //  call at end of import : try to solve interfaces
    virtual void solve(int context, WrapperStr idref);

    //  call at end of import : try to solve generalization dependencies and realization
    //  not from a class
    virtual void generalizeDependRealize(UmlItem * target, FileIn & in, int context, WrapperStr label, WrapperStr constraint);

    //  call at end of import : try to solve generalization dependencies and realization,
    //  not from a class
    virtual void solveGeneralizationDependencyRealization(int context, WrapperStr idref, WrapperStr label, WrapperStr constraint);

    static int numberOf() {
        return NumberOf;
    };


protected:
    static int NumberOf;

};

#endif
