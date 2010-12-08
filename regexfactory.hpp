/*!
 * \file
 * \author Alex Elliott <alex@alex-elliott.co.uk>
 * \version 0.1pre
 *
 * \section LICENSE
 * This file is part of Expression editor
 *
 * Expression editor is Copyright 2009,2010 Alex Elliott <alex@alex-elliott.co.uk>
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
/*!
 * \brief   The RegexFactory class is a simple implementation of the factory
 *          pattern used to provide polymorphic instances of regular expression
 *          backends as a base class pointer
 */

#ifndef REGEXFACTORY_HPP
#define REGEXFACTORY_HPP

#include "RegexModules/qtregex.hpp"
#include "cmakeconfig.hpp"

#ifndef NO_POSIX
#include "RegexModules/posixregex.hpp"
#endif

#ifndef NO_PCRE
#include "RegexModules/pcreregex.hpp"
#include "RegexModules/perlregex.hpp"
#endif // NO_PCRE

#ifndef NO_ICU
#include "RegexModules/icuregex.hpp"
#endif // NO_ICU

#ifdef WITH_CPP0X
#include "RegexModules/cpp0xregex.hpp"
#endif // WITH_CPP0X

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
        POSIX,
#endif // NO_POSIX
#ifndef NO_ICU
        //! ICU style regular expressions
        ICU,
#endif // NO_ICU
#ifdef WITH_CPP0X
        //! C++0x style regular expressions
        CPP0X,
#endif // WITH_CPP0X
        //! Qt4 style regular expressions
        Qt
    };

    RegexFactory(int type = 0);
    void setRegexpFormat(int type);
    int format() const;
    RegexBase* factory(QString pattern = QString(), int type = -1);

private:
    int _format;
};

#endif // REGEXFACTORY_HPP
