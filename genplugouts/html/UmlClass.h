#ifndef _UMLCLASS_H
#define _UMLCLASS_H


#include "UmlBaseClass.h"
#include <q3cstring.h>
#include "Vector.h"
#include <q3valuelist.h>

class UmlActualParameter;
class UmlFormalParameter;

// This class manages 'classes', notes that the class 'ClassItem'
// is a mother class of the class's children.
//
// You can modify it as you want (except the constructor)
class UmlClass : public UmlBaseClass
{
public:
    UmlClass(void * id, const Q3CString & n) : UmlBaseClass(id, n) {
        inherited_opers = 0;
    };

    //returns a string indicating the king of the element
    virtual Q3CString sKind();

    //set he html ref
    //set the classes list
    //set the operations list including inherited ones
    //set the daugther inheritance classes list
    virtual void memo_ref();

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(Q3CString pfix, unsigned int rank, unsigned int level);

    //generate the html definition in an own file

    void html();

    //generate the html definition except header/chapter in the current file

    void gen_html(Q3CString pfix, unsigned int rank, unsigned int level);

    //write a html ref to the class
    virtual void write();

    //write a html ref to the class going to an other html file
    virtual void write(Q3CString target);

    static void ref_index();

    static void generate_index();


private:
    void add_inherited_opers(Vector * ops);


protected:
    Vector * inherited_opers;

    static Vector classes;


private:
    //produce the definition in C++
    void gen_cpp_decl(Q3CString s, bool descr);

    //produce the definition in Java
    void gen_java_decl(Q3CString s, bool descr);

    //produce the definition in Php
    void gen_php_decl(Q3CString s, bool descr);

    //produce the definition in Python
    void gen_python_decl(Q3CString s, bool descr);

    void generate(const Q3ValueList<UmlActualParameter> a, UmlClass * mother, bool cpp);

    void generate(const Q3ValueList<UmlFormalParameter> f);

    void generics();


public:
    static void generate();


protected:
    Vector subClasses;


public:
    virtual bool chapterp();

};

#endif
