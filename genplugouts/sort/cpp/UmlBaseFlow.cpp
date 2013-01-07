
#include "UmlCom.h"
#include "UmlBaseFlow.h"
#include "UmlFlow.h"
#include "UmlActivityNode.h"
//Added by qt3to4:
#include <Q3CString>

anItemKind UmlBaseFlow::kind()
{
    return aFlow;
}

UmlFlow * UmlBaseFlow::create(UmlActivityNode * start, UmlActivityNode * end)
{
    UmlCom::send_cmd(start->_identifier, createCmd, aFlow,
                     end->_identifier);
    UmlFlow * result = (UmlFlow *) UmlBaseItem::read_();

    if (result != 0)
        start->reread_children_if_needed_();

    return result;
}

UmlActivityNode * UmlBaseFlow::target()
{
    read_if_needed_();
    return _target;
}

const Q3CString & UmlBaseFlow::weight()
{
    read_if_needed_();
    return _uml.weight;
}

bool UmlBaseFlow::set_Weight(const char * v)
{
    return set_it_(_uml.weight, v, setUmlActivityCmd);
}

const Q3CString & UmlBaseFlow::guard()
{
    read_if_needed_();
    return _uml.guard;
}

bool UmlBaseFlow::set_Guard(const char * v)
{
    return set_it_(_uml.guard, v, setUmlGuardCmd);
}

const Q3CString & UmlBaseFlow::selection()
{
    read_if_needed_();
    return _uml.selection;
}

bool UmlBaseFlow::set_Selection(const char * v)
{
    return set_it_(_uml.selection, v, setUmlEntryBehaviorCmd);
}

const Q3CString & UmlBaseFlow::transformation()
{
    read_if_needed_();
    return _uml.transformation;
}

bool UmlBaseFlow::set_Transformation(const char * v)
{
    return set_it_(_uml.transformation, v, setUmlExitBehaviorCmd);
}

#ifdef WITHCPP
const Q3CString & UmlBaseFlow::cppWeight()
{
    read_if_needed_();
    return _cpp.weight;
}

bool UmlBaseFlow::set_CppWeight(const char * v)
{
    return set_it_(_cpp.weight, v, setCppActivityCmd);
}

const Q3CString & UmlBaseFlow::cppGuard()
{
    read_if_needed_();
    return _cpp.guard;
}

bool UmlBaseFlow::set_CppGuard(const char * v)
{
    return set_it_(_cpp.guard, v, setCppGuardCmd);
}

const Q3CString & UmlBaseFlow::cppSelection()
{
    read_if_needed_();
    return _cpp.selection;
}

bool UmlBaseFlow::set_CppSelection(const char * v)
{
    return set_it_(_cpp.selection, v, setCppEntryBehaviorCmd);
}

const Q3CString & UmlBaseFlow::cppTransformation()
{
    read_if_needed_();
    return _cpp.transformation;
}

bool UmlBaseFlow::set_CppTransformation(const char * v)
{
    return set_it_(_cpp.transformation, v, setCppExitBehaviorCmd);
}
#endif

#ifdef WITHJAVA
const Q3CString & UmlBaseFlow::javaWeight()
{
    read_if_needed_();
    return _java.weight;
}

bool UmlBaseFlow::set_JavaWeight(const char * v)
{
    return set_it_(_java.weight, v, setJavaActivityCmd);
}

const Q3CString & UmlBaseFlow::javaGuard()
{
    read_if_needed_();
    return _java.guard;
}

bool UmlBaseFlow::set_JavaGuard(const char * v)
{
    return set_it_(_java.guard, v, setJavaGuardCmd);
}

const Q3CString & UmlBaseFlow::javaSelection()
{
    read_if_needed_();
    return _java.selection;
}

bool UmlBaseFlow::set_JavaSelection(const char * v)
{
    return set_it_(_java.selection, v, setJavaEntryBehaviorCmd);
}

const Q3CString & UmlBaseFlow::javaTransformation()
{
    read_if_needed_();
    return _java.transformation;
}

bool UmlBaseFlow::set_JavaTransformation(const char * v)
{
    return set_it_(_java.transformation, v, setJavaExitBehaviorCmd);
}
#endif

void UmlBaseFlow::unload(bool rec, bool del)
{
    _uml.unload();
#ifdef WITHCPP
    _cpp.unload();
#endif
#ifdef WITHJAVA
    _java.unload();
#endif
    UmlBaseItem::unload(rec, del);
}

void UmlBaseFlow::read_uml_()
{
    UmlBaseItem::read_uml_();
    _target = (UmlActivityNode *) UmlBaseItem::read_();
    _uml.read();
}

#ifdef WITHCPP
void UmlBaseFlow::read_cpp_()
{
    _cpp.read();
}
#endif

#ifdef WITHJAVA
void UmlBaseFlow::read_java_()
{
    _java.read();
}
#endif

