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

class Dialog : public QDialog {
  Q_OBJECT
  public:
    Dialog(Q3CString & path, Q3CString & encoding, Q3CString & nomodel, Q3CString & genview, Q3CString & uml20, Q3CString & pk, Q3CString & vis, Q3CString & primitivetype, Q3CString & genextension, Q3CString & geneclipse, Q3CString & commentexporter, Q3CString & linefeed, Language & lang);


  protected:
    Q3CString & _path;

    Q3CString & _encoding;

    Q3CString & _nomodel;

    Q3CString & _genview;

    //yes => generate pk_ prefix
    Q3CString & _uml20;

    //yes => generate pk_ prefix
    Q3CString & _pk;

    //yes => generate vis_ prefix
    Q3CString & _vis;

    //yes => use primitiveType rather than dataType for int ...
    Q3CString & _primitivetype;

    Q3CString & _genextension;

    Q3CString & _geneclipse;

    Q3CString & _commentexporter;

    //yes => generate linefeed inside string, else &#10;
    Q3CString & _linefeed;

    Language & _lang;

    QLineEdit * ed;

    QRadioButton * uml20_rb;

    QRadioButton * uml21_rb;

    QComboBox * encoding_cb;

    QCheckBox * nomodel_cb;

    QCheckBox * genview_cb;

    QCheckBox * pk_cb;

    QCheckBox * vis_cb;

    QCheckBox * primitivetype_cb;

    QCheckBox * genextension_cb;

    QCheckBox * geneclipse_cb;

    QCheckBox * commentexporter_cb;

    QCheckBox * linefeed_cb;

  protected slots:
    virtual void polish();

    void browse();

    void accept_cpp();

    void accept_uml();

    void accept_java();

    void accept();

};

#endif
