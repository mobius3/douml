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
#include <Q3CString>

#include "UmlItem.h"
#include "misc/codec.h"

UmlItem::~UmlItem()
{
}

bool UmlItem::manage_comment(const char *& p, const char *& pp,
                             bool javadoc)
{
    static QString the_comment;

    p += 10;

    if ((pp != 0) || // comment contains ${comment} !
        description().isEmpty())
        return FALSE;

    const char * comment = description();

    if (javadoc) {
        the_comment = "/**\n * ";

        do {
            the_comment += *comment;

            if ((*comment++ == '\n') && *comment)
                the_comment += " * ";
        }
        while (*comment);

        if (*p != '\n')
            the_comment += (comment[-1] != '\n') ? "\n */\n" : " */\n";
        else
            the_comment += (comment[-1] != '\n') ? "\n */" : " */";
    }
    else {
        the_comment = "//";

        do {
            the_comment += *comment;

            if ((*comment++ == '\n') && *comment)
                the_comment += "//";
        }
        while (*comment);

        switch (*p) {
        case 0:
        case '\n':
            break;

        default:
            the_comment += '\n';
        }
    }

    pp = p;
    p = the_comment;
    return TRUE;
}

bool UmlItem::manage_description(const char *& p, const char *& pp)
{
    static WrapperStr the_comment;

    p += 14;

    if ((pp != 0) || // comment contains ${description} !
        description().isEmpty())
        return FALSE;

    the_comment = description();

    switch (*p)
    {
    case 0:
    case '\n':
        break;

    default:
        the_comment += '\n';
    }

    pp = p;
    p = the_comment;
    return TRUE;
}

void UmlItem::replace_alias(WrapperStr & s)
{
    int index = 0;

    while ((index = s.find("@{", index)) != -1) {
        int index2 = s.find('}', index + 2);

        if (index2 == -1)
            return;

        UmlBaseItem * obj = this;
        WrapperStr key = s.mid(index + 2, index2 - index - 2);
        WrapperStr value;

        for (;;) {
            if (obj->propertyValue(key, value)) {
                s.replace(index, index2 - index + 1, value);
                index += value.length();
                break;
            }
            else if ((obj = obj->parent()) == 0) {
                index = index2 + 1;
                break;
            }
        }
    }
}

void UmlItem::manage_alias(const char *& p, QTextStream & ts)
{
    // p starts by '@'
    const char * pclosed;

    if ((p[1] == '{') && ((pclosed = strchr(p + 2, '}')) != 0)) {
        Q3CString key_(p + 2, pclosed - p - 1);
        WrapperStr key = key_;
        WrapperStr value;
        UmlItem * node = this;

        do {
            if (node->propertyValue(key, value))
                break;

            node = node->parent();
        }
        while (node != 0);

        if (node != 0)
            // find, insert the value
            ts << value;
        else
            // not find, insert the key
            ts << "@{" << key << '}';

        // bypass the key
        p += strlen(key) + 3;
    }
    else
        // bypass '$'
        ts << toLocale(p);
}

void UmlItem::generate()
{
    // does nothing
}

UmlPackage * UmlItem::package()
{
    return parent()->package();
}
