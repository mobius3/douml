
#include "UmlOperation.h"
#include "FileOut.h"

#include <stdlib.h>
#include "../src/misc/mystr.h"
#include "UmlClass.h"
#include "CppSettings.h"
#include "JavaSettings.h"
#include "UmlPackage.h"
//Added by qt3to4:
#include "misc/mystr.h"
#include <Q3ValueList>
#include <array>
void UmlOperation::write(FileOut & out)
{
    WrapperStr decl;

    switch (_lang) {
    case Uml:
        out.indent();
        out << "<ownedOperation xmi:type=\"uml:Operation\" name=\"";
        out.quote((const char *)name()); //[jasa] ambiguous call
        break;

    case Cpp:
        decl = cppDecl();

        if (decl.isEmpty())
            return;

        remove_comments(decl);
        out.indent();
        out << "<ownedOperation xmi:type=\"uml:Operation\" name=\"";
        out.quote((const char *)true_name(name(), cppDecl())); //[jasa] ambiguous call
        break;

    default: // Java
        decl = javaDecl();

        if (decl.isEmpty())
            return;

        remove_comments(decl);
        out.indent();
        out << "<ownedOperation xmi:type=\"uml:Operation\" name=\"";
        out.quote((const char *)true_name(name(), javaDecl())); //[jasa] ambiguous call
        break;
    }

    out << '"';
    out.id(this);

    write_visibility(out);
    write_scope(out);

    if ((_lang == Cpp) && isCppConst())
        out << " isQuery=\"true\"";

    out << " isAbstract=\""
        << ((isAbstract()) ? "true" : "false")
        << "\">\n";

    out.indent(+1);

    write_constraint(out);
    write_annotation(out);
    write_description_properties(out);
    write_exceptions(out);
    write_return_type(out, decl);

    if (_lang == Uml)
        write_uml_params(out);
    else
        write_cpp_java_params(out, decl);

    out.indent(-1);
    out.indent();
    out << "</ownedOperation>\n";

    unload();
}

void UmlOperation::write_exceptions(FileOut & out)
{
    const Q3ValueList<UmlTypeSpec> excpts = exceptions();
    Q3ValueList<UmlTypeSpec>::ConstIterator iter;

    for (iter = excpts.begin(); iter != excpts.end(); ++iter) {
        const UmlTypeSpec & e = *iter;

        if (e.type != 0) {
            out.indent();
            out << "<raisedException";
            out.idref(e.type);
            out << "/>\n";
        }
        else if (!e.explicit_type.isEmpty()) {
            out.indent();
            out << "<raisedException";
            out.idref_datatype(e.explicit_type);
            out << "/>\n";
        }
    }
}

void UmlOperation::write_return_type(FileOut & out, WrapperStr decl)
{
    const UmlTypeSpec & t = returnType();
    static int return_rank = 0;

    if ((t.type != 0) || !t.explicit_type.isEmpty()) {
        out.indent();
        out << "<ownedParameter name=\"return\" xmi:id=\"BOUML_return_"
            << ++return_rank << "\" direction=\"";

        if (_pk_prefix)
            out << "pk_";

        out << "return\">\n";

        switch (_lang) {
        case Uml:
            out.indent(+1);
            UmlItem::write_type(out, t);
            out.indent(-1);
            break;

        case Cpp:
            out.indent();
            out << "\t<type xmi:type=\"uml:Class\"";
            write_cpp_returntype(out, decl);
            out << "/>\n";
            break;

        default: // java
            out.indent();
            out << "\t<type xmi:type=\"uml:Class\"";
            write_java_returntype(out, decl);
            out << "/>\n";
        }

        out.indent();
        out << "</ownedParameter>\n";
    }
}

void UmlOperation::write_cpp_returntype(FileOut & out, WrapperStr decl)
{
    // doesn't manage function pointer
    // manage keywords
    int index;

    if ((index = decl.find("${static}")) != -1)
        decl.remove(index, 9);

    if ((index = decl.find("${friend}")) != -1)
        decl.remove(index, 9);

    if ((index = decl.find("${virtual}")) != -1)
        decl.remove(index, 10);

    if ((index = decl.find("${inline}")) != -1)
        decl.remove(index, 9);

    if ((index = decl.find("${(}")) == -1)
        decl = "${type} ${name}";
    else
        decl.truncate(index);

    UmlTypeSpec t = returnType();

    if ((t.type != 0) ||
        !(t.explicit_type = CppSettings::type(t.explicit_type)).isEmpty())
        write_type(out, t, decl, "${name}", "${type}");
}

void UmlOperation::write_java_returntype(FileOut & out, WrapperStr decl)
{
// manage keywords
    int index;

    if ((index = decl.find("${visibility}")) != -1)
        decl.remove(index, 13);

    if ((index = decl.find("${final}")) != -1)
        decl.remove(index, 8);

    if ((index = decl.find("${static}")) != -1)
        decl.remove(index, 9);

    if ((index = decl.find("${abstract}")) != -1)
        decl.remove(index, 11);

    if ((index = decl.find("${synchronized}")) != -1)
        decl.remove(index, 15);

    if ((index = decl.find("${@}")) != -1)
        decl.remove(index, 4);

    if ((index = decl.find("${(}")) == -1)
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
    const Q3ValueList<UmlParameter> p = params();
    Q3ValueList<UmlParameter>::ConstIterator it;

    for (it = p.begin(); it != p.end(); ++it) {
        out.indent();
        out << "<ownedParameter xmi:type=\"uml:Parameter\" name=\"" << (*it).name.operator QString()
            << "\" xmi:id=\"BOUML_op_param_"
            << ++param_id << "\" direction=\"";

        if (_pk_prefix)
            out << "pk_";

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

        out.indent(+1);
        UmlItem::write_type(out, (*it).type);
        out.indent(-1);

        out.indent();
        out << "</ownedParameter>\n";
    }
}

void UmlOperation::write_cpp_java_params(FileOut & out, WrapperStr decl)
{
    int index1 = decl.find("${(}");

    if (index1 == -1)
        return;

    int index2 = decl.find("${)}", index1 + 4);

    if (index2 == -1)
        return;

    decl = decl.mid(index1 + 4, index2 - index1 - 4);

    index1 = 0;

    const Q3ValueList<UmlParameter> p = params();
    WrapperStr sparam;
    WrapperStr kname;
    WrapperStr ktype;
    int rank;

    while (get_param(decl, index1, sparam, kname, ktype, rank)) {
        if (rank < (int) p.count()) {
            const UmlParameter & pa = p[rank];

            out.indent();
            out << "<ownedParameter xmi:type=\"uml:Parameter\" name=\"" << pa.name.operator QString()
                << "\" xmi:id=\"BOUML_op_param_"
                << ++param_id << "\" direction =\"";

            if (_pk_prefix)
                out << "pk_";

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
                out << "\t<type xmi:type=\"uml:Class\"";
                write_type(out, t, sparam, kname, ktype);
                out << "/>\n";
            }

            out.indent();
            out << "</ownedParameter>\n";
        }
    }
}

// some really insane code from stackoverflow that allows to shorten lengthy ifs
template <typename T0, typename T1, std::size_t N>
bool operator *(const T0& lhs, const std::array<T1, N>& rhs) {
    return std::find(begin(rhs), end(rhs), lhs) != end(rhs);
}

template<class T0, class...T> std::array<T0, 1+sizeof...(T)> in(T0 arg0, T...args) {
    return {{arg0, args...}};
}


bool UmlOperation::get_param(WrapperStr s, int & index, WrapperStr & r, WrapperStr & kname, WrapperStr & ktype, int & rank)
{
    int index0 = index;
    int level = 0;
//const char * p = (const char *) s;

    r = "";

    do {
        if (index >= (int) s.length()) {
            if (level != 0)
                return FALSE;

            r = s.mid(index0, index - index0).stripWhiteSpace();

            if (r.isEmpty())
                return FALSE;

            break;
        }
        if(s[index] *in('(', '{', '['))
            level += 1;
        else if(s.at(index) == ",")
        {
            if (level == 0) {
                r = s.mid(index0, index - index0).stripWhiteSpace();
                index += 1;

                if (r.isEmpty())
                    return FALSE;
            }
        }
        else if(s[index] *in(')', '}', ']'))
        {
            if (--level < 0)
                return FALSE;
        }

        index += 1;
    }
    while (r.isEmpty());

    int index1;
    int index2;

    rank = -1;

    if (((index1 = r.find("${p")) != -1) &&
        ((index2 = r.find("}", index1 + 3)) != -1)) {
        kname = r.mid(index1, index2 - index1 + 1);
        rank = atoi(((const char *) r) + index1 + 3);
    }
    else
        kname = "";

    if (((index1 = r.find("${t")) != -1) &&
        ((index2 = r.find("}", index1 + 3)) != -1)) {
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

const char * UmlOperation::event(bool rec)
{
    int n = (int)((long) SentReceived[this]);

    if (n == 0) {
        static unsigned rank = 0;

        n = ++rank;

        SentReceived.insert(this, (char *) n);
    }

    static char s[24];

    sprintf(s, (rec) ? "RECOPEREVT%u_" : "SENDOPEREVT%u_", n);
    return s;
}

const char * UmlOperation::event(const char * pfix, WrapperStr msg)
{
    int index0 = 0;
    int index1;

    while ((index1 = msg.find('\n', index0)) != -1)
    {
        msg.replace(index1,1, " ");
        index0 = index1 + 1;
    }

    msg = *pfix + msg.simplifyWhiteSpace();

    char * presult = Events[msg];

    if (presult == 0) {
        static unsigned rank = 0;
        char s[16];

        sprintf(s, "%sEVT%u_", pfix, ++rank);
        presult = strdup(s);
        Events.insert(msg, presult);
    }

    return presult;
}

void UmlOperation::write_events(FileOut & out)
{
    const char * k = (_uml_20) ? "ownedMember" : "packagedElement";
    UmlItem * prj = UmlPackage::getProject();
    Q3PtrDictIterator<char> it_oper(SentReceived);

    while (it_oper.current()) {
        out.indent();
        out << "<" << k << " xmi:type=\"uml:SendOperationEvent\"";
        out.id_prefix(prj, "SENDOPEREVT", (int)((long) it_oper.current()));
        out << " name=\"";
        out.quote((const char *)((UmlOperation *)it_oper.currentKey())->name()); //[jasa] ambiguous call
        out << '"';
        out.ref((UmlOperation *)it_oper.currentKey(), "operation");
        out << "/>\n";

        out.indent();
        out << "<" << k << " xmi:type=\"uml:ReceiveOperationEvent\"";
        out.id_prefix(prj, "RECOPEREVT", (int)((long) it_oper.current()));
        out << " name=\"";
        out.quote((const char *)((UmlOperation *)it_oper.currentKey())->name()); //[jasa] ambiguous call
        out << '"';
        out.ref((UmlOperation *)it_oper.currentKey(), "operation");
        out << "/>\n";

        ++it_oper;
    }

    Q3AsciiDictIterator<char> it_evt(Events);

    while (it_evt.current()) {
        out.indent();

        if (it_evt.currentKey()[0] == 'D') {
            out << "<" << k << " xmi:type=\"uml:DestructionEvent\"";
            out.id_prefix(prj, it_evt.current());
            out << "/>\n";
        }
        else {
            out << "<" << k << " xmi:type=\"uml:ExecutionEvent\"";
            out.id_prefix(prj, it_evt.current());

            if (*it_evt.currentKey() != 0) {
                out << " name=\"";
                out.quote(it_evt.currentKey() + 1);
                out << "\"/>\n";
            }
            else
                out << "/>\n";
        }

        free(it_evt.current());
        ++it_evt;
    }
}

int UmlOperation::param_id;

Q3PtrDict<char> UmlOperation::SentReceived;

Q3AsciiDict<char> UmlOperation::Events;

