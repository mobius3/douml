#ifndef _ASSOCIATION_H
#define _ASSOCIATION_H


#include <q3cstring.h>
#include "aRelationKind.h"
#include <qmap.h>

class FileIn;
class Token;

// an unused role has an empty id
struct Role {
    Q3CString name;

    Q3CString id;

    // idref of the type containing it
    Q3CString idref;

    aRelationKind aggregate;

    bool navigable : 1;

    bool readOnly : 1;

    bool isDerived : 1;

    bool isDerivedUnion : 1;

    bool isOrdered : 1;

    bool isUnique : 1;

    bool isStatic : 1;

    Q3CString multiplicity;

    Q3CString visibility;

    Q3CString comment;

    Q3CString constraint;

    Q3CString defaultValue;

    Role() : aggregate(anAssociation), navigable(TRUE), readOnly(FALSE), isStatic(FALSE) {}

    void setMultiplicity(Q3CString v, bool upper, const char * dflt);

};

class Association {
  public:
    Association() : is_class_association(FALSE) {}

    void import(FileIn & in, Token & token);

    void set_class_association(){ is_class_association = TRUE; }
    // search for the association from its id
    
    static Association & get(Q3CString id, Q3CString s = "");

    static void solveThem();


  protected:
    Q3CString name;

    Role roles[2];

    static QMap<Q3CString, Association> All;

    bool is_class_association;


  private:
    void solve(Q3CString id);

};

#endif
