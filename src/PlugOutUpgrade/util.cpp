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

#include "UmlClass.h"
#include "UmlOperation.h"
#include "UmlArtifact.h"

#include "util.h"
//Added by qt3to4:
#include "misc/mystr.h"

void defGetField_(UmlClass * base, const char * where, const char * oper,
                  const char * field, UmlTypeSpec type,
                  const char * if_def, const char * end_if,
                  const char * descr, UmlOperation *& op)
{
    WrapperStr body = "  read_if_needed_();\n"
                     "  return " + WrapperStr(where) + "."  + WrapperStr(field) + ";\n";

    op = base->add_op(oper, PublicVisibility, type);
    op->set_Description(" return the " + WrapperStr(descr));
    op->set_cpp("const ${type} &", "", body , FALSE, if_def, end_if);
    op->set_java("${type}", "", body, FALSE);
}

void defSetField_(UmlClass * base, const char * where, const char * oper,
                  const char * field, UmlTypeSpec type,
                  const char * cmd, const char * if_def, const char * end_if,
                  const char * descr, UmlOperation *& op)
{
    op = base->add_op(oper, PublicVisibility, "bool", TRUE);
    op->set_Description(" set the " + WrapperStr(descr) + "\n"
                        "\n"
                        " On error return FALSE in C++, produce a RuntimeException in Java");
    op->add_param(0, InputDirection, "v", type);

    WrapperStr body;

    body = "  return set_it_(" + WrapperStr(where) + "." + WrapperStr(field) + ", v, " + WrapperStr(cmd) + ");\n";
    op->set_cpp("${type}", "const ${t0} ${p0}", body, FALSE, if_def, end_if);

    body = "\
  UmlCom.send_cmd(identifier_(), OnInstanceCmd." + WrapperStr(cmd) + ", v);\n\
  UmlCom.check();\n\
\n\
  " + WrapperStr(where) + "." + WrapperStr(field) + " = v;\n";
    op->set_java("void", "${t0} ${p0}", body, FALSE);
}

void defGet_(UmlClass * base, const char * where, const char * oper,
             UmlTypeSpec type, const char * if_def, const char * end_if,
             const char * descr, UmlOperation *& op)
{
    op = base->add_op(oper, PublicVisibility, type);
    op->set_Description(" return the " + WrapperStr(descr));

    WrapperStr body;

    body = "  read_if_needed_();\n"
           "  return " + WrapperStr(where) + ";\n";

    op->set_cpp("const ${type} &", "", body, FALSE, if_def, end_if);
    op->set_java("${type}", "", body, FALSE);
}

void defSet_(UmlClass * base, const char * where, const char * oper,
             UmlTypeSpec type, const char * cmd, const char * if_def,
             const char * end_if, const char * descr, UmlOperation *& op)
{
    op = base->add_op(oper, PublicVisibility, "bool", TRUE);
    op->set_Description(" set the " + WrapperStr(descr) + "\n"
                        "\n"
                        " On error return FALSE in C++, produce a RuntimeException in Java");
    op->add_param(0, InputDirection, "v", type);

    WrapperStr body;

    body = "  return set_it_(" + WrapperStr(where) + ", v, " + WrapperStr(cmd) + ");\n";
    op->set_cpp("${type}", "const ${t0} ${p0}", body, FALSE, if_def, end_if);

    body = "\
  UmlCom.send_cmd(identifier_(), OnInstanceCmd." + WrapperStr(cmd) + ", v);\n\
  UmlCom.check();\n\
\n\
  " + WrapperStr(where) + " = v;\n";
    op->set_java("void", "${t0} ${p0}", body, FALSE);
}

void defGetPtr_(UmlClass * base, const char * where, const char * oper,
                UmlTypeSpec type, const char * if_def, const char * end_if,
                const char * descr, UmlOperation *& op)
{
    op = base->add_op(oper, PublicVisibility, type);
    op->set_Description(" return the " + WrapperStr(descr));

    WrapperStr body = "  read_if_needed_();\n"
                     "  return " + WrapperStr(where) + ";\n";

    op->set_cpp("${type} *", "", body, FALSE, if_def, end_if);
    op->set_java("${type}", "", body, FALSE);
}

void defSetPtr_(UmlClass * base, const char * where, const char * oper,
                UmlTypeSpec type, const char * cmd, const char * if_def,
                const char * end_if, const char * descr, UmlOperation *& op)
{
    op = base->add_op(oper, PublicVisibility, "bool", TRUE);
    op->set_Description(" set the "  + WrapperStr(descr) + "\n"
                        "\n"
                        " On error return FALSE in C++, produce a RuntimeException in Java");
    op->add_param(0, InputDirection, "v", type);

    WrapperStr body;

    body = "\
  UmlCom::send_cmd(_identifier, " + WrapperStr(cmd) + ", (v == 0) ? (void *) v : ((UmlBaseItem *) v)->_identifier);\n\
  if (UmlCom::read_bool()) {\n\
    " + WrapperStr(where) + " = v;\n\
    return TRUE;\n\
  }\n\
  else\n\
    return FALSE;\n";
    op->set_cpp("${type}", "${t0} * ${p0}", body, FALSE, if_def, end_if);

    body = "\
  UmlCom.send_cmd(identifier_(), OnInstanceCmd." + WrapperStr(cmd) + ", (v == null) ? (long) 0 : v.identifier_());\n\
  UmlCom.check();\n\
\n\
  " + WrapperStr(where) + " = v;\n";
    op->set_java("void", "${t0} ${p0}", body, FALSE);
}

void defSetRefType_(UmlClass * base, const char * where, const char * oper,
                    UmlTypeSpec type, const char * cmd, const char * if_def,
                    const char * end_if, const char * descr, UmlOperation *& op)
{
    op = base->add_op(oper, PublicVisibility, "bool", TRUE);
    op->set_Description(" set the "  + WrapperStr(descr) +  "\n"
                        "\n"
                        " On error return FALSE in C++, produce a RuntimeException in Java");
    op->add_param(0, InputDirection, "v", type);

    WrapperStr body;

    body = "  return set_it_(" + WrapperStr(where) + ", v, " + WrapperStr(cmd) + ");\n";
    op->set_cpp("${type}", "const ${t0} & ${p0}", body, FALSE, if_def, end_if);

    body = "\
  UmlCom.send_cmd(identifier_(), OnInstanceCmd." + WrapperStr(cmd) + ", v);\n\
  UmlCom.check();\n\
\n\
  " + WrapperStr(where) + " = v;\n";
    op->set_java("void", "${t0} ${p0}", body, FALSE);
}

void defGetValue_(UmlClass * base, const char * where, const char * oper,
                  UmlTypeSpec type, const char * if_def, const char * end_if,
                  const char * descr, UmlOperation *& op)
{
    op = base->add_op(oper, PublicVisibility, type);
    op->set_Description(" return the " + WrapperStr(descr));

    WrapperStr body;

    body = "  read_if_needed_();\n"
           "  return " + WrapperStr(where) + ";\n";

    op->set_cpp("${type}", "", body, FALSE, if_def, end_if);
    op->set_java("${type}", "", body, FALSE);
}

void defSetBool_(UmlClass * base, const char * where, const char * oper,
                 const char * cmd, const char * if_def, const char * end_if,
                 const char * descr, UmlOperation *& op)
{
    op = base->add_op(oper, PublicVisibility, "bool", TRUE);
    op->set_Description(WrapperStr(descr) + "\n"
                        "\n"
                        " On error return FALSE in C++, produce a RuntimeException in Java");
    op->add_param(0, InputDirection, "v", "bool");

    WrapperStr body;

    body = "  return set_it_(" + WrapperStr(where) + ", v, " + WrapperStr(cmd) + ");\n";
    op->set_cpp("${type}", "${t0} ${p0}", body, FALSE, if_def, end_if);

    body = "\
  UmlCom.send_cmd(identifier_(), OnInstanceCmd." + WrapperStr(cmd) + ", (v) ? (byte) 1 : (byte) 0);\n\
  UmlCom.check();\n\
\n\
  " + WrapperStr(where) + " = v;\n";
    op->set_java("void", "${t0} ${p0}", body, FALSE);
}

void defSetEnum_(UmlClass * base, const char * where, const char * oper,
                 UmlTypeSpec type, const char * cmd, const char * if_def,
                 const char * end_if, const char * descr, UmlOperation *& op)
{
    op = base->add_op(oper, PublicVisibility, "bool", TRUE);
    op->set_Description(" set the " + WrapperStr(descr) + "\n"
                        "\n"
                        " On error return FALSE in C++, produce a RuntimeException in Java");
    op->add_param(0, InputDirection, "v", type);

    WrapperStr body;

    body = "\
  UmlCom::send_cmd(_identifier, " + WrapperStr(cmd) + ", (char) v);\n\
  if (UmlCom::read_bool()) {\n\
    " + WrapperStr(where) + " = v;\n\
    return TRUE;\n\
  }\n\
  else\n\
    return FALSE;\n";
    op->set_cpp("${type}", "${t0} ${p0}", body, FALSE, if_def, end_if);

    body = "\
  UmlCom.send_cmd(identifier_(), OnInstanceCmd." + WrapperStr(cmd) + ", (byte) v.value());\n\
  UmlCom.check();\n\
\n\
  " + WrapperStr(where) + " = v;\n";
    op->set_java("void", "${t0} ${p0}", body, FALSE);
}

void defSetBoolBitField_(UmlClass * base, const char * where, const char * oper,
                         const char * cmd, const char * if_def, const char * end_if,
                         const char * descr, UmlOperation *& op)
{
    op = base->add_op(oper, PublicVisibility, "bool", TRUE);
    op->set_Description(WrapperStr(descr) + "\n"
                        "\n"
                        " On error return FALSE in C++, produce a RuntimeException in Java");
    op->add_param(0, InputDirection, "v", "bool");

    WrapperStr body;

    body = "\
  UmlCom::send_cmd(_identifier, " + WrapperStr(cmd) + ", (char) v);\n\
  if (UmlCom::read_bool()) {\n\
    " + WrapperStr(where) + " = v;\n\
    return TRUE;\n\
  }\n\
  else\n\
    return FALSE;\n";
    op->set_cpp("${type}", "${t0} ${p0}", body, FALSE, if_def, end_if);

    body = "\
  UmlCom.send_cmd(identifier_(), OnInstanceCmd." + WrapperStr(cmd) + ", (v) ? 1 : 0);\n\
  UmlCom.check();\n\
\n\
  " + WrapperStr(where) + " = v;\n";
    op->set_java("void", "${t0} ${p0}", body, FALSE);
}

//

void include_umlcom(UmlClass * cl)
{
    UmlArtifact * art = cl->associatedArtifact();
    WrapperStr s = art->cppSource();

    s.insert(s.find("${includes}"), "#include \"UmlCom.h\"\n");
    art->set_CppSource(s);
}

void include_umlcom(UmlArtifact * art)
{
    WrapperStr s = art->cppSource();

    s.insert(s.find("${includes}"), "#include \"UmlCom.h\"\n");
    art->set_CppSource(s);
}

//

void add_assoc_diag_ops(UmlClass * base, UmlClass * diag)
{
    UmlOperation * op;

    op = base->add_op("associatedDiagram", PublicVisibility, diag);

    op->set_cpp("${type} *", "",
                "  read_if_needed_();\n\n"
                "  return _assoc_diagram;\n",
                FALSE, 0, 0);
    op->set_java("${type}", "",
                 "  read_if_needed_();\n\n"
                 "  return _assoc_diagram;\n",
                 FALSE);
    op->set_Description(" returns the optional associated diagram");

    //

    op = base->add_op("set_AssociatedDiagram", PublicVisibility, "bool", TRUE);
    op->add_param(0, InputDirection, "d", diag);

    op->set_cpp("${type}", "${t0} * ${p0}",
                "  UmlCom::send_cmd(_identifier, setAssocDiagramCmd, (d == 0) ? (void *) 0 : ((UmlBaseItem *) d)->_identifier);\n"
                "  if (UmlCom::read_bool()) {\n"
                "    _assoc_diagram = d;\n"
                "    return TRUE;\n"
                "  }\n"
                "  else\n"
                "    return FALSE;\n",
                FALSE, 0, 0);
    op->set_java("void", "${t0} ${p0}",
                 "  UmlCom.send_cmd(identifier_(), OnInstanceCmd.setAssocDiagramCmd, (d == null) ? (long) 0 : d.identifier_());\n"
                 "  UmlCom.check();\n"
                 "  _assoc_diagram = d;\n",
                 FALSE);
    op->set_Description(" sets the associated diagram, arg may be null to unset it\n\n"
                        " On error return FALSE in C++, produce a RuntimeException in Java");
}
//

void conditional(WrapperStr & s, const char * if_def, const char * end_if)
{
    if (if_def != 0) {
        const char * p = s;
        const char * p2 = p;

        while ((*p2 == ' ') || (*p2 == '\t'))
            p2 += 1;

        s.insert(p2 - p, (const char *)(WrapperStr("#ifdef ") + if_def + "\n"));
    }

    if (end_if != 0)
        s.append((((const char *) s)[s.length() - 1] == '\n')
                 ? "#endif\n"
                 : "\n#endif");
}

//

WrapperStr java2Php(WrapperStr s)
{
    int index;

    while ((index = s.find("JAVA")) != -1)
        s.replace(index, 4, "PHP");

    while ((index = s.find("Java")) != -1)
        s.replace(index, 4, "Php");

    while ((index = s.find("java")) != -1)
        s.replace(index, 4, "php");

    if ((index = s.find("produce a RuntimeException in Php")) != -1)
        s.replace(index + 30, 3, "Java");

    return s;
}

WrapperStr java2Python(WrapperStr s)
{
    int index;

    while ((index = s.find("JAVA")) != -1)
        s.replace(index, 4, "PYTHON");

    while ((index = s.find("Java")) != -1)
        s.replace(index, 4, "Python");

    while ((index = s.find("java")) != -1)
        s.replace(index, 4, "python");

    if ((index = s.find("produce a RuntimeException in Python")) != -1)
        s.replace(index + 30, 6, "Java");

    return s;
}

WrapperStr cpp2Python(WrapperStr s)
{
    int index;

    while ((index = s.find("CPP")) != -1)
        s.replace(index, 3, "PYTHON");

    while ((index = s.find("Cpp")) != -1)
        s.replace(index, 3, "Python");

    while ((index = s.find("cpp")) != -1)
        s.replace(index, 3, "python");

    return s;
}

