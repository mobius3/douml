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

#ifndef PACKAGEDATA_H
#define PACKAGEDATA_H

#include "SimpleData.h"
//Added by qt3to4:
#include <QTextStream>

class QTextStream;

class BrowserPackage;
class PackageDialog;

class PackageData : public SimpleData
{
    friend class PackageDialog;

protected:
    WrapperStr cpp_src_dir;
    WrapperStr cpp_h_dir;
    WrapperStr java_dir;
    WrapperStr php_dir;
    WrapperStr python_dir;
    WrapperStr idl_dir;

    WrapperStr cpp_namespace;
    WrapperStr java_package;
    WrapperStr php_namespace;
    WrapperStr python_package;
    WrapperStr idl_module;

    virtual void send_cpp_def(ToolCom * com);
    virtual void send_java_def(ToolCom * com);
    virtual void send_php_def(ToolCom * com);
    virtual void send_python_def(ToolCom * com);
    virtual void send_idl_def(ToolCom * com);

public:
    PackageData();
    PackageData(PackageData * model);
    virtual ~PackageData();

    void edit();

    const WrapperStr & get_cpp_src_dir() const {
        return cpp_src_dir;
    };
    const WrapperStr & get_cpp_h_dir() const {
        return cpp_h_dir;
    };
    const WrapperStr & get_java_dir() const {
        return java_dir;
    };
    const WrapperStr & get_php_dir() const {
        return php_dir;
    };
    const WrapperStr & get_python_dir() const {
        return python_dir;
    };
    const WrapperStr & get_idl_dir() const {
        return idl_dir;
    };

    const WrapperStr & get_cpp_namespace() const {
        return cpp_namespace;
    };
    const WrapperStr & get_java_package() const {
        return java_package;
    };
    const WrapperStr & get_php_namespace() const {
        return php_namespace;
    };
    const WrapperStr & get_python_package() const {
        return python_package;
    };
    const WrapperStr & get_idl_module() const {
        return idl_module;
    };

    virtual bool tool_cmd(ToolCom * com, const char * args,
                          BrowserNode * bn, const QString & comment);

    void save(QTextStream &, QString & warning) const;
    void read(char *& st, char *& k);
};

#endif
