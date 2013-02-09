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

// fstream is bugged under Windows
#include <stdio.h>
#include <qstring.h>
#include <q3asciidict.h>
//Added by qt3to4:
#include "misc/mystr.h"

class LexContext
{
    friend class Lex;
private:
    char * pointer;
    QString comments;
    QString description;
    unsigned line_number;

    char * read_word_pointer;
    QString read_word_comments;
    QString read_word_description;
    unsigned read_word_line_number;
};

class Lex
{
private:
    static Q3AsciiDict<char> _defines;
    static QString _filename;
    static char * _buffer;
    static LexContext _context;
    static LexContext _mark;

    static int get();
    static int peek();
    static void unget();

    static void goes_to_word_beginning();
    static void complete_template(QString & result);
    static WrapperStr manage_operator(QString  & result, int c, bool oper);
    static WrapperStr read_string();
    static WrapperStr read_character();
    static WrapperStr read_array_dim();
    static void bypass_template();
    static void bypass_pp();
    static void bypass_cpp_comment();
    static void bypass_c_comment();
    static char bypass_operator(int c, bool oper);
    static void bypass_string();
    static void bypass_character();
    static void bypass_array_dim();
    static bool start_template(int c);

public:
    static void defines(const WrapperStr & f);
    static WrapperStr read_word(bool in_expr = FALSE);
    static char read_word_bis(bool set_context, bool in_expr);
    static void unread_word();
    static WrapperStr get_comments(WrapperStr & co);
    static WrapperStr get_comments();
    static WrapperStr get_description(WrapperStr & co);
    static WrapperStr get_description();
    static void clear_comments();
    static void finish_line();
    static bool open(const QString &);
    static void close();
    static const QString & filename();
    static unsigned line_number();
    static bool identifierp(const char *, bool strictp);
    static bool star(const char *);
    static void mark();
    static WrapperStr region();
    static void come_back();
    static const LexContext & get_context();
    static void set_context(const LexContext & context);
    static void syntax_error(WrapperStr = 0);
    static void warn(WrapperStr = 0);
    static void premature_eof();
    static void error_near(WrapperStr);
    static WrapperStr quote(WrapperStr);
    static WrapperStr complete_template_type(WrapperStr id);
    static WrapperStr normalize(const WrapperStr & s);
    static WrapperStr read_list_elt();
    static bool finish_template(WrapperStr &);
    static WrapperStr simplify_comment(WrapperStr &);
};

bool neq(const WrapperStr & s1, const WrapperStr & s2);
bool nequal(const WrapperStr & s1, const WrapperStr & s2);

#endif
