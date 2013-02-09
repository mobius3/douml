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

#include "UmlAttribute.h"
#include "UmlSettings.h"
#include "JavaSettings.h"
#include "UmlClass.h"
#include "UmlCom.h"
#include "util.h"

void UmlAttribute::generate(QTextStream & f, const WrapperStr & cl_stereotype,
                            WrapperStr indent)
{
    generate(f, cl_stereotype, indent, FALSE);
}

void UmlAttribute::generate(QTextStream & f, const WrapperStr & cl_stereotype,
                            WrapperStr indent, bool enumitem)
{
    if (!javaDecl().isEmpty()) {
        const char * p = javaDecl();
        const char * pp = 0;

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
                UmlClass::write(f, type());
            }
            else if (!strncmp(p, "${stereotype}", 13)) {
                p += 13;
                f << JavaSettings::relationAttributeStereotype(stereotype());
            }
            else if (!strncmp(p, "${name}", 7)) {
                p += 7;
                f << name();
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
                    if (enumitem)
                        f << '(' << defaultValue() << ')';
                    else {
                        if (need_equal(p, defaultValue()))
                            f << " = ";

                        f << defaultValue();
                    }
                }

                p += 8;
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

        if (cl_stereotype != "enum")
            f << '\n';
    }
}

void UmlAttribute::generate_enum_pattern_item(QTextStream & f, int & current_value,
        const WrapperStr & class_name,
        WrapperStr indent)
{
    if (!javaDecl().isEmpty()) {
        const char * p = javaDecl();
        const char * pp = 0;

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

            if (!strncmp(p, "${comment}", 10))
                manage_comment(p, pp, JavaSettings::isGenerateJavadocStyleComment());
            else if (!strncmp(p, "${description}", 14))
                manage_description(p, pp);
            else if (!strncmp(p, "${name}", 7)) {
                p += 7;
                f << name();
            }
            else if (!strncmp(p, "${class}", 8)) {
                p += 8;
                f << class_name;
            }
            else if (!strncmp(p, "${value}", 8)) {
                p += 8;

                if (!defaultValue().isEmpty()) {
                    WrapperStr d = defaultValue().simplifyWhiteSpace();

                    if (*((const char *) d) == '=')
                        d = d.mid(1).simplifyWhiteSpace();

                    bool ok;
                    int v;

                    v = d.operator QString().toInt(&ok);

                    if (! ok) {
                        UmlCom::trace(WrapperStr("&nbsp;&nbsp;&nbsp;&nbsp;<font color=\"red\"><b><i>") +
                                      defaultValue() + "</i> wrong value for <i> "
                                      + name() + "</i></b></font><br>");
                        incr_error();
                    }
                    else
                        current_value = v;
                }

                f << " = " << current_value++;
            }
            else if (*p == '\n') {
                f << *p++;

                if (*p)
                    f << indent;
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
            else if (*p == '@')
                manage_alias(p, f);
            else
                f << *p++;
        }
    }
}

void UmlAttribute::generate_enum_pattern_case(QTextStream & f,
        WrapperStr indent)
{
    if (!javaDecl().isEmpty()) {
        const char * p = JavaSettings::enumPatternItemCase();
        const char * pp = 0;

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

            if (!strncmp(p, "${comment}", 10))
                manage_comment(p, pp, JavaSettings::isGenerateJavadocStyleComment());
            else if (!strncmp(p, "${description}", 14))
                manage_description(p, pp);
            else if (!strncmp(p, "${name}", 7)) {
                p += 7;
                f << name();
            }
            else if (*p == '\n') {
                f << *p++;

                if (*p)
                    f << indent;
            }
            else if (*p == '@')
                manage_alias(p, f);
            else
                f << *p++;
        }
    }
}

void UmlAttribute::generate_enum_item(QTextStream & f,
                                      WrapperStr indent,
                                      BooL & first)
{
    if (stereotype() != "attribute") {
        if (first)
            first = FALSE;
        else
            f << '\n';

        generate(f, "enum", indent, TRUE);
    }
}

void UmlAttribute::generate_enum_member(QTextStream & f,
                                        WrapperStr indent)
{
    if (stereotype() == "attribute")
        generate(f, "enum", indent, FALSE);
}

