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





#include <qlayout.h>
#include <q3vbox.h>
#include <qlabel.h>
#include <qdir.h>
#include <q3filedialog.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>

#include "ImageDialog.h"
#include "DialogUtil.h"
#include "UmlDesktop.h"
#include "UmlWindow.h"
#include "BrowserView.h"
#include "translate.h"

QSize ImageDialog::previous_size;

static QString Absolute;
static QString RelativeRoot;
static QString RelativePrj;

ImageDialog::ImageDialog(QString & p)
    : QDialog(0, "Image dialog", TRUE), path(p)
{
    setCaption(TR("Image dialog"));

    Q3VBoxLayout * vbox = new Q3VBoxLayout(this);
    Q3HBoxLayout * hbox;

    vbox->setMargin(5);

    hbox = new Q3HBoxLayout(vbox);
    hbox->setMargin(5);

    hbox->addWidget(new QLabel(TR("Image path :"), this));
    hbox->addWidget(edpath = new LineEdit(path, this));

    RelativeRoot = TR("Set it relative to image root");
    RelativePrj = TR("Set it relative to project");
    Absolute = TR("Set it absolute");

    hbox->addWidget(new QLabel("", this));

    QPushButton * b = new SmallPushButton(TR("Browse"), this);

    hbox->addWidget(b);
    connect(b, SIGNAL(clicked()), this, SLOT(browse()));
    hbox->addWidget(new QLabel("", this));

    Q3VBox * vtab = new Q3VBox(this);

    hbox->addWidget(vtab);

    pathrootbutton = new SmallPushButton((path.isEmpty() || QDir::isRelativePath(path))
                                         ? Absolute : RelativeRoot, vtab);
    connect(pathrootbutton, SIGNAL(clicked()), this, SLOT(root_relative()));
    pathprjbutton = new SmallPushButton((path.isEmpty() || QDir::isRelativePath(path))
                                        ? Absolute : RelativePrj, vtab);
    connect(pathprjbutton, SIGNAL(clicked()), this, SLOT(prj_relative()));
    pathrootbutton->setEnabled(!UmlWindow::images_root_dir().isEmpty());
    hbox->addWidget(new QLabel("", this));

    //

    QPushButton * accept = new QPushButton(TR("&OK"), this);
    QPushButton * cancel = new QPushButton(TR("&Cancel"), this);
    QSize bs(cancel->sizeHint());

    accept->setDefault(TRUE);
    accept->setFixedSize(bs);
    cancel->setFixedSize(bs);

    hbox = new Q3HBoxLayout(vbox);

    hbox->addWidget(accept);
    hbox->addWidget(cancel);

    connect(accept, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

    UmlDesktop::setsize_center(this, previous_size, 0.7, 0.01);
}

ImageDialog::~ImageDialog()
{
    previous_size = size();
}

void ImageDialog::browse()
{
    QString s = edpath->text().simplifyWhiteSpace();
    const QString ns = Q3FileDialog::getOpenFileName(s, "", this, 0, TR("Select image"));

    if (! ns.isEmpty()) {
        edpath->setText(ns);
        pathrootbutton->setText(RelativeRoot);
        pathprjbutton->setText(RelativePrj);
    }
}

void ImageDialog::root_relative()
{
    QString root = UmlWindow::images_root_dir();

    if (root.isEmpty()) {
        pathrootbutton->setEnabled(FALSE);
        return;
    }

    const QString s = edpath->text();

    if (root.at(root.length() - 1) != QChar('/'))
        root += '/';

    if (pathrootbutton->text() == RelativeRoot) {
        int len = root.length();

        if (



            (s.find(root) == 0) &&

            (s.length() >= len)) {
            edpath->setText(s.mid(len));
            pathrootbutton->setText(Absolute);
            pathprjbutton->setText(Absolute);
        }
    }
    else {
        edpath->setText(root + s);
        pathrootbutton->setText(RelativeRoot);
        pathprjbutton->setText(RelativePrj);
    }
}

void ImageDialog::prj_relative()
{
    QString root = BrowserView::get_dir().absPath();
    const QString s = edpath->text();

    if (root.at(root.length() - 1) != QChar('/'))
        root += '/';

    if (pathprjbutton->text() == RelativePrj) {
        int len = root.length();

        if (



            (s.find(root) == 0) &&

            (s.length() >= len)) {
            edpath->setText(s.mid(len));
            pathrootbutton->setText(Absolute);
            pathprjbutton->setText(Absolute);
        }
    }
    else {
        edpath->setText(root + s);
        pathrootbutton->setText(RelativeRoot);
        pathprjbutton->setText(RelativePrj);
    }

    pathrootbutton->setEnabled(!UmlWindow::images_root_dir().isEmpty());
}

void ImageDialog::accept()
{
    path = edpath->text().simplifyWhiteSpace();
    QDialog::accept();
}
