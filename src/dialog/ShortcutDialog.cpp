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





#include <stdio.h>

#include <qcursor.h>
#include <vvbox.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qlayout.h>
//#include <q3popupmenu.h>
//Added by qt3to4:
#include <QPixmap>

#include "ShortcutDialog.h"
#include "Shortcut.h"
#include "Tool.h"
#include "DialogUtil.h"
#include "UmlDesktop.h"
#include "ComboItem.h"
#include "translate.h"
#include "widgetwithlayout.h"
#include "menufactory.h"
#include <QHeaderView>

QSize ShortcutDialog::previous_size;

ShortcutDialog::ShortcutDialog() : TabDialog(0, 0, TRUE)
{
    setOkButton(TR("OK"));
    setCancelButton(TR("Cancel"));
    setWindowTitle(TR("Shortcut dialog"));

    // count number of entries

    QStringList tools = Tool::all_display();
    const QMap<QString, QString> & shortcuts = Shortcut::shortcuts();
    QMap<QString, QString>::ConstIterator iter;
    int ntools = 0;
    int ncmds = 0;

    for (iter = shortcuts.begin(); iter != shortcuts.end(); ++iter) {
        if (tools.indexOf(iter.value()) != -1)
            ntools += 1;
        else
            ncmds += 1;
    }

    // tab for command

    VVBox * vtab;

    vtab = new VVBox(this);
    //vtab->setSpacing(5);
    vtab->setMargin(5);

    vtab->addWidget((new QLabel(TR("Here are the shortcuts to do a command (menu entry)"), vtab)));

#ifdef __APPLE__
    (new QLabel(TR("Note : sometimes the key 'Alt' is named 'Option'"), vtab))
            ->setAlignment(::Qt::AlignHCenter);
#endif

    vtab->addWidget(cmd_table = new ShortcutTable(vtab, FALSE, ncmds));

    addTab(vtab, QObject::tr("Command"));

    // tab for tool

    vtab = new VVBox(this);
    //vtab->setSpacing(5);
    //vtab->setMargin(5);

    QLabel *label;
    vtab->addWidget((label = new QLabel(TR("Here are the shortcuts to call a tool (plug-out)"), vtab)));
    label->setAlignment(::Qt::AlignHCenter);

#ifdef __APPLE__
    (new QLabel(TR("Note : sometimes the key 'Alt' is named 'Option'"), vtab))
            ->setAlignment(::Qt::AlignHCenter);

#endif
    vtab->addWidget(tool_table = new ShortcutTable(vtab, TRUE, ntools));

    addTab(vtab, QObject::tr("Tool"));
}

ShortcutDialog::~ShortcutDialog()
{
    previous_size = size();
}

void ShortcutDialog::polish()
{
    TabDialog::ensurePolished();
    UmlDesktop::limitsize_center(this, previous_size, 0.8, 0.8);
}

void ShortcutDialog::accept()
{
    QStringList bindings;

    if (cmd_table->check(bindings) && tool_table->check(bindings)) {
        Shortcut::raz();
        cmd_table->accept();
        tool_table->accept();
        Shortcut::save();
        TabDialog::accept();
    }
}

//
// ShortcutTable
//

// copy/cut/paste

ShortcutTable::ShortcutTable(QWidget * parent, bool tool, int n)
    : MyTable(n + 1, 6, parent), for_tool(tool)
{
    //setSortingEnabled(true);
    m_delegate = new TableWidgetItemDelegate(this);
    setItemDelegateForColumn(3,m_delegate);
    setItemDelegateForColumn(4,m_delegate);
    verticalHeader()->setSectionsMovable(true);
    setSelectionMode(NoSelection);	// single does not work
    QStringList headerLabels;
    headerLabels.append(TR("Shift"));
#ifdef __APPLE__
#include "../xpm/pomme_xpm.xpm"
    QPixmap pomme_xpm((const char **) pomme);
    QIcon ic(pomme_xpm);
    headerLabels.append(ic, "");
#else
    headerLabels.append(TR("Ctrl"));
#endif
    headerLabels.append(TR("Alt"));
    headerLabels.append( QObject::tr("Key"));
    headerLabels.append((tool) ? QObject::tr("tool display") : QObject::tr("command"));
    headerLabels.append(TR("do"));
    setHorizontalHeaderLabels(headerLabels);

    QStringList tools = Tool::all_display();

    values.append("");
    keys.append("");

    if (tool)
        values += tools;
    else {
        const QStringList & cmds = Shortcut::cmds();

        for (QStringList::ConstIterator it = cmds.begin(); it != cmds.end(); ++it)
            values.append(
                        *it
                        );
    }

    keys += Shortcut::keys();

    const QMap<QString, QString> & shortcuts = Shortcut::shortcuts();
    QMap<QString, QString>::ConstIterator iter;
    int row = 0;

    for (iter = shortcuts.begin(); iter != shortcuts.end(); ++iter) {
        int tool_index = tools.indexOf(iter.value());

        if ((tool) ? (tool_index != -1) : (tool_index == -1)) {
            BooL shift;
            BooL ctrl;
            BooL alt;
            QString key = Shortcut::extract(iter.key(), shift, ctrl, alt);

            if (shift) setText(row, 0, QObject::tr("yes"));

            if (ctrl) setText(row, 1, QObject::tr("yes"));

            if (alt) setText(row, 2, QObject::tr("yes"));

            setItem(row, 3, new ComboItem(this, key, keys, FALSE));
            setItem(row, 4, new ComboItem(this, (tool) ? iter.value() : iter.value(), values, FALSE));
            row += 1;
        }
    }
    sortByColumn(3);
    setItem(row, 3, new ComboItem(this, QString(), Shortcut::keys(), FALSE));
    setItem(row, 4, new ComboItem(this, QString(), values, FALSE));
    adjustColumn(0);
    adjustColumn(1);
    adjustColumn(2);
    adjustColumn(5);
    setColumnStretchable(4, TRUE);
    setColumnStretchable(5, FALSE);

    connect(this, SIGNAL(pressed(QModelIndex)),
            this, SLOT(button_pressed(QModelIndex)));
    connect(this, SIGNAL(cellChanged(int, int)),
            this, SLOT(value_changed(int, int)));
}

void ShortcutTable::value_changed(int row, int col)
{
    if ((row == (rowCount() - 1)) && (col == 3) && !text(row, 3).isEmpty())
        insert_row_after(row);
}

void ShortcutTable::button_pressed(const QModelIndex &index)
{
    int row = index.row();
    int col = index.column();
    if (col < 3) {
        setText(row, col, text(row, col).isEmpty() ? QObject::tr("yes") : QString());
        //item(row, col)->setText(text(row, col).isEmpty() ? QObject::tr("yes") : QString());
    }

    if (col == 5) {
        char s[16];

        sprintf(s, "%d", row + 1);

        QMenu m;
        MenuFactory::addItem(m, QObject::tr("shortcut ") + QString(s), -1);
        m.addSeparator();
        MenuFactory::addItem(m,TR("Insert shortcut before"), 0);
        MenuFactory::addItem(m,TR("Insert shortcut after"), 1);
        m.addSeparator();
        MenuFactory::addItem(m,TR("Delete shortcut"), 2);
        m.addSeparator();
        MenuFactory::addItem(m,TR("Copy shortcut"), 3);
        MenuFactory::addItem(m,TR("Cut shortcut"), 4);
        MenuFactory::addItem(m,TR("Paste shortcut"), 5);
        m.addSeparator();
        QAction *retAction = m.exec(QCursor::pos());
        if(retAction)
            switch (retAction->data().toInt()) {
            case 0:
                insert_row_before(row);
                break;

            case 1:
                insert_row_after(row);
                break;

            case 2:
                delete_row(row);
                break;

            case 3:
                copy_row(row);
                break;

            case 4:
                cut_row(row);
                break;

            case 5:
                paste_row(row);
                break;

            default:
                break;
            }
    }
}

void ShortcutTable::insert_row_before(int row)
{
    /*int n = rowCount();
    int index;

    setRowCount(n + 1);

    for (index = n; index != row; index -= 1) {
        QTableWidgetItem * it;

        item(index, 0)->setText( item(index - 1, 0)->text());
        item(index, 1)->setText( item(index - 1, 1)->text());
        item(index, 2)->setText(item(index - 1, 2)->text());
        it = item(index - 1, 3);

        if(it)
        {
            takeItem(it->row(), it->column());
            setItem(index, 3, it);
        }
        it = item(index - 1, 4);
        if(it)
        {
            takeItem(it->row(), it->column());
            setItem(index, 4, it);
        }
    }
    */
    blockSignals(true);
    DISABLESORTINGMYTABLE;
    insertRow(row);
    setText(row, 0, QString());
    setText(row, 1, QString());
    setText(row, 2, QString());
    setItem(row, 3, new ComboItem(this, QString(), Shortcut::keys(), FALSE));
    setItem(row, 4, new ComboItem(this, QString(), values, FALSE));
    ENABLESORTINGMYTABLE;
    blockSignals(false);
}

void ShortcutTable::insert_row_after(int row)
{
    /*int n = rowCount();
    int index;

    setRowCount(n + 1);

    for (index = n; index > row + 1; index -= 1) {
        QTableWidgetItem * it;

        item(index, 0)->setText( item(index - 1, 0)->text());;
        item(index, 1)->setText( item(index - 1, 1)->text());;
        item(index, 2)->setText( item(index - 1, 2)->text());;
        it = item(index - 1, 3);
        takeItem(it->row(), it->column());
        setItem(index, 3, it);
        it = item(index - 1, 4);
        takeItem(it->row(), it->column());
        setItem(index, 4, it);
    }
    */
    blockSignals(true);
    DISABLESORTINGMYTABLE;
    insertRow(row+1);
    setText(row + 1, 0, QString());
    setText(row + 1, 1, QString());
    setText(row + 1, 2, QString());
    setItem(row + 1, 3, new ComboItem(this, QString(), Shortcut::keys(), FALSE));
    setItem(row + 1, 4, new ComboItem(this, QString(), values, FALSE));
    ENABLESORTINGMYTABLE;
    blockSignals(false);
}

void ShortcutTable::delete_row(int row)
{
    int n = rowCount();
    int index;


    removeCellWidget(row, 1);
    removeRow(row);
    return;

    if (row == (n - 1)) {
        // the last line : empty it
        setText(row, 0, QString());
        setText(row, 1, QString());
        setText(row, 2, QString());
        setItem(row, 3, new ComboItem(this, QString(), Shortcut::keys(), FALSE));
        setItem(row, 4, new ComboItem(this, QString(), values, FALSE));
    }
    else {
        for (index = row; index != n - 1; index += 1) {
            QTableWidgetItem * it;

            setText(index, 0, text(index + 1, 0));;
            setText(index, 1, text(index + 1, 1));;
            setText(index, 2, text(index + 1, 2));;
            it = item(index + 1, 3);
            takeItem(it->row(), it->column());
            setItem(index, 3, it);
            it = item(index + 1, 4);
            takeItem(it->row(), it->column());
            setItem(index, 4, it);
        }

        setRowCount(n - 1);
    }
}

void ShortcutTable::copy_row(int row)
{
    shift_copy = text(row, 0);
    control_copy = text(row, 1);
    alt_copy = text(row, 2);
    key_copy = text(row, 3);
    val_copy = text(row, 4);
}

void ShortcutTable::cut_row(int row)
{
    copy_row(row);
    delete_row(row);
}

void ShortcutTable::paste_row(int row)
{
    setText(row, 0, shift_copy);
    setText(row, 1, control_copy);
    setText(row, 2, alt_copy);
    setText(row, 3, key_copy);
    setText(row, 4, val_copy);

    if ((row == (rowCount() - 1)) &&
            (!key_copy.isEmpty() ||
             !val_copy.isEmpty()))
        insert_row_after(row);
}

bool ShortcutTable::check(QStringList & bindings)
{
    forceUpdateCells();

    int n = rowCount();
    int row;

    for (row = 0; row != n; row += 1) {
        if (!text(row, 3).isEmpty() && !text(row, 4).isEmpty()) {
            QString s;

            if (!text(row, 0).isEmpty())
                s = QObject::tr("Shift ");

            if (!text(row, 1).isEmpty())
#ifdef __APPLE__
                s += "Apple ";

#else
                s += QObject::tr("Ctrl ");
#endif

            if (!text(row, 2).isEmpty())
                s += QObject::tr("Alt ");

            s += text(row, 3);

            if (bindings.indexOf(s) == -1)
                bindings.append(s);
            else {
                msg_warning(TR("Shortcut"), tr("Several use of the shortcut '%1'").arg(s));
                return FALSE;
            }
        }
    }

    return TRUE;
}

void ShortcutTable::accept()
{
    const QStringList & cmds = Shortcut::cmds();
    int n = rowCount();
    int row;

    for (row = 0; row != n; row += 1)
        if (!text(row, 3).isEmpty() && !text(row, 4).isEmpty())
            Shortcut::add(text(row, 3), !text(row, 0).isEmpty(),
                          !text(row, 1).isEmpty(), !text(row, 2).isEmpty(),
                          (for_tool) ? text(row, 4) : cmds[values.indexOf(text(row, 4)) - 1]);
}
