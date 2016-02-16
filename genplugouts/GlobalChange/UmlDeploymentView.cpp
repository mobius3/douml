
#include "UmlDeploymentView.h"
#include "Context.h"
#include <QVector>

void UmlDeploymentView::change(Context & ctx)
{
    if (ctx.onArtifact()) {
        const QVector<UmlItem*> ch = children();
        int i;

        for (i = 0; i != ch.size(); i += 1)
            ch[i]->change(ctx);

        unload(TRUE, TRUE);
    }
}

