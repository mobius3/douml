#ifdef WITHCPP


#include "CppSettings.h"

#include "UmlCom.h"
#include "UmlSettings.h"
//#include "Tools/ApiCmd.h"
#include "UmlBuiltin.h"
#include "UmlStereotype.h"
//Added by qt3to4:
#include <Q3CString>
bool CppSettings::useDefaults()
{
    UmlCom::send_cmd(cppSettingsCmd, getCppUseDefaultsCmd);
    return UmlCom::read_bool();
}

bool CppSettings::set_UseDefaults(bool y)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppUseDefaultsCmd, (char) y);
    return UmlCom::read_bool();
}

Q3CString CppSettings::type(Q3CString s)
{
    read_if_needed_();

    UmlBuiltin * b = UmlSettings::_map_builtins.find(s);

    return (b) ? b->cpp : s;
}

bool CppSettings::set_Type(Q3CString s, Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppTypeCmd, s, v);

    if (UmlCom::read_bool()) {
        UmlBuiltin * b = UmlSettings::_map_builtins.find(s);

        if (b == 0)
            b = UmlSettings::add_type(s);

        b->cpp = v;

        return TRUE;
    }
    else
        return FALSE;
}

Q3CString CppSettings::umlType(Q3CString s)
{
    read_if_needed_();

    return UmlSettings::uml_type(s, &UmlBuiltin::cpp);
}

Q3CString CppSettings::relationStereotype(Q3CString s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_relation_stereotypes.find(s);

    return (b) ? b->cpp : s;
}

bool CppSettings::set_RelationStereotype(Q3CString s, Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppRelationStereotypeCmd, s, v);

    if (UmlCom::read_bool()) {
        UmlStereotype * st = UmlSettings::_map_relation_stereotypes.find(s);

        if (st == 0)
            st = UmlSettings::add_rel_stereotype(s);

        st->cpp = v;

        return TRUE;
    }
    else
        return FALSE;
}

Q3CString CppSettings::relationUmlStereotype(Q3CString s)
{
    read_if_needed_();

    return UmlSettings::uml_rel_stereotype(s, &UmlStereotype::cpp);
}

Q3CString CppSettings::classStereotype(Q3CString s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_class_stereotypes.find(s);

    return (b) ? b->cpp : s;
}

bool CppSettings::set_ClassStereotype(Q3CString s, Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppClassStereotypeCmd, s, v);

    if (UmlCom::read_bool()) {
        UmlStereotype * st = UmlSettings::_map_class_stereotypes.find(s);

        if (st == 0)
            st = UmlSettings::add_class_stereotype(s);

        st->cpp = v;

        return TRUE;
    }
    else
        return FALSE;
}

Q3CString CppSettings::classUmlStereotype(Q3CString s)
{
    read_if_needed_();

    return UmlSettings::uml_class_stereotype(s, &UmlStereotype::cpp);
}

Q3CString CppSettings::include(Q3CString s)
{
    read_if_needed_();

    Q3CString * r = _map_includes[s];

    return (r) ? *r : Q3CString(0);
}

bool CppSettings::set_Include(Q3CString s, Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppIncludeCmd, s, v);

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

Q3CString CppSettings::rootDir()
{
    read_if_needed_();

    return _root;
}

bool CppSettings::set_RootDir(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppRootDirCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _root = v;
        return TRUE;
    }
    else
        return FALSE;
}

Q3CString CppSettings::headerContent()
{
    read_if_needed_();

    return _h_content;
}

bool CppSettings::set_HeaderContent(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppHeaderContentCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _h_content = v;
        return TRUE;
    }
    else
        return FALSE;
}

Q3CString CppSettings::sourceContent()
{
    read_if_needed_();

    return _src_content;
}

bool CppSettings::set_SourceContent(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppSourceContentCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _src_content = v;
        return TRUE;
    }
    else
        return FALSE;
}

Q3CString CppSettings::headerExtension()
{
    read_if_needed_();

    return _h_ext;
}

bool CppSettings::set_HeaderExtension(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppHeaderExtensionCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _h_ext = v;
        return TRUE;
    }
    else
        return FALSE;
}

Q3CString CppSettings::sourceExtension()
{
    read_if_needed_();

    return _src_ext;
}

bool CppSettings::set_SourceExtension(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppSourceExtensionCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _src_ext = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool CppSettings::includeWithPath()
{
    read_if_needed_();

    return _incl_with_path;
}

bool CppSettings::set_IncludeWithPath(bool v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppIncludeWithPathCmd, v);

    if (UmlCom::read_bool()) {
        _incl_with_path = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::enumIn()
{
    read_if_needed_();

    return _enum_in;
}

bool CppSettings::set_EnumIn(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppEnumInCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _enum_in = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::enumOut()
{
    read_if_needed_();

    return _enum_out;
}

bool CppSettings::set_EnumOut(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppEnumOutCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _enum_out = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::enumInout()
{
    read_if_needed_();

    return _enum_inout;
}

bool CppSettings::set_EnumInout(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppEnumInOutCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _enum_inout = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::in()
{
    read_if_needed_();

    return _in;
}

bool CppSettings::set_In(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppInCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _in = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::out()
{
    read_if_needed_();

    return _out;
}

bool CppSettings::set_Out(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppOutCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _out = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::inout()
{
    read_if_needed_();

    return _inout;
}

bool CppSettings::set_Inout(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppInOutCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _inout = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::classDecl()
{
    read_if_needed_();

    return _class_decl;
}

bool CppSettings::set_ClassDecl(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppClassDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _class_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::externalClassDecl()
{
    read_if_needed_();

    return _external_class_decl;
}

bool CppSettings::set_ExternalClassDecl(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppExternalClassDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _external_class_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::structDecl()
{
    read_if_needed_();

    return _struct_decl;
}

bool CppSettings::set_StructDecl(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppStructDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _struct_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::unionDecl()
{
    read_if_needed_();

    return _union_decl;
}

bool CppSettings::set_UnionDecl(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppUnionDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _union_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::enumDecl()
{
    read_if_needed_();

    return _enum_decl;
}

bool CppSettings::set_EnumDecl(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppEnumDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _enum_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::typedefDecl()
{
    read_if_needed_();

    return _typedef_decl;
}

bool CppSettings::set_TypedefDecl(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppTypedefDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _typedef_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::attributeDecl()
{
    read_if_needed_();

    return _attr_decl;
}

bool CppSettings::set_AttributeDecl(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppAttributeDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _attr_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::enumItemDecl()
{
    read_if_needed_();

    return _enum_item_decl;
}

bool CppSettings::set_EnumItemDecl(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppEnumItemDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _enum_item_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::relationDecl(bool by_value, const char * multiplicity)
{
    read_if_needed_();

    return _rel_decl[(by_value) ? 1 : 0][UmlSettings::multiplicity_column(multiplicity)];
}

bool CppSettings::set_RelationDecl(bool by_value, const char * multiplicity, const char * v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppRelationDeclCmd, by_value, multiplicity, v);

    if (UmlCom::read_bool()) {
        _rel_decl[(by_value) ? 1 : 0][UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::operationDecl()
{
    read_if_needed_();

    return _oper_decl;
}

bool CppSettings::set_OperationDecl(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppOperationDeclCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _oper_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::operationDef()
{
    read_if_needed_();

    return _oper_def;
}

bool CppSettings::set_OperationDef(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppOperationDefCmd, (const char *)v); //ambiguous call

    if (UmlCom::read_bool()) {
        _oper_def = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool CppSettings::operationForceThrow()
{
    read_if_needed_();

    return _force_oper_throw;
}

bool CppSettings::set_OperationForceThrow(bool v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppOperationForceThrowCmd, v);

    if (UmlCom::read_bool()) {
        _force_oper_throw = v;
        return TRUE;
    }
    else
        return FALSE;
}

aVisibility CppSettings::getVisibility()
{
    read_if_needed_();

    return _get_visibility;
}

bool CppSettings::set_GetVisibility(aVisibility v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppGetVisibilityCmd, v);

    if (UmlCom::read_bool()) {
        _get_visibility = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::getName()
{
    read_if_needed_();

    return _get_name;
}

bool CppSettings::set_GetName(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppGetNameCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _get_name = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool CppSettings::isGetInline()
{
    read_if_needed_();

    return _is_get_inline;
}

bool CppSettings::set_IsGetInline(bool v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppIsGetInlineCmd, v);

    if (UmlCom::read_bool()) {
        _is_get_inline = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool CppSettings::isGetConst()
{
    read_if_needed_();

    return _is_get_const;
}

bool CppSettings::set_IsGetConst(bool v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppIsGetConstCmd, v);

    if (UmlCom::read_bool()) {
        _is_get_const = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool CppSettings::isGetValueConst()
{
    read_if_needed_();

    return _is_get_value_const;
}

bool CppSettings::set_IsGetValueConst(bool v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppIsGetValueConstCmd, v);

    if (UmlCom::read_bool()) {
        _is_get_value_const = v;
        return TRUE;
    }
    else
        return FALSE;
}

aVisibility CppSettings::setVisibility()
{
    read_if_needed_();

    return _set_visibility;
}

bool CppSettings::set_SetVisibility(aVisibility v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppSetVisibilityCmd, v);

    if (UmlCom::read_bool()) {
        _set_visibility = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & CppSettings::setName()
{
    read_if_needed_();

    return _set_name;
}

bool CppSettings::set_SetName(Q3CString v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppSetNameCmd, (const char *)v); //[jasa] ambiguous call

    if (UmlCom::read_bool()) {
        _set_name = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool CppSettings::isSetInline()
{
    read_if_needed_();

    return _is_set_inline;
}

bool CppSettings::set_IsSetInline(bool v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppIsSetInlineCmd, v);

    if (UmlCom::read_bool()) {
        _is_set_inline = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool CppSettings::isSetParamConst()
{
    read_if_needed_();

    return _is_set_param_const;
}

bool CppSettings::set_IsSetParamConst(bool v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppIsSetParamConstCmd, v);

    if (UmlCom::read_bool()) {
        _is_set_param_const = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool CppSettings::_defined;

Q3CString CppSettings::_root;

Q3CString CppSettings::_in;

Q3CString CppSettings::_out;

Q3CString CppSettings::_inout;

Q3CString CppSettings::_enum_in;

Q3CString CppSettings::_enum_out;

Q3CString CppSettings::_enum_inout;

Q3CString CppSettings::_class_decl;

Q3CString CppSettings::_external_class_decl;

Q3CString CppSettings::_struct_decl;

Q3CString CppSettings::_union_decl;

Q3CString CppSettings::_enum_decl;

Q3CString CppSettings::_typedef_decl;

Q3CString CppSettings::_attr_decl;

Q3CString CppSettings::_enum_item_decl;

Q3CString CppSettings::_rel_decl[2/*relation kind*/][3/*multiplicity*/];

Q3CString CppSettings::_oper_decl;

Q3CString CppSettings::_oper_def;

bool CppSettings::_force_oper_throw;

aVisibility CppSettings::_get_visibility;

Q3CString CppSettings::_get_name;

bool CppSettings::_is_get_inline;

bool CppSettings::_is_get_const;

bool CppSettings::_is_get_value_const;

aVisibility CppSettings::_set_visibility;

Q3CString CppSettings::_set_name;

bool CppSettings::_is_set_inline;

bool CppSettings::_is_set_param_const;

Q3CString CppSettings::_h_content;

Q3CString CppSettings::_src_content;

Q3CString CppSettings::_h_ext;

Q3CString CppSettings::_src_ext;

bool CppSettings::_incl_with_path;

Q3Dict<Q3CString> CppSettings::_map_includes;

void CppSettings::read_()
{
    _root = UmlCom::read_string();

    unsigned n;
    unsigned index;

    n = UmlCom::read_unsigned();

    for (index = 0; index != n; index += 1) {
        UmlSettings::_builtins[index].cpp = UmlCom::read_string();
        UmlSettings::_builtins[index].cpp_in = UmlCom::read_string();
        UmlSettings::_builtins[index].cpp_out = UmlCom::read_string();
        UmlSettings::_builtins[index].cpp_inout = UmlCom::read_string();
    }

    n = UmlCom::read_unsigned();

    for (index = 0; index != n; index += 1)
        UmlSettings::_relation_stereotypes[index].cpp = UmlCom::read_string();

    n = UmlCom::read_unsigned();

    for (index = 0; index != n; index += 1)
        UmlSettings::_class_stereotypes[index].cpp = UmlCom::read_string();

    n = UmlCom::read_unsigned();
    _map_includes.clear();

    if (n > _map_includes.size())
        _map_includes.resize(n);

    for (index = 0; index != n; index += 1) {
        Q3CString t = UmlCom::read_string();
        Q3CString i = UmlCom::read_string();

        _map_includes.insert(t, new Q3CString(i));
    }

    _h_content = UmlCom::read_string();
    _src_content = UmlCom::read_string();
    _h_ext = UmlCom::read_string();
    _src_ext = UmlCom::read_string();
    _incl_with_path = UmlCom::read_bool();

    _in = UmlCom::read_string();
    _out = UmlCom::read_string();
    _inout = UmlCom::read_string();
    _enum_in = UmlCom::read_string();
    _enum_out = UmlCom::read_string();
    _enum_inout = UmlCom::read_string();
    _class_decl = UmlCom::read_string();
    _external_class_decl = UmlCom::read_string();
    _struct_decl = UmlCom::read_string();
    _union_decl = UmlCom::read_string();
    _enum_decl = UmlCom::read_string();
    _typedef_decl = UmlCom::read_string();
    _attr_decl = UmlCom::read_string();
    _enum_item_decl = UmlCom::read_string();

    for (index = 0; index != 3; index += 1) {
        _rel_decl[0][index] = UmlCom::read_string();
        _rel_decl[1][index] = UmlCom::read_string();
    }

    _oper_decl = UmlCom::read_string();
    _oper_def = UmlCom::read_string();
    _force_oper_throw = UmlCom::read_bool();
    _get_visibility = (aVisibility) UmlCom::read_char();
    _get_name = UmlCom::read_string();
    _is_get_inline = UmlCom::read_bool();
    _is_get_const = UmlCom::read_bool();
    _is_get_value_const = UmlCom::read_bool();
    _set_visibility = (aVisibility) UmlCom::read_char();
    _set_name = UmlCom::read_string();
    _is_set_inline = UmlCom::read_bool();
    _is_set_param_const = UmlCom::read_bool();

}

void CppSettings::read_if_needed_()
{
    UmlSettings::read_if_needed_();

    if (!_defined) {
        UmlCom::send_cmd(cppSettingsCmd, getCppSettingsCmd);
        read_();
        _defined = TRUE;
    }
}


#endif
