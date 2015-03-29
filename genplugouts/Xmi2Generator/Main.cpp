#include <qapplication.h>

#include "UmlCom.h"
#include "UmlItem.h"

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
            // warning : update release number in UmlPackage::xmi !
            UmlCom::trace("<b>Xmi 2.1 generator</b> release 1.14.1<br>");
#ifdef habip
            UmlCom::targetItem()->xmi(argc - 2, argv + 1);
#else
            char* args[]={
                "gxmi2","1024"
            };
            UmlCom::targetItem()->xmi(0, args + 1);
#endif
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
