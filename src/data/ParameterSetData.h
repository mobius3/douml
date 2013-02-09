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

#ifndef PARAMETERSETDATA_H
#define PARAMETERSETDATA_H

#include <QTextStream>
#include <q3valuelist.h>

#include "SimpleData.h"

class BrowserPin;
class ToolCom;
class BrowserNode;

class ParameterSetData : public SimpleData
{
    Q_OBJECT

    friend class ParameterSetDialog;

protected:
    Q3ValueList<BrowserPin *> pins;

public:
    ParameterSetData();
    ParameterSetData(ParameterSetData * model, BrowserNode * bn);

    const Q3ValueList<BrowserPin *> & get_pins() const {
        return pins;
    }

    void edit();

    void send_uml_def(ToolCom * com, BrowserNode * bn,
                      const QString & comment);
    bool tool_cmd(ToolCom * com, const char * args,
                  BrowserNode * bn, const QString & comment);

    void save(QTextStream &, QString & warning) const;
    void read(char *& , char *&);

protected:
    void set_pins(const Q3ValueList<BrowserPin *> & l);

protected slots:
    void check();
};

#endif
