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





#include <qstring.h>
//Added by qt3to4:
#include <Q3StrList>

#include "Logging/QsLog.h"

#include "mystr.h"
char WrapperStr::returnableNullPtr[1] = { 0 };
QByteArray WrapperStr::ba[20];
int WrapperStr::arrayRotate = 0;
bool operator==(const WrapperStr & s1, const char * s2)
{
    return s1.wrappedString == QString(QLatin1String(s2));
}
bool operator==(const char * s1, const WrapperStr & s2)
{
    return s2.wrappedString == QString(QLatin1String(s1));
}
bool operator==(const WrapperStr & s1, const QString & s2)
{
    return s1.wrappedString == s2;
}
bool operator==(const WrapperStr & s1, const WrapperStr & s2)
{
    return s1.wrappedString == s2.wrappedString;
}

bool operator==(const QString & s1, const WrapperStr & s2)
{
    return s1 == s2.wrappedString ;
}

bool operator!=(const WrapperStr & s1, const char * s2)
{
    return s1.wrappedString != QString(QLatin1String(s2));
}
bool operator!=(const char * s1, const WrapperStr & s2)
{
    return QString(QLatin1String(s1)) != s2.wrappedString ;
}
bool operator!=(const WrapperStr & s1, const QString & s2)
{
    return s1.wrappedString == s2;
}

bool operator !=(const WrapperStr &s1, const WrapperStr &s2)
{
    return s1.wrappedString != s2.wrappedString;
}


bool operator!=(const QString & s1, const WrapperStr & s2)
{
    return s1 != s2.wrappedString ;
}


WrapperStr operator+(const WrapperStr & s1, const char * s2)
{
//    QLOG_INFO() << Q_FUNC_INFO;
//    QLOG_INFO() << s1.wrappedString << " " << QString(QLatin1String(s2))<< Q_FUNC_INFO;
    return s1.wrappedString + QString(QLatin1String(s2));
}

WrapperStr operator+(const char * s1, const WrapperStr & s2)
{

//    QLOG_INFO() << Q_FUNC_INFO;
//    QLOG_INFO() << s2.wrappedString << " " << QString(QLatin1String(s1));
    return QString(QLatin1String(s1)) + s2.wrappedString ;
}
WrapperStr operator+(const WrapperStr & s1, const QString & s2)
{
//    QLOG_INFO() << Q_FUNC_INFO;
//    QLOG_INFO() << s1.wrappedString << " " << s2 << Q_FUNC_INFO;
    return s1.wrappedString + s2;
}
WrapperStr operator+(const WrapperStr & s1, const WrapperStr & s2)
{
//    QLOG_INFO() << Q_FUNC_INFO;
//    QLOG_INFO() << s1.wrappedString << " " << s2 << Q_FUNC_INFO;
    return s1.wrappedString + s2.wrappedString;
}
WrapperStr operator+(const QString & s1, const WrapperStr & s2)
{
//    QLOG_INFO() << Q_FUNC_INFO;
//    QLOG_INFO() << s1 << " " << s2.wrappedString << Q_FUNC_INFO;
    return s1 + s2.wrappedString ;
}

QTextStream & operator<<(QTextStream & ds, const WrapperStr &str)
{
    //QLOG_INFO() << "Piping: " + str.wrappedString;
    //ds << WrapperStr(str.wrappedString.toStdString().c_str());
    ds << QTextCodec::codecForLocale()->toUnicode(str.operator const char *());
    return ds;
}
//
bool neq(const WrapperStr & s1, const WrapperStr & s2)
{
    const char * p1 = (s1.isNull()) ? "" : (const char *) s1;
    const char * p2 = (s2.isNull()) ? "" : (const char *) s2;

    for (;;) {
        while (*p1 == '\r') p1 += 1;

        while (*p2 == '\r') p2 += 1;

        if (*p1 == 0)
            return (*p2 != 0);

        if (*p1 != *p2)
            return TRUE;

        p1 += 1;
        p2 += 1;
    }
}
