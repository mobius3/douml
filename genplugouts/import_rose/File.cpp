
#include "File.h"

#include <stdlib.h>
#include <qinputdialog.h>
#include <q3dict.h>
#include <qfileinfo.h>
#include <qdir.h>
//Added by qt3to4:
#include <Q3CString>
#include "UmlCom.h"

File::File(QString s, QString here)
{
    for (;;)  {
        int index = 0;

        while ((index = s.find('\\', index)) != -1)
            s.replace(index++, 1, "/");

        int index0;

        if ((index0 = s.find('$')) == -1)
            break;

        if ((index = s.find('/', index0 + 1)) == -1)
            index = s.length();

        static Q3Dict<char> alias;

        QString var = s.left(index);
        const char * val = alias[var];

        if (val == 0) {
            if ((val = getenv(var.mid(1))) == 0) {
                QString v = QInputDialog::getText("Unknown environment variable",
                                                  var.mid(1) + " : ");

                if (v.isEmpty())
                    throw 0;

                val = strdup((const char *) v);
            }
            else
                val = strdup(val);

            alias.insert(var, val);
        }

        if (*val == '&') {
            QFileInfo fi(here);

            s.replace(index0, index - index0, fi.dirPath(TRUE));
        }
        else
            s.replace(index0, index - index0, val);
    }

    setName(QDir::cleanDirPath(s));

    unread_k = -1;

}

bool File::open(int m)
{
    line_number = 1;

    //[jasa] Possible QFile problem here.
    //return QFile::open(m);//[jasa] original line.
    return QFile::open((QIODevice::OpenModeFlag)m);//[jasa] fix ambiguous enum/int call
}

int File::read(Q3CString & s)
{
    if (unread_k != -1) {
        s = unread_s;

        int r = unread_k;

        unread_k = -1;
        return r;
    }

    s = "";

    for (;;) {
        int c = getch();

        switch (c) {
        case '(':
        case ')':
            s += c;	// s = c does not work
            return c;

        case -1:
            s = "<eof>";
            return c;

        case '\n':
            line_number += 1;

            // no break
        case ' ':
        case '\r':
        case '\t':
            break;

        case '"':
            return readString(s);

        case '|':
            return readMLString(s);

        default:
            s += c;	// s = c does not work
            return readAtom(s);
        }
    }
}

void File::read(const char * e)
{
    Q3CString s;

    if (read(s) == -1)
        eof();

    if (s != e)
        syntaxError(s, e);
}

void File::unread(int k, const Q3CString & s)
{
    unread_k = k;
    unread_s = s;
}

Q3CString File::context()
{
    Q3CString s;

    return Q3CString(name().toAscii()) + " line " + s.setNum(line_number);//[jasa] QString to Q3CString conversion
}

int File::readString(Q3CString & s)
{
    int c;

    while ((c = getch()) != '"') {
        if (c == -1) {
            UmlCom::trace("<br>end of file reading a string in " + context());
            throw 0;
        }

        s += ((c == '\\') ? getch() : c);
    }

    return STRING;
}

int File::readMLString(Q3CString & s)
{
    for (;;) {
        int c = getch();

        switch (c) {
        case -1:
            return STRING;

        case '\n':
            line_number += 1;
            c = getch();

            if (c == '\r')
                c = getch();

            switch (c) {
            case -1:
                return STRING;

            case '|':
                s += '\n';
                break;

            default:
                ungetch(c);
                return STRING;
            }

        case '\r':
            break;

        default:
            s += ((c == '\\') ? getch() : c);
        }
    }
}

int File::readAtom(Q3CString & s)
{
    for (;;) {
        int c = getch();

        switch (c) {
        case '(':
        case ')':
        case '"':
        case '\n':
            ungetch(c);

            // no break !
        case -1:
        case ' ':
        case '\r':
        case '\t':
            return ATOM;

        default:
            s += c;
        }
    }
}

void File::syntaxError(const Q3CString s)
{
    UmlCom::trace("<br>syntax error near '" + s + "' in " + context());
    throw 0;
}

void File::syntaxError(const Q3CString s, const Q3CString e)
{
    Q3CString msg = "<br>'" + e + "' expected rather than '" + s + "' in " + context();

    UmlCom::trace(msg);
    throw 0;
}

void File::skipBlock()
{
    int lvl = 1;
    Q3CString s;

    for (;;) {
        switch (read(s)) {
        case -1:
            return;

        case '(':
            lvl += 1;
            break;

        case ')':
            if (--lvl == 0)
                return;

        default:
            break;
        }
    }

}

void File::skipNextForm()
{
    Q3CString s;

    switch (read(s)) {
    case ')':
        ungetch(')');
        break;

    case '(':
        skipBlock();
        break;

    default:
        break;
    }

}

void File::eof()
{
    UmlCom::trace("<br>premature end of file in " + name());
}

void File::rewind()
{
    line_number = 1;
    at(0);
    unread_k = -1;
}

aVisibility File::readVisibility()
{
    Q3CString s;

    if (read(s) == STRING) {
        if (s == "Private")
            return PrivateVisibility;

        if (s == "Protected")
            return ProtectedVisibility;

        if (s == "Public")
            return PublicVisibility;
    }

    //syntaxError(s, "a visibility");
    return PublicVisibility;
}

bool File::readBool()
{
    Q3CString s;

    if (read(s) == ATOM) {
        if (s == "TRUE")
            return TRUE;

        if (s == "FALSE")
            return FALSE;
    }

    syntaxError(s, "TRUE or FALSE");
    return FALSE;	// to avoid warning
}

Language File::readLanguage()
{
    Q3CString s;

    if (read(s) != STRING)
        syntaxError(s, "a language");

    if (s == "C++")
        return Cplusplus;

    if (s == "ANSI C++")
        return AnsiCplusplus;

    if (s == "VC++")
        return VCplusplus;

    if (s == "CORBA")
        return Corba;

    if (s == "Oracle8")
        return Oracle8;

    if (s == "Java")
        return Java;

    return None;
}

int File::readDefinitionBeginning(Q3CString & s, Q3CString & id, Q3CString & ste, Q3CString & doc, Q3Dict<Q3CString> & prop)
{
    for (;;) {
        int k = read(s);

        switch (k) {
        case -1:
            eof();
            throw 0;

        case ')':
            return k;

        case '(':
            skipBlock();

            // no break !
        default:
            continue;

        case ATOM:
            break;
        }

        if (s == "quid") {
            if (read(id) != STRING)
                syntaxError(id, "quid value");
        }
        else if (s == "attributes") {
            readProperties(prop);
        }
        else if (s == "documentation") {
            if (read(doc) != STRING)
                syntaxError(doc, "the documentation");
        }
        else if (s == "stereotype") {
            if (read(ste) != STRING)
                syntaxError(ste, "the stereotype");
        }
        else
            return k;
    }
}

void File::readProperties(Q3Dict<Q3CString> & d)
{
    d.setAutoDelete(TRUE);

    read("(");
    read("list");
    read("Attribute_Set");

    for (;;) {
        Q3CString s;

        switch (read(s)) {
        case ')':
            return;

        case '(':
            read("object");
            read("Attribute");
            read("tool");

            if (read(s) != STRING)
                syntaxError(s, "the tool");

            read("name");
            {
                Q3CString s2;

                if (read(s2) != STRING)
                    syntaxError(s2, "the name");

                s += "/" + s2;

                read("value");

                switch (read(s2)) {
                case '(':
                    if ((read(s2) == ATOM) && (s2 == "value")) {
                        read("Text");

                        if (read(s2) != STRING)
                            syntaxError(s2, "the value");

                        read(")");
                    }
                    else
                        skipBlock();

                    // no break !
                case STRING:
                case ATOM:
                    d.insert(s, new Q3CString(s2));
                    break;

                default:
                    syntaxError(s, "the value");
                }
            }

            read(")");
            break;

        default:
            syntaxError(s);
        }
    }

}

