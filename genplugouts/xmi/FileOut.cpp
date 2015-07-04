
#include "FileOut.h"
#include "UmlItem.h"

#include <qtextstream.h>
#include <qfile.h>
//Added by qt3to4:
#include <QByteArray>
FileOut::FileOut(QFile * fp) : QTextStream(fp), _indent(0)
{
}

void FileOut::indent()
{
    QTextStream & ts = *this;

    for (int n = _indent; n > 0; n -= 1)
        ts << '\t';
}

void FileOut::id(const UmlItem * x)
{
    ((QTextStream &) *this) << " xmi.id=\"BOUML_" << ((void *) x) << '"';

}

void FileOut::idref(const UmlItem * x)
{
    ((QTextStream &) *this) << " xmi.idref=\"BOUML_" << ((void *) x) << '"';

}

void FileOut::idref(QByteArray s, const UmlItem * x)
{
    QString keys;
    {
        QTextStream keyst(&keys, QIODevice::WriteOnly);

        keyst << ((void *) x) << "_" << s;
    }

    QMap<QByteArray, int>::ConstIterator it =
        _modifiedtypes.find((const char *) keys.toLatin1().constData());

    if (it == _modifiedtypes.end())
        it = _modifiedtypes.insert((const char *) keys.toLatin1().constData(), _modifiedtypes.count());

    ((QTextStream &) *this) << " xmi.idref=\"BOUML_basedontype_"
                             << it.value() << '"';

}

void FileOut::ref(const UmlItem * x)
{
    ((QTextStream &) *this) << "BOUML_" << ((void *) x);
}

void FileOut::idref_datatype(const QByteArray & t)
{
    QMap<QByteArray, int>::ConstIterator it = _datatypes.find(t);

    if (it == _datatypes.end())
        it = _datatypes.insert(t, _datatypes.count());

    ((QTextStream &) *this) << " xmi.idref=\"BOUML_datatype_"
                             << it.value() << '"';

}

void FileOut::define_datatypes(int taggedvalue_mode)
{
    QMap<QByteArray, int>::ConstIterator it;

    for (it = _datatypes.begin();
         it != _datatypes.end();
         ++it) {
        indent();
        (*this) << "<UML:DataType xmi.id=\"BOUML_datatype_"
                << it.value() << "\" name = \"";
        quote(it.key());
        (*this) << "\" visibility=\"private\" isRoot=\"false\" isLeaf=\"false\" isAbstract=\"false\"/>\n";
    }

    for (it = _modifiedtypes.begin();
         it != _modifiedtypes.end();
         ++it) {
        QByteArray k = it.key();
        int index = k.indexOf('_');

        indent();
        (*this) << "<UML:DataType xmi.id=\"BOUML_basedontype_"
                << it.value() << "\" name = \"";
        quote(k.mid(index + 1));
        (*this) << "\" visibility=\"private\" isRoot=\"false\" isLeaf=\"false\" isAbstract=\"false\">\n";

        switch (taggedvalue_mode) {
        case 1:
            indent();
            (*this) << "\t<UML:ModelElement.taggedValue>\n";
            indent();
            (*this) << "\t\t<UML:TaggedValue tag=\"basedOn\" value=\"BOUML_"
                    << k.left(index) << "\"/>\n";
            indent();
            (*this) << "\t</UML:ModelElement.taggedValue>\n";
            break;

        case 2:
            indent();
            (*this) << "\t<UML:ModelElement.taggedValue>\n";
            indent();
            (*this) << "\t\t<UML:TaggedValue.tag>basedOn</UML:TaggedValue.tag>\n";
            indent();
            (*this) << "\t\t<UML:TaggedValue.value>BOUML_" << k.left(index) << "</UML:TaggedValue.value>\n";
            indent();
            (*this) << "\t</UML:ModelElement.taggedValue>\n";
            break;
        }

        indent();
        (*this) << "</UML:DataType>\n";
    }
}

void FileOut::quote(const char * s)
{
    for (;;) {
        switch (*s) {
        case 0:
            return;

        case '<':
            (*this) << "&lt;";
            break;

        case '>':
            (*this) << "&gt;";
            break;

        case '"':
            (*this) << "&quot;";
            break;

        case '&':
            (*this) << "&amp;";
            break;

        default:
            (*this) << *s;
        }

        s += 1;
    }
}

