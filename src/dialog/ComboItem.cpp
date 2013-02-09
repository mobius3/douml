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





#include <q3combobox.h>

#include "ComboItem.h"
#include "DialogUtil.h"

ComboItem::ComboItem(Q3Table * ta, const QString & s,
                     const QStringList & list, bool edit)
    : TableItem(ta, Q3TableItem::WhenCurrent, s), editable(edit), cb(0), types(list)
{
    if (editable)
        setReplaceable(FALSE);	// sinon le combo n est pas editable (!)
}

QWidget * ComboItem::createEditor() const
{
    ((ComboItem *) this)->cb = new Q3ComboBox(table()->viewport());
    // setEditable doit etre fait maintenant sinon les items sont perdus !
    cb->setEditable(editable);
    cb->setAutoCompletion(completion());
    cb->insertItem(text());
    cb->insertStringList(types);

    int index = types.findIndex(text());

    if (index != -1)
        cb->setCurrentItem(index + 1);

    return cb;
}

void ComboItem::setContentFromEditor(QWidget * w)
{
    Q3ComboBox * editor = qobject_cast<Q3ComboBox *>(w);

    if (editor)
        setText(editor->currentText());
    else
        Q3TableItem::setContentFromEditor(w);
}

