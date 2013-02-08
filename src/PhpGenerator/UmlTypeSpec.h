#ifndef _UMLTYPESPEC_H
#define _UMLTYPESPEC_H


#include "UmlBaseTypeSpec.h"
//Added by qt3to4:
#include "misc/mystr.h"
#include <QTextStream>

class QTextStream;
class UmlArtifact;

// this class memorize a type specification, which may be
//
// - a class reference
//
// - an explicit type
class UmlTypeSpec : public UmlBaseTypeSpec
{
public:
    void generate_require_onces(QTextStream & f,
                                WrapperStr & made,
                                UmlArtifact * using_art) const;
};

#endif
