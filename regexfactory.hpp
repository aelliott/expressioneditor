/*!
 * \file
 *
 * Copyright (c) 2009,2010,2011 Alex Elliott <alex@alex-elliott.co.uk>
 *
 * \section LICENSE
 * This file is part of Expression editor
 *
 * Expression editor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Expression editor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Expression editor.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef REGEXFACTORY_HPP
#define REGEXFACTORY_HPP

#include "RegexModules/regexbase.hpp"
#include "RegexModules/parser.hpp"

#include "cmakeconfig.hpp"

/*!
 * \brief   The RegexFactory class is a simple implementation of the factory
 *          pattern used to provide polymorphic instances of regular expression
 *          backends as a base class pointer
 */
class RegexFactory
{
public:
    /*!
     * Enum of the supported regular expression formats
     */
    enum RegexFormat
    {
#ifndef NO_PCRE
        //! PCRE style regular expressions
        PCRE,
        //! Perl style regular expressions (facilitated by PCRE)
        PerlEmulation,
#endif // NO_PCRE
#ifndef NO_POSIX
        //! POSIX style regular expressions
        C_POSIX_ERE,
        C_POSIX_BRE,
#endif // NO_POSIX
#ifndef NO_ICU
        //! ICU style regular expressions
        ICU,
#endif // NO_ICU
#ifndef NO_CPP11
        //! C++11 style regular expressions
        CPP11_ECMASCRIPT,
        CPP11_BASIC,
        CPP11_EXTENDED,
        CPP11_AWK,
        CPP11_GREP,
        CPP11_EGREP,
#endif // NO_CPP11
        //! Qt4 style regular expressions
        Qt,
        Default
    };

    RegexFactory(RegexFormat type = Qt);
    void setRegexpFormat(RegexFormat type);
    RegexFactory::RegexFormat format() const;
    RegexBase *regexpEngine(QString pattern = QString(), RegexFormat type = Default);
    Parser *regexpParser(RegexFormat type = Default);

private:
    RegexFormat _format;
};

#endif // REGEXFACTORY_HPP
