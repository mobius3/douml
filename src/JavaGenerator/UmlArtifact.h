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

#ifndef UMLARTIFACT_H
#define UMLARTIFACT_H

#include <q3asciidict.h>
//Added by qt3to4:
#include "misc/mystr.h"

#include "UmlBaseArtifact.h"

class UmlPackage;

// This class manages 'artifacts'
// You can modify it as you want (except the constructor)

class UmlArtifact : public UmlBaseArtifact
{
private:
    bool managed;
    Q3AsciiDict<UmlArtifact> * imports;

    static UmlArtifact * current;
    static UmlPackage * package_of_generated_artifact;

    static bool must_be_saved(const char * path, const char * new_contains);

    void generate_text();

public:
    UmlArtifact(void * id, const WrapperStr & n)
        : UmlBaseArtifact(id, n), managed(FALSE), imports(0) {};

    virtual void generate();

    void imported(const WrapperStr & s);
    bool is_imported(const WrapperStr & s);
    bool is_imported(WrapperStr path, WrapperStr class_name);

    static UmlArtifact * generated_one();
    static UmlPackage * generation_package();
};

#endif
