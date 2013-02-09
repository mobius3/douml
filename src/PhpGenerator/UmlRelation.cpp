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

#include "UmlRelation.h"
#include "UmlClass.h"
#include "UmlSettings.h"
#include "PhpSettings.h"
#include "util.h"
#include "UmlCom.h"

void UmlRelation::generate_extends(const char *& sep, QTextStream & f,
                                   const WrapperStr & cl_stereotype)
{
    switch (relationKind()) {
    default:
        return;

    case aGeneralisation:
    case aRealization:
        if (phpDecl().isEmpty())
            return;

        UmlClass * role_type = roleType();
        const WrapperStr & other_stereotype = role_type->php_stereotype();

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
            if (cl_stereotype == "union") {
                write_trace_header();
                UmlCom::trace(WrapperStr("&nbsp;&nbsp;&nbsp;&nbsp;<font color=\"red\"><b>an <i>")
                              + cl_stereotype + "</i> cannot extends</b></font><br>");
                incr_warning();
                return;
            }
            else if ((other_stereotype == "union") ||
                     (other_stereotype == "enum")) {
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

        const char * p = phpDecl();

        while (*p) {
            if (!strncmp(p, "${type}", 7)) {
                role_type->write(f);
                p += 7;
            }
            else if (*p == '@')
                manage_alias(p, f);
            else
                f << *p++;
        }
    }
}

void UmlRelation::generate_implements(const char *& sep, QTextStream & f,
                                      const WrapperStr & cl_stereotype)
{
    switch (relationKind()) {
    default:
        return;

    case aGeneralisation:
    case aRealization:
        if (phpDecl().isEmpty())
            return;

        UmlClass * role_type = roleType();
        const WrapperStr & other_stereotype = role_type->php_stereotype();

        if (other_stereotype == "interface") {
            if (cl_stereotype == "union") {
                write_trace_header();
                UmlCom::trace(WrapperStr("&nbsp;&nbsp;&nbsp;&nbsp;<font color=\"red\"><b>an <i>")
                              + cl_stereotype + "</i> cannot inherits</b></font><br>");
                incr_warning();
            }
            else {
                f << sep;
                sep = ", ";

                const char * p = phpDecl();

                while (*p) {
                    if (!strncmp(p, "${type}", 7)) {
                        role_type->write(f);
                        p += 7;
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

void UmlRelation::generate(QTextStream & f, const WrapperStr &,
                           WrapperStr indent, int &)
{
    switch (relationKind()) {
    case aDependency:
    case aGeneralisation:
    case aRealization:
        break;

    default:
        if (!phpDecl().isEmpty()) {
            const char * p = phpDecl();
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
                    manage_comment(p, pp, PhpSettings::isGenerateJavadocStyleComment());
                else if (!strncmp(p, "${description}", 14))
                    manage_description(p, pp);
                else if (!strncmp(p, "${visibility}", 13)) {
                    p += 13;
                    generate_visibility(f);
                }
                else if (!strncmp(p, "${static}", 9)) {
                    p += 9;

                    if (isClassMember())
                        f << "static ";
                }
                else if (!strncmp(p, "${type}", 7)) {
                    p += 7;
                    roleType()->write(f);
                }
                else if (!strncmp(p, "${name}", 7)) {
                    p += 7;

                    if (!isReadOnly())
                        f << "$";

                    f << roleName();
                }
                else if (!strncmp(p, "${inverse_name}", 15)) {
                    p += 15;

                    switch (relationKind()) {
                    case anAssociation:
                    case anAggregation:
                    case anAggregationByValue: {
                        UmlRelation * inverse = side(side(TRUE) != this);

                        if (!inverse->isReadOnly())
                            f << "$";

                        f << inverse->roleName();
                    }

                    default:
                        break;
                    }
                }
                else if (!strncmp(p, "${var}", 6)) {
                    p += 6;

                    if (!isReadOnly() &&
                        !isClassMember() &&
                        (visibility() == PackageVisibility))
                        f << "var ";
                }
                else if (!strncmp(p, "${value}", 8)) {
                    if (!defaultValue().isEmpty()) {
                        if (need_equal(p, defaultValue()))
                            f << " = ";

                        f << defaultValue();
                    }

                    p += 8;
                }
                else if (!strncmp(p, "${const}", 8)) {
                    p += 8;

                    if (isReadOnly())
                        f << "const ";
                }
                else
                    f << *p++;
            }

            f << '\n';
        }
    }
}

void UmlRelation::generate_require_onces(QTextStream & f, WrapperStr & made)
{
    if (!phpDecl().isEmpty())
        roleType()->generate_require_onces(f, made, ((UmlClass *) parent())->assocArtifact());
}
