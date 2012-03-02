// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
//
// This file is part of the BOUML Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// e-mail : bouml@free.fr
// home   : http://bouml.free.fr
//
// *************************************************************************

#include "UmlCom.h"
#include "UmlItem.h"
#include "util.h"
//Added by qt3to4:
#include <Q3CString>
#include <QApplication>
#include <QDir>
#include "Logging/QsLog.h"
#include "Logging/QsLogDest.h"
int main(int argc, char ** argv)
{

    QsLogging::Logger& logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    QDir dir;
    dir.setPath(qApp->applicationDirPath());
    dir.remove(QString("cpp_generator") + QString(".log"));
    const QString sLogPath(QDir(qApp->applicationDirPath()).filePath(QString("cpp_generator") + QString(".log")));
    QsLogging::DestinationPtr fileDestination(QsLogging::DestinationFactory::MakeFileDestination(sLogPath) );
    QsLogging::DestinationPtr debugDestination(QsLogging::DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(debugDestination.get());
    logger.addDestination(fileDestination.get());

    QLOG_INFO() << " STARTING CPP_GENERATOR";

    int port_index;
  
  if (argc == 2)
  {
      port_index = 1;
      QLOG_INFO() << "Got two arguments from Douml as argv";
      QLOG_INFO() << "Using first port index mode";
  }
  else if (argc == 3)
  {
      QLOG_INFO() << "Got three arguments from Douml as argv";
      if (argv[1][1] == 'v')
      {
          QLOG_INFO() << "Using verbose mode";
          set_verbose();
      }
      else
      {
          QLOG_INFO() << "Using preserve mode";
          set_preserve();
      }
      QLOG_INFO() << "Using second port index mode";
      port_index = 2;
  }
  else if (argc == 4)
  {
    QLOG_INFO() << "Got four arguments from Douml as argv";
    QLOG_INFO() << "Using preserve mode";
    QLOG_INFO() << "Using verbose mode";
    QLOG_INFO() << "Using third port index mode";
    set_verbose();
    set_preserve();
    port_index = 3;
  }
  else
  {
      QLOG_INFO() << "Got too little or too much arguments from Douml, exiting";
      return 0;
  }
  


  if (UmlCom::connect(QString(argv[port_index]).toUInt())) {
    try {
      UmlCom::trace("<b>C++ generator</b> release 2.18<br>");
      UmlCom::traceAutoRaise(FALSE);
      UmlCom::targetItem()->generate();      
      
      Q3CString s;
      
      s.sprintf("<hr><font face=helvetica>Generation done : %d warnings, %d errors</font><br>",
		n_warnings(), n_errors());
      UmlCom::trace(s);

      UmlCom::showTrace();
      UmlCom::message("");
    
      UmlCom::bye(n_errors());
    }
    catch (...)
      {
          QLOG_INFO() << "unhandled exception caught";
      }
  }
  
  UmlCom::close();
  return 0;
}
