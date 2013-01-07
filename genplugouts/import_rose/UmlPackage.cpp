
#include "UmlPackage.h"
#include "UmlArtifact.h"

#include <q3filedialog.h>
//Added by qt3to4:
#include <Q3CString>

#include "File.h"
#include "UmlCom.h"
#include "UmlClassView.h"
#include "UmlUseCaseView.h"
#include "UmlDeploymentView.h"
#include "Artifact.h"

void UmlPackage::roseImport()
{
    QString s = Q3FileDialog::getOpenFileName(QString::null, "*.mdl", 0);

    if (!s.isEmpty()) {
        File f(s, "");

        if (! f.open(QIODevice::ReadOnly)) {
            UmlCom::trace("<br>cannot open " + s);
            throw 0;
        }

        UmlItem * prj = this;

        while (prj->parent() != 0)
            prj = prj->parent();

        prj->set_childrenVisible(FALSE);

        try {
            UmlCom::message("Phase 1");
            scanning = TRUE;

            while (import(f))
                ;

            scanning = FALSE;
            UmlCom::message("Phase 2");
            f.rewind();

            while (import(f))
                ;
        }
        catch (...) {
            set_childrenVisible(TRUE);
            throw 0;
        }

        set_childrenVisible(TRUE);
    }
}

Q3CString UmlPackage::fullName()
{
    return (this == getProject()) ? name() : UmlItem::fullName();
}

void UmlPackage::subArtifacts(Q3PtrList<UmlArtifact> & l, Q3CString name, Q3CString deplview_name)
{
    UmlDeploymentView * deplview;

    for (deplview = _deplviews.first(); deplview != 0; deplview = _deplviews.next()) {
        if (deplview->baseName() == deplview_name) {
            const Q3PtrVector<UmlItem> ch = deplview->children();
            unsigned i;

            for (i = 0; i != ch.size(); i += 1) {
                UmlItem * it = ch[i];

                if ((it->kind() == anArtifact) && (it->name() == name))
                    l.append((UmlArtifact *) it);
            }
        }
    }

}

void UmlPackage::subDeplViews(Q3PtrList<UmlDeploymentView> & l, Q3CString s)
{
    UmlDeploymentView * deplview;

    for (deplview = _deplviews.first(); deplview != 0; deplview = _deplviews.next())
        if (deplview->baseName() == s)
            l.append(deplview);
}

UmlPackage * UmlPackage::addPackage(Q3CString s)
{
    UmlPackage * r;

    while ((r = UmlPackage::create(this, s)) == 0)
        s += "_";

    return r;
}

UmlDeploymentView * UmlPackage::addDeplView(Q3CString s, UmlPackage * p)
{
    UmlDeploymentView * dpv;
    Q3CString bn = s;

    while ((dpv = UmlDeploymentView::create(p, s, bn)) == 0)
        s += '_';

    _deplviews.append(dpv);

    return dpv;
}

bool UmlPackage::import(File & f)
{
    Q3CString s;

    switch (f.read(s)) {
    case -1:
        return FALSE;

    case '(':
        break;

    default:
        f.syntaxError(s);
    }

    if ((f.read(s) != ATOM) || (s != "object"))
        f.syntaxError(s, "object");

    if (f.read(s) != ATOM)
        f.syntaxError(s);

    if (s == "Design") {
        f.read(s);	// "Logical View"

        for (;;) {
            switch (f.read(s)) {
            case ATOM:
                break;

            case ')':
                return TRUE;

            case -1:
                f.eof();
                throw 0;

            default:
                f.syntaxError(s, "an atom");
            }

            if (s == "root_usecase_package")
                readUseCaseView(f);
            else if (s == "root_category")
                readClassView(f);
            else if (s == "root_subsystem")
                readComponentView(f);
            else if (s == "process_structure")
                readDeploymentView(f);
            else {
#ifdef DEBUGROSE

                if (s != "properties")
                    UmlCom::trace("<br>import does not manage '" + s + "'");

#endif
                f.skipNextForm();
            }
        }

        return TRUE;
    }
    else if (s == "Petal") {
        f.skipBlock();
        return TRUE;
    }
    else {
        UmlCom::trace("<br>" + s + " : not yet managed " + f.context());
        throw 0;
    }
}

void UmlPackage::readUseCaseView(File & f)
{
    f.read("(");
    f.read("object");
    f.read("Class_Category");

    UmlUseCaseView::import(this, f);
}

void UmlPackage::readClassView(File & f)
{
    f.read("(");
    f.read("object");
    f.read("Class_Category");

    UmlClassView::import(this, f);
}

void UmlPackage::readComponentView(File & f)
{
    if (scanning) {
        f.read("(");
        f.read("object");
        f.read("SubSystem");
        Artifact::import_component_view(f);
    }
    else
        f.skipNextForm();
}

void UmlPackage::readDeploymentView(File & f)
{
    f.read("(");
    f.read("object");
    f.read("Processes");

    UmlDeploymentView::import(this, f);
}

