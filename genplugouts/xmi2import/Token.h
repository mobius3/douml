#ifndef _TOKEN_H
#define _TOKEN_H



#include <q3valuelist.h>

class FileIn;

//A token correspond to the information of a form <...> or <... /> or </...>
class Token
{
public:
    void read(FileIn & in, bool any);

    //return the work read just after <, may start by /
    const WrapperStr & what() const;

    //return the value of the xmi:type
    const WrapperStr & xmiType() const;

    //return the value of the xmi:id
    const WrapperStr & xmiId() const;

    //return the value of the xmi:idref
    const WrapperStr & xmiIdref() const;

    //return true if the token is </...>
    bool close() const;

    //return true if the token is </what>
    bool close(const char * what) const;

    //return true if the token is <.../>
    bool closed() const;

    //return the value associated to a key, "" if the couple doesn't exist
    const WrapperStr & valueOf(WrapperStr key) const;

    //return TRUE if the couple exist and set v with the value associated to a key
    bool valueOf(WrapperStr key, WrapperStr & v) const;


private:
    //associate a key and a value
    struct Couple {
        WrapperStr key;

        WrapperStr value;

    };



protected:
    Q3ValueList<Couple> _couples;

    //the work after < with out the / if it is </what>
    WrapperStr _what;

    //true if the token is </..>
    bool _close;

    //true if the token is <../>
    bool _closed;

};

inline  const WrapperStr & Token::what() const
{
    return _what;
}

inline const WrapperStr & Token::xmiType() const
{
    return valueOf("xmi:type");
}

inline const WrapperStr & Token::xmiId() const
{
    return valueOf("xmi:id");
}

inline const WrapperStr & Token::xmiIdref() const
{
    return valueOf("xmi:idref");
}

inline bool Token::close() const
{
    return _close;
}

inline bool Token::closed() const
{
    return _closed;
}

#endif
