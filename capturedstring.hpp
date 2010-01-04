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

#ifndef CAPTUREDSTRING_HPP
#define CAPTUREDSTRING_HPP

#include <string>
#include <utility>

class CapturedString
{
public:
    CapturedString(const std::string &text, const int &startpos, const int &endpos);
    std::string text() const;
    std::pair<int,int> pos() const;
    int start() const;
    int end() const;

private:
    std::string text_;
    std::pair<int,int> position_;
};

#endif // CAPTUREDSTRING_HPP
