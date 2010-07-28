#ifndef REGEXFACTORY_HPP
#define REGEXFACTORY_HPP

#include "qtregex.hpp"
#include "cmakeconfig.hpp"

#ifndef NO_POSIX
#include "posixregex.hpp"
#endif

#ifndef NO_PCRE
#include "pcreregex.hpp"
#endif // NO_PCRE

#ifndef NO_ICU
#include "icuregex.hpp"
#endif // NO_ICU

class RegexFactory
{
public:
    enum RegexType
    {
        Qt,
        PCRE,
        POSIX,
        ICU,
        PerlEmulation
    };

    RegexFactory(int type = 0);
    void setType(int type);
    int type() const;
    RegexBase* factory(QString pattern = QString(), int type = -1);

private:
    int defaultType;
};

#endif // REGEXFACTORY_HPP
