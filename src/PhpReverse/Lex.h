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
    typedef struct sContext {
      QString filename;
      unsigned line_number;
      char * buffer;
      char * pointer;
      QString reread;
      QString comments;
      QString description;
      char * mark;
	  //[lgfreitas] operator= added so copy happens the way we expect.
	  sContext & operator=(const sContext & src) {
		memcpy(this, &src, sizeof(*this));
		return *this;
	  }
    } Context;
  
  private:
    static int get();
    static int peek();
    static void unget();
    
    static void bypass_cpp_comment();
    static void bypass_c_comment();
    static Q3CString manage_operator(QString  & result, int c);  
    static Q3CString read_string();     
    static Q3CString read_character();    
    static Q3CString read_array_dim();  
    static char bypass_operator(int c);  
    static void bypass_string();     
    static void bypass_character();    
    static void bypass_array_dim();  
    
    static Context context;
    static QStack<Context> stack;
    
  public:
    static Q3CString read_word();
    static char read_word_bis();
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
    static void error_near(Q3CString);
    static Q3CString quote(Q3CString);
    static void push_context();
    static void pop_context();
};

Q3CString value_of(Q3CString s, Q3CString k, int & index);
Q3CString value_of(Q3CString s, Q3CString k, int & index,
		  Q3CString & next, int & index2);

#endif
