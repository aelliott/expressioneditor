/*!
 * \file
 *
 * Copyright (c) 2011 Alex Elliott <alex@alex-elliott.co.uk>
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
#include "token.hpp"

Token::Token(RegexpToken tokenType, QString val)
    : _type(tokenType)
    , _value(val)
{
}

RegexpToken Token::type() const
{
    return _type;
}

QString Token::value() const
{
    return _value;
}

void Token::setType(RegexpToken tokenType)
{
    _type = tokenType;
}

void Token::setValue(QString val)
{
    _value = val;
}
