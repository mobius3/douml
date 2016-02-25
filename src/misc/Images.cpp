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
////
#include <qdir.h>
#include <qimage.h>
#include <QPixmap>
#include "Images.h"
#include "UmlWindow.h"
#include "BrowserView.h"
#include "translate.h"
#include "DialogUtil.h"

// all the pixmap for diagram with scale 100, key = path,
static QMap<QString, QPixmap*> DiagramPixmap;

// all the pixmap for diagram, key = path,
// value is QPtrDict with key = width
static QMap<QString, QMap<void*,QPixmap*> *> DiagramScaledPixmap;

// return pixmap for zoom 100%
QPixmap * get_pixmap(QString path)
{
    QPixmap * px = DiagramPixmap.value(path);

    if (px == 0) {
        QString abspath;

        if (!QDir::isRelativePath(path))
            abspath = path;
        else if ((UmlWindow::images_root_dir().isEmpty() ||
                  !QFile::exists(abspath = QDir::cleanPath(UmlWindow::images_root_dir() + '/' + path))) &&
                 !QFile::exists(abspath = path))
            abspath = BrowserView::get_dir().absoluteFilePath(path);

        px = new QPixmap(abspath);

        DiagramPixmap.insert(path, px);

        if (px->isNull()) {
            msg_critical(QObject::tr("Error"),
                         QString(path) + QObject::tr("\ndoesn't exist or is not a know image format"));
            return 0;
        }

        DiagramScaledPixmap.insert(path, new QMap<void*,QPixmap*>());
    }

    return (px->isNull()) ? 0 : px;
}

// return pixmap for a given zoom != 100
QPixmap * get_pixmap(QString path, double zoom)
{
    QPixmap * px = get_pixmap(path);

    if (px == 0)
        return 0;

    if (((int)(zoom * 100)) == 100)
        return px;

    QMap<void*,QPixmap*> * d = DiagramScaledPixmap[path]; // != 0
    intptr_t scaled_w = static_cast<intptr_t>(px->width() * zoom);
    void * k = (void *) scaled_w;
    QPixmap * scaled_px = d->value(k);

    if (scaled_px == 0) {
        QImage img =
            px->toImage().scaled(scaled_w, (int)(px->height() * zoom));

        scaled_px = new QPixmap();
        scaled_px->convertFromImage(img);
        d->insert(k, scaled_px);
    }

    return scaled_px;
}

void init_images()
{
    //DiagramPixmap.setAutoDelete(TRUE);


    QList<QPixmap*> pList = DiagramPixmap.values();
    while(!pList.isEmpty())
        delete pList.takeFirst();
    DiagramPixmap.clear();

    //DiagramScaledPixmap.setAutoDelete(TRUE);


    QList<QMap<void*,QPixmap*> *> pSList = DiagramScaledPixmap.values();
    while(!pSList.isEmpty())
        delete pSList.takeFirst();

    DiagramScaledPixmap.clear();
}
