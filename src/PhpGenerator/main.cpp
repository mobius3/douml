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

#include "UmlCom.h"
#include "UmlItem.h"
#include "util.h"
//Added by qt3to4:
#include "misc/mystr.h"

int main(int argc, char ** argv)
{
    int port_index;

    if (argc == 2)
        port_index = 1;
    else if (argc == 3) {
        if (argv[1][1] == 'v')
            set_verbose();
        else
            set_preserve();

        port_index = 2;
    }
    else if (argc == 4) {
        set_verbose();
        set_preserve();
        port_index = 3;
    }
    else
        return 0;

    if (UmlCom::connect(WrapperStr(argv[port_index]).operator QString().toUInt())) {
        try {
            UmlCom::trace("<b>Php generator</b> release 1.10.1<br>");
            UmlCom::traceAutoRaise(FALSE);

            UmlCom::targetItem()->generate();

            QString s;

            s = "<hr><font face=helvetica>Generation done : %1 warnings, %2 errors</font><br>";
            s=s.arg(QString::number(n_warnings())).arg(QString::number(n_errors()));

            UmlCom::trace(s);

            UmlCom::showTrace();
            UmlCom::message("");

            UmlCom::bye(n_errors());
        }
        catch (...) {
        }
    }

    UmlCom::close();
    return 0;
}
