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
#ifndef CAPTUREDSTRING_HPP
#define CAPTUREDSTRING_HPP

#include <string>
#include <utility>

/*!
 * \brief   This class is a simple representation of a captured string from a
 *          capture group.
 *
 * The class contains the string itself and its starting position and ending
 * position within the text.
 *
 * It uses only stdlib classes to allow it to be re-used outside of a Qt
 * context if necessary, but this is only precautionary.  In this case there
 * was little difference between Qt and stdlib in terms of how it was written.
 */
class CapturedString
{
public:
    CapturedString(const std::string &text, const int &startpos, const int &endpos);
    std::string getText() const;
    std::pair<int,int> pos() const;
    int start() const;
    int end() const;

private:
    std::string _text;
    std::pair<int,int> _position;
};

#endif // CAPTUREDSTRING_HPP
