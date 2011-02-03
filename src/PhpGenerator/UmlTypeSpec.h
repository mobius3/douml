#ifndef _UMLTYPESPEC_H
#define _UMLTYPESPEC_H


#include "UmlBaseTypeSpec.h"
//Added by qt3to4:
#include <Q3CString>
#include <QTextOStream>

class QTextOStream;
class UmlArtifact;

// this class memorize a type specification, which may be
//
// - a class reference
//
// - an explicit type
class UmlTypeSpec : public UmlBaseTypeSpec {
  public:
    void generate_require_onces(QTextOStream & f,
				Q3CString & made,
				UmlArtifact * using_art) const;
};

#endif
