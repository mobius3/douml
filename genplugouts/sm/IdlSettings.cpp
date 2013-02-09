#ifdef WITHIDL


#include "IdlSettings.h"

#include "UmlCom.h"
#include "UmlSettings.h"
//#include "Tools/ApiCmd.h"
#include "UmlBuiltin.h"
#include "UmlStereotype.h"
//Added by qt3to4:
#include <Q3CString>
bool IdlSettings::useDefaults()
{
    UmlCom::send_cmd(idlSettingsCmd, getIdlUseDefaultsCmd);
    return UmlCom::read_bool();
}

bool IdlSettings::set_UseDefaults(bool y)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlUseDefaultsCmd, (char) y);
    return UmlCom::read_bool();
}

Q3CString IdlSettings::type(Q3CString s)
{
    read_if_needed_();

    UmlBuiltin * b = UmlSettings::_map_builtins.find(s);

    return (b) ? b->idl : s;
}

bool IdlSettings::set_Type(Q3CString s, Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlTypeCmd, s, v);

    if (UmlCom::read_bool()) {
        UmlBuiltin * b = UmlSettings::_map_builtins.find(s);

        if (b == 0)
            b = UmlSettings::add_type(s);

        b->idl = v;

        return TRUE;
    }
    else
        return FALSE;
}

Q3CString IdlSettings::umlType(Q3CString s)
{
    read_if_needed_();

    return UmlSettings::uml_type(s, &UmlBuiltin::idl);
}

Q3CString IdlSettings::relationAttributeStereotype(const Q3CString & s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_relation_attribute_stereotypes.find(s);

    return (b) ? b->idl : s;
}

bool IdlSettings::set_RelationAttributeStereotype(Q3CString s, Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlRelationAttributeStereotypeCmd, s, v);

    if (UmlCom::read_bool()) {
        UmlStereotype * st = UmlSettings::_map_relation_attribute_stereotypes.find(s);

        if (st == 0)
            st = UmlSettings::add_rel_attr_stereotype(s);

        st->idl = v;

        return TRUE;
    }
    else
        return FALSE;
}

Q3CString IdlSettings::relationAttributeUmlStereotype(Q3CString s)
{
    read_if_needed_();

    return UmlSettings::uml_rel_attr_stereotype(s, &UmlStereotype::idl);
}

Q3CString IdlSettings::classStereotype(Q3CString s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_class_stereotypes.find(s);

    return (b) ? b->idl : s;
}

bool IdlSettings::set_ClassStereotype(Q3CString s, Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlClassStereotypeCmd, s, v);

    if (UmlCom::read_bool()) {
        UmlStereotype * st = UmlSettings::_map_class_stereotypes.find(s);

        if (st == 0)
            st = UmlSettings::add_class_stereotype(s);

        st->idl = v;

        return TRUE;
    }
    else
        return FALSE;
}

Q3CString IdlSettings::classUmlStereotype(Q3CString s)
{
    read_if_needed_();

    return UmlSettings::uml_class_stereotype(s, &UmlStereotype::idl);
}

Q3CString IdlSettings::include(Q3CString s)
{
    read_if_needed_();

    Q3CString * r = _map_includes[s];

    return (r) ? *r : Q3CString(0);
}

bool IdlSettings::set_Include(Q3CString s, Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlIncludeCmd, s, v);

    if (UmlCom::read_bool()) {
        Q3CString * r = _map_includes.take(s);

        if (!v.isEmpty())
            _map_includes.insert(s, new Q3CString(v));

        if (r)
            delete r;

        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::rootDir()
{
    read_if_needed_();

    return _root;
}

bool IdlSettings::set_RootDir(Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlRootDirCmd, v);

    if (UmlCom::read_bool()) {
        _root = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::sourceContent()
{
    read_if_needed_();

    return _src_content;
}

bool IdlSettings::set_SourceContent(Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlSourceContentCmd, v);

    if (UmlCom::read_bool()) {
        _src_content = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::sourceExtension()
{
    read_if_needed_();

    return _ext;
}

bool IdlSettings::set_SourceExtension(Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlSourceExtensionCmd, v);

    if (UmlCom::read_bool()) {
        _ext = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::interfaceDecl()
{
    read_if_needed_();

    return _interface_decl;
}

bool IdlSettings::set_InterfaceDecl(Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlInterfaceDeclCmd, v);

    if (UmlCom::read_bool()) {
        _interface_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::valuetypeDecl()
{
    read_if_needed_();

    return _valuetype_decl;
}

bool IdlSettings::set_ValuetypeDecl(Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlValuetypeDeclCmd, v);

    if (UmlCom::read_bool()) {
        _valuetype_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::externalClassDecl()
{
    read_if_needed_();

    return _external_class_decl;
}

bool IdlSettings::set_ExternalClassDecl(Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlExternalClassDeclCmd, v);

    if (UmlCom::read_bool()) {
        _external_class_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::structDecl()
{
    read_if_needed_();

    return _struct_decl;
}

bool IdlSettings::set_StructDecl(Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlStructDeclCmd, v);

    if (UmlCom::read_bool()) {
        _struct_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::typedefDecl()
{
    read_if_needed_();

    return _typedef_decl;
}

bool IdlSettings::set_TypedefDecl(Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlTypedefDeclCmd, v);

    if (UmlCom::read_bool()) {
        _typedef_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::exceptionDecl()
{
    read_if_needed_();

    return _exception_decl;
}

bool IdlSettings::set_ExceptionDecl(Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlExceptionDeclCmd, v);

    if (UmlCom::read_bool()) {
        _exception_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::unionDecl()
{
    read_if_needed_();

    return _union_decl;
}

bool IdlSettings::set_UnionDecl(Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlUnionDeclCmd, v);

    if (UmlCom::read_bool()) {
        _union_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::enumDecl()
{
    read_if_needed_();

    return _enum_decl;
}

bool IdlSettings::set_EnumDecl(Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlEnumDeclCmd, v);

    if (UmlCom::read_bool()) {
        _enum_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::attributeDecl(const char * multiplicity)
{
    read_if_needed_();

    return _attr_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_AttributeDecl(const char * multiplicity, Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlAttributeDeclCmd, multiplicity, v);

    if (UmlCom::read_bool()) {
        _attr_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::valuetypeAttributeDecl(const char * multiplicity)
{
    read_if_needed_();

    return _valuetype_attr_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_ValuetypeAttributeDecl(const char * multiplicity, Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlValuetypeAttributeDeclCmd, multiplicity, v);

    if (UmlCom::read_bool()) {
        _valuetype_attr_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::unionItemDecl(const char * multiplicity)
{
    read_if_needed_();

    return _union_item_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_UnionItemDecl(const char * multiplicity, Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlUnionItemDeclCmd, multiplicity, v);

    if (UmlCom::read_bool()) {
        _union_item_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::enumItemDecl()
{
    read_if_needed_();

    return _enum_item_decl;
}

bool IdlSettings::set_EnumItemDecl(Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlEnumItemDeclCmd, v);

    if (UmlCom::read_bool()) {
        _enum_item_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::constDecl(const char * multiplicity)
{
    read_if_needed_();

    return _const_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_ConstDecl(const char * multiplicity, Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlConstDeclCmd, multiplicity, v);

    if (UmlCom::read_bool()) {
        _const_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::relationDecl(const char * multiplicity)
{
    read_if_needed_();

    return _rel_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_RelationDecl(const char * multiplicity, Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlRelationDeclCmd, multiplicity, v);

    if (UmlCom::read_bool()) {
        _rel_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::valuetypeRelationDecl(const char * multiplicity)
{
    read_if_needed_();

    return _valuetype_rel_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_ValuetypeRelationDecl(const char * multiplicity, Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlValuetypeRelationDeclCmd, multiplicity, v);

    if (UmlCom::read_bool()) {
        _valuetype_rel_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::unionRelationDecl(const char * multiplicity)
{
    read_if_needed_();

    return _union_rel_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_UnionRelationDecl(const char * multiplicity, Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlUnionRelationDeclCmd, multiplicity, v);

    if (UmlCom::read_bool()) {
        _union_rel_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::operationDecl()
{
    read_if_needed_();

    return _oper_decl;
}

bool IdlSettings::set_OperationDecl(Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlOperationDeclCmd, v);

    if (UmlCom::read_bool()) {
        _oper_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::getName()
{
    read_if_needed_();

    return _get_name;
}

bool IdlSettings::set_GetName(Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlGetNameCmd, v);

    if (UmlCom::read_bool()) {
        _get_name = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & IdlSettings::setName()
{
    read_if_needed_();

    return _set_name;
}

bool IdlSettings::set_SetName(Q3CString v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlSetNameCmd, v);

    if (UmlCom::read_bool()) {
        _set_name = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool IdlSettings::isSetOneway()
{
    read_if_needed_();

    return _is_set_oneway;
}

bool IdlSettings::set_IsSetOneway(bool v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlIsSetOneWayCmd, v);

    if (UmlCom::read_bool()) {
        _is_set_oneway = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool IdlSettings::_defined;

Q3CString IdlSettings::_root;

Q3CString IdlSettings::_interface_decl;

Q3CString IdlSettings::_valuetype_decl;

Q3CString IdlSettings::_struct_decl;

Q3CString IdlSettings::_typedef_decl;

Q3CString IdlSettings::_exception_decl;

Q3CString IdlSettings::_union_decl;

Q3CString IdlSettings::_enum_decl;

Q3CString IdlSettings::_external_class_decl;

Q3CString IdlSettings::_attr_decl[3/*multiplicity*/];

Q3CString IdlSettings::_valuetype_attr_decl[3/*multiplicity*/];

Q3CString IdlSettings::_union_item_decl[3/*multiplicity*/];

Q3CString IdlSettings::_enum_item_decl;

Q3CString IdlSettings::_const_decl[3/*multiplicity*/];

Q3CString IdlSettings::_rel_decl[3/*multiplicity*/];

Q3CString IdlSettings::_valuetype_rel_decl[3/*multiplicity*/];

Q3CString IdlSettings::_union_rel_decl[3/*multiplicity*/];

Q3CString IdlSettings::_oper_decl;

Q3CString IdlSettings::_get_name;

Q3CString IdlSettings::_set_name;

bool IdlSettings::_is_set_oneway;

Q3CString IdlSettings::_src_content;

Q3CString IdlSettings::_ext;

Q3Dict<Q3CString> IdlSettings::_map_includes;

void IdlSettings::read_()
{
    _root = UmlCom::read_string();

    unsigned n;
    unsigned index;

    n = UmlCom::read_unsigned();

    for (index = 0; index != n; index += 1) {
        UmlSettings::_builtins[index].idl = UmlCom::read_string();
    }

    n = UmlCom::read_unsigned();

    for (index = 0; index != n; index += 1)
        UmlSettings::_relation_attribute_stereotypes[index].idl = UmlCom::read_string();

    n = UmlCom::read_unsigned();

    for (index = 0; index != n; index += 1)
        UmlSettings::_class_stereotypes[index].idl = UmlCom::read_string();

    n = UmlCom::read_unsigned();
    _map_includes.clear();

    if (n > _map_includes.size())
        _map_includes.resize(n);

    for (index = 0; index != n; index += 1) {
        Q3CString t = UmlCom::read_string();
        Q3CString i = UmlCom::read_string();

        _map_includes.insert(t, new Q3CString(i));
    }

    _src_content = UmlCom::read_string();
    _ext = UmlCom::read_string();

    _interface_decl = UmlCom::read_string();
    _valuetype_decl = UmlCom::read_string();
    _struct_decl = UmlCom::read_string();
    _typedef_decl = UmlCom::read_string();
    _exception_decl = UmlCom::read_string();
    _union_decl = UmlCom::read_string();
    _enum_decl = UmlCom::read_string();
    _external_class_decl = UmlCom::read_string();

    for (index = 0; index != 3; index += 1)
        _attr_decl[index] = UmlCom::read_string();

    for (index = 0; index != 3; index += 1)
        _valuetype_attr_decl[index] = UmlCom::read_string();

    for (index = 0; index != 3; index += 1)
        _union_item_decl[index] = UmlCom::read_string();

    _enum_item_decl = UmlCom::read_string();

    for (index = 0; index != 3; index += 1)
        _const_decl[index] = UmlCom::read_string();

    for (index = 0; index != 3; index += 1) {
        _rel_decl[index] = UmlCom::read_string();
        _valuetype_rel_decl[index] = UmlCom::read_string();
        _union_rel_decl[index] = UmlCom::read_string();
    }

    _oper_decl = UmlCom::read_string();
    _get_name = UmlCom::read_string();
    _set_name = UmlCom::read_string();
    _is_set_oneway = UmlCom::read_bool();
}

void IdlSettings::read_if_needed_()
{
    UmlSettings::read_if_needed_();

    if (!_defined) {
        UmlCom::send_cmd(idlSettingsCmd, getIdlSettingsCmd);
        read_();
        _defined = TRUE;
    }
}


#endif
