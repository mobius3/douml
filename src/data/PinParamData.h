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

#ifndef PINPARAMDATA_H
#define PINPARAMDATA_H

#include <QTextStream>

#include "SimpleData.h"
#include "ObjectData.h"

struct PinParamData : public ObjectData {
    bool unique : 1;
    bool exception : 1;	// exclusive with stream
    bool stream : 1;
    int dummy : 4;
    UmlParamDirection dir : 8;
    UmlParamEffect effect : 8;

    PinParamData();
    PinParamData(PinParamData * model);

    UmlParamDirection get_dir() const {
        return dir;
    };
    UmlParamEffect get_effect() const {
        return effect;
    };
    bool get_is_unique() const {
        return unique;
    }
    bool get_is_exception() const {
        return exception;
    }
    bool get_is_stream() const {
        return stream;
    }

    void send_uml_def(ToolCom * com);
    bool tool_cmd(ToolCom * com, const char * args, BooL & ack);

    void save(QTextStream &, QString & warning) const;
    void read(char *& , char *&);
};

#endif
