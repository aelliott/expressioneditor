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

#include "perlregex.hpp"

PerlRegex::PerlRegex(QString expression, QObject *parent) : _valid(true)
{
    expression = parseExpression(expression);
    PcreRegex(expression, parent);
    regexp = expression;
    pcre.setExpression(expression.toStdString());
}

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
    return (pcre.isValid() && _valid);
}

void PerlRegex::setExpression(QString expression)
{
    regexp = expression;
    pcre.setExpression(parseExpression(expression).toStdString());
}
