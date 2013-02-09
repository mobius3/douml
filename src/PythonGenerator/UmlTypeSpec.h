//Added by qt3to4:
#include "misc/mystr.h"
#include <QTextStream>
#ifndef _UMLTYPESPEC_H
#define _UMLTYPESPEC_H

class QTextStream;
class UmlArtifact;

#include "UmlBaseTypeSpec.h"

// this class memorize a type specification, which may be
//
// - a class reference
//
// - an explicit type
class UmlTypeSpec : public UmlBaseTypeSpec
{
public:
    void generate_import(QTextStream & f, UmlArtifact * using_art, bool from, WrapperStr & made) const;
};

#endif
