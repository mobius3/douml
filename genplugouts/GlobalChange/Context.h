#ifndef _CONTEXT_H
#define _CONTEXT_H
#include <QByteArray>



enum Equation {
    NoFilter,
    Filter1,
    And12,
    Or12,
    And12_And23,
    And12_Or23,
    Or12_And23,
    Or12_Or23

};
class Context
{
public:
    Context(const QByteArray & o, const QByteArray & f);

    const char * set_filters(const QByteArray & f1, const QByteArray & f2, const QByteArray & f3, bool w1, bool w2, bool w3, bool and12, bool and23);

    void set_stereotype(const QByteArray & s, bool eq, bool neq);

    void set_targets(bool art, bool cl, bool op, bool att, bool rel);

    void set_language(bool c, bool j, bool p, bool y, bool i);

    bool match_stereotype(const QByteArray & s);

    bool match(QByteArray s);

    void err();

    QByteArray replace(QByteArray s);

    bool onArtifact() const;

    bool onClass() const;

    bool onOperation() const;

    bool onAttribute() const;

    bool onRelation() const;

    bool cpp() const;

    bool java() const;

    bool php() const;

    bool python() const;

    bool idl() const;

    int n_match() const;

    int n_err() const;


protected:
    QByteArray _filter1;

    QByteArray _filter2;

    QByteArray _filter3;

    bool _with1;

    bool _with2;

    bool _with3;

    QByteArray _stereotype;

    bool _is;

    bool _isnot;

    bool _onArtifact;

    bool _onClass;

    bool _onOperation;

    bool _onAttribute;

    bool _onRelation;

    bool _cpp;

    bool _java;

    bool _php;

    bool _python;

    bool _idl;

    QByteArray _old;

    QByteArray _future;

    Equation _equation;

    int _n_match;

    int _n_err;

    bool match(QByteArray s, const QByteArray & filter, bool with);

};

inline void Context::set_stereotype(const QByteArray & s, bool eq, bool neq)
{
    _stereotype = s;
    _is = eq;
    _isnot = neq;
}

inline void Context::set_targets(bool art, bool cl, bool op, bool att, bool rel)
{
    _onArtifact = art;
    _onClass = cl;
    _onOperation = op;
    _onAttribute = att;
    _onRelation = rel;
}

inline void Context::set_language(bool c, bool j, bool p, bool y, bool i)
{
    _cpp = c;
    _java = j;
    _php = p;
    _python = y;
    _idl = i;
}

inline bool Context::onArtifact() const
{
    return _onArtifact;
}

inline bool Context::onClass() const
{
    return _onClass;
}

inline bool Context::onOperation() const
{
    return _onOperation;
}

inline bool Context::onAttribute() const
{
    return _onAttribute;
}

inline bool Context::onRelation() const
{
    return _onRelation;
}

inline bool Context::cpp() const
{
    return _cpp;
}

inline bool Context::java() const
{
    return _java;
}

inline bool Context::php() const
{
    return _php;
}

inline bool Context::python() const
{
    return _python;
}

inline bool Context::idl() const
{
    return _idl;
}

inline int Context::n_match() const
{
    return _n_match;
}

inline int Context::n_err() const
{
    return _n_err;
}

#endif
