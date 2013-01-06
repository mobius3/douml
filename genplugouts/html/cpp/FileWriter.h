#ifndef _FILEWRITER_H
#define _FILEWRITER_H


#include <q3cstring.h>
//Added by qt3to4:
#include <Q3TextStream>

class QFile;
class Q3TextStream;

// The original html generator was written in Java to test the Java
// version of the API, this class allows to have a source code similar
// in C++
class FileWriter
{
public:
    bool open(Q3CString s);

    void close();

    void write(Q3CString s);

    void write(const char * s);

    void write(char c);

    void write(unsigned n);


protected:
    Q3TextStream * ts;

    QFile * f;

};

#endif
