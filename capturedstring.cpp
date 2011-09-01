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
#include "capturedstring.hpp"

/*!
 * Constructs a new CapturedString representation with a string, start and end position
 *
 * \param   text    The string that has been captured/matched
 * \param   startpos    The starting position of the matched text within the whole
 * \param   endpos  The end position of the matched text within the whole
 */
CapturedString::CapturedString(const std::string &text, const int &startpos, const int &endpos)
    : _text(text)
    , _position(startpos,endpos)
{
}

/*!
 * Returns the captured string
 *
 * \return  Returns the captured text as an std::string
 */
std::string CapturedString::getText() const
{
    return _text;
}

/*! Returns the start and end position together as a pair<start,end>
 *
 * \return  Returns an std::pair of the stard and end positions where
 *          start is at pair.first and end is at pair.second
 */
std::pair<int,int> CapturedString::pos() const
{
    return _position;
}

/*!
 * Return the captured string's starting position
 *
 * \return  Returns the starting position of the matched string
 */
int CapturedString::start() const
{
    return _position.first;
}

/*!
 * Return the captured string's ending position
 *
 * \return  Returns the ending position of the matched string
 */
int CapturedString::end() const
{
    return _position.second;
}
