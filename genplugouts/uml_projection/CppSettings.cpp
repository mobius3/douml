#ifdef WITHCPP


#include "CppSettings.h"

#include "UmlCom.h"
#include "UmlSettings.h"
#include "Tools/ApiCmd.h"
#include "UmlBuiltin.h"
#include "UmlStereotype.h"
//Added by qt3to4:
#include <QByteArray>
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

QByteArray CppSettings::type(QByteArray s)
{
    read_if_needed_();

    UmlBuiltin * b = UmlSettings::_map_builtins.value(s);

    return (b) ? b->cpp : s;
}

bool CppSettings::set_Type(QByteArray s, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(cppSettingsCmd, setCppTypeCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        UmlBuiltin * b = UmlSettings::_map_builtins.value(s);

        if (b == 0)
            b = UmlSettings::add_type(s);

        b->cpp = v;

        return TRUE;
    }
    else
        return FALSE;
}

QByteArray CppSettings::umlType(QByteArray s)
{
    read_if_needed_();

    return UmlSettings::uml_type(s, &UmlBuiltin::cpp);
}

QByteArray CppSettings::relationAttributeStereotype(QByteArray s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_relation_attribute_stereotypes.value(s);

    return (b) ? b->cpp : s;
}

bool CppSettings::set_RelationAttributeStereotype(QByteArray s, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(cppSettingsCmd, setCppRelationAttributeStereotypeCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        UmlStereotype * st = UmlSettings::_map_relation_attribute_stereotypes.value(s);

        if (st == 0)
            st = UmlSettings::add_rel_attr_stereotype(s);

        st->cpp = v;

        return TRUE;
    }
    else
        return FALSE;
}

QByteArray CppSettings::relationAttributeUmlStereotype(QByteArray s)
{
    read_if_needed_();

    return UmlSettings::uml_rel_attr_stereotype(s, &UmlStereotype::cpp);
}

QByteArray CppSettings::classStereotype(QByteArray s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_class_stereotypes.value(s);

    return (b) ? b->cpp : s;
}

bool CppSettings::set_ClassStereotype(QByteArray s, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(cppSettingsCmd, setCppClassStereotypeCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        UmlStereotype * st = UmlSettings::_map_class_stereotypes.value(s);

        if (st == 0)
            st = UmlSettings::add_class_stereotype(s);

        st->cpp = v;

        return TRUE;
    }
    else
        return FALSE;
}

QByteArray CppSettings::classUmlStereotype(QByteArray s)
{
    read_if_needed_();

    return UmlSettings::uml_class_stereotype(s, &UmlStereotype::cpp);
}

QByteArray CppSettings::include(QByteArray s)
{
    read_if_needed_();

    QByteArray * r = _map_includes[s];

    return (r) ? *r : QByteArray(0);
}

bool CppSettings::set_Include(QByteArray s, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(cppSettingsCmd, setCppIncludeCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        QByteArray * r = _map_includes.take(s);

        if (!v.isEmpty())
            _map_includes.insert(s, new QByteArray(v));

        if (r)
            delete r;

        return TRUE;
    }
    else
        return FALSE;
}

QByteArray CppSettings::rootDir()
{
    read_if_needed_();

    return _root;
}

bool CppSettings::set_RootDir(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppRootDirCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _root = v;
        return TRUE;
    }
    else
        return FALSE;
}

QByteArray CppSettings::headerContent()
{
    read_if_needed_();

    return _h_content;
}

bool CppSettings::set_HeaderContent(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppHeaderContentCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _h_content = v;
        return TRUE;
    }
    else
        return FALSE;
}

QByteArray CppSettings::sourceContent()
{
    read_if_needed_();

    return _src_content;
}

bool CppSettings::set_SourceContent(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppSourceContentCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _src_content = v;
        return TRUE;
    }
    else
        return FALSE;
}

QByteArray CppSettings::headerExtension()
{
    read_if_needed_();

    return _h_ext;
}

bool CppSettings::set_HeaderExtension(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppHeaderExtensionCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _h_ext = v;
        return TRUE;
    }
    else
        return FALSE;
}

QByteArray CppSettings::sourceExtension()
{
    read_if_needed_();

    return _src_ext;
}

bool CppSettings::set_SourceExtension(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppSourceExtensionCmd, (const char *)v); //[rageek] Fix prototype

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

bool CppSettings::isRelativePath()
{
    read_if_needed_();

    return _is_relative_path;
}

bool CppSettings::set_IsRelativePath(bool v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppRelativePathCmd, v);

    if (UmlCom::read_bool()) {
        _is_relative_path = v;

        if (v) _is_root_relative_path = FALSE;

        return TRUE;
    }
    else
        return FALSE;
}

bool CppSettings::isRootRelativePath()
{
    read_if_needed_();

    return _is_root_relative_path;
}

bool CppSettings::set_IsRootRelativePath(bool v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppRootRelativePathCmd, v);

    if (UmlCom::read_bool()) {
        _is_root_relative_path = v;

        if (v) _is_relative_path = FALSE;

        return TRUE;
    }
    else
        return FALSE;
}

bool CppSettings::isForceNamespacePrefixGeneration()
{
    read_if_needed_();

    return _is_force_namespace_gen;
}

bool CppSettings::set_IsForceNamespacePrefixGeneration(bool v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppForceNamespaceGenCmd, v);

    if (UmlCom::read_bool()) {
        _is_force_namespace_gen = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool CppSettings::isGenerateJavadocStyleComment()
{
    read_if_needed_();

    return _is_generate_javadoc_comment;
}

bool CppSettings::set_IsGenerateJavadocStyleComment(bool v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppJavadocStyleCmd, v);

    if (UmlCom::read_bool()) {
        _is_generate_javadoc_comment = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & CppSettings::enumIn()
{
    read_if_needed_();

    return _enum_in;
}

bool CppSettings::set_EnumIn(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppEnumInCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_in = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & CppSettings::enumOut()
{
    read_if_needed_();

    return _enum_out;
}

bool CppSettings::set_EnumOut(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppEnumOutCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_out = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & CppSettings::enumInout()
{
    read_if_needed_();

    return _enum_inout;
}

bool CppSettings::set_EnumInout(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppEnumInOutCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_inout = v;
        return TRUE;
    }
    else
        return FALSE;
}

QByteArray CppSettings::enumReturn()
{
    read_if_needed_();

    return _enum_return;
}

bool CppSettings::set_EnumReturn(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppEnumReturnCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_return = v;
        return TRUE;
    }
    else
        return FALSE;
}

QByteArray CppSettings::builtinIn(QByteArray s)
{
    read_if_needed_();

    UmlBuiltin * b = UmlSettings::_map_builtins.value(s);

    return (b) ? b->cpp_in : QByteArray("");
}

bool CppSettings::set_BuiltinIn(QByteArray type, QByteArray form)
{
    read_if_needed_();
    UmlCom::send_cmd(cppSettingsCmd, setCppInCmd, (const char *)type, (const char *)form); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        UmlBuiltin * b = UmlSettings::_map_builtins.value(type);

        if (b == 0)
            b = UmlSettings::add_type(type);

        b->cpp_in = form;

        return TRUE;
    }
    else
        return FALSE;
}

QByteArray CppSettings::builtinOut(QByteArray s)
{
    read_if_needed_();

    UmlBuiltin * b = UmlSettings::_map_builtins.value(s);

    return (b) ? b->cpp_out : QByteArray("");
}

bool CppSettings::set_BuiltinOut(QByteArray type, QByteArray form)
{
    read_if_needed_();
    UmlCom::send_cmd(cppSettingsCmd, setCppOutCmd, (const char *)type, (const char *)form); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        UmlBuiltin * b = UmlSettings::_map_builtins.value(type);

        if (b == 0)
            b = UmlSettings::add_type(type);

        b->cpp_out = form;

        return TRUE;
    }
    else
        return FALSE;
}

QByteArray CppSettings::builtinInOut(QByteArray s)
{
    read_if_needed_();

    UmlBuiltin * b = UmlSettings::_map_builtins.value(s);

    return (b) ? b->cpp_inout : QByteArray();
}

bool CppSettings::set_BuiltinInOut(QByteArray type, QByteArray form)
{
    read_if_needed_();
    UmlCom::send_cmd(cppSettingsCmd, setCppInOutCmd, (const char *)type, (const char *)form); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        UmlBuiltin * b = UmlSettings::_map_builtins.value(type);

        if (b == 0)
            b = UmlSettings::add_type(type);

        b->cpp_inout = form;

        return TRUE;
    }
    else
        return FALSE;
}

QByteArray CppSettings::builtinReturn(QByteArray s)
{
    read_if_needed_();

    UmlBuiltin * b = UmlSettings::_map_builtins.value(s);

    return (b) ? b->cpp_return : QByteArray("");
}

bool CppSettings::set_BuiltinReturn(QByteArray type, QByteArray form)
{
    read_if_needed_();
    UmlCom::send_cmd(cppSettingsCmd, setCppReturnCmd, (const char *)type, (const char *)form); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        UmlBuiltin * b = UmlSettings::_map_builtins.value(type);

        if (b == 0)
            b = UmlSettings::add_type(type);

        b->cpp_return = form;

        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & CppSettings::in()
{
    read_if_needed_();

    return _in;
}

bool CppSettings::set_In(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppInCmd, (const char *)v, ""); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _in = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & CppSettings::out()
{
    read_if_needed_();

    return _out;
}

bool CppSettings::set_Out(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppOutCmd, (const char *)v, ""); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _out = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & CppSettings::inout()
{
    read_if_needed_();

    return _inout;
}

bool CppSettings::set_Inout(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppInOutCmd, (const char *)v, ""); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _inout = v;
        return TRUE;
    }
    else
        return FALSE;
}

QByteArray CppSettings::Return()
{
    read_if_needed_();

    return _return;
}

bool CppSettings::set_Return(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppReturnCmd, (const char *)v, ""); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _return = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & CppSettings::classDecl()
{
    read_if_needed_();

    return _class_decl;
}

bool CppSettings::set_ClassDecl(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppClassDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _class_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & CppSettings::externalClassDecl()
{
    read_if_needed_();

    return _external_class_decl;
}

bool CppSettings::set_ExternalClassDecl(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppExternalClassDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _external_class_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & CppSettings::structDecl()
{
    read_if_needed_();

    return _struct_decl;
}

bool CppSettings::set_StructDecl(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppStructDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _struct_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & CppSettings::unionDecl()
{
    read_if_needed_();

    return _union_decl;
}

bool CppSettings::set_UnionDecl(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppUnionDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _union_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & CppSettings::enumDecl()
{
    read_if_needed_();

    return _enum_decl;
}

bool CppSettings::set_EnumDecl(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppEnumDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & CppSettings::typedefDecl()
{
    read_if_needed_();

    return _typedef_decl;
}

bool CppSettings::set_TypedefDecl(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppTypedefDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _typedef_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & CppSettings::attributeDecl(const char * multiplicity)
{
    read_if_needed_();

    return _attr_decl[UmlSettings::multiplicity_column(multiplicity)];
}

bool CppSettings::set_AttributeDecl(const char * multiplicity, QByteArray v)
{
    read_if_needed_();
    UmlCom::send_cmd(cppSettingsCmd, setCppAttributeDeclCmd, multiplicity, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _attr_decl[UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & CppSettings::enumItemDecl()
{
    read_if_needed_();

    return _enum_item_decl;
}

bool CppSettings::set_EnumItemDecl(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppEnumItemDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_item_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & CppSettings::relationDecl(bool by_value, const char * multiplicity)
{
    read_if_needed_();

    return _rel_decl[(by_value) ? 1 : 0][UmlSettings::multiplicity_column(multiplicity)];
}

bool CppSettings::set_RelationDecl(bool by_value, const char * multiplicity, const char * v)
{
    read_if_needed_();
    UmlCom::send_cmd(cppSettingsCmd, setCppRelationDeclCmd, by_value, multiplicity, v);

    if (UmlCom::read_bool()) {
        _rel_decl[(by_value) ? 1 : 0][UmlSettings::multiplicity_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & CppSettings::operationDecl()
{
    read_if_needed_();

    return _oper_decl;
}

bool CppSettings::set_OperationDecl(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppOperationDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _oper_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const QByteArray & CppSettings::operationDef()
{
    read_if_needed_();

    return _oper_def;
}

bool CppSettings::set_OperationDef(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppOperationDefCmd, (const char *)v); //[rageek] Fix prototype

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

const QByteArray & CppSettings::getName()
{
    read_if_needed_();

    return _get_name;
}

bool CppSettings::set_GetName(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppGetNameCmd, (const char *)v); //[rageek] Fix prototype

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

const QByteArray & CppSettings::setName()
{
    read_if_needed_();

    return _set_name;
}

bool CppSettings::set_SetName(QByteArray v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppSetNameCmd, (const char *)v); //[rageek] Fix prototype

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

bool CppSettings::isSetParamRef()
{
    read_if_needed_();

    return _is_set_param_ref;
}

bool CppSettings::set_IsSetParamRef(bool v)
{
    UmlCom::send_cmd(cppSettingsCmd, setCppIsSetParamRefCmd, v);

    if (UmlCom::read_bool()) {
        _is_set_param_ref = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool CppSettings::_defined;

QByteArray CppSettings::_root;

QByteArray CppSettings::_in;

QByteArray CppSettings::_out;

QByteArray CppSettings::_inout;

QByteArray CppSettings::_return;

QByteArray CppSettings::_enum_in;

QByteArray CppSettings::_enum_out;

QByteArray CppSettings::_enum_inout;

QByteArray CppSettings::_enum_return;

QByteArray CppSettings::_class_decl;

QByteArray CppSettings::_external_class_decl;

QByteArray CppSettings::_struct_decl;

QByteArray CppSettings::_union_decl;

QByteArray CppSettings::_enum_decl;

QByteArray CppSettings::_typedef_decl;

QByteArray CppSettings::_attr_decl[3/*multiplicity*/];

QByteArray CppSettings::_enum_item_decl;

QByteArray CppSettings::_rel_decl[2/*relation kind*/][3/*multiplicity*/];

QByteArray CppSettings::_oper_decl;

QByteArray CppSettings::_oper_def;

bool CppSettings::_force_oper_throw;

aVisibility CppSettings::_get_visibility;

QByteArray CppSettings::_get_name;

bool CppSettings::_is_get_inline;

bool CppSettings::_is_get_const;

bool CppSettings::_is_get_value_const;

aVisibility CppSettings::_set_visibility;

QByteArray CppSettings::_set_name;

bool CppSettings::_is_set_inline;

bool CppSettings::_is_set_param_const;

bool CppSettings::_is_set_param_ref;

QByteArray CppSettings::_h_content;

QByteArray CppSettings::_src_content;

QByteArray CppSettings::_h_ext;

QByteArray CppSettings::_src_ext;

bool CppSettings::_incl_with_path;

bool CppSettings::_is_relative_path;

bool CppSettings::_is_root_relative_path;

bool CppSettings::_is_force_namespace_gen;

bool CppSettings::_is_generate_javadoc_comment;

QHash<QByteArray,QByteArray*>  CppSettings::_map_includes;

void CppSettings::read_()
{
    _root = UmlCom::read_string();

    int n;
    int index;

    n = UmlCom::read_unsigned();

    for (index = 0; index != n; index += 1) {
        UmlSettings::_builtins[index].cpp = UmlCom::read_string();
        UmlSettings::_builtins[index].cpp_in = UmlCom::read_string();
        UmlSettings::_builtins[index].cpp_out = UmlCom::read_string();
        UmlSettings::_builtins[index].cpp_inout = UmlCom::read_string();
        UmlSettings::_builtins[index].cpp_return = UmlCom::read_string();
    }

    n = UmlCom::read_unsigned();

    for (index = 0; index != n; index += 1)
        UmlSettings::_relation_attribute_stereotypes[index].cpp = UmlCom::read_string();

    n = UmlCom::read_unsigned();

    for (index = 0; index != n; index += 1)
        UmlSettings::_class_stereotypes[index].cpp = UmlCom::read_string();

    n = UmlCom::read_unsigned();
    _map_includes.clear();

    if (n > _map_includes.size())
        _map_includes.reserve(n);

    for (index = 0; index != n; index += 1) {
        QByteArray t = UmlCom::read_string();
        QByteArray i = UmlCom::read_string();

        _map_includes.insert(t, new QByteArray(i));
    }

    _h_content = UmlCom::read_string();
    _src_content = UmlCom::read_string();
    _h_ext = UmlCom::read_string();
    _src_ext = UmlCom::read_string();
    _incl_with_path = UmlCom::read_bool();

    _in = UmlCom::read_string();
    _out = UmlCom::read_string();
    _inout = UmlCom::read_string();
    _return = UmlCom::read_string();
    _enum_in = UmlCom::read_string();
    _enum_out = UmlCom::read_string();
    _enum_inout = UmlCom::read_string();
    _enum_return = UmlCom::read_string();
    _class_decl = UmlCom::read_string();
    _external_class_decl = UmlCom::read_string();
    _struct_decl = UmlCom::read_string();
    _union_decl = UmlCom::read_string();
    _enum_decl = UmlCom::read_string();
    _typedef_decl = UmlCom::read_string();

    for (index = 0; index != 3; index += 1)
        _attr_decl[index] = UmlCom::read_string();

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

    _is_set_param_ref = UmlCom::read_bool();
    _is_relative_path = UmlCom::read_bool();
    _is_force_namespace_gen = UmlCom::read_bool();
    _is_root_relative_path = UmlCom::read_bool();
    _is_generate_javadoc_comment = UmlCom::read_bool();
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

QByteArray CppSettings::builtinInout(QByteArray s)
{
    read_if_needed_();

    UmlBuiltin * b = UmlSettings::_map_builtins.value(s);

    return (b) ? b->cpp_inout : QByteArray("");
}


#endif
