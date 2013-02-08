#ifdef WITHIDL


#include "IdlSettings.h"

#include "UmlCom.h"
#include "UmlSettings.h"
#include "Tools/ApiCmd.h"
#include "UmlBuiltin.h"
#include "UmlStereotype.h"
//Added by qt3to4:
#include "misc/mystr.h"
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

WrapperStr IdlSettings::type(WrapperStr s)
{
    read_if_needed_();

    UmlBuiltin * b = UmlSettings::_map_builtins.find(s);

    return (b) ? b->idl : s;
}

bool IdlSettings::set_Type(WrapperStr s, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlTypeCmd, (const char *)s, (const char *)v); //[jasa] ambiguous call

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

WrapperStr IdlSettings::umlType(WrapperStr s)
{
    read_if_needed_();

    return UmlSettings::uml_type(s, &UmlBuiltin::idl);
}

WrapperStr IdlSettings::relationAttributeStereotype(const WrapperStr & s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_relation_attribute_stereotypes.find(s);

    return (b) ? b->idl : s;
}

bool IdlSettings::set_RelationAttributeStereotype(WrapperStr s, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlRelationAttributeStereotypeCmd, (const char *)s, (const char *)v); //[jasa] ambiguous call

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

WrapperStr IdlSettings::relationAttributeUmlStereotype(WrapperStr s)
{
    read_if_needed_();

    return UmlSettings::uml_rel_attr_stereotype(s, &UmlStereotype::idl);
}

WrapperStr IdlSettings::classStereotype(WrapperStr s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_class_stereotypes.find(s);

    return (b) ? b->idl : s;
}

bool IdlSettings::set_ClassStereotype(WrapperStr s, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlClassStereotypeCmd, (const char *)s, (const char *)v); //[jasa] ambiguous call

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

WrapperStr IdlSettings::classUmlStereotype(WrapperStr s)
{
    read_if_needed_();

    return UmlSettings::uml_class_stereotype(s, &UmlStereotype::idl);
}

WrapperStr IdlSettings::include(WrapperStr s)
{
    read_if_needed_();

    WrapperStr * r = _map_includes[s];

    return (r) ? *r : WrapperStr(0);
}

bool IdlSettings::set_Include(WrapperStr s, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlIncludeCmd, (const char *)s, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        WrapperStr * r = _map_includes.take(s);

        if (!v.isEmpty())
            _map_includes.insert(s, new WrapperStr(v));

        if (r)
            delete r;

        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::rootDir()
{
    read_if_needed_();

    return _root;
}

bool IdlSettings::set_RootDir(WrapperStr v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlRootDirCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _root = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::sourceContent()
{
    read_if_needed_();

    return _src_content;
}

bool IdlSettings::set_SourceContent(WrapperStr v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlSourceContentCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _src_content = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::sourceExtension()
{
    read_if_needed_();

    return _ext;
}

bool IdlSettings::set_SourceExtension(WrapperStr v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlSourceExtensionCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _ext = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::interfaceDecl()
{
    read_if_needed_();

    return _interface_decl;
}

bool IdlSettings::set_InterfaceDecl(WrapperStr v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlInterfaceDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _interface_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::valuetypeDecl()
{
    read_if_needed_();

    return _valuetype_decl;
}

bool IdlSettings::set_ValuetypeDecl(WrapperStr v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlValuetypeDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _valuetype_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::externalClassDecl()
{
    read_if_needed_();

    return _external_class_decl;
}

bool IdlSettings::set_ExternalClassDecl(WrapperStr v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlExternalClassDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _external_class_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::structDecl()
{
    read_if_needed_();

    return _struct_decl;
}

bool IdlSettings::set_StructDecl(WrapperStr v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlStructDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _struct_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::typedefDecl()
{
    read_if_needed_();

    return _typedef_decl;
}

bool IdlSettings::set_TypedefDecl(WrapperStr v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlTypedefDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _typedef_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::exceptionDecl()
{
    read_if_needed_();

    return _exception_decl;
}

bool IdlSettings::set_ExceptionDecl(WrapperStr v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlExceptionDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _exception_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::unionDecl()
{
    read_if_needed_();

    return _union_decl;
}

bool IdlSettings::set_UnionDecl(WrapperStr v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlUnionDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _union_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::enumDecl()
{
    read_if_needed_();

    return _enum_decl;
}

bool IdlSettings::set_EnumDecl(WrapperStr v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlEnumDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _enum_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::attributeDecl(const char * multiplicity)
{
    read_if_needed_();

    return _attr_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_AttributeDecl(const char * multiplicity, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlAttributeDeclCmd, multiplicity, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _attr_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::valuetypeAttributeDecl(const char * multiplicity)
{
    read_if_needed_();

    return _valuetype_attr_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_ValuetypeAttributeDecl(const char * multiplicity, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlValuetypeAttributeDeclCmd, multiplicity, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _valuetype_attr_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::unionItemDecl(const char * multiplicity)
{
    read_if_needed_();

    return _union_item_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_UnionItemDecl(const char * multiplicity, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlUnionItemDeclCmd, multiplicity, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _union_item_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::enumItemDecl()
{
    read_if_needed_();

    return _enum_item_decl;
}

bool IdlSettings::set_EnumItemDecl(WrapperStr v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlEnumItemDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _enum_item_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::constDecl(const char * multiplicity)
{
    read_if_needed_();

    return _const_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_ConstDecl(const char * multiplicity, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlConstDeclCmd, multiplicity, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _const_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::relationDecl(const char * multiplicity)
{
    read_if_needed_();

    return _rel_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_RelationDecl(const char * multiplicity, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlRelationDeclCmd, multiplicity, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _rel_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::valuetypeRelationDecl(const char * multiplicity)
{
    read_if_needed_();

    return _valuetype_rel_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_ValuetypeRelationDecl(const char * multiplicity, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlValuetypeRelationDeclCmd, multiplicity, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _valuetype_rel_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::unionRelationDecl(const char * multiplicity)
{
    read_if_needed_();

    return _union_rel_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool IdlSettings::set_UnionRelationDecl(const char * multiplicity, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(idlSettingsCmd, setIdlUnionRelationDeclCmd, multiplicity, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _union_rel_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::operationDecl()
{
    read_if_needed_();

    return _oper_decl;
}

bool IdlSettings::set_OperationDecl(WrapperStr v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlOperationDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _oper_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::getName()
{
    read_if_needed_();

    return _get_name;
}

bool IdlSettings::set_GetName(WrapperStr v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlGetNameCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _get_name = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & IdlSettings::setName()
{
    read_if_needed_();

    return _set_name;
}

bool IdlSettings::set_SetName(WrapperStr v)
{
    UmlCom::send_cmd(idlSettingsCmd, setIdlSetNameCmd, (const char *)v); //[jasa] ambiguous call

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

WrapperStr IdlSettings::_root;

WrapperStr IdlSettings::_interface_decl;

WrapperStr IdlSettings::_valuetype_decl;

WrapperStr IdlSettings::_struct_decl;

WrapperStr IdlSettings::_typedef_decl;

WrapperStr IdlSettings::_exception_decl;

WrapperStr IdlSettings::_union_decl;

WrapperStr IdlSettings::_enum_decl;

WrapperStr IdlSettings::_external_class_decl;

WrapperStr IdlSettings::_attr_decl[3/*multiplicity*/];

WrapperStr IdlSettings::_valuetype_attr_decl[3/*multiplicity*/];

WrapperStr IdlSettings::_union_item_decl[3/*multiplicity*/];

WrapperStr IdlSettings::_enum_item_decl;

WrapperStr IdlSettings::_const_decl[3/*multiplicity*/];

WrapperStr IdlSettings::_rel_decl[3/*multiplicity*/];

WrapperStr IdlSettings::_valuetype_rel_decl[3/*multiplicity*/];

WrapperStr IdlSettings::_union_rel_decl[3/*multiplicity*/];

WrapperStr IdlSettings::_oper_decl;

WrapperStr IdlSettings::_get_name;

WrapperStr IdlSettings::_set_name;

bool IdlSettings::_is_set_oneway;

WrapperStr IdlSettings::_src_content;

WrapperStr IdlSettings::_ext;

Q3Dict<WrapperStr> IdlSettings::_map_includes;

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
        WrapperStr t = UmlCom::read_string();
        WrapperStr i = UmlCom::read_string();

        _map_includes.insert(t, new WrapperStr(i));
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

    _enum_item_decl = UmlCom::read_string();

    for (index = 0; index != 3; index += 1) {
        _attr_decl[index] = UmlCom::read_string();
        _valuetype_attr_decl[index] = UmlCom::read_string();
        _union_item_decl[index] = UmlCom::read_string();
        _const_decl[index] = UmlCom::read_string();
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
