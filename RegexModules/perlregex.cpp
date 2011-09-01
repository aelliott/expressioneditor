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
#include "perlregex.hpp"

/*!
 * Create a new PerlRegex backend
 *
 * \param   expression  The expression to translate into PCRE format and compile
 * \param   parent      This object's parent object
 */
PerlRegex::PerlRegex(QString expression, QObject *parent)
    : _valid(true)
{
    expression = parseExpression(expression);
    PcreRegex(expression, parent);
    _regexp = expression;
    PcreRegex::setExpression(expression);
}

/*!
 * Parse the provided expression from perl-style into a more standard PCRE form
 * which can be compiled and used
 *
 * \param   expression  The regular expression in perl-emulation format
 * \return  A PCRE translation of the perl-emulation format expression
 */
QString PerlRegex::parseExpression(QString expression)
{
    if(expression.isEmpty())
        return expression;

    QChar delim = expression.at(0);
    if(expression.indexOf(delim, 1) == -1)
    {
        _valid = false;
        return QString();
    }

    _valid = true;
    int endDelim = expression.lastIndexOf(delim, expression.length()-1);
    QString parsed = expression.mid(1, endDelim-1);
    expression.remove(0, endDelim+1);
    QString modifiers = expression;

    if(!modifiers.isEmpty())
        for(int i = 0; i < modifiers.length(); ++i)
            parsed = QString("(?") + modifiers.at(i) + ")" + parsed;

    return parsed;
}

bool PerlRegex::isValid() const
{
    return (PcreRegex::isValid() && _valid);
}

void PerlRegex::setExpression(QString expression)
{
    _regexp = expression;
    PcreRegex::setExpression(parseExpression(expression));
}
