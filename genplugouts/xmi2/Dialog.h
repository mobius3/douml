#ifndef _DIALOG_H
#define _DIALOG_H



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
    Dialog(WrapperStr & path, WrapperStr & encoding, WrapperStr & nomodel, WrapperStr & genview, WrapperStr & uml20, WrapperStr & pk, WrapperStr & vis, WrapperStr & primitivetype, WrapperStr & genextension, WrapperStr & geneclipse, WrapperStr & commentexporter, WrapperStr & linefeed, Language & lang);


protected:
    WrapperStr & _path;

    WrapperStr & _encoding;

    WrapperStr & _nomodel;

    WrapperStr & _genview;

    //yes => generate pk_ prefix
    WrapperStr & _uml20;

    //yes => generate pk_ prefix
    WrapperStr & _pk;

    //yes => generate vis_ prefix
    WrapperStr & _vis;

    //yes => use primitiveType rather than dataType for int ...
    WrapperStr & _primitivetype;

    WrapperStr & _genextension;

    WrapperStr & _geneclipse;

    WrapperStr & _commentexporter;

    //yes => generate linefeed inside string, else &#10;
    WrapperStr & _linefeed;

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
