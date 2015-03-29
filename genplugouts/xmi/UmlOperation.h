#ifndef _UMLOPERATION_H
#define _UMLOPERATION_H


#include "UmlBaseOperation.h"
#include <QByteArray>

class FileOut;

// This class manages 'operations', notes that the class 'UmlClassItem'
// is a mother class of all the class's children.
//
// You can modify it as you want (except the constructor)
class UmlOperation : public UmlBaseOperation
{
public:
    UmlOperation(void * id, const QByteArray & n) : UmlBaseOperation(id, n) {};

    virtual bool write_if_needed(FileOut & out);

    void write_return_type(FileOut & out, QByteArray decl);

    void write_cpp_returntype(FileOut & out, QByteArray decl);

    void write_java_returntype(FileOut & out, QByteArray decl);

    void write_uml_params(FileOut & out);

    void write_cpp_java_params(FileOut & out, QByteArray decl);

    bool get_param(QByteArray s, int & index, QByteArray & r, QByteArray & kname, QByteArray & ktype, int & rank);


protected:
    static int param_id;

};

#endif
