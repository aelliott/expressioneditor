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
#include "cpp0xregex.hpp"

/*!
 * Creates a new Cpp0xRegex object
 *
 * \param   expr    The expression to use
 * \param   parent  This item's parent
 */
Cpp0xRegex::Cpp0xRegex(QString expr, QObject *parent)
    : RegexBase(expr, parent)
    , expression(expr)
    , matchLength(0)
    , valid(false)
{
    regexp = new std::regex(expr.toStdString());
}

/*!
 * Gets the current expression out of the object
 *
 * \return  Returns the expression currently in use
 */
QString Cpp0xRegex::getExpression() const
{
    return expression;
}

/*!
 * Gets the returned error string from the regular expression library
 *
 * \return  The last error encountered
 */
QString Cpp0xRegex::getErrorString() const
{
    //NOTE: Complete
    return "";
}

/*!
 * Returns the capture group specified by the given offset
 *
 * \param   offset  The capture group to get
 * \return  The specified capture group
 */
QString Cpp0xRegex::cap(int offset)
{
    //NOTE: Complete
    return "";
}

/*!
 * Returns the number of captured groups in the last match
 *
 * \return  The number of capture groups in the regular expression
 */
int Cpp0xRegex::captureCount() const
{
    //NOTE: Complete
    return -1;
}

/*!
 * Returns a QStringList containing all of the captured groups within the last
 * match
 *
 * \return  All of the matched strings in the last match
 */
QStringList Cpp0xRegex::capturedTexts()
{
    return captured;
}

/*!
 * Returns the index of the first match using the current expression, if no
 * match is found returns -1
 *
 * \param   string  The string to search for a match in
 * \param   offset  The offset to start searching at
 * \return  The index of the first match in the given string
 */
int Cpp0xRegex::indexIn(QString string, int offset)
{
    //NOTE: Complete
    return -1;
}

/*!
 * Returns the index of the last match using the current expression, if no
 * match is found returns -1
 *
 * \param   string  The string to search for a match in
 * \param   offset  The offset to start searching at
 * \return  The index of the last match in the given string
 */
int Cpp0xRegex::lastIndexIn(QString string, int offset)
{
    //NOTE: Complete
    return -1;
}

/*!
 * Returns the length of the last match
 *
 * \return The length of the last match
 */
int Cpp0xRegex::matchedLength() const
{
    return matchLength;
}

/*!
 * Returns the position (offset from the start of the string) of the specified
 * capture group matched
 *
 * \param   offset  The capture group to get the position of
 * \return  The position of the specified capture group
 */
int Cpp0xRegex::pos(int offset)
{
    //NOTE: Complete
    return -1;
}

/*!
 * Returns true if the expression is valid according to the regular expression
 * library used (i.e. no error, or the error code returned means no actual
 * error)
 *
 * \return  True if the expression given is valid, false if not
 */
bool Cpp0xRegex::isValid() const
{
    return valid;
}

/*!
 * Attempts a complete match on the given string using the current regular
 * expression, returns true if a match is found and false otherwise
 *
 * \param   string  The string to attempt a full match against
 * \return  True if an exact match is found, false otherwise
 */
bool Cpp0xRegex::exactMatch(const QString &string)
{
    //NOTE: Complete
    return false;
}

/*!
 * Sets the current regular expression to the provided string, updates valid
 * flag and the error string
 *
 * \param   expr    The new expression
 */
void Cpp0xRegex::setExpression(QString expr)
{
    // A regexp object was created in the constructor so there is definitely an
    // instance of std::regex in memory, free it
    delete regexp;

    // Create a new std::regex object with the new expression
    regexp = new std::regex(expr.toStdString());
}

/*!
 * Sets regular expression options like case sensitivity
 *
 * \param   options The options to be set
 */
void Cpp0xRegex::setOptions(RegexpOptions options)
{
    //NOTE: Complete
}

/*!
 * Sets case sensitivity
 *
 * \param   caseSensitivity True if case sensitive false if not
 */
void Cpp0xRegex::setCaseSensitivity(bool caseSensitivity)
{
    //NOTE: Complete
}

/*!
 * Helper function, returns an escaped version of the current regular
 * expression
 */
QString Cpp0xRegex::escape()
{
    return escape(getExpression());
}

/*!
 * Helper function, returns an escaped version of the provided regular
 * expression
 */
QString Cpp0xRegex::escape(QString expr)
{
    //NOTE: Complete
    return expr;
}
