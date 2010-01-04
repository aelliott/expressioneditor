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
        case PCRE:
            return new PcreRegex(pattern);
            break;
        default:
            // This should never happen
            return new PcreRegex(pattern);
    }
}
