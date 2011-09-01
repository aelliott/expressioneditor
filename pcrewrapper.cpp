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
#include "pcrewrapper.hpp"

/*!
 * Create a new PcreWrapper object using the provided expression (if present)
 *
 * \param   expression  The regular expression to compile and use
 */
PcreWrapper::PcreWrapper(std::string expression)
    : valid(false)
    , failed(false)
    , errorStr("")
    , options_(0)
    , matchLength(0)
{
    if(!expression.empty())
    {
        setExpression(expression);
    }
}

/*!
 * Set the regular expression to use
 *
 * \param   expression  The regular expression to compile and use
 */
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

/*!
 * Initialisation to perform before each match, clear out and set up some
 * variables
 */
void PcreWrapper::InitMatch()
{
    captureGroups.clear();
    failed = false;
}

/*!
 * Attempt to perform an exact match of the current regular expression on the
 * provided string.  This is achieved by wrapping the expression in a
 * non-capturing group and appending \\Z
 *
 * \param   string  The string to attempt a complete match on
 * \return  True if a full match can be found, false otherwise
 */
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

/*!
 * Attempt to match any portion of the provided string using the current
 * regular expression, starting at "offset" within the string if one has been
 * provided
 *
 * \param   string  The string to perform our partial match against
 * \param   offset  The offset at which to start matching
 * \return  True if any partial match is found, false otherwise
 */
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

/*!
 * Use pcrecpp to escape the current regular expression and return it as a
 * pattern-format literal
 *
 * \return  The current regular expression in escaped form
 */
std::string PcreWrapper::escape()
{
    return pcrecpp::RE::QuoteMeta(pattern);
}

/*!
 * Use pcrecpp to escape the provided regular expression and return it as a
 * pattern-format literal
 *
 * \return  The provided regular expression in escaped form
 */
std::string PcreWrapper::escape(const std::string &string)
{
    return pcrecpp::RE::QuoteMeta(string);
}

/*!
 * Return the valid flag which determines whether the last attempt to compile a
 * regular expression to use was successful or not
 *
 * \return  True if the last compile was successful, false otherwise
 */
bool PcreWrapper::isValid() const
{
    return valid;
}

/*!
 * Return the length of the last match (capture group \0, the full match)
 *
 * \return  The length of the matched text
 */
unsigned int PcreWrapper::matchedLength() const
{
    return matchLength;
}

/*!
 * Return the number of capture groups in the current pattern
 *
 * \return  The number of capture groups contained in the current regular expression
 */
int PcreWrapper::capturingCount() const
{
    if(!isValid())
        return -1;

    int result;
    pcre_fullinfo(re, NULL, PCRE_INFO_CAPTURECOUNT, &result);
    return result;
}

/*!
 * Return the capture group specified by the offset provided
 *
 * \param   offset  The offset determining the capture group requested
 * \return  The requested capture group, or an empty string on failure
 */
std::string PcreWrapper::cap(unsigned int offset)
{
    if(offset < captureGroups.size())
        return captureGroups.at(offset).getText();
    else
        return "";
}

/*!
 * Returns the starting position of the specified capture group
 *
 * \param   offset  The offset determining the capture group queried
 * \return  The starting position of the queried offset, or -1 on failure
 */
int PcreWrapper::startPos(unsigned int offset)
{
    if(offset < captureGroups.size())
        return captureGroups.at(offset).start();
    else
        return -1;
}

/*!
 * Returns the ending position of the specified capture group
 *
 * \param   offset  The offset determining the capture group queried
 * \return  The ending position of the queried offset, or -1 on failure
 */
int PcreWrapper::endPos(unsigned int offset)
{
    if(offset < captureGroups.size())
        return captureGroups.at(offset).end();
    else
        return -1;
}

/*!
 * Returns any errors from the last attempt to compile the last provided
 * regular expression
 *
 * \return  The last error message encountered
 */
std::string PcreWrapper::error() const
{
    return errorStr;
}
