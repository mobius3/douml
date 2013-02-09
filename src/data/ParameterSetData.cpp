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





#include <qcursor.h>
//Added by qt3to4:
#include <QTextStream>
#include <Q3ValueList>

#include "ParameterSetData.h"
#include "ParameterSetDialog.h"
#include "BrowserPin.h"
#include "myio.h"
#include "ToolCom.h"
#include "mu.h"

ParameterSetData::ParameterSetData()
{
}

ParameterSetData::ParameterSetData(ParameterSetData * model, BrowserNode * bn)
    : SimpleData(model)
{
    browser_node = bn;
    set_pins(model->pins);
}

void ParameterSetData::set_pins(const Q3ValueList<BrowserPin *> & l)
{
    Q3ValueList<BrowserPin *>::Iterator iter;

    // disconnect old pins
    for (iter = pins.begin(); iter != pins.end(); iter++)
        disconnect((*iter)->get_data(), SIGNAL(deleted()), this, SLOT(check()));

    pins = l;

    // connect new pins
    for (iter = pins.begin(); iter != pins.end(); iter++)
        connect((*iter)->get_data(), SIGNAL(deleted()), this, SLOT(check()));
}

void ParameterSetData::check()
{
    // remove deleted items, note : can't disconnect
    Q3ValueList<BrowserPin *>::Iterator iter = pins.begin();

    while (iter != pins.end())
        if ((*iter)->deletedp())
            iter = pins.remove(iter);
        else
            iter++;
}

void ParameterSetData::edit()
{
    setName(browser_node->get_name());

    (new ParameterSetDialog(this))->show();
}

void ParameterSetData::send_uml_def(ToolCom * com, BrowserNode * bn,
                                    const QString & comment)
{
    SimpleData::send_uml_def(com, bn, comment);
    com->write_unsigned(pins.count());

    Q3ValueList<BrowserPin *>::ConstIterator iter = pins.begin();

    for (iter = pins.begin(); iter != pins.end(); iter++)
        (*iter)->write_id(com);
}

bool ParameterSetData::tool_cmd(ToolCom * com, const char * args,
                                BrowserNode * bn,
                                const QString & comment)
{
    if (((unsigned char) args[-1]) >= firstSetCmd) {
        if (!bn->is_writable() && !root_permission())
            com->write_ack(FALSE);
        else {
            switch ((unsigned char) args[-1]) {
            case replaceParameterCmd:
                // replace all the pins
            {
                unsigned n = com->get_unsigned(args);
                Q3ValueList<BrowserPin *> l;

                while (n--)
                    l.append((BrowserPin *) com->get_id(args));

                set_pins(l);
            }
            break;

            default:
                return BasicData::tool_cmd(com, args, bn, comment);
            }

            // ok case
            bn->modified();
            bn->package_modified();
            modified();
            com->write_ack(TRUE);
        }
    }
    else
        return BasicData::tool_cmd(com, args, bn, comment);

    return TRUE;
}

void ParameterSetData::save(QTextStream & st, QString & warning) const
{
    BasicData::save(st, warning);
    nl_indent(st);
    st << "pins";
    indent(+1);

    Q3ValueList<BrowserPin *>::ConstIterator iter = pins.begin();

    for (iter = pins.begin(); iter != pins.end(); iter++) {
        nl_indent(st);
        (*iter)->save(st, TRUE, warning);
    }

    indent(-1);
    nl_indent(st);
    st << "end";
}

void ParameterSetData::read(char *& st, char *& k)
{
    BasicData::read(st, k);	// updates k

    if (strcmp(k, "pins"))
        wrong_keyword(k, "pins");

    Q3ValueList<BrowserPin *> l;

    while (strcmp((k = read_keyword(st)), "end")) {
        BrowserPin * pa = BrowserPin::read(st, k, 0);

        if (pa != 0)
            l.append(pa);
    }

    set_pins(l);

    k = read_keyword(st);
}
