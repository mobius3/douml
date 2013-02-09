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

// lexer written by hand rather than using [f]lex as usual,
// BOUML is also my first development including a source code
// reader where I do not use yacc/bison, to see how it is
// without ...

#ifdef TRACE
#include <iostream>
//Added by qt3to4:
#include "misc/mystr.h"

using namespace std;
#endif

// Because stdio and fstream are bugged under Windows
// concerning fseek and equivalent, I read all the file in a buffer
// and manage it after.
#include <qfile.h>

#include "Lex.h"
#include "JavaCatWindow.h"

// the current context
Lex::Context Lex::context;

// to save/restore the current context
QStack<Lex::Context> Lex::stack;

void Lex::push_context()
{
    //Context * c = new Context;
    Context c = context;

    //*c = context;
    stack.push(c);
}

void Lex::pop_context()
{
    Context c = stack.pop();
    //[lgfreitas] not needed
    //context = *c;
    //delete c;
}

int Lex::get()
{
    return (*context.pointer == 0) ? EOF : *context.pointer++;
}

int Lex::peek()
{
    return (*context.pointer == 0) ? EOF : *context.pointer;
}

void Lex::unget()
{
    context.pointer -= 1;
}

static WrapperStr Separators = " \t\f\n&~\"#{'(-|`)[]=}%*<>?,;/:!@";

const QString & Lex::filename()
{
    return context.filename;
}

unsigned Lex::line_number()
{
    return context.line_number;
}

bool Lex::open(const QString & f)
{
#ifdef TRACE
    QLOG_INFO() << "Lex::open(" << f << ")\n";
#endif

    context.filename = f;
    context.line_number = 1;
    context.comments = "";
    context.description = "";
    context.reread = "";
    context.mark = 0;

    QFile in(f);
    unsigned sz;

    if (!in.open(QIODevice::ReadOnly) ||
        ((context.buffer = new char[(sz = in.size()) + 1]) == 0))
        return FALSE;

    unsigned offset = 0;

    do offset += in.readBlock(context.buffer + offset, sz - offset);

    while (offset != sz);

    context.pointer = context.buffer;
    context.buffer[sz] = 0;

    // remove \r
    char * p1 = strchr(context.buffer, '\r');

    if (p1 != 0) {
        char * p2 = p1 + 1;
        char c;

        while ((c = *p2++) != 0) {
            if (c != '\r')
                *p1++ = c;
        }

        *p1 = 0;
    }

    return TRUE;
}

void Lex::close()
{
#ifdef TRACE
    QLOG_INFO() << "Lex::close()\n";
#endif
    delete [] context.buffer;
}

void Lex::unread_word(const char * s)
{
    context.reread = s;
}

void Lex::complete_template(QString & result)
{
    // template
    unsigned level = 1;
    char * pointer = context.pointer;

    result += '<';

    for (;;) {
        switch (read_word_bis(TRUE)) {
        case 0:
            return;

        case '<':
            level += 1;
            break;

        case '>':
            if (--level == 0) {
                char c = *context.pointer;

                *context.pointer = 0;
                result += pointer;
                *context.pointer = c;
                return;
            }

        default:
            break;
        }
    }
}

void Lex::bypass_template()
{
    // template
    unsigned level = 1;

    for (;;) {
        switch (read_word_bis(TRUE)) {
        case 0:
            return;

        case '<':
            level += 1;
            break;

        case '>':
            if (--level == 0)
                return;

        default:
            break;
        }
    }
}

void Lex::bypass_cpp_comment()
{
    get();	// second '/'

    if (! context.comments.isEmpty())
        context.comments += '\n';

    context.description += (! context.description.isEmpty())
                           ? "\n//" :  "//";

    int c;
    char * p = context.pointer;

    for (;;) {
        c = get();

        if (c == EOF) {
            context.comments += p;
            context.description += p;
            return;
        }

        if (c == '\n') {
            context.line_number += 1;
            context.pointer[-1] = 0;
            context.comments += p;
            context.description += p;
            context.pointer[-1] = '\n';
            return;
        }
    }
}

// '/' read, '*' only peek

void Lex::bypass_c_comment()
{
    while (*context.pointer == '*')
        context.pointer += 1;

    if ((*context.pointer == '/') && (context.pointer[-2] != '/')) {
        // /**/ or /***/ etc ...
        context.pointer += 1;
        return;
    }

    if (! context.comments.isEmpty())
        context.comments += '\n';

    context.description += (! context.description.isEmpty())
                           ? "\n/*" :  "/*";

    char * p = context.pointer;	// start of the comment on the line

    for (;;) {
        int c = get();

        switch (c) {
        case EOF:
            return;

        case '\n':
            context.line_number += 1;

            if ((p != 0) && (context.pointer != (p + 1))) {
                // non empty line
                c = *context.pointer;
                *context.pointer = 0;
                context.comments += p;
                context.description += p;
                *context.pointer = c;
            }
            else {
                context.comments += c;
                context.description += c;
            }

            p = 0;
            break;

        case '*':
            if (peek() == '/') {
                if ((p != 0) && (context.pointer != (p + 1))) {
                    // non empty line
                    context.pointer[-1] = 0;
                    context.comments += p;
                    context.pointer[-1] = '*';
                    c = context.pointer[1];
                    context.pointer[1] = 0;
                    context.description += p;
                    context.pointer[1] = c;
                }

                get();	// '/'
                return;
            }

            if (p == 0) {
                if (peek() == ' ')
                    get();

                p = context.pointer;
            }

            break;

        case ' ':
        case '\t':
            break;

        default:
            if (p == 0)
                p = context.pointer - 1;
        }
    }
}

WrapperStr Lex::manage_operator(QString & result, int c)
{
    result += c;

    int next = peek();

    switch (c) {
    case '!':
    case '%':
    case '*':
    case '/':
    case '=':
    case '^':
        if (next == '=')
            result += get();

        break;

    case '<':
    case '>':
        if (next == '=')
            result += get();
        else if (next == c) {
            result += get();

            if (peek() == '=')
                result += get();
        }

        break;

    case '-':
    case '&':
    case '+':
    case '|':
        if ((next == '=') || (next == c))
            result += get();

        break;
    }

#ifdef TRACE
    QLOG_INFO() << "retourne '" << result << "'\n";
#endif
    return WrapperStr(result.toAscii().constData());
}

char Lex::bypass_operator(int c)
{
    int next = peek();

    switch (c) {
    case '!':
    case '%':
    case '*':
    case '/':
    case '=':
    case '^':
        if (next == '=') {
            get();
            return '!'; // to not be = when ==
        }

        return (char) c;

    case '<':
    case '>':
        if (next == '=')
            get();
        else if (next == c) {
            get();

            if (peek() == '=')
                get();
        }
        else
            return (char) c;

        return '!'; // to not be < or > if << >> <= or >=

    case '-':
    case '&':
    case '+':
    case '|':
        if ((next == '=') || (next == c))
            get();

        return (char) c;

    default:
        return (char) c;
    }
}

WrapperStr Lex::read_string()
{
    QString result = "\"";;

    for (;;) {
        int c = get();

        switch (c) {
        case EOF:
            return 0;

        case '\\':
            c = get();

            if (c == '\n')
                context.line_number += 1;

            result += '\\';
            result += c;
            break;

        case '"':
            return WrapperStr((result += c).toAscii().constData());

        default:
            result += c;
        }
    }
}

void Lex::bypass_string()
{
    for (;;) {
        int c = get();

        switch (c) {
        case EOF:
            return;

        case '\\':
            c = get();

            if (c == '\n')
                context.line_number += 1;

            break;

        case '"':
            return;

        default:
            break;
        }
    }
}

WrapperStr Lex::read_character()
{
    WrapperStr result = "'";

    for (;;) {
        int c = get();

        switch (c) {
        case EOF:
            return 0;

        case '\'':
            return WrapperStr(result += c);

        case '\\':
            result += c;
            result += get();
            break;

        default:
            result += c;
        }
    }
}

void Lex::bypass_character()
{
    for (;;) {
        switch (get()) {
        case EOF:
            return;

        case '\'':
            return;

        case '\\':
            get();
            break;

        default:
            break;
        }
    }
}

WrapperStr Lex::read_array_dim()
{
    WrapperStr result = "[";
    char * pointer = context.pointer;

    for (;;) {
        switch (read_word_bis()) {
        case 0:
            result = 0;
            return result;

        case ']': {
            char c = *context.pointer;

            *context.pointer = 0;
            result += pointer;
            *context.pointer = c;

#ifdef TRACE
            QLOG_INFO() << "retourne '" << result << "'\n";
#endif
            return result;
        }

        default:
            break;
        }
    }
}

void Lex::bypass_array_dim()
{
    for (;;) {
        switch (read_word_bis()) {
        case 0:
            return;

        case ']':
            return;

        default:
            break;
        }
    }
}

// read all sequential annotations

WrapperStr Lex::read_annotation()
{
    char * p1 = context.pointer - 1;	// '@' was read

    for (;;) {
        if (read_word_bis() == 0)
            // eof
            return p1;

        char * p2 = context.pointer;
        char c = read_word_bis();

        if (c == '(') {
            int level = 1;

            for (;;) {
                c = read_word_bis();

                if (c == 0)
                    // eof
                    return p1;
                else if (c == '(')
                    level += 1;
                else if ((c == ')') && (--level == 0))
                    break;
            }

            p2 = context.pointer;
            c = read_word_bis();
        }

        if (c == 0)
            return p1;
        else if (c == '@') {
            c = *context.pointer;
            *context.pointer = 0;

            WrapperStr result = p1;

            *context.pointer = c;
            return result;
        }
        else  {
            context.pointer = p2;
            c = *p2;
            *p2 = 0;

            WrapperStr result = p1;

            *p2 = c;
            return result;
        }
    }
}

void Lex::bypass_annotation()
{
    // '@' was read

    for (;;) {
        if (read_word_bis() == 0)
            // eof
            return;

        char * p2 = context.pointer;
        char c = read_word_bis();

        if (c == '(') {
            int level = 1;

            for (;;) {
                c = read_word_bis();

                if (c == 0)
                    // eof
                    return;
                else if (c == '(')
                    level += 1;
                else if ((c == ')') && (--level == 0))
                    break;
            }

            p2 = context.pointer;
            c = read_word_bis();
        }

        if ((c != 0) && (c != '@'))
            context.pointer = p2;

        return;
    }
}

WrapperStr Lex::read_word(bool in_templ)
{
    QString result;

    if (!context.reread.isEmpty()) {
        result = context.reread;

        if (in_templ && (result == ">>")) {
            // >> read as > because unlike C++ not have to write "T<..X<..> >"
            context.reread = result.mid(1);
            result = result.left(1);
        }
        else
            context.reread = QString();
    }
    else {
        for (;;) {
            int c = get();

#ifdef TRACE
            QLOG_INFO() << "deja \"" << result << "\", '" << ((char) c) << "'\n";
#endif

            if (c == EOF)
                break;
            else if (Separators.find(c) == -1)
                result += c;
            else if (! result.isEmpty()) {
                unget();
                break;
            }
            else {
                switch (c) {
                case '"':
                    return read_string();

                case '[':
                    return read_array_dim();

                case '\'':
                    return read_character();

                case '/':
                    switch (peek()) {
                    case '/':
                        bypass_cpp_comment();
                        break;

                    case '*':
                        bypass_c_comment();
                        break;

                    case '=':
                        get();
#ifdef TRACE
                        QLOG_INFO() << "retourne '/='\n";
#endif
                        return "/=";

                    default:
#ifdef TRACE
                        QLOG_INFO() << "retourne '/'\n";
#endif
                        return "/";
                    }

                    break;

                case '\n':
                    context.line_number += 1;
                    break;

                case '@':
                    return read_annotation();

                case '>':
                    if (in_templ && (peek() == '>')) {
                        // >> read as > because unlike C++ not have to write "T<..X<..> >"
                        get();

                        if (peek() != '=') {
                            unget();
#ifdef TRACE
                            QLOG_INFO() << "retourne '>'\n";
#endif
                            return ">";
                        }

                        unget();
                    }

                    // no break
                default:
                    if (c > ' ')
                        return manage_operator(result, c);

                    break;
                }
            }
        }
    }

#ifdef TRACE
    QLOG_INFO() << "retourne '" << result << "'\n";
#endif
    return WrapperStr(result.toAscii().constData());
}

char Lex::read_word_bis(bool in_templ)
{
    char result = 0;

    if (!context.reread.isEmpty()) {
        if (in_templ && (context.reread == ">>")) {
            // >> read as > because unlike C++ not have to write "T<..X<..> >"
            context.reread = context.reread.mid(1);
            result = '>';
        }
        else {
            result = context.reread.latin1()[0];
            context.reread = QString();
        }
    }
    else {
        for (;;) {
            int c = get();

#ifdef TRACE
            QLOG_INFO() << "deja \"" << result << "\", '" << ((char) c) << "'\n";
#endif

            if (c == EOF)
                break;
            else if (Separators.find(c) == -1) {
                if (result == 0)
                    result = c;
            }
            else if (result != 0) {
                unget();
                break;
            }
            else {
                switch (c) {
                case '"':
                    bypass_string();
#ifdef TRACE
                    QLOG_INFO() << "retourne '" << (char) c << "'\n";
#endif
                    return (char) c;

                case '[':
                    bypass_array_dim();
#ifdef TRACE
                    QLOG_INFO() << "retourne '!' (array dim)\n";
#endif
                    return '!';	// to not be [

                case '\'':
                    bypass_character();
#ifdef TRACE
                    QLOG_INFO() << "retourne ' (char)\n";
#endif
                    return (char) c;

                case '/':
                    switch (peek()) {
                    case '/':
                        bypass_cpp_comment();
                        break;

                    case '*':
                        bypass_c_comment();
                        break;

                    case '=':
                        get();
#ifdef TRACE
                        QLOG_INFO() << "retourne '/' (/=)\n";
#endif
                        return (char) c;

                    default:
#ifdef TRACE
                        QLOG_INFO() << "retourne '/'\n";
#endif
                        return (char) c;
                    }

                    break;

                case '\n':
                    context.line_number += 1;
                    break;

                case '@':
                    bypass_annotation();
#ifdef TRACE
                    QLOG_INFO() << "retourne '@' (annotation)\n";
#endif
                    return (char) c;

                case '>':
                    if (in_templ && (peek() == '>')) {
                        // >> read as > because unlike C++ not have to write "T<..X<..> >"
                        get();

                        if (peek() != '=') {
                            unget();
#ifdef TRACE
                            QLOG_INFO() << "retourne '>'\n";
#endif
                            return '>';
                        }

                        unget();
                    }

                    // no break
                default:
                    if (c > ' ')
                        return bypass_operator(c);

                    break;
                }
            }
        }
    }

#ifdef TRACE
    QLOG_INFO() << "retourne '" << result << "'\n";
#endif
    return result;
}

void Lex::finish_line()
{
    for (;;) {
        int c = get();

        switch (c) {
        case '/':
            switch (peek()) {
            case '/':
                bypass_cpp_comment();
                return;

            case '*':
                bypass_c_comment();
                continue;
            }

            // no break
        default:
            unget();
            return;

        case '\n':
            context.line_number += 1;

            // no break
        case EOF:
            return;

        case ' ':
        case '\t':
            break;
        }
    }
}

WrapperStr Lex::get_comments()
{
    WrapperStr result = WrapperStr(context.comments.toAscii().constData());

    context.comments = QString();
    return result;
}

WrapperStr Lex::get_comments(WrapperStr & co)
{
    WrapperStr result = WrapperStr(context.comments.toAscii().constData());

    context.comments = QString();

    return (co.isEmpty())
           ? result
           : co += "\n" + result;
}

WrapperStr Lex::get_description()
{
    WrapperStr result = WrapperStr(context.description.toAscii().constData());

    context.description = QString();
    return result;
}

WrapperStr Lex::get_description(WrapperStr & co)
{
    WrapperStr result = WrapperStr(context.description.toAscii().constData());

    context.description = QString();

    return (co.isEmpty())
           ? result
           : co += "\n" + result;
}

void Lex::clear_comments()
{
    context.comments = QString();
}

bool Lex::identifierp(const char * s)
{
    return (Separators.find(*s) == -1);
}

void Lex::mark()
{
    context.mark = context.pointer;
}

WrapperStr Lex::region()
{
    char c = *context.pointer;

    *context.pointer = 0;

    WrapperStr result = context.mark;

    *context.pointer = c;

    return result;
}

//

void Lex::syntax_error(WrapperStr s)
{
    JavaCatWindow::trace(WrapperStr("<font face=helvetica>syntax error in <i> ")
                         + WrapperStr(context.filename.toAscii().constData()) + "</i> line " +
                         WrapperStr().setNum(context.line_number) + " <b>"
                         + s + "</b></font><br>");

#ifdef TRACE
    QLOG_INFO() << "ERROR IN " << context.filename
                << " LINE " << context.line_number << " : " << s << '\n';
#endif
#ifdef ROUNDTRIP
    throw 0;
#endif
}

void Lex::premature_eof()
{
    JavaCatWindow::trace(WrapperStr("<font face=helvetica>syntax error in <i> ")
                         + WrapperStr(context.filename.toAscii().constData()) + "</i> line " +
                         WrapperStr().setNum(context.line_number) +
                         " <b>premature eof</b></font><br>");

#ifdef TRACE
    QLOG_INFO() << "SYNTAX ERROR IN " << context.filename
                << " LINE " << context.line_number << " : premature eof\n";
#endif
#ifdef ROUNDTRIP
    throw 0;
#endif
}

void Lex::error_near(WrapperStr s, const char * m)
{
    JavaCatWindow::trace(WrapperStr("<font face=helvetica>syntax error in <i> ")
                         + WrapperStr(context.filename.toAscii().constData()) + "</i> line " +
                         WrapperStr().setNum(context.line_number) + " <b>near <font color =\"red\">"
                         + quote(s) + "</font></b>" + m + "</font><br>");

#ifdef TRACE
    QLOG_INFO() << "SYNTAX ERROR IN " << context.filename
                << " LINE " << context.line_number << " : near '" << s << "'\n";
#endif
#ifdef ROUNDTRIP
    throw 0;
#endif
}

// allows a string to be written as it is by an html writer

WrapperStr Lex::quote(WrapperStr s)
{
    WrapperStr result;
    const char * p = s;

    for (;;) {
        switch (*p) {
        case 0:
            return result;

        case '<':
            result += "&lt;";
            break;

        case '>':
            result += "&gt;";
            break;

        case '&':
            result += "&amp;";
            break;

        default:
            result += *p;
        }

        p += 1;
    }
}

// remove first and last line in comment if non significant
WrapperStr Lex::simplify_comment(WrapperStr & comment)
{
    if (comment.isEmpty())
        return comment;

    const char * s = comment;
    const char * p = s;

    for (;;) {
        switch (*p) {
        case 0:
            return comment;

        case ' ':
        case '\t':
            p += 1;
            break;

        case '\n':
            comment.remove(0, p - s + 1);

            if (comment.isEmpty())
                return comment;

            s = comment;

            // no break
        default:
            p = s + comment.length() - 1;

            while (p != s) {
                switch (*p) {
                case ' ':
                case '\t':
                    p -= 1;
                    break;

                case '\n':
                    comment.resize(p - s + 1);

                    // no break
                default:
                    return comment;
                }
            }

            if (*p == '\n')
                comment = "";

            return comment;
        }
    }
}

// don't produce error

bool Lex::bypass_type(WrapperStr s)
{
    if (s.isEmpty() && (read_word_bis() == 0))
        return FALSE;

    for (;;) {
        s = read_word();

        if (s != "<")
            break;

        char c;

        do {
            int level = 0;

            for (;;) {
                c = read_word_bis(TRUE);

                if (c == ',') {
                    if (level == 0)
                        break;
                }
                else if (c == '>') {
                    if (level-- == 0)
                        break;
                }
                else if (c == '<')
                    level += 1;
                else if (c == 0)
                    return FALSE;
            }
        }
        while (c == ',');

        s = read_word();

        if (s.isEmpty() || (*s != '.'))
            break;
    }

    if (! s.isEmpty())
        unread_word(s);

    return TRUE;
}

// to compare strings bypassing \r


// White space means the decimal ASCII codes 9, 10, 11, 12, 13 and 32.
inline bool is_white_space(char c)
{
    return ((c == ' ') || ((c >= '\t') && (c <= '\r')));
}

bool nequal(const WrapperStr & s1, const WrapperStr & s2)
{
    // don't take into account first and last white spaces (like a stripWhiteSpace())
    const char * p1 = (s1.isNull()) ? "" : (const char *) s1;
    const char * p2 = (s2.isNull()) ? "" : (const char *) s2;
    const char * e1 = p1 + s1.length();
    const char * e2 = p2 + s2.length();

    while ((p1 != e1) && is_white_space(p1[0]))
        p1 += 1;

    while ((p2 != e2) && is_white_space(p2[0]))
        p2 += 1;

    while ((e1 != p1) && is_white_space(e1[-1]))
        e1 -= 1;

    while ((e2 != p2) && is_white_space(e2[-1]))
        e2 -= 1;

    for (;;) {
        if (p1 >= e1)
            return (p2 < e2);

        if (*p1 != *p2)
            return TRUE;

        while (*++p1 == '\r') ;

        while (*++p2 == '\r') ;
    }
}
