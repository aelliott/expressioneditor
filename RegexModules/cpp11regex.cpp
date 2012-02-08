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
#include "cpp11regex.hpp"

/*!
 * Creates a new Cpp11Regex object
 *
 * \param   expr    The expression to use
 * \param   parent  This item's parent
 */
Cpp11Regex::Cpp11Regex(QString expr, int format, QObject *parent)
    : RegexBase(expr, parent)
    , _matchLength(0)
    , _valid(false)
{
    _regexp = new std::regex(expr.toStdString());
}

QString Cpp11Regex::getErrorString() const
{
    //NOTE: Complete
    return "";
}

QString Cpp11Regex::cap(int offset)
{
    //NOTE: Complete
    return "";
}

int Cpp11Regex::captureCount() const
{
    //NOTE: Complete
    return -1;
}

QStringList Cpp11Regex::capturedTexts()
{
    return _captured;
}

int Cpp11Regex::indexIn(QString string, int offset)
{
    //NOTE: Complete
    return -1;
}

int Cpp11Regex::lastIndexIn(QString string, int offset)
{
    //NOTE: Complete
    return -1;
}

int Cpp11Regex::matchedLength() const
{
    return _matchLength;
}

int Cpp11Regex::pos(int offset)
{
    //NOTE: Complete
    return -1;
}

bool Cpp11Regex::isValid() const
{
    return _valid;
}

bool Cpp11Regex::exactMatch(const QString &string)
{
    //NOTE: Complete
    return false;
}

void Cpp11Regex::setExpression(QString expr)
{
    // A regexp object was created in the constructor so there is definitely an
    // instance of std::regex in memory, free it
    delete _regexp;

    // Create a new std::regex object with the new expression
    _regexp = new std::regex(expr.toStdString());
}

void Cpp11Regex::setOptions(RegexpOptions options)
{
    //NOTE: Complete
}

void Cpp11Regex::setCaseSensitivity(bool caseSensitivity)
{
    //NOTE: Complete
}
