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

#ifndef LEX_H
#define LEX_H

#include <qstack.h>
//Added by qt3to4:
#include "misc/mystr.h"

// fstream is bugged under Windows
#include <stdio.h>
#include <qstring.h>

class Lex
{
public:
    typedef struct {
        QString filename;
        unsigned line_number;
        char * buffer;
        char * pointer;
        QString reread;
        QString comments;
        QString description;
        char * mark;
    } Context;

private:
    static int get();
    static int peek();
    static void unget();

    static void complete_template(QString & result);
    static WrapperStr manage_operator(QString  & result, int c);
    static WrapperStr read_string();
    static WrapperStr read_character();
    static WrapperStr read_array_dim();
    static WrapperStr read_annotation();
    static void bypass_template();
    static void bypass_cpp_comment();
    static void bypass_c_comment();
    static char bypass_operator(int c);
    static void bypass_string();
    static void bypass_character();
    static void bypass_annotation();
    static void bypass_array_dim();

    static Context context;
    static QStack<Context> stack;

public:
    static WrapperStr read_word(bool in_templ = FALSE);
    static char read_word_bis(bool in_templ = FALSE);
    static void unread_word(const char * s);
    static WrapperStr get_comments();
    static WrapperStr get_comments(WrapperStr & co);
    static WrapperStr get_description();
    static WrapperStr get_description(WrapperStr & co);
    static void clear_comments();
    static void finish_line();
    static bool open(const QString &);
    static void close();
    static const QString & filename();
    static unsigned line_number();
    static bool identifierp(const char *);
    static void mark();
    static WrapperStr region();
    static void syntax_error(WrapperStr = 0);
    static void premature_eof();
    static void error_near(WrapperStr, const char * m = "");
    static WrapperStr quote(WrapperStr);
    static void push_context();
    static void pop_context();
    static WrapperStr simplify_comment(WrapperStr &);
    static bool bypass_type(WrapperStr s);
};

bool neq(const WrapperStr & s1, const WrapperStr & s2);
bool nequal(const WrapperStr & s1, const WrapperStr & s2);

#endif
