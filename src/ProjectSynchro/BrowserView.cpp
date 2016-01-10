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





#include <qlabel.h>
#include <QMenu>
#include <qcursor.h>
#include "BrowserView.h"
#include "BrowserNode.h"
#include "SynchroWindow.h"

#define DICT_SIZE 101

BrowserView::BrowserView(QWidget * parent)
    : QTreeWidget(parent), lbl(0), need_update(FALSE), cant_update(FALSE)
{
    nodes.reserve(DICT_SIZE);

    setSortingEnabled(false);		// manual sorting


    setColumnCount(3);
    QStringList headers;

     headers<<("browser          ");
     headers<<("Rev.");
     headers<<("Modified by");
    setHeaderLabels(headers);
    connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
            this, SLOT(select(QTreeWidgetItem*,QTreeWidgetItem*)));
}

BrowserView::~BrowserView()
{
}

void BrowserView::close()
{
    if (itemAt(0,0)) {
        dir.rmdir("all.lock");
        clear();
    }
}

BrowserNode * BrowserView::get_project() const
{
    return (BrowserNode *) itemAt(0,0);
}

void BrowserView::set_project(QDir di)
{
    dir = di;
    new BrowserNode(this, dir.dirName() + ".prj");
    setRootIsDecorated(TRUE/*FALSE*/);

    di.cdUp();
#if 0
    setColumnText(0, di.path());
#endif
}

void BrowserView::select(QTreeWidgetItem *b, QTreeWidgetItem *previous)
{
    static bool ongoing = FALSE;

    if(!b)
        return;
    if (!ongoing) {
        ongoing = TRUE;

        const QList<BrowserView *> & l = SynchroWindow::get_browsers();
        QList<BrowserView*>::const_iterator it = l.begin();
        QString fn = ((BrowserNode *) b)->file_name();

        for (; it!= l.end(); ++it) {
            (*it)->clearSelection();

            BrowserNode * bn = (*it)->nodes.find(fn).value();

            if (bn != 0) {
                (*it)->scrollToItem(bn);
                setCurrentItem(bn);
                //(*it)->Q3ListView::setSelected(bn, TRUE);
            }
        }

        ongoing = FALSE;
    }
}

//

void BrowserView::add_node(BrowserNode * bn)
{
    nodes.insert(bn->file_name(), bn);
}

BrowserNode * BrowserView::get_node(QString f) const
{
    return nodes.find(f).value();
}

//

struct Use {
    int rev_min;
    int rev_max;
    int count;

    Use(int rev) : rev_min(rev), rev_max(rev), count(1) {}
};

void BrowserView::update(const QList<BrowserView *> & lv)
{
    QHash<QString, Use*> all_nodes;//(DICT_SIZE);
    QList<BrowserView*>::const_iterator itv = lv.begin();

    //all_nodes.setAutoDelete(TRUE);

    // look at the revision in each view

    for (; itv != lv.end(); ++itv) {
        QHash<QString, BrowserNode*>::iterator itd = (*itv)->nodes.begin();

        for (; itd != (*itv)->nodes.end() ; ++itd) {
            BrowserNode * bn = *itd;
            int rev = bn->get_rev();
            Use * use = all_nodes.find(itd.key()).value();

            if (use == 0)
                all_nodes.insert(itd.key(), new Use(rev));
            else {
                if (rev < use->rev_min)
                    use->rev_min = rev;

                if (rev > use->rev_max)
                    use->rev_max = rev;

                use->count += 1;
            }
        }
    }

    // first solve step
    // only the package existing in all the view are solved

    int nviews = lv.count();
    QStringList deleted_or_new;

    QHash<QString, Use*>::iterator itu = all_nodes.begin();

    for (; itu!=all_nodes.end(); ++itu) {
        QString who = itu.key();
        Use * use = itu.value();

        if (use->count == nviews) {
            // exist in all views : solve the state
            if (use->rev_min == use->rev_max) {
                // up to date in all views
                itv = lv.begin();
                for (; itv != lv.end(); ++itv)
                    (*itv)->nodes.find(who).value()->set_state(UpToDate);
            }
            else {
                int max = use->rev_max;

                itv = lv.begin();
                for (; itv != lv.end(); ++itv) {
                    BrowserNode * pack = (*itv)->nodes.find(who).value();

                    pack->set_state((pack->get_rev() == max) ? Young : Old);
                }
            }
        }
        else {
            // deleted or new, mark it unknown for this step
            deleted_or_new.append(who);

            itv = lv.begin();
            for (; itv != lv.end(); ++itv) {
                BrowserNode * pack = (*itv)->nodes.find(who).value();

                if (pack != 0)
                    pack->set_state(Unknown);
            }
        }
    }
    itu = all_nodes.begin();
    for (; itu!=all_nodes.end(); ++itu)
    {
        delete itu.value();
    }
    all_nodes.clear();

    // solve packages marked unknown
    // a package is deleted if its parent is never 'Young'

    QStringList::Iterator it;

    for (it = deleted_or_new.begin(); it != deleted_or_new.end(); ++it) {
        QString who = *it;
        QList<BrowserNode *> images;
        bool young = FALSE;

        // set the state in each view without looking at the others
        itv = lv.begin();
        for (; itv != lv.end(); ++itv) {
            BrowserNode * pack = (*itv)->nodes.find(who).value();

            if (pack != 0) {
                images.append(pack);

                if (pack->solve())
                    young = TRUE;
            }
        }

        // set the final state if young, else all already marked deleted
        if (young) {
            ;

            foreach (BrowserNode * pack, images) {
                pack->set_state(Young);
            }
        }
    }

    // force update on views
    itv = lv.begin();
    for (; itv != lv.end(); ++itv)
        (*itv)->update_it();
}

void BrowserView::update_it()
{
    if (lbl == 0)
        lbl = new QLabel(parentWidget());

    int nold = 0;
    int ndel = 0;

    QHash<QString, BrowserNode*>::iterator itd = nodes.begin();

    for (; itd != nodes.end(); ++itd) {
        BrowserNode * bn = itd.value();

        switch (bn->get_state()) {
        case Old:
            nold += 1;
            break;

        case Deleted:
            ndel += 1;
            break;

        default:
            break;
        }
    }

    QString s;

    if (nold != 0) {
        need_update = TRUE;

        s = QString::number(nold) + " need update";

        if (ndel != 0)
            s += ", " + QString::number(ndel) + " deleted";

        if (cant_update)
            s += ", RO !";

        lbl->setText(s);
    }
    else
        lbl->setText("Up to date");

    lbl->show();
#if 0
    triggerUpdate();
#endif
}

//

void BrowserView::synchronize()
{
    BrowserNode::synchronize(dir, nodes);
}
