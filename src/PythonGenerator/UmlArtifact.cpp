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

#include <stdio.h>
#include <QTextStream>
//Added by qt3to4:
#include "misc/mystr.h"
#include <QTextStream>

#include "UmlArtifact.h"
#include "UmlPackage.h"
#include "UmlOperation.h"
#include "UmlClass.h"
#include "UmlNcRelation.h"
#include "PythonSettings.h"
#include "UmlCom.h"
#include "util.h"

UmlPackage * UmlArtifact::package_of_generated_artifact;
UmlArtifact * UmlArtifact::current;
WrapperStr UmlArtifact::imports;

void UmlArtifact::generate_imports(QTextStream & f, WrapperStr & made)
{
    Q3PtrVector<UmlItem> ch = children();
    unsigned index;
    const unsigned sup = ch.size();

    for (index = 0; index != sup; index += 1) {
        UmlNcRelation * r = dynamic_cast<UmlNcRelation *>(ch[index]);

        if ((r != 0) &&
            (r->relationKind() == aDependency) &&
            (r->target()->kind() == anArtifact)) {
            UmlArtifact * other_art = (UmlArtifact *) r->target();
            WrapperStr s_art =
                ((UmlPackage *) other_art->parent()->parent())->pythonPackage();

            if (! s_art.isEmpty())
                s_art += "." + other_art->name();
            else
                s_art = other_art->name();

            WrapperStr s = r->stereotype();

            if (s == "import")
                s = "import " + s_art;
            else if (s == "from")
                s = "from " + s_art + " import *";
            else
                return;

            if (made.find(s) == -1) {
                made += s + "\n";
                f << s << '\n';
            }
        }
    }
}

void UmlArtifact::generate()
{
    if (! managed) {
        managed = TRUE;

        if (stereotype() == "text") {
            generate_text();
            return;
        }
        else if (stereotype() != "source")
            return;

        package_of_generated_artifact = package();
        current = this;

        const WrapperStr filedef = pythonSource();

        if (filedef.isEmpty())
            return;

        const WrapperStr & name = this->name();
        WrapperStr path = package_of_generated_artifact->file_path(name);

        UmlCom::message(name);

        if (verbose())
            UmlCom::trace(WrapperStr("<hr><font face=helvetica>Generate code for <i> ")
                          + name + "</i> in " + path + "</i></font><br>");
        else
            set_trace_header(WrapperStr("<font face=helvetica>Generate code for <i> ")
                             + name + "</i> in " + path + "</i></font><br>");

        // get bodies if preserve
        const Q3PtrVector<UmlClass> & cls = associatedClasses();

        if (preserve())
            UmlOperation::read_bodies(path);

        // generate file

        WrapperStr indent;
        BooL indent_needed;
        unsigned n = cls.count();
        unsigned index;
        QByteArray file;
        // note : QTextStream(FILE *) does not work under windows
        QTextStream f(&file);
        const char * p = filedef;
        const char * pp = 0;

        for (;;) {
            if (*p == 0) {
                if (pp == 0)
                    break;

                // comment management done
                p = pp;
                pp = 0;

                if (*p == 0)
                    break;
            }

            if (*p == '@') {
                indent_needed = FALSE;
                manage_alias(p, f, indent, indent_needed);
            }
            else if (*p != '$')
                f << *p++;
            else if (!strncmp(p, "${comment}", 10))
                manage_comment(p, pp);
            else if (!strncmp(p, "${description}", 14))
                manage_description(p, pp);
            else if (!strncmp(p, "${name}", 7)) {
                p += 7;
                f << name;
            }
            else if (!strncmp(p, "${Name}", 7)) {
                p += 7;
                f << capitalize(name);
            }
            else if (!strncmp(p, "${NAME}", 7)) {
                p += 7;
                f << name.upper();
            }
            else if (!strncmp(p, "${nAME}", 7)) {
                p += 7;
                f << name.lower();
            }
            else if (!strncmp(p, "${definition}", 13)) {
                indent_needed = TRUE;

                for (index = 0; index != n; index += 1)
                    cls[index]->generate(f, indent, indent_needed);

                p += 13;

                if (*p == '\n')
                    p += 1;
            }
            else if (!strncmp(p, "${import}", 9)) {
                imports = "";
                generate_imports(f, imports);

                for (index = 0; index != n; index += 1)
                    cls[index]->generate_imports(f, imports);

                p += 9;
            }
            else
                f << *p++;
        }

        f << '\000';

        if (must_be_saved(path, file)) {
            write_trace_header();

            FILE * fp;

            if ((fp = fopen((const char *) path, "wb")) == 0) {
                write_trace_header();
                UmlCom::trace(WrapperStr("<font color=\"red\"><b><i> ")
                              + name + "</i> : cannot open <i> "
                              + path + "</i>, edit the <i> generation settings</i> (tab directory) or the <i>"
                              + package_of_generated_artifact->name()
                              + "</i> Python directory specification</b></font><br>");
                incr_error();
            }
            else {
                fputs((const char *) file, fp);
                fclose(fp);
            }
        }
        else if (get_trace_header().isEmpty())
            UmlCom::trace(WrapperStr("<font face=helvetica><i> ")
                          + path + "</i> not modified</font><br>");
    }
}

void UmlArtifact::generate_text()
{
    const WrapperStr srcdef = pythonSource();

    if (srcdef.isEmpty()) {
        if (verbose())
            UmlCom::trace(WrapperStr("<hr><font face=helvetica>artifact <i>")
                          + name() + "</i> has an empty Python definition</font><br>");

        return;
    }

    UmlPackage * pack = package();
    const WrapperStr & name = UmlArtifact::name();
    WrapperStr src_path = pack->text_path(name);

    WrapperStr s = " in <i> " + src_path + "</i>";

    UmlCom::message(name);

    if (verbose())
        UmlCom::trace(WrapperStr("<hr><font face=helvetica>Generate code for <i> ")
                      + name + "</i>" + s + "</font><br>");
    else
        set_trace_header(WrapperStr("<font face=helvetica>Generate code for <i> ")
                         + name + "</i>" + s + "</font><br>");

    if (must_be_saved(src_path, (const char *) srcdef)) {
        write_trace_header();

        FILE * fp_src;

        if ((fp_src = fopen((const char *) src_path, "wb")) == 0) {
            write_trace_header();
            UmlCom::trace(WrapperStr("<font color=\"red\"><b><i> ")
                          + name + " : </i> cannot open <i> "
                          + src_path + "</i>, edit the <i> generation settings</i> (tab directory) or the <i>"
                          + pack->name() + "</i> Python directory specification</b></font><br>");
            incr_error();
        }
        else {
            fputs((const char *) srcdef, fp_src);
            fclose(fp_src);
        }
    }
    else if (get_trace_header().isEmpty())
        UmlCom::trace(WrapperStr("<font face=helvetica><i> ")
                      + src_path + "</i> not modified</font><br>");
}

UmlPackage * UmlArtifact::generation_package()
{
    return package_of_generated_artifact;
}

UmlArtifact * UmlArtifact::generated_one()
{
    return current;
}

const WrapperStr & UmlArtifact::all_imports()
{
    return imports;
}

bool UmlArtifact::must_be_saved(const char * path, const char * new_contains)
{
    FILE * fp = fopen(path, "rb");

    if (fp == 0)
        return TRUE;

    int c;

    while ((c = fgetc(fp)) != EOF) {
        if (((char) c) != *new_contains++) {
            fclose(fp);
            return TRUE;
        }
    }

    fclose(fp);

    return *new_contains != 0;
}
