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

// because QT is generally compiled without thread support
// I do not use a thread calling the external editor waiting
// and waiting for its end, and I use a timer which get each
// second the edit file content





#include <stdio.h>
#include <QTextStream>
#include <qfile.h>
#include <q3tabdialog.h>

#include "DialogTimer.h"

DialogTimer::DialogTimer(QString s, QString p, Q3TabDialog * d, post_edit pf)
    : QTimer(d), current(s), path(p), dlg(d), f(pf)
{
    connect(this, SIGNAL(timeout()), this, SLOT(readfile()));
}

void DialogTimer::readfile()
{
    FILE * fp;

    if ((fp = fopen((const char *) path, "rb")) != 0) {
        QString result;











        QFile fi;

        fi.open(QIODevice::ReadOnly, fp);

        QTextStream ts(&fi);

        ts.setEncoding(QTextStream::Latin1);

        result = ts.read();
        ts.flush();
        fi.close();

        fclose(fp);

        if (result != current) {
            current = result;
            f(dlg, result);
        }
    }
}

