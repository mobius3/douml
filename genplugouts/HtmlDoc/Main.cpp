#include <qapplication.h>
//Added by qt3to4:
#include <QByteArray>

#include "UmlCom.h"
#include "UmlItem.h"
#include "UmlDiagram.h"
#include "UmlClass.h"

// the program is called with the socket port number in argument

int main(int argc, char ** argv)
{
#define habip
#ifdef habip
    if (argc < 2)
        return 0;
#endif
    QApplication a(argc, argv);
#ifdef habip
    if (UmlCom::connect(QString(argv[argc - 1]).toUInt())) {
#else
    if (UmlCom::connect(5000)) {
#endif
        try {
            UmlCom::trace("<b>Html generator</b> release 2.20 (C++ version)<br />");

            UmlItem * target = UmlCom::targetItem();
#ifdef habip
            target->set_dir(argc - 2, argv + 1);
#else
            char* args[]={
                "ghtml","1024"
            };
            target->set_dir(0, args+1);
#endif
            UmlCom::message("Memorize references ...");
            target->memo_ref();
            UmlItem::frame();
            UmlCom::message("Indexes ...");
            UmlItem::generate_indexes();
            UmlItem::start_file("index", target->name() + "\nDocumentation", FALSE);
            target->html(QByteArray(""), 0u, 0u);
            UmlItem::end_file();
            UmlItem::start_file("navig", "", TRUE);
            UmlItem::end_file();
            UmlClass::generate();
            UmlCom::trace("Done");
            UmlCom::message("");
        }
        catch (...) {
        }

        // must be called to cleanly inform that all is done
        UmlCom::bye(0);
    }
#ifdef habip
#undef habip
#endif
    UmlCom::close();
    return 0;
}
