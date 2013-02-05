#include "misc/codec.h"
#include "misc/mystr.h"
#include "misc/strutil.h"
static QTextCodec * Codec = 0;

bool hasCodec()
{
    return Codec != 0;
}

QString codec()
{
    if (Codec != 0) {
        QString na = Codec->name();
        int pos = 0;

        while ((pos = na.find(' ', pos)) != -1)
            na.replace(pos, 1, "_");

        if (QTextCodec::codecForName(na) == Codec)
            return na;
    }

    return "";
}

void set_codec(QString s)
{
    if (s.isEmpty())
        Codec = 0;
    else
        Codec = QTextCodec::codecForName(s);
}

QString toUnicode(const char * str)
{
    if (Codec == 0)
        return str;
    else if ((str == 0) || (*str == 0))
        return QString();
    else
        return Codec->toUnicode(str);
}

void latinize(QString & s)
{
    unsigned i = s.length();

    while (i != 0) {
        QChar c = s.at(--i);

        if (c.latin1() == 0) {
            if (c.unicode() == 8217)
                // special case for the pseudo ' returned by microsoft editors
                c = '\'';
            else
                c = ' ';

            s.replace(i, 1, &c, 1);
        }
    }
}

WrapperStr fromUnicode(const QString & s)
{
    if (Codec == 0) {
        QString str = s;

        latinize(str);
        QByteArray ba = str.toLatin1();
        const char * retTemp = ba.data();
        return retTemp; //[lgfreitas] that nasty trick
    }
    else if (s.isEmpty())	// fromUnicode crash if null string
        return "";
    else
        return WrapperStr(Codec->fromUnicode(s));
}

//

void remove_crlf(char * s)
{
    int len = strlen(s);

    if (len != 0) {
        if (s[len - 1] == '\n')
            s[--len] = 0;

        if ((len != 0) && (s[len - 1] == '\r'))
            s[len - 1] = 0;
    }
}

