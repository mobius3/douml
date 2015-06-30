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

#ifndef COMPONENTDIALOG_H
#define COMPONENTDIALOG_H

#include <qmap.h>
#include <tabdialog.h>
#include <QList>
#include "BrowserComponent.h"

class QComboBox;
class QListWidget;
class VVBox;
class LineEdit;
class MultiLineEdit;
class SimpleData;
class KeyValuesTable;
class FormalParamsTable;
class ActualParamsTable;
class BodyDialog;

class ComponentDialog : public TabDialog
{
    Q_OBJECT

protected:
    QWidget * umltab;
    SimpleData * data;
    LineEdit * edname;
    QComboBox * edstereotype;
    MultiLineEdit * comment;
    QList<BodyDialog *> edits;

    // required classes
    VVBox * rq_page;
    QComboBox * rq_stereotypefilter;
    QListWidget * lb_rq_available;
    QListWidget * lb_rq;
    QList<BrowserClass *> rqs;

    // provided classes
    VVBox * pr_page;
    QComboBox * pr_stereotypefilter;
    QListWidget * lb_pr_available;
    QListWidget * lb_pr;
    QList<BrowserClass *> prs;

    // realization classes
    VVBox * rz_page;
    QComboBox * rz_stereotypefilter;
    QListWidget * lb_rz_available;
    QListWidget * lb_rz;
    QList<BrowserClass *> rzs;

    // user
    KeyValuesTable * kvtable;

    static QSize previous_size;

    void init_uml_tab();
    void init_l_tab(VVBox *& page, QComboBox *& stereotypefilter,
                    void (ComponentDialog::* filteractivated)(const QString & st),
                    const char * filter_slt,
                    const char * add_slt, const char * remove_slt,
                    QListWidget *&lb_available, QListWidget *&lb,
                    const QList<BrowserClass *> & cls,
                    QString lbl);

    static void post_edit_description(ComponentDialog * d, QString s);

public:
    ComponentDialog(SimpleData * nd);
    virtual ~ComponentDialog();

protected slots:
    virtual void polish();
    virtual void accept();
    void edit_description();
    void rq_stereotypeFilterActivated(const QString & st);
    void pr_stereotypeFilterActivated(const QString & st);
    void rz_stereotypeFilterActivated(const QString & st);
    void require_cls();
    void unrequire_cls();
    void provide_cls();
    void unprovide_cls();
    void realize_cls();
    void unrealize_cls();

    void change_tabs(QWidget *);
};

#endif
