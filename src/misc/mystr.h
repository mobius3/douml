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

#ifndef MY_STR_H
#define MY_STR_H

// I consider that QString and Q3CString are too memory expensive

#include <q3strlist.h>
#include <QString>
//Added by qt3to4:
#include <Q3CString>
#include "Logging/QsLog.h"
#include "myio.h"
#include "strutil.h"


class WrapperStr
{
  public:
    WrapperStr(){}
    ~WrapperStr(){}
    WrapperStr(const WrapperStr & other)
    {
        QLOG_INFO() << Q_FUNC_INFO;
        *this = other;
    }
    WrapperStr(const QString & other)
    {
        QLOG_INFO() << Q_FUNC_INFO;
        this->s = other;
    }
    //QString get(){return s;}
    bool isEmpty() const
    {

        return this->s.isEmpty();
    }
    unsigned int length() const
    {
        return this->s.length();
    }
    int find(const char * toFind, int index = 0) const
    {
        return s.indexOf(toFind, index);
    }
    int find(int c, int index = 0) const
    {
        return s.indexOf(QString::number(c) , index);
    }

    WrapperStr & operator=(const WrapperStr & other)
    {
        QLOG_INFO() << Q_FUNC_INFO;
        QLOG_INFO() << "Otheris " << other.s << "this is" << this->s;
        this->s = other.s; return *this;
        QLOG_INFO() << "Otheris " << other.s << "this is" << this->s;
    }
    WrapperStr & operator=(const char * c)
    {
        QLOG_INFO() << Q_FUNC_INFO;
        QLOG_INFO() << "Otheris " << c << "this is" << this->s;
        this->s = QString(c);return *this;
        QLOG_INFO() << "Otheris " << c << "this is" << this->s;
    }
    WrapperStr & operator=(const QString &other )
    {
        QLOG_INFO() << Q_FUNC_INFO;
        QLOG_INFO() << "Otheris " << other << "this is" << this->s;
        this->s = s; return *this;
        QLOG_INFO() << "Otheris " << other << "this is" << this->s;

    }
    WrapperStr & operator=(const Q3CString &cstr)
    {
        QLOG_INFO() << Q_FUNC_INFO;
        QLOG_INFO() << cstr.data()<< Q_FUNC_INFO;
        this->s = QByteArray(cstr); return *this;
    }
    operator const char *() const
    {
        QLOG_INFO() << Q_FUNC_INFO;
        QLOG_INFO() << this->s.toLatin1().data();
        return toUnicode(this->s.toLatin1().data());
    }
    operator QString() const
    {
        QLOG_INFO() << Q_FUNC_INFO;
        QLOG_INFO() << this->s;
        return this->s;
    }
    operator Q3CString() const
    {
        QLOG_INFO() << Q_FUNC_INFO;
        QLOG_INFO() << this->s.toLatin1();
        return this->s.toLatin1();
    }

    friend bool operator==(const WrapperStr & s1, const char * s2);
    friend bool operator==(const char * s1, const WrapperStr & s2);
    friend bool operator==(const WrapperStr & s1, const QString & s2);
    friend bool operator==(const QString & s1, const WrapperStr & s2);

    friend bool operator!=(const WrapperStr & s1, const char * s2);
    friend bool operator!=(const char * s1, const WrapperStr & s2);
    friend bool operator!=(const WrapperStr & s1, const QString & s2);
    friend bool operator!=(const QString & s1, const WrapperStr & s2);

    friend QString operator+(const WrapperStr & s1, const char * s2);
    friend QString operator+(const char * s1, const WrapperStr & s2);
    friend QString operator+(const WrapperStr & s1, const QString & s2);
    friend QString operator+(const QString & s1, const WrapperStr & s2);

    void assign(const char *c, int len)
    {
        QLOG_INFO() << Q_FUNC_INFO;
        QLOG_INFO() << QString::fromLatin1(c);
        Q_UNUSED(len); this->s = QString::fromLatin1(c);
    }
    //void assign(QString::null, int len){this->s = QString();}

  protected:

  QString s;
};

bool operator==(const WrapperStr & s1, const char * s2);
bool operator==(const char * s1, const WrapperStr & s2);
bool operator==(const WrapperStr & s1, const QString & s2);
bool operator==(const QString & s1, const WrapperStr & s2);
bool operator!=(const WrapperStr & s1, const char * s2);
bool operator!=(const char * s1, const WrapperStr & s2);
bool operator!=(const WrapperStr & s1, const QString & s2);
bool operator!=(const QString & s1, const WrapperStr & s2);
QString operator+(const WrapperStr & s1, const char * s2);
QString operator+(const char * s1, const WrapperStr & s2);
QString operator+(const WrapperStr & s1, const QString & s2);
QString operator+(const QString & s1, const WrapperStr & s2);



#endif
