
#include "File.h"

#include <stdlib.h>
#include <qinputdialog.h>

#include <qfileinfo.h>
#include <qdir.h>
//Added by qt3to4:
#include <QByteArray>
#include "UmlCom.h"

File::File(QString s, QString here)
{
    for (;;)  {
        int index = 0;

        while ((index = s.indexOf('\\', index)) != -1)
            s.replace(index++, 1, "/");

        int index0;

        if ((index0 = s.indexOf('$')) == -1)
            break;

        if ((index = s.indexOf('/', index0 + 1)) == -1)
            index = s.length();

        static QHash<QString,char*> alias;

        QString var = s.left(index);
        const char * val = alias[var];

        if (val == 0) {
            if ((val = getenv(var.mid(1).toLatin1().constData())) == 0) {
                QString v = QInputDialog::getText(0,"Unknown environment variable",
                                                  var.mid(1) + " : ");

                if (v.isEmpty())
                    throw 0;

                val = strdup((const char *) v.toLatin1().constData());
            }
            else
                val = strdup(val);

            alias.insert(QString(var), const_cast<char*>(val));
        }

        if (*val == '&') {
            QFileInfo fi(here);

            s.replace(index0, index - index0, fi.path());
        }
        else
            s.replace(index0, index - index0, val);
    }

    setFileName(QDir::cleanPath(s));

    unread_k = -1;

}

bool File::open(OpenMode flags)
{
    line_number = 1;

    return QFile::open(flags);
}

int File::read(QByteArray & s)
{
    if (unread_k != -1) {
        s = unread_s;

        int r = unread_k;

        unread_k = -1;
        return r;
    }

    s = "";

    for (;;) {
        char ch;
        bool retVal = getChar(&ch);
        if(!retVal) //possibly end of file
            ch = -1;
        int c = ch;

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
    QByteArray s;

    if (read(s) == -1)
        eof();

    if (s != e)
        syntaxError(s, e);
}

void File::unread(int k, const QByteArray & s)
{
    unread_k = k;
    unread_s = s;
}

QByteArray File::context()
{
    QByteArray s;

    return QByteArray(fileName().toLatin1()) + " line " + s.setNum(line_number);//[jasa] QString to QByteArray conversion
}

int File::readString(QByteArray & s)
{
    int c;
    char ch;

    while (1) {
        getChar(&ch);
        c = ch;
        if(c  == '"')
            break;
        if (c == -1) {
            UmlCom::trace("<br>end of file reading a string in " + context());
            throw 0;
        }

        if(c == '\\')
        {
            getChar(&ch);
            s += ch;
        }
        else
            s += c;
    }

    return STRING;
}

int File::readMLString(QByteArray & s)
{
    for (;;) {
        char ch;
        getChar(&ch);
        int c = ch;

        switch (c) {
        case -1:
            return STRING;

        case '\n':
            line_number += 1;
            getChar(&ch);
            c = ch;

            if (c == '\r')
            {
                getChar(&ch);
                c = ch;
            }

            switch (c) {
            case -1:
                return STRING;

            case '|':
                s += '\n';
                break;

            default:
                ungetChar(c);
                return STRING;
            }

        case '\r':
            break;

        default:
        {
            //s += ((c == '\\') ? getch() : c);
            if(c == '\\')
            {
                getChar(&ch);
                s += ch;
            }
            else
                s += c;
        }
        }
    }
}

int File::readAtom(QByteArray & s)
{
    for (;;) {
        char ch;
        getChar(&ch);
        int c = ch;

        switch (c) {
        case '(':
        case ')':
        case '"':
        case '\n':
            ungetChar(c);

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

void File::syntaxError(const QByteArray s)
{
    UmlCom::trace("<br>syntax error near '" + s + "' in " + context());
    throw 0;
}

void File::syntaxError(const QByteArray s, const QByteArray e)
{
    QByteArray msg = "<br>'" + e + "' expected rather than '" + s + "' in " + context();

    UmlCom::trace(msg);
    throw 0;
}

void File::skipBlock()
{
    int lvl = 1;
    QByteArray s;

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
    QByteArray s;

    switch (read(s)) {
    case ')':
        ungetChar(')');
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
    UmlCom::trace(QString("<br>premature end of file in " + fileName()).toLatin1().constData());
}

void File::rewind()
{
    line_number = 1;
    seek(0);
    unread_k = -1;
}

aVisibility File::readVisibility()
{
    QByteArray s;

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
    QByteArray s;

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
    QByteArray s;

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

int File::readDefinitionBeginning(QByteArray & s, QByteArray & id, QByteArray & ste, QByteArray & doc, QHash<QByteArray, QByteArray*> & prop)
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

void File::readProperties(QHash<QByteArray, QByteArray*> & d)
{
    //d.setAutoDelete(TRUE);

    read("(");
    read("list");
    read("Attribute_Set");

    for (;;) {
        QByteArray s;

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
                QByteArray s2;

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
                    d.insert(s, new QByteArray(s2));
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

