// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
//
// This file is part of the BOUML Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// e-mail : bouml@free.fr
// home   : http://bouml.free.fr
//
// *************************************************************************

#ifndef LEX_H
#define LEX_H

#include <qstack.h>
//Added by qt3to4:
#include <Q3CString>

// fstream is bugged under Windows
#include <stdio.h>
#include <qstring.h>

class Lex {
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
    static Q3CString manage_operator(QString  & result, int c);  
    static Q3CString read_string();     
    static Q3CString read_character();    
    static Q3CString read_array_dim();  
    static Q3CString read_annotation();
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
    static Q3CString read_word(bool in_templ = FALSE);
    static char read_word_bis(bool in_templ = FALSE);
    static void unread_word(const char * s);
    static Q3CString get_comments();
    static Q3CString get_comments(Q3CString & co);
    static Q3CString get_description();
    static Q3CString get_description(Q3CString & co);
    static void clear_comments();
    static void finish_line();
    static bool open(const QString &);
    static void close();
    static const QString & filename();
    static unsigned line_number();
    static bool identifierp(const char *);
    static void mark();
    static Q3CString region();
    static void syntax_error(Q3CString = 0);
    static void premature_eof();
    static void error_near(Q3CString, const char * m = "");
    static Q3CString quote(Q3CString);
    static void push_context();
    static void pop_context();
    static Q3CString simplify_comment(Q3CString &);
    static bool bypass_type(Q3CString s);
};

bool neq(const Q3CString & s1, const Q3CString & s2);
bool nequal(const Q3CString & s1, const Q3CString & s2);

#endif
