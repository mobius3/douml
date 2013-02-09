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

#include <qdir.h>
#include <QTextStream>
//Added by qt3to4:
#include "misc/mystr.h"

#include "UmlPackage.h"
#include "UmlCom.h"
#include "PhpSettings.h"
#include "util.h"

UmlPackage::UmlPackage(void * id, const WrapperStr & n)
    : UmlBasePackage(id, n)
{
    dir.read = FALSE;
}

static bool RootDirRead;
static WrapperStr RootDir;

static WrapperStr relative_path(const QDir & destdir, WrapperStr relto)
{
    QDir fromdir(relto);
    WrapperStr from = WrapperStr(fromdir.absPath().toAscii().constData());
    WrapperStr to = WrapperStr(destdir.absPath().toAscii().constData());
    const char * cfrom = from;
    const char * cto = to;
    int lastsep = -1;
    int index = 0;

    for (;;) {
        char f = cfrom[index];
        char t = cto[index];

        if (f == 0) {
            switch (t) {
            case 0:
                // same path
                return "";

            case '/':
                // to = .../aze/qsd/wxc, from = .../aze => qsd/wxc/
                return (cto + index + 1) + WrapperStr("/");

            default:
                // to = .../aze/qsd/wxc, from = .../az => ../aze/qsd/wxc/
                return "../" + WrapperStr(cto + lastsep + 1) + "/";
            }
        }
        else if (t == f) {
            if (t == '/')
                lastsep = index;

            index += 1;
        }
        else if (t == 0) {
            WrapperStr r;
            const char * p = cfrom + index;

            do {
                if (*p == '/')
                    r += "../";
            }
            while (*++p != 0);

            if (f == '/')
                // to = .../aze, from = .../aze/qsd/wxc => ../../
                return r;
            else
                // to = .../az, from = .../aze/qsd/wxc => ../../../az/
                return ("../"  + r + (cto + lastsep + 1)) + "/";
        }
        else {
            // to = .../aze, from = .../iop/klm => ../../aze/
            WrapperStr r = "../";
            const char * p = cfrom + lastsep + 1;

            while (*p != 0)
                if (*p++ == '/')
                    r += "../";

            return (r + (cto + lastsep + 1)) + "/";
        }
    }
}

WrapperStr UmlPackage::rootDir()
{
    if (! RootDirRead) {
        RootDirRead = TRUE;
        RootDir = PhpSettings::rootDir();

        if (!RootDir.isEmpty() && // empty -> error
            QDir::isRelativePath(RootDir)) {
            QFileInfo f(getProject()->supportFile());
            QDir d(f.dirPath());

            RootDir = d.filePath(RootDir);
        }
    }

    return RootDir;
}

WrapperStr UmlPackage::file_path(const WrapperStr & f, WrapperStr relto)
{
    if (!dir.read) {
        dir.file = phpDir();
        dir.file_absolute = FALSE;

        QDir d_root(rootDir());

        if (dir.file.isEmpty())
            dir.file = RootDir;
        else if (QDir::isRelativePath(dir.file))
            dir.file = d_root.filePath(dir.file);
        else
            dir.file_absolute = TRUE;

        if (dir.file.isEmpty()) {
            UmlCom::trace(WrapperStr("<font color=\"red\"><b><b> The generation directory "
                                    "must be specified for the package<i> ") + name()
                          + "</i>, edit the <i> generation settings</i> (tab 'directory') "
                          "or edit the package (tab 'Php')</b></font><br>");
            UmlCom::bye(n_errors() + 1);
            UmlCom::fatal_error("UmlPackage::file_path");
        }

        dir.read = TRUE;
    }

    if (f.isEmpty())
        return dir.file;

    QDir d(dir.file);

    if (! d.exists()) {
        // create directory including the intermediates
        WrapperStr s = dir.file;
        int index = 0;
        QChar sep = QDir::separator();

        if (sep != '/') {
            while ((index = s.find(sep, index)) != -1)
                s.replace(index++, 1, "/");
        }

        s = QDir::cleanDirPath(s) + "/";
        index = s.find("/");

        int index2;

        while ((index2 = s.find("/", index + 1)) != -1) {
            WrapperStr s2 = s.left(index2);
            QDir sd(s2);

            if (!sd.exists()) {
                if (!sd.mkdir(s2)) {
                    UmlCom::trace(WrapperStr("<font color=\"red\"><b> cannot create directory <i>")
                                  + s2 + "</i></b></font><br>");
                    UmlCom::bye(n_errors() + 1);
                    UmlCom::fatal_error("UmlPackage::file_path");
                }
            }

            index = index2;
        }
    }

    WrapperStr df = (dir.file_absolute || relto.isEmpty())
                   ? WrapperStr(d.filePath(f).toAscii().constData())
                   : relative_path(d, relto) + f;

    if (PhpSettings::isRelativePath() && (df[0] != '/') && (df[0] != '.'))
        df = "./" + df;

    return df + WrapperStr(".") + PhpSettings::sourceExtension();
}

WrapperStr UmlPackage::text_path(const WrapperStr & f)
{
    WrapperStr r = file_path(f);

    return r.left(r.length() - 1 - PhpSettings::sourceExtension().length());
}

void UmlPackage::generate()
{
    Q3PtrVector<UmlItem> ch = UmlItem::children();

    for (unsigned index = 0; index != ch.size(); index += 1)
        ch[index]->generate();
}

UmlPackage * UmlPackage::package()
{
    return this;
}

