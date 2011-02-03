#ifndef _UMLITEM_H
#define _UMLITEM_H


#include <q3cstring.h>
#include <q3valuelist.h>
#include "UmlBaseItem.h"
#include <qstring.h>
#include "anItemKind.h"
#include <qmap.h>

#include "UmlTypeSpec.h"
#include "Association.h"
class FileIn;
class Token;
class UmlTypeSpec;

typedef void (*PFunc)(FileIn &, Token &, UmlItem *);
//  'element' has an unresolved reference
class Unresolved {
  public:
    static void addGeneralization(UmlItem * e, Q3CString & id, Q3CString cstr);

    static void addRef(UmlItem * e, Q3CString & id);

    //  for QValueList
    Unresolved(){};


  protected:
    Unresolved(UmlItem * e, Q3CString id, Q3CString cstr) : element(e), idref(id), constraint(cstr) {}

    UmlItem * element;

    Q3CString idref;

    Q3CString constraint;

    static Q3ValueList<Unresolved> Generalizations;

    static Q3ValueList<Unresolved> Refs;


  public:
    static void solveThem();

};

//  'element' has an unresolved reference
class UnresolvedWithContext {
  public:
    static void add(UmlItem * e, Q3CString id, int c);

    static void solveThem();

    //  for QValueList
    UnresolvedWithContext(){};


  protected:
    UnresolvedWithContext(UmlItem * e, Q3CString id, int c) : element(e), idref(id), context(c) {}

    UmlItem * element;

    Q3CString idref;

    int context;

    static Q3ValueList<UnresolvedWithContext> All;

};

class UnresolvedRelation {
  public:
    static void add(int ctx, Q3CString idFrom, Q3CString idTo, Q3CString label, Q3CString constraint);

    //  for QValueList
    UnresolvedRelation();


  protected:
    UnresolvedRelation(int ctx, Q3CString idFrom, Q3CString idTo, Q3CString label, Q3CString cnst)
      : context(ctx), from(idFrom), to(idTo), name(label), constraint(cnst) {}

    int context;

    Q3CString from;

    Q3CString to;

    Q3CString name;

    Q3CString constraint;

    static Q3ValueList<UnresolvedRelation> All;


  public:
    static void solveThem();

};

// This class is a mother class for all the other Uml* classes, this
// allows to generalize their management, declare virtual operations etc ...
//
// You can modify it as you want (except the constructor)
class UmlItem : public UmlBaseItem {
  public:
    UmlItem(void * id, const Q3CString & n) : UmlBaseItem(id, n) {};

    virtual ~UmlItem();

    Q3CString id() const {
      return _xmi_id;
    }

    //Import an xmi file, only allowed in a package
    virtual void import(QString path);

    void addItem(Q3CString id, FileIn & in);

    //look at the token kind to call the function managing
    //this case or bypass the token
    
    virtual void import(FileIn & in, Token & tk);

    //returns the first container for a 'kind', going up in the browser tree
    virtual UmlItem * container(anItemKind kind, Token & token, FileIn & in);

    //  call at end of import : try to solve reference
    //  does nothing at this level : never called
    virtual void solve(Q3CString idref);

    //  call at end of import : try to solve reference
    //  does nothing at this level : never called
    virtual void solve(int context, Q3CString idref);

    //  call at end of import : try to solve generalization dependencies and realization
    //  not from a class
    virtual void generalizeDependRealize(UmlItem * target, FileIn & in, int context, Q3CString label, Q3CString constraint);

    //  call at end of import : try to solve generalization dependencies and realization,
    //  not from a class
    virtual void solveGeneralizationDependencyRealization(int context, Q3CString idref, Q3CString label, Q3CString constraint);


  protected:
    //  try to solve type, return true is type already known
    //  else memorize unsolved couple if needed and return false
    bool setType(Q3CString idref, UmlTypeSpec & type);

    //  try to solve type, return true is type already known
    //  else memorize unsolved couple if needed and return false
    bool setType(Q3CString idref, int context, UmlTypeSpec & type);

    //  try to solve token being <type ..>, return true is type already known
    //  else memorize unsolved couple if needed and return false
    bool setType(Token & token, UmlTypeSpec & type);

    //  try to solve type, return true is type already known
    //  else memorize unsolved couple if needed and return false
    bool setType(Token & token, int context, UmlTypeSpec & type);


  public:
    //  element defined in a profile, if xmiId property defined update All
    
    void loadFromProfile();


  protected:
    //  try to solve type, return true if type already known
    //  and set 'type', else return false
    static bool getType(Q3CString idref, UmlTypeSpec & type);


  public:
    static void declareFct(Q3CString what, Q3CString type, PFunc fct);

    static PFunc getFct(const Token & tk);

    static Q3CString readComment(FileIn & in, Token & token);

    static void init();

    static void importDocumentation(FileIn & in, Token & token, UmlItem * where);

    static void importComment(FileIn & in, Token & token, UmlItem * where);

    static void importExtension(FileIn & in, Token & token, UmlItem * where);

    static void importOpaqueDef(FileIn & in, Token & token, UmlItem * where);

    static void importGeneralization(FileIn & in, Token & token, UmlItem * where);

    static void importDependency(FileIn & in, Token & token, UmlItem * where);

    static void importRealization(FileIn & in, Token & token, UmlItem * where);

    //
    
    static void incoming(FileIn & in, Token & token, UmlItem * where);

    //
    
    static void outgoing(FileIn & in, Token & token, UmlItem * where);

    static Q3CString legalName(Q3CString s);

    static bool fromEclipse();

    static Q3CString readConstraint(FileIn & in, Token & token);

    static QMap<Q3CString, Q3CString> OpaqueDefs;


  protected:
    static bool FromBouml;

    static bool FromEclipse;


  public:
    static QMap<Q3CString, UmlItem *> All;


  protected:
    static QMap<Q3CString, PFunc> Functions;

    static QMap<Q3CString, UmlTypeSpec> PrimitiveTypes;

    static QMap<Q3CString,UmlItem*> Incomings;

    static QMap<Q3CString, UmlItem*> Outgoings;


  private:
    Q3CString _xmi_id;

};

#endif
