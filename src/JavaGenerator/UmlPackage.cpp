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
#include <QTextStream>

#include "UmlPackage.h"
#include "UmlCom.h"
#include "JavaSettings.h"
#include "UmlArtifact.h"
#include "util.h"

UmlPackage::UmlPackage(void * id, const WrapperStr & n)
    : UmlBasePackage(id, n)
{
    dir.read = FALSE;
}

static bool RootDirRead;
static WrapperStr RootDir;

WrapperStr UmlPackage::file_path(const WrapperStr & f)
{
    if (!dir.read) {
        dir.file = javaDir();

        if (! RootDirRead) {
            RootDirRead = TRUE;
            RootDir = JavaSettings::rootDir();

            if (!RootDir.isEmpty() && // empty -> error
                QDir::isRelativePath(RootDir)) {
                QFileInfo f(getProject()->supportFile());
                QDir d(f.dirPath());

                RootDir = d.filePath(RootDir);
            }
        }

        QDir d_root(RootDir);

        if (dir.file.isEmpty())
            dir.file = RootDir;
        else if (QDir::isRelativePath(dir.file))
            dir.file = d_root.filePath(dir.file);

        if (dir.file.isEmpty()) {
            UmlCom::trace(WrapperStr("<font color=\"red\"><b><b> The generation directory "
                                    "must be specified for the package<i> ") + name()
                          + "</i>, edit the <i> generation settings</i> (tab 'directory') "
                          "or edit the package (tab 'Java')</b></font><br>");
            UmlCom::bye(n_errors() + 1);
            UmlCom::fatal_error("UmlPackage::file_path");
        }

        dir.read = TRUE;
    }

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

    return WrapperStr(d.filePath(f).toAscii().constData()) + WrapperStr(".") +
           JavaSettings::sourceExtension();
}

WrapperStr UmlPackage::text_path(const WrapperStr & f)
{
    WrapperStr r = file_path(f);

    return r.left(r.length() - 1 - JavaSettings::sourceExtension().length());
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

void UmlPackage::import(QTextStream & f, const WrapperStr & indent)
{
    WrapperStr s = javaPackage();

    if (!s.isEmpty()) {
        s += ".*";

        if (! UmlArtifact::generated_one()->is_imported(s)) {
            f << indent << "import " << s << ";\n";
            UmlArtifact::generated_one()->imported(s);
        }
    }
}
