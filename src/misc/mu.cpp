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





#include <stdlib.h>
#include <stdio.h>
#include <qdatetime.h>
//Added by qt3to4:


#include "mu.h"
#include "myio.h"
#include "BrowserView.h"
#include "DialogUtil.h"
#include "EnvDialog.h"
#include "translate.h"

static int Uid = -1;
static int RootPermission;	// old Uid or 0

void set_user_id(int i)
{
    if ((Uid > 0) && BrowserView::get_project()) {
        QDir dir = BrowserView::get_dir();

        dir.rmdir(QString::number(Uid) + ".lock");
    }

    Uid = i;
}

int user_id()
{
    if (Uid == -1) {
        QDir dir = BrowserView::get_dir();

        if (dir.exists("all.lock")) {
            msg_critical("Douml",
                         TR("\
                            The project is open in read-only mode because it is\n\
                            under the control of 'Project control' or 'Project merge'\n\
                            (the directory '%1' exists", dir.absFilePath("all.lock")));
            force_read_only(TRUE);
        }
        else
            force_read_only(FALSE);

        int uid = read_doumlrc();

        // when loading the project file itself and creating the
        // BrowserPackage for it, BrowserView::get_project() return 0
        if (BrowserView::get_project()) {
            Uid = uid;

            QString fn = QString::number(Uid) + ".lock";

            if (! dir.mkdir(fn)) {
                if (!dir.exists(fn)) {
                    msg_critical(TR("User Own Identifier"),
                                 TR("Can't create directory '%1',\nthe project is open in read-only mode",
                                    dir.absFilePath(fn)));
                    force_read_only(TRUE);
                }
                else {
                    int retCode = msg_critical(TR("User Own Identifier"),
                                               TR("It seems that you are already editing the project.\n\n"
                                                  "If you're SURE that this is not the case and\n"
                                                  "another user does not have an identifier equal\n"
                                                  "to yours you can gain ownership of the lock.").arg(dir.absFilePath(fn))
                                               , QMessageBox::Ok, QMessageBox::Close);

                    if (retCode == QMessageBox::Ok) {
                        dir.rmdir(fn);
                        return uid;

                    }
                    else
                        exit(1);
                }
            }
        }

        return uid;
    }
    else
        return Uid;
}

void set_root_permission(bool y)
{
    RootPermission = (y) ? Uid : 0;
}

int root_permission()
{
    return RootPermission;
}

//

const char * user_name()
{
    static bool done = FALSE;
    static WrapperStr name;

    if (! done) {
        name = homeDir().dirName();
        done = TRUE;
    }

    return name;
}
