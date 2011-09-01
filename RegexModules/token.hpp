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
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <QString>
#include "tokens.hpp"

/*!
 * \brief   Represents a section of a regular expression
 *
 * This class provides a data structure for the tokenised output of the lexing
 * parsers. The token consists of a type, which determines what it is (i.e. a
 * T_LITERAL or a T_ALTERNATION) and optionally (for those that require it) a
 * value stored as a QString.
 */
class Token
{
public:
    Token(RegexpToken tokenType, QString val = QString());

    RegexpToken type() const;
    QString value() const;

    void setType(RegexpToken tokenType);
    void setValue(QString val);

private:
    RegexpToken _type;
    QString _value;
};

#endif // TOKEN_HPP
