
#include "UmlPackage.h"
#include "UmlItem.h"
#include "UmlClassView.h"
#include "UmlComponentView.h"
#include "UmlDeploymentView.h"
#include "UmlUseCaseView.h"

#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <q3filedialog.h>
#include <qapplication.h>
//Added by qt3to4:
#include "misc/mystr.h"
#include <Q3ValueList>

#include "UmlCom.h"
#include "FileIn.h"
#include "Token.h"
#include "UmlUseCase.h"
#include "UmlClass.h"
#include "UmlState.h"
#include "UmlActivity.h"
#include "UmlComponent.h"
#include "UmlArtifact.h"
#include "UmlNode.h"
#include "UmlFlow.h"
#include "UmlTransition.h"
#include "Binding.h"
#include "ClassInstance.h"
#include "Manifestation.h"
#include "UmlNcRelation.h"

void UmlPackage::import(QString path)
{
    bool manual = path.isEmpty();

    if (manual)
        path = Q3FileDialog::getOpenFileName(QString::null, QString::null, 0, 0, "open xmi/xml file");

    if (! path.isEmpty()) {
        // note : QTextStream(FILE *) bugged under windows
        FILE * fp = fopen(path, "rb");

        if (fp == 0)
            UmlCom::trace("cannot open " + path);
        else {
            QString s = "import " + path + "<br>";

            UmlCom::trace(s);

            FileIn in(path, fp);

            getProject()->set_childrenVisible(FALSE);

            init();
            importHeader(in);

            UmlCom::trace(WrapperStr("<br><font face=helvetica>xmi import done<br><br>") +
                          WrapperStr("<font face=helvetica> ") +
                          WrapperStr().setNum(numberOf() - 1) + WrapperStr(" packages </font><br>") +
                          WrapperStr("<font face=helvetica> ") +
                          WrapperStr().setNum(UmlUseCase::numberOf()) + WrapperStr(" use cases </font><br>") +
                          WrapperStr("<font face=helvetica> ") +
                          WrapperStr().setNum(UmlClass::numberOf()) + WrapperStr(" classes </font><br>") +
                          WrapperStr("<font face=helvetica> ") +
                          WrapperStr().setNum(UmlActivity::numberOf()) + WrapperStr(" activities </font><br>") +
                          WrapperStr("<font face=helvetica> ") +
                          WrapperStr().setNum(UmlState::numberOf()) + " states </font><br>" +
                          WrapperStr("<font face=helvetica> ") +
                          WrapperStr().setNum(UmlComponent::numberOf()) + WrapperStr(" components </font><br>") +
                          WrapperStr("<font face=helvetica> ") +
                          WrapperStr().setNum(UmlArtifact::numberOf()) + WrapperStr(" artifacts </font><br>") +
                          WrapperStr("<font face=helvetica> ") +
                          WrapperStr().setNum(UmlNode::numberOf()) + WrapperStr(" deployment nodes </font><br>") +
                          WrapperStr("<font face=helvetica> ") +
                          WrapperStr().setNum(UmlPackage::numberOfProfile()) + WrapperStr(" profiles </font><br>") +
                          WrapperStr("<font face=helvetica> ") +
                          WrapperStr().setNum(UmlClass::numberOfStereotype()) + WrapperStr(" stereotypes </font><br><br>"));

            if (manual)
                getProject()->set_childrenVisible(TRUE);
        }
    }
}

void UmlPackage::importHeader(FileIn & in)
{
    Token & tk = in.read();

    if (tk.what() != "xml")
        in.error("xml version expected");

    if (tk.valueOf("version") != "1.0") {
        UmlCom::trace("Only import xml 1.0");
        return;
    }

    in.setEncoding(tk.valueOf("encoding"));

    (void) in.read();	// update tk

    if (tk.what() == "xmi:xmi") {
        WrapperStr ver = tk.valueOf("xmi:version");

        if (ver.isEmpty())
            UmlCom::trace("warning : unknown xmi version<br><br>");
        else if (ver != "2.1")
            UmlCom::trace("warning : imported file is not xmi 2.1<br><br>");

        FromEclipse =
            // for instance RSA Eclipse xmi export
            !tk.valueOf("xmlns:ecore").isEmpty();

        if (FromEclipse)
            UmlCom::trace("xmi file produced under <b>Eclipse</b><br><br>");

        // read all before stereotype use
        WrapperStr prof_st;
        Q3ValueList<WrapperStr> base_v;

        while ((void) in.read(), !tk.close("xmi:xmi")) {
            if (UmlClass::isAppliedStereotype(tk, prof_st, base_v))
                break;

            UmlCom::targetItem()->import(in, tk);
        }

        solveRefs();

        if (NumberOfProfile != 0)
            // to take into account inheritances
            updateProfiles();

        // read stereotype use
        while (!tk.close("xmi:xmi")) {
            applyStereotype(in, tk);
            (void) in.read();
        }
    }
    else if ((tk.what() == "uml:model") || (tk.what() == "uml:profile")) {
        // Borland Together 2006 for Eclipse
        // Visual Paradigm for UML 6.1
        // RSA Eclipse (profile)
        WrapperStr ver = tk.valueOf("xmi:version");

        if (ver.isEmpty())
            UmlCom::trace("warning : unknown xmi version<br><br>");
        else if (ver != "2.1")
            UmlCom::trace("warning : imported file is not xmi 2.1<br><br>");

        FromEclipse =
            // .uml
            !tk.valueOf("xmlns:ecore").isEmpty();

        if (FromEclipse)
            UmlCom::trace("xmi file produced under <b>Eclipse</b><br><br>");

        UmlCom::targetItem()->import(in, tk);

        solveRefs();

        if (NumberOfProfile != 0)
            updateProfiles();
    }
    else
        in.error("uml:model or uml:profile or xmi:xmi expected, nothing imported");
}

UmlItem * UmlPackage::container(anItemKind kind, Token & token, FileIn & in)
{
    switch (kind) {
    case aClass:
    case aClassInstance:
    case aState:
    case anActivity:
        if (_classview == 0)
            _classview = UmlClassView::create(this,
                                              (stereotype() == "profile")
                                              ? "Stereotype View" : "Class View");

        return _classview;

    case anUseCase:
        if (_usecaseview == 0)
            _usecaseview = UmlUseCaseView::create(this, "Use Case View");

        return _usecaseview;

    case aComponent:
        if (_compview == 0)
            _compview = UmlComponentView::create(this, "Component View");

        return _compview;

    case aNode:
    case anArtifact:
        if (_deplview == 0)
            _deplview = UmlDeploymentView::create(this, "Deployment View");

        return _deplview;

    default:
        in.bypass(token);
        return 0;
    }
}

void UmlPackage::importIt(FileIn & in, Token & token, UmlItem * where)
{
    while (where->kind() != aPackage)
        where = where->parent();

    WrapperStr s = token.valueOf("name");

    if (s.isEmpty()) {
        static unsigned n = 0;

        s.sprintf("anonymous %u", ++n);
    }

    UmlPackage * pack = create((UmlPackage *) where, s);

    if (pack == 0)
        in.error("cannot create package '" + s + "' in '" + where->name() + "'");

    bool profile =
        (token.what() == "uml:profile") || (token.xmiType() == "uml:Profile");

    if (profile) {
        pack->set_Stereotype("profile");
        pack->set_PropertyValue("xmiId", token.xmiId());
        NumberOf -= 1;
        NumberOfProfile += 1;

        if (!(s = token.valueOf("metamodelreference")).isEmpty())
            pack->set_PropertyValue("metamodelReference", s);

        if (!(s = token.valueOf("metaclassreference")).isEmpty())
            pack->set_PropertyValue("metaclassReference", s);
    }

    s = token.xmiId();

    if (!s.isEmpty()) {
        pack->addItem(s, in);

        if (! token.closed()) {
            WrapperStr k = token.what();
            const char * kstr = k;

            if (profile) {
                while (in.read(), !token.close(kstr)) {
                    if ((token.what() == "packagedelement") &&
                        (token.xmiType() == "uml:Extension")) {
                        if (! token.closed())
                            in.finish(token.what());
                    }
                    else if (token.what() == "packageimport")
                        pack->packageImport(in, token);
                    else
                        pack->UmlItem::import(in, token);
                }

                updateProfiles();
            }
            else
                while (in.read(), !token.close(kstr))
                    pack->UmlItem::import(in, token);
        }
    }
    else if (! token.valueOf("href", s))
        in.error("xmi:id is missing"); // doesn't return
    else {
        in.warning("bypass external package " + s);

        if (! token.closed())
            in.finish(token.what());
    }

    pack->unload(TRUE, FALSE);
}

void UmlPackage::appliedProfile(FileIn & in, Token & token, UmlItem *)
{
    if (! token.closed()) {
        WrapperStr k = token.what();
        const char * kstr = k;

        while (in.read(), !token.close(kstr)) {
            if (token.what() == "appliedprofile") {
                WrapperStr s = token.valueOf("href");

                importProfile(in, s);
            }

            if (! token.closed())
                in.finish(token.what());
        }
    }

}

void UmlPackage::init()
{
    declareFct("uml:model", "uml:Model", &importIt);
    declareFct("packagedelement", "uml:Package", &importIt);
    declareFct("ownedmember", "uml:Package", &importIt);
    declareFct("ownedmember", "uml:Model", &importIt); // magic draw
    declareFct("packagedelement", "uml:Profile", &importIt);
    declareFct("ownedmember", "uml:Profile", &importIt);

    declareFct("uml:package", "", &importIt);

    declareFct("uml:model", "", &importIt);

    declareFct("uml:profile", "", &importIt);
    declareFct("profileapplication", "", &appliedProfile);
    declareFct("profileapplication", "uml:ProfileApplication", &appliedProfile);

    //

    UmlItem::init();
    UmlUseCase::init();
    UmlClass::init();
    UmlState::init();
    UmlActivity::init();
    UmlComponent::init();
    UmlNode::init();
    UmlArtifact::init();
}

void UmlPackage::applyStereotype(FileIn & in, Token & token)
{
    WrapperStr prof_st;
    Q3ValueList<WrapperStr> base_v;
    WrapperStr s;

    if (UmlClass::isAppliedStereotype(token, prof_st, base_v)) {
        WrapperStr s;
        Q3ValueList<WrapperStr>::Iterator it_ext;

        for (it_ext = base_v.begin(); it_ext != base_v.end(); ++it_ext) {
            WrapperStr s2;

            if (token.valueOf(*it_ext, s2)) {
                if (s.isEmpty())
                    s = s2;
                else if (s != s2)
                    in.warning("doesn't refer to the same element ('" + s + "' != '" + s2 + "')");
            }
        }

        if (s.isEmpty())
            in.warning("value of 'base_...' is missing");
        else {
            UmlItem * elt = All[s];

            if (elt == 0) {
                if (!FileIn::isBypassedId(s))
                    in.warning("unknown reference '" + s + "'");
            }
            else {
                elt->set_Stereotype(prof_st);
                elt->UmlItem::applyStereotype();	// set properties

                Q3Dict<WrapperStr> props = elt->properties();
                Q3DictIterator<WrapperStr> it(props);

                while (it.current()) {
                    WrapperStr k = it.currentKey().latin1();

                    if (token.valueOf(k.mid(k.operator QString().indexOf(':') + 1).lower(), s))
                        elt->set_PropertyValue(k, s);

                    ++it;
                }
            }
        }

        if (! token.closed())
            in.finish(token.what());
    }
    else
        in.bypass(token);

}

UmlPackage * UmlPackage::importProfile(FileIn & in, WrapperStr href)
{
    if (!href.isEmpty() && (href.left(5) != "http:") && (href.left(8) != "pathmap:")) {
        int index = href.find('#');

        if (index != -1) {
            WrapperStr id = href.mid(index + 1);
            QMap<QString, UmlItem *>::Iterator it = All.find(id);

            if (it == All.end()) {
                UmlPackage * pf = getProject()->findProfile(id);

                if (pf == 0) {
                    QFileInfo fi(in.path());
                    QDir d(fi.dir(TRUE));
                    QString fn = d.absFilePath(href.left(index));

                    if (QFile::exists(fn)) {
                        WrapperStr cmd = qApp->argv()[0] + WrapperStr(" ") + WrapperStr((const char *)fn); //[rageek] ambiguous, cast
                        int pid = UmlCom::targetItem()->apply(cmd);

                        while (isToolRunning(pid)) {
#ifdef WIN32
                            Sleep(1000);
#else
                            sleep(1);
#endif
                        }

                        UmlCom::targetItem()->unload(FALSE, FALSE); // to reread children

                        if ((pf = ((UmlPackage *) UmlCom::targetItem())->findProfile(id)) != 0)
                            // not in Bouml case
                            pf->loadFromProfile();
                    }
                    else
                        in.warning("can't open " + href.left(index));
                }
                else
                    // not in Bouml case
                    pf->loadFromProfile();

                return pf;
            }
            else if ((*it)->kind() == aPackage)
                return (UmlPackage *) *it;
        }
    }

    return 0;
}

void UmlPackage::packageImport(FileIn & in, Token & tk)
{
    if (! tk.closed()) {
        WrapperStr id = tk.xmiId();
        WrapperStr k = tk.what();
        const char * kstr = k;

        while (in.read(), !tk.close(kstr)) {
            if (tk.what() == "importedpackage") {
                if (tk.xmiType() == "uml:Model") {
                    WrapperStr v;

                    if (propertyValue("metamodelReference", v) && (v == id)) {
                        WrapperStr href = tk.valueOf("href");
                        int index = href.find('#');

                        set_PropertyValue("metamodelReference",
                                          (index == -1)
                                          ? href : href.left(index));
                    }
                }
                else if (tk.xmiType() == "uml:Profile") {
                    WrapperStr s = tk.xmiIdref();
                    UmlPackage * pf = 0;

                    if (!s.isEmpty()) {
                        QMap<QString, UmlItem *>::Iterator it = All.find(s);

                        if (it == All.end())
                            UnresolvedRelation::add(4, this->id(), s, "", "");
                        else if ((*it)->kind() == aPackage)
                            pf = (UmlPackage *) *it;
                    }
                    else
                        pf = importProfile(in, tk.valueOf("href"));

                    if (pf != 0) {
                        UmlNcRelation * ncr = UmlNcRelation::create(aDependency, this, pf);

                        if (ncr != 0)
                            ncr->set_Stereotype("import");
                    }
                }
            }
            else if (tk.what() == "importedelement") {
                WrapperStr v;

                if (propertyValue("metaclassReference", v) && (v == id)) {
                    WrapperStr href = tk.valueOf("href");
                    int index = href.find('#');

                    set_PropertyValue("metaclassReference",
                                      (index == -1)
                                      ? href : href.left(index));
                }
            }

            if (! tk.closed())
                in.finish(tk.what());
        }
    }
}

void UmlPackage::solveRefs()
{
    UmlCom::trace("<br><font face=helvetica>solve references<br>");

    UnresolvedWithContext::solveThem();
    UnresolvedRelation::solveThem();
    Association::solveThem();	// must be done after UnresolvedRelation::solveThem();
    Unresolved::solveThem();	// must be done when all relations are done for activity read/write var=rel
    UmlFlow::solveThem();
    UmlTransition::solveThem();
    Binding::solveThem(); // must be done when all classes and realization or generalization are done
    ClassInstance::solveThem(); // must be done when all classes are done
    Manifestation::solveThem(); // must be done when all artifact, class, component and node exist

}

UmlPackage * UmlPackage::findProfile(WrapperStr xmiId)
{
    if (stereotype() == "profile") {
        WrapperStr id;

        if (propertyValue("xmiId", id) && (id == xmiId))
            return this;
    }

    const Q3PtrVector<UmlItem> ch = children();
    unsigned n = ch.size();
    UmlPackage * r;

    for (unsigned u = 0; u != n; u += 1) {
        if ((ch[u]->kind() == aPackage) &&
            ((r = ((UmlPackage *) ch[u])->findProfile(xmiId)) != 0))
            return r;
    }

    return 0;
}

int UmlPackage::NumberOf;

int UmlPackage::NumberOfProfile;

