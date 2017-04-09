
#include "UmlClassMember.h"
#include "FileOut.h"
#include "UmlTypeSpec.h"
#include "UmlClass.h"
#include <QByteArray>
void UmlClassMember::write_scope(FileOut & out, const char * who)
{
    out << " "
        << who
        << ((isClassMember()) ? "Scope=\"classifier\""
            : "Scope=\"instance\"");
}

void UmlClassMember::write_visibility(FileOut & out)
{
    out << " visibility=\"";

    switch (visibility()) {
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

void UmlClassMember::write_visibility(FileOut & out, aVisibility v)
{
    out << " visibility=\"";

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
        QByteArray a = javaAnnotations();

        if (!a.isEmpty()) {
            switch (_taggedvalue_mode) {
            case 1:
                out.indent();
                out << "<UML:ModelElement.taggedValue>\n";
                out.indent();
                out << "\t<UML:TaggedValue tag=\"annotations\" value=\"";
                out.quote(a);
                out << "\"/>\n";
                out.indent();
                out << "</UML:ModelElement.taggedValue>\n";
                break;

            case 2:
                out.indent();
                out << "<UML:ModelElement.taggedValue>\n";
                out.indent();
                out << "\t<UML:TaggedValue.tag>annotations</UML:TaggedValue.tag>\n";
                out.indent();
                out << "\t<UML:TaggedValue.value>";
                out.quote(a);
                out << "</UML:TaggedValue.value>\n";
                out.indent();
                out << "</UML:ModelElement.taggedValue>\n";
            }
        }
    }
}

QByteArray UmlClassMember::true_name(QByteArray decl)
{
    int index = decl.indexOf("${name}", 0); //[rageek] Removed CS=FALSE param - rethink this, case sensitive

    if (index == -1)
        // too complicated, return the Uml one
        return name();

    int begin = index;

    while ((begin != 0) && identChar(decl[begin - 1]))
        begin -= 1;

    int sup = index + 7;

    while (identChar(decl[sup]))
        sup += 1;

    QByteArray r = decl.mid(begin, index - begin);
    QByteArray k = decl.mid(index + 2, 4);

    if (k == "name")
        r += name();
    else if (k == "Name")
        r += name().left(1).toUpper() + name().mid(1);
    else
        // NAME
        r += name().toUpper();

    r += decl.mid(index + 7, sup - index - 7);

    return r;
}

bool UmlClassMember::identChar(char c)
{
    return (((c >= 'a') && (c <= 'z')) ||
            ((c >= 'A') && (c <= 'Z')) ||
            ((c >= '0') && (c <= '9')) ||
            (c == '_'));
}

void UmlClassMember::write_type(FileOut & out, const UmlTypeSpec & t, QByteArray s, const char * k_name, const char * k_type)
{
    s = s.simplified();

    int index;

    // remove k_name and all after it except []
    if (k_name && *k_name && ((index = s.indexOf(k_name, 0)) != -1)) {//[rageek] Removed CS=FALSE - rethink this, case sensitive
        //remove name
        s.remove(index, strlen(k_name));

        for (;;) {
            if (s[index] == ' ')
                s.remove(index, 1);

            if (s[index] != '[')
                break;

            index += 1;

            int index2;

            if ((index2 = s.indexOf(index, ']')) == -1)
                break;

            index = index2 + 1;
        }

        s.resize(index);
    }
    else if ((index = s.indexOf('=')) != -1) {
        s.resize(index);
        s = s.simplified();
    }

    if (k_type && *k_type && ((index = s.indexOf(k_type)) == -1))
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

void UmlClassMember::remove_comments(QByteArray & s)
{
    int index;

    if ((index = s.indexOf("${comment}")) != -1)
        s.replace(index, 10, " ");

    index = 0;

    while ((index = s.indexOf('#', index)) != -1) {
        int index2 = s.indexOf('\n', index + 1);

        if (index2 == -1) {
            s.resize(index);
            break;
        }

        s.remove(index, index2 - index);
    }

    index = 0;

    while ((index = s.indexOf("//", index)) != -1) {
        int index2 = s.indexOf('\n', index + 2);

        if (index2 == -1) {
            s.resize(index);
            break;
        }

        s.remove(index, index2 - index);
    }

    index = 0;

    while ((index = s.indexOf("/*", index)) != -1) {
        int index2 = s.indexOf("*/", index + 2);

        if (index2 == -1) {
            s.resize(index);
            break;
        }

        s.replace(index, index2 + 2 - index, " ");
    }

    s = s.simplified();
}

