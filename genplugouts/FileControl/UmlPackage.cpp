
#include "UmlPackage.h"

#include <stdlib.h>
#include <qfileinfo.h>
//Added by qt3to4:
#include <QByteArray>

#include "Dialog.h"
#include "UmlCom.h"

void UmlPackage::fileControl(bool ci)
{
    UmlPackage * prj = getProject();
    QByteArray prjfile = prj->supportFile();
    BooL rec;
    BooL reload;
    QByteArray cmd;

    if (! prj->propertyValue((ci) ? "check-in-cmd" : "check-out-cmd", cmd))
        cmd = "specify the command containing %file and %dir or %dironly";

    Dialog dialog(ci, cmd, rec, reload);	// the dialog execution set 'cmd' and 'rec'

    if (dialog.exec() == QDialog::Accepted) {
        // save the command for a future usage
        prj->set_PropertyValue((ci) ? "check-in-cmd" : "check-out-cmd", cmd);

        if (reload)
            saveProject();

        // get files list
        QHash<QString,void*> files;

        getFiles(files, (rec) ? ~0u : 1);

        if (this == prj)
            getAuxFiles(files);

        // apply the command on each file
        QHashIterator<QString,void*> it(files);
        QFileInfo prjpath(prjfile);
        QString dir = prjpath.path();
        QString dironly = dir;
        int index;

        if ((dironly.length() > 3) &&
            (dironly[1] == ':') &&
            (dironly[2] == '/'))
            dironly = dironly.mid(2);

        while ((index = cmd.indexOf("%dironly")) != -1)
            cmd.replace(index, 8, dironly.toLatin1());

        while ((index = cmd.indexOf("%dir")) != -1)
            cmd.replace(index, 4, dir.toLatin1());

        while (it.hasNext()) {
            it.next();
            QString s = cmd;

            while ((index = s.indexOf("%file")) != -1)
                s.replace(index, 5, it.key().toLatin1());

            system((const char *) s.toLatin1().constData());
            //++it;
        }

        UmlCom::trace("Done.");

        if (reload)
            loadProject(prjfile);
    }
}

void UmlPackage::getFiles(QHash<QString, void *> &files, unsigned rec)
{
    if (rec != 0)
        UmlItem::getFiles(files, rec - 1);
}

void UmlPackage::getAuxFiles(QHash<QString,void*> & files)
{
    static const char * aux[] = {
        "cpp_includes", "generation_settings", "idl_includes",
        "java_imports", "stereotypes", "tools", 0
    };

    const char ** p = aux;
    QFileInfo prjpath(supportFile());
    QString dir = prjpath.path() + "/";

    while (*p != 0) {
        QFileInfo fi(dir + *p);

        if (fi.exists())
            files.insert(*p, (void *) 1);

        p += 1;
    }
}

