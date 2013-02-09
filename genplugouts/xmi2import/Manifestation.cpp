
#include "Manifestation.h"
#include "UmlArtifact.h"
#include "FileIn.h"
#include "Token.h"
//Added by qt3to4:
#include "misc/mystr.h"
#include <Q3ValueList>

void Manifestation::import(FileIn & in, Token & token, UmlArtifact * artifact)
{
    WrapperStr s;
    WrapperStr name;
    WrapperStr utilized;

    name = token.valueOf("name");

    if (!(s = token.valueOf("utilizedelement")).isEmpty())
        utilized = s;
    else if (!(s = token.valueOf("client")).isEmpty())
        utilized = s;

    if (! token.closed()) {
        WrapperStr k = token.what();
        const char * kstr = k;

        while (in.read(), !token.close(kstr)) {
            s = token.what();

            if (s == "utilizedelement")
                utilized = token.xmiIdref();
            else if ((s == "client") && s.isEmpty())
                utilized = token.xmiIdref();

            if (! token.closed())
                in.finish(s);
        }
    }

    if (utilized.isEmpty())
        in.warning("'utilizedElement' and 'client' missing in Manifestation");
    else
        All.append(Manifestation(name, artifact, utilized));
}

void Manifestation::solveThem()
{
    Q3ValueList<Manifestation>::Iterator it;

    for (it = All.begin(); it != All.end(); ++it)
        (*it).artifact->solveManifestation((*it).name, (*it).utilized);

    All.clear();
}

Q3ValueList<Manifestation> Manifestation::All;

