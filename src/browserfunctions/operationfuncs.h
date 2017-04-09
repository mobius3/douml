#ifndef OPERATIONFUNCS_H
#define OPERATIONFUNCS_H
#include <QString>
class BrowserOperation;
class OperationData;

namespace OperationFuncs
{
void add_param(BrowserOperation* oper, QString & form, int rank, QString s);
void replace_param( QString & form, int rank, QString s);
void recompute_param(BrowserOperation* oper, int rank, bool recompute);
// automatic add / remove param when only one language is set
int bypass_string(const char * s, int index);
int bypass_char(const char * s, int index);
int bypass_cpp_comment(const char * s, int index);
int bypass_c_comment(const char * s, int index);
int supOf(const char * s, int index);
int param_begin(QString s, int rank);
void renumber(QString & form, int rank,
                     int delta, bool equal = FALSE);

void delete_param(int rank, OperationData *data);
QString delete_param(int rank, QString text);
void move_param(int old_rank, int new_rank);
void move_param(int old_rank, int new_rank,
                                 QString proto);

QString extract_specifier(int position, QString s);
QString extract_pointer(int position,  QString s);
QString set_specifier(int position,  QString s, QString newValue);
QString set_pointer(int position,  QString s, QString newValue);
}


#endif // OPERATIONFUNCS_H
