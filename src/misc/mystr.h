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

#ifndef MY_STR_H
#define MY_STR_H

#include <q3strlist.h>
#include <QString>
#include <Q3CString>
#include "Logging/QsLog.h"


class WrapperStr
{
public:
    // this serves as a keeper for temporary array that got destroyed otherwise
    // messing the output of operator const char*
    static  QByteArray ba[20];
    static int arrayRotate;

    WrapperStr() {}
    ~WrapperStr() {}
    WrapperStr(const WrapperStr & other) {
        *this = other;
    }
    WrapperStr(const QString & other) {
        this->wrappedString = other;
    }
    WrapperStr(const QByteArray & other) {
        this->wrappedString = QString(other);
    }
    WrapperStr(const char* other) {
        this->wrappedString = QString(other);
    }
    //QString get(){return s;}
    WrapperStr & operator=(const Q3CString & cstr) {
        this->wrappedString = QByteArray(cstr);
        return *this;
    }
    bool isEmpty() const {
        return this->wrappedString.isEmpty();
    }
    unsigned int length() const {
        return this->wrappedString.length();
    }
    int find(const char * toFind, int index = 0) const {
        return wrappedString.indexOf(QString(QLatin1String(toFind)), index);
    }
//    int find(int c, int index = 0) const {
//        return wrappedString.indexOf(QString::number(c) , index);
//    }

    WrapperStr & operator=(const WrapperStr & other) {
        this->wrappedString = other.wrappedString;
        return *this;
    }
//    WrapperStr & operator=(const WrapperStr & other) {
//        this->wrappedString = other.wrappedString;
//        return *this;
//    }
    WrapperStr & operator=(const char * c) {
        this->wrappedString = QString(QLatin1String(c));
        return *this;
    }
    WrapperStr & operator+=(const char * c) {
        this->wrappedString += QString(QLatin1String(c));
        return *this;
    }
    WrapperStr & operator+=(const QString& str) {
        this->wrappedString += str;
        return *this;
    }
    WrapperStr & operator+=(const WrapperStr& str) {
        this->wrappedString += str.wrappedString;
        return *this;
    }
//    WrapperStr & operator+=(const char* str) {
//        this->wrappedString += QString(str);
//        return *this;
//    }
    WrapperStr & operator+=(char c) {
        this->wrappedString += QString(c);
        return *this;
    }
    WrapperStr & operator=(const QString & other) {
        this->wrappedString = other;
        return *this;
    }

    operator const char * () const
    {
        return wrappedString;
    }
    operator WrapperStr() const {
         //QLOG_INFO()() << Q_FUNC_INFO;
         //QLOG_INFO()() << this->wrappedString.toLatin1();
         return this->wrappedString.toLatin1();
     }

    operator QString() const {
        return this->wrappedString;
    }

    void sprintf(QString proto, unsigned val)
    {
        proto.replace("%u", QString::number(val));
        this->wrappedString = proto;
    }

    friend bool operator==(const WrapperStr & s1, const char * s2);
    friend bool operator==(const char * s1, const WrapperStr & s2);
    friend bool operator==(const WrapperStr & s1, const QString & s2);
    friend bool operator==(const WrapperStr & s1, const WrapperStr & s2);
    friend bool operator==(const QString & s1, const WrapperStr & s2);

    friend bool operator!=(const WrapperStr & s1, const char * s2);
    friend bool operator!=(const char * s1, const WrapperStr & s2);
    friend bool operator!=(const WrapperStr & s1, const QString & s2);
    friend bool operator!=(const WrapperStr & s1, const WrapperStr & s2);
    friend bool operator!=(const QString & s1, const WrapperStr & s2);

    friend WrapperStr operator+(const WrapperStr & s1, const char * s2);
    friend WrapperStr operator+(const WrapperStr & s1, const WrapperStr & s2);
    //friend QString operator+(const WrapperStr & s1, const char * s2);
    friend WrapperStr operator+(const char * s1, const WrapperStr & s2);
    friend WrapperStr operator+(const WrapperStr & s1, const QString & s2);
    friend WrapperStr operator+(const QString & s1, const WrapperStr & s2);
    friend QTextStream & operator<<(QTextStream & ds, const WrapperStr &str);

    void assign(const char * c, int len) {
        Q_UNUSED(len);
        this->wrappedString = QString(QLatin1String(c));
    }

    WrapperStr& replace(int pos, int len, const char* c)
    {
        wrappedString = wrappedString.replace(pos, len, c);
        return *this;
    }
    WrapperStr& insert(int pos, const char* c)
    {
        wrappedString  = wrappedString.insert(pos, c);
        return *this;
    }
    WrapperStr left(int len) const
    {
        return wrappedString.left(len);
    }
    WrapperStr right(int len) const
    {
        return wrappedString.right(len);
    }
    const char* data() const
    {
        return this->operator const char *();
    }
    WrapperStr stripWhiteSpace() const
    {
        return wrappedString.trimmed();
    }
    WrapperStr simplifyWhiteSpace() const
    {
        return wrappedString.simplified();
    }

    WrapperStr& remove(int pos, int len)
    {
        wrappedString = wrappedString.remove(pos, len);
        return *this;
    }
    WrapperStr mid(int pos, int len = -1) const
    {
        return wrappedString.mid(pos, len);
    }
    WrapperStr& setNum(int num)
    {
        wrappedString = wrappedString.setNum(num);
        return *this;
    }
    void truncate(int pos)
    {
        wrappedString = wrappedString.left(pos);
    }
    QString upper() const
    {
        return wrappedString.toUpper();
    }
    QString lower() const
    {
        return wrappedString.toLower();
    }

    QString& GetInternalRef()
    {
        return wrappedString;
    }
    QString at(int pos) const
    {
        return wrappedString.at(pos);
    }
    int find(QChar c, int from = 0) const
    {
        return wrappedString.toAscii().find(c, from);
    }
    WrapperStr & append ( const char * str )
    {
        wrappedString += QString(str);
        return *this;
    }
    WrapperStr & append (QString str )
    {
        wrappedString += str;
        return *this;
    }
    WrapperStr & append (const WrapperStr& str )
    {
        wrappedString += str.wrappedString;
        return *this;
    }
    bool isNull() const
    {
        return wrappedString.isNull();
    }
    void resize(int size)
    {
        wrappedString.resize(size);
    }
    QCharRef operator[](int i)
    {
        return wrappedString[i];
    }
    //void assign(QString(), int len){this->s = QString();}

protected:
    static char returnableNullPtr[1];

    QString wrappedString;
};

bool operator==(const WrapperStr & s1, const char * s2);
bool operator==(const char * s1, const WrapperStr & s2);
bool operator==(const WrapperStr & s1, const QString & s2);
bool operator==(const WrapperStr & s1, const WrapperStr & s2);
bool operator==(const QString & s1, const WrapperStr & s2);
bool operator!=(const WrapperStr & s1, const char * s2);
bool operator!=(const char * s1, const WrapperStr & s2);
bool operator!=(const WrapperStr & s1, const QString & s2);
bool operator!=(const WrapperStr & s1, const WrapperStr & s2);
bool operator!=(const QString & s1, const WrapperStr & s2);
WrapperStr operator+(const WrapperStr & s1, const char * s2);
WrapperStr operator+(const WrapperStr & s1, const WrapperStr& s2);
WrapperStr operator+(const char * s1, const WrapperStr & s2);
WrapperStr operator+(const WrapperStr & s1, const QString & s2);
WrapperStr operator+(const QString & s1, const WrapperStr & s2);
QTextStream & operator<<(QTextStream & ds, const WrapperStr &str);
bool neq(const WrapperStr & s1, const WrapperStr & s2);

#endif
