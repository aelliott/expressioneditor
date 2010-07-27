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

#include "icuregex.hpp"

IcuRegex::IcuRegex(QString expression, QObject *parent) : RegexBase(expression, parent), valid(false)
{
    status = U_ZERO_ERROR;
    pattern = expression.toStdString().c_str();
    matcher = new RegexMatcher(pattern, 0, status);
    valid = !U_FAILURE(status);
}

IcuRegex::~IcuRegex()
{
    delete matcher;
}

QString IcuRegex::getErrorString() const
{
    return QString(u_errorName(status));
}

QString IcuRegex::cap(int offset)
{
    UnicodeString val = matcher->group(offset, status);

    UConverter *conv = ucnv_open("iso-8859-1", &status);
    char *dest = new char[1001];
    int32_t targetsize = val.extract(dest, 1000, conv, status);
    dest[targetsize] = 0;

    return QString(dest);
}

int IcuRegex::captureCount() const
{
    if(!isValid() || pattern.length() == 0)
        return -1;

    return matcher->groupCount();
}

QStringList IcuRegex::capturedTexts()
{
    return captures;
}

int IcuRegex::indexIn(QString string, int offset)
{
    if(!isValid() || string == "" || pattern.length() == 0)
        return -1;

    targetString = string.toStdString().c_str();
    matcher->reset(targetString);

    if(matcher->find(offset, status))
        return matcher->start(status);
    else
        return -1;
}

int IcuRegex::lastIndexIn(QString string, int offset)
{
    if(!isValid() || string == "" || pattern.length() == 0)
        return -1;

    targetString = string.toStdString().c_str();
    matcher->reset(targetString);

    while(matcher->find(offset, status))
        offset = matcher->start(status);

    if(matcher->find(offset, status))
        return matcher->start(status);
    else
        return -1;
}

int IcuRegex::matchedLength() const
{
    return captures.at(0).length();
}

int IcuRegex::pos(int offset)
{
    return matcher->start(offset, status);
}

bool IcuRegex::isValid() const
{
    return valid;
}

bool IcuRegex::exactMatch(const QString &string)
{
    if(!isValid() || string == "" || pattern.length() == 0)
        return false;

    targetString = string.toStdString().c_str();
    matcher->reset(targetString);
    return matcher->matches(status);
}

void IcuRegex::setExpression(QString expression)
{
    delete matcher;
    pattern = expression.toStdString().c_str();
    matcher = new RegexMatcher(pattern, 0, status);
    valid = !U_FAILURE(status);
}

void IcuRegex::setOptions(RegexpOptions options)
{
    Q_UNUSED(options);
    //TODO
}

void IcuRegex::setCaseSensitivity(bool caseSensitivity)
{
    Q_UNUSED(caseSensitivity);
    //TODO
}

QString IcuRegex::escape(const QString expression)
{
    //TODO
    return expression;
}

QString IcuRegex::escape()
{
    //TODO
    return QString();
}
