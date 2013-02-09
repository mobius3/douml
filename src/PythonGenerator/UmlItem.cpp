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

#include "UmlItem.h"

UmlItem::~UmlItem()
{
}

void UmlItem::manage_comment(const char *& p, const char *& pp)
{
    static WrapperStr the_comment;

    p += 10;

    if ((pp != 0) || // comment contains ${comment} !
        description().isEmpty())
        return;

    const char * comment = description();

    the_comment = "#";

    do {
        the_comment += *comment;

        if ((*comment++ == '\n') && *comment)
            the_comment += "#";
    }
    while (*comment);

    switch (*p) {
    case 0:
    case '\n':
        break;

    default:
        the_comment += '\n';
    }

    pp = p;
    p = the_comment;
}

void UmlItem::manage_description(const char *& p, const char *& pp)
{
    static WrapperStr the_comment;

    p += 14;

    the_comment = description();

    if ((pp != 0) || // comment contains ${description} !
        the_comment.isEmpty())
        return;

    pp = p;
    p = the_comment;
}

void UmlItem::manage_docstring(const char *& p, const char *& pp, BooL & indent_needed,
                               WrapperStr & indent, WrapperStr & saved_indent)
{
    static WrapperStr the_comment;

    p += 12;

    the_comment = description();

    if ((pp != 0) || // comment contains ${description} !
        the_comment.isEmpty())
        return;

    int index = 0;

    while ((index = the_comment.find("\"\"\"", index)) != -1) {
        the_comment.insert(index, "\\");
        index += 2;
    }

    if (!indent.isEmpty()) {
        int len = indent.length() + 1;

        index = 0;

        while ((index = the_comment.find('\n', index)) != -1) {
            the_comment.insert(index + 1, (const char *)indent);
            index += len;
        }
    }

    the_comment = "\"\"\"" + the_comment + "\"\"\"\n";

    if (indent_needed) {
        indent_needed = FALSE;
        the_comment = indent + the_comment;
    }

    pp = p;
    p = the_comment;
    saved_indent =  indent;
    indent = "";
}

void UmlItem::manage_alias(const char *& p, QTextStream & ts,
                           WrapperStr indent, BooL & indent_needed)
{
    if (indent_needed) {
        indent_needed = FALSE;
        ts << indent;
    }

    // p starts by '@'
    const char * pclosed;

    if ((p[1] == '{') && ((pclosed = strchr(p + 2, '}')) != 0)) {
        Q3CString key(p + 2, pclosed - p - 1);
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
        ts << *p++;
}

void UmlItem::generate()
{
    // does nothing
}

UmlPackage * UmlItem::package()
{
    return parent()->package();
}
