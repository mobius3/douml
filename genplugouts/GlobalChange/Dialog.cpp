
#include "Dialog.h"

#ifdef WIN32
#include <stdlib.h>
#endif

#include <qdir.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qlabel.h>
#include <HHBox.h>
#include <vvbox.h>
#include <qcheckbox.h>
#include <qradiobutton.h>
//#include <qhbuttongroup.h> //[jasa] has compiler errors.
//[jasa] including q3buttongroup.h instead seems to work.
#include <bbuttongroup.h>
#include "vgridbox.h"
#include "gridbox.h"
#include <qmessagebox.h>
#include <QByteArray>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QSettings>
#include "UmlCom.h"
#include "Context.h"
#include "UmlItem.h"

LineEdit::LineEdit(QWidget * parent) : QLineEdit(parent)
{
}

bool LineEdit::focusNextPrevChild(bool)
{
    return FALSE;
}

void LineEdit::keyPressEvent(QKeyEvent * e)
{
    if (!e->text().length())
        QLineEdit::keyPressEvent(e);
    else {
        switch (e->key()) {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            insert("\\n");
            break;

        case Qt::Key_Tab:
            insert("\\t");
            break;

        default:
            QLineEdit::keyPressEvent(e);
        }
    }
}

Dialog::Dialog() : QDialog(0)
{
    setModal(true);
    QVBoxLayout * vbox = new QVBoxLayout(this);
    VGridBox * gbox;
    BButtonGroup * bg;
    HHBox * htab;

    vbox->setMargin(5);

    gbox = new VGridBox(10,this,"Filters");
    vbox->addWidget(gbox);

    gbox->addWidget(htab = new HHBox(gbox));
    //htab->setMargin(5);

    htab->addWidget(new QLabel("filter 1 : ", htab));
    htab->addWidget(filter1_le = new LineEdit(htab));

    htab->addWidget(new QLabel("  ", htab));

    htab->addWidget(bg = new BButtonGroup(htab));
    //bg->setRadioButtonExclusive(TRUE);

    bg->addWidget(with1_rb = new QRadioButton("with", bg));
    bg->addWidget(new QRadioButton("without", bg));
    with1_rb->setChecked(TRUE);

    //

    gbox->addWidget(htab = new HHBox(gbox));
    //htab->setMargin(5);

    htab->addWidget(new QLabel("", htab));
    htab->addWidget(bg = new BButtonGroup(htab));
    //bg->setRadioButtonExclusive(TRUE);

    bg->addWidget(and12_rb = new QRadioButton("and", bg));
    bg->addWidget(new QRadioButton("or", bg));
    and12_rb->setChecked(TRUE);

    htab->addWidget(new QLabel("", htab));

    //

    gbox->addWidget(htab = new HHBox(gbox));
    //htab->setMargin(5);

    htab->addWidget(new QLabel("filter 2 : ", htab));
    htab->addWidget(filter2_le = new LineEdit(htab));

    htab->addWidget(new QLabel("  ", htab));

    htab->addWidget(bg = new BButtonGroup(htab));
    //bg->setRadioButtonExclusive(TRUE);

    bg->addWidget(with2_rb = new QRadioButton("with", bg));
    bg->addWidget(new QRadioButton("without", bg));
    with2_rb->setChecked(TRUE);

    //

    gbox->addWidget(htab = new HHBox(gbox));
    //htab->setMargin(5);

    htab->addWidget(new QLabel("", htab));
    htab->addWidget(bg = new BButtonGroup(htab));
    //bg->setRadioButtonExclusive(TRUE);

    bg->addWidget(and23_rb = new QRadioButton("and", bg));
    bg->addWidget(new QRadioButton("or", bg));
    and23_rb->setChecked(TRUE);

    htab->addWidget(new QLabel("", htab));

    //

    gbox->addWidget(htab = new HHBox(gbox));
    //htab->setMargin(5);

    htab->addWidget(new QLabel("filter 3 : ", htab));
    htab->addWidget(filter3_le = new LineEdit(htab));

    htab->addWidget(new QLabel("  ", htab));

    htab->addWidget(bg = new BButtonGroup(htab));
    //bg->setRadioButtonExclusive(TRUE);

    bg->addWidget(with3_rb = new QRadioButton("with", bg));
    bg->addWidget(new QRadioButton("without", bg));
    with3_rb->setChecked(TRUE);

    //
    //

    gbox = new VGridBox(2,this,"Stereotype" );
    vbox->addWidget(gbox);

    gbox->addWidget(htab = new HHBox(gbox));
    //htab->setMargin(5);

    htab->addWidget(bg = new BButtonGroup(htab));
    //bg->setRadioButtonExclusive(TRUE);

    bg->addWidget(any_rb = new QRadioButton("any", bg));
    bg->addWidget(is_rb = new QRadioButton("is", bg));
    bg->addWidget(isnot_rb = new QRadioButton("is not", bg));
    any_rb->setChecked(TRUE);
    htab->addWidget(stereotype_le = new QLineEdit(htab));

    //
    //

    gbox = new VGridBox(2,this,"Targets" );
    vbox->addWidget(gbox);

    gbox->addWidget(htab = new HHBox(gbox));
    //htab->setMargin(5);

    htab->addWidget(artifact_cb = new QCheckBox("artifact", htab));
    htab->addWidget(class_cb = new QCheckBox("class", htab));
    htab->addWidget(operation_cb = new QCheckBox("operation", htab));
    htab->addWidget(attribute_cb = new QCheckBox("attribute", htab));
    htab->addWidget(relation_cb = new QCheckBox("relation", htab));

    //
    //

    gbox = new VGridBox(2,this,"Languages");
    vbox->addWidget(gbox);

    gbox->addWidget(htab = new HHBox(gbox));
    //htab->setMargin(5);

    htab->addWidget(cpp_cb = new QCheckBox("C++", htab));
    htab->addWidget(java_cb = new QCheckBox("Java", htab));
    htab->addWidget(php_cb = new QCheckBox("Php", htab));
    htab->addWidget(python_cb = new QCheckBox("Python", htab));
    htab->addWidget(idl_cb = new QCheckBox("Idl", htab));

    //
    //

    GridBox * grid = new GridBox(2, this);
    vbox->addWidget(grid);
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel("current : ", grid));
    grid->addWidget(current_le  = new LineEdit(grid));

    grid->addWidget(new QLabel("new : ", grid));
    grid->addWidget(new_le  = new LineEdit(grid));

    //
    //

    htab = new HHBox(this);
    htab->setMargin(5);
    vbox->addWidget(htab);

    htab->addWidget(new QLabel(htab));
    QPushButton * replace;
    htab->addWidget(replace = new QPushButton("Replace", htab));
    htab->addWidget(new QLabel(htab));
    QPushButton * quit;
    htab->addWidget(quit = new QPushButton("Quit", htab));
    htab->addWidget(new QLabel(htab));

    QSize bs(replace->sizeHint());

    quit->setFixedSize(bs);

    connect(replace, SIGNAL(clicked()), this, SLOT(do_replace()));
    connect(quit, SIGNAL(clicked()), this, SLOT(reject()));

}

void Dialog::do_replace()
{
    Context ctx(digest(current_le->text()), digest(new_le->text()));

    const char * err =
        ctx.set_filters(digest(filter1_le->text()), digest(filter2_le->text()), digest(filter3_le->text()),
                        with1_rb->isChecked(), with2_rb->isChecked(), with3_rb->isChecked(),
                        and12_rb->isChecked(), and23_rb->isChecked());

    if (err != 0)
        QMessageBox::critical(this, "Global change", err);
    else {
        ctx.set_stereotype(QByteArray(stereotype_le->text().toLatin1()),//[jasa] change QString to QByteArray to const char* for QByteArray constructor.
                           is_rb->isChecked(), isnot_rb->isChecked());
        ctx.set_targets(artifact_cb->isChecked(), class_cb->isChecked(),
                        operation_cb->isChecked(), attribute_cb->isChecked(), relation_cb->isChecked());
        ctx.set_language(cpp_cb->isChecked(), java_cb->isChecked(), php_cb->isChecked(),
                         python_cb->isChecked(), idl_cb->isChecked());

        UmlCom::targetItem()->change(ctx);

        QString msg;
        int n_match = ctx.n_match();
        int n_err = ctx.n_err();

        if (n_match == 0)
            msg = "Not found !";
        else if (n_err == 0)
            msg.sprintf("%d replacements done", n_match);
        else
            msg.sprintf("%d replacements done,\n%d not done on read-only elements",
                        n_match - n_err, n_err);

        QMessageBox::information(this, "Global change", msg);
    }
}

QByteArray Dialog::digest(const QString s)
{
    QByteArray c = s.toLatin1();
    int index;

    index = 0;

    while ((index = c.indexOf("\\n", index)) != -1) {
        c.replace(index, 2, "\n");
        index += 1;
    }

    index = 0;

    while ((index = c.indexOf("\\t", index)) != -1) {
        c.replace(index, 2, "\t");
        index += 1;
    }

    index = 0;

    while ((index = c.indexOf("\r", index)) != -1) {
        c.remove(index, 1);
    }

    return c;
}

void Dialog::polish()
{
    QDialog::ensurePolished();
    QSize sz = size();

    // width = height
    resize(sz.height(), sz.height());

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "DoUML", "settings");
    settings.setIniCodec("UTF-8");
    int l, t, r, b;
    l = settings.value("Desktop/left", -1).toInt();
    r = settings.value("Desktop/right", -1).toInt();
    t = settings.value("Desktop/top", -1).toInt();
    b = settings.value("Desktop/bottom", -1).toInt();

    if(l != -1 && r != -1 && t != -1 && b != -1)
    {
      if (!((r == 0) && (t == 0) && (r == 0) && (b == 0)) &&
          !((r < 0) || (t < 0) || (r < 0) || (b < 0)) &&
          !((r <= l) || (b <= t)))
      {
        int cx = (r + l) / 2;
        int cy = (t + b) / 2;

        move(x() + cx - (x() + width() / 2), y() + cy - (y() + height() / 2));
      }
    }
}

