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

#include "UmlClassItem.h"
#include "UmlCom.h"
#include "UmlSettings.h"
//Added by qt3to4:
#include "misc/mystr.h"

void UmlClassItem::remove_comments(WrapperStr & s)
{
    int index1 = 0;

    while ((index1 = s.find('/', index1)) != -1) {
        int index2;

        switch (((const char *) s)[index1 + 1]) {
        case '/':
            if ((index2 = s.find('\n', index1 + 2)) != -1)
                s.remove(index1, index2 - index1 + 1);
            else
                s.truncate(index1);

            break;

        case '*':
            if ((index2 = s.find("*/", index1 + 2)) != -1)
                s.replace(index1, index2 - index1 + 1, " ");
            else
                s.truncate(index1);

            break;

        default:
            index1 += 1;
        }
    }
}

void UmlClassItem::remove_preprocessor(WrapperStr & s)
{
    int index = 0;

    while ((index = s.find('#', index)) != -1) {
        // remove all up to the end of line
        int index2 = index + 1;
        int index3;

        while ((index3 = s.find('\n', index2)) != -1) {
            // manage multi lines #define
            if (((const char *) s)[index3 - 1] != '\\')
                break;
            else
                index2 = index3 + 1;
        }

        // the \n is still here to hava a separator
        if (index3 == -1)
            s.truncate(index);
        else
            s.remove(index, index3 - index);
    }
}

void UmlClassItem::remove_arrays(WrapperStr & s)
{
    int index1 = 0;

    while ((index1 = s.find('[', index1)) != -1) {
        int index2 = index1 = s.find(']', index1 + 1);

        if (index2 == -1) {
            s.truncate(index1);
            return;
        }
        else
            s.replace(index1, index2 - index1 + 1, " ");
    }
}

