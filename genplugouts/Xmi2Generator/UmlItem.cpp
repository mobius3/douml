
#include "UmlItem.h"
#include "FileOut.h"
#include "UmlUseCaseDiagram.h"
#include "UmlTypeSpec.h"

#include "UmlCom.h"
#include "UmlClass.h"
//Added by qt3to4:
#include "misc/mystr.h"
#include <Q3ValueList>

UmlItem::~UmlItem()
{
}

void UmlItem::xmi(int, char **)
{
    UmlCom::trace("Error : must be applied on the project<br>");
}

void UmlItem::write(FileOut & out)
{
    const Q3PtrVector<UmlItem> ch = children();
    unsigned n = ch.size();

    for (unsigned i = 0; i != n; i += 1)
        ch[i]->write(out);

}

void UmlItem::write(FileOut &, bool)
{
}

void UmlItem::write_description_properties(FileOut & out)
{
    if (! description().isEmpty()) {
        static int rank = 0;

        out.indent();
        out << "<ownedComment xmi:type=\"uml:Comment\" xmi:id=\"COMMENT_"
            << ++rank << "\" body=\"";
        out.quote((const char *)description()); //[jasa] ambiguous call
        out << "\"/>\n";
    }

    WrapperStr ste = stereotype();

    if (_gen_extension) {
        const Q3Dict<WrapperStr> up = properties();
        Q3DictIterator<WrapperStr> it(up);

        if (it.current()) {
            out.indent();
            out << "<xmi:Extension extender=\"Bouml\">\n";

            if (! ste.isEmpty()) {
                out.indent();
                out << "\t<stereotype name=\"";
                out.quote((const char *)ste); //[jasa] ambiguous call
                out << "\"/>\n";
            }

            do {
                out.indent();
                out << "\t<taggedValue tag=\"";
                out.quote((const char *)it.currentKey()); //[jasa] ambiguous call
                out << "\" value=\"";
                out.quote((const char *) * (it.current())); //[jasa] ambiguous call
                out << "\"/>\n";
                ++it;
            }
            while (it.current());

            out.indent();
            out << "</xmi:Extension>\n";
        }
        else if (! ste.isEmpty()) {
            out.indent();
            out << "<xmi:Extension extender=\"Bouml\"><stereotype name=\"";
            out.quote((const char *)ste); //[jasa] ambiguous call
            out << "\"/></xmi:Extension>\n";
        }
    }

    if (ste.operator QString().contains(':') == 1)
        // probably a stereotype part of profile
        _stereotypes[ste].append(this);
}

void UmlItem::search_class_assoc()
{
}

void UmlItem::memo_relation(UmlItem * r)
{
    parent()->memo_relation(r);
}

void UmlItem::memo_ac_uc_assoc(UmlUseCaseDiagram * d)
{
    parent()->memo_ac_uc_assoc(d);
}

void UmlItem::write_multiplicity(FileOut & out, WrapperStr s, UmlItem * who)
{
    if (!s.isEmpty()) {
        WrapperStr min;
        WrapperStr max;
        int index = s.find("..");

        if (index != -1) {
            min = s.left(index).stripWhiteSpace();
            max = s.mid(index + 2).stripWhiteSpace();
        }
        else
            min = max = s.stripWhiteSpace();

        out.indent();
        out << "<lowerValue xmi:type=\"uml:LiteralString\"";
        out.id_prefix(who, "MULTIPLICITY_L_");
        out << " value=\"" << min.operator QString() << "\"/>\n";

        out.indent();
        out << "<upperValue xmi:type=\"uml:LiteralString\"";
        out.id_prefix(who, "MULTIPLICITY_U_");
        out << " value=\"" << max.operator QString() << "\"/>\n";
    }
}

void UmlItem::write_type(FileOut & out, const UmlTypeSpec & t, const char * tk)
{
    if (t.type != 0) {
        out.indent();
        out << '<' << ((tk != 0) ? tk : "type") << " xmi:type=\"uml:Class\"";
        out.idref(t.type);
        out << "/>\n";
    }
    else if (!t.explicit_type.isEmpty()) {
        out.indent();
        out << '<' << ((tk != 0) ? tk : "type") << " xmi:type=\"uml:";

        if (t.explicit_type == "int")
            out << ((_uml_20)
                    ? "PrimitiveType\" href=\"http://schema.omg.org/spec/UML/2.0/uml.xml#Integer\"/>\n"
                    : "PrimitiveType\" href=\"http://schema.omg.org/spec/UML/2.1/uml.xml#Integer\"/>\n");
        else if (t.explicit_type == "bool")
            out << ((_uml_20)
                    ? "PrimitiveType\" href=\"http://schema.omg.org/spec/UML/2.0/uml.xml#Boolean\"/>\n"
                    : "PrimitiveType\" href=\"http://schema.omg.org/spec/UML/2.1/uml.xml#Boolean\"/>\n");
        else if (t.explicit_type == "string")
            out << ((_uml_20)
                    ? "PrimitiveType\" href=\"http://schema.omg.org/spec/UML/2.0/uml.xml#String\"/>\n"
                    : "PrimitiveType\" href=\"http://schema.omg.org/spec/UML/2.1/uml.xml#String\"/>\n");
        else if (t.explicit_type == "long")
            out << ((_uml_20)
                    ? "PrimitiveType\" href=\"http://schema.omg.org/spec/UML/2.0/uml.xml#UnlimitedNatural\"/>\n"
                    : "PrimitiveType\" href=\"http://schema.omg.org/spec/UML/2.1/uml.xml#UnlimitedNatural\"/>\n");
        else {
            out << "Class\"";
            out.idref_datatype(t.explicit_type);
            out << "/>\n";
        }
    }

}

void UmlItem::write_default_value(FileOut & out, WrapperStr v, UmlItem * who, int rank)
{
    if (! v.isEmpty()) {
        if (v[0] == '=') {
            v = v.mid(1);

            if (v.isEmpty())
                return;
        }

        out.indent();
        out << "<defaultValue xmi:type=\"uml:LiteralString\"";

        if (rank == -1)
            out.id_prefix(who, "VALUE_");
        else
            out.id_prefix(who, "VALUE", rank);

        out << " value=\"";
        out.quote((const char *)v); //[jasa] ambiguous call
        out << "\"/>\n";
    }
}

void UmlItem::write_stereotyped(FileOut & out)
{
    QMap<QString, Q3PtrList<UmlItem> >::Iterator it;

    for (it = _stereotypes.begin(); it != _stereotypes.end(); ++it) {
        const char * st = it.key();
        UmlClass * cl = UmlClass::findStereotype(it.key(), TRUE);

        if (cl != 0) {
            Q3ValueList<WrapperStr> extended;

            cl->get_extended(extended);

            Q3PtrList<UmlItem> & l = it.data();
            UmlItem * elt;

            for (elt = l.first(); elt != 0; elt = l.next()) {
                out << "\t<" << st;
                out.id_prefix(elt, "STELT_");

                const Q3Dict<WrapperStr> props = elt->properties();
                Q3DictIterator<WrapperStr> itp(props);

                while (itp.current()) {
                    QString k = itp.currentKey();

                    if (k.contains(':') == 2) {
                        out << " ";
                        out.quote((const char *)k.mid(k.findRev(':') + 1)); //[jasa] ambiguous call
                        out << "=\"";
                        out.quote((const char *)*itp.current());
                        out << '"';
                    }

                    ++itp;
                }

                Q3ValueList<WrapperStr>::Iterator iter_extended;

                for (iter_extended = extended.begin();
                     iter_extended != extended.end();
                     ++iter_extended) {
                    WrapperStr vr = "base_" + *iter_extended;

                    out.ref(elt, vr);
                }

                out << "/>\n";

                elt->unload();
            }
        }
    }

}

bool UmlItem::gen_extension()
{
    return _gen_extension;
}

bool UmlItem::_gen_views;

Language UmlItem::_lang;

bool UmlItem::_uml_20;

bool UmlItem::_pk_prefix;

bool UmlItem::_vis_prefix;

bool UmlItem::_primitive_type;

bool UmlItem::_linefeed;

bool UmlItem::_gen_extension;

bool UmlItem::_gen_eclipse;

QMap<QString, Q3PtrList<UmlItem> > UmlItem::_stereotypes;

