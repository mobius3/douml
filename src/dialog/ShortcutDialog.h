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

#ifndef SHORTCUTDIALOG_H
#define SHORTCUTDIALOG_H

#include <q3tabdialog.h>

#include "MyTable.h"

class Q3ComboBox;
class QPushButton;

class ShortcutTable;

class ShortcutDialog : public Q3TabDialog
{
    Q_OBJECT

protected:
    ShortcutTable * cmd_table;
    ShortcutTable * tool_table;

    static QSize previous_size;

protected:

public:
    ShortcutDialog();
    virtual ~ShortcutDialog();

protected slots:
    virtual void polish();
    virtual void accept();
};

class ShortcutTable : public MyTable
{
    Q_OBJECT

protected:
    bool for_tool;
    QString shift_copy;		// copy/cut/paste
    QString control_copy;
    QString alt_copy;
    QString key_copy;
    QString val_copy;
    QStringList keys;
    QStringList values;

public:
    ShortcutTable(QWidget * parent, bool tool, int n);

protected:
    void insert_row_before(int row);
    void insert_row_after(int row);
    void delete_row(int row);
    void copy_row(int row);
    void cut_row(int row);
    void paste_row(int row);
    void move_row(int from, int to);

public:
    bool check(QStringList &);
    void accept();

protected slots:
    void button_pressed(int row, int col, int button, const QPoint & mousePos);
    void value_changed(int row, int col);
};

#endif
