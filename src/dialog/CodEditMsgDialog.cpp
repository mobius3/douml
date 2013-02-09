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





#include <qdialog.h>
#include <qlayout.h>
//Added by qt3to4:
#include <Q3VBoxLayout>

#include "CodEditMsgDialog.h"
#include "ColDiagramView.h"
#include "ColMsgTable.h"
#include "UmlDesktop.h"
#include "translate.h"

void CodEditMsgDialog::exec(ColDiagramView * view, ColMsgList & msgs)
{
    QDialog d(0, "Communication diagram message dialog", TRUE, 0);

    d.setCaption(TR("Communication diagram message dialog"));

    Q3VBoxLayout vbox(&d);

    vbox.addWidget(new ColMsgTable(&d, view, msgs));

    static QSize previous_size;

    UmlDesktop::limitsize_center(&d, previous_size, 0.8, 0.8);

    d.exec();

    previous_size = d.size();
}

