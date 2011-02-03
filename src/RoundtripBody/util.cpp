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

#include <qstring.h>
//Added by qt3to4:
#include <Q3CString>

#include "util.h"
#include "UmlCom.h"

static Q3CString TraceHeader;
static bool Verbose = FALSE;

void set_verbose()
{
  Verbose = TRUE;
}

bool verbose()
{
  return Verbose;
}

void set_trace_header(Q3CString s)
{
  TraceHeader = s;
}

Q3CString get_trace_header()
{
  return TraceHeader;
}

void write_trace_header()
{
  if (!Verbose && !TraceHeader.isEmpty()) {
    UmlCom::trace("<hr>" + TraceHeader);
    TraceHeader = "";
  }
}

//

static int NErrors;

void incr_error()
{
  NErrors += 1;
}

int n_errors()
{
  return NErrors;
}
