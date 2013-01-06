#ifndef _DIALOG_H
#define _DIALOG_H


#include <q3cstring.h>
#include "Language.h"

#include <qdialog.h>

class QLineEdit;
class QPushButton;
class QCheckBox;
class QComboBox;
class QRadioButton;

class Dialog : public QDialog
{
    Q_OBJECT
public:
    Dialog(Q3CString & path, Q3CString & encoding, Q3CString & genview, int & taggedvalue, Language & lang);


protected:
    Q3CString & _path;

    Q3CString & _encoding;

    Q3CString & _genview;

    int & _taggedvalue;

    Language & _lang;

    QCheckBox * gen_cb;

    QComboBox * encoding_cb;

    QRadioButton * tg_0;

    QRadioButton * tg_1;

    QRadioButton * tg_2;

    QLineEdit * ed;

protected slots:
    void browse();

    void accept_cpp();

    void accept_uml();

    void accept_java();

    void accept();

};

#endif
