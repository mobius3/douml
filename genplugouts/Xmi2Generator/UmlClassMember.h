#ifndef _UMLCLASSMEMBER_H
#define _UMLCLASSMEMBER_H



#include "UmlBaseClassMember.h"

class FileOut;
class UmlTypeSpec;

// This class globaly manages class's relations, attributes, operations
// and sub-classes
//
// You can modify it as you want (except the constructor)
class UmlClassMember : public UmlBaseClassMember
{
public:
    UmlClassMember(void * id, const WrapperStr & n) : UmlBaseClassMember(id, n) {};

    void write_scope(FileOut & out);

    void write_visibility(FileOut & out);

    void write_annotation(FileOut & out);

    void write_constraint(FileOut & out);

    //  return the true name of the item

    WrapperStr true_name(WrapperStr name, WrapperStr decl);

    static bool identChar(QCharRef);

    //The keyword link to the language are removed/replaced
    //Have to remove the name and type keywords given in argument,
    //and to remove the initial value.
    //t.type != 0 or t.explicit_type != ""
    static void write_type(FileOut & out, const UmlTypeSpec & t, WrapperStr s, const char * k_name, const char * k_type);

    static void remove_comments(WrapperStr & s);

};

#endif
