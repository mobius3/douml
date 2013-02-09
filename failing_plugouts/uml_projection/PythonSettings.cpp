#ifdef WITHPYTHON


#include "PythonSettings.h"

#include "UmlCom.h"
#include "Tools/ApiCmd.h"
#include "UmlStereotype.h"
//Added by qt3to4:
#include <Q3CString>
bool PythonSettings::isPython_2_2()
{
    read_if_needed_();
    return _2_2;
}

bool PythonSettings::set_IsPython_2_2(bool y)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPython22Cmd, (char) y);

    if (UmlCom::read_bool()) {
        _2_2 = y;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & PythonSettings::indentStep()
{
    read_if_needed_();
    return _indent_step;
}

bool PythonSettings::set_IndentStep(char * v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonIndentStepCmd, v);

    if (UmlCom::read_bool()) {
        _indent_step = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool PythonSettings::useDefaults()
{
    UmlCom::send_cmd(pythonSettingsCmd, getPythonUseDefaultsCmd);
    return UmlCom::read_bool();
}

bool PythonSettings::set_UseDefaults(bool y)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonUseDefaultsCmd, (char) y);
    return UmlCom::read_bool();
}

Q3CString PythonSettings::relationAttributeStereotype(const Q3CString & s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_relation_attribute_stereotypes.find(s);

    return (b) ? b->python : s;
}

bool PythonSettings::set_RelationAttributeStereotype(Q3CString s, Q3CString v)
{
    read_if_needed_();
    UmlCom::send_cmd(pythonSettingsCmd, setPythonRelationAttributeStereotypeCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        UmlStereotype * st = UmlSettings::_map_relation_attribute_stereotypes.find(s);

        if (st == 0)
            st = UmlSettings::add_rel_attr_stereotype(s);

        st->python = v;

        return TRUE;
    }
    else
        return FALSE;
}

Q3CString PythonSettings::relationAttributeUmlStereotype(const Q3CString & s)
{
    read_if_needed_();

    return UmlSettings::uml_rel_attr_stereotype(s, &UmlStereotype::python);
}

Q3CString PythonSettings::classStereotype(const Q3CString & s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_class_stereotypes.find(s);

    return (b) ? b->python : s;
}

bool PythonSettings::set_ClassStereotype(Q3CString s, Q3CString v)
{
    read_if_needed_();
    UmlCom::send_cmd(pythonSettingsCmd, setPythonClassStereotypeCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        UmlStereotype * st = UmlSettings::_map_class_stereotypes.find(s);

        if (st == 0)
            st = UmlSettings::add_class_stereotype(s);

        st->python = v;

        return TRUE;
    }
    else
        return FALSE;
}

Q3CString PythonSettings::classUmlStereotype(const Q3CString & s)
{
    read_if_needed_();

    return UmlSettings::uml_class_stereotype(s, &UmlStereotype::python);
}

Q3CString PythonSettings::get_import(const Q3CString & s)
{
    read_if_needed_();

    Q3CString * r = _map_imports[s];

    return (r) ? *r : Q3CString(0);
}

bool PythonSettings::set_Import(Q3CString s, Q3CString v)
{
    read_if_needed_();
    UmlCom::send_cmd(pythonSettingsCmd, setPythonImportCmd, (const char *)s, (const char *)v); //[rageek] Fix prototype

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

const Q3CString & PythonSettings::rootDir()
{
    read_if_needed_();

    return _root;
}

bool PythonSettings::set_RootDir(Q3CString v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonRootdirCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _root = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & PythonSettings::sourceContent()
{
    read_if_needed_();

    return _src_content;
}

bool PythonSettings::set_SourceContent(Q3CString v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonSourceContentCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _src_content = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & PythonSettings::sourceExtension()
{
    read_if_needed_();

    return _ext;
}

bool PythonSettings::set_SourceExtension(Q3CString v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonSourceExtensionCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _ext = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & PythonSettings::classDecl()
{
    read_if_needed_();

    return _class_decl;
}

bool PythonSettings::set_ClassDecl(Q3CString v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonClassDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _class_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & PythonSettings::externalClassDecl()
{
    read_if_needed_();

    return _external_class_decl;
}

bool PythonSettings::set_ExternalClassDecl(Q3CString v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonExternalClassDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _external_class_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

Q3CString PythonSettings::enumDecl()
{
    read_if_needed_();

    return _enum_decl;
}

bool PythonSettings::set_EnumDecl(Q3CString v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonEnumDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & PythonSettings::attributeDecl(const char * multiplicity)
{
    read_if_needed_();

    return _attr_decl[mult_column(multiplicity)];
}

bool PythonSettings::set_AttributeDecl(const char * multiplicity, Q3CString v)
{
    read_if_needed_();
    UmlCom::send_cmd(pythonSettingsCmd, setPythonAttributeDeclCmd, multiplicity, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _attr_decl[mult_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

Q3CString PythonSettings::enumItemDecl()
{
    read_if_needed_();

    return _enum_item_decl;
}

bool PythonSettings::set_EnumItemDecl(Q3CString v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonEnumItemDeclCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _enum_item_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & PythonSettings::relationDecl(bool by_value, const char * multiplicity)
{
    read_if_needed_();

    return _rel_decl[(by_value) ? 1 : 0][mult_column(multiplicity)];
}

bool PythonSettings::set_RelationDecl(bool by_value, const char * multiplicity, const char * v)
{
    read_if_needed_();
    UmlCom::send_cmd(pythonSettingsCmd, setPythonRelationDeclCmd, by_value, multiplicity, v);

    if (UmlCom::read_bool()) {
        _rel_decl[(by_value) ? 1 : 0][mult_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & PythonSettings::operationDef()
{
    read_if_needed_();

    return _oper_def;
}

bool PythonSettings::set_OperationDef(Q3CString v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonOperationDefCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _oper_def = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & PythonSettings::getName()
{
    read_if_needed_();

    return _get_name;
}

bool PythonSettings::set_GetName(Q3CString v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonGetNameCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _get_name = v;
        return TRUE;
    }
    else
        return FALSE;
}

const Q3CString & PythonSettings::setName()
{
    read_if_needed_();

    return _set_name;
}

bool PythonSettings::set_SetName(Q3CString v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonSetNameCmd, (const char *)v); //[rageek] Fix prototype

    if (UmlCom::read_bool()) {
        _set_name = v;
        return TRUE;
    }
    else
        return FALSE;
}

unsigned PythonSettings::mult_column(const Q3CString & mult)
{
    return (mult.isEmpty() || (mult == "1")) ? 0 : 1;
}

bool PythonSettings::_defined;

bool PythonSettings::_2_2;

Q3CString PythonSettings::_indent_step;

Q3CString PythonSettings::_root;

Q3CString PythonSettings::_class_decl;

Q3CString PythonSettings::_external_class_decl;

Q3CString PythonSettings::_enum_decl;

Q3CString PythonSettings::_attr_decl[2/*multiplicity*/];

Q3CString PythonSettings::_enum_item_decl;

Q3CString PythonSettings::_rel_decl[2/*relation kind*/][2/*multiplicity*/];

Q3CString PythonSettings::_oper_def;

Q3CString PythonSettings::_get_name;

Q3CString PythonSettings::_set_name;

Q3CString PythonSettings::_src_content;

Q3CString PythonSettings::_ext;

Q3Dict<Q3CString> PythonSettings::_map_imports;

void PythonSettings::read_()
{
    _2_2 = UmlCom::read_bool();

    _indent_step = UmlCom::read_string();

    _root = UmlCom::read_string();

    unsigned n;
    unsigned index;

    n = UmlCom::read_unsigned();

    for (index = 0; index != n; index += 1)
        UmlSettings::_relation_attribute_stereotypes[index].python = UmlCom::read_string();

    n = UmlCom::read_unsigned();

    for (index = 0; index != n; index += 1)
        UmlSettings::_class_stereotypes[index].python = UmlCom::read_string();

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
    _attr_decl[0] = UmlCom::read_string();
    _attr_decl[0] = UmlCom::read_string();
    _enum_item_decl = UmlCom::read_string();
    _rel_decl[0][0] = UmlCom::read_string();
    _rel_decl[0][1] = UmlCom::read_string();
    _rel_decl[1][0] = UmlCom::read_string();
    _rel_decl[1][1] = UmlCom::read_string();
    _oper_def = UmlCom::read_string();
    _get_name = UmlCom::read_string();
    _set_name = UmlCom::read_string();
}

void PythonSettings::read_if_needed_()
{
    UmlSettings::read_if_needed_();

    if (!_defined) {
        UmlCom::send_cmd(pythonSettingsCmd, getPythonSettingsCmd);
        read_();
        _defined = TRUE;
    }
}


#endif
