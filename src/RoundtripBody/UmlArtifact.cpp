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

#include "UmlArtifact.h"
#include "UmlPackage.h"
#include "UmlClass.h"
#include "UmlOperation.h"
#include "UmlCom.h"
#include "util.h"

void UmlArtifact::roundtrip_cpp()
{
    if (! managed) {
        managed = TRUE;

        if (stereotype() != "source")
            return;

        const WrapperStr hdef = cppHeader();
        const WrapperStr srcdef = cppSource();

        if (hdef.isEmpty() && srcdef.isEmpty())
            return;

        const WrapperStr & name = UmlArtifact::name();
        UmlPackage * pack = package();
        WrapperStr h_path = pack->header_path(name);
        WrapperStr src_path = pack->source_path(name);

        {
            WrapperStr s;

            if (!hdef.isEmpty())
                s = "<i> " + h_path + "</i>";

            if (!srcdef.isEmpty()) {
                if (!hdef.isEmpty())
                    s += " and <i> " + src_path + "</i>";
                else
                    s = "<i> " + src_path + "</i>";
            }

            UmlCom::message(name);

            if (verbose())
                UmlCom::trace(WrapperStr("<hr><font face=helvetica>roundtrip body from")
                              + s + "</font><br>");
            else
                set_trace_header(WrapperStr("<font face=helvetica>roundtrip body from")
                                 + s + "</font><br>");
        }

        UmlOperation::roundtrip(h_path, cppLanguage);
        UmlOperation::roundtrip(src_path, cppLanguage);
    }
}

void UmlArtifact::roundtrip_java()
{
    if (! managed) {
        managed = TRUE;

        if (stereotype() != "source")
            return;

        const WrapperStr srcdef = javaSource();

        if (srcdef.isEmpty())
            return;

        const WrapperStr & name = UmlArtifact::name();
        UmlPackage * pack = package();
        WrapperStr src_path = pack->java_path(name);

        {
            WrapperStr s = " <i> " + src_path + "</i>";

            UmlCom::message(name);

            if (verbose())
                UmlCom::trace(WrapperStr("<hr><font face=helvetica>roundtrip body from")
                              + s + "</font><br>");
            else
                set_trace_header(WrapperStr("<font face=helvetica>roundtrip body from")
                                 + s + "</font><br>");
        }

        UmlOperation::roundtrip(src_path, javaLanguage);
    }
}

void UmlArtifact::roundtrip_php()
{
    if (! managed) {
        managed = TRUE;

        if (stereotype() != "source")
            return;

        const WrapperStr srcdef = phpSource();

        if (srcdef.isEmpty())
            return;

        const WrapperStr & name = UmlArtifact::name();
        UmlPackage * pack = package();
        WrapperStr src_path = pack->php_path(name);

        {
            WrapperStr s = " <i> " + src_path + "</i>";

            UmlCom::message(name);

            if (verbose())
                UmlCom::trace(WrapperStr("<hr><font face=helvetica>roundtrip body from")
                              + s + "</font><br>");
            else
                set_trace_header(WrapperStr("<font face=helvetica>roundtrip body from")
                                 + s + "</font><br>");
        }

        UmlOperation::roundtrip(src_path, phpLanguage);
    }
}

void UmlArtifact::roundtrip_python()
{
    if (! managed) {
        managed = TRUE;

        if (stereotype() != "source")
            return;

        const WrapperStr srcdef = pythonSource();

        if (srcdef.isEmpty())
            return;

        const WrapperStr & name = UmlArtifact::name();
        UmlPackage * pack = package();
        WrapperStr src_path = pack->python_path(name);

        {
            WrapperStr s = " <i> " + src_path + "</i>";

            UmlCom::message(name);

            if (verbose())
                UmlCom::trace(WrapperStr("<hr><font face=helvetica>roundtrip body from")
                              + s + "</font><br>");
            else
                set_trace_header(WrapperStr("<font face=helvetica>roundtrip body from")
                                 + s + "</font><br>");
        }

        UmlOperation::roundtrip(src_path, pythonLanguage);
    }
}
