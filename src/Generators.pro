TEMPLATE = subdirs
SUBDIRS += CppGenerator\
        CppReverse\
        CppRoundtrip\
        IdlGenerator\
        JavaCat\
        JavaGenerator\
        JavaReverse\
        JavaRoundtrip\
        PhpGenerator\
        PhpReverse\
        PythonGenerator\
        RoundtripBody\
        ProjectControl\
        ProjectSynchro

CODECFORTR      = UTF-8
CODECFORSRC     = UTF-8

CONFIG+=ordered
CONFIG+= warn_on
