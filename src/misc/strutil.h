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

#ifndef STRUTIL_H
#define STRUTIL_H

#include "qstring.h"
//Added by qt3to4:
#include "misc/mystr.h"
#include "mystr.h"
#include "codec.h"

extern bool manage_comment(QString comment, const char *& p,
                           const char *& pp, bool javadoc);
extern bool manage_description(QString comment, const char *& p,
                               const char *& pp);
extern bool manage_python_comment(QString comment, const char *& p,
                                  const char *& pp);
extern bool manage_python_description(QString comment, const char *& p,
                                      const char *& pp);
extern void manage_python_docstring(QString comment, const char *& p, const char *& pp,
                                    BooL & indent_needed, QString & indent,
                                    QString & saved_indent);
extern QString capitalize(const QString & s);
extern QString true_name(const QString & name, const QString & decl);
extern bool is_char_of_name(char c);
extern QString extract_name(QString s);
extern QString quote(QString s);
extern void remove_comments(WrapperStr & s);
extern void remove_comments(QString & s);
extern void remove_python_comments(WrapperStr & s);
extern void remove_python_comments(QString & s);
extern void remove_preprocessor(WrapperStr & s);
extern void remove_preprocessor(QString & s);
extern QString java_multiplicity(QString m);
extern bool need_equal(const char * p, QString v, bool cpp);
extern bool need_equal(const char * p, const char * v, bool cpp);


extern void remove_crlf(char *);

extern bool is_referenced(const char * s, int id, const char * kc, const char * kr);

#endif
