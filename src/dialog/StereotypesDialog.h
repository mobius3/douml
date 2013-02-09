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

#ifndef STEREOTYPESDIALOG_H
#define STEREOTYPESDIALOG_H

#include <q3tabdialog.h>

#include <UmlEnum.h>

class LineEdit;
class MyTable;

class StereotypesDialog : public Q3TabDialog
{
    Q_OBJECT

protected:
    LineEdit * package_list;
    MyTable * packagetable;
    LineEdit * class_list;
    MyTable * classtable;
    LineEdit * usecase_list;
    MyTable * usecasetable;
    LineEdit * artifact_list;
    MyTable * artifacttable;
    LineEdit * attribute_list;
    LineEdit * operation_list;
    LineEdit * component_list;
    LineEdit * node_list;
    LineEdit * msg_list;
    LineEdit * state_list;
    LineEdit * pseudostate_list;
    LineEdit * stateaction_list;
    LineEdit * activity_list;
    LineEdit * interruptibleactivityregion_list;
    LineEdit * expansionregion_list;
    LineEdit * parameter_list;
    LineEdit * parameterset_list;
    LineEdit * activitynode_list;
    LineEdit * activityaction_list;
    LineEdit * activityobject_list;
    LineEdit * activitypartition_list;
    LineEdit * pin_list;
    LineEdit * expansionnode_list;
    LineEdit * flow_list;
    LineEdit * classview_list;
    LineEdit * usecaseview_list;
    LineEdit * componentview_list;
    LineEdit * deploymentview_list;
    LineEdit * classdiagram_list;
    LineEdit * objectdiagram_list;
    LineEdit * coldiagram_list;
    LineEdit * seqdiagram_list;
    LineEdit * usecasediagram_list;
    LineEdit * statediagram_list;
    LineEdit * activitydiagram_list;
    LineEdit * componentdiagram_list;
    LineEdit * deploymentdiagram_list;

    static QSize previous_size;

public:
    StereotypesDialog();
    virtual ~StereotypesDialog();

protected slots:
    virtual void polish();
    void accept();
};

#endif
