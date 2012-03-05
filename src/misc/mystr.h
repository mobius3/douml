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
    // this serves as a keeper for temporary array that got destroyed otherwise
    // messing the output of operator const char*
    static  QByteArray ba[20];
    static int arrayRotate;

    WrapperStr(){}
    ~WrapperStr(){}
    WrapperStr(const WrapperStr & other)
    {
        //QLOG_INFO()() << Q_FUNC_INFO;
        *this = other;
    }
    WrapperStr(const QString & other)
    {
        //QLOG_INFO()() << Q_FUNC_INFO;
        this->wrappedString = other;
    }
    //QString get(){return s;}
    bool isEmpty() const
    {
        return this->wrappedString.isEmpty();
    }
    unsigned int length() const
    {
        return this->wrappedString.length();
    }
    int find(const char * toFind, int index = 0) const
    {
        return wrappedString.indexOf(QString(QLatin1String(toFind)), index);
    }
    int find(int c, int index = 0) const
    {
        return wrappedString.indexOf(QString::number(c) , index);
    }

    WrapperStr & operator=(const WrapperStr & other)
    {
        //QLOG_INFO()() << Q_FUNC_INFO;
        //QLOG_INFO()() << "Otheris " << other.wrappedString << "this is" << this->wrappedString;
        this->wrappedString = other.wrappedString; return *this;
        //QLOG_INFO()() << "Otheris " << other.wrappedString << "this is" << this->wrappedString;
    }
    WrapperStr & operator=(const char * c)
    {
        //QLOG_INFO()() << Q_FUNC_INFO;
        //QLOG_INFO()() << "Otheris " << c << "this is" << this->wrappedString;
        this->wrappedString = QString(QLatin1String(c));
        return *this;
        //QLOG_INFO()() << "Otheris " << c << "this is" << this->wrappedString;
    }
    WrapperStr & operator=(const QString &other )
    {
        //QLOG_INFO()() << Q_FUNC_INFO;
        //QLOG_INFO()() << "Otheris " << other << "this is" << this->wrappedString;
        this->wrappedString = other; return *this;
        //QLOG_INFO()() << "Otheris " << other << "this is" << this->wrappedString;

    }
    WrapperStr & operator=(const Q3CString &cstr)
    {
        //QLOG_INFO()() << Q_FUNC_INFO;
        //QLOG_INFO()() << cstr.data()<< Q_FUNC_INFO;
        this->wrappedString = QByteArray(cstr); return *this;
    }
    operator const char *() const
    {
        ////QLOG_INFO()() << Q_FUNC_INFO;
        ////QLOG_INFO()() << wrappedString;
        if(wrappedString.length()>0)
        {
            arrayRotate++;
            if(arrayRotate == 20)
                arrayRotate=0;
            ba[arrayRotate] = wrappedString.toLatin1();
            ////QLOG_INFO()() << ba;
            const char* retVal = ba[arrayRotate].data();
            return retVal;
        }
        int k = 0;
        k++;
        return returnableNullPtr;
    }

    operator QString() const
    {
        //QLOG_INFO()() << Q_FUNC_INFO;
        //QLOG_INFO()() << this->wrappedString;
        return this->wrappedString;
    }
    operator Q3CString() const
    {
        //QLOG_INFO()() << Q_FUNC_INFO;
        //QLOG_INFO()() << this->wrappedString.toLatin1();
        return this->wrappedString.toLatin1();
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
        //QLOG_INFO()() << Q_FUNC_INFO;
        //QLOG_INFO()() << QString(QLatin1String(c));
        Q_UNUSED(len); this->wrappedString = QString(QLatin1String(c));
    }
    //void assign(QString(), int len){this->s = QString();}

  protected:
    static char returnableNullPtr[1];

  QString wrappedString;
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
