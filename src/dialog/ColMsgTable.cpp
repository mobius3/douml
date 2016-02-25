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





//#include <q3popupmenu.h>
#include <qvalidator.h>
#include <qcursor.h>

#include "ColMsgTable.h"
#include "ColDiagramView.h"
#include "CodMsgSupport.h"
#include "CodObjCanvas.h"
#include "ui/menufactory.h"
#include "CodChangeMsgDialog.h"
#include "MyInputDialog.h"
#include "DialogUtil.h"
#include "translate.h"
#include "QHeaderView"
#define ABS_RANK_COL	0
#define HI_RANK_COL	1
#define FROM_COL	2
#define MSG_COL		3
#define TO_COL		4
#define CMD_COL		5

// to not align number at right and cannot edit items

class MsgTableItem : public TableItem
{
protected:
    int align;

public:
    MsgTableItem(const QString & txt, int al = Qt::AlignLeft)
        : TableItem(Never, txt, TableItem::MsgTableItemType), align(al | Qt::AlignVCenter) { }

    MsgTableItem(unsigned u, int al = Qt::AlignLeft)
        : TableItem(Never, QString::number(u), TableItem::MsgTableItemType), align(al | Qt::AlignVCenter) { }

    virtual int alignment() const override {
        return align;
    }
};

//

class HierarchicalRankValidator : public QValidator
{
protected:
    QString sub;
public:
    HierarchicalRankValidator(QWidget * parent, const QString & h)
        : QValidator(parent), sub(h + '.') {};

    virtual QValidator::State validate(QString & s, int &) const override;
};

QValidator::State HierarchicalRankValidator::validate(QString & s, int &) const
{
    if (s.isEmpty())
        return QValidator::Intermediate;

    QByteArray byteArray = s.toLatin1();
    const char * p = byteArray.constData();

    for (;;) {
        // digits expected
        switch (*p) {
        case 0:
            return QValidator::Intermediate;

        case '.':
            return (strncmp(sub.toLatin1().constData(), s.toLatin1().constData(), sub.length()))
                   ? QValidator::Intermediate
                   : QValidator::Invalid;

        default:
            if ((*p <= '0') || (*p > '9'))
                return QValidator::Invalid;
        }

        // bypass digits
        do p += 1;

        while ((*p >= '0') && (*p <= '9'));

        // '.' or end of string expected
        switch (*p) {
        case 0:
            return (strncmp(sub.toLatin1().constData(), s.toLatin1().constData(), sub.length()))
                   ? QValidator::Acceptable
                   : QValidator::Invalid;

        case '.':
            p += 1;
            break;

        default:
            return QValidator::Invalid;
        }
    }
}

//

ColMsgTable::ColMsgTable(QWidget * parent, ColDiagramView * v, ColMsgList & m)
    : MyTable(parent), rec(v->get_msgs() == m), view(v), msgs(m)
{
    //setSortingEnabled(true);
    setSelectionMode(NoSelection);	// single does not work

    setColumnCount(6);

    verticalHeader()->hide();
    setHorizontalHeaderLabel(ABS_RANK_COL, tr("Rank"));
    setHorizontalHeaderLabel(HI_RANK_COL, tr("Hierarchical rank"));
    setHorizontalHeaderLabel(FROM_COL, tr("From"));
    setHorizontalHeaderLabel(MSG_COL, tr("Message"));
    setHorizontalHeaderLabel(TO_COL, tr("To"));
    setHorizontalHeaderLabel(CMD_COL, tr("do"));

    refresh();

    connect(this, SIGNAL(pressed(QModelIndex)),
            this, SLOT(button_pressed(QModelIndex)));
}

void ColMsgTable::button_pressed(const QModelIndex &index)
{
    int row, col;
    row = index.row();
    col = index.column();
    if ((( row) >= flat_msg_list.count()) || (col > CMD_COL))
        // wrong signal
        return;

    if (col == MSG_COL)
        edit_msg(row);
    else if (col <= HI_RANK_COL)
        change_ranks(row, col);
    else {
        QMenu m;

        MenuFactory::createTitle(m, QString(tr("rank ")) + text(row, ABS_RANK_COL)
                                 + " : " + text(row, HI_RANK_COL));
        m.addSeparator();
        MenuFactory::addItem(m, tr("Edit message"), 1);
        MenuFactory::addItem(m, tr("Change ranks"), 2);
        m.addSeparator();
        MenuFactory::addItem(m, tr("Delete it"), 3);

        if (!flat_msg_list[row]->msgs.isEmpty())
            MenuFactory::addItem(m, tr("Delete recursively"), 4);

        QAction* retAction = m.exec(QCursor::pos());
        if(retAction)
        {
        switch (retAction->data().toInt()) {
        case 1:
            edit_msg(row);

            // no break;
        default:
            return;

        case 2:
            change_ranks(row, col);
            return;

        case 3:
            flat_msg_list[row]->delete_it(FALSE, view->get_msgs());
            break;

        case 4:
            flat_msg_list[row]->delete_it(TRUE, view->get_msgs());
            break;
        }
        }

        view->update_msgs();
        refresh();
    }
}

void ColMsgTable::refresh()
{
    setRowCount(0);
    flat_msg_list.clear();
    refresh(msgs);
    adjustColumn(ABS_RANK_COL);
    adjustColumn(HI_RANK_COL);
    adjustColumn(FROM_COL);
    adjustColumn(TO_COL);
    adjustColumn(CMD_COL);
    setColumnStretchable(MSG_COL, TRUE);
}

void ColMsgTable::refresh(ColMsgList & m)
{
    foreach (ColMsg *msg, m) {
        QString def = msg->def(FALSE, TRUE, UmlView, DefaultShowContextMode);
        CodObjCanvas * from;
        CodObjCanvas * to;
        int r = rowCount();

        msg->in->get_from_to(from, to, msg->is_forward);

        setRowCount(r + 1);

        setItem(r, ABS_RANK_COL, new MsgTableItem(msg->absolute_rank));
        setItem(r, HI_RANK_COL, new MsgTableItem(msg->hierarchical_rank));
        setItem(r, FROM_COL, new MsgTableItem(from->get_full_name()));
        setItem(r, MSG_COL, new MsgTableItem(def.mid(def.indexOf(" ") + 1)));
        setItem(r, TO_COL, new MsgTableItem(to->get_full_name()));
        setItem(r, CMD_COL, new MsgTableItem(tr("do"), Qt::AlignHCenter));

        flat_msg_list.append(msg);

        if (rec)
            refresh(msg->msgs);
    }
}

void ColMsgTable::edit_msg(int row)
{
    ColMsg * msg = flat_msg_list[row];

    CodChangeMsgDialog d(this, msg);

    if (d.exec() == QDialog::Accepted) {
        QString def = msg->def(FALSE, TRUE, UmlView, DefaultShowContextMode);

        msg->in->update_msgs();
        item(row, MSG_COL)->setText(def.mid(def.indexOf(" ") + 1));
    }
}

#ifdef NEW_METHOD
void ColMsgTable::save_list(ColMsgList & l, Q3PtrDict<ColMsgList> & saved)
{
    if (saved.find(&l) == 0) {
        saved.insert(&l, new ColMsgList(l));

        foreach (ColMsg *m, l) {
            save_list(m->get_msgs(), saved);
            save_list(m->in->get_msgs(), saved);
        }
    }
}
#endif

void ColMsgTable::change_ranks(int row, int col)
{
    ColMsg * msg = flat_msg_list[row];
    HierarchicalRankValidator validator(view, msg->hierarchical_rank);
    BooL ok;
    QString new_hr = MyInputDialog::getText(tr("Enter new hierarchical rank"), tr("Hierarchical rank : "),
                                            msg->hierarchical_rank, ok,
                                            &validator);

    if (ok && (new_hr != msg->hierarchical_rank)) {
        QString old_hr = msg->hierarchical_rank;

#ifndef NEW_METHOD
        // it may be (?, not reproduced) not possible to reintroduce the message
        // at its original rank when the new rank is wrong => stop to follow this
        // way and save the original def before trying to use the new rank ;-(
        //
        // Fixed by doing a ColDiagramView::update_msgs() after load ?

        for (;;) {
            msg->in->remove_it(msg);
            msg->extract_it(view->get_msgs());
            ColMsg::update_ranks(view->get_msgs());

            msg->hierarchical_rank = new_hr;
            msg->place_in_internal(view->get_msgs());
            msg->place_in_its_support();
            ColMsg::update_ranks(view->get_msgs());

            if (new_hr.indexOf('.') != -1) {
                // upper level msg dest must be msg start
                ColMsg * upper =
                    ColMsg::find_rec(new_hr.left(new_hr.lastIndexOf('.')), view->get_msgs());

                if (upper == 0)
                    // error
                    new_hr = QString();
                else {
                    CodObjCanvas * from;
                    CodObjCanvas * from_bis;
                    CodObjCanvas * to;

                    msg->in->get_from_to(from, to, msg->is_forward);
                    upper->in->get_from_to(from_bis, to, upper->is_forward);

                    if (to != from)
                        // error
                        new_hr = QString();
                }
            }

            if (msg->hierarchical_rank != new_hr) {
                msg_warning(tr("Warning"), tr("Invalid hierarchical rank"));
                new_hr = old_hr;
            }
            else
                break;
        }

        view->update_msgs();

        if (new_hr != old_hr) {
            refresh();
            setCurrentCell(flat_msg_list.indexOf(msg), col);
        }

#else
        // save all the messages
        Q3PtrDict<ColMsgList> saved;

        saved.setAutoDelete(TRUE);
        save_list(view->get_msgs(), saved);

        // remove the message
        msg->in->remove_it(msg);
        msg->extract_it(view->get_msgs());
        ColMsg::update_ranks(view->get_msgs());

        // try to insert the msg with the asked rank
        msg->hierarchical_rank = new_hr;
        msg->place_in_internal(view->get_msgs());
        msg->place_in_its_support();
        ColMsg::update_ranks(view->get_msgs());

        if (new_hr.find('.') != -1) {
            // upper level msg dest must be msg start
            ColMsg * upper =
                ColMsg::find_rec(new_hr.left(new_hr.findRev('.')), view->get_msgs());

            if (upper == 0)
                // error
                new_hr = QString();
            else {
                CodObjCanvas * from;
                CodObjCanvas * from_bis;
                CodObjCanvas * to;

                msg->in->get_from_to(from, to, msg->is_forward);
                upper->in->get_from_to(from_bis, to, upper->is_forward);

                if (to != from)
                    // error
                    new_hr = QString();
            }
        }

        if (msg->hierarchical_rank != new_hr) {
            msg_warning(TR("Warning"), TR("Invalid hierarchical rank"));

            msg->hierarchical_rank = old_hr;

            // restore saved lists

            Q3PtrDictIterator<ColMsgList> it(saved);

            while (it.current()) {
                *((ColMsgList *) it.currentKey()) = *(it.current());
                ++it;
            }
        }

        view->update_msgs();
        refresh();
        setCurrentCell(flat_msg_list.findIndex(msg), col);
#endif
    }
}
