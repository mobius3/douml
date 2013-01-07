#ifndef _UMLOPERATION_H
#define _UMLOPERATION_H


#include "UmlBaseOperation.h"
#include <q3cstring.h>

class FileOut;

// This class manages 'operations', notes that the class 'UmlClassItem'
// is a mother class of all the class's children.
//
// You can modify it as you want (except the constructor)
class UmlOperation : public UmlBaseOperation
{
public:
    UmlOperation(void * id, const Q3CString & n) : UmlBaseOperation(id, n) {};

    virtual bool write_if_needed(FileOut & out);

    void write_return_type(FileOut & out, Q3CString decl);

    void write_cpp_returntype(FileOut & out, Q3CString decl);

    void write_java_returntype(FileOut & out, Q3CString decl);

    void write_uml_params(FileOut & out);

    void write_cpp_java_params(FileOut & out, Q3CString decl);

    bool get_param(Q3CString s, int & index, Q3CString & r, Q3CString & kname, Q3CString & ktype, int & rank);


protected:
    static int param_id;

};

#endif
