/**
 * This file is part of Expression editor
 *
 * Expression editor is Copyright 2010 Alex Elliott <alex@alex-elliott.co.uk>
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
 *
 */

#include "qtregex.hpp"

QtRegex::QtRegex(QString expression, QObject *parent) : RegexBase(expression, parent), qtRegexp(expression)
{
}

QString QtRegex::getErrorString() const
{
    return qtRegexp.errorString();
}

QString QtRegex::cap(int offset)
{
    return qtRegexp.cap(offset);
}

int QtRegex::captureCount() const
{
    return qtRegexp.captureCount();
}

QStringList QtRegex::capturedTexts()
{
    return qtRegexp.capturedTexts();
}

int QtRegex::indexIn(QString string, int offset)
{
    return qtRegexp.indexIn(string, offset);
}

int QtRegex::lastIndexIn(QString string, int offset)
{
    return qtRegexp.lastIndexIn(string, offset);
}

int QtRegex::matchedLength() const
{
    return qtRegexp.matchedLength();
}

int QtRegex::pos(int offset)
{
    return qtRegexp.pos(offset);
}

bool QtRegex::isValid() const
{
    return qtRegexp.isValid();
}

bool QtRegex::exactMatch(const QString &string)
{
    return qtRegexp.exactMatch(string);
}

void QtRegex::setExpression(QString expression)
{
    regexp = expression;
    qtRegexp.setPattern(expression);
}

void QtRegex::setOptions(RegexBase::RegexpOptions options)
{
    if(options > RegexBase::CaseSensitive)
    {
        //options &= ~RegexBase::CaseSensitive;
        setCaseSensitivity(true);
    }
}

void QtRegex::setCaseSensitivity(bool caseSensitivity)
{
    if(caseSensitivity)
        qtRegexp.setCaseSensitivity(Qt::CaseSensitive);
    else
        qtRegexp.setCaseSensitivity(Qt::CaseInsensitive);
}

QString QtRegex::escape()
{
    return QRegExp::escape(regexp);
}

QString QtRegex::escape(QString expression)
{
    return QRegExp::escape(expression);
}
