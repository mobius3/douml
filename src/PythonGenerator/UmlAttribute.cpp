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
#include "PythonSettings.h"
#include "UmlClass.h"
#include "UmlCom.h"
#include "util.h"

void UmlAttribute::generate_imports(QTextStream & f, WrapperStr & made)
{
    if (!pythonDecl().isEmpty())
        type().generate_import(f, ((UmlClass *) parent())->assocArtifact(),
                               FALSE, made);
}

void UmlAttribute::generate(QTextStream & f, const WrapperStr & st,
                            WrapperStr indent, BooL & indent_needed,
                            int & enum_item_rank, const WrapperStr & self)
{
    if (self.isEmpty() != isClassMember())
        return;

    const char * p = pythonDecl();

    if ((p == 0) || (*p == 0))
        return;

    const char * pp = 0;

    for (;;) {
        if (*p == 0) {
            if (pp == 0)
                break;

            // comment management done
            p = pp;

            if (*p == 0)
                break;

            pp = 0;
        }

        if (*p != '$') {
            if (*p == '@')
                manage_alias(p, f, indent, indent_needed);
            else {
                if (indent_needed)
                    f << indent;

                indent_needed = (*p == '\n');

                f << *p++;
            }
        }
        else if (!strncmp(p, "${comment}", 10))
            manage_comment(p, pp);
        else if (!strncmp(p, "${description}", 14))
            manage_description(p, pp);
        else if (!strncmp(p, "${name}", 7)) {
            if (indent_needed) {
                indent_needed = FALSE;
                f << indent;
            }

            p += 7;
            f << name();
        }
        else if (!strncmp(p, "${value}", 8)) {
            if (indent_needed) {
                indent_needed = FALSE;
                f << indent;
            }

            const WrapperStr & v = defaultValue();

            if (!v.isEmpty()) {
                if (need_equal(p, v))
                    f << " = ";

                f << v;
            }
            else if (st == "enum")
                f << " = " << enum_item_rank;
            else if (need_equal(p, "None"))
                f << " = None";
            else
                f << "None";

            p += 8;
        }
        else if (!strncmp(p, "${self}", 7)) {
            p += 7;

            if (! self.isEmpty()) {
                if (indent_needed) {
                    indent_needed = FALSE;
                    f << indent;
                }

                f << self;
            }
        }
        else if (!strncmp(p, "${stereotype}", 13)) {
            if (indent_needed) {
                indent_needed = FALSE;
                f << indent;
            }

            p += 13;
            f << PythonSettings::relationAttributeStereotype(stereotype());
        }
        else if (!strncmp(p, "${type}", 7)) {
            if (indent_needed) {
                indent_needed = FALSE;
                f << indent;
            }

            p += 7;
            UmlClass::write(f, type());
        }
        else {
            // strange
            if (indent_needed) {
                indent_needed = FALSE;
                f << indent;
            }

            f << *p++;
        }
    }

    if (! indent_needed) {
        f << '\n';
        indent_needed = TRUE;
    }

    enum_item_rank += 1;
}
