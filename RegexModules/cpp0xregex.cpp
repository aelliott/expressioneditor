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
#include "cpp0xregex.hpp"

/*!
 * Creates a new Cpp0xRegex object
 *
 * \param   expr    The expression to use
 * \param   parent  This item's parent
 */
Cpp0xRegex::Cpp0xRegex(QString expr, QObject *parent)
    : RegexBase(expr, parent)
    , _matchLength(0)
    , _valid(false)
{
    _regexp = new std::regex(expr.toStdString());
}

QString Cpp0xRegex::getErrorString() const
{
    //NOTE: Complete
    return "";
}

QString Cpp0xRegex::cap(int offset)
{
    //NOTE: Complete
    return "";
}

int Cpp0xRegex::captureCount() const
{
    //NOTE: Complete
    return -1;
}

QStringList Cpp0xRegex::capturedTexts()
{
    return _captured;
}

int Cpp0xRegex::indexIn(QString string, int offset)
{
    //NOTE: Complete
    return -1;
}

int Cpp0xRegex::lastIndexIn(QString string, int offset)
{
    //NOTE: Complete
    return -1;
}

int Cpp0xRegex::matchedLength() const
{
    return _matchLength;
}

int Cpp0xRegex::pos(int offset)
{
    //NOTE: Complete
    return -1;
}

bool Cpp0xRegex::isValid() const
{
    return _valid;
}

bool Cpp0xRegex::exactMatch(const QString &string)
{
    //NOTE: Complete
    return false;
}

void Cpp0xRegex::setExpression(QString expr)
{
    // A regexp object was created in the constructor so there is definitely an
    // instance of std::regex in memory, free it
    delete _regexp;

    // Create a new std::regex object with the new expression
    _regexp = new std::regex(expr.toStdString());
}

void Cpp0xRegex::setOptions(RegexpOptions options)
{
    //NOTE: Complete
}

void Cpp0xRegex::setCaseSensitivity(bool caseSensitivity)
{
    //NOTE: Complete
}

QString Cpp0xRegex::escape()
{
    return escape(getExpression());
}

QString Cpp0xRegex::escape(QString expr)
{
    //NOTE: Complete
    return expr;
}
