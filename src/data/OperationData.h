// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
// Copyright 2012-2013 Nikolai Marchenko.
// Copyright 2012-2013 Leonardo Guilherme.
//
// This file is part of the DOUML Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License Version 3.0 as published by
// the Free Software Foundation and appearing in the file LICENSE.GPL included in the
//  packaging of this file.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License Version 3.0 for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// e-mail : doumleditor@gmail.com
// home   : http://sourceforge.net/projects/douml
//
// *************************************************************************

#ifndef OPERATIONDATA_H
#define OPERATIONDATA_H

#include <q3memarray.h>
//Added by qt3to4:
#include <QTextStream>
#include  <memory>


#include "UmlEnum.h"
#include "AType.h"
#include "ClassMemberData.h"
#include "Labeled.h"
#include "MultipleDependency.h"

class QFile;
class ParamData;
class ExceptionData;
class KeyValueData;
class BrowserClass;
class BrowserOperation;
class BrowserOperationAttribute;
class BrowserOperationReturnType;
class QuickEdit;
class OperationBody
{
public:
    int offset;	// offset in the file
    int length;	// body length, 0 if empty, -1 if unknown (file not yet read)

    OperationBody() : offset(0), length(0) {};
};

class OperationData : public ClassMemberData,
    public Labeled<OperationData>,
    public MultipleDependency<BasicData>
{
    Q_OBJECT

    friend class OperationDialog;
    friend class BrowserOperation;
    friend class QuickEdit;
    friend class BrowserOperationAttribute;
    friend class BrowserOperationReturnType;

protected:
    static IdDict<OperationData> all;

    // uml
    UmlVisibility uml_visibility : 4;
    UmlVisibility cpp_visibility : 4;
    bool is_deleted : 1;
    bool is_get_or_set : 1;
    bool isa_class_operation : 1;
    bool is_abstract : 1;
    bool force_body_gen : 1;
    bool is_volatile : 1;
    bool cpp_const : 1;			// C++
    bool cpp_friend : 1;		// C++
    bool cpp_virtual : 1;		// C++
    bool cpp_inline : 1;		// C++
    bool cpp_default : 1;		// C++
    bool cpp_delete : 1;		// C++
    bool cpp_override : 1;		// C++
    bool cpp_final : 1;		// C++
    bool cpp_get_set_frozen : 1;	// C++
    bool cpp_indent_body : 1;		// C++
    bool java_final : 1;		// Java
    bool java_synchronized : 1;		// java
    bool java_get_set_frozen : 1;	// java
    bool java_indent_body : 1;		// java
    bool php_final : 1;			// php
    bool php_get_set_frozen : 1;	// php
    bool php_indent_body : 1;		// php
    bool python_get_set_frozen : 1;	// python
    bool python_indent_body : 1;	// python
    bool idl_oneway : 1;		// Idl
    bool idl_get_set_frozen : 1;	// Idl
    unsigned short nparams;
    unsigned short nexceptions;
    AType return_type;
    WrapperStr originClass = QString("0");
    QList<std::shared_ptr<ParamData>> params;
    //ParamData * params = nullptr;			// remark : do NOT use QArray
    ExceptionData * exceptions;
    WrapperStr constraint;

    // c++
    OperationBody cpp_body;
    WrapperStr cpp_decl;
    WrapperStr cpp_def;
    WrapperStr cpp_name_spec;	// get_${name}

    // java
    OperationBody java_body;
    WrapperStr java_def;
    WrapperStr java_name_spec;	// get${Name}
    WrapperStr java_annotation;

    // php
    OperationBody php_body;
    WrapperStr php_def;
    WrapperStr php_name_spec;	// get${Name}

    // python
    OperationBody python_body;
    WrapperStr python_def;
    WrapperStr python_name_spec;	// get${Name}
    WrapperStr python_decorator;

    // idl
    WrapperStr idl_decl;
    WrapperStr idl_name_spec;	// get_${name}

    friend bool operator==(const OperationData & , const OperationData & );
    friend bool PropagationEquality(const OperationData & origin, const OperationData & another);

    void depend_on(BrowserClass * cl);
    void no_longer_depend_on(BrowserClass * cl);

    virtual void send_uml_def(ToolCom * com, BrowserNode * bn,
                              const QString & comment);
    virtual void send_cpp_def(ToolCom * com);
    virtual void send_java_def(ToolCom * com);
    virtual void send_php_def(ToolCom * com);
    virtual void send_python_def(ToolCom * com);
    virtual void send_idl_def(ToolCom * com);

    void set_bodies_info();
    static char * set_bodies_info(BrowserClass * cl, int id);

public:
    OperationData(int id = 0);
    OperationData(OperationData * model, BrowserNode *);
    virtual ~OperationData();
    void PropagateFrom(const OperationData*, bool goBack = true, QList<const OperationData *> passed = QList<const OperationData *>());

    virtual bool deletedp() const;
    virtual void set_deletedp(bool y);

    void remove_param(std::shared_ptr<ParamData>);
    void insert_param(int position, std::shared_ptr<ParamData> param);

    void set_browser_node(BrowserOperation *, bool update);

    virtual QString definition(bool full, bool with_kind) const;
    QString definition(bool full, bool withdir, bool withname,
                       ShowContextMode mode = noContext) const;
    QString definition(bool full, DrawingLanguage language,
                       bool withdir, bool withname,
                       ShowContextMode mode = noContext) const;

    virtual bool decldefbody_contain(const QString & s, bool cs, BrowserNode *);

    const char * get_constraint() const {
        return constraint;
    }

    bool get_isa_class_operation() const {
        return isa_class_operation;
    };
    void set_isa_class_operation(bool value) {
        isa_class_operation = value;
    };

    bool get_is_abstract() const {
        return is_abstract;
    };
    void set_is_abstract(bool yes);

    bool get_is_volatile() const {
        return is_volatile;
    }
    void set_is_volatile(bool value){
        is_volatile = value;
    }
    bool body_generation_forced() const {
        return force_body_gen;
    };

    bool get_cpp_const() const {
        return cpp_const;
    };
    void set_cpp_const(bool value){
        cpp_const = value;
    }
    bool get_cpp_friend() const {
        return cpp_friend;
    };
    void set_cpp_friend(bool value){
        cpp_friend = value;
    }
    bool get_cpp_virtual() const {
        return cpp_virtual;
    };
    void set_cpp_virtual(bool value){
        cpp_virtual = value;
    }
    bool get_cpp_inline() const {
        return cpp_inline;
    };
    void set_cpp_inline(bool value){
        cpp_inline = value;
    }
    bool get_cpp_default() const {
        return cpp_default;
    };
    void set_cpp_default(bool value){
        cpp_default = value;
    }
    bool get_cpp_delete() const {
        return cpp_delete;
    }
    void set_cpp_delete(bool value){
        cpp_delete = value;
    }
    bool get_cpp_override() const {
        return cpp_override;
    };
    void set_cpp_override(bool value){
        cpp_override = value;
    }
    bool get_cpp_final() const {
        return cpp_final;
    };
    void set_cpp_final(bool value){
        cpp_final = value;
    }
    QString get_cpp_name_spec() const {
        return cpp_name_spec;
    }
    void set_cpp_pass_type(QString value)
    {
        value = value;
        //do nothing, yet
    }
    QString get_cpp_pass_type() const
    {
        return QString();
    }

    bool get_java_final() const {
        return java_final;
    };
    void set_java_final(bool value){
        java_final = value;
    }
    bool get_java_synchronized() const {
        return java_synchronized;
    };
    void set_java_synchronized(bool value){
        java_synchronized = value;
    }
    bool get_php_final() const {
        return php_final;
    };
    void set_php_final(bool value){
        php_final = value;
    }

    bool get_idl_oneway() const {
        return idl_oneway;
    };
    void set_idl_oneway(bool value){
        idl_oneway = value;
    }
    WrapperStr get_origin_class() { return originClass;}

    UmlVisibility get_uml_visibility() const {
        return uml_visibility;
    };
    virtual UmlVisibility get_visibility(BrowserNode *);
    UmlVisibility get_cpp_visibility() const {
        return cpp_visibility;
    };
    void set_uml_visibility(UmlVisibility v);
    void set_cpp_visibility(UmlVisibility v);
    void set_cpp_visibility(int v);
    void set_origin_class(WrapperStr value){originClass = value;}
    const AType & get_return_type() const {
        return return_type;
    };
    void set_return_type(const AType & t);
    void set_return_type(const QString & value);

    const char * get_param_name(int rank) const;
    QStringList get_param_names() const;
    QStringList get_param_types() const;
    QStringList get_param_default_values() const;
    void set_param_name(int rank, const char * s);
    UmlParamDirection get_param_dir(int rank) const;
    void set_param_dir(int rank, UmlParamDirection d);
    const AType & get_param_type(int rank) const;
    void set_param_type(int rank, const AType & t);
    const char * get_param_default_value(int rank) const;
    void set_param_default_value(int rank, const char * s);
    unsigned get_n_params() const {
        return nparams;
    };
    void set_n_params(unsigned n);	// the old params are lost

    const AType & get_exception(int rank) const;
    void set_exception(int rank, const AType & t);
    unsigned get_n_exceptions() const {
        return nexceptions;
    };
    void set_n_exceptions(unsigned n);	// the old exceptions are lost

    const char * get_cppdecl() const
    {
        return cpp_decl;
    };
    const char * get_cppdef() const
    {
            return cpp_def;
    };
    void set_cppdef(QString value){cpp_def = value;}
    void set_cppdecl(QString value){cpp_decl = value;}
    QString default_cpp_decl(const QString & name);
    QString default_cpp_def(const QString & name);

    const char * get_javadef() const {
        return java_def;
    };
    void set_javadef(QString value){java_def = value;}
    QString default_java_def(const QString & name);

    const char * get_phpdef() const {
        return php_def;
    };
    void set_phpdef(QString value){php_def = value;}
    QString default_php_def(const QString & name, bool nobody);

    const char * get_pythondef() const {
        return python_def;
    };
    void set_pythondef(QString value){python_def = value;}
    QString default_python_def(const QString & name);

    const char * get_idldecl() const {
        return idl_decl;
    };
    void set_idldecl(QString value){idl_decl = value;}
    QString default_idl_decl(const QString & name);

    void edit(DrawingLanguage);

    bool get_or_set() const {
        return is_get_or_set;
    }
    void set_get_or_set(bool value)  {
        is_get_or_set = value;
    }
    void update_get_of(const QString & attr_name,
                       QString cpp_decl, QString java_decl,
                       QString php_decl, QString python_decl,
                       QString idl_decl,
                       bool cpp_const, bool is_class_member,
                       const AType & cl, QString multiplicity,
                       QString stereotype, bool create);
    void update_set_of(const QString & attr_name,
                       QString cpp_decl, QString java_decl,
                       QString php_decl, QString python_decl,
                       QString idl_decl,
                       bool cpp_const, bool is_class_member,
                       const AType & cl, QString multiplicity,
                       QString stereotype, bool create);
    void copy_getset(const OperationData * model);

    virtual bool tool_cmd(ToolCom * com, const char * args,
                          BrowserNode * bn, const QString & comment);

    bool reference(BrowserClass *) const;

    void new_body(QString, int who);
    char * get_body(int who);
    void create_modified_body_file();
    void save_body(QFile & qf, QString & filename, bool dobackup,
                   char * modified_bodies, int who);
    void save(QTextStream &, bool ref, QString & warning) const;
    void raz_body();
    static OperationData * read_ref(char *&);
    void read(char *& , char *&);
    static void import(BrowserClass * cl, int id);

    static void clear(bool old);
    static void update_idmax_for_root();
    void renumber(int phase);

    bool is_template_operation() const;
    bool is_template_operation(QString) const;

    void replace(BrowserClass * old, BrowserClass * nw);

    static void convert(OperationData * comp, OperationData * art);
    static void update_cpp_get_of(WrapperStr & decl, WrapperStr & def,
                                  const QString & attr_name,
                                  QString attcpp_decl, bool attis_const,
                                  QString multiplicity, bool isStatic);
    static void update_java_get_of(WrapperStr & def, const QString & attr_name,
                                   QString attjava_decl, QString multiplicity);
    static void update_php_get_of(WrapperStr & def, const QString & attr_name,
                                  QString attphp_decl);
    static void update_python_get_of(WrapperStr & def, const QString & attr_name,
                                     QString attpython_decl, bool attis_class_member);
    static void update_idl_get_of(WrapperStr & decl, QString attidl_decl,
                                  QString multiplicity);
    void update_cpp_set_of(WrapperStr & decl, WrapperStr & def,
                           const QString & attr_name,
                           QString attcpp_decl, bool attis_const,
                           QString multiplicity);
    static void update_java_set_of(WrapperStr & def, const QString & attr_name,
                                   QString attjava_decl, QString multiplicity);
    static void update_php_set_of(WrapperStr & def,
                                  const QString & attr_name,
                                  QString attphp_decl);
    static void update_python_set_of(WrapperStr & def, const QString & attr_name,
                                     QString attpython_decl, bool attis_class_member);
    static void update_idl_set_of(WrapperStr & decl, QString attidl_decl,
                                  QString multiplicity);

protected slots:
    void on_delete();
};

bool operator==(const OperationData & s1, const OperationData & s2);
bool PropagationEquality(const OperationData & origin, const OperationData & another);
//bool operator!=(const OperationData & s1, const OperationData & s2);
#endif

