#ifndef _UMLOPERATION_H
#define _UMLOPERATION_H


#include "UmlBaseOperation.h"

#include <q3ptrdict.h>
#include <q3asciidict.h>

class FileOut;

// This class manages 'operations', notes that the class 'UmlClassItem'
// is a mother class of all the class's children.
//
// You can modify it as you want (except the constructor)
class UmlOperation : public UmlBaseOperation
{
public:
    UmlOperation(void * id, const WrapperStr & n) : UmlBaseOperation(id, n) {};

    virtual void write(FileOut & out);

    void write_exceptions(FileOut & out);

    void write_return_type(FileOut & out, WrapperStr decl);

    void write_cpp_returntype(FileOut & out, WrapperStr decl);

    void write_java_returntype(FileOut & out, WrapperStr decl);

    void write_uml_params(FileOut & out);

    void write_cpp_java_params(FileOut & out, WrapperStr decl);

    bool get_param(WrapperStr s, int & index, WrapperStr & r, WrapperStr & kname, WrapperStr & ktype, int & rank);

    // oper is sent/received in sequence/communication diagram, return event prefix
    // warning a class modify previous operation results
    const char * event(bool rec);

    // explicit operation/message sent in sequence/communication diagram, return event prefix
    static const char * event(const char * pfix, WrapperStr msg);

    static void write_events(FileOut & out);


protected:
    static int param_id;

    static Q3PtrDict<char> SentReceived;

    static Q3AsciiDict<char> Events;

};

#endif
