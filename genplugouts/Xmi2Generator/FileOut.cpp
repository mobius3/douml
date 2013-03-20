
#include "FileOut.h"
#include "UmlItem.h"

#include <q3textstream.h>
#include <qfile.h>
#include <unordered_map>
//Added by qt3to4:
#include "misc/mystr.h"
FileOut::FileOut(QFile * fp, bool lf, bool utf8) : Q3TextStream(fp), _lf(lf), _indent(0)
{
    if (utf8)
        setEncoding(Q3TextStream::UnicodeUTF8);
}

void FileOut::indent()
{
    Q3TextStream & ts = *this;

    for (int n = _indent; n > 0; n -= 1)
        ts << '\t';
}

void FileOut::id(UmlItem * x)
{
    ((Q3TextStream &) *this) << " xmi:id=\"BOUML_" << ((void *) x->getIdentifier()) << "_" << x->kind() << '"';

}

void FileOut::id_prefix(UmlItem * x, const char * pfix)
{
    ((Q3TextStream &) *this) << " xmi:id=\"BOUML_" << pfix << ((void *) x->getIdentifier()) << "_" << x->kind() << '"';
}

void FileOut::id_prefix(UmlItem * x, const char * pfix, int n)
{
    ((Q3TextStream &) *this) << " xmi:id=\"BOUML_" << pfix << n << "_" << ((void *) x->getIdentifier()) << "_" << x->kind() << '"';
}

void FileOut::idref(UmlItem * x)
{
    ((Q3TextStream &) *this) << " xmi:idref=\"BOUML_" << ((void *) x->getIdentifier()) << "_" << x->kind() << '"';

}

void FileOut::idref(WrapperStr s, UmlItem * x)
{
    QString keys;
    {
        Q3TextStream keyst(&keys, QIODevice::WriteOnly);

        keyst << ((void *) x) << "_" << s.operator QString();
    }

    QMap<QString, int>::ConstIterator it =
            _modifiedtypes.find((const char *) keys);

    if (it == _modifiedtypes.end())
        it = _modifiedtypes.insert((const char *) keys, _modifiedtypes.count());

    ((Q3TextStream &) *this) << " xmi:idref=\"BOUML_basedontype_"
                             << it.data() << '"';

}

void FileOut::idref_prefix(UmlItem * x, const char * pfix)
{
    ((Q3TextStream &) *this) << " xmi:idref=\"BOUML_"
                             << pfix << ((void *) x->getIdentifier()) << "_" << x->kind() << '"';

}

void FileOut::idref_prefix(UmlItem * x, const char * pfix, int n)
{
    ((Q3TextStream &) *this) << " xmi:idref=\"BOUML_"
                             << pfix << n << "_" << ((void *) x->getIdentifier()) << "_" << x->kind() << '"';

}

void FileOut::idref_datatype(const WrapperStr & t)
{
    if (t.isEmpty())
        return;

    QMap<QString, int>::ConstIterator it = _datatypes.find(t);

    if (it == _datatypes.end())
        it = _datatypes.insert(t, _datatypes.count());

    ((Q3TextStream &) *this) << " xmi:idref=\"BOUML_datatype_"
                             << it.data() << '"';

}

void FileOut::ref(UmlItem * x, const char * pfix1, const char * pfix2)
{
    ((Q3TextStream &) *this) << " " << pfix1 << "=\"BOUML_"
                             << pfix2 << ((void *) x->getIdentifier()) << "_" << x->kind() << '"';
}

void FileOut::ref(UmlItem * x, const char * pfix1, const char * pfix2, int n)
{
    ((Q3TextStream &) *this) << " " << pfix1 << "=\"BOUML_"
                             << pfix2 << n << "_" << ((void *) x->getIdentifier()) << "_" << x->kind() << '"';
}

void FileOut::ref_only(UmlItem * x, const char * pfix)
{
    ((Q3TextStream &) *this) << "BOUML_" << pfix << ((void *) x->getIdentifier())
                             << "_" << x->kind();
}

void FileOut::define_datatypes(bool uml_20, bool primitive_type, bool gen_extension)
{
    const char * pfix = (primitive_type)
            ? ((uml_20) ? "<ownedMember xmi:type=\"uml:PrimitiveType\""
                        : "<packagedElement xmi:type=\"uml:PrimitiveType\"")
            : ((uml_20) ? "<ownedMember xmi:type=\"uml:DataType\""
                        : "<packagedElement xmi:type=\"uml:DataType\"");

    QMap<QString, int>::ConstIterator it;

    for (it = _datatypes.begin();
         it != _datatypes.end();
         ++it) {
        indent();
        (*this) << pfix << " xmi:id=\"BOUML_datatype_"
                        << it.data() << "\" name=\"";
        quote((const char *)it.key()); //[jasa] ambiguous call
        (*this) << "\"/>\n";
    }

    const char * postfix =
            (uml_20) ? "</ownedMember>\n" : "</packagedElement>\n";

    for (it = _modifiedtypes.begin();
         it != _modifiedtypes.end();
         ++it) {
        WrapperStr k = it.key();
        int index = k.find('_');

        indent();
        (*this) << pfix << " xmi:id=\"BOUML_basedontype_"
                        << it.data() << "\" name = \"";
        quote((const char *)k.mid(index + 1));
        (*this) << '"';

        if (gen_extension) {
            (*this) << ">\n";
            indent();
            (*this) << "\t<xmi:Extension extender=\"Bouml\">\n";
            indent();
            (*this) << "\t\t<basedOn \"BOUML_" << k.left(index).operator QString() << "\"/>\n";
            indent();
            (*this) << "\t</xmi:Extension>\n";
            indent();
            (*this) << postfix;
        }
        else
            (*this) << "/>\n";
    }
}

void FileOut::quote(const QString &s)
{
    int i = 0;
    static std::unordered_map <std::string, std::function<void()>> converter = {
    {"<", [&](){ (*this) <<  "&lt;";}},
    {">", [&](){ (*this) <<  "&gt;";}},
    {"\"", [&](){ (*this) <<  "&quot;";}},
    {"&", [&](){ (*this) <<  "&amp;";}},
    {"\n", [&](){if (_lf) (*this) << s.mid(i, 1); else (*this) << "&#10;";}},
    {"\r", [&](){if (_lf) (*this) << s.mid(i, 1); else (*this) << "&#13;";}},
};

    while(i < s.length())
    {
        if(converter.count(s.mid(i, 1).toStdString()) > 0)
            converter[s.mid(i, 1).toStdString()]();
        else
            (*this) << s.mid(i, 1);
        i++;
    }
}

