
#include "UmlOperation.h"
#include "File.h"
#include "UmlClass.h"

#include <qstringlist.h>
//Added by qt3to4:
#include <QByteArray>

#include "UmlCom.h"
#include "util.h"
#include "CppSettings.h"
#include "JavaSettings.h"
#include "IdlSettings.h"
void UmlOperation::import(File & f, UmlClass * parent)
{
    QByteArray s;

    if (f.read(s) != STRING)
        f.syntaxError(s, "operations's name");

    QByteArray id;
    QByteArray ste;
    QByteArray doc;
    QHash<QByteArray, QByteArray*> prop;
    QByteArray s2;
    int k;

    do {
        k = f.readDefinitionBeginning(s2, id, ste, doc, prop);
    }
    while (id.isEmpty());

    UmlOperation * x;

    if (scanning) {
        QByteArray name;

        if (s.left(8) != "operator")
            name = (s.at(0) == '~')
                   ? ("~" + legalName(s.mid(1)))
                   : legalName(s);
        else
            name = s;

        if ((x = UmlBaseOperation::create(parent, name)) == 0) {
            UmlCom::trace("<br>cannot create operation '" + s + "' in " +
                          parent->fullName());
            throw 0;
        }

        newItem(x, id);

        if (!ste.isEmpty()) {
            bool managed = FALSE;
            QStringList l = QString(ste).split(",");

            for (QStringList::Iterator it = l.begin();
                 it != l.end();
                 ++it) {
                if ((*it) == "const") {
                    managed = TRUE;
                    x->set_isCppConst(TRUE);
                }
                else if ((*it) == "abstract") {
                    managed = TRUE;
                    x->set_isAbstract(TRUE);
                    x->set_isCppVirtual(TRUE);
                }
                else if ((*it) == "virtual") {
                    managed = TRUE;
                    x->set_isCppVirtual(TRUE);
                }
                else if ((*it) == "static") {
                    managed = TRUE;
                    x->set_isClassMember(TRUE);
                }
            }

            if (!managed)
                x->set_Stereotype(ste);
        }

        if (!doc.isEmpty())
            x->set_Description(doc);
    }
    else if ((x = (UmlOperation *) findItem(id, anOperation)) == 0) {
        UmlCom::trace("<br>unknown operation '" + s + "' in " +
                      parent->fullName());
        throw 0;
    }
    else {
        switch (((UmlClass *) x->parent())->language()) {
        case Cplusplus:
        case AnsiCplusplus:
        case VCplusplus:
            x->cplusplus(prop);
            break;

        case Oracle8:
            x->oracle8(prop);
            break;

        case Corba:
            x->corba(prop);
            break;

        case Java:
            x->java(prop);
            break;

        default:
            break;
        }

        x->setProperties(prop);
    }

    f.unread(k, s2);
    x->import(f);
}

void UmlOperation::import(File & f)
{
    if (scanning) {
        f.skipBlock();
        return;
    }

    QByteArray s;
    UmlTypeSpec t;

    for (;;) {
        switch (f.read(s)) {
        case -1:
            f.eof();
            throw 0;

        case ')':
            set_ReturnType(t);
            return;

        case ATOM:
            break;

        default:
            f.syntaxError(s);
        }

        // atom
        if (s == "parameters") {
            f.read("(");
            f.read("list");
            f.read("Parameters");
            importParameters(f);
        }
        else if (s == "result") {
            if (f.read(s) != STRING)
                f.syntaxError(s, "return type");

            t.explicit_type = s;
        }
        else if (s == "quidu") {
            if (f.read(s) != STRING)
                f.syntaxError(s, "wrong quidu");

            if (UmlClass::replaceType(t, s, "${type}")) {
                switch (((UmlClass *) parent())->language()) {
                case Cplusplus:
                case AnsiCplusplus:
                case VCplusplus:
                    set_CppDecl(replace(cppDecl(), "${type}", s));
                    set_CppDef(replace(cppDef(), "${type}", s));
                    break;

                case Oracle8:
                    break;

                case Corba:
                    set_IdlDecl(replace(idlDecl(), "${type}", s));
                    break;

                case Java:
                    set_JavaDecl(replace(javaDecl(), "${type}", s));
                    break;

                default:
                    break;
                }
            }
        }
        else if (s == "exceptions")
            importExceptions(f);
        else if (s == "opExportControl")
            set_Visibility(f.readVisibility());
        else
            f.skipNextForm();
    }

}

void UmlOperation::importParameters(File & f)
{
    QByteArray s;
    unsigned rank = 0;
    const char * sep = "";
    QByteArray doc = description();

    for (;;) {
        switch (f.read(s)) {
        case ')':
            if (doc != description())
                set_Description(doc);

            return;

        case '(':
            // a parameter
            break;

        default:
            f.syntaxError(s);
        }

        f.read("object");
        f.read("Parameter");

        UmlParameter p;
        QByteArray ti;

        ti = QString("${t%1}").arg(rank).toLatin1();

        if (f.read(p.name) != STRING)
            f.syntaxError(s, "parameter's name");

        QByteArray id;
        QByteArray ste;
        QByteArray p_doc;
        QHash<QByteArray, QByteArray*> prop;
        int k;

        for (;;) {
            k = f.readDefinitionBeginning(s, id, ste, p_doc, prop);

            if (k == ')')
                break;

            if (s == "type") {
                if (f.read(s) != STRING)
                    f.syntaxError(s, "parameter type");

                switch (((UmlClass *) parent())->language()) {
                case Corba:
                    if (strncmp(s,  "in ", 3) == 0) {
                        p.dir = InputDirection;
                        s = s.mid(3);
                    }
                    else if (strncmp(s,  "out ", 4) == 0) {
                        p.dir = OutputDirection;
                        s = s.mid(4);
                    }
                    else if (strncmp(s,  "inout ", 6) == 0) {
                        p.dir = InputOutputDirection;
                        s = s.mid(6);
                    }
                    else {
                        QByteArray err =
                            "<br>'" + s + "' : wrong parameter direction, in " + f.context();

                        UmlCom::trace(err);
                        p.dir = InputOutputDirection;
                    }

                    break;

                default:
                    // !!!!!!!!!!!!!
                    p.dir = InputOutputDirection;
                }

                p.type.explicit_type = s;
            }
            else if (s == "quidu") {
                if (f.read(s) != STRING)
                    f.syntaxError(s, "wrong quidu");

                if (UmlClass::replaceType(p.type, s, ti))
                    ti = s;
            }
            else
                f.skipNextForm();
        }

        QByteArray d;
        int index;

        switch (((UmlClass *) parent())->language()) {
        case Cplusplus:
        case AnsiCplusplus:
        case VCplusplus:
            s= QString("%1%2 ${p%3}").arg(sep).arg((const char *) ti).arg(rank).toLatin1();

            if ((index = (d = cppDecl()).indexOf("${)}")) != -1)
                //set_CppDecl(d.insert(index, s));//[jasa] original line
                set_CppDecl(d.insert(index, (const char *)s)); //[jasa] fix ambiguous call

            if ((index = (d = cppDef()).indexOf("${)}")) != -1)
                set_CppDef(d.insert(index, (const char *)s)); //[jasa] fix ambiguous call

            break;

        case Oracle8:
            break;

        case Corba:
            if ((index = (d = idlDecl()).indexOf("${)}")) != -1) {
                s = QString("%1${d%2} %3 ${p%4}").arg(
                          sep).arg(rank).arg((const char *) ti).arg(rank).toLatin1();
                set_IdlDecl(d.insert(index, (const char *)s)); //[jasa] fix ambiguous call
            }

            break;

        case Java:
            if ((index = (d = javaDecl()).indexOf("${)}")) != -1) {
                s = QString("%s%s ${p%u}").arg( sep).arg( (const char *) ti).arg( rank).toLatin1();
                set_JavaDecl(d.insert(index, (const char *)s)); //[jasa]
            }

            break;

        default:
            break;
        }

        addParameter(rank++, p);
        sep = ", ";
    }
}

void UmlOperation::importExceptions(File & f)
{
    QByteArray s;
    unsigned rank = 0;

    if (f.read(s) != STRING)
        f.syntaxError(s, "the exceptions");

    int index = 0;

    while (!(s = s.mid(index).trimmed()).isEmpty()) {
        if ((index = s.indexOf(' ')) == -1)
            index = s.length();

        UmlTypeSpec t;
        int index2;

        t.explicit_type = s.left(index);

        if (((index2 = t.explicit_type.indexOf("[")) != -1) &&
            (((const char *) t.explicit_type)[t.explicit_type.length() - 1]
             == ']')) {
            QByteArray target_id =
                t.explicit_type.mid(index2 + 1,
                                    t.explicit_type.length() - index2 - 2);
            UmlClass * cl = (UmlClass *) UmlItem::findItem(target_id, aClass);

            if (cl != 0) {
                t.explicit_type = 0;
                t.type = cl;
            }
            else
                t.explicit_type.truncate(index2);
        }

        addException(rank++, t);
    }
}

void UmlOperation::cplusplus(QHash<QByteArray, QByteArray*> &)
{
    set_CppDecl(CppSettings::operationDecl());
    set_CppDef(CppSettings::operationDef());
}

void UmlOperation::oracle8(QHash<QByteArray, QByteArray*> &)
{
}

void UmlOperation::corba(QHash<QByteArray, QByteArray*> & prop)
{
    QByteArray * v;

    if ((v = prop.value("CORBA/OperationIsOneWay")) != 0) {
        if (*v == "TRUE")
            set_isIdlOneway(TRUE);

        prop.remove("CORBA/OperationIsOneWay");
    }

    set_IdlDecl(IdlSettings::operationDecl());
}

void UmlOperation::java(QHash<QByteArray, QByteArray*> & prop)
{
    QByteArray d = JavaSettings::operationDef();
    QByteArray * v;

    if ((v = prop.value("Java/Final")) != 0) {
        if (*v == "TRUE")
            set_isJavaFinal(TRUE);

        prop.remove("Java/Final");
    }

    if ((v = prop.value("Java/Synchronized")) != 0) {
        if (*v == "TRUE")
            set_isJavaSynchronized(TRUE);

        prop.remove("Java/Synchronized");
    }

    if ((v = prop.value("Java/Static")) != 0) {
        if (*v == "TRUE")
            set_isClassMember(TRUE);

        prop.remove("Java/Static");
    }

    if ((v = prop.value("Java/Abstract")) != 0) {
        if (*v == "TRUE")
            set_isAbstract(TRUE);

        prop.remove("Java/Abstract");
    }

    if ((v = prop.value("Java/Strictfp")) != 0) {
        if (*v == "TRUE") {
            int index = d.indexOf("${final}");

            if (index != -1)
                d.insert(index, "strictfp ");
        }

        prop.remove("Java/Strictfp");
    }

    set_JavaDef(d);
}

