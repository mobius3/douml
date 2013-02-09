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





#include <q3buttongroup.h>
#include <qradiobutton.h>

#include "VisibilityGroup.h"

Q3ButtonGroup * VisibilityGroup::init(QWidget * parent, UmlVisibility v, bool pack_allowed,
                                      const char * title,
                                      const char * default_prefix)
{
    if (!bgroup) {
        bgroup = new Q3ButtonGroup((default_prefix != 0) ? 5 : 4, Qt::Horizontal, title, parent);
        public_rb = new QRadioButton("public", bgroup);
        protected_rb = new QRadioButton("protected", bgroup);
        private_rb = new QRadioButton("private", bgroup);
        package_rb = (pack_allowed) ? new QRadioButton("package", bgroup) : 0;
        default_visibility_rb =
            new QRadioButton(default_pfix + " (protected)", bgroup);
    }

    bgroup->setExclusive(TRUE);

    if (default_prefix != 0) {
        default_pfix = default_prefix;
        default_visibility_rb->setText(default_pfix + " (protected)");
    }
    else
        default_visibility_rb->hide();


    switch (v) {
    case UmlPublic:
        public_rb->setChecked(TRUE);
        break;

    case UmlProtected:
        protected_rb->setChecked(TRUE);
        break;

    case UmlPrivate:
        private_rb->setChecked(TRUE);
        break;

    case UmlPackageVisibility:
        ((pack_allowed) ? package_rb : public_rb)->setChecked(TRUE);
        break;

    default:
        if (!default_visibility_rb->isHidden())
            default_visibility_rb->setChecked(TRUE);
    }

    return bgroup;
}

void VisibilityGroup::update_default(const VisibilityGroup & default_grp)
{
    if (default_visibility_rb != 0) {
        if (default_grp.public_rb->isChecked())
            default_visibility_rb->setText(default_pfix + " (public)");
        else if (default_grp.protected_rb->isChecked())
            default_visibility_rb->setText(default_pfix + " (protected)");
        else if (default_grp.private_rb->isChecked())
            default_visibility_rb->setText(default_pfix + " (private)");
        else
            default_visibility_rb->setText(default_pfix + " (package)");
    }
}


void VisibilityGroup::connect(const char * sig, QWidget * w, const char * slt)
{
    QObject::connect(bgroup, sig, w, slt);
}

void VisibilityGroup::follow(const VisibilityGroup & other)
{
    static bool inside = FALSE;

    if (! inside) {
        inside = TRUE;

        public_rb->setChecked(other.public_rb->isChecked());
        protected_rb->setChecked(other.protected_rb->isChecked());
        private_rb->setChecked(other.private_rb->isChecked());

        if (package_rb != 0) {
            if (other.package_rb != 0)
                package_rb->setChecked(other.package_rb->isChecked());
            else
                package_rb->setChecked(FALSE);
        }

        inside = FALSE;
    }
}

UmlVisibility VisibilityGroup::value()
{
    if ((default_visibility_rb != 0) && default_visibility_rb->isChecked())
        return UmlDefaultVisibility;
    else if (public_rb->isChecked())
        return UmlPublic;
    else if (protected_rb->isChecked())
        return UmlProtected;
    else if (private_rb->isChecked())
        return UmlPrivate;
    else
        return UmlPackageVisibility;
}

QString VisibilityGroup::state()
{
    if (public_rb->isChecked())
        return "public";
    else if (protected_rb->isChecked())
        return "protected";
    else if (private_rb->isChecked())
        return "private";
    else
        return "package";
}
