//#define TRACE
#ifdef TRACE
#include <iostream>
//Added by qt3to4:


using namespace std;
#endif

#include "UmlCom.h"

#include <q3socketdevice.h>

#include "UmlCom.h"
#include "UmlItem.h"
#include "UmlTypeSpec.h"
#include "UmlClass.h"
#include "UmlSettings.h"
#include "Tools/ApiCmd.h"
#include "Logging/QsLog.h"

bool UmlCom::connect(unsigned int port)
{
    sock = new Q3SocketDevice(Q3SocketDevice::Stream);
    sock->setAddressReusable(TRUE);

    buffer_in_size = 1024;
    buffer_in = new char[buffer_in_size];
    buffer_in_end = p_buffer_in = 0;

    buffer_out_size = 1024;
    buffer_out = new char[buffer_out_size];
    p_buffer_out = buffer_out + 4/*bytes for length*/;

    QHostAddress ha;

    ha.setAddress("127.0.0.1");

    if (sock->connect(ha, port)) {
        // send API version
        QLOG_INFO() << "Sending API version";
        write_unsigned(APIVERSION);
        flush();
        return TRUE;
    }
    else
        return FALSE;
}

UmlItem * UmlCom::targetItem()
{
    send_cmd(miscGlobalCmd, targetCmd);
    return UmlBaseItem::read_();
}

void UmlCom::trace(const char * s)
{
    send_cmd(miscGlobalCmd, traceCmd, s);
}

void UmlCom::showTrace()
{
    send_cmd(miscGlobalCmd, showTraceCmd);
}

void UmlCom::traceAutoRaise(bool y)
{
    send_cmd(miscGlobalCmd, traceAutoRaiseCmd, (y == 0) ? 0 : 1);
}

void UmlCom::message(const char * s)
{
    send_cmd(miscGlobalCmd, messageCmd, s);
}

void UmlCom::bye(int v)
{
    send_cmd(miscGlobalCmd, byeCmd, v, "");
}

void UmlCom::close()
{
    delete sock;
    sock = 0;
}

Q3SocketDevice * UmlCom::sock;

char * UmlCom::buffer_in;

unsigned int UmlCom::buffer_in_size;

char * UmlCom::p_buffer_in;

char * UmlCom::buffer_in_end;

char * UmlCom::buffer_out;

char * UmlCom::p_buffer_out;

unsigned int UmlCom::buffer_out_size;

void UmlCom::check_size_out(unsigned int len)
{
    QLOG_INFO() << "Size check initiated for length :" << len;
    unsigned used = p_buffer_out - buffer_out;

    if ((used + len) >= buffer_out_size) {
        buffer_out_size = used + len + 1024;

        QLOG_INFO() << "Allocating new buffer fo size :" << buffer_out_size;
        char * newbuff = new char[buffer_out_size];

        memcpy(newbuff, buffer_out, used);
        delete [] buffer_out;

        p_buffer_out = (buffer_out = newbuff) + used;
    }
}

void UmlCom::read_if_needed()
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::read_if_needed " << buffer_in_end - p_buffer_in << '\n';
#endif

    if (p_buffer_in == buffer_in_end) {
        read_buffer(4);
#ifdef TRACE
        QLOG_INFO() << "UmlCom::read " << ((((unsigned char *) buffer_in)[0] << 24) + (((unsigned char *) buffer_in)[1] << 16) + (((unsigned char *) buffer_in)[2] << 8) + ((unsigned char *) buffer_in)[3]) << " bytes\n";
#endif
        read_buffer((((unsigned char *) buffer_in)[0] << 24) +
                    (((unsigned char *) buffer_in)[1] << 16) +
                    (((unsigned char *) buffer_in)[2] << 8) +
                    ((unsigned char *) buffer_in)[3]);
    }
}

void UmlCom::read_buffer(unsigned int len)
{
#ifdef TRACE
    QLOG_INFO() << "enter UmlCom::read_buffer(" << len << ")\n";
#endif

    if (buffer_in_size < len) {
        delete [] buffer_in;
        buffer_in_size = len + 256;
        buffer_in = new char[buffer_in_size];
    }

    int remainder = (int) len;
    int nread;
    char * p = buffer_in;

    for (;;) {
        if ((nread = sock->readBlock(p, remainder)) == -1) {
            if (sock->error() != 0) {
#ifdef TRACE
                QLOG_INFO() << "UmlCom::read_buffer ERROR, already " << p - buffer_in
                            << " remainder " << remainder << '\n';
#endif
                fatal_error("UmlCom read error");
            }
            else
                nread = 0;
        }

#ifdef TRACE
        QLOG_INFO() << "UmlCom a lu " << nread << '\n';
        QLOG_INFO() << "Data read :" << QString::fromLatin1(buffer_in, nread);
#endif

        if ((remainder -= nread) == 0)
            break;

        p += nread;
        sock->waitForMore(100);
    }

#ifdef TRACE
    QLOG_INFO() << "exit UmlCom::read_buffer()\n";
#endif

    p_buffer_in = buffer_in;
    buffer_in_end = buffer_in + len;
}

void UmlCom::write_bool(bool b)
{
    check_size_out(1);

    *p_buffer_out++ = (b == 0) ? 0 : 1;
}

void UmlCom::write_char(char c)
{
    check_size_out(1);

    *p_buffer_out++ = c;
}

void UmlCom::write_unsigned(unsigned int u)
{
    QLOG_INFO() << "Writing unsigned" << u;

    check_size_out(4);

    p_buffer_out[0] = u >> 24;
    p_buffer_out[1] = u >> 16;
    p_buffer_out[2] = u >> 8;
    p_buffer_out[3] = u;

    p_buffer_out += 4;
}

void UmlCom::write_id(const void * id)
{
    check_size_out(sizeof(void *));

    memcpy(p_buffer_out, &id, sizeof(void *));
    p_buffer_out += sizeof(void *);
}

void UmlCom::write_string(const char * p)
{
    if (p == 0)
        p = "";

    unsigned len = strlen(p) + 1;

    check_size_out(len);
    memcpy(p_buffer_out, p, len);
    p_buffer_out += len;
}

void UmlCom::send_cmd(CmdFamily f, unsigned int cmd)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd((CmdFamily) " << f << ", " << cmd << ")\n";
#endif

    write_char(f);
    write_char(cmd);
    flush();
}

void UmlCom::send_cmd(CmdFamily f, unsigned int cmd, char arg)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd((CmdFamily) " << f << ", " << cmd << ", " << (int) arg << ")\n";
#endif

    write_char(f);
    write_char(cmd);
    write_char(arg);
    flush();
}

void UmlCom::send_cmd(CmdFamily f, unsigned int cmd, int arg, const char *)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd((CmdFamily) " << f << ", " << cmd << ", " << arg << ")\n";
#endif

    write_char(f);
    write_char(cmd);
    write_unsigned((unsigned) arg);
    flush();
}

void UmlCom::send_cmd(CmdFamily f, unsigned int cmd, void * id)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd((CmdFamily) " << f << ", " << cmd << ", " << id << ")\n";
#endif

    write_char(f);
    write_char(cmd);
    write_id(id);
    flush();
}

void UmlCom::send_cmd(CmdFamily f, unsigned int cmd, const char * s)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd((CmdFamily) " << f << ", " << cmd << ", " << ((s) ? s : "") << ")\n";
#endif

    write_char(f);
    write_char(cmd);
    write_string(s);
    flush();
}

void UmlCom::send_cmd(CmdFamily f, unsigned int cmd, const char * s, bool b)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd((CmdFamily) " << f << ", " << cmd << ", " << ((s) ? s : "") << b << ")\n";
#endif

    write_char(f);
    write_char(cmd);
    write_string(s);
    write_bool(b);
    flush();
}

void UmlCom::send_cmd(CmdFamily f, unsigned int cmd, void * id, const char * n)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd((CmdFamily) " << f << ", " << cmd << ", " << id << ", " << ((n) ? n : "") << ")\n";
#endif

    write_char(f);
    write_char(cmd);
    write_id(id);
    write_string(n);
    flush();
}

void UmlCom::send_cmd(CmdFamily f, unsigned int cmd, const char * s, const char * v)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd((CmdFamily) " << f << ", " << cmd << ", " << ((s) ? s : "") << ", " << ((v) ? v : "") << ")\n";
#endif

    write_char(f);
    write_char(cmd);
    write_string(s);
    write_string(v);
    flush();
}

void UmlCom::send_cmd(CmdFamily f, unsigned int cmd, bool b, const char * s, const char * v)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd((CmdFamily) " << f << ", " << cmd << ", " << b << ", " << ((s) ? s : "") << ", " << ((v) ? v : "") << ")\n";
#endif

    write_char(f);
    write_char(cmd);
    write_bool(b);
    write_string(s);
    write_string(v);
    flush();
}

void UmlCom::send_cmd(const void * id, OnInstanceCmd cmd)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd(id, " << cmd << ")\n";
#endif

    write_char(onInstanceCmd);
    write_id(id);
    write_char(cmd);
    flush();
}

void UmlCom::send_cmd(const void * id, OnInstanceCmd cmd, const char * arg)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd(id, " << cmd << ", " << ((arg) ? arg : "") << ")\n";
#endif

    write_char(onInstanceCmd);
    write_id(id);
    write_char(cmd);
    write_string(arg);
    flush();
}

void UmlCom::send_cmd(const void * id, OnInstanceCmd cmd, char arg)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd(id, " << cmd << ", " << ((int) arg) << '\n';
#endif

    write_char(onInstanceCmd);
    write_id(id);
    write_char(cmd);
    write_char(arg);
    flush();
}

void UmlCom::send_cmd(const void * id, OnInstanceCmd cmd, unsigned int arg)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd(id, " << cmd << ", " << arg << '\n';
#endif

    write_char(onInstanceCmd);
    write_id(id);
    write_char(cmd);
    write_unsigned(arg);
    flush();
}

void UmlCom::send_cmd(const void * id, OnInstanceCmd cmd, const UmlTypeSpec & arg)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd(id, " << cmd << ", UmlTypeSpec)\n";
#endif

    write_char(onInstanceCmd);
    write_id(id);
    write_char(cmd);

    if (arg.type) {
        write_id(arg.type->_identifier);
        write_string("");
    }
    else {
        write_id(0);
        write_string(arg.explicit_type);
    }

    flush();
}

void UmlCom::send_cmd(const void * id, OnInstanceCmd cmd, const char * arg1, const char * arg2)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd(id, " << cmd << ", " << ((arg1) ? arg1 : "") << ", " << ((arg2) ? arg2 : "") << ")\n";
#endif

    write_char(onInstanceCmd);
    write_id(id);
    write_char(cmd);
    write_string(arg1);
    write_string(arg2);
    flush();
}

void UmlCom::send_cmd(const void * id, OnInstanceCmd cmd, anItemKind arg1, const char * arg2)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd(id, " << cmd << ", " << arg1 << ", " << ((arg2) ? arg2 : "") << ")\n";
#endif

    write_char(onInstanceCmd);
    write_id(id);
    write_char(cmd);
    write_char(arg1);
    write_string(arg2);
    flush();
}

void UmlCom::send_cmd(const void * id, OnInstanceCmd cmd, anItemKind arg1, aRelationKind arg2, const void * id2)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd(id, " << cmd << ", " << arg1 << ", " << arg2 << ", " << id2 << ")\n";
#endif

    write_char(onInstanceCmd);
    write_id(id);
    write_char(cmd);
    write_char(arg1);
    write_char(arg2);
    write_id(id2);
    flush();
}

void UmlCom::send_cmd(const void * id, OnInstanceCmd cmd, const void * id1)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd(id, " << cmd << ", id1)\n";
#endif

    write_char(onInstanceCmd);
    write_id(id);
    write_char(cmd);
    write_id(id1);
    flush();
}

void UmlCom::send_cmd(const void * id, OnInstanceCmd cmd, const void * id1, const char * arg2)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd(id, " << cmd << ", id1, " << ((arg2) ? arg2 : "") << ")\n";
#endif

    write_char(onInstanceCmd);
    write_id(id);
    write_char(cmd);
    write_id(id1);
    write_string(arg2);
    flush();
}

void UmlCom::send_cmd(const void * id, OnInstanceCmd cmd, unsigned int arg1, const UmlTypeSpec & arg2)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd(id, " << cmd << ", " << arg1 << ", UmlTypeSpec)\n";
#endif

    write_char(onInstanceCmd);
    write_id(id);
    write_char(cmd);
    write_unsigned(arg1);

    if (arg2.type) {
        write_id(arg2.type->_identifier);
        write_string("");
    }
    else {
        write_id(0);
        write_string(arg2.explicit_type);
    }

    flush();
}

void UmlCom::send_cmd(const void * id, OnInstanceCmd cmd, unsigned int arg1, const char * arg2, const char * arg3, const UmlTypeSpec & arg4, const UmlTypeSpec & arg5)
{
#ifdef DEBUGDOUML
    QLOG_INFO() << "UmlCom::send_cmd(id, " << cmd << ", " << arg1 << \", \"" << arg2 << "\", \"" << arg3 << "\", " << ", UmlTypeSpec, UmlTypeSpec)\n";
#endif

    write_char(onInstanceCmd);
    write_id(id);
    write_char(cmd);
    write_unsigned(arg1);
    write_string(arg2);
    write_string(arg3);

    if (arg4.type) {
        write_id(arg4.type->_identifier);
        write_string("");
    }
    else {
        write_id(0);
        write_string(arg4.explicit_type);
    }

    if (arg5.type) {
        write_id(arg5.type->_identifier);
        write_string("");
    }
    else {
        write_id(0);
        write_string(arg5.explicit_type);
    }

    flush();
}
void UmlCom::send_cmd(const void * id, OnInstanceCmd cmd, unsigned int arg1, char arg2, const char * arg3, const char * arg4, const UmlTypeSpec & arg5)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd(id, " << cmd << ", " << arg1 << ", " << (int) arg2 << ", " << ((arg3) ? arg3 : "") << ", " << ((arg4) ? arg4 : "") << ", UmlTypeSpec)\n";
#endif

    write_char(onInstanceCmd);
    write_id(id);
    write_char(cmd);
    write_unsigned(arg1);
    write_char(arg2);
    write_string(arg3);
    write_string(arg4);

    if (arg5.type) {
        write_id(arg5.type->_identifier);
        write_string("");
    }
    else {
        write_id(0);
        write_string(arg5.explicit_type);
    }

    flush();
}

void UmlCom::send_cmd(const void * id, OnInstanceCmd cmd, const Q3PtrVector<UmlItem> & l)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd(id, " << cmd << ", const Q3PtrVector<UmlItem> & l)\n";
#endif

    write_char(onInstanceCmd);
    write_id(id);
    write_char(cmd);

    unsigned n = l.count();
    UmlItem ** v = l.data();
    UmlItem ** vsup = v + n;

    write_unsigned(n);

    for (; v != vsup; v += 1)
        write_id((*v)->_identifier);

    flush();
}

void UmlCom::send_cmd(const void * id, OnInstanceCmd cmd, const Q3PtrVector<UmlClass> & l1, const Q3PtrVector<UmlClass> & l2, const Q3PtrVector<UmlClass> & l3)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd(id, " << cmd << ", const Q3PtrVector<UmlClass> & l1, const Q3PtrVector<UmlClass> & l2, const Q3PtrVector<UmlClass> & l3)\n";
#endif

    write_char(onInstanceCmd);
    write_id(id);
    write_char(cmd);

    unsigned n;
    UmlClass ** v;
    UmlClass ** vsup;

    n = l1.count();
    write_unsigned(n);
    v = l1.data();
    vsup = v + n;

    for (; v != vsup; v += 1)
        write_id(((UmlBaseItem *) *v)->_identifier);

    n = l2.count();
    write_unsigned(n);
    v = l2.data();
    vsup = v + n;

    for (; v != vsup; v += 1)
        write_id(((UmlBaseItem *) *v)->_identifier);

    n = l3.count();
    write_unsigned(n);
    v = l3.data();
    vsup = v + n;

    for (; v != vsup; v += 1)
        write_id(((UmlBaseItem *) *v)->_identifier);

    flush();
}

void UmlCom::send_cmd(const void * id, OnInstanceCmd cmd, anItemKind arg, const void * id2)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd(id, " << cmd << ", " << arg << ", " << id2 << ")\n";
#endif

    write_char(onInstanceCmd);
    write_id(id);
    write_char(cmd);
    write_char(arg);
    write_id(id2);
    flush();
}

void * UmlCom::read_id()
{
    read_if_needed();

    void * a;

    // sizeof(void *) must be the same for DOUML and
    // the plug-out, bypass it
    memcpy((char *) &a, p_buffer_in + 1, sizeof(void *));
    p_buffer_in += sizeof(void *) + 1;
    return a;
}

const char * UmlCom::read_string()
{

    read_if_needed();

    unsigned len = strlen(p_buffer_in) + 1;
    QLOG_INFO() << "reading string of length" << len;
    p_buffer_in += len;

#ifdef TRACE
    QLOG_INFO() << "UmlCom::read_string : \"" << p_buffer_in - len << "\"\n";
    QLOG_INFO() << "String contents are: " << QString::fromLocal8Bit(p_buffer_in - len, len);
#endif

    return p_buffer_in - len;
}

bool UmlCom::read_bool()
{
    read_if_needed();
    QLOG_INFO() << "reading bool" << *p_buffer_in;
    return *p_buffer_in++ != 0;
}

char UmlCom::read_char()
{
    read_if_needed();
    QLOG_INFO() << "reading char" << QChar::fromLatin1(*p_buffer_in);
    return *p_buffer_in++;
}

unsigned int UmlCom::read_unsigned()
{
    read_if_needed();

    p_buffer_in += 4;
    QLOG_INFO() << "reading unsigned" << QChar::fromLatin1(*p_buffer_in);
    QLOG_WARN() << "Some hackery here";
    return (((unsigned char *) p_buffer_in)[-4] << 24) +
           (((unsigned char *) p_buffer_in)[-3] << 16) +
           (((unsigned char *) p_buffer_in)[-2] << 8) +
           ((unsigned char *) p_buffer_in)[-1];
}

void UmlCom::read_item_list(Q3PtrVector<UmlItem> & v)
{
    QLOG_INFO() << "reading item list" ;
    unsigned n = read_unsigned();
    QLOG_INFO() << "item list seems to have a sice of " << n;
    v.resize(n);

#ifdef TRACE
    QLOG_INFO() << "UmlCom::read_item_list " << n << " items\n";
#endif

    // warning : don't use data() to directly store
    // in UmlItem ** else count() will be false later
    for (unsigned index = 0; index != n; index += 1)
        v.insert(index, UmlBaseItem::read_());
}

void UmlCom::fatal_error(const WrapperStr &
#ifdef DEBUG_DOUML
                         msg
#endif
                        )
{
#ifdef DEBUG_DOUML
    QLOG_INFO() << msg << '\n';
#endif

    throw 0;
}

void UmlCom::flush()
{
    if (sock != 0) {
        int len = p_buffer_out - buffer_out - 4;
        QLOG_INFO() << "writing legth to read" << len;
        /* the four first bytes of buffer_out are free to contains the length */
        buffer_out[0] = len >> 24;
        buffer_out[1] = len >> 16;
        buffer_out[2] = len >> 8;
        buffer_out[3] = len;

        len += 4;
        p_buffer_out = buffer_out;

        for (;;) {
            int sent = sock->writeBlock(p_buffer_out, len);

            if (sent == -1) {
                close();	// to not try to send "bye" !
                fatal_error("send error");
            }
            else if ((len -= sent) == 0) {
                sock->flush();
                p_buffer_out = buffer_out + 4/*bytes for length*/;
                return;
            }
            else
                p_buffer_out += sent;
        }
    }
}

unsigned UmlCom::user_id()
{
    send_cmd(miscGlobalCmd, userIdCmd);
    return (unsigned char) read_char();
}

void UmlCom::set_user_id(unsigned uid)
{
    send_cmd(miscGlobalCmd, setUserIdCmd, (char) uid);
}

bool UmlCom::set_root_permission(bool y)
{
    send_cmd(miscGlobalCmd, setRootPermissionCmd, (char) y);
    // read_char only valid if y is TRUE, else com closed
    return (y) ? (bool) read_char() : (bool) FALSE;
}

void UmlCom::send_cmd(CmdFamily f, unsigned int cmd, unsigned int u, char c)
{
#ifdef TRACE
    QLOG_INFO() << "UmlCom::send_cmd((CmdFamily) " << f << ", " << cmd << ", " << u << ", " << (int) c << ")\n";
#endif

    write_char(f);
    write_char(cmd);
    write_unsigned(u);
    write_char(c);
    flush();
}
