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
    case PerlEmulation: //TODO: make an actual perl emulator :p
            return new PerlRegex(pattern);
            break;
#endif // NO_PCRE
#ifndef NO_POSIX
        case POSIX:
            return new PosixRegex(pattern);
            break;
#endif // NO_POSIX
#ifndef NO_ICU
        case ICU:
            return new IcuRegex(pattern);
            break;
#endif // NO_ICU
        default:
            // This should never happen
            return new QtRegex(pattern);
    }
}
