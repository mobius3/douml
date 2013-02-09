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
#include "PhpCatWindow.h"

// the current context
Lex::Context Lex::context;

// to save/restore the current context
QStack<Lex::Context> Lex::stack;

void Lex::push_context()
{
    Context c = context;
    stack.push(c);
}

void Lex::pop_context()
{
    Context c = stack.pop();
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

static WrapperStr Separators = " \r\t\f\n&~\"#{'(-|`)[]=}%*<>?,;/:!";

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

    context.buffer[sz] = 0;
    context.pointer = context.buffer;

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

// '//' or '#' read
void Lex::bypass_cpp_comment()
{
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

        default:
            result += c;
        }
    }
}

void Lex::bypass_character()
{
    for (;;) {
        int c = get();

        switch (c) {
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
        case ']':
            return;

        default:
            break;
        }
    }
}

WrapperStr Lex::read_word()
{
    QString result;

    if (!context.reread.isEmpty()) {
        result = context.reread;
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
                case '#':
                    bypass_cpp_comment();
                    break;

                case '"':
                    return read_string();

                case '[':
                    return read_array_dim();

                case '\'':
                    return read_character();

                case '/':
                    switch (peek()) {
                    case '/':
                        get();	// second '/'
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

                default:
                    if (c > ' ')
                        return manage_operator(result, c);

                    break;
                }
            }
        }
    }

#ifdef TRACE

    if (result.isEmpty())
        QLOG_INFO() << "EOF\n";
    else
        QLOG_INFO() << "retourne '" << result << "'\n";

#endif
    return WrapperStr(result.toAscii().constData());
}

char Lex::read_word_bis()
{
    if (!context.reread.isEmpty()) {
        char result = context.reread[0].latin1();

        context.reread = QString();
        return result;
    }
    else {
        char result = 0;
        int c;

        for (;;) {
            c = get();

#ifdef TRACE
            QLOG_INFO() << "deja \"" << result << "\", '" << ((char) c) << "'\n";
#endif

            if (c == EOF)
                return result;
            else if (Separators.find(c) == -1) {
                if (result == 0)
                    result = (char) c;
            }
            else if (result != 0) {
                unget();
                return result;
            }
            else {
                switch (c) {
                case '#':
                    bypass_cpp_comment();
                    break;

                case '"':
                    bypass_string();
                    return (char) c;

                case '[':
                    bypass_array_dim();
                    return '!';	// to not be [

                case '\'':
                    bypass_character();
                    return (char) c;

                case '/':
                    switch (peek()) {
                    case '/':
                        get();	// second '/'
                        bypass_cpp_comment();
                        break;

                    case '*':
                        bypass_c_comment();
                        break;

                    case '=':
                        get();
                        return (char) c;

                    default:
                        return (char) c;
                    }

                    break;

                case '\n':
                    context.line_number += 1;
                    break;

                default:
                    if (c > ' ')
                        return bypass_operator(c);
                }
            }
        }
    }
}

void Lex::finish_line()
{
    for (;;) {
        int c = get();

        switch (c) {
        case '#':
            bypass_cpp_comment();
            break;

        case '/':
            switch (peek()) {
            case '/':
                get();	// second '/'
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
    PhpCatWindow::trace(WrapperStr("<font face=helvetica>syntax error in <i> ")
                        + WrapperStr(context.filename.toAscii().constData()) + "</i> line " +
                        WrapperStr().setNum(context.line_number) + " <b>"
                        + s + "</b></font><br>");

#ifdef TRACE
    QLOG_INFO() << "ERROR IN " << context.filename
                << " LINE " << context.line_number << " : " << s << '\n';
#endif
}

void Lex::premature_eof()
{
    PhpCatWindow::trace(WrapperStr("<font face=helvetica>syntax error in <i> ")
                        + WrapperStr(context.filename.toAscii().constData()) + "</i> line " +
                        WrapperStr().setNum(context.line_number) +
                        " <b>premature eof</b></font><br>");

#ifdef TRACE
    QLOG_INFO() << "SYNTAX ERROR IN " << context.filename
                << " LINE " << context.line_number << " : premature eof\n";
#endif
}

void Lex::error_near(WrapperStr s)
{
    PhpCatWindow::trace(WrapperStr("<font face=helvetica>syntax error in <i> ")
                        + WrapperStr(context.filename.toAscii().constData()) + "</i> line " +
                        WrapperStr().setNum(context.line_number) + " <b>near <font color =\"red\">"
                        + quote(s) + "</font></b></font><br>");

#ifdef TRACE
    QLOG_INFO() << "SYNTAX ERROR IN " << context.filename
                << " LINE " << context.line_number << " : near '" << s << "'\n";
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

//

static WrapperStr get_next_word(WrapperStr s, int & index, int & index2)
{
    WrapperStr result;
    const char * p = ((const char *)  s) + index;

    for (;;) {
        // bypass spaces before word
        switch (*p) {
        case ' ':
        case '\t':
            index += 1;
            p += 1;
            break;

        case '\r':
        case '\n':
        case 0:
            index2 = index;
            return result;

        default: {
            index2 = index;

            for (;;) {
                // search for end of word
                switch (*p) {
                case ' ':
                case '\t':
                case '\r':
                case '\n':
                case 0:
                    if (index2 != index)
                        result = s.mid(index, index2 - index);

                    return result;

                default:
                    index2 += 1;
                    p += 1;
                    break;
                }
            }
        }
        }
    }
}

WrapperStr value_of(WrapperStr s, WrapperStr k, int & index)
{
    index = s.find(k);

    if (index == -1) {
        WrapperStr result;

        return result;
    }
    else {
        int index2;

        index += k.length();
        return get_next_word(s, index, index2);
    }
}

WrapperStr value_of(WrapperStr s, WrapperStr k, int & index,
                   WrapperStr & next, int & index2)
{
    WrapperStr result;

    index = s.find(k, index);

    if (index != -1) {
        index += k.length();
        result = get_next_word(s, index, index2);

        if (! result.isEmpty()) {
            int index3;

            next = get_next_word(s, index2, index3);
        }
    }

    return result;
}

