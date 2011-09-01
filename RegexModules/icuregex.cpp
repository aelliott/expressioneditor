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
#include "icuregex.hpp"

/*!
 * Create a new IcuRegex regular expression
 *
 * \param   expression  The regular expression to compile
 * \param   parent      This item's parent item
 */
IcuRegex::IcuRegex(QString expression, QObject *parent)
    : RegexBase(expression, parent)
    , _valid(false)
{
    _status = U_ZERO_ERROR;
    _pattern = expression.toStdString().c_str();
    _matcher = new RegexMatcher(_pattern, 0, _status);
    _valid = !U_FAILURE(_status);
}

/*!
 * Free dynamically allocated memory
 */
IcuRegex::~IcuRegex()
{
    delete _matcher;
}

QString IcuRegex::getErrorString() const
{
    return QString(u_errorName(_status));
}

QString IcuRegex::cap(int offset)
{
    UnicodeString val = _matcher->group(offset, _status);

    UConverter *conv = ucnv_open("iso-8859-1", &_status);
    char *dest = new char[1001];
    int32_t targetsize = val.extract(dest, 1000, conv, _status);
    dest[targetsize] = 0;

    return QString(dest);
}

int IcuRegex::captureCount() const
{
    if(!isValid() || _pattern.length() == 0)
        return -1;

    return _matcher->groupCount();
}

QStringList IcuRegex::capturedTexts()
{
    return _captured;
}

int IcuRegex::indexIn(QString string, int offset)
{
    if(!isValid() || string == "" || _pattern.length() == 0)
        return -1;

    _targetString = string.toStdString().c_str();
    _matcher->reset(_targetString);

    if(_matcher->find(offset, _status))
        return _matcher->start(_status);
    else
        return -1;
}

int IcuRegex::lastIndexIn(QString string, int offset)
{
    if(!isValid() || string == "" || _pattern.length() == 0)
        return -1;

    _targetString = string.toStdString().c_str();
    _matcher->reset(_targetString);

    while(_matcher->find(offset, _status))
        offset = _matcher->start(_status);

    if(_matcher->find(offset, _status))
        return _matcher->start(_status);
    else
        return -1;
}

int IcuRegex::matchedLength() const
{
    return _captured.at(0).length();
}

int IcuRegex::pos(int offset)
{
    return _matcher->start(offset, _status);
}

bool IcuRegex::isValid() const
{
    return _valid;
}

bool IcuRegex::exactMatch(const QString &string)
{
    if(!isValid() || string == "" || _pattern.length() == 0)
        return false;

    _targetString = string.toStdString().c_str();
    _matcher->reset(_targetString);
    return _matcher->matches(_status);
}

void IcuRegex::setExpression(QString expression)
{
    delete _matcher;
    _pattern = expression.toStdString().c_str();
    _matcher = new RegexMatcher(_pattern, 0, _status);
    _valid = !U_FAILURE(_status);
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
