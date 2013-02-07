// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
// Copyright 2012-2013 Nikolai Marchenko.
// Copyright 2012-2013 Leonardo Guilherme.
//
// This file is part of the DOUML Uml Toolkit.
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
// e-mail : enmarantispam@gmail.com
// home   : http://sourceforge.net/projects/douml
//
// *************************************************************************

#ifndef OPERATIONLISTDIALOG_H
#define OPERATIONLISTDIALOG_H

#include <q3ptrlist.h>
#include <qdialog.h>
#include <q3ptrlist.h>

class Q3ComboBox;
class BrowserOperation;

class OperationListDialog : public QDialog
{
protected:
    Q3ComboBox * cb;

    static QSize previous_size;

public:
    OperationListDialog(const char * m, Q3PtrList<BrowserOperation> & l);
    virtual ~OperationListDialog();

    int choosen();
};

#endif
