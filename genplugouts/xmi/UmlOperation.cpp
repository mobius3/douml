
#include "UmlOperation.h"
#include "FileOut.h"

#include <stdlib.h>

#include "UmlClass.h"
#include "CppSettings.h"
#include "JavaSettings.h"
//Added by qt3to4:
#include <QByteArray>
#include <QList>
bool UmlOperation::write_if_needed(FileOut & out)
{
    QByteArray decl;

    switch (_lang) {
    case Uml:
        parent()->write(out);
        out.indent();
        out << "<UML:Operation name=\"";
        out.quote(name());
        break;

    case Cpp:
        decl = cppDecl();

        if (decl.isEmpty())
            return FALSE;

        remove_comments(decl);
        parent()->write(out);
        out.indent();
        out << "<UML:Operation name=\"";
        out.quote(true_name(cppDecl()));
        break;

    default: // Java
        decl = javaDecl();

        if (decl.isEmpty())
            return FALSE;

        remove_comments(decl);
        parent()->write(out);
        out.indent();
        out << "<UML:Operation name=\"";
        out.quote(true_name(javaDecl()));
        break;
    }

    out << '"';
    out.id(this);

    switch (_lang) {
    case Uml:
        write_visibility(out);
        break;

    case Cpp:
        write_visibility(out,
                         (cppVisibility() == DefaultVisibility)
                         ? visibility() : cppVisibility());
        break;

    default: // Java
        if (javaDecl().indexOf("${visibility}") != -1)
            write_visibility(out, visibility());

        break;
    }

    write_scope(out);
    out << " isAbstract=\""
        << ((isAbstract()) ? "true" : "false")
        << "\">\n";

    out.indent(+1);

    write_stereotype(out);
    write_annotation(out);
    write_description_properties(out);

    out.indent();
    out << "<UML:BehavioralFeature.parameter>\n";
    out.indent(+1);

    write_return_type(out, decl);

    if (_lang == Uml)
        write_uml_params(out);
    else
        write_cpp_java_params(out, decl);

    out.indent(-1);
    out.indent();
    out << "</UML:BehavioralFeature.parameter>\n";

    out.indent(-1);
    out.indent();
    out << "</UML:Operation>\n";

    unload();

    return TRUE;
}

void UmlOperation::write_return_type(FileOut & out, QByteArray decl)
{
    const UmlTypeSpec & t = returnType();
    static int return_rank = 0;

    if ((t.type != 0) || !t.explicit_type.isEmpty()) {
        out.indent();
        out << "<UML:Parameter name=\"return\" xmi.id=\"BOUML_return_"
            << ++return_rank << "\" kind=\"return\">\n";
        out.indent();
        out << "\t<UML:Parameter.type>\n";
        out.indent();
        out << "\t\t<UML:DataType";

        switch (_lang) {
        case Uml:
            if (t.type != 0)
                out.idref(t.type);
            else
                out.idref_datatype(t.explicit_type);

            break;

        case Cpp:
            write_cpp_returntype(out, decl);
            break;

        default: // java
            write_java_returntype(out, decl);
        }

        out << "/>\n";
        out.indent();
        out << "\t</UML:Parameter.type>\n";
        out.indent();
        out << "</UML:Parameter>\n";
    }
}

void UmlOperation::write_cpp_returntype(FileOut & out, QByteArray decl)
{
    // doesn't manage function pointer
    // manage keywords
    int index;

    if ((index = decl.indexOf("${static}")) != -1)
        decl.remove(index, 9);

    if ((index = decl.indexOf("${friend}")) != -1)
        decl.remove(index, 9);

    if ((index = decl.indexOf("${virtual}")) != -1)
        decl.remove(index, 10);

    if ((index = decl.indexOf("${inline}")) != -1)
        decl.remove(index, 9);

    if ((index = decl.indexOf("${(}")) == -1)
        decl = "${type} ${name}";
    else
        decl.truncate(index);

    UmlTypeSpec t = returnType();

    if ((t.type != 0) ||
        !(t.explicit_type = CppSettings::type(t.explicit_type)).isEmpty())
        write_type(out, t, decl, "${name}", "${type}");
}

void UmlOperation::write_java_returntype(FileOut & out, QByteArray decl)
{
// manage keywords
    int index;

    if ((index = decl.indexOf("${visibility}")) != -1)
        decl.remove(index, 13);

    if ((index = decl.indexOf("${final}")) != -1)
        decl.remove(index, 8);

    if ((index = decl.indexOf("${static}")) != -1)
        decl.remove(index, 9);

    if ((index = decl.indexOf("${abstract}")) != -1)
        decl.remove(index, 11);

    if ((index = decl.indexOf("${synchronized}")) != -1)
        decl.remove(index, 15);

    if ((index = decl.indexOf("${@}")) != -1)
        decl.remove(index, 4);

    if ((index = decl.indexOf("${(}")) == -1)
        decl = "${type} ${name}";
    else
        decl.truncate(index);

    UmlTypeSpec t = returnType();

    if ((t.type != 0) ||
        !(t.explicit_type = JavaSettings::type(t.explicit_type)).isEmpty())
        write_type(out, t, decl, "${name}", "${type}");
}

void UmlOperation::write_uml_params(FileOut & out)
{
    const QList<UmlParameter> p = params();
    QList<UmlParameter>::ConstIterator it;

    for (it = p.begin(); it != p.end(); ++it) {
        out.indent();
        out << "<UML:Parameter name=\"" << (*it).name
            << "\" xmi.id=\"BOUML_op_param_"
            << ++param_id << "\" kind =\"";

        switch ((*it).dir) {
        case InputOutputDirection:
            out << "inout\">\n";
            break;

        case OutputDirection:
            out << "out\">\n";
            break;

        default:
            out << "in\">\n";
        }

        const UmlTypeSpec & pt = (*it).type;

        if (pt.type != 0) {
            out.indent();
            out << "\t<UML:Parameter.type>\n";
            out.indent();
            out << "\t\t<UML:DataType";
            out.idref(pt.type);
            out << "/>\n";
            out.indent();
            out << "\t</UML:Parameter.type>\n";
        }
        else if (!pt.explicit_type.isEmpty()) {
            out.indent();
            out << "\t<UML:Parameter.type>\n";
            out.indent();
            out << "\t\t<UML:DataType";
            out.idref_datatype(pt.explicit_type);
            out << "/>\n";
            out.indent();
            out << "\t</UML:Parameter.type>\n";
        }

        out.indent();
        out << "</UML:Parameter>\n";
    }
}

void UmlOperation::write_cpp_java_params(FileOut & out, QByteArray decl)
{
    int index1 = decl.indexOf("${(}");

    if (index1 == -1)
        return;

    int index2 = decl.indexOf("${)}", index1 + 4);

    if (index2 == -1)
        return;

    decl = decl.mid(index1 + 4, index2 - index1 - 4);

    index1 = 0;

    const QList<UmlParameter> p = params();
    QByteArray sparam;
    QByteArray kname;
    QByteArray ktype;
    int rank;

    if ((name() == "unload") && (parent()->name() == "UmlBasePackage"))
        rank = 123;

    while (get_param(decl, index1, sparam, kname, ktype, rank)) {
        if (rank < (int) p.count()) {
            const UmlParameter & pa = p[rank];

            out.indent();
            out << "<UML:Parameter name=\"" << pa.name
                << "\" xmi.id=\"BOUML_op_param_"
                << ++param_id << "\" kind =\"";

            switch (pa.dir) {
            case InputOutputDirection:
                out << "inout\">\n";
                break;

            case OutputDirection:
                out << "out\">\n";
                break;

            default:
                out << "in\">\n";
            }

            UmlTypeSpec t = pa.type;

            if ((t.type != 0) ||
                !(t.explicit_type = (_lang == Cpp)
                                    ? CppSettings::type(t.explicit_type)
                                    : JavaSettings::type(t.explicit_type)).isEmpty()) {
                out.indent();
                out << "\t<UML:Parameter.type>\n";
                out.indent();
                out << "\t\t<UML:DataType";
                write_type(out, t, sparam, kname, ktype);
                out << "/>\n";
                out.indent();
                out << "\t</UML:Parameter.type>\n";
            }

            out.indent();
            out << "</UML:Parameter>\n";
        }
    }
}

bool UmlOperation::get_param(QByteArray s, int & index, QByteArray & r, QByteArray & kname, QByteArray & ktype, int & rank)
{
    int index0 = index;
    int level = 0;
    const char * p = (const char *) s;

    r = "";

    do {
        switch (p[index]) {
        case 0:
            if (level != 0)
                return FALSE;

            r = s.mid(index0, index - index0).trimmed();

            if (r.isEmpty())
                return FALSE;

        case ',':
            if (level == 0) {
                r = s.mid(index0, index - index0).trimmed();
                index += 1;

                if (r.isEmpty())
                    return FALSE;
            }

            break;

        case '(':
        case '{':
        case '[':
            level += 1;
            break;

        case ')':
        case '}':
        case ']':
            if (--level < 0)
                return FALSE;
        }

        index += 1;
    }
    while (r.isEmpty());

    int index1;
    int index2;

    rank = -1;

    if (((index1 = r.indexOf("${p")) != -1) &&
        ((index2 = r.indexOf("}", index1 + 3)) != -1)) {
        kname = r.mid(index1, index2 - index1 + 1);
        rank = atoi(((const char *) r) + index1 + 3);
    }
    else
        kname = "";

    if (((index1 = r.indexOf("${t")) != -1) &&
        ((index2 = r.indexOf("}", index1 + 3)) != -1)) {
        ktype = r.mid(index1, index2 - index1 + 1);

        if (rank == -1)
            rank = atoi(((const char *) r) + index1 + 3);
    }
    else if (rank == -1)
        // too complicated;
        return FALSE;
    else
        ktype = "";

    return TRUE;
}

int UmlOperation::param_id;

