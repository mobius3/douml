#ifndef _UMLOPERATION_H
#define _UMLOPERATION_H


#include "UmlBaseOperation.h"
#include <q3cstring.h>
#include <q3ptrdict.h>
#include <q3asciidict.h>

class FileOut;

// This class manages 'operations', notes that the class 'UmlClassItem'
// is a mother class of all the class's children.
//
// You can modify it as you want (except the constructor)
class UmlOperation : public UmlBaseOperation {
  public:
    UmlOperation(void * id, const Q3CString & n) : UmlBaseOperation(id, n) {};

    virtual void write(FileOut & out);

    void write_exceptions(FileOut & out);

    void write_return_type(FileOut & out, Q3CString decl);

    void write_cpp_returntype(FileOut & out, Q3CString decl);

    void write_java_returntype(FileOut & out, Q3CString decl);

    void write_uml_params(FileOut & out);

    void write_cpp_java_params(FileOut & out, Q3CString decl);

    bool get_param(Q3CString s, int & index, Q3CString & r, Q3CString & kname, Q3CString & ktype, int & rank);

    // oper is sent/received in sequence/communication diagram, return event prefix
    // warning a class modify previous operation results
    const char * event(bool rec);

    // explicit operation/message sent in sequence/communication diagram, return event prefix
    static const char * event(const char * pfix, Q3CString msg);

    static void write_events(FileOut & out);


  protected:
    static int param_id;

    static Q3PtrDict<char> SentReceived;

    static Q3AsciiDict<char> Events;

};

#endif
