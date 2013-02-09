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





#include "InfoData.h"
#include "myio.h"
#include "ToolCom.h"
//Added by qt3to4:
#include <QTextStream>

void InfoData::save(QTextStream & st, const char * s1, const char * s2) const
{
    indent(+1);

    if (!first.isEmpty()) {
        nl_indent(st);
        st << s1 << " ";
        save_string(first, st);
    }

    if (!second.isEmpty()) {
        nl_indent(st);
        st << s2 << " ";
        save_string(second, st);
    }

    indent(-1);
}

void InfoData::read(char *& st, char *& k, const char * s1, const char * s2)
{
    if (!strcmp(k, s1)) {
        first = read_string(st);
        k = read_keyword(st);
    }

    if (!strcmp(k, s2)) {
        second = read_string(st);
        k = read_keyword(st);
    }
}

void InfoData::send_def(ToolCom * com)
{
    com->write_string(first);
    com->write_string(second);
}
