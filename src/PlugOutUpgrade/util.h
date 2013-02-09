//Added by qt3to4:
#include "misc/mystr.h"
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

#ifndef UTIL_H
#define UTIL_H

extern void defGetField_(UmlClass * base, const char * where, const char * oper,
                         const char * field, UmlTypeSpec type,
                         const char * if_def, const char * end_if,
                         const char * descr, UmlOperation *& op);

extern void defSetField_(UmlClass * base, const char * where, const char * oper,
                         const char * field, UmlTypeSpec type,
                         const char * cmd, const char * if_def, const char * end_if,
                         const char * descr, UmlOperation *& op);

extern void defGet_(UmlClass * base, const char * where, const char * oper,
                    UmlTypeSpec type, const char * if_def, const char * end_if,
                    const char * descr, UmlOperation *& op);

extern void defSet_(UmlClass * base, const char * where, const char * oper,
                    UmlTypeSpec type, const char * cmd, const char * if_def,
                    const char * end_if, const char * descr, UmlOperation *& op);

extern void defGetPtr_(UmlClass * base, const char * where, const char * oper,
                       UmlTypeSpec type, const char * if_def, const char * end_if,
                       const char * descr, UmlOperation *& op);

extern void defSetPtr_(UmlClass * base, const char * where, const char * oper,
                       UmlTypeSpec type, const char * cmd, const char * if_def,
                       const char * end_if, const char * descr, UmlOperation *& op);

extern void defSetRefType_(UmlClass * base, const char * where, const char * oper,
                           UmlTypeSpec type, const char * cmd, const char * if_def,
                           const char * end_if, const char * descr, UmlOperation *& op);

extern void defGetValue_(UmlClass * base, const char * where, const char * oper,
                         UmlTypeSpec type, const char * if_def, const char * end_if,
                         const char * descr, UmlOperation *& op);

extern void defSetBool_(UmlClass * base, const char * where, const char * oper,
                        const char * cmd, const char * if_def, const char * end_if,
                        const char * descr, UmlOperation *& op);

extern void defSetEnum_(UmlClass * base, const char * where, const char * oper,
                        UmlTypeSpec type, const char * cmd, const char * if_def,
                        const char * end_if, const char * descr, UmlOperation *& op);

extern void defSetBoolBitField_(UmlClass * base, const char * where, const char * oper,
                                const char * cmd, const char * if_def, const char * end_if,
                                const char * descr, UmlOperation *& op);

#define defGetField(base, where, oper, field, type, if_def, end_if, descr) \
  defGetField_(base, #where, #oper, #field, type, if_def, end_if, descr, op)

#define defSetField(base, where, oper, field, type, cmd, if_def, end_if, descr) \
  defSetField_(base, #where, #oper, #field, type, #cmd, if_def, end_if, descr, op)

#define defGet(base, where, oper, type, if_def, end_if, descr) \
  defGet_(base, #where, #oper, type, if_def, end_if, descr, op)

#define defSet(base, where, oper, type, cmd, if_def, end_if, descr) \
  defSet_(base, #where, #oper, type, #cmd, if_def, end_if, descr, op)

#define defGetPtr(base, where, oper, type, if_def, end_if, descr) \
  defGetPtr_(base, #where, #oper, type, if_def, end_if, descr, op)

#define defSetPtr(base, where, oper, type, cmd, if_def, end_if, descr) \
  defSetPtr_(base, #where, #oper, type, #cmd, if_def, end_if, descr, op)

#define defSetRefType(base, where, oper, type, cmd, if_def, end_if, descr) \
  defSetRefType_(base, #where, #oper, type, #cmd, if_def, end_if, descr, op)

#define defGetBool(base, where, oper, if_def, end_if, descr) \
  defGetValue_(base, #where, #oper, "bool", if_def, end_if, descr, op)

#define defSetBool(base, where, oper, cmd, if_def, end_if, descr) \
  defSetBool_(base, #where, #oper, #cmd, if_def, end_if, descr, op)

#define defGetEnum(base, where, oper, type, if_def, end_if, descr) \
  defGetValue_(base, #where, #oper, type, if_def, end_if, descr, op)

#define defSetEnum(base, where, oper, type, cmd, if_def, end_if, descr) \
  defSetEnum_(base, #where, #oper, type, #cmd, if_def, end_if, descr, op)

#define defSetBoolBitField(base, where, oper, cmd, if_def, end_if, descr) \
  defSetBoolBitField_(base, #where, #oper, #cmd, if_def, end_if, descr, op)

extern void include_umlcom(UmlClass * cl);
extern void include_umlcom(UmlArtifact * art);
extern void add_assoc_diag_ops(UmlClass * base, UmlClass * diag);
extern void conditional(WrapperStr & s, const char * if_def,
                        const char * end_if);
extern WrapperStr java2Php(WrapperStr s);
extern WrapperStr java2Python(WrapperStr s);
extern WrapperStr cpp2Python(WrapperStr s);

#endif
