
#include "UmlBasePackage.h"
#include "UmlPackage.h"
#include "UmlClassDiagram.h"

#include "UmlCom.h"
//#include "Tools/ApiCmd.h"
//Added by qt3to4:
#include <QByteArray>
UmlPackage * UmlBasePackage::create(UmlPackage * parent, const char * name)
{
    return (UmlPackage *) parent->create_(aPackage, name);
}

anItemKind UmlBasePackage::kind()
{
    return aPackage;
}

UmlClassDiagram * UmlBasePackage::associatedDiagram()
{
    read_if_needed_();

    return _assoc_diagram;
}

bool UmlBasePackage::set_AssociatedDiagram(UmlClassDiagram * d)
{
    UmlCom::send_cmd(_identifier, setAssocDiagramCmd, ((UmlBaseItem *) d)->_identifier);

    if (UmlCom::read_bool()) {
        _assoc_diagram = d;
        return TRUE;
    }
    else
        return FALSE;
}

#ifdef WITHCPP
const QByteArray & UmlBasePackage::cppSrcDir()
{
    read_if_needed_();

    return _cpp_src_dir;
}

bool UmlBasePackage::set_CppSrcDir(const QByteArray & s)
{
    return set_it_(_cpp_src_dir, s, setCppSrcDirCmd);
}

const QByteArray & UmlBasePackage::cppHDir()
{
    read_if_needed_();

    return _cpp_h_dir;
}

bool UmlBasePackage::set_CppHDir(const QByteArray & s)
{
    return set_it_(_cpp_h_dir, s, setCppHDirCmd);
}

QByteArray UmlBasePackage::cppNamespace()
{
    read_if_needed_();

    return _cpp_namespace;
}

bool UmlBasePackage::set_CppNamespace(const QByteArray & s)
{
    return set_it_(_cpp_namespace, s, setCppNamespaceCmd);
}

UmlPackage * UmlBasePackage::getNamespace(const QByteArray & n, const UmlBasePackage * p)
{
    UmlCom::send_cmd(packageGlobalCmd, findCppNamespaceCmd, (p) ? p->_identifier : 0, n);

    return (UmlPackage *) UmlBaseItem::read_();
}
#endif

#ifdef WITHJAVA
const QByteArray & UmlBasePackage::javaDir()
{
    read_if_needed_();

    return _java_dir;
}

bool UmlBasePackage::set_JavaDir(const QByteArray & s)
{
    return set_it_(_java_dir, s, setJavaDirCmd);
}

QByteArray UmlBasePackage::javaPackage()
{
    read_if_needed_();

    return _java_package;
}

bool UmlBasePackage::set_JavaPackage(const QByteArray & s)
{
    return set_it_(_java_package, s, setJavaPackageCmd);
}

UmlPackage * UmlBasePackage::getPackage(const QByteArray & n, const UmlBasePackage * p)
{
    UmlCom::send_cmd(packageGlobalCmd, findJavaPackageCmd, (p) ? p->_identifier : 0, n);

    return (UmlPackage *) UmlBaseItem::read_();
}
#endif

#ifdef WITHIDL
const QByteArray & UmlBasePackage::idlDir()
{
    read_if_needed_();

    return _idl_dir;
}

bool UmlBasePackage::set_IdlDir(const QByteArray & s)
{
    return set_it_(_idl_dir, s, setIdlDirCmd);
}

QByteArray UmlBasePackage::idlModule()
{
    read_if_needed_();

    return _idl_module;
}

bool UmlBasePackage::set_IdlModule(const QByteArray & s)
{
    return set_it_(_idl_module, s, setIdlModuleCmd);
}

UmlPackage * UmlBasePackage::getModule(const QByteArray & n, const UmlBasePackage * p)
{
    UmlCom::send_cmd(packageGlobalCmd, findIdlModuleCmd, (p) ? p->_identifier : 0, n);

    return (UmlPackage *) UmlBaseItem::read_();
}
#endif

UmlBasePackage * UmlBasePackage::getProject()
{
    UmlCom::send_cmd(packageGlobalCmd, getProjectCmd);

    return (UmlPackage *) UmlBaseItem::read_();
}

void UmlBasePackage::unload(bool rec, bool del)
{
    _assoc_diagram = 0;
#ifdef WITHCPP
    _cpp_src_dir = 0;
    _cpp_h_dir = 0;
    _cpp_namespace = 0;
#endif
#ifdef WITHJAVA
    _java_dir = 0;
    _java_package = 0;
#endif
#ifdef WITHIDL
    _idl_dir = 0;
    _idl_module = 0;
#endif
    UmlBaseItem::unload(rec, del);
}

void UmlBasePackage::read_uml_()
{
    _assoc_diagram = (UmlClassDiagram *) UmlBaseItem::read_();
    UmlBaseItem::read_uml_();
}

#ifdef WITHCPP
void UmlBasePackage::read_cpp_()
{
    _cpp_src_dir = UmlCom::read_string();
    _cpp_h_dir = UmlCom::read_string();
    _cpp_namespace = UmlCom::read_string();
}
#endif

#ifdef WITHJAVA
void UmlBasePackage::read_java_()
{
    _java_dir = UmlCom::read_string();
    _java_package = UmlCom::read_string();
}
#endif
#ifdef WITHPHP
void UmlBasePackage::read_php_()
{
    _php_dir = UmlCom::read_string();
    _php_namespace = UmlCom::read_string();
}
#endif

#ifdef WITHPYTHON
void UmlBasePackage::read_python_()
{
    _python_dir = UmlCom::read_string();
    _python_package = UmlCom::read_string();
}
#endif

#ifdef WITHIDL
void UmlBasePackage::read_idl_()
{
    _idl_dir = UmlCom::read_string();
    _idl_module = UmlCom::read_string();
}
#endif

