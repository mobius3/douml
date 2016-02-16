#ifdef WITHJAVA


#include "JavaSettings.h"

#include "UmlCom.h"
#include "UmlSettings.h"
#include "Tools/ApiCmd.h"
#include "UmlBuiltin.h"
#include "UmlStereotype.h"
//Added by qt3to4:
#include <QByteArray>
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

QByteArray JavaSettings::type(const QByteArray & s)
{
    read_if_needed_();

    UmlBuiltin * b = UmlSettings::_map_builtins.value(s);

    return (b) ? b->java : s;
}

bool JavaSettings::set_Type(QByteArray s, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(javaSettingsCmd, setJavaTypeCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        UmlBuiltin * b = UmlSettings::_map_builtins.value(s);

        if (b == 0)
            b = UmlSettings::add_type(s);

        b->java = v;

        return TRUE;
    }
    else
        return FALSE;
}

QByteArray JavaSettings::umlType(const QByteArray & s)
{
    read_if_needed_();

    return UmlSettings::uml_type(s, &UmlBuiltin::java);
}

QByteArray JavaSettings::relationAttributeStereotype(const QByteArray & s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_relation_attribute_stereotypes.value(s);

    return (b) ? b->java : s;
}

bool JavaSettings::set_RelationAttributeStereotype(QByteArray s, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(javaSettingsCmd, setJavaRelationAttributeStereotypeCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        UmlStereotype * st = UmlSettings::_map_relation_attribute_stereotypes.value(s);

        if (st == 0)
            st = UmlSettings::add_rel_attr_stereotype(s);

        st->java = v;

        return TRUE;
    }
    else
        return FALSE;
}

QByteArray JavaSettings::relationAttributeUmlStereotype(const QByteArray & s)
{
    read_if_needed_();

    return UmlSettings::uml_rel_attr_stereotype(s, &UmlStereotype::java);
}

QByteArray JavaSettings::classStereotype(const QByteArray & s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_class_stereotypes.value(s);

    return (b) ? b->java : s;
}

bool JavaSettings::set_ClassStereotype(QByteArray s, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(javaSettingsCmd, setJavaClassStereotypeCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        UmlStereotype * st = UmlSettings::_map_class_stereotypes.value(s);

        if (st == 0)
            st = UmlSettings::add_class_stereotype(s);

        st->java = v;

        return TRUE;
    }
    else
        return FALSE;
}

QByteArray JavaSettings::classUmlStereotype(const QByteArray & s)
{
    read_if_needed_();

    return UmlSettings::uml_class_stereotype(s, &UmlStereotype::java);
}

QByteArray JavaSettings::get_import(const QByteArray & s)
{
    read_if_needed_();

    QByteArray * r = _map_imports[s];

    return (r) ? *r : QByteArray(0);
}

bool JavaSettings::set_Import(QByteArray s, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(javaSettingsCmd, setJavaImportCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        QByteArray * r = _map_imports.take(s);

        if (!v.isEmpty())
            _map_imports.insert(s, new QByteArray(v));

        if (r)
            delete r;

        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & JavaSettings::rootDir()
{
    read_if_needed_();

    return _root;
}

bool JavaSettings::set_RootDir(QByteArray v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaRootdirCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _root = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & JavaSettings::sourceContent()
{
    read_if_needed_();

    return _src_content;
}

bool JavaSettings::set_SourceContent(QByteArray v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaSourceContentCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _src_content = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & JavaSettings::sourceExtension()
{
    read_if_needed_();

    return _ext;
}

bool JavaSettings::set_SourceExtension(QByteArray v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaSourceExtensionCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _ext = v;
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

const QByteArray & JavaSettings::classDecl()
{
    read_if_needed_();

    return _class_decl;
}

bool JavaSettings::set_ClassDecl(QByteArray v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaClassDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _class_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & JavaSettings::externalClassDecl()
{
    read_if_needed_();

    return _external_class_decl;
}

bool JavaSettings::set_ExternalClassDecl(QByteArray v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaExternalClassDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _external_class_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & JavaSettings::enumPatternDecl()
{
    read_if_needed_();

    return _enum_pattern_decl;
}

bool JavaSettings::set_EnumPatternDecl(QByteArray v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaEnumPatternDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_pattern_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

QByteArray JavaSettings::enumDecl()
{
    read_if_needed_();

    return _enum_decl;
}

bool JavaSettings::set_EnumDecl(QByteArray v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaEnumDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & JavaSettings::interfaceDecl()
{
    read_if_needed_();

    return _interface_decl;
}

bool JavaSettings::set_InterfaceDecl(QByteArray v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaInterfaceDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _interface_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & JavaSettings::attributeDecl(const char * multiplicity)
{
    read_if_needed_();

    return _attr_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool JavaSettings::set_AttributeDecl(const char * multiplicity, QByteArray v)
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

const QByteArray & JavaSettings::enumPatternItemDecl()
{
    read_if_needed_();

    return _enum_pattern_item_decl;
}

bool JavaSettings::set_EnumPatternItemDecl(QByteArray v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaEnumPatternItemDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_pattern_item_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & JavaSettings::enumPatternItemCase()
{
    read_if_needed_();

    return _enum_pattern_item_case;
}

bool JavaSettings::set_EnumPatternItemCase(QByteArray v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaEnumPatternItemCaseCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_pattern_item_case = v;
        return TRUE;
    }
    else
        return FALSE;
}

QByteArray JavaSettings::enumItemDecl()
{
    read_if_needed_();

    return _enum_item_decl;
}

bool JavaSettings::set_EnumItemDecl(QByteArray v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaEnumItemDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_item_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & JavaSettings::relationDecl(const char * multiplicity)
{
    read_if_needed_();

    return _rel_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool JavaSettings::set_RelationDecl(const char * multiplicity, QByteArray v)
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

const QByteArray & JavaSettings::operationDef()
{
    read_if_needed_();

    return _oper_def;
}

bool JavaSettings::set_OperationDef(QByteArray v)
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

const QByteArray & JavaSettings::getName()
{
    read_if_needed_();

    return _get_name;
}

bool JavaSettings::set_GetName(QByteArray v)
{
    UmlCom::send_cmd(javaSettingsCmd, setJavaGetNameCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _get_name = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & JavaSettings::setName()
{
    read_if_needed_();

    return _set_name;
}

bool JavaSettings::set_SetName(QByteArray v)
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

QByteArray JavaSettings::_root;

QByteArray JavaSettings::_class_decl;

QByteArray JavaSettings::_external_class_decl;

QByteArray JavaSettings::_enum_pattern_decl;

QByteArray JavaSettings::_enum_decl;

QByteArray JavaSettings::_interface_decl;

QByteArray JavaSettings::_attr_decl[3/*multiplicity*/];

QByteArray JavaSettings::_enum_pattern_item_decl;

QByteArray JavaSettings::_enum_pattern_item_case;

QByteArray JavaSettings::_enum_item_decl;

QByteArray JavaSettings::_rel_decl[3/*multiplicity*/];

QByteArray JavaSettings::_oper_def;

aVisibility JavaSettings::_get_visibility;

QByteArray JavaSettings::_get_name;

bool JavaSettings::_is_get_final;

aVisibility JavaSettings::_set_visibility;

QByteArray JavaSettings::_set_name;

bool JavaSettings::_is_set_final;

bool JavaSettings::_is_set_param_final;

QByteArray JavaSettings::_src_content;

QByteArray JavaSettings::_ext;

bool JavaSettings::_is_generate_javadoc_comment;

bool JavaSettings::_is_force_package_gen;

QHash<QByteArray, QByteArray*> JavaSettings::_map_imports;

void JavaSettings::read_()
{
    _root = UmlCom::read_string();

    int n;
    int index;

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
        _map_imports.reserve(n);

    for (index = 0; index != n; index += 1) {
        QByteArray t = UmlCom::read_string();
        QByteArray i = UmlCom::read_string();

        _map_imports.insert(t, new QByteArray(i));
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
