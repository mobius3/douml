
#include "FileWriter.h"

#include <q3textstream.h>
#include <qfile.h>
//Added by qt3to4:
#include <Q3CString>

bool FileWriter::open(Q3CString s)
{
    f = new QFile(s);

    if (! f->open(QIODevice::WriteOnly)) {
        delete f;
        return FALSE;
    }

    ts = new Q3TextStream(f);
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

void FileWriter::write(Q3CString s)
{
    ts->writeRawBytes(s, s.length());
}

void FileWriter::write(const char * s)
{
    ts->writeRawBytes(s, strlen(s));
}

void FileWriter::write(char c)
{
    ts->writeRawBytes(&c, 1);
}

void FileWriter::write(unsigned n)
{
    Q3CString s;

    s.setNum(n);

    ts->writeRawBytes(s, s.length());

}

