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
#include "posixregex.hpp"
#include "regexfactory.hpp"

/*!
 * Create a new PosixRegex backend
 *
 * \param   expression  The regular expression to compile and use
 * \param   format      The format of POSIX to use (ERE/BRE)
 * \param   parent      This object's parent object
 */
PosixRegex::PosixRegex(QString expression, int format, QObject *parent)
    : RegexBase(expression, parent)
    , _failed(false)
    , _valid(false)
{
    _captured.clear();
    setExpression(expression);
}

/*!
 * Perform cleanup of memory allocated for POSIX's regex matcher
 */
PosixRegex::~PosixRegex()
{
    regfree(&_posix);
}

QString PosixRegex::getErrorString() const
{
    return _errorString;
}

QString PosixRegex::cap(int offset)
{
    if(offset >= captureCount())
        return QString();

    return QString(_captured.at(offset).getText().c_str());
}

int PosixRegex::captureCount() const
{
    return _captured.size();
}

QStringList PosixRegex::capturedTexts()
{
    QStringList list;
    for(int i = 0; i < captureCount(); ++i)
        list << cap(i);
    return list;
}

int PosixRegex::indexIn(QString string, int offset)
{
    if(!isValid())
        return -1;

    string.remove(0, offset);

    regmatch_t pmatch[100];
    int result = regexec(&_posix, string.toAscii(), 100, pmatch, 0);

    if(result != 0)
    {
        _failed = true;
        char error[100];
        regerror(result, &_posix, error, 100);
        _errorString = error;
        return -1;
    }

    parseCaptures(string, pmatch);

    return (pmatch[0].rm_so == -1) ? pmatch[0].rm_so : pmatch[0].rm_so+offset;
}

int PosixRegex::lastIndexIn(QString string, int offset)
{
    if(!isValid())
        return -1;

    int ret, last;
    while((ret = indexIn(string, offset))  != -1)
    {
        offset = ret;
        last = offset;
    }

    return last;
}

int PosixRegex::matchedLength() const
{
    return _matchLength;
}

int PosixRegex::pos(int offset)
{
    return offset;
}

bool PosixRegex::isValid() const
{
    return _valid;
}

bool PosixRegex::exactMatch(const QString &string)
{
    if(!isValid())
        return -1;

    regmatch_t pmatch[100];
    int result = regexec(&_posix, string.toAscii(), 100, pmatch, 0);

    if(result != 0)
    {
        _failed = true;
        char error[100];
        regerror(result, &_posix, error, 100);
        _errorString = error;
    }

    parseCaptures(string, pmatch);

    int length = pmatch[0].rm_eo-pmatch[0].rm_so;
    return (length == string.length());
}

void PosixRegex::setExpression(QString expression)
{
    _regexp = expression;

    if(isValid())
        regfree(&_posix);

    int status = regcomp(&_posix, expression.toStdString().c_str(), REG_EXTENDED);

    if(status != 0)
    {
        _valid = false;
        char error[100];
        regerror(status, &_posix, error, 100);
        _errorString = error;
    }
    else
        _valid = true;
}

void PosixRegex::setOptions(RegexpOptions options)
{
    //
}

void PosixRegex::setCaseSensitivity(bool caseSensitivity)
{
    //
}

QString PosixRegex::escape()
{
    return escape(QString());
}

QString PosixRegex::escape(QString expression)
{
    return expression;
}

void PosixRegex::parseCaptures(QString str, regmatch_t captures[])
{
    for(int i = 0; captures[i].rm_so != -1; ++i)
    {
        int start = captures[i].rm_so;
        int end = captures[i].rm_eo;
        int length = end-start;
        if(i == 0)
            _matchLength = length;
        str.remove(0, start);
        str = str.left(length);
        _captured.push_back(CapturedString(str.toStdString(), start, end));
    }
}
