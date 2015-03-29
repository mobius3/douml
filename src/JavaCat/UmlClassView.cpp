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
#include "UmlClassView.h"

#ifdef ROUNDTRIP
#include "ClassContainer.h"
#include "UmlArtifact.h"
#include "UmlPackage.h"
#include "Package.h"

static QHash<UmlArtifact*,UmlArtifact*> Artifacts;

void UmlClassView::upload(ClassContainer * cnt)
{
    const QVector<UmlItem*> & ch = UmlItem::children();
    UmlItem *const* v = ch.data();
    UmlItem *const*  vsup = v + ch.size();

    for (; v != vsup; v += 1)
        (*v)->upload(cnt);
}

bool UmlClassView::set_roundtrip_expected()
{
    const QVector<UmlItem*> & ch = UmlItem::children();
    UmlItem *const* v = ch.data();
    UmlItem *const*  vsup = v + ch.size();
    bool result = isWritable();

    for (; v != vsup; v += 1)
        result &= (*v)->set_roundtrip_expected();

    return result;
}

void UmlClassView::mark_useless(QList<UmlItem *> & l)
{
    QVector<UmlItem*> ch = UmlItem::children();
    UmlClassItem ** v = (UmlClassItem **) ch.data();
    UmlClassItem ** const vsup = v + ch.size();

    for (; v != vsup; v += 1)
        (*v)->mark_useless(l);
}

void UmlClassView::scan_it(int & n)
{
    // compute artifact list
    const QVector<UmlItem*> & ch = UmlItem::children();
    UmlItem *const* v = ch.data();
    UmlItem *const*  vsup = v + ch.size();

    n = 0;

    for (; v != vsup; v += 1) {
        if ((*v)->kind() == aClass) {
            UmlClass * cl = (UmlClass *) *v;

            if (cl->is_roundtrip_expected()) {
                UmlArtifact * art = cl->associatedArtifact();

                if ((art != 0) && (Artifacts.value(art) == 0)) {
                    Artifacts.insert(art, art);
                    n += 1;
                }
            }
        }
    }

    if (n != 0) {
        Package::set_step(1, n);

        QHashIterator<UmlArtifact*,UmlArtifact*> iter(Artifacts);

        while (iter.hasNext()){
            iter.next();
            if(iter.value() != 0)
            ((UmlPackage *) iter.value()->parent()->parent())->get_package()->reverse(iter.value());
        }

        Package::set_step(1, -1);
    }
}

void UmlClassView::send_it(int n)
{
    if (n != 0) {
        Package::set_step(2, n);

        QHashIterator<UmlArtifact*,UmlArtifact*> iter(Artifacts);

        while (iter.hasNext()){
            iter.next();
            if(iter.value() != 0)
            ((UmlPackage *) iter.value()->parent()->parent())->get_package()->reverse(iter.value());
        }
        Package::set_step(2, -1);
    }
}

#endif
