#ifndef _UMLITEM_H
#define _UMLITEM_H



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
class Unresolved
{
public:
    static void addGeneralization(UmlItem * e, WrapperStr & id, WrapperStr cstr);

    static void addRef(UmlItem * e, WrapperStr & id);

    //  for QValueList
    Unresolved() {};


protected:
    Unresolved(UmlItem * e, WrapperStr id, WrapperStr cstr) : element(e), idref(id), constraint(cstr) {}

    UmlItem * element;

    WrapperStr idref;

    WrapperStr constraint;

    static Q3ValueList<Unresolved> Generalizations;

    static Q3ValueList<Unresolved> Refs;


public:
    static void solveThem();

};

//  'element' has an unresolved reference
class UnresolvedWithContext
{
public:
    static void add(UmlItem * e, WrapperStr id, int c);

    static void solveThem();

    //  for QValueList
    UnresolvedWithContext() {};


protected:
    UnresolvedWithContext(UmlItem * e, WrapperStr id, int c) : element(e), idref(id), context(c) {}

    UmlItem * element;

    WrapperStr idref;

    int context;

    static Q3ValueList<UnresolvedWithContext> All;

};

class UnresolvedRelation
{
public:
    static void add(int ctx, WrapperStr idFrom, WrapperStr idTo, WrapperStr label, WrapperStr constraint);

    //  for QValueList
    UnresolvedRelation();


protected:
    UnresolvedRelation(int ctx, WrapperStr idFrom, WrapperStr idTo, WrapperStr label, WrapperStr cnst)
        : context(ctx), from(idFrom), to(idTo), name(label), constraint(cnst) {}

    int context;

    WrapperStr from;

    WrapperStr to;

    WrapperStr name;

    WrapperStr constraint;

    static Q3ValueList<UnresolvedRelation> All;


public:
    static void solveThem();

};

// This class is a mother class for all the other Uml* classes, this
// allows to generalize their management, declare virtual operations etc ...
//
// You can modify it as you want (except the constructor)
class UmlItem : public UmlBaseItem
{
public:
    UmlItem(void * id, const WrapperStr & n) : UmlBaseItem(id, n) {};

    virtual ~UmlItem();

    WrapperStr id() const {
        return _xmi_id;
    }

    //Import an xmi file, only allowed in a package
    virtual void import(QString path);

    void addItem(WrapperStr id, FileIn & in);

    //look at the token kind to call the function managing
    //this case or bypass the token

    virtual void import(FileIn & in, Token & tk);

    //returns the first container for a 'kind', going up in the browser tree
    virtual UmlItem * container(anItemKind kind, Token & token, FileIn & in);

    //  call at end of import : try to solve reference
    //  does nothing at this level : never called
    virtual void solve(WrapperStr idref);

    //  call at end of import : try to solve reference
    //  does nothing at this level : never called
    virtual void solve(int context, WrapperStr idref);

    //  call at end of import : try to solve generalization dependencies and realization
    //  not from a class
    virtual void generalizeDependRealize(UmlItem * target, FileIn & in, int context, WrapperStr label, WrapperStr constraint);

    //  call at end of import : try to solve generalization dependencies and realization,
    //  not from a class
    virtual void solveGeneralizationDependencyRealization(int context, WrapperStr idref, WrapperStr label, WrapperStr constraint);


protected:
    //  try to solve type, return true is type already known
    //  else memorize unsolved couple if needed and return false
    bool setType(WrapperStr idref, UmlTypeSpec & type);

    //  try to solve type, return true is type already known
    //  else memorize unsolved couple if needed and return false
    bool setType(WrapperStr idref, int context, UmlTypeSpec & type);

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
    static bool getType(WrapperStr idref, UmlTypeSpec & type);


public:
    static void declareFct(WrapperStr what, WrapperStr type, PFunc fct);

    static PFunc getFct(const Token & tk);

    static WrapperStr readComment(FileIn & in, Token & token);

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

    static WrapperStr legalName(WrapperStr s);

    static bool fromEclipse();

    static WrapperStr readConstraint(FileIn & in, Token & token);

    static QMap<QString, WrapperStr> OpaqueDefs;


protected:
    static bool FromBouml;

    static bool FromEclipse;


public:
    static QMap<QString, UmlItem *> All;


protected:
    static QMap<QString, PFunc> Functions;

    static QMap<QString, UmlTypeSpec> PrimitiveTypes;

    static QMap<QString, UmlItem *> Incomings;

    static QMap<QString, UmlItem *> Outgoings;


private:
    WrapperStr _xmi_id;

};

#endif
