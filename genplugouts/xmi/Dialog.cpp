
#include "Dialog.h"

#include <stdlib.h>

#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qfiledialog.h>
#include <qfileinfo.h>
#include <qlabel.h>
#include <HHBox.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qradiobutton.h>
#include <bbuttongroup.h>
//Added by qt3to4:
#include <QByteArray>
#include <QVBoxLayout>

#include "SmallPushButton.h"

Dialog::Dialog(QByteArray & path, QByteArray & encoding, QByteArray & genview, int & taggedvalue, Language & lang)
    : QDialog(0), _path(path), _encoding(encoding), _genview(genview), _taggedvalue(taggedvalue), _lang(lang)
{
    QVBoxLayout * vbox = new QVBoxLayout(this);
    HHBox * htab;
    setModal(true);
    vbox->setMargin(5);

    // get xmi pathname

    htab = new HHBox(this);
    htab->setMargin(5);
    vbox->addWidget(htab);

    htab->addWidget(new QLabel("generated \nXMI file : ", htab));

    htab->addWidget(ed = new QLineEdit(htab));
    ed->setText(_path);

    htab->addWidget(new QLabel(" ", htab));

    SmallPushButton * br;
    htab->addWidget(br = new SmallPushButton("browse", htab));

    connect(br, SIGNAL(clicked()), this, SLOT(browse()));

    // to choose encoding

    htab = new HHBox(this);
    htab->setMargin(5);
    vbox->addWidget(htab);

    htab->addWidget(new QLabel("Encoding : ", htab));

    QString charset = getenv("BOUML_CHARSET");
    int index = 0;

    while ((index = charset.indexOf('_')) != -1) {
        charset[index] = '-';
        index += 1;
    }

    htab->addWidget(encoding_cb = new QComboBox(htab));
    encoding_cb->setEditable(true);
    encoding_cb->addItem(QString(_encoding));

    if (!charset.isEmpty() && (_encoding != charset.toLatin1()))
        encoding_cb->addItem(charset);

#ifdef WIN32

    if ((_encoding != "windows-1252") && (charset != "windows-1252"))
        encoding_cb->addItem("windows-1252");

    if ((_encoding != "ISO-8859-1") && (charset != "ISO-8859-1"))
        encoding_cb->addItem("ISO-8859-1");

#else

    if ((_encoding != "ISO-8859-1") && (charset != "ISO-8859-1"))
        encoding_cb->addItem("ISO-8859-1");

    if ((_encoding != "windows-1252") && (charset != "windows-1252"))
        encoding_cb->addItem("windows-1252");

#endif

    // generate view checkbox

    htab = new HHBox(this);
    htab->setMargin(5);
    vbox->addWidget(htab);

    htab->addWidget(gen_cb = new QCheckBox("Generate views as package", htab));

    if (_genview == "yes")
        gen_cb->setChecked(TRUE);

    // tagged value generation mode

    htab = new HHBox(this);
    htab->setMargin(5);
    vbox->addWidget(htab);

    BButtonGroup * bg;
    htab->addWidget(bg=
        new BButtonGroup(3, Qt::Vertical, "Tagged values generation", htab));

    bg->addWidget(tg_0 = new QRadioButton("Not generated", bg));
    bg->addWidget(tg_1 = new QRadioButton("<UML:TaggedValue tag=\"..\" value=\"..\"/>", bg));
    bg->addWidget(tg_2 = new QRadioButton("<UML:TaggedValue>\n"
                            "    <Uml:TaggedValue.tag>..</Uml:TaggedValue.tag>\n"
                            "    <Uml:TaggedValue.value>..</Uml:TaggedValue.value>\n"
                            "</UML:TaggedValue>",
                            bg));

    switch (taggedvalue) {
    case 1:
        tg_1->setChecked(TRUE);
        break;

    case 2:
        tg_2->setChecked(TRUE);
        break;

    default:
        tg_0->setChecked(TRUE);
        break;
    }

    // uml , c++, java, cancel buttons

    htab = new HHBox(this);
    htab->setMargin(5);
    vbox->addWidget(htab);

    htab->addWidget(new QLabel(htab));
    QPushButton * uml;
    htab->addWidget(uml = new QPushButton("&Uml", htab));
    htab->addWidget(new QLabel(htab));
    QPushButton * cpp;
    htab->addWidget(cpp = new QPushButton("&C++", htab));
    htab->addWidget(new QLabel(htab));
    QPushButton * java;
    htab->addWidget(java = new QPushButton("&Java", htab));
    htab->addWidget(new QLabel(htab));
    QPushButton * cancel;
    htab->addWidget(cancel = new QPushButton("&Cancel", htab));
    htab->addWidget(new QLabel(htab));
    QSize bs(cancel->sizeHint());

    uml->setFixedSize(bs);
    cpp->setFixedSize(bs);
    java->setFixedSize(bs);

    connect(uml, SIGNAL(clicked()), this, SLOT(accept_uml()));
    connect(cpp, SIGNAL(clicked()), this, SLOT(accept_cpp()));
    connect(java, SIGNAL(clicked()), this, SLOT(accept_java()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

void Dialog::browse()
{
    QString s = QFileDialog::getSaveFileName(0, "",_path, "*.xmi");

    if (! s.isEmpty()) {
        if (s.right(4).toLower() != ".xmi")
            ed->setText(s + ".xmi");
        else
            ed->setText(s);
    }
}

void Dialog::accept_cpp()
{
    _lang = Cpp;

    accept();
}

void Dialog::accept_uml()
{
    _lang = Uml;
    accept();
}

void Dialog::accept_java()
{
    _lang = Java;
    accept();
}

void Dialog::accept()
{
    _path = ed->text().toLatin1();
    _encoding = encoding_cb->currentText().toLatin1();
    _genview = (gen_cb->isChecked()) ? "yes" : "no";

    if (tg_0->isChecked())
        _taggedvalue = 0;
    else if (tg_1->isChecked())
        _taggedvalue = 1;
    else if (tg_2->isChecked())
        _taggedvalue = 2;

    QDialog::accept();
}

