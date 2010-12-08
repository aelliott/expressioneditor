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

#include "regexfactory.hpp"

/*!
 * Create a new RegexFactory
 *
 * \param   type    The type of regular expression backend to produce pointers
 *                  to
 */
RegexFactory::RegexFactory(int type) : _format(type)
{
}

/*!
 * Update the type of regular expression backend the factory should provide
 * pointers to
 *
 * \param   type    The type of regular expression backend to produce pointers
 *                  for
 */
void RegexFactory::setRegexpFormat(int type)
{
    _format = type;
}

/*!
 * Return the current regexp backend that is to be produced
 *
 * \return  The current type of regular expression backend that is being output
 */
int RegexFactory::format() const
{
    return _format;
}

/*!
 * Main implementation of the factory pattern, produce a regular expression
 * backend optionally using the provided pattern and optionally using a specific
 * regular expression backend (otherwise the current default setting is used)
 *
 * \param   pattern The regular expression to create a backend for
 * \param   format  The regular expression backend to use
 * \return  A base class pointer to the requested regular expression backend
 */
RegexBase* RegexFactory::factory(QString pattern, int format)
{
    int usedFormat = (format == -1) ? _format : format;
    switch(usedFormat)
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
#ifdef WITH_CPP0X
        case CPP0X:
            return new Cpp0xRegex(pattern);
            break;
#endif // WITH_CPP0X
        default:
            // This should never happen
            return new QtRegex(pattern);
    }
}
