#ifndef _MANIFESTATION_H
#define _MANIFESTATION_H


#include <q3cstring.h>
#include <q3valuelist.h>

class UmlArtifact;
class FileIn;
class Token;

class Manifestation {
  public:
    //for QValueList
    Manifestation(){}

    Manifestation(Q3CString s, UmlArtifact * art, Q3CString client) : name(s), artifact(art), utilized(client) {}

    static void import(FileIn & in, Token & token, UmlArtifact * artifact);

    static void solveThem();


  protected:
    Q3CString name;

    UmlArtifact * artifact;

    Q3CString utilized;

    static Q3ValueList<Manifestation> All;

};

#endif
