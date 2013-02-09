// *************************************************************************cr();
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

#ifndef ACTIVITYPARTITIONDATA_H
#define ACTIVITIPARTITIONDATA_H

#include "SimpleData.h"
#include "InfoData.h"
//Added by qt3to4:
#include <QTextStream>

class QTextStream;

class BrowserActivityPartition;
class ActivityPartitionDialog;

class ActivityPartitionData : public SimpleData
{
    friend class ActivityPartitionDialog;

protected:
    bool is_dimension;
    bool is_external;
    BrowserNode * represents;

    virtual void send_uml_def(ToolCom * com, BrowserNode * bn,
                              const QString & comment);

public:
    ActivityPartitionData();
    ActivityPartitionData(ActivityPartitionData * model, BrowserNode * br);
    virtual ~ActivityPartitionData();

    bool get_is_dimension() const {
        return is_dimension;
    }
    bool get_is_external() const {
        return is_external;
    }
    BrowserNode * get_represents() const {
        return represents;
    }

    virtual bool tool_cmd(ToolCom * com, const char * args,
                          BrowserNode * bn, const QString & comment);

    void save(QTextStream &, QString & warning) const;
    void read(char *& st, char *& k);
    void post_load();
};

#endif
