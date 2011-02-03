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

#ifndef UMLPACKAGE_H
#define UMLPACKAGE_H

#include "UmlBasePackage.h"
//Added by qt3to4:
#include <Q3CString>
#include <QTextOStream>

struct Dir {
  Q3CString file;
  bool read;
};
 
class UmlPackage : public UmlBasePackage {
  public:
    UmlPackage(void * id, const Q3CString & n);
  
  protected:
    Dir dir;
  
  public:
    Q3CString file_path(const Q3CString &);
    Q3CString text_path(const Q3CString &);
    virtual void generate();
    virtual UmlPackage * package();
    void import(QTextOStream & f, const Q3CString & indent);
};

#endif
