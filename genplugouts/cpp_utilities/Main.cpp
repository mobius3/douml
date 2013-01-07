#include <qapplication.h>

#include "UmlCom.h"
#include "UmlItem.h"
#include "Logging/QsLog.h"

// the program is called with the socket port number in argument

int main(int argc, char ** argv)
{
    QsLogging::Logger & logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    QDir dir;
    dir.setPath(qApp->applicationDirPath());
    dir.remove(QString("cpp_generator") + QString(".log"));
    const QString sLogPath(QDir(qApp->applicationDirPath()).filePath(QString("cpp_generator") + QString(".log")));
    QsLogging::DestinationPtr fileDestination(QsLogging::DestinationFactory::MakeFileDestination(sLogPath));
    QsLogging::DestinationPtr debugDestination(QsLogging::DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(debugDestination.get());
    logger.addDestination(fileDestination.get());

    if (argc != 2)
        return 0;

    QApplication a(argc, argv);

    if (UmlCom::connect(QString(argv[1]).toUInt())) {
        UmlCom::trace("<b>Class utilities</b> release 1.1.2<hr>");

        try {
            UmlCom::targetItem()->utilities();
        }
        catch (...) {
        }

        // must be called to cleanly inform that all is done
        UmlCom::bye();
    }

    UmlCom::close();
    return 0;
}
