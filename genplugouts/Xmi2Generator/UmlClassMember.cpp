
#include "UmlClassMember.h"
#include "FileOut.h"
#include "UmlTypeSpec.h"

#include "UmlClass.h"
#include <QRegExp>
//Added by qt3to4:
#include "misc/mystr.h"
void UmlClassMember::write_scope(FileOut & out)
{
    if (isClassMember())
        out << " isStatic=\"true\"";
}

void UmlClassMember::write_visibility(FileOut & out)
{
    aVisibility v;

    switch (_lang) {
    case Uml:
        v = visibility();
        break;

    case Cpp:
        v = (cppVisibility() == DefaultVisibility)
            ? visibility()
            : cppVisibility();
        break;

    default: // Java
        v = (javaDecl().find("${visibility}") != -1)
            ? visibility() : PackageVisibility;
        break;
    }

    out << " visibility=\"";

    if (_vis_prefix)
        out << "vis_";

    switch (v) {
    case PublicVisibility:
        out << "public\"";
        break;

    case ProtectedVisibility:
        out << "protected\"";
        break;

    case PrivateVisibility:
        out << "private\"";
        break;

    default:
        out << "package\"";
    }
}

void UmlClassMember::write_annotation(FileOut & out)
{
    if (_lang == Java) {
        WrapperStr a = javaAnnotations();

        if (!a.isEmpty()) {
            out.indent();
            out << "<xmi:Extension extender=\"Bouml\">\n\t<annotation value=\"";
            out.quote(a);
            out << "\"/>\n";
            out.indent();
            out << "</xmi:Extension>\n";
        }
    }
}

void UmlClassMember::write_constraint(FileOut & out)
{
    WrapperStr s = constraint();

    if (! s.isEmpty()) {
        out.indent();
        out << "<ownedRule xmi:type=\"uml:Constraint\"";
        out.id_prefix(this, "CONSTRAINT_");
        out.ref(this, "constrainedElement");
        out << ">\n";
        out.indent();
        out << "\t<specification xmi:type=\"uml:OpaqueExpression\"";
        out.id_prefix(this, "CSPEC_");
        out << ">\n";
        out.indent();
        out << "\t\t<body>";
        out.quote(s);
        out << "</body>\n";
        out.indent();
        out << "\t</specification>\n";
        out.indent();
        out << "</ownedRule>\n";
    }
}

WrapperStr UmlClassMember::true_name(WrapperStr name, WrapperStr decl)
{
//int index = decl.find("${name}", 0, FALSE);//[jasa] no matching call
    int index = decl.lower().find("${name}", 0);//[jasa] lowercase for find()

    if (index == -1)
        // too complicated, return the Uml one
        return name;

    int begin = index;

    while ((begin != 0) && identChar(decl[begin - 1]))
        begin -= 1;

    int sup = index + 7;

    while (identChar(decl[sup]))
        sup += 1;

    WrapperStr r = decl.mid(begin, index - begin);
    WrapperStr k = decl.mid(index + 2, 4);

    if (k == "name")
        r += name;
    else if (k == "Name")
        r += name.left(1).upper() + name.mid(1);
    else
        // NAME
        r += name.upper();

    r += decl.mid(index + 7, sup - index - 7);

    return r;
}

bool UmlClassMember::identChar(QCharRef s)
{
    QRegExp rx(QRegExp::escape("[A-Za-z0-9_]"));
    return rx.indexIn(QString(s)) != -1;
//    return (((c >= 'a') && (c <= 'z')) ||
//            ((c >= 'A') && (c <= 'Z')) ||
//            ((c >= '0') && (c <= '9')) ||
//            (c == '_'));
}

void UmlClassMember::write_type(FileOut & out, const UmlTypeSpec & t, WrapperStr s, const char * k_name, const char * k_type)
{
    s = s.simplifyWhiteSpace();

    int index;

    // remove k_name and all after it except []
    //if (k_name && *k_name && ((index = s.find(k_name, 0, FALSE)) != -1)) {//[jasa] original line
    if (k_name && *k_name && ((index = s.lower().find(WrapperStr(k_name).lower(), 0)) != -1)) {//[jasa] covert to lowercase for find()
        //remove name
        s.remove(index, strlen(k_name));

        for (;;) {
            if (s[index] == ' ')
                s.remove(index, 1);

            if (s[index] != '[')
                break;

            index += 1;

            int index2;

            if ((index2 = s.find(index, ']')) == -1)
                break;

            index = index2 + 1;
        }

        s.resize(index);
    }
    else if ((index = s.find('=')) != -1) {
        s.resize(index);
        s = s.simplifyWhiteSpace();
    }

    if (k_type && *k_type && ((index = s.find(k_type)) == -1))
        out.idref_datatype(s);
    else if (s != k_type) {
        // have modifiers
        if (t.type != 0) {
            s.replace(index, strlen(k_type), t.type->name());
            out.idref(s, t.type);
        }
        else
            out.idref_datatype(s.replace(index, strlen(k_type), t.explicit_type));
    }
    else if (t.type != 0)
        out.idref(t.type);
    else
        out.idref_datatype(t.explicit_type);
}

void UmlClassMember::remove_comments(WrapperStr & s)
{
    int index;

    if ((index = s.find("${comment}")) != -1)
        s.replace(index, 10, " ");

    index = 0;

    while ((index = s.find('#', index)) != -1) {
        int index2 = s.find('\n', index + 1);

        if (index2 == -1) {
            s.resize(index);
            break;
        }

        s.remove(index, index2 - index);
    }

    index = 0;

    while ((index = s.find("//", index)) != -1) {
        int index2 = s.find('\n', index + 2);

        if (index2 == -1) {
            s.resize(index);
            break;
        }

        s.remove(index, index2 - index);
    }

    index = 0;

    while ((index = s.find("/*", index)) != -1) {
        int index2 = s.find("*/", index + 2);

        if (index2 == -1) {
            s.resize(index);
            break;
        }

        s.replace(index, index2 + 2 - index, " ");
    }

    s = s.simplifyWhiteSpace();
}

