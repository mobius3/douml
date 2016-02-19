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

#ifndef HAVEKEYVALUEDATA_H
#define HAVEKEYVALUEDATA_H

#include <qstring.h>
//Added by qt3to4:
#include <QTextStream>

class QTextStream;
class KeyValueData;
class ToolCom;

// this class manage a table of couple key-value

class HaveKeyValueData
{
protected:
    KeyValueData * keyvalues;	// remark : do NOT use QArray
    unsigned nkeyvalues;

public:
    HaveKeyValueData();
    virtual ~HaveKeyValueData();

    QString get_key(int rank) const;

    void set_key(int rank, QString k);
    QString get_value(int rank) const;
    QString get_value(QString k) const;
    void set_value(int rank, QString v);
    int has_key(QString);
    unsigned get_n_keys() const {
        return nkeyvalues;
    };
    void remove_key_value(unsigned index);
    void remove_key_value(QString k);
    void set_n_keys(unsigned n);	// the old key-values are lost
    void resize_n_keys(unsigned n, bool realloc); // the old key-values are not lost

    void send_def(ToolCom * com) const;
    void set_value(QString k, QString v);

    void save(QTextStream &) const;
    void read(char *& , char *& k);
};

#endif
