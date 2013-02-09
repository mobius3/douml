#ifdef WITHPYTHON


#include "PythonSettings.h"

#include "UmlCom.h"
#include "UmlSettings.h"
#include "Tools/ApiCmd.h"
#include "UmlBuiltin.h"
#include "UmlStereotype.h"
//Added by qt3to4:
#include "misc/mystr.h"

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

WrapperStr PythonSettings::indentStep()
{
    read_if_needed_();

    return _indent_step;
}

bool PythonSettings::set_IndentStep(const char * v)
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

WrapperStr PythonSettings::relationAttributeStereotype(const WrapperStr & s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_relation_attribute_stereotypes.find(s);

    return (b) ? b->python : s;
}

bool PythonSettings::set_RelationAttributeStereotype(WrapperStr s, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(pythonSettingsCmd, setPythonRelationAttributeStereotypeCmd, s, v);

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

WrapperStr PythonSettings::relationAttributeUmlStereotype(const WrapperStr & s)
{
    read_if_needed_();

    return UmlSettings::uml_rel_attr_stereotype(s, &UmlStereotype::python);
}

WrapperStr PythonSettings::classStereotype(const WrapperStr & s)
{
    read_if_needed_();

    UmlStereotype * b = UmlSettings::_map_class_stereotypes.find(s);

    return (b) ? b->python : s;
}

bool PythonSettings::set_ClassStereotype(WrapperStr s, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(pythonSettingsCmd, setPythonClassStereotypeCmd, s, v);

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

WrapperStr PythonSettings::classUmlStereotype(const WrapperStr & s)
{
    read_if_needed_();

    return UmlSettings::uml_class_stereotype(s, &UmlStereotype::python);
}

WrapperStr PythonSettings::get_import(const WrapperStr & s)
{
    read_if_needed_();

    QString * r = _map_imports[s];

    return (r) ? *r : QString::number(0);
}

bool PythonSettings::set_Import(WrapperStr s, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(pythonSettingsCmd, setPythonImportCmd, s, v);

    if (UmlCom::read_bool()) {
        QString * r = _map_imports.take(s);

        if (!v.isEmpty())
            _map_imports.insert(s, new QString(v.operator QString()));

        if (r)
            delete r;

        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & PythonSettings::rootDir()
{
    read_if_needed_();

    return _root;
}

bool PythonSettings::set_RootDir(WrapperStr v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonRootdirCmd, v);

    if (UmlCom::read_bool()) {
        _root = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & PythonSettings::sourceContent()
{
    read_if_needed_();

    return _src_content;
}

bool PythonSettings::set_SourceContent(WrapperStr v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonSourceContentCmd, v);

    if (UmlCom::read_bool()) {
        _src_content = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & PythonSettings::sourceExtension()
{
    read_if_needed_();

    return _ext;
}

bool PythonSettings::set_SourceExtension(WrapperStr v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonSourceExtensionCmd, v);

    if (UmlCom::read_bool()) {
        _ext = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & PythonSettings::classDecl()
{
    read_if_needed_();

    return _class_decl;
}

bool PythonSettings::set_ClassDecl(WrapperStr v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonClassDeclCmd, v);

    if (UmlCom::read_bool()) {
        _class_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & PythonSettings::externalClassDecl()
{
    read_if_needed_();

    return _external_class_decl;
}

bool PythonSettings::set_ExternalClassDecl(WrapperStr v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonExternalClassDeclCmd, v);

    if (UmlCom::read_bool()) {
        _external_class_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

WrapperStr PythonSettings::enumDecl()
{
    read_if_needed_();

    return _enum_decl;
}

bool PythonSettings::set_EnumDecl(WrapperStr v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonEnumDeclCmd, v);

    if (UmlCom::read_bool()) {
        _enum_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

unsigned PythonSettings::mult_column(const WrapperStr & mult)
{
    return (mult.isEmpty() || (mult == "1")) ? 0 : 1;
}

const WrapperStr & PythonSettings::attributeDecl(const char * multiplicity)
{
    read_if_needed_();

    return _attr_decl[mult_column(multiplicity)];
}

bool PythonSettings::set_AttributeDecl(const char * multiplicity, WrapperStr v)
{
    read_if_needed_();
    UmlCom::send_cmd(pythonSettingsCmd, setPythonAttributeDeclCmd, multiplicity, v);

    if (UmlCom::read_bool()) {
        _attr_decl[mult_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

WrapperStr PythonSettings::enumItemDecl()
{
    read_if_needed_();

    return _enum_item_decl;
}

bool PythonSettings::set_EnumItemDecl(WrapperStr v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonEnumItemDeclCmd, v);

    if (UmlCom::read_bool()) {
        _enum_item_decl = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & PythonSettings::relationDecl(bool composition, const char * multiplicity)
{
    read_if_needed_();

    return _rel_decl[(composition) ? 1 : 0][mult_column(multiplicity)];
}

bool PythonSettings::set_RelationDecl(bool composition, const char * multiplicity, WrapperStr v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonRelationDeclCmd, composition, multiplicity, v);

    if (UmlCom::read_bool()) {
        _rel_decl[(composition) ? 1 : 0][mult_column(multiplicity)] = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & PythonSettings::operationDef()
{
    read_if_needed_();

    return _oper_def;
}

bool PythonSettings::set_OperationDef(WrapperStr v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonOperationDefCmd, v);

    if (UmlCom::read_bool()) {
        _oper_def = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & PythonSettings::getName()
{
    read_if_needed_();

    return _get_name;
}

bool PythonSettings::set_GetName(WrapperStr v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonGetNameCmd, v);

    if (UmlCom::read_bool()) {
        _get_name = v;
        return TRUE;
    }
    else
        return FALSE;
}

const WrapperStr & PythonSettings::setName()
{
    read_if_needed_();

    return _set_name;
}

bool PythonSettings::set_SetName(WrapperStr v)
{
    UmlCom::send_cmd(pythonSettingsCmd, setPythonSetNameCmd, v);

    if (UmlCom::read_bool()) {
        _set_name = v;
        return TRUE;
    }
    else
        return FALSE;
}

bool PythonSettings::_defined;

bool PythonSettings::_2_2;

bool PythonSettings::_operation_3;

WrapperStr PythonSettings::_indent_step;

WrapperStr PythonSettings::_root;

WrapperStr PythonSettings::_class_decl;

WrapperStr PythonSettings::_external_class_decl;

WrapperStr PythonSettings::_enum_decl;

WrapperStr PythonSettings::_attr_decl[2/*multiplicity*/];

WrapperStr PythonSettings::_enum_item_decl;

WrapperStr PythonSettings::_rel_decl[2/*relation kind*/][2/*multiplicity*/];

WrapperStr PythonSettings::_oper_def;

WrapperStr PythonSettings::_get_name;

WrapperStr PythonSettings::_set_name;

WrapperStr PythonSettings::_src_content;

WrapperStr PythonSettings::_ext;

Q3Dict<QString> PythonSettings::_map_imports;

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
        WrapperStr t = UmlCom::read_string();
        WrapperStr i = UmlCom::read_string();

        _map_imports.insert(t, new QString(i.operator QString()));
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
    (void) UmlCom::read_string(); // python_initoper_def

    _operation_3 = UmlCom::read_bool();
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
