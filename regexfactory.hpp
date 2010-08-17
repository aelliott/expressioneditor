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

class RegexFactory
{
public:
    enum RegexFormat
    {
        Qt,
        PCRE,
        POSIX,
        ICU,
        PerlEmulation
    };

    RegexFactory(int type = 0);
    void setRegexpFormat(int type);
    int format() const;
    RegexBase* factory(QString pattern = QString(), int type = -1);

private:
    int _format;
};

#endif // REGEXFACTORY_HPP
