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

#ifndef KEYVALUETABLE_H
#define KEYVALUETABLE_H

#include <q3dict.h>
#include "StringTable.h"

class HaveKeyValueData;

class KeyValuesTable : public StringTable
{
public:
    KeyValuesTable(HaveKeyValueData * h, QWidget * parent, bool visit);

    virtual void init_row(int index);
    bool eventFilter(QObject *o, QEvent *);
    bool check_unique();
    void updateNodeFromThis(HaveKeyValueData * h);
    void updateThisFromNode(HaveKeyValueData * h, bool visit = false);
    bool get_value(const char * key, QString & value);
    void remove(const char * key);

    bool EqualData(HaveKeyValueData*);

private:
    void Init(HaveKeyValueData * h, bool isReadOnly);
    void SetupTableText(HaveKeyValueData * hv, bool isReadOnly);
    void AdjustColumnCount(bool);
    void AdjustRowCount(HaveKeyValueData *, bool);
    void AdjustEditability(bool);
    QHash<QString, QStringList> props;
    QHash<int, QString> colNames;


};

#endif
