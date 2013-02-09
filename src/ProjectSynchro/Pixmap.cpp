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





#include "Pixmap.h"
//Added by qt3to4:
#include <QPixmap>

QPixmap * UpToDatePackageIcon;
QPixmap * YoungPackageIcon;
QPixmap * OldPackageIcon;
QPixmap * DeletedPackageIcon;
QPixmap * PackageIcon;

//

void init_pixmaps()
{
    // browser icons

#include "package_xpm.xpm"

    UpToDatePackageIcon = new QPixmap((const char **) uptodate_package_xpm);
    YoungPackageIcon = new QPixmap((const char **) young_package_xpm);
    OldPackageIcon = new QPixmap((const char **) old_package_xpm);
    DeletedPackageIcon = new QPixmap((const char **) deleted_package_xpm);
    PackageIcon = new QPixmap((const char **) package_xpm);
}
