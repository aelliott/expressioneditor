/*!
 * \file
 *
 * Copyright (c) 2009-2012 Alex Elliott <alex@alex-elliott.co.uk>
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
#include "regexfactory.hpp"

/*!
 * Creates a new Cpp11Regex object
 *
 * \param   expr    The expression to use
 * \param   parent  This item's parent
 */
Cpp11Regex::Cpp11Regex(QString expr, int format, QObject *parent)
    : RegexBase(expr, parent)
    , _regexp(expr)
    , _matchLength(-1)
    , _valid(true)
    , _error("")
{
    _type = std::regex_constants::ECMAScript;
    if(format != -1)
        switch(format)
        {
        case RegexFactory::CPP11_EXTENDED:
            _type = std::regex_constants::extended;
            break;
        case RegexFactory::CPP11_BASIC:
            _type = std::regex_constants::basic;
            break;
        case RegexFactory::CPP11_AWK:
            _type = std::regex_constants::awk;
            break;
        case RegexFactory::CPP11_GREP:
            _type = std::regex_constants::grep;
            break;
        case RegexFactory::CPP11_EGREP:
            _type = std::regex_constants::egrep;
            break;
        default:
            _type = std::regex_constants::ECMAScript;
        }

    try
    {
        _re = std::regex(expr.toStdString(), _type);
    }
    catch(std::regex_error errorException)
    {
        _valid = false;
        _error = QString(errorException.what());
    }
}

QString Cpp11Regex::getErrorString() const
{
    return _error;
}

QString Cpp11Regex::cap(int offset)
{
    if(offset >= _captured.size())
        return "";

    return _captured.at(offset);
}

int Cpp11Regex::captureCount() const
{
    return _captured.size();
}

QStringList Cpp11Regex::capturedTexts()
{
    return _captured;
}

int Cpp11Regex::indexIn(QString string, int offset)
{
    if(!isValid())
        return -1;

    string = string.mid(offset);
    std::string target = string.toStdString();
    std::smatch results;

    try
    {
        if(!std::regex_search(target, results, _re))
            return -1;
    }
    catch(std::regex_error errorException)
    {
        _error = QString(errorException.what());
        return -1;
    }

    parseResults(results);

    return results.position(0)+offset;
}

int Cpp11Regex::lastIndexIn(QString string, int offset)
{
    if(!isValid())
        return -1;

    std::string target = string.toStdString();
    target = target.substr(offset, target.length()-offset);
    std::smatch results;

    try
    {
        if(!std::regex_search(target, results, _re))
            return -1;
    }
    catch(std::regex_error errorException)
    {
        _error = QString(errorException.what());
        return -1;
    }

    parseResults(results);

    return results.position(results.size()-1)+offset;
}

int Cpp11Regex::matchedLength() const
{
    return _matchLength;
}

int Cpp11Regex::pos(int offset)
{
    if(offset >= _capturePositions.size())
        return -1;

    return _capturePositions[offset];
}

bool Cpp11Regex::isValid() const
{
    return _valid;
}

bool Cpp11Regex::exactMatch(const QString &string)
{
    if(!isValid())
        return false;

    std::string target = string.toStdString();
    std::smatch results;

    try
    {
        if(!std::regex_match(target, results, _re))
        {
            // Even if there is no match, we might want the results, so...
            std::regex_search(target, results, _re);
            if(!results.empty())
                parseResults(results);

            return false;
        }
    }
    catch(std::regex_error errorException)
    {
        _error = QString(errorException.what());
        return false;
    }

    parseResults(results);

    return (results.length(0) == string.length());
}

void Cpp11Regex::setExpression(QString expr)
{
    _regexp = expr;

    // Create a new std::regex object with the new expression
    _re = std::regex(expr.toStdString(), _type);
}

void Cpp11Regex::setOptions(RegexpOptions options)
{
    //NOTE: Complete
}

void Cpp11Regex::setCaseSensitivity(bool caseSensitivity)
{
    //NOTE: Complete
}

void Cpp11Regex::parseResults(std::smatch &results)
{
    _matchLength = -1;
    _captured.clear();
    _capturePositions.clear();

    if(results.empty())
        return;

    _matchLength = results.length(0);

    for(int i = 0; i < results.size(); ++i)
    {
        _captured.append(QString(results.str(i).c_str()));
        _capturePositions.push_back(results.position(i));
    }

    qDebug() << _matchLength;
    qDebug() << _captured;
    for(int i = 0; i < results.size(); ++i)
        qDebug() << "Position " << i << ": " << _capturePositions[i];
}
