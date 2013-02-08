#ifdef WITHJAVA


#include "JavaSettings.h"

#include "UmlCom.h"
#include "UmlSettings.h"
#include "Tools/ApiCmd.h"
#include "UmlBuiltin.h"
#include "UmlStereotype.h"
//Added by qt3to4:
#include "misc/mystr.h"
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

WrapperStr JavaSettings::type(const WrapperStr & s)
{
    read_if_needed_();

    UmlBuiltin * b = UmlSettings::_map_builtins.find(s);

    return (b) ? b->java : s;
}

bool JavaSettings::set_Type(WrapperStr s, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(javaSettingsCmd, setJavaTypeCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

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

WrapperStr JavaSettings::umlType(const WrapperStr & s)
{
    read_if_needed_();

    return UmlSettings::uml_type(s, &UmlBuiltin::java);
}

WrapperStr JavaSettings::relationAttributeStereotype(const WrapperStr & s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_relation_attribute_stereotypes.find(s);

    return (b) ? b->java : s;
}

bool JavaSettings::set_RelationAttributeStereotype(WrapperStr s, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(javaSettingsCmd, setJavaRelationAttributeStereotypeCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        UmlStereotype * st = UmlSettings::_map_relation_attribute_stereotypes.find(s);

        if (st == 0)
            st = UmlSettings::add_rel_attr_stereotype(s);

        st->java = v;

        return TRUE;
    }
    else
        return FALSE;
}

WrapperStr JavaSettings::relationAttributeUmlStereotype(const WrapperStr & s)
{
    read_if_needed_();

    return UmlSettings::uml_rel_attr_stereotype(s, &UmlStereotype::java);
}

WrapperStr JavaSettings::classStereotype(const WrapperStr & s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_class_stereotypes.find(s);

    return (b) ? b->java : s;
}

bool JavaSettings::set_ClassStereotype(WrapperStr s, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(javaSettingsCmd, setJavaClassStereotypeCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

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

WrapperStr JavaSettings::classUmlStereotype(const WrapperStr & s)
{
    read_if_needed_();

    return UmlSettings::uml_class_stereotype(s, &UmlStereotype::java);
}

WrapperStr JavaSettings::get_import(const WrapperStr & s)
{
    read_if_needed_();

    WrapperStr * r = _map_imports[s];

    return (r) ? *r : WrapperStr(0);
}

bool JavaSettings::set_Import(WrapperStr s, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(javaSettingsCmd, setJavaImportCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        WrapperStr * r = _map_imports.take(s);

        if (!v.isEmpty())
            _map_imports.insert(s, new WrapperStr(v));

        if (r)
            delete r;

        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & JavaSettings::rootDir()
{
    read_if_needed_();

    return _root;
}

bool JavaSettings::set_RootDir(WrapperStr v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaRootdirCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _root = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & JavaSettings::sourceContent()
{
    read_if_needed_();

    return _src_content;
}

bool JavaSettings::set_SourceContent(WrapperStr v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaSourceContentCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _src_content = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & JavaSettings::sourceExtension()
{
    read_if_needed_();

    return _ext;
}

bool JavaSettings::set_SourceExtension(WrapperStr v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaSourceExtensionCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _ext = v;
        return TRUE;
    }
    else
        return FALSE;
}

WrapperStr JavaSettings::reverseRoundtripDirRegExp()
{
    read_if_needed_();

    return _dir_regexp;
}

bool JavaSettings::isReverseRoundtripDirRegExpCaseSensitive()
{
    read_if_needed_();

    return _dir_regexp_case_sensitive;
}

bool JavaSettings::set_ReverseRoundtripDirRegExp(WrapperStr s, bool cs)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaDirRevFilterCmd, s, cs);

    if (UmlCom::read_bool()) {
        _dir_regexp = s;
        _dir_regexp_case_sensitive = cs;
        return TRUE;
    }
    else
        return FALSE;
}

WrapperStr JavaSettings::reverseRoundtripFileRegExp()
{
    read_if_needed_();

    return _file_regexp;
}

bool JavaSettings::isReverseRoundtripFileRegExpCaseSensitive()
{
    read_if_needed_();

    return _file_regexp_case_sensitive;
}

bool JavaSettings::set_ReverseRoundtripFileRegExp(WrapperStr s, bool cs)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaFileRevFilterCmd, s, cs);

    if (UmlCom::read_bool()) {
        _file_regexp = s;
        _file_regexp_case_sensitive = cs;
        return TRUE;
    }
    else
        return FALSE;
}

bool JavaSettings::isGenerateJavadocStyleComment()
{
    read_if_needed_();

    return _is_generate_javadoc_comment;
}

bool JavaSettings::set_IsGenerateJavadocStyleComment(bool v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaJavadocStyleCmd, v);

    if (UmlCom::read_bool()) {
        _is_generate_javadoc_comment = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool JavaSettings::isForcePackagePrefixGeneration()
{
    read_if_needed_();

    return _is_force_package_gen;
}

bool JavaSettings::set_IsForcePackagePrefixGeneration(bool v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaForcePackageGenCmd, v);

    if (UmlCom::read_bool()) {
        _is_force_package_gen = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & JavaSettings::classDecl()
{
    read_if_needed_();

    return _class_decl;
}

bool JavaSettings::set_ClassDecl(WrapperStr v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaClassDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _class_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & JavaSettings::externalClassDecl()
{
    read_if_needed_();

    return _external_class_decl;
}

bool JavaSettings::set_ExternalClassDecl(WrapperStr v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaExternalClassDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _external_class_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & JavaSettings::enumPatternDecl()
{
    read_if_needed_();

    return _enum_pattern_decl;
}

bool JavaSettings::set_EnumPatternDecl(WrapperStr v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaEnumPatternDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_pattern_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

WrapperStr JavaSettings::enumDecl()
{
    read_if_needed_();

    return _enum_decl;
}

bool JavaSettings::set_EnumDecl(WrapperStr v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaEnumDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & JavaSettings::interfaceDecl()
{
    read_if_needed_();

    return _interface_decl;
}

bool JavaSettings::set_InterfaceDecl(WrapperStr v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaInterfaceDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _interface_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & JavaSettings::attributeDecl(const char * multiplicity)
{
    read_if_needed_();

    return _attr_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool JavaSettings::set_AttributeDecl(const char * multiplicity, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(javaSettingsCmd, setJavaAttributeDeclCmd, multiplicity, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _attr_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & JavaSettings::enumPatternItemDecl()
{
    read_if_needed_();

    return _enum_pattern_item_decl;
}

bool JavaSettings::set_EnumPatternItemDecl(WrapperStr v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaEnumPatternItemDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_pattern_item_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & JavaSettings::enumPatternItemCase()
{
    read_if_needed_();

    return _enum_pattern_item_case;
}

bool JavaSettings::set_EnumPatternItemCase(WrapperStr v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaEnumPatternItemCaseCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_pattern_item_case = v;
        return TRUE;
    }
    else
        return FALSE;
}

WrapperStr JavaSettings::enumItemDecl()
{
    read_if_needed_();

    return _enum_item_decl;
}

bool JavaSettings::set_EnumItemDecl(WrapperStr v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaEnumItemDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_item_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & JavaSettings::relationDecl(const char * multiplicity)
{
    read_if_needed_();

    return _rel_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool JavaSettings::set_RelationDecl(const char * multiplicity, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(javaSettingsCmd, setJavaRelationDeclCmd, multiplicity, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _rel_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & JavaSettings::operationDef()
{
    read_if_needed_();

    return _oper_def;
}

bool JavaSettings::set_OperationDef(WrapperStr v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaOperationDefCmd, (const char *)v); //[rageek] Fix prototype

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

const WrapperStr & JavaSettings::getName()
{
    read_if_needed_();

    return _get_name;
}

bool JavaSettings::set_GetName(WrapperStr v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaGetNameCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _get_name = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & JavaSettings::setName()
{
    read_if_needed_();

    return _set_name;
}

bool JavaSettings::set_SetName(WrapperStr v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaSetNameCmd, (const char *)v); //[rageek] Fix prototype

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

WrapperStr JavaSettings::_root;

WrapperStr JavaSettings::_class_decl;

WrapperStr JavaSettings::_external_class_decl;

WrapperStr JavaSettings::_enum_pattern_decl;

WrapperStr JavaSettings::_enum_decl;

WrapperStr JavaSettings::_interface_decl;

WrapperStr JavaSettings::_attr_decl[3/*multiplicity*/];

WrapperStr JavaSettings::_enum_pattern_item_decl;

WrapperStr JavaSettings::_enum_pattern_item_case;

WrapperStr JavaSettings::_enum_item_decl;

WrapperStr JavaSettings::_rel_decl[3/*multiplicity*/];

WrapperStr JavaSettings::_oper_def;

aVisibility JavaSettings::_get_visibility;

WrapperStr JavaSettings::_get_name;

bool JavaSettings::_is_get_final;

aVisibility JavaSettings::_set_visibility;

WrapperStr JavaSettings::_set_name;

bool JavaSettings::_is_set_final;

bool JavaSettings::_is_set_param_final;

WrapperStr JavaSettings::_src_content;

WrapperStr JavaSettings::_ext;

WrapperStr JavaSettings::_dir_regexp;

bool JavaSettings::_dir_regexp_case_sensitive;

WrapperStr JavaSettings::_file_regexp;

bool JavaSettings::_file_regexp_case_sensitive;

bool JavaSettings::_is_generate_javadoc_comment;

bool JavaSettings::_is_force_package_gen;

Q3Dict<WrapperStr> JavaSettings::_map_imports;

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
        UmlSettings::_relation_attribute_stereotypes[index].java = UmlCom::read_string();

    n = UmlCom::read_unsigned();

    for (index = 0; index != n; index += 1)
        UmlSettings::_class_stereotypes[index].java = UmlCom::read_string();

    n = UmlCom::read_unsigned();
    _map_imports.clear();

    if (n > _map_imports.size())
        _map_imports.resize(n);

    for (index = 0; index != n; index += 1) {
        WrapperStr t = UmlCom::read_string();
        WrapperStr i = UmlCom::read_string();

        _map_imports.insert(t, new WrapperStr(i));
    }

    _src_content = UmlCom::read_string();
    _ext = UmlCom::read_string();

    _class_decl = UmlCom::read_string();
    _external_class_decl = UmlCom::read_string();
    _enum_decl = UmlCom::read_string();
    _enum_pattern_decl = UmlCom::read_string();
    _interface_decl = UmlCom::read_string();

    for (index = 0; index != 3; index += 1)
        _attr_decl[index] = UmlCom::read_string();

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
    _is_generate_javadoc_comment = UmlCom::read_bool();
    _is_force_package_gen = UmlCom::read_bool();

    _dir_regexp = UmlCom::read_string();
    _dir_regexp_case_sensitive = UmlCom::read_bool();

    _file_regexp = UmlCom::read_string();
    _file_regexp_case_sensitive = UmlCom::read_bool();
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
