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

#include "regexbase.hpp"

/*!
 * Create a new regexp engine base, initialise various internal members
 */
RegexBase::RegexBase(QString expression, QObject *parent) : QObject(parent), regexp(expression), matchLength(0)
{
    captured.clear();
}

/*!
 * Accessor, provides access to the regular expression string
 *
 * \return String of the current regular expression in use
 */
QString RegexBase::getExpression() const
{
    return regexp;
}

/*!
 * Checks if the regular expression string passed in is empty, true if it is
 * empty, false otherwise
 *
 * \return  True if the regexp string is empty, false otherwise
 */
bool RegexBase::isEmpty() const
{
    return regexp.isEmpty();
}
