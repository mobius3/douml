
#include "UmlDeploymentView.h"
#include "Context.h"

void UmlDeploymentView::change(Context & ctx)
{
    if (ctx.onArtifact()) {
        const Q3PtrVector<UmlItem> ch = children();
        unsigned i;

        for (i = 0; i != ch.size(); i += 1)
            ch[i]->change(ctx);

        unload(TRUE, TRUE);
    }
}

