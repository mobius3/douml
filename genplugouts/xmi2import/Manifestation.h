#ifndef _MANIFESTATION_H
#define _MANIFESTATION_H



#include <q3valuelist.h>

class UmlArtifact;
class FileIn;
class Token;

class Manifestation
{
public:
    //for QValueList
    Manifestation() {}

    Manifestation(WrapperStr s, UmlArtifact * art, WrapperStr client) : name(s), artifact(art), utilized(client) {}

    static void import(FileIn & in, Token & token, UmlArtifact * artifact);

    static void solveThem();


protected:
    WrapperStr name;

    UmlArtifact * artifact;

    WrapperStr utilized;

    static Q3ValueList<Manifestation> All;

};

#endif
