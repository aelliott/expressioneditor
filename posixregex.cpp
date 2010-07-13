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

#include "posixregex.hpp"

PosixRegex::PosixRegex(QString expression, QObject *parent) : RegexBase(expression, parent), failed(false), valid(false), matched(-1)
{
    captured.clear();
    setExpression(expression);
}

PosixRegex::~PosixRegex()
{
    regfree(&posix);
}

QString PosixRegex::getErrorString() const
{
    return errorString;
}

QString PosixRegex::cap(int offset)
{
    if(offset >= captureCount())
        return QString();

    return QString(captured.at(offset).text().c_str());
}

int PosixRegex::captureCount() const
{
    return captured.size();
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
    int result = regexec(&posix, string.toAscii(), 100, pmatch, 0);

    if(result != 0)
    {
        failed = true;
        char error[100];
        regerror(result, &posix, error, 100);
        errorString = error;
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
    return matched;
}

int PosixRegex::pos(int offset)
{
    return offset;
}

bool PosixRegex::isValid() const
{
    return valid;
}

bool PosixRegex::exactMatch(const QString &string)
{
    if(!isValid())
        return -1;

    regmatch_t pmatch[100];
    int result = regexec(&posix, string.toAscii(), 100, pmatch, 0);

    if(result != 0)
    {
        failed = true;
        char error[100];
        regerror(result, &posix, error, 100);
        errorString = error;
    }

    parseCaptures(string, pmatch);

    int length = pmatch[0].rm_eo-pmatch[0].rm_so;
    return (length == string.length());
}

void PosixRegex::setExpression(QString expression)
{
    regexp = expression;

    if(isValid())
        regfree(&posix);

    int status = regcomp(&posix, expression.toStdString().c_str(), REG_EXTENDED);

    if(status != 0)
    {
        valid = false;
        char error[100];
        regerror(status, &posix, error, 100);
        errorString = error;
    }
    else
        valid = true;
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
            matched = length;
        str.remove(0, start);
        str = str.left(length);
        captured.push_back(CapturedString(str.toStdString(), start, end));
    }
}
