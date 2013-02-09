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
//Added by qt3to4:
#include "misc/mystr.h"
#include <stdlib.h>

#include "UmlCom.h"
#include "UmlItem.h"
#include "UmlPackage.h"
#include "Package.h"
#include "JavaCatWindow.h"
#include "Pixmap.h"
#include "Class.h"
#include <QDesktopWidget>

int main(int argc, char ** argv)
{
    if (argc != 2)
        return 0;

    if (UmlCom::connect(WrapperStr(argv[1]).operator QString().toUInt())) {
        try {
            //UmlCom::with_ack(FALSE);

            // warning : release is also in JavaCatWindow
            UmlCom::trace("<b>Java catalog</b> release 2.17<br><hr>");
            UmlCom::traceAutoRaise(FALSE);

            UmlItem * item = UmlCom::targetItem();

            if (item->kind() != aPackage)
                UmlCom::trace("<font face=helvetica><b>must be applied on a <i>package</i></b></font><br><hr><br>");
            else {
                char * argv = 0;
                int argc = 0;

                QApplication * app = new QApplication(argc, &argv);

                app->connect(app, SIGNAL(lastWindowClosed()), SLOT(quit()));

                init_pixmaps();

                JavaCatWindow * w = new JavaCatWindow();

                w->resize((QApplication::desktop()->width() * 3) / 5,
                          (QApplication::desktop()->height() * 3) / 5);

                w->show();

                Package::init((UmlPackage *) item, app);
                app->exec();
            }
        }
        catch (...) {
        }

        try {
            // socket may be already closed
            UmlCom::showTrace();
            UmlCom::bye(0);	// application must not be deleted
        }
        catch (...) {
        }
    }

    UmlCom::close();	// application must not be deleted
    return 0;
}
