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
#include "parser.hpp"

Parser::Parser(QString pattern, QObject *parent)
    : QObject(parent)
    , _expression(pattern)
    , _pos(0)
{
}

Parser::~Parser()
{
    for(std::vector<Token *>::iterator iter = _tokens.begin(); iter != _tokens.end(); ++iter)
        delete *iter;
}

bool Parser::parse(QString pattern)
{
    if(!pattern.isEmpty())
        setExpression(pattern);

    for(std::vector<Token *>::iterator iter = _tokens.begin(); iter != _tokens.end(); ++iter)
        delete *iter;

    _tokens.clear();

    int previousPositon;
    while(_pos < pattern.length())
    {
        handleToken(findMatch());

        // In the case where no progress is being made, exit returning false
        if(previousPositon == _pos)
            return false;

        previousPositon = _pos;
    }

    return true;
}

QString Parser::expression() const
{
    return _expression;
}

std::vector<Token *> Parser::tokens() const
{
    return _tokens;
}

void Parser::setExpression(QString pattern)
{
    _expression = pattern;
}

RegexpToken Parser::findMatch()
{
    RegexpToken token = T_ERROR;
    QString pattern;
    _matchLength = 0;
    QRegExp regexp;

    std::map<RegexpToken, QString>::iterator iter;
    for(iter = _syntax.begin(); iter != _syntax.end(); ++iter)
    {
        pattern = (*iter).second;
        regexp.setPattern(pattern);

        if(regexp.indexIn(_expression, _pos) == _pos)
        {
            if(regexp.matchedLength() > _matchLength)
            {
                _matchLength = regexp.matchedLength();
                token = (*iter).first;
            }
        }
    }

    _matchLength = qMax(_matchLength, 1);

    return token;
}
