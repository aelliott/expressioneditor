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

#include "pcrewrapper.hpp"

PcreWrapper::PcreWrapper(std::string expression) : valid(false), failed(false), errorStr(""), options_(0), matchLength(0)
{
    if(!expression.empty())
    {
        setExpression(expression);
    }
}

void PcreWrapper::setExpression(const std::string &expression)
{
    pattern = expression;
    int errorOffset;
    const char *error;
    re = pcre_compile(expression.c_str(), options_, &error, &errorOffset, NULL);

    if(!re)
    {
        errorStr = std::string(error);
        valid = false;
    }
    else
        valid = true;
}

void PcreWrapper::InitMatch()
{
    captureGroups.clear();
    failed = false;
}

bool PcreWrapper::ExactMatch(const std::string &string)
{
    // Make sure it matches the full string if possible.
    std::string tmp = pattern;
    setExpression(std::string("(?:") + pattern + ")\\Z");

    if(!isValid())
        return false;

    InitMatch();

    bool match = PartialMatch(string);

    setExpression(tmp);

    return (match && string.length() == matchedLength());
}

bool PcreWrapper::PartialMatch(const std::string &string, int offset)
{
    if(!isValid())
        return false;

    InitMatch();

    int outcount = capturingCount()+1;
    int requiredSize = (1 + outcount) * 3;
    int space[21]; // hint from pcrecpp.cc
    int *outvec = (21 >= requiredSize) ? space : new int[requiredSize];
    int rc = pcre_exec(re, NULL, string.c_str(), string.length(), offset, options_, outvec, requiredSize);

    if(rc < 0 && rc != PCRE_ERROR_NOMATCH)
    {
        errorStr = "Error occurred while parsing regular expression";
        failed = true;
        return false;
    }
    else
    {
        failed = false;
    }

    for(int i = 0; i < rc; ++i)
    {
        int start = outvec[2*i];
        int end = outvec[(2*i)+1];
        int length = end-start;
        if(i == 0)
            matchLength = length;

        if(start > -1)
        {
            std::string str = string.substr(start, length);
            captureGroups.push_back(CapturedString(str, start, end));
        }
    }

    return (rc >= 0);
}

std::string PcreWrapper::escape()
{
    return pcrecpp::RE::QuoteMeta(pattern);
}

std::string PcreWrapper::escape(const std::string &string)
{
    return pcrecpp::RE::QuoteMeta(string);
}

bool PcreWrapper::isValid() const
{
    return valid;
}

unsigned int PcreWrapper::matchedLength() const
{
    return matchLength;
}

int PcreWrapper::capturingCount() const
{
    if(!isValid())
        return -1;

    int result;
    pcre_fullinfo(re, NULL, PCRE_INFO_CAPTURECOUNT, &result);
    return result;
}

std::string PcreWrapper::cap(unsigned int offset)
{
    if(offset < captureGroups.size())
        return captureGroups.at(offset).text();
    else
        return "";
}

int PcreWrapper::startPos(unsigned int offset)
{
    if(offset < captureGroups.size())
        return captureGroups.at(offset).start();
    else
        return -1;
}

int PcreWrapper::endPos(unsigned int offset)
{
    if(offset < captureGroups.size())
        return captureGroups.at(offset).end();
    else
        return -1;
}

std::string PcreWrapper::error() const
{
    return errorStr;
}
