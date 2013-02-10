#include <qapplication.h>

#include "UmlCom.h"
#include "UmlItem.h"
#include "Logging/QsLog.h"
#include "Logging/QsLogDest.h"
#include <QDir>

// the program is called with the socket port number in argument

int main(int argc, char ** argv)
{
#ifdef DEBUG
    QsLogging::Logger & logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    QDir dir;
    dir.setPath(qApp->applicationDirPath());
    dir.remove(QString("cpp_uyils") + QString(".log"));
    const QString sLogPath(QDir(qApp->applicationDirPath()).filePath(QString("cpp_utils") + QString(".log")));
    QsLogging::DestinationPtr fileDestination(QsLogging::DestinationFactory::MakeFileDestination(sLogPath));
    QsLogging::DestinationPtr debugDestination(QsLogging::DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(debugDestination.get());
    logger.addDestination(fileDestination.get());
    QLOG_INFO() << "Starting the log";
#endif
    if (argc != 2)
        return 0;

    QApplication a(argc, argv);
    QLOG_INFO()  << "Attempting to connect";
    if (UmlCom::connect(QString(argv[1]).toUInt()))
    {
        QLOG_INFO() << "<b>Class utilities</b> release 1.1.2<hr>";
        UmlCom::trace("<b>Class utilities</b> release 1.1.2<hr>");

        try {
            QLOG_INFO() << 1;
            UmlCom::targetItem()->utilities();
            QLOG_INFO() << 2;
        }
        catch (...) {
            QLOG_INFO() << 3;
        }

        // must be called to cleanly inform that all is done
        UmlCom::bye();
    }

    UmlCom::close();
    return 0;
}
