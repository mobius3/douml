#ifndef _DIALOG_H
#define _DIALOG_H


#include <QByteArray>
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
    Dialog(QByteArray & path, QByteArray & encoding, QByteArray & genview, int & taggedvalue, Language & lang);


protected:
    QByteArray & _path;

    QByteArray & _encoding;

    QByteArray & _genview;

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
