#ifndef _UMLCLASS_H
#define _UMLCLASS_H


#include "UmlBaseClass.h"
#include <q3cstring.h>
#include "anItemKind.h"
#include <q3valuelist.h>
#include <qmap.h>

class UmlItem;
class Token;
class FileIn;
class UmlTypeSpec;

// This class manages 'classes', notes that the class 'ClassItem'
// is a mother class of the class's children.
//
// You can modify it as you want (except the constructor)
class UmlClass : public UmlBaseClass {
  public:
    UmlClass(void * id, const Q3CString & n) : UmlBaseClass(id, n) { NumberOf += 1; };

    //returns the first container for a 'kind', going up in the browser tree
    virtual UmlItem * container(anItemKind kind, Token & token, FileIn & in);

    static void init();

    //import the class starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

    //import the primitive type starting by 'tk' inside 'where'
    static void importPrimitiveType(FileIn & in, Token & token, UmlItem * where);

    //  call at end of import : try to solve generalization dependencies and realization
    
    virtual void generalizeDependRealize(UmlItem * target, FileIn & in, int context, Q3CString label, Q3CString constraint);

    //  call at end of import : try to solve generalization dependencies, realization
    //
    
    virtual void solveGeneralizationDependencyRealization(int context, Q3CString idref, Q3CString label, Q3CString constraint);

    static int numberOf() { return NumberOf; };

    static int numberOfStereotype() { return NumberOfStereotype; };

    //return the class owing the signature whose id is given in parameter,
    //may return 0
    
    static UmlClass * signature(Q3CString id);

    //returns the rank of the formal from its id,
    //return -1 if not found and produce error message
    int formalRank(Q3CString id);

    // if this generalize tmpl return true
    // else if this realize tmpl, set stereotype to bind and return true
    // else add a realization to tmpl stereotyped bind and return true
    // return FALSE on error
    
    bool bind(UmlClass * tmpl);

    // the class is a stereotype extending mcl
    void extend(Q3CString mcl);

    //if the token is a stereotype application give prof:st and the names of the attribute
    //specifying the element on which the stereotype is applied and return TRUE
    static bool isAppliedStereotype(Token & tk, Q3CString & prof_st, Q3ValueList<Q3CString> & base_v);

    static bool isPrimitiveType(Token & token, UmlTypeSpec & ts);


  private:
    void readFormal(FileIn & in, Token & token);

    UmlClass * addMetaclass(Q3CString mclname, const char * mclpath);


  protected:
    static int NumberOf;

    static int NumberOfStereotype;

    //xmiId of the formals following formals order
    Q3ValueList<Q3CString> formalsId;

    //associate the class owning the template signature with the signature id
    static QMap<Q3CString, UmlClass *> signatures;

};

#endif
