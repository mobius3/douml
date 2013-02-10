// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
// Copyright 2012-2013 Nikolai Marchenko.
// Copyright 2012-2013 Leonardo Guilherme.
//
// This file is part of the DOUML Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License Version 3.0 as published by
// the Free Software Foundation and appearing in the file LICENSE.GPL included in the
//  packaging of this file.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License Version 3.0 for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// e-mail : doumleditor@gmail.com
// home   : http://sourceforge.net/projects/douml
//
// *************************************************************************
#include <qapplication.h>
//Added by qt3to4:
#include "misc/mystr.h"

#include "UmlCom.h"
#include "UmlItem.h"
#include "CppSettings.h"
#include "UmlPackage.h"
#include "Package.h"
#include "Lex.h"
#include "Statistic.h"
#include "Logging/QsLogDest.h"
#include "Logging/QsLog.h"
#include <QDir>
#include <QTest>

int main(int argc, char ** argv)
{
    if (argc != 2)
        return 0;

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#ifdef DEBUG
    QsLogging::Logger & logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    QDir dir;
    dir.setPath(qApp->applicationDirPath());
    dir.remove(QString("cpp_reverse") + QString(".log"));
    const QString sLogPath(QDir(qApp->applicationDirPath()).filePath(QString("cpp_reverse") + QString(".log")));
    QsLogging::DestinationPtr fileDestination(QsLogging::DestinationFactory::MakeFileDestination(sLogPath));
    QsLogging::DestinationPtr debugDestination(QsLogging::DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(debugDestination.get());
    logger.addDestination(fileDestination.get());
    QLOG_INFO() << "Starting the log";
#endif
    //QTest::qSleep(7000);
    if (UmlCom::connect(WrapperStr(argv[1]).operator QString().toUInt())) {
        try {
            //UmlCom::with_ack(FALSE);
            UmlCom::trace("<b>C++ reverse</b> release 2.15<br>");
            UmlCom::traceAutoRaise(FALSE);

            UmlItem * item = UmlCom::targetItem();

            if (item->kind() != aPackage)
                UmlCom::trace("<font face=helvetica><b>must be applied on a <i>package</i></b></font><br><hr><br>");
            else {
                char * argv = 0;
                int argc = 0;
                QApplication * app = new QApplication(argc, &argv);

                /* lgfreitas: This initiates the root package as well, using the item provided by the
                 connection above */
                Package::init((UmlPackage *) item, app);

                WrapperStr f;

                if (UmlPackage::getProject()->propertyValue("#file", f))
                    Lex::defines(f);

                // add c++ catalog like java ?

                int n;

                /* lgfreitas: This is where the reversing happens */
                Package::scan_dirs(n);

                if (n != 0) {
                    CppSettings::set_UseDefaults(TRUE);
                    Package::send_dirs(n, TRUE);
                    Statistic::produce();
                }
            }
        }
        catch (...) {
        }

        try {
            // socket may be already closed
            UmlCom::message("");
            UmlCom::showTrace();
            UmlCom::bye(0);	// application must not be deleted
        }
        catch (...) {
        }
    }

    UmlCom::close();
    return 0;
}
