// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
//
// This file is part of the BOUML Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// e-mail : bouml@free.fr
// home   : http://bouml.free.fr
//
// *************************************************************************

#ifndef SYNCHRODIALOG_H
#define SYNCHRODIALOG_H

#include <qdialog.h>
#include <q3ptrlist.h>
//Added by qt3to4:
#include <Q3PtrList>

class QCheckBox;
class BrowserView;

class SynchroDialog : public QDialog {
  Q_OBJECT
 
  protected:
    Q3PtrList<BrowserView> & browsers;
    Q3PtrList<QCheckBox> checks;
      
  public:
    SynchroDialog(Q3PtrList<BrowserView> & b);
    virtual ~SynchroDialog();
    
  public slots:
    virtual void accept();
};

#endif
