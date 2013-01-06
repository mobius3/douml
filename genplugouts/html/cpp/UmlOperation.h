#ifndef _UMLOPERATION_H
#define _UMLOPERATION_H


#include "UmlBaseOperation.h"
#include <q3cstring.h>
#include "Vector.h"

// This class manages 'operations', notes that the class 'UmlClassItem'
// is a mother class of all the class's children.
//
// You can modify it as you want (except the constructor)
class UmlOperation : public UmlBaseOperation
{
public:
    UmlOperation(void * id, const Q3CString & n) : UmlBaseOperation(id, n) {};

    //returns a string indicating the king of the element
    virtual Q3CString sKind();

    virtual void memo_ref();

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(Q3CString pfix, unsigned int rank, unsigned int level);

    static void ref_index();

    static void generate_index();


private:
    //produce the definition in Uml
    void gen_uml_decl();

    //produce the definition in C++
    void gen_cpp_decl(Q3CString s, bool descr);

    //produce the definition in Java
    void gen_java_decl(Q3CString s, bool descr);

    //produce the definition in Php
    void gen_php_decl(Q3CString s, bool descr);

    //produce the definition in Python
    void gen_python_decl(Q3CString s, bool descr);


public:
    Q3CString compute_name(Q3CString s);


protected:
    static Vector opers;

};

#endif
