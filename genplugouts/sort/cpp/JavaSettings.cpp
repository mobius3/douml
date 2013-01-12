#ifdef WITHJAVA


#include "JavaSettings.h"

#include "UmlCom.h"
#include "UmlSettings.h"
#include "Tools/ApiCmd.h"
#include "UmlBuiltin.h"
#include "UmlStereotype.h"
//Added by qt3to4:
#include <Q3CString>
bool JavaSettings::useDefaults()
{
    UmlCom::send_cmd(javaSettingsCmd, getJavaUseDefaultsCmd);
    return UmlCom::read_bool();
}

bool JavaSettings::set_UseDefaults(bool y)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaUseDefaultsCmd, (char) y);
    return UmlCom::read_bool();
}

Q3CString JavaSettings::type(const Q3CString & s)
{
    read_if_needed_();

    UmlBuiltin * b = UmlSettings::_map_builtins.find(s);

    return (b) ? b->java : s;
}

bool JavaSettings::set_Type(Q3CString s, Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaTypeCmd, s, v);

    if (UmlCom::read_bool()) {
        UmlBuiltin * b = UmlSettings::_map_builtins.find(s);

        if (b == 0)
            b = UmlSettings::add_type(s);

        b->java = v;

        return TRUE;
    }
    else
        return FALSE;
}

Q3CString JavaSettings::umlType(const Q3CString & s)
{
    read_if_needed_();

    return UmlSettings::uml_type(s, &UmlBuiltin::java);
}

Q3CString JavaSettings::relationStereotype(const Q3CString & s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_relation_stereotypes.find(s);

    return (b) ? b->java : s;
}

bool JavaSettings::set_RelationStereotype(Q3CString s, Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaRelationStereotypeCmd, s, v);

    if (UmlCom::read_bool()) {
        UmlStereotype * st = UmlSettings::_map_relation_stereotypes.find(s);

        if (st == 0)
            st = UmlSettings::add_rel_stereotype(s);

        st->java = v;

        return TRUE;
    }
    else
        return FALSE;
}

Q3CString JavaSettings::relationUmlStereotype(const Q3CString & s)
{
    read_if_needed_();

    return UmlSettings::uml_rel_stereotype(s, &UmlStereotype::java);
}

Q3CString JavaSettings::classStereotype(const Q3CString & s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_class_stereotypes.find(s);

    return (b) ? b->java : s;
}

bool JavaSettings::set_ClassStereotype(Q3CString s, Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaClassStereotypeCmd, s, v);

    if (UmlCom::read_bool()) {
        UmlStereotype * st = UmlSettings::_map_class_stereotypes.find(s);

        if (st == 0)
            st = UmlSettings::add_class_stereotype(s);

        st->java = v;

        return TRUE;
    }
    else
        return FALSE;
}

Q3CString JavaSettings::classUmlStereotype(const Q3CString & s)
{
    read_if_needed_();

    return UmlSettings::uml_class_stereotype(s, &UmlStereotype::java);
}

Q3CString JavaSettings::get_import(const Q3CString & s)
{
    read_if_needed_();

    Q3CString * r = _map_imports[s];

    return (r) ? *r : Q3CString(0);
}

bool JavaSettings::set_Import(Q3CString s, Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaImportCmd, s, v);

    if (UmlCom::read_bool()) {
        Q3CString * r = _map_imports.take(s);

        if (!v.isEmpty())
            _map_imports.insert(s, new Q3CString(v));

        if (r)
            delete r;

        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & JavaSettings::rootDir()
{
    read_if_needed_();

    return _root;
}

bool JavaSettings::set_RootDir(Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaRootdirCmd, v);

    if (UmlCom::read_bool()) {
        _root = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & JavaSettings::sourceContent()
{
    read_if_needed_();

    return _src_content;
}

bool JavaSettings::set_SourceContent(Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaSourceContentCmd, v);

    if (UmlCom::read_bool()) {
        _src_content = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & JavaSettings::sourceExtension()
{
    read_if_needed_();

    return _ext;
}

bool JavaSettings::set_SourceExtension(Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaSourceExtensionCmd, v);

    if (UmlCom::read_bool()) {
        _ext = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & JavaSettings::classDecl()
{
    read_if_needed_();

    return _class_decl;
}

bool JavaSettings::set_ClassDecl(Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaClassDeclCmd, v);

    if (UmlCom::read_bool()) {
        _class_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & JavaSettings::externalClassDecl()
{
    read_if_needed_();

    return _external_class_decl;
}

bool JavaSettings::set_ExternalClassDecl(Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaExternalClassDeclCmd, v);

    if (UmlCom::read_bool()) {
        _external_class_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & JavaSettings::enumPatternDecl()
{
    read_if_needed_();

    return _enum_pattern_decl;
}

bool JavaSettings::set_EnumPatternDecl(Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaEnumPatternDeclCmd, v);

    if (UmlCom::read_bool()) {
        _enum_pattern_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

Q3CString JavaSettings::enumDecl()
{
    read_if_needed_();

    return _enum_decl;
}

bool JavaSettings::set_EnumDecl(Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaEnumDeclCmd, v);

    if (UmlCom::read_bool()) {
        _enum_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & JavaSettings::interfaceDecl()
{
    read_if_needed_();

    return _interface_decl;
}

bool JavaSettings::set_InterfaceDecl(Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaInterfaceDeclCmd, v);

    if (UmlCom::read_bool()) {
        _interface_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & JavaSettings::attributeDecl()
{
    read_if_needed_();

    return _attr_decl;
}

bool JavaSettings::set_AttributeDecl(Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaAttributeDeclCmd, v);

    if (UmlCom::read_bool()) {
        _attr_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & JavaSettings::enumPatternItemDecl()
{
    read_if_needed_();

    return _enum_pattern_item_decl;
}

bool JavaSettings::set_EnumPatternItemDecl(Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaEnumPatternItemDeclCmd, v);

    if (UmlCom::read_bool()) {
        _enum_pattern_item_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & JavaSettings::enumPatternItemCase()
{
    read_if_needed_();

    return _enum_pattern_item_case;
}

bool JavaSettings::set_EnumPatternItemCase(Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaEnumPatternItemCaseCmd, v);

    if (UmlCom::read_bool()) {
        _enum_pattern_item_case = v;
        return TRUE;
    }
    else
        return FALSE;
}

Q3CString JavaSettings::enumItemDecl()
{
    read_if_needed_();

    return _enum_item_decl;
}

bool JavaSettings::set_EnumItemDecl(Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaEnumItemDeclCmd, v);

    if (UmlCom::read_bool()) {
        _enum_item_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & JavaSettings::relationDecl(const char * multiplicity)
{
    read_if_needed_();

    return _rel_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool JavaSettings::set_RelationDecl(const char * multiplicity, Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaRelationDeclCmd, multiplicity, v);

    if (UmlCom::read_bool()) {
        _rel_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & JavaSettings::operationDef()
{
    read_if_needed_();

    return _oper_def;
}

bool JavaSettings::set_OperationDef(Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaOperationDefCmd, v);

    if (UmlCom::read_bool()) {
        _oper_def = v;
        return TRUE;
    }
    else
        return FALSE;
}

aVisibility JavaSettings::getVisibility()
{
    read_if_needed_();

    return _get_visibility;
}

bool JavaSettings::set_GetVisibility(aVisibility v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaGetvisibilityCmd, v);

    if (UmlCom::read_bool()) {
        _get_visibility = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & JavaSettings::getName()
{
    read_if_needed_();

    return _get_name;
}

bool JavaSettings::set_GetName(Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaGetNameCmd, v);

    if (UmlCom::read_bool()) {
        _get_name = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & JavaSettings::setName()
{
    read_if_needed_();

    return _set_name;
}

bool JavaSettings::set_SetName(Q3CString v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaSetNameCmd, v);

    if (UmlCom::read_bool()) {
        _set_name = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool JavaSettings::isGetFinal()
{
    read_if_needed_();

    return _is_get_final;
}

bool JavaSettings::set_IsGetFinal(bool v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaIsGetFinalCmd, v);

    if (UmlCom::read_bool()) {
        _is_get_final = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool JavaSettings::isSetFinal()
{
    read_if_needed_();

    return _is_set_final;
}

bool JavaSettings::set_IsSetFinal(bool v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaIsSetFinalCmd, v);

    if (UmlCom::read_bool()) {
        _is_set_final = v;
        return TRUE;
    }
    else
        return FALSE;
}

aVisibility JavaSettings::setVisibility()
{
    read_if_needed_();

    return _set_visibility;
}

bool JavaSettings::set_SetVisibility(aVisibility v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaSetVisibilityCmd, v);

    if (UmlCom::read_bool()) {
        _set_visibility = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool JavaSettings::isSetParamFinal()
{
    read_if_needed_();

    return _is_set_param_final;
}

bool JavaSettings::set_IsSetParamFinal(bool v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaIsSetParamFinalCmd, v);

    if (UmlCom::read_bool()) {
        _is_set_param_final = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool JavaSettings::_defined;

Q3CString JavaSettings::_root;

Q3CString JavaSettings::_class_decl;

Q3CString JavaSettings::_external_class_decl;

Q3CString JavaSettings::_enum_pattern_decl;

Q3CString JavaSettings::_enum_decl;

Q3CString JavaSettings::_interface_decl;

Q3CString JavaSettings::_attr_decl;

Q3CString JavaSettings::_enum_pattern_item_decl;

Q3CString JavaSettings::_enum_pattern_item_case;

Q3CString JavaSettings::_enum_item_decl;

Q3CString JavaSettings::_rel_decl[3/*multiplicity*/];

Q3CString JavaSettings::_oper_def;

aVisibility JavaSettings::_get_visibility;

Q3CString JavaSettings::_get_name;

bool JavaSettings::_is_get_final;

aVisibility JavaSettings::_set_visibility;

Q3CString JavaSettings::_set_name;

bool JavaSettings::_is_set_final;

bool JavaSettings::_is_set_param_final;

Q3CString JavaSettings::_src_content;

Q3CString JavaSettings::_ext;

Q3Dict<Q3CString> JavaSettings::_map_imports;

void JavaSettings::read_()
{
    _root = UmlCom::read_string();

    unsigned n;
    unsigned index;

    n = UmlCom::read_unsigned();

    for (index = 0; index != n; index += 1) {
        UmlSettings::_builtins[index].java = UmlCom::read_string();
    }

    n = UmlCom::read_unsigned();

    for (index = 0; index != n; index += 1)
        UmlSettings::_relation_stereotypes[index].java = UmlCom::read_string();

    n = UmlCom::read_unsigned();

    for (index = 0; index != n; index += 1)
        UmlSettings::_class_stereotypes[index].java = UmlCom::read_string();

    n = UmlCom::read_unsigned();
    _map_imports.clear();

    if (n > _map_imports.size())
        _map_imports.resize(n);

    for (index = 0; index != n; index += 1) {
        Q3CString t = UmlCom::read_string();
        Q3CString i = UmlCom::read_string();

        _map_imports.insert(t, new Q3CString(i));
    }

    _src_content = UmlCom::read_string();
    _ext = UmlCom::read_string();

    _class_decl = UmlCom::read_string();
    _external_class_decl = UmlCom::read_string();
    _enum_decl = UmlCom::read_string();
    _enum_pattern_decl = UmlCom::read_string();
    _interface_decl = UmlCom::read_string();
    _attr_decl = UmlCom::read_string();
    _enum_item_decl = UmlCom::read_string();
    _enum_pattern_item_decl = UmlCom::read_string();
    _enum_pattern_item_case = UmlCom::read_string();

    for (index = 0; index != 3; index += 1)
        _rel_decl[index] = UmlCom::read_string();

    _oper_def = UmlCom::read_string();
    _get_visibility = (aVisibility) UmlCom::read_char();
    _get_name = UmlCom::read_string();
    _is_get_final = UmlCom::read_bool();
    _set_visibility = (aVisibility) UmlCom::read_char();
    _set_name = UmlCom::read_string();
    _is_set_final = UmlCom::read_bool();
    _is_set_param_final = UmlCom::read_bool();
}

void JavaSettings::read_if_needed_()
{
    UmlSettings::read_if_needed_();

    if (!_defined) {
        UmlCom::send_cmd(javaSettingsCmd, getJavaSettingsCmd);
        read_();
        _defined = TRUE;
    }
}


#endif
