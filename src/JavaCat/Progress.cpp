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





#include <qapplication.h>

#include "Progress.h"

Progress * Progress::it = 0;

Progress::Progress(int n, const char * lbl, QApplication * a)
    : Q3ProgressDialog(0, 0, n, 0, 0, FALSE, Qt::WDestructiveClose), n(0), app(a)
{
    if (it != 0)
        delete it;

    it = this;
    setLabelText(lbl);
    setMinimumDuration(1000);
}

Progress::~Progress()
{
    it = 0;
}

void Progress::tic()
{
    setProgress(++n);
    raise();
    app->processEvents();
}

void Progress::delete_it()
{
    if (it != 0)
        delete it;
}

void Progress::tic_it()
{
    if (it != 0)
        it->tic();
}
