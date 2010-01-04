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

#ifndef PCREWRAPPER_HPP
#define PCREWRAPPER_HPP

#include <pcre.h>
#include <pcrecpp.h>
#include "capturedstring.hpp"
#include <string>
#include <vector>
#include <utility>

/**
 * This class wraps the C API for PCRE, I decided against using pcrecpp
 * because I couldn't get it to do everything I wanted it to do.
 *
 * For reusability, this doesn't contain Qt Classes.
 */
class PcreWrapper
{
public:
    PcreWrapper(std::string expression = std::string());
    void setExpression(const std::string &expression);
    bool ExactMatch(const std::string &string);
    bool PartialMatch(const std::string &string, int offset = 0);
    std::string escape();
    std::string escape(const std::string &string);

    bool isValid() const;
    unsigned int matchedLength() const;
    int capturingCount() const;

    std::string cap(unsigned int offset = 0);
    int startPos(unsigned int offset = 0);
    int endPos(unsigned int offset = 0);
    std::string error() const;

private:
    void InitMatch();

    std::vector<CapturedString> captureGroups;
    std::string pattern;
    bool valid;
    bool failed;
    std::string errorStr;
    int options_;
    unsigned int matchLength;
    pcre *re;
};

#endif // PCREWRAPPER_HPP
