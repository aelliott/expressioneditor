#ifndef REGEXFACTORY_HPP
#define REGEXFACTORY_HPP

#include "pcreregex.hpp"
#include "qtregex.hpp"

class RegexFactory
{
public:
    enum RegexType
    {
        Qt,
        PCRE,
        POSIX
    };

    RegexFactory(int type = -1);
    void setType(int type);
    RegexBase* factory(QString pattern = QString(), int type = -1);

private:
    int defaultType;
};

#endif // REGEXFACTORY_HPP
