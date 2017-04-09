
#include "FileWriter.h"

#include <QTextStream.h>
#include <qfile.h>
//Added by qt3to4:
#include <QByteArray>

bool FileWriter::open(QByteArray s)
{
    f = new QFile(s);

    if (! f->open(QIODevice::WriteOnly)) {
        delete f;
        return FALSE;
    }

    ts = new QTextStream(f);
    return TRUE;
}

void FileWriter::close()
{
    f->flush();
    f->close();
    delete ts;
    delete f;
    f = 0;
    ts = 0;
}

void FileWriter::write(QByteArray s)
{
    //ts->writeRawBytes(s, s.length());
    *ts<<s;
}

void FileWriter::write(const char * s)
{
    //ts->writeRawBytes(s, strlen(s));
    *ts<<s;
}

void FileWriter::write(char c)
{
    //ts->writeRawBytes(&c, 1);
    *ts<<c;
}

void FileWriter::write(unsigned n)
{
    QByteArray s;

    s.setNum(n);

    //ts->writeRawBytes(s, s.length());
    *ts<<s;

}

