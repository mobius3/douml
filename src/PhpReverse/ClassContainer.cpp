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

#include "ClassContainer.h"
#include "UmlClass.h"
#include "Class.h"
#include "Lex.h"
//Added by qt3to4:
#include "misc/mystr.h"

ClassContainer::~ClassContainer()
{
}

bool ClassContainer::read_type(UmlTypeSpec & typespec, Class ** cl)
{
    WrapperStr s = Lex::read_word();

    if (s.isEmpty()) {
        Lex::premature_eof();
        return FALSE;
    }

    compute_type(s, typespec, cl);

    return TRUE;
}

// don't produce error

bool ClassContainer::bypass_type(WrapperStr s)
{
    if (s.isEmpty() && (s = Lex::read_word()).isEmpty())
        return FALSE;

    for (;;) {
        s = Lex::read_word();

        if (s != "<")
            break;

        do {
            int level = 0;

            for (;;) {
                s = Lex::read_word();

                if (s == ",") {
                    if (level == 0)
                        break;
                }
                else if (s == ">") {
                    if (level-- == 0)
                        break;
                }
                else if (s == "]")
                    level -= 1;
                else if ((s == "<") || (s == "["))
                    level += 1;
                else if (s.isEmpty())
                    return FALSE;
            }
        }
        while (s == ",");

        s = Lex::read_word();

        if (s.isEmpty() || (*s != '.'))
            break;
    }

    if (! s.isEmpty())
        Lex::unread_word(s);

    return TRUE;
}
