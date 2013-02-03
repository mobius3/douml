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

// I consider that QString and WrapperStr are too memory expensive

#include <q3strlist.h>
#include <QString>
#include <Q3CString>
//Added by qt3to4:
#include "Logging/QsLog.h"
//#include "myio.h"
//#include "strutil.h"


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
    bool isEmpty() const {
        return this->wrappedString.isEmpty();
    }
    unsigned int length() const {
        return this->wrappedString.length();
    }
    int find(const char * toFind, int index = 0) const {
        return wrappedString.indexOf(QString(QLatin1String(toFind)), index);
    }
    int find(int c, int index = 0) const {
        return wrappedString.indexOf(QString::number(c) , index);
    }

    WrapperStr & operator=(const WrapperStr & other) {
        this->wrappedString = other.wrappedString;
        return *this;
    }
//    WrapperStr & operator=(const WrapperStr & other) {
//        this->wrappedString = other.wrappedString;
//        return *this;
//    }
    WrapperStr & operator=(const Q3CString & cstr) {
        this->wrappedString = QByteArray(cstr);
        return *this;
    }
    WrapperStr & operator=(const char * c) {
        this->wrappedString = QString(QLatin1String(c));
        return *this;
    }
    WrapperStr & operator+=(const char * c) {
        this->wrappedString += QString(QLatin1String(c));
        return *this;
    }
    WrapperStr & operator+=(const WrapperStr& str) {
        this->wrappedString += str.wrappedString;
        return *this;
    }
    WrapperStr & operator+=(const QString& str) {
        this->wrappedString += str;
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

    operator const char * () const {
        if (wrappedString.length() > 0) {
            arrayRotate++;

            if (arrayRotate == 20)
                arrayRotate = 0;

            ba[arrayRotate] = wrappedString.toLatin1();
            const char * retVal = ba[arrayRotate].data();
            return retVal;
        }

        int k = 0;
        k++;
        return returnableNullPtr;
    }
    operator Q3CString() const {
         //QLOG_INFO()() << Q_FUNC_INFO;
         //QLOG_INFO()() << this->wrappedString.toLatin1();
         return this->wrappedString.toLatin1();
     }

    operator QString() const {
        return this->wrappedString;
    }

    QString& GetInternalRef()
    {
        return wrappedString;
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

    void replace(int pos, int len, const char* c)
    {
        wrappedString.replace(pos, len, c);
    }
    WrapperStr& insert(int pos, const char* c)
    {
        wrappedString.insert(pos, c);
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
        wrappedString.remove(pos, len);
        return *this;
    }
    WrapperStr mid(int pos, int len = -1) const
    {
        return wrappedString.mid(pos, len);
    }
    WrapperStr& setNum(int num)
    {
        wrappedString.setNum(num);
        return *this;
    }
    void truncate(int pos)
    {
        wrappedString.left(pos);
    }
    QString upper() const
    {
        return wrappedString.toUpper();
    }
    QString lower() const
    {
        return wrappedString.toLower();
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


#endif
