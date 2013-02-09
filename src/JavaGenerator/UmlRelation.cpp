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

#include <QTextStream>
//Added by qt3to4:
#include "misc/mystr.h"
#include <QTextStream>
#include <Q3ValueList>

#include "UmlRelation.h"
#include "UmlClass.h"
#include "UmlSettings.h"
#include "JavaSettings.h"
#include "util.h"
#include "UmlCom.h"

void UmlRelation::generate_extends(const char *& sep, QTextStream & f,
                                   const Q3ValueList<UmlActualParameter> & actuals,
                                   const WrapperStr & cl_stereotype)
{
    switch (relationKind()) {
    default:
        return;

    case aGeneralisation:
    case aRealization:
        if (javaDecl().isEmpty())
            return;

        UmlClass * role_type = roleType();
        const WrapperStr & other_stereotype = role_type->java_stereotype();

        if ((cl_stereotype == "interface") || (cl_stereotype == "@interface")) {
            if ((other_stereotype != "interface") && (other_stereotype != "@interface")) {
                write_trace_header();
                UmlCom::trace(WrapperStr("&nbsp;&nbsp;&nbsp;&nbsp;<font color=\"red\"><b>cannot extends a <i>")
                              + other_stereotype + "</i></b></font><br>");
                incr_warning();
                return;
            }
        }
        else if ((other_stereotype != "interface") && (other_stereotype != "@interface")) {
            if ((cl_stereotype == "union") || (cl_stereotype == "enum_pattern")) {
                write_trace_header();
                UmlCom::trace(WrapperStr("&nbsp;&nbsp;&nbsp;&nbsp;<font color=\"red\"><b>an <i>")
                              + cl_stereotype + "</i> cannot extends</b></font><br>");
                incr_warning();
                return;
            }
            else if ((other_stereotype == "union") ||
                     (other_stereotype == "enum") ||
                     (other_stereotype == "enum_pattern")) {
                write_trace_header();
                UmlCom::trace(WrapperStr("&nbsp;&nbsp;&nbsp;&nbsp;<font color=\"red\"><b>cannot extends an <i>")
                              + other_stereotype + "</i></b></font><br>");
                incr_warning();
                return;
            }
            else if (*sep == ',') {
                write_trace_header();
                UmlCom::trace("&nbsp;&nbsp;&nbsp;&nbsp;<font color=\"red\"><b>extend several classes</b></font><br>");
                incr_warning();
                return;
            }
        }
        else
            return;

        // here the code is legal
        f << sep;
        sep = ", ";

        const char * p = javaDecl();

        while (*p) {
            if (!strncmp(p, "${type}", 7)) {
                role_type->write(f);
                p += 7;

                if (!actuals.isEmpty()) {
                    Q3ValueList<UmlActualParameter>::ConstIterator ita;
                    bool used = FALSE;

                    for (ita = actuals.begin(); ita != actuals.end(); ++ita) {
                        if ((*ita).superClass() == role_type) {
                            used = TRUE;
                            (*ita).generate(f);
                        }
                    }

                    if (used) {
                        f << ">";
                    }
                }
            }
            else if (*p == '@')
                manage_alias(p, f);
            else
                f << *p++;
        }
    }
}

void UmlRelation::generate_implements(const char *& sep, QTextStream & f,
                                      const Q3ValueList<UmlActualParameter> & actuals,
                                      const WrapperStr & cl_stereotype)
{
    switch (relationKind()) {
    default:
        return;

    case aGeneralisation:
    case aRealization:
        if (javaDecl().isEmpty())
            return;

        UmlClass * role_type = roleType();
        const WrapperStr & other_stereotype = role_type->java_stereotype();

        if ((other_stereotype == "interface") || (other_stereotype == "@interface")) {
            if ((cl_stereotype == "union") || (cl_stereotype == "enum_pattern")) {
                write_trace_header();
                UmlCom::trace(WrapperStr("&nbsp;&nbsp;&nbsp;&nbsp;<font color=\"red\"><b>an <i>")
                              + cl_stereotype + "</i> cannot inherits</b></font><br>");
                incr_warning();
            }
            else {
                f << sep;
                sep = ", ";

                const char * p = javaDecl();

                while (*p) {
                    if (!strncmp(p, "${type}", 7)) {
                        role_type->write(f);
                        p += 7;

                        if (!actuals.isEmpty()) {
                            Q3ValueList<UmlActualParameter>::ConstIterator ita;
                            bool used = FALSE;

                            for (ita = actuals.begin(); ita != actuals.end(); ++ita) {
                                if ((*ita).superClass() == role_type) {
                                    used = TRUE;
                                    (*ita).generate(f);
                                }
                            }

                            if (used) {
                                f << ">";
                            }
                        }
                    }
                    else if (*p == '@')
                        manage_alias(p, f);
                    else
                        f << *p++;
                }
            }
        }
    }
}

void UmlRelation::generate(QTextStream & f, const WrapperStr & cl_stereotype,
                           WrapperStr indent)
{
    switch (relationKind()) {
    case aDependency:
    case aGeneralisation:
    case aRealization:
        break;

    default:
        if (!javaDecl().isEmpty()) {
            if (cl_stereotype == "enum_pattern") {
                write_trace_header();
                UmlCom::trace("&nbsp;&nbsp;&nbsp;&nbsp;<font color=\"red\"><b>an <i>enum_pattern</i> cannot have relation</b></font><br>");
                incr_warning();
                return;
            }

            const char * p = javaDecl();
            const char * pp = 0;
            WrapperStr s;

            while ((*p == ' ') || (*p == '\t'))
                indent += *p++;

            f << indent;

            for (;;) {
                if (*p == 0) {
                    if (pp == 0)
                        break;

                    // comment management done
                    p = pp;
                    pp = 0;

                    if (*p == 0)
                        break;

                    f << indent;
                }

                if (*p == '\n') {
                    f << *p++;

                    if (*p)
                        f << indent;
                }
                else if (*p == '@')
                    manage_alias(p, f);
                else if (*p != '$')
                    f << *p++;
                else if (!strncmp(p, "${comment}", 10))
                    manage_comment(p, pp, JavaSettings::isGenerateJavadocStyleComment());
                else if (!strncmp(p, "${description}", 14))
                    manage_description(p, pp);
                else if (!strncmp(p, "${visibility}", 13)) {
                    p += 13;
                    generate_visibility(f, cl_stereotype);
                }
                else if (!strncmp(p, "${static}", 9)) {
                    p += 9;

                    if (isClassMember())
                        f << "static ";
                }
                else if (!strncmp(p, "${final}", 8)) {
                    p += 8;

                    if (isReadOnly())
                        f << "final ";
                }
                else if (!strncmp(p, "${transient}", 12)) {
                    p += 12;

                    if (isJavaTransient())
                        f << "transient ";
                }
                else if (!strncmp(p, "${volatile}", 11)) {
                    p += 11;

                    if (isVolatile())
                        f << "volatile ";
                }
                else if (!strncmp(p, "${type}", 7)) {
                    p += 7;
                    roleType()->write(f);
                }
                else if (!strncmp(p, "${stereotype}", 13)) {
                    p += 13;
                    f << JavaSettings::relationAttributeStereotype(stereotype());
                }
                else if (!strncmp(p, "${name}", 7)) {
                    p += 7;
                    f << roleName();
                }
                else if (!strncmp(p, "${inverse_name}", 15)) {
                    p += 15;

                    switch (relationKind()) {
                    case anAssociation:
                    case anAggregation:
                    case anAggregationByValue:
                        f << side(side(TRUE) != this)->roleName();

                    default:
                        break;
                    }
                }
                else if (!strncmp(p, "${multiplicity}", 15)) {
                    p += 15;

                    WrapperStr m = multiplicity();

                    if (*m != '[')
                        f << "[]";
                    else {
                        for (unsigned index = 0; index != m.length(); index += 1) {
                            switch (m.at(index).toAscii().at(0)) {
                            case '[':
                                f << '[';
                                break;

                            case ']':
                                f << ']';

                            default:
                                break;
                            }
                        }
                    }
                }
                else if (!strncmp(p, "${value}", 8)) {
                    if (!defaultValue().isEmpty()) {
                        if (need_equal(p, defaultValue()))
                            f << " = ";

                        f << defaultValue();
                    }

                    p += 8;
                }
                else if (!strncmp(p, "${association}", 14)) {
                    p += 14;
                    UmlClass::write(f, association());
                }
                else if (!strncmp(p, "${@}", 4)) {
                    p += 4;

                    if (pp != 0)
                        f << "${@}";
                    else if (! javaAnnotations().isEmpty()) {
                        pp = p;
                        p = javaAnnotations();
                    }
                }
                else
                    // strange
                    f << *p++;
            }

            f << '\n';
        }
    }
}

void UmlRelation::generate_enum_pattern_item(QTextStream &, int &,
        const WrapperStr &, WrapperStr)
{
    write_trace_header();
    UmlCom::trace("&nbsp;&nbsp;&nbsp;&nbsp;<font color=\"red\"><b>an <i>enum_pattern</i> cannot have relation</b></font><br>");
    incr_warning();
}

void UmlRelation::generate_enum_pattern_case(QTextStream &, WrapperStr)
{
    // error already signaled
}

void UmlRelation::generate_enum_member(QTextStream & f, WrapperStr indent)
{
    generate(f, "enum", indent);
}

void UmlRelation::generate_import(QTextStream & f, const WrapperStr & indent)
{
    if ((relationKind() == aDependency) &&
        (stereotype() == "import"))
        roleType()->import(f, indent);
}
