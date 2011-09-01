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
#include "qtregex.hpp"

/*!
 * Create a new Qt4 regular expression backend
 *
 * \param   expression  The regular expression to compile and use
 * \param   parent      This object's parent object
 */
QtRegex::QtRegex(QString expression, QObject *parent)
    : RegexBase(expression, parent)
    , _qtRegexp(expression)
{
}

QString QtRegex::getErrorString() const
{
    return _qtRegexp.errorString();
}

QString QtRegex::cap(int offset)
{
    return _qtRegexp.cap(offset);
}

int QtRegex::captureCount() const
{
    return _qtRegexp.captureCount();
}

QStringList QtRegex::capturedTexts()
{
    return _qtRegexp.capturedTexts();
}

int QtRegex::indexIn(QString string, int offset)
{
    return _qtRegexp.indexIn(string, offset);
}

int QtRegex::lastIndexIn(QString string, int offset)
{
    return _qtRegexp.lastIndexIn(string, offset);
}

int QtRegex::matchedLength() const
{
    return _qtRegexp.matchedLength();
}

int QtRegex::pos(int offset)
{
    return _qtRegexp.pos(offset);
}

bool QtRegex::isValid() const
{
    return _qtRegexp.isValid();
}

bool QtRegex::exactMatch(const QString &string)
{
    return _qtRegexp.exactMatch(string);
}

void QtRegex::setExpression(QString expression)
{
    _regexp = expression;
    _qtRegexp.setPattern(expression);
}

void QtRegex::setOptions(RegexBase::RegexpOptions options)
{
    if(options > RegexBase::CaseInsensitive)
    {
        setCaseSensitivity(true);
    }
}

void QtRegex::setCaseSensitivity(bool caseSensitivity)
{
    if(caseSensitivity)
        _qtRegexp.setCaseSensitivity(Qt::CaseSensitive);
    else
        _qtRegexp.setCaseSensitivity(Qt::CaseInsensitive);
}

QString QtRegex::escape()
{
    return QRegExp::escape(_regexp);
}

QString QtRegex::escape(QString expression)
{
    return QRegExp::escape(expression);
}
