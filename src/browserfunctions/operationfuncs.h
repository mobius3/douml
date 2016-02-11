// *************************************************************************
//
//
//
// This file is part of the Douml Uml Toolkit.
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
//
// *************************************************************************

#ifndef OPERATIONFUNCS_H
#define OPERATIONFUNCS_H

#include <QString>

class BrowserOperation;
class OperationData;

namespace OperationFuncs
{

void add_param(BrowserOperation* oper, QString& form, int rank, const QString& s);
void replace_param(QString & form, int rank, const QString& s);
void recompute_param(BrowserOperation* oper, int rank, bool recompute);
// automatic add / remove param when only one language is set
int bypass_string(const char* s, int index);
int bypass_char(const char* s, int index);
int bypass_cpp_comment(const char* s, int index);
int bypass_c_comment(const char* s, int index);
int supOf(const char* s, int index);
int param_begin(const QString& s, int rank);
void renumber(QString& form, int rank,
              int delta, bool equal = FALSE);

void delete_param(int rank, OperationData* data);
QString delete_param(int rank, const QString& text);
void move_param(int old_rank, int new_rank);
void move_param(int old_rank, int new_rank,
                const QString& proto);

QString extract_specifier(int position, const QString& s);
QString extract_pointer(int position, const QString& s);
QString set_specifier(int position, const QString& s, const QString& newValue);
QString set_pointer(int position, const QString& s, const QString& newValue);

} // namespace OperationFuncs

#endif // OPERATIONFUNCS_H
