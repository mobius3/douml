#ifndef OPERATIONFUNCS_H
#define OPERATIONFUNCS_H
#include <QString>
class BrowserOperation;
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

#endif // OPERATIONFUNCS_H
