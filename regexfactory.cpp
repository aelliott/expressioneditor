#include "regexfactory.hpp"

RegexFactory::RegexFactory(int type) : defaultType(type)
{
}

void RegexFactory::setType(int type)
{
    defaultType = type;
}

int RegexFactory::type() const
{
    return defaultType;
}

RegexBase* RegexFactory::factory(QString pattern, int type)
{
    int usedType = (type == -1) ? defaultType : type;
    switch(usedType)
    {
        case Qt:
            return new QtRegex(pattern);
            break;
#ifndef NO_PCRE
        case PCRE:
            return new PcreRegex(pattern);
            break;
#endif // NO_PCRE
#ifndef NO_POSIX
        case POSIX:
            return new PosixRegex(pattern);
            break;
#endif // NO_POSIX
        default:
            // This should never happen
            return new QtRegex(pattern);
    }
}
